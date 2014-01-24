<?php
// $Id: assignments.module,v 1.0 2011/08/09 Exp Saravana$

/**
 * @file
 * Handling Listing page for assignments.
 */

/**
 * My Assignments Page, listing all assets/links assigned to the user
 *
 * Generate the assignment teaser, consists of
 * - title
 * - assiged by user name
 * - Message from assigner
 * list 10 entries paginated or null message as appropriate
 *  @param $status
 *  (Optional), Default is Pending. Available options (1- Pending, 2- Completed)
 *  @param $mobile_flag
 *  (Optional), Default is False. Check whether this method call from mobile or not.
 *  @param $total_count
 *  (Optional), Default is False. Check whether this method call from mobile or not.
 * 
 * @return array with the above fields
 *
 * @todo field name to be changed from asset to link - work with Feroz
 * @see assignment_preprocess_assignment_listing() in assignment.module
 * @see _my_assignments()
 */
function assignment_view($limit = 5, $status = 1, $mobile_flag = FALSE, $total_count = FALSE) {
  global $base_url, $user;
  //Set the title for the page.
  drupal_set_title('Assignments');

  //Assignment Count per page
  //$limit = 10;
  // @todo change both count and Query to support functions

  
  $results = array();
  $flag = 0;
  $j = 0;
  $k = 0;
  //Check whether the request came from Mobile Apps.
  if($mobile_flag) {
    $mobile_assign_page = isset($_GET['page']) ? $_GET['page'] : 0;
    if($status == 1) {
      //Get Cached output for Assignment pending list page.
      $cache_ouput = cache_get("assignment_mobile:uid:" . $user->uid . ":page:" . $mobile_assign_page, "cache_eb");
      if ($cache_ouput->data) {
        return $cache_ouput->data;
      }

      $assignments = _my_assignments(0, $limit, 0, 1, 1, 0, $mobile_flag);
      //if ($total_count) {
      //  global $pager_total_items;
      //  $assign_count = $pager_total_items;
      //}      
    }
    else if($status == 2) {
      //Get Cached output for Assignment completed list page.
      $cache_ouput = cache_get("completed_assignment_mobile:uid:" . $user->uid . ":page:" . $mobile_assign_page, "cache_eb");
      if ($cache_ouput1->data) {
        return $cache_ouput->data;
      }      
      $assignments = _my_assignments(0, $limit, 0, 2, 1, 0, $mobile_flag);
      //if ($total_count) {
      //  global $pager_total_items;
      //  $assign_count = $pager_total_items;
      //}      
    }
  }
  else {
    // Assignment completed tab
    if (arg(2) == 'completed') {
      drupal_add_js(array('assignment_completed_pager' => TRUE), 'setting');
      $assignment_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, ASSIGNMENT_LISTING_COMPLETED_PAGER_ID + 1, 0));
      $cache_ouput = cache_get("assignment_completed_listing:uid:" . $user->uid . ":page:" . $assignment_page, "cache_eb");    
      if ($cache_ouput->data) {
        return $cache_ouput->data;
      }
      else {
        $assignments = _my_assignments(0, $limit, 0, 2, 1, ASSIGNMENT_LISTING_COMPLETED_PAGER_ID);
        $flag = 1;
      }
    }
    // Assignment Pending tab
    else {
      drupal_add_js(array('bridge_basket_assignment' => TRUE), 'setting');
      $assignment_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, ASSIGNMENT_LISTING_PAGER_ID + 1, 0));
      //$cache_ouput = cache_get("assignment_listing:uid:" . $user->uid . ":page:" . $assignment_page, "cache_eb");
      if ($cache_ouput->data) {
        return $cache_ouput->data;
      }
      else {
        $assignments = _my_assignments(0, $limit, 0, 1, 1, ASSIGNMENT_LISTING_PAGER_ID);
      }
    }    
  }
  
  if ($mobile_flag) {
    $j = 0; 
    if (db_affected_rows()) {
      while($date = db_fetch_object($assignments)) {
        $dates[] = $date->assinged_date;
      }
      // get first date
      $date1 = explode('-', array_shift($dates));
      // get last date
      if ($ending_date = end($dates)) {
        $date2 = explode('-', $ending_date);
      }
      else {
        $date2 = $date1;
      }
      //assign both dates
      //mktime(hh, mm, ss, month, day, year);
      $first_date = mktime(23, 59, 59, $date1[1], $date1[0], $date1[2]);
      $second_date = mktime(0, 0, 0, $date2[1], $date2[0], $date2[2]);

    }
    $query = _subtopic_assignment_query($user->uid, $status, 1, $first_date, $second_date);
    if (db_affected_rows()) {
      $i = 0;
      while($obj_sub = db_fetch_object($query)) {
       
        $results[$obj_sub->assinged_date]['subtopics'][$i]['playlist'] = function_exists("node_title")? node_title($obj_sub->cid):NULL;
        $assign = null;
        $results[$obj_sub->assinged_date]['subtopics'][$i]['assignment_type'] = null;
        if(is_numeric($obj_sub->asset)) {
          $results[$obj_sub->assinged_date]['subtopics'][$i]['nid'] = $obj_sub->asset;
          $assign = node_load($obj_sub->asset);
          // when the assignment is a node (asset)
          $assign_title = $assign->title;
        }
        else {
          $assign_title = $obj_sub->title;
        }
        if($assign->type == 'quiz') {
          $results[$obj_sub->assinged_date]['subtopics'][$i]['title'] = $assign_title;
          //For Mobile we need to send the Subtopic ID for Assignment view services.
            $results[$obj_sub->assinged_date]['subtopics'][$i]['subtopic_id'] = $obj_sub->st_id; 
            $results[$obj_sub->assinged_date]['subtopics'][$i]['assigned_uid'] = $obj_sub->to_uid;
            
            $results[$obj_sub->assinged_date]['subtopics'][$i]['assignment_type'] = $assign->type;
            
        }
        else {
          $results[$obj_sub->assinged_date]['subtopics'][$i]['title'] = $assign_title;
          //For Mobile we need to send the Subtopic ID for Assignment view services.
            $results[$obj_sub->assinged_date]['subtopics'][$i]['assigned_uid'] = $obj_sub->to_uid;
            $results[$obj_sub->assinged_date]['subtopics'][$i]['subtopic_id'] = $obj_sub->st_id;
            if(!is_numeric($obj_sub->asset)) {
              $results[$obj_sub->assinged_date]['subtopics'][$i]['assignment_type'] = 'federated'; 
            }
            else if($assign->type == 'asset' || $assign->type == 'bead'){
              $results[$obj_sub->assinged_date]['subtopics'][$i]['assignment_type'] = $assign->type;
              $results[$obj_sub->assinged_date]['subtopics'][$i]['assignment_format_type'] = $assign->field_format[0]['value'];
            }
            else {
              $results[$obj_sub->assinged_date]['subtopics'][$i]['assignment_type'] = $assign->type;
            }
        }
        // generate Assigned by user, create_eduauthor() function is in eb_others.module.
        $results[$obj_sub->assinged_date]['subtopics'][$i]['user'] = create_eduauthor($obj_sub->from_uid);
        if ($flag ==  0) {
          //Fetch the DB value for Visited or Not visited functionality for All assignment types except Quiz Assignment. Based on the value we need to add a class in Assignment listing itemts
          if (db_result(db_query("SELECT as_id FROM {assignment_statistics} WHERE st_id = %d AND uid = %d", $obj_sub->st_id, $obj_sub->to_uid))){
            $results[$obj_sub->assinged_date]['subtopics'][$i]['read status'] = 'read';
          }
          //Here we fetch the value for Visited or Not visited functionality for Quiz assignments.
          elseif(db_result(db_query("SELECT dis_id FROM {eb_group_discussion_statistics} WHERE uid = %d AND dis_nid = %d", $user->uid, $obj_sub->asset))){
            $results[$obj_sub->assinged_date]['subtopics'][$i]['read status'] = 'read';
          }
          else {
            $results[$obj_sub->assinged_date]['subtopics'][$i]['read status'] = 'un read';
          }
        }
        // message from Assigner
        $results[$obj_sub->assinged_date]['subtopics'][$i]['body'] = $obj_sub->message;
        $i++;
      }
    }
    else {
      $results['null_content'] = 'You have no assignments.';
    }
  }
  else {
  
    if (db_affected_rows()) {
      while($obj = db_fetch_object($assignments)) {
        if(is_numeric($obj->asset)) {
          // when the assignment is a node (asset)
          $assign_title = db_result(db_query("SELECT title FROM {node} WHERE nid= %d", $obj->asset));
        }
        else {
          $assign_title = $obj->title;
        }
        $assign = node_load($obj->asset);
  
        if($assign->type == 'quiz') {
          $results[$i]['title'] = l($assign_title, 'node/' . $obj->asset, array('attributes' => array('title' => 'Click to view content' )));
          //For Mobile we need to send the Subtopic ID for Assignment view services.
          if($mobile_flag) {
            $results[$i]['subtopic_id'] = $obj->asset;
            $results[$i]['assignment_type'] = $assign->type;
          }
        } else {
          $results[$i]['title'] = l($assign_title, 'assignment/view/' . $obj->st_id . '/'. $obj->to_uid, array('attributes' => array('title' => 'Click to view content' )));
          //For Mobile we need to send the Subtopic ID for Assignment view services.
          if($mobile_flag) {        
            $results[$i]['subtopic_id'] = $obj->st_id;
            if(!is_numeric($obj->asset)) {
              $results[$i]['assignment_type'] = 'federated'; 
            }
            else if($assign->type == 'asset' || $assign->type == 'bead'){
              $results[$i]['assignment_type'] = $assign->field_format[0]['value'];
            }
            else {
              $results[$i]['assignment_type'] = $assign->type;
            }
          }
        }
  
        // generate Assigned by user, create_eduauthor() function is in eb_others.module.
        $results[$i]['user'] = create_eduauthor($obj->from_uid);
        if ($flag ==  0) {
          //Fetch the DB value for Visited or Not visited functionality for All assignment types except Quiz Assignment. Based on the value we need to add a class in Assignment listing itemts
          if (db_result(db_query("SELECT as_id FROM {assignment_statistics} WHERE st_id = %d AND uid = %d", $obj->st_id, $obj->to_uid))){
            if($mobile_flag){
              $results[$i]['read status'] = 'read';
            }
            else{
              $results[$i]['selected'] = ' selected-author';
            }
            
          }
          //Here we fetch the value for Visited or Not visited functionality for Quiz assignments.
          elseif(db_result(db_query("SELECT dis_id FROM {eb_group_discussion_statistics} WHERE uid = %d AND dis_nid = %d", $user->uid, $obj->asset))){
            if($mobile_flag){
              $results[$i]['read status'] = 'read';
            }
            else{
              $results[$i]['selected'] = ' selected-author';
            }
          }
          else {
            if($mobile_flag){
              $results[$i]['read status'] = 'un read';
            }
            else{
              $results[$i]['selected'] = '';
            }
          }
        }
        // message from Assigner
        $results[$i]['body'] = $obj->message;
        $i++;
      }
    }
    else {
      $results['null_content'] = 'You have no assignments.';
    }
  }
  if($mobile_flag) {
    //Assignment Pending Results
    if($status == 1) {
      $cid = "assignment_mobile:uid:" . $user->uid . ":page:" . $mobile_assign_page;
    }
    else if($status == 2) {
      //Assignment Completed Results
      $cid = "completed_assignment_mobile:uid:" . $user->uid . ":page:" . $mobile_assign_page;
    }
    if(count($i)) {
      $mobile_results['total_count'] = $i;
    }
    $mobile_results['results'] = $results;
    //set the Assignment Pending listing cache
    cache_set($cid, $mobile_results, "cache_eb");
    return $mobile_results;
  }
  //Using assignment_listing theme function is in assignment.module.
  $output = theme('assignment_listing', $results);
  // Assignment completed tab
  if (arg(2) == 'completed') {
    cache_set("assignment_completed_listing:uid:" . $user->uid . ":page:" . $assignment_page, $output, "cache_eb");
  }
  else {
    cache_set("assignment_listing:uid:" . $user->uid . ":page:" . $assignment_page, $output, "cache_eb");
  }

  return $output;
}

/**
 * To get assignment details based on Date
 *
 * @param $uid
 *  It contains Assigned user id
 *
 * @param $status
 *  It contains pending and completed status (0 => pending, 1 => completed)
 *
 * @param $assign_status
 * It contains assigned status
 *
 * @param $first_date
 *  It contains date based on that we generate assignment (begin date)
 *
 * @param $last_date
 *  It contains date based on that we generate assignment (end date)
 *  
 * @return
 *  It contains query results
 *
 */
function _subtopic_assignment_query($uid, $status = 1, $assign_status = 1, $first_date, $last_date) {
  //return db_query("SELECT assign.from_uid, assign.st_id, assign.to_uid, assign.aid, assign.message, curriculum.asset, curriculum.title, curriculum.description FROM assignment assign INNER JOIN assignment_assign aa ON aa.st_id  = assign.st_id INNER JOIN curriculum_topics_assets curriculum ON assign.st_id = curriculum.id INNER JOIN curriculum_topics curriculumtopic ON curriculumtopic.topic_id = curriculum.topic_id WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d AND aa.assign_status = %d and curriculumtopic.cid=%d  GROUP BY  assign.from_uid, assign.to_uid, assign.link", $uid, $uid, $status, $assign_status, $cid);

  

  return db_query("SELECT assign.from_uid, assign.st_id, assign.to_uid, assign.aid, assign.message, curriculum.asset, curriculum.title, curriculum.description, FROM_UNIXTIME( assign.changed, '%%d-%%m-%%Y') AS assinged_date, curriculumtopic.cid FROM {assignment} assign INNER JOIN {assignment_assign} aa ON aa.st_id  = assign.st_id INNER JOIN {curriculum_topics_assets} curriculum ON assign.link = curriculum.asset INNER JOIN curriculum_topics curriculumtopic ON curriculumtopic.topic_id = curriculum.topic_id WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d   AND aa.assign_status = %d AND (assign.changed >=%d and assign.changed <=%d) GROUP BY assign.from_uid, assign.to_uid, assign.link ORDER BY assign.changed DESC", $uid, $uid, $status, $assign_status, $last_date, $first_date);
}
/**
 * Display members assigned to a specific assignment
 *
 * @param $st_id
 * It contains assignment ID, return null content
 *
 * @see theme_assigned_member().
 *
 */
function assigned_member($mobile_flag = FALSE, $playlist_nodeid = FALSE, $subtopic_id = FALSE) {
  global $user;
  drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment.js');

  $individual = array();
  $i = 0;

  //query for getting assigning node title.
  $query = db_fetch_array(db_query("SELECT asset, title FROM {curriculum_topics_assets} WHERE id = %d", $subtopic_id));

  //If the assignment is a Node
  if(is_numeric($query['asset'])){
    $sub_title = node_load($query['asset']);
   drupal_set_title(check_plain($sub_title->title));
  } else {
    //If the assignment is an external link.
    drupal_set_title(check_plain($query['title']));
  }

  //Assigned Member Count per page
  $limit = 10;

  if($_GET['member_status'] == 1  || $_GET['member_status'] == 2) {
    $extra_cond = ' AND aa.assign_status = %d ';
    $status = $_GET['member_status'];
  }
  else if($_GET['member_status'] == 3){
    $extra_cond = '';
  }

  if(!$mobile_flag){
    $query = pager_query("SELECT aa.st_id, aa.uid, aa.assign_status, a.to_uid FROM {assignment} a INNER JOIN {assignment_assign} aa ON a.st_id = aa.st_id WHERE a.from_uid = %d AND a.to_uid != %d AND a.st_id = %d $extra_cond GROUP BY aa.uid ORDER BY created DESC", $limit, 0, NULL, $user->uid,  0, $subtopic_id, $status);      
  }
  else{
    $query = db_query("SELECT aa.st_id, aa.uid, aa.assign_status, a.to_uid FROM {assignment} a INNER JOIN {assignment_assign} aa ON a.st_id = aa.st_id WHERE a.from_uid = %d AND a.to_uid != %d AND a.st_id = %d GROUP BY aa.uid ORDER BY created DESC", $user->uid,  0, $subtopic_id);      
  }

  if (db_affected_rows) {
    while($row = db_fetch_object($query)) {
      //member_detail($uid, $type) function is in eb_others_common.module
      if (function_exists("member_detail") && !$mobile_flag) {
        $individual[$i] = member_detail($row->uid, $row->assign_status, 'undo-assign', 'large');
        $i++;
      }
      else if(function_exists("member_detail") && $mobile_flag){
        $individual[$i] = member_detail($row->uid, $row->assign_status, 'undo-assign', 'large', $mobile_flag);
        //Get user name for Already assigned user for the particular subtopic for Mobile App.
        $assigned_user = user_load($row->uid);
        $individual[$i]['assigned_name'] = $assigned_user->name;
        $i++;          
      }
    }
    return $individual;
  }
}
/**
 * Constructing delete popup form
 *
 * @param arg(3) = $st_id, arg(2) = $uid
 *
 */
function assigned_members_delete_form() {
  global $user, $base_url;

  $form = array();

  $form['st_id'] = array(
    '#type' => 'hidden',
    '#value' =>  arg(3),
    '#id' => 'st_id',
  );
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' =>  arg(2),
    '#id' => 'uid',
  );
  $form['node_id'] = array(
    '#type' => 'hidden',
    '#value' => arg(4),
    '#id' => 'node_id',
  );

  return confirm_form($form, 'Delete', $_SERVER['HTTP_REFERER'], t('Are you sure you want to delete this member from the assignment?'), 'Yes', 'No');
}

/**
 * Constructing reassign popup form
 *
 * @param arg(3) = $st_id, arg(2) = $uid
 *
 */
function assigned_members_reassign_form() {
  global $user, $base_url;

  $form = array();

  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => arg(2),
    '#id' => 'uid',
  );

  $form['st_id'] = array(
    '#type' => 'hidden',
    '#value' => arg(3),
    '#id' => 'st_id',
  );

  $form['node_id'] = array(
    '#type' => 'hidden',
    '#value' => arg(4),
    '#id' => 'node_id',
  );

  return confirm_form($form, 'Reassign', $_SERVER['HTTP_REFERER'], t('Are you sure you want to reassign this user?'), 'Yes', 'No');

}

/**
 * To make members reassign in assigned members page.
 *
 * @param $st_id, $uid
 *
 */
function assigned_members_reassign() {
  global $user;

  //Update the assign_status as reassigned(value as => 2) and set the changed column value as current time
  db_query("UPDATE assignment_assign SET assign_status = %d, changed = %d WHERE uid = %d AND st_id = %d", 1, time(), arg(3), arg(4));
  //Update the value of created and changed as current time
  db_query("UPDATE assignment SET created = %d, changed = %d WHERE to_uid = %d AND st_id = %d", time(), time(), arg(3), arg(4));
  
  $result = db_fetch_array(db_query("SELECT asset, title FROM assignment_assign aa INNER JOIN curriculum_topics_assets cta ON aa.st_id = cta.id WHERE st_id = %d GROUP BY aa.st_id", arg(4)));

  if(is_numeric($result['asset'])) {
    $node_obj = node_load($result['asset']);
    $title = $node_obj->title;
    $nd_name = l($node_obj->title, 'assignment/view/' . arg(4) . '/' . arg(3));
  } else {
    $title = $result['title'];
    $nd_name = l($result['title'], 'assignment/view/'. arg(4) . '/' . arg(3));
  }

  $user_obj = user_load(arg(3));
  $user_name = $user_obj->name;
  $rec[$user_obj->uid] = $user_obj;

  // messsage heartbeat
  if (function_exists("eb_others_popup_link")) {
    $message_id = 'heartbeat_assign_student_assignment';
    $variables = array(
        '@teacher-name' => eb_others_popup_link($user->name, 'user/' . $user->uid),
        '@assigned-status' => 'Re-Assigned',
        '@assignment-name' => $nd_name,
    );
  }
  if (function_exists("heartbeat_api_log")) {
    heartbeat_api_log($message_id, arg(3), $user->uid, arg(4), 0, $variables);
  }
  //construct email
  if (is_array($rec) && (count($rec) > 0)) {
    privatemsg_mail_send($rec, $user, t('Re-Assigned: '.$title), t($user->name .', has  reassigned you ' .$title));    
  }


  drupal_set_message($user_name ." has been successfully reassigned. A message has been sent to the member.");
}

/**
 * To delete members in assigned members page.
 *
 * @param $st_id, $uid
 *
 */
function assigned_members_delete() {
  global $user;
  $result = db_fetch_array(db_query("SELECT asset, title FROM {assignment_assign} aa INNER JOIN {curriculum_topics_assets} cta ON aa.st_id = cta.id WHERE st_id = %d GROUP BY aa.st_id", arg(4)));
  if(is_numeric($result['asset'])) {
    $node_obj = node_load($result['asset']);
    $title = $node_obj->title;
    //$nd_name = l($node_obj->title, 'assignment/view/' . arg(4) . '/' . arg(3));
  }
  else {
    $title = $result['title'];
    //$nd_name = l($result['title'], 'assignment/view/'. arg(4) . '/' . arg(3));
  }
  // Will delete the unassigned user in hearbeat_activity table
  if (module_exists('heartbeat')) {
    $query = heartbeat_ids(arg(4), 'heartbeat_delete_student_assignment', arg(3));
    if (db_affected_rows()) {
      while($row = db_fetch_object($query)) {
        _heartbeat_activity_delete($row->uaid);
      }
    }
  }

  $user_obj = user_load(arg(3));
  $user_name = $user_obj->name;
  $rec[$user_obj->uid] = $user_obj;

  // messsage heartbeat
  $message_id = 'heartbeat_delete_student_assignment';
  if (function_exists("eb_others_popup_link")) {
    $variables = array(
      '@teacher-name' => eb_others_popup_link($user->name, 'user/' . $user->uid),
      '@assignment-name' => $title,
    );
  }
  if (module_exists('heartbeat')) {
    heartbeat_api_log($message_id, arg(3), $user->uid, 0, 0, $variables);
  }
  if ((function_exists("privatemsg_mail_send")) && is_array($rec) && (count($rec) > 0)) {
    privatemsg_mail_send($rec, $user, t('Deletion: '.$title), t($user->name .', has  removed you from assignment '. $title));
  }

  db_query("DELETE FROM assignment_assign WHERE uid = %d and st_id = %d", arg(3), arg(4));
  db_query("DELETE FROM assignment WHERE to_uid = %d and st_id = %d", arg(3), arg(4));

  drupal_set_message($user_name ." has been successfully deleted. A message has been sent to the member.");
}

/**
 * Display members assigned to a specific assignment
 *
 * @param $st_id
 * It contains assignment ID, return null content
 *
 * @see theme_assigned_group().
 *
 *
 */
function assigned_group($mobile_flag = FALSE, $playlist_nodeid = FALSE, $subtopic_id = FALSE) {
  global $user;
  $individual = array();
  $i = 0;

  //query for getting assigning node title.
  $query = db_fetch_array(db_query("SELECT asset, title FROM {curriculum_topics_assets} WHERE id = %d", arg(3)));

  //If the assignment is a Node
  if(is_numeric($query['asset'])){
    $sub_title = node_load($query['asset']);
    drupal_set_title($sub_title->title);
  }
  else{//If the assignment is an external link.
    drupal_set_title($query['title']);
  }

  //Assigned Group Count per page
  $limit = 10;
  if(!$mobile_flag){
    $query = pager_query("SELECT to_gid FROM {assignment} WHERE from_uid = %d AND to_gid != %d AND st_id = %d GROUP BY to_gid ORDER BY created DESC", $limit, 0, NULL, $user->uid, 0, arg(3));    
  }
  else if($mobile_flag){
    $query = db_query("SELECT to_gid FROM {assignment} WHERE from_uid = %d AND to_gid != %d AND st_id = %d GROUP BY to_gid ORDER BY created DESC", $user->uid, 0, $subtopic_id);        
  }


  if (db_affected_rows) {

    while($row = db_fetch_object($query)) {
      //member_detail($uid, $type) function is in eb_others.module
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

    // to get all the group details.
    foreach ($result as $value) {
      // this function is located in eb_others.module.
      $group[] = group_detail($value);
    }
    return $group;
    //$result = theme('assigned_group', $group);
    //return $result;
  }
}

/**
 * Implementation of teacher instruction in assignment
 *
 * @param $st_id
 *  It contains sub topic id
 * @param $assigned_uid
 *  It contains assigned uid
 * @param $mobile_flag
 *  It contains true or false (optional). default is false, it calls from mobile services
 *
 * @return $output
 *  It contains themed html content
 */
function message_teacher($st_id, $assigned_uid, $mobile_flag = FALSE){
  global $user, $base_url;
  $results = array();
  $roles = array();
  $roles = $user->roles;
  // to display the heading for student and teacher in assignment view page...
  //if(in_array("Teacher", $roles)) {
  if (user_access("create assignment")) {
    $results['heading'] = 'Your Instruction';
  }
  //else if(in_array("Student", $roles)) {
  else if (user_access("view assignments")) {
    $results['heading'] = 'Teacher\'s Instruction';
  }

  if($user->uid != $assigned_uid) {
    $alt = 'My Profile';
    $attributes = array('attributes' => array('title' => $alt, 'alt' => $alt), 'html' => TRUE);
  }
  else {
    $alt = 'View Profile';
    $attributes = array('attributes' => array('title' => $alt, 'alt' => $alt, 'class' => 'popups', 'on-popups-options' => '{width: "670px"}'), 'html' => TRUE);
  }

  $query = db_query("SELECT from_uid, message, created FROM {assignment} WHERE st_id = %d AND to_uid" , $st_id, $assigned_uid);
    if (db_affected_rows()) {
      while($obj = db_fetch_object($query)){
        $results['fields']['body'] = $obj->message;
      //In l() itself we defined the redirection path('?destination=assignment/view/' . arg(2)) after the Write Message form submit.
      //$results['fields']['assigned_by'] = l(strip_tags(create_eduauthor($obj->from_uid)), $base_url . '/messages/new/' . $obj->from_uid . '?destination=assignment/view/' . arg(2));
      $user_item = user_load($obj->from_uid);
      $user_no_image = variable_get('user_picture_default', '');
      
      if ($mobile_flag) {
        $results['fields']['picture'] = $user_item->picture ? $user_item->picture : $user_no_image;
      }
      else {
        $results['fields']['picture'] = $user_item->picture ? l(theme_imagecache('members_87', $user_item->picture, $alt, $alt), 'user/'.$user->uid, $attributes) : l(theme_imagecache('members_87', $user_no_image, $alt, $alt), 'user/'.$user->uid, $attributes);  
      } 
      $results['fields']['user_name'] = create_eduauthor($user_item->uid);
      $results['fields']['posted_date'] = format_date($obj->created, 'custom', 'l, F d, Y H:i ');
      }
    }
    else{
      $results['no_content'] = 'No message from Teacher.';
    }
    // for mobile services
    if ($mobile_flag) {
      $output = $results;
    }
    else {
      $output = theme('message_teacher', $results);
    }
    return $output;
}

/**
 * Generate query for assignment listing
 *
 * @param $bridge_limit
 *    It contains Integer value for limits of assignment
 *
 * @param $limit
 *   It contains Integer value for assignment pager
 *
 * @param $uid
 *   This param is set when this function is called from Mobile apps.
 * @param $status
 *   (Optional) default is 1=> it contains pending status, 2 => it contains completed status
 *
 * @param $assign_status
 *   (Optional) default is 1=> it contains assigned status, 2 => it contains user unassigned status
 *
 * @param $pager_id
 *   (Optional) default is 0 -> it contains pager id used to distinct pager(multiple pager in a single page) 
 * @return $qry
 *  It contains query results
 *
 */
function _my_assignments($bridge_limit = 0, $limit = 10, $uid = 0, $status = 1, $assign_status = 1, $pager_id = 0, $mobile_flag = false){
  global $user;

  /*Bridge limit for Bridge page left side block content.*/

  if ($bridge_limit != 0) {
    $qry = db_query("SELECT assign.from_uid, assign.st_id, assign.aid, assign.message, curriculum.asset, curriculum.title, curriculum.description FROM {assignment} assign INNER JOIN {assignment_assign} aa ON aa.st_id  = assign.st_id INNER JOIN {curriculum_topics_assets} curriculum ON assign.link = curriculum.asset WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d   AND aa.assign_status = %d  GROUP BY assign.from_uid, assign.to_uid, assign.link
ORDER BY assign.created DESC LIMIT 0, %d", $user->uid, $user->uid, $status, $assign_status, $bridge_limit);
  }
  else {
    //Assignment listing page, based on the $status we classified Pending, Completed Assignment list.
    // Write sub select query to get the count.
    if ($mobile_flag == false) {
      $count_query = "SELECT COUNT(*) FROM (SELECT assign.from_uid FROM {assignment} assign INNER JOIN {assignment_assign} aa ON aa.st_id  = assign.st_id INNER JOIN {curriculum_topics_assets} curriculum ON assign.link = curriculum.asset WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d GROUP BY assign.from_uid, assign.to_uid, assign.link
  ORDER BY assign.created DESC) q";
        $qry = pager_query("SELECT assign.from_uid, assign.st_id, assign.to_uid, assign.aid, assign.message, curriculum.asset, curriculum.title, curriculum.description FROM {assignment} assign INNER JOIN {assignment_assign} aa ON aa.st_id  = assign.st_id INNER JOIN {curriculum_topics_assets} curriculum ON assign.link = curriculum.asset WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d   AND aa.assign_status = %d  GROUP BY assign.from_uid, assign.to_uid, assign.link
  ORDER BY assign.created DESC", $limit, $pager_id, $count_query, $user->uid, $user->uid, $status, $assign_status);
    }
    else {
      $count_query = "SELECT COUNT(*) FROM (SELECT assign.from_uid FROM {assignment} assign INNER JOIN {assignment_assign} aa ON aa.st_id  = assign.st_id INNER JOIN {curriculum_topics_assets} curriculum ON assign.link = curriculum.asset WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d   AND aa.assign_status = %d GROUP BY FROM_UNIXTIME(assign.changed,'%%d-%%m-%%Y')
  ORDER BY assign.changed DESC) q";
    $qry = pager_query("SELECT FROM_UNIXTIME( assign.changed, '%%d-%%m-%%Y') AS assinged_date FROM {assignment} assign INNER JOIN {assignment_assign} aa ON aa.st_id  = assign.st_id INNER JOIN {curriculum_topics_assets} curriculum ON assign.link = curriculum.asset WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d   AND aa.assign_status = %d  GROUP BY assinged_date
  ORDER BY assign.changed DESC", $limit, $pager_id, $count_query, $user->uid, $user->uid, $status, $assign_status);
    }
  }
  return $qry;
}



/**
 * Constructing Assignment Group delete popup form
 *
 */
function assigned_group_delete(&$form_state) {
  global $user, $base_url;
  drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment.js');
  $form = array();

  $form['cid'] = array(
    '#type' => 'hidden',
    '#value' =>  arg(2),
    '#id' => 'uid',
  );

  $form['st_id'] = array(
    '#type' => 'hidden',
    '#value' =>  arg(3),
    '#id' => 'st_id',
  );

  return confirm_form($form, 'Delete', $_SERVER['HTTP_REFERER'], t('Are you sure you want to delete this group from the assignment?'), t('Yes'), t('No'));

}

/**
 * Custom function for Assignment group delete form.
 * @param
 * Group ID's to delete.
 */
function assigned_group_delete_form(){
 global $user;
  //Check whether the Group ID's are posted or not.
  if ($_POST['gid']) {
    foreach ($_POST['gid'] as $val => $key) {
      $group_title = node_title($key);
      $result = db_query("SELECT st_id, to_uid FROM assignment WHERE to_gid = %d AND st_id = %d", $key, $_POST['st_id']);
      //Fetching the group details and deleting from assignment_assign table
      if (db_affected_rows()) {
        while ($result_exe = db_fetch_object($result)) {
          $query = db_query("SELECT asset, title, aa.uid, aa.st_id FROM assignment_assign aa INNER JOIN curriculum_topics_assets cta ON aa.st_id = cta.id WHERE aa.st_id = %d AND aa.uid = %d GROUP BY aa.st_id", $result_exe->st_id, $result_exe->to_uid);
          if (db_affected_rows()) {
            $rec = '';
            $result_subtopic = db_fetch_array($query);
            $temp_user = user_load($result_subtopic['uid']);
            $rec[$temp_user->uid] = $temp_user;
            if(is_numeric($result_subtopic['asset'])) {
              $title = node_title($result_subtopic['asset']);
            }
            else {
              $title = $result_subtopic['title'];
            }
              // messsage heartbeat
            $message_id = 'heartbeat_delete_student_assignment';

            $variables = array(
            '@teacher-name' => l($user->name, 'user/' . $user->uid, array('attributes' => array('class' => 'popups'))),        '@assignment-name' => $title,
            );
            if (function_exists("heartbeat_api_log")) {
              heartbeat_api_log($message_id, $result_subtopic['uid'], $user->uid, $result_subtopic['st_id'], 0, $variables);
            }
            if ((function_exists("privatemsg_mail_send")) && is_array($rec) && (count($rec) > 0)) {
              privatemsg_mail_send($rec, $user, t('Deletion: '.$title), t($user->name .', has  removed you from assignment '. $title . '<br> ' . l($group_title, 'node/' . $key, array('html' => TRUE)) .' group has been removed from the assignment'));
            }
            // For assgined member record also deleted
            db_query("DELETE FROM {assignment} WHERE to_gid = %d AND to_uid = %d AND st_id =%d", 0, $result_subtopic['uid'], $result_exe->st_id);
          }
            db_query("DELETE FROM {assignment_assign} WHERE st_id = %d AND uid = %d", $result_exe->st_id, $result_exe->to_uid);
        }
      }
      //deleting from assignment table
      db_query("DELETE FROM assignment WHERE to_gid = %d", $key);
    }
    print 'Selected groups has been deleted.';
  }
  else {
    print NULL;
  }
}
/**
 * Assignment basket block pager in ajax load.
 *
 */
function assignment_block_ajax() {
  module_load_include('inc', 'assignment', 'includes/assignment_form');
  print_r(assignment_block_default_content());
  exit;
}
/**
 * Assignment listing page pager in ajax load.
 *
 */
function assignment_listing_ajax() {
  // Assignment completed tab
  if (arg(2) == 'completed') {
    $_GET['q'] = 'bridge/myassignments/completed';
  }
  else {
    $_GET['q'] = 'bridge/myassignments';
  }
  print_r(assignment_view());
  exit;
}