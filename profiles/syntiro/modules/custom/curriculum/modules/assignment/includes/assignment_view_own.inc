<?php
// $Id: assignments.module,v 1.0 2011/08/08 Exp $

/**
 * @file
 * Handling forms for assignment completion related task.
 */

/**
 * This form will be displayed when students clcik on assingmnets which listed on My Assignments Page.
 * The form allows you to set the status of the assignment and to give remarks of the assignment.
 */

/**
 * Comment form will display above post or comments.
 */
// define('UNASSIGNED', 0);

/**
 * Comments will display without user image
 */
define('PENDING', 1);

/**
 * Comments will display with user image
 */
define('COMPLETED', 2);

/**
 * Comments will display without user image
 */
define('ASSIGNED', 1);

/**
 * Comments will display with user image
 */
define('UNASSIGNED', 2);
/**
 * Implementation of assignment view page
 *
 * @param $st_id
 *  It contains subtopic id
 *
 * @param $assigned_uid
 *  It contains assigned user id
 *
 * @param $mobile_flag
 *  It contains true or false (optional). default is false, it calls from mobile services
 *
 * @return $output
 *  It contains html
 *
 */
function assignment_view_own($st_id, $assigned_uid, $mobile_flag = FALSE){
  global $user, $base_url;
  if ($st_id != NULL ) {
    // Generate the content in Assignment Page that include:
    // Title, Content(based on type of Asset/Bead or Quiz), Completed Check box and Remarks Text Area
    // Asset
    //@TODO: Change assignment_statistics column st_id to aid


    if (!db_result(db_query("SELECT a.st_id, a.uid FROM {assignment_statistics} a WHERE a.st_id = %d AND a.uid = %d", $st_id, $user->uid))) {
      db_query("INSERT INTO {assignment_statistics} (uid, access_time, st_id) VALUES (%d, %d, %d)", $user->uid, time(), $st_id);
      cache_clear_all("assignment_listing:uid:" . $user->uid . ":", "cache_eb", TRUE);
      // for mobile clear cache
      cache_clear_all("assignment_mobile:uid:" . $user->uid . ":", "cache_eb", TRUE);
    }


    //Getting the Node ID, From UID for an assignment.

    $assign = db_fetch_array(db_query("SELECT a.link, a.from_uid FROM {assignment} a WHERE a.st_id = %d AND a.to_uid = %d", $st_id, $assigned_uid));

    //Check whether the Assignment having Node id and also it had numeric value, else that assignment is an external link(federated content).
    if (is_numeric($assign['link'])) {
      // it is node and not a federated content
      $node = node_load($assign['link']);
      if ($node->type == 'asset' || $node->type == 'bead'){
        drupal_set_title(check_plain($node->title));
        switch ($node->field_format[0]['value']){
          case 'HTML':
              $results['content'] = $node->body;
          break;
          // use functions that are written in asset module and construct these variables
          case 'VIDEO':
            $image_path = $node->field_custom_file_upload[0]['filepath'];
            if ($mobile_flag) {
              $results['content'] = $image_path;
            }
            else {
              //Get the Video image for Video Asset view page.
              $image = url(drupal_get_path('theme', 'educationhub') . '/images/default_video.jpg');
              $results['content'] = theme('flowplayer', array(
                              'playlist' => array(array( 'url' => $image), array('url' => url($image_path),
                                // this is the SubRib file with captions info
                                // 'captionUrl' => $captions_file_path,
                   'autoPlay' => FALSE, // Turn autoplay off
                    ),
                                ),
                 ));
            }

          break;
          case 'PDF':
            $file_path = $node->field_custom_file_upload[0]['filepath'];
            if ($mobile_flag) {
              $results['iframe_src'] =  $file_path;
            }
            else {
              $results['iframe_src'] = $base_url . '/' . $file_path;  
            }            
            //$results = pdf_content($node->body);
          break;
          case 'IMAGE':
            $image_path = $node->field_custom_file_upload[0]['filepath'];
            if ($mobile_flag) {
              $results['content'] = $image_path;
            }
            else {
              $results['content'] = l(theme('imagecache', 'assetimage', $image_path), $image_path, array('attributes' => array('rel' => 'lightbox'), 'html' => 'TRUE'));  
            }
            
          break;
          case 'DOCUMENT':
          case 'EXCEL':
          case 'PRESENTATION':
            $file_path = $node->field_custom_file_upload[0]['filepath'];
            if ($mobile_flag) {
              $results['iframe_src'] =  $file_path;
            }
            else {
              $results['iframe_src'] = "http://docs.google.com/viewer?url=". $base_url . '/' . $file_path . "&embedded=true";  
            }
            
            break;
          case 'AUDIO':
            // code here.
          break;
          
        }
      }
      //else will include Quiz or any other content type
      //@todo need to remove possiblity of assignming any other content type to curriculum playlist
      else {
        // redirect to the cloned Quiz node or any other content type node
        $results['original_link'] = 'Please '. l('click here',$node->path? $node->path:'node/' . $node->nid) . ' to view the Quiz.';
      }
      $results['type'] = $node->type;
      $results['eb_format_type'] = $node->field_format[0]['value']; 
      //Adding link to the original Assignment page.
      $results['docs_link'] = 'Copyright: ' . l($node->title, $base_url . '/node/' . $assign['link']) . ' was created by ' . create_eduauthor($assign['from_uid']);
      // for mobile services
      $results['title'] = $node->title;
    }
    else {
     
      //Federated content definition
      $query = db_fetch_array(db_query("SELECT asset, title FROM {curriculum_topics_assets} WHERE id = %d", db_result(db_query("SELECT st_id FROM {assignment} WHERE st_id = %d AND to_uid = %d", $st_id, $assigned_uid))));

      //Set the page title.
      drupal_set_title($query['title']);
      $results['iframe_src'] = $query['asset'];
      $results['type'] = "federated"; 
      // use st_id to obtain link assignment table get st_id, curriculum_topic_assets find the federated link

      //Adding link to the original Assignment (web)page.
      $results['docs_link'] = 'Link to Source: ' . l($query['title'], $query['asset'],
      array('attributes' => array('target' => '_blank')));
      // for mobile services
      $results['title'] = $query['title'];
    }
    module_load_include('inc', 'assignment', 'includes/assignment_page');
    module_load_include('inc', 'assignment', 'includes/assignment_form');
    $results['message_teacher_list'] = message_teacher($st_id, $assigned_uid, $mobile_flag);
    // if access from Mobile 
    if($mobile_flag) {
      // for mobile 
      $results['subtopic_id'] = $st_id;
      $results['assignment_details'] = _construct_assignment_details($st_id, $assigned_uid);
      return $results;
    }
    else {
        //attach form $content[form]
      $results['completion_form'] = drupal_get_form('assignment_form_completion', $st_id, $assigned_uid);
      //theme function
      $output = theme('assignment_view', $results);
    }
   
   

  }
  else {
    drupal_not_found();
  }
  
  //Using assignment_listing theme function is in assignment.module.
  return $output;

}

/**
 * construct assignment view page details
 *
 * @param $st_id
 *  It contains sub topic id
 * @param $assigned_uid
 *  It contains assigned uid
 *
 * @return $output
 *  It contains array with assigned details
 * 
 *
 */
function _construct_assignment_details($st_id, $assigned_uid) {
  global $user, $base_url;
   //query for getting assignment remarks & status value node title.
  $output['result'] = db_fetch_array(db_query("SELECT status, remarks, feedback, remarks_time, feedback_time FROM {assignment_assign} WHERE st_id = %d AND uid = %d", $st_id, $assigned_uid));
  // query which is used to display the teacher's name in student login.
  $get_teacher = db_result(db_query("SELECT from_uid FROM assignment WHERE st_id = %d AND to_uid = %d", $st_id, $assigned_uid));
  $output['teacher'] = user_load($get_teacher);
  $output['roles'] = $user->roles;
  $output['student'] = user_load($assigned_uid);

  if (user_access("create assignment")) {
    $output['teacher_name_me'] = 'Your';
    $output['teacher_name'] = create_eduauthor($output['teacher']->uid);
    $output['student'] = user_load($assigned_uid);
    $output['student_name'] = create_eduauthor($output['student']->uid);
    $output['student_name_me'] = $output['student_name'] . ' has ';
    $output['student_name_your'] = $output['student_name'];
    $teacher_attr = array('attributes' => array('title' => 'My Profile', 'alt' => 'My Profile'), 'html' => TRUE);
    $student_attr = array('attributes' => array('title' => 'View Profile', 'alt' => 'View Profile', 'class' => 'popups', 'on-popups-options' => '{width: "670px"}'), 'html' => TRUE);

  }
  else if (user_access("view assignments")) {
    $output['teacher_name'] = create_eduauthor($output['teacher']->uid);
    $output['student_name'] = create_eduauthor($assigned_uid);
    $output['student_name_me'] = 'You have';
    $output['teacher_name_me'] = $output['teacher_name'];
    $output['student_name_your'] = "Your";
    $student_attr = array('attributes' => array('title' => 'My Profile', 'alt' => 'My Profile'), 'html' => TRUE);
    $teacher_attr = array('attributes' => array('title' => 'View Profile', 'alt' => 'View Profile', 'class' => 'popups', 'on-popups-options' => '{width: "670px"}'), 'html' => TRUE);
  }


  if($user->uid == $assigned_uid) {
    $alt = 'My Profile';
    $attributes = array('attributes' => array('title' => $alt, 'alt' => $alt), 'html' => TRUE);
    l(theme_imagecache('members_87', $output['teacher']->picture, $alt, $alt), 'user/'.$user->uid, $attributes);
  }
  else {
    $alt = 'View Profile';
    $attributes = array('attributes' => array('title' => $alt, 'alt' => $alt, 'class' => 'popups', 'on-popups-options' => '{width: "670px"}'), 'html' => TRUE);
  }

  $output['teacher_post_date'] = format_date($output['result']['feedback_time'], 'custom', 'l, F d, Y H:i ');
  $user_no_image = variable_get('user_picture_default', '');
  if (!$output['student']->picture || !$output['teacher']->picture) {
    $output['student_image'] =  l(theme_imagecache('members_87', $user_no_image, 'View Profile', 'View Profile'), 'user/'.$output['student']->uid, $student_attr);
    $output['teacher_image'] =  l(theme_imagecache('members_87', $user_no_image, 'My Profile', 'My Profile'), 'user/'.$output['teacher']->uid, $teacher_attr);
  }
  else {
    $output['teacher_image'] = l(theme_imagecache('members_87', $output['teacher']->picture,'My Profile', 'My Profile'), 'user/'.$output['teacher']->uid, $teacher_attr);
    $output['student_image'] = l(theme_imagecache('members_87', $output['student']->picture, 'View Profile', 'View Profile'), 'user/'.$output['student']->uid, $student_attr);
  }

  $output['student_post_date'] = format_date($output['result']['remarks_time'], 'custom', 'l, F d, Y H:i ');
  return $output;
  
}






/**
 * Get subtopic List
 *
 * @param $nid
 *   It contains curriculum node id
 *
 * @return
 *   It returns subtopic list
 *
 * @todo: Move to assignment_report.inc
 */
function subtopic_list($nid, $gid = NULL, $uid = NULL) {
  if (!empty($gid)) {
    $pattern = '%' . $gid . '%';
    $query = db_query("SELECT TA.id FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = %d
AND  A.from_uid = %d AND A.to_gid LIKE '%s'", $nid, $uid, $pattern);
  }
  else {
    $query = db_query("SELECT TA.asset, TA.title, TA.type, TA.id FROM {curriculum_topics} OGA INNER JOIN {curriculum_topics_assets} TA ON TA.topic_id = OGA.topic_id WHERE OGA.cid = %d", $nid);
  }
  return $query;
}

/**
 * Get Group List
 *
 * @param $nid
 *   It contains curriculum node id
 * @param $uid
 *   It contains user id
 *
 * @return
 *   It returns Group list
 *
 * @todo: Move to assignment_report.inc
 */
function get_group_list($nid, $uid) {

  $query = db_query("SELECT A.to_gid FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = %d
AND A.to_gid != %d AND A.from_uid = %d", $nid,  0, $uid);
  if (db_affected_rows) {
    while($row = db_fetch_object($query)) {
      $gid = explode("," , $row->to_gid);
      $to_gid[] = array_unique($gid);
    }

    //static variable alignment.
    $result = array();

    // to make multiple arrays in to single array
    // Loop outer array
    if(count($to_gid) > 0) {
      foreach ($to_gid as $sub) {
        // Loop inner arrays
        foreach ($sub as $val) {
          // Check for duplicates
          if (!in_array($val, $result)) {
            // Add to result array
            $result[] = $val;
          }
        }
      }
    }
  }
  return $result;
}


/*
 * function used to theme the group dropdown list in Report level1
 *
 * @param $values
 *  It contains collection of group id in an array
 *
 * @return
 *  It contains themed
 */
function theme_group_list_dropdown($values) {
  drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment_report.js');
  $output = '<div class="list-one group-list-one selected-list"><div class="selectbox-list seleted-option">All</div></div><ul class="custom-selectboxes-replaced-list" id="assign-available-option" style="display:none">';
  $output .= '<li value=0>All</li>';
  foreach($values as $key) {
    $output .= '<li value=' . trim($key) . '>' . node_title($key) . '</li>';
  }
	$output .= '</ul>';

  // If count of values not equal to zero it will print the themed output else it returns nothing.
  if(count($values) != 0) {
  return $output;
  } else {
    return '';
  }
}
