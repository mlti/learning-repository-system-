<?php

// $Id: assignments.module,v 1.0 2011/08/08 Exp $

/**
* @file
* Handling forms for assignment module
*/
/**
* The main Assignment form that gets triggered when we click assign icon in curriculum page.
*
* The form allows you to assign a node to a user or flag it to a group
* On form submit an emial is sent to a user with the node link oR
* To all the users of the Group
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


function assignment_form($form_state, $assign_subtopics = NULL, $assign_options = 1) {
  global $user, $base_url;
  drupal_add_js(drupal_get_path('module', 'recommend') . '/recommend.js');
  drupal_add_js(drupal_get_path('module', 'eb_search') . '/js/json_parse.js');
  drupal_add_js(array('ed_search_userselect' => array()), 'setting');
  //Adding Jquery UI js files for Autocomplete functionality in Assignment form.
  jquery_ui_add(array('ui.widget', 'ui.position', 'ui.autocomplete'));
  drupal_add_js(drupal_get_path('module', 'assignment') . '/js/custom_autocomplete.js');
  //Creating Java script setting variable for passing the Sub topic Id to autocomplete function in assignment_autocomplete.js
  drupal_add_js(array('nid' => $assign_subtopics), 'setting');
  $form = array();
  //Adding a div for whole form.
  $form['#prefix'] = '<div class="assignment-new-form search-align art-actions-block ">';
  $form['#suffix'] = '</div>';
  $form['assign_options'] = array(
    '#type' => 'hidden',
    '#value' => $assign_options,
  );
  $form['assign_groups'] = array(
    '#title' => t('Communities'),
    '#attributes' => array('readonly' => 'readonly'),
    '#type' => 'textfield',
    '#prefix' => '<div class="rec-groups " style="display:none">',
    '#suffix' => '<div class="group-search-img">' . l(theme_image(drupal_get_path('theme', 'educationhub') . "/images/browse-button.jpg", "Browse", "Browse"), 'group/assignment', array('attributes' => array('class' => 'popups', 'title' => 'Browse to add communities', 'on-popups-options' => '{ width: "350px", height: "100px"}'), 'html' => TRUE)) . '</div></div>',
    '#theme' => 'recommend_input_theme',
    '#rules' => array('check_user'),
  );
  //}

  $form['assign_recipient'] = array(
    '#type' => 'textfield',
    '#title' => t('Users'),
    '#default_value' => '',
    '#maxlength' => 256,
    '#size' => 1550,
    '#rules' => array('check_user'),
    '#theme' => 'recommend_input_theme',
    '#suffix' => '<div class="user-search-img">' . l(theme_image(drupal_get_path('theme', 'educationhub') . "/images/browse-button.jpg", "Browse", "Browse"), 'popupsearch/assignment', array('attributes' => array('class' => 'popups', 'title' => 'Browse to add users', 'on-popups-options' => '{ width: "350px", height: "100px"}'), 'html' => TRUE)) . '</div>'
  );

  $form['assign_subtopics'] = array(
    '#type' => 'hidden',
    '#value' => $assign_subtopics,
  );
  //check if this is for internal link or external link
  //and set the details , make this a support function
  if ($assign_subtopics) {
    //node id is passed as argument 1, so get the node details
    $query = db_fetch_array(db_query("SELECT asset, title, type FROM {curriculum_topics_assets} WHERE id = %d", $node_link));
    //Check whether the Asset is Numeric(Internal Asset) or not(External Asset).
    if(is_numeric($query['asset'])){
      $nodeobj = node_load($query['asset']);
      $asset = $nodeobj->nid;
      $type = $nodeobj->type;
      $link_title = $nodeobj->title;
      $link_desc = '';
    }
    else{//External Asset content.
      $type = $query['type'];
      $link_title = $query['title'];
      $link_desc = '';
    }
  }
  
  $form['assign_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#required' => TRUE,
    '#rows' => 6,
    '#default_value' => 'Please drop your instructions here..',
    '#rules' => array('check_assign_body'),
    '#resizable' => TRUE,
  );
  $form['assign_asset'] = array(
    '#type' => 'hidden',
    '#value' => $asset,
  );
  $form['assign_node_type'] = array(
    '#type' => 'hidden',
    '#value' => $type,
  );
  $form['assign_link_title'] = array(
    '#type' => 'hidden',
    '#value' => $link_title,
  );
  $form['assign_link_desc'] = array(
    '#type' => 'hidden',
    '#value' => $link_desc,
  );
  $form['assign_submit'] = array(
    '#prefix' => '<div class="button-main">',
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#suffix' => '</div>',
  );
  $form['#theme'] = 'assign_form_theme';
  return $form;
}


/**
 *
 * Theme function for Assignment form.
 *
 */
function theme_assign_form_theme($form){
  //Construct custom select box in Assignment form page
  $output = '<a class="close" title="Close" href="">Close</a>';
  $output .= '<div class="assign-to clearfix"><div class="assignment-options"><span>Assign To: </span><div class="selected-dropdown"><div class="selected-list"><div class="seleted-option"><a href="javascript:;">Users</a></div></div>';
  $output .= '<div id="assign-available-option"><div class="user-option"><a href="javascript:;">Users</a></div><div class="group-option"><a href="javascript:;">Communities</a></div></div>';
  $output .= '</div></div>';
  $output .= drupal_render($form['assign_options']);
  $output .= drupal_render($form['assign_groups']);
  $output .= drupal_render($form['assign_recipient']);
  $output .= '</div><div class="assign-detail">' . drupal_render($form['assign_subject']);
  $output .= drupal_render($form['assign_body']);
  $output .= drupal_render($form['assign_asset']);
  $output .= drupal_render($form['assign_node_type']);
  $output .= drupal_render($form['assign_link_title']);
  $output .= drupal_render($form['assign_link_desc']);
  $output .= drupal_render($form['assign_submit']);
  $output .= drupal_render($form['assign_cancel']) . '</div>';
  $output .= drupal_render($form);
  return $output;
}

/*
* Implementing hook_validate().
*
* It is used to validate the custom assign form
*/
function assignment_validate($form, &$form_state) {
  global $user;
  $error = '';
  switch ($form['assign_options']['#post']['assign_options']) {
    case 1:
      //condition to check weather the user name field is empty or not.
      if (!$form['assign_recipient']['#post']['assign_recipient']) {
        form_set_error($form['assign_recipient']['#default_value'], t('User name can not be empty.'));
      }
      else {
        $blank_space = trim($form['assign_recipient']['#post']['assign_recipient']);
        //Creating array of users
        $to_users = explode(',', $form_state['values']['assign_recipient']);
        /* Ckecking for Null content in Array Final Element */
        if (trim($to_users[count($to_users) - 1]) == '') {
          array_pop($to_users);
        }
        // Passing user id to the validate the cases.
        foreach($to_users as $key => $val) {
          $validate = validate_check($val, $form_state['clicked_button']['#post']['assign_subtopics']);
          if(count($validate) > 0){
            $return_value[] = $validate;
          }
        }
      }
      if (empty($blank_space)) {
        $error = t('User name can not be empty.') . '<br>';
      }
      if(count($return_value) > 0){
        foreach($return_value as $key => $value){
          // checking waeather the users are valid or not.
          if (isset($value['not_valid_user'])) {
            $not_user_names[] = _return_string($value['not_valid_user']);
          }
          // validation to check weather he is assigning to himself.
          if ($value['current_user'] == TRUE) {
            $current_user_names = 'Yes';
          }
          // validation to check weather the assigned users have permissions to access the content.
          if (count($value['no_perm_user']) > 0) {
            $no_perm_user_names[] = _return_string($value['no_perm_user']);
          }
          // validation to check weather the assigned users have been already assigned users or not.
          if (count($value['already_assgined_user']) > 0) {
            $al_assign_user_names[] = _return_string($value['already_assgined_user']);
          }
          // validation to check weather the assigned users have been already assigned assets or not.
          if (count($value['already_assigned_asset']) > 0) {
            $al_assign_asset_names[] = _return_string($value['already_assigned_asset']);
          }
        }
      }
      //Error construction for Invalid User names starts here
      if(count($not_user_names) > 0){
        $not_valid_error = implode(', ', $not_user_names);
        if (count($not_user_names) == 1) {
          $error = $error . $not_valid_error . ', is not a valid user.<br>';
        } else {
          $error = $error . $not_valid_error . ', are not valid users.<br>';
        }
      }
      //Error construction for Invalid User names ends here
      //Error construction for assigning him/herself starts here
      if (count($current_user_names) > 0) {
        $error = $error . 'Can not assign to yourself! <br>';
      }
      //Error construction for assigning him/herself ends here
      //Error construction for Permission denied User names starts here
      if(count($no_perm_user_names) > 0){
        $no_perm_error = implode(', ', $no_perm_user_names);
        if (count($no_perm_user) == 1) {
          $error = $error . $no_perm_error . ', does not have permissions to view assignment.<br>';
        }
        else {
          $error = $error . $no_perm_error . ', do not have permissions to view assignment.<br>';
        }
      }
      //Error construction for Permission denied User names ends here
      //Error construction for Already assigned User names starts here
      if(count($al_assign_user_names) > 0){
        $al_assign_error = implode(', ', $al_assign_user_names);
        if (count($already_assgined_user) == 1) {
          $error = $error . $al_assign_error . ', has already been assigned this assignment.<br>';
        } else {
          $error = $error . $al_assign_error . ', have already been assigned this assignment.<br>';
        }
      }
      //Error construction for Already assigned User names ends here
      //Error construction for Already assigned User names starts here
      if(count($al_assign_asset_names) > 0){
        $al_assign_asset_error = implode(', ', $al_assign_asset_names);
        if (count($already_assigned_asset) == 1) {
         $error = $error . $al_assign_asset_error . ', has already been assigned this assignment.<br>';
        } else {
         $error = $error . $al_assign_asset_error . ', have already been assigned this assignment.<br>';
        }
      }
      // This error message will concatenate will all other error messages.
      if ($error) {
        $error = $error . 'Please correct and reassign.';
        form_set_error($form['assign_recipient']['#default_value'], t($error));
      }
    break;
    case 2:
    // This validation is to check weather the user has selected the community checkbox or not.
    if (!$form['assign_recipient']['#post']['assign_groups']) {
      form_set_error($form['assign_recipient']['#default_value'], t('Please select a community.'));
    }
    // If all communities are assigned for the specific sub topic the following error message will display.
    if ($form['assign_recipient']['#post']['assign_groups'] == 'All communities are assigned for this sub topic.') {
      form_set_error($form['assign_recipient']['#default_value'], t('As all communities are already assigned, You can not able to submit this form.'));
    }
    // Validation to check where the assignment message should cotain 100 characters.
    //if ($form['assign_recipient']['#post']['assign_body'] != '') {
    //  if (strlen($form['assign_recipient']['#post']['assign_body']) < 100) {
    //    form_set_error($form['assign_recipient']['#default_value'], t('Assignment Message should contain at least 100 characters.'));
    //  }
    //}
    break;
  }
}

function validate_check($val, $sub_topicid = 0) {
  global $user;

  $arr = array();
  $counter = '';

  if (trim($val)) {
    $temp_user = user_load(array('name' => trim($val)));
    if (!$temp_user) {
      // The user is not valid
      $not_valid_user[$counter] = $val;
      $arr['not_valid_user'][$counter] = $val;
    } else {
      // User can not assign to himself
      // If current user throw a message, can not assign to yourself!
      if ($temp_user->uid == $user->uid) {
      $current_user = TRUE;
      $arr['current_user'] = TRUE;
      } else {
        // Check if user has view assignments permissions and add to $no_perm_user
        if (!user_access('view assignments', $temp_user)) {
          $no_perm_user[$counter] = $temp_user->name;
          $arr['no_perm_user'][$counter] = $val;
        } else {
          // Check if user has an entry in assignment table for the same curriculum & topic, if he does add to $already_assgined_user
          $exist_aid = db_fetch_array(db_query("SELECT aid, to_uid FROM {assignment} WHERE st_id = %d AND from_uid = %d AND to_uid = %d", $sub_topicid, $user->uid, $temp_user->uid));
          if ($exist_aid['aid']) {
            $already_assgined_user[$counter] = $temp_user->name;
            $arr['already_assgined_user'][$counter] = $val;
          }
          else {
            // check if user has an entry in assignment table for the same node id by the same teacher for a different teacher, update $aleardy_assigned_asset
            $asset_nid = db_result(db_query("SELECT t.asset FROM {curriculum_topics_assets} t WHERE t.id= %d", $sub_topicid));
            if (is_numeric($asset_nid)) {
              if (db_result(db_query("SELECT a.aid FROM {assignment} a WHERE a.to_uid = %d AND a.link = %d", $temp_user->uid, $asset_nid))) {
                $aleardy_assigned_asset[$counter] = $temp_user->name;
                $arr['aleardy_assigned_asset'][$counter] = $val;
              }
            }
          }
        }
      }
    }
    $counter += 1;
  }

  return $arr;
}

function assignment_form_submit($form, &$form_state) {
  global $base_url, $user;
  // Assign to Users and Group
  $options_heartbeat['attributes'] = array('target' => '_blank');
  if(count($form_state['clicked_button']['#post']['assign_subtopics']) > 0){
    $subtopics = explode(',', $form_state['clicked_button']['#post']['assign_subtopics']);
    $i = 0;
    //For each subtopic
    foreach($subtopics as $key => $sub_id) {  
      //Assign to Users.
      if ($form_state['values']['assign_recipient']) {
        $to_users = explode(',', $form_state['values']['assign_recipient']);
       
        /* Ckecking for Null content in Array Final Element */
        if (trim($to_users[count($to_users) - 1]) == '') {
          array_pop($to_users);
        }
        $message = t($form_state['values']['assign_body']);

        if(count($to_users) > 0){   
          foreach ($to_users as $key => $val) {
            $users_arr = assignment_entry($sub_id, $val, 'user', '', $message);
            if($users_arr['assign_now']){
              $assigned_now[] = $users_arr['assign_now'];
            }
            else if($users_arr['already_assigned']){
              $already_assigned[] = $users_arr['already_assigned'];
            }
            else if($users_arr['assign_now_user']){
              $assigned_now_user[] = $users_arr['assign_now_user'];
            }
            //get users uid 
            $user_id = db_result(db_query("SELECT uid FROM {users} WHERE mail='%s'", $val));
            //clear the cache
            cache_clear_all("assignment_completed_listing:uid:" . $user_id . ":", "cache_eb", TRUE);
            cache_clear_all("assignment_listing:uid:" . $user_id . ":", "cache_eb", TRUE);
            cache_clear_all("assignment_basket:uid:" . $user_id . ":", "cache_eb", TRUE);
            // for mobile clear cache
            cache_clear_all("assignment_mobile:uid:" . $user_id . ":", "cache_eb", TRUE);
          }
        }
      }
      //Assign to Users of selected Community.
      if ($form_state['values']['assign_groups']) {
        $group_array = array();
        $to_groups = explode(',', $form_state['values']['assign_groups']);
        foreach ($to_groups as $key => $value) {
          // Get Group title with link for watchdog notic and confirmation message
          $group[] = l(node_title($value), 'node/' . $value);

          $to_users = array();
          $uid_group = db_query("SELECT uid FROM (og_uid) WHERE uid != %d AND nid = %d", 1, $value);
          while ($result_uid = db_fetch_object($uid_group)) {
            $to_users[] = $result_uid->uid;
          }

          $message = t($form_state['values']['assign_body']);
          if(count($to_users) > 0){
            foreach($to_users as $key => $userid){
              $users_arr = assignment_entry($sub_id, $userid, 'group', $value, $message);
              if($users_arr['assign_now']){
                $assigned_now[] = $users_arr['assign_now'];
              }
              else if($users_arr['already_assigned']){
                $already_assigned[] = $users_arr['already_assigned'];
              }
              else if($users_arr['assign_now_user']){
                $assigned_now_user[] = $users_arr['assign_now_user'];
              }
              //clear the cache
              cache_clear_all("assignment_completed_listing:uid:" . $userid . ":", "cache_eb", TRUE);
              cache_clear_all("assignment_listing:uid:" . $userid . ":", "cache_eb", TRUE);
              cache_clear_all("assignment_basket:uid:" . $userid . ":", "cache_eb", TRUE);
              // for mobile clear cache
              cache_clear_all("assignment_mobile:uid:" . $userid . ":", "cache_eb", TRUE);
            }
          }
        }
      }

      //query for getting assigning node title.
      $query = db_query("SELECT asset, title FROM {curriculum_topics_assets} WHERE id = %d", $sub_id);
      $result = db_fetch_array($query);

      if (is_numeric($result['asset'])) {
        $node_title = check_plain(node_title($result['asset']));
      }
      else{
        $node_title = check_plain($result['title']);
      }

      // Making watchdog entries.
      //generate assigned user list for watchdog entry
      if(count($assigned_now_user) > 0) {
        $user_list = implode(', ', $assigned_now_user);
      }
      
      $play_id = db_result(db_query("SELECT CT.cid FROM {curriculum_topics} CT INNER JOIN {curriculum_topics_assets} CTA ON CT.topic_id = CTA.topic_id WHERE CTA.id=%d", $sub_id));
      if(!empty($user_list)) {
        //watchdog('assignment', 'Your Assignment, ' . l($node_title, 'node/' . arg(2)) . ', has been sent to ' . $user_list . '.');
        watchdog('assignment', 'Your Assignment, ' . l($node_title, 'node/' . $play_id) . ', has been sent to ' . $user_list . '.');
      }
      //Construct Drupal confirmation message
      if((count($assigned_now) > 0) && (count($already_assigned) > 0)) {
          $now = format_plural(count($assigned_now), l('1 new student', 'assignment/list/' . $play_id . '/' . $sub_id), l('@count new students', 'assignment/list/' . $play_id . '/' . $sub_id));
        $already = format_plural(count($already_assigned), l('1 student', 'assignment/list/' . $play_id . '/' . $sub_id), l('@count students', 'assignment/list/' . $play_id . '/' . $sub_id));
        drupal_set_message($node_title . ': ' . $now . ' were assigned and ' . $already . ' were already assigned.');
        // To get confirmation message in mobile services
        $form_state["values"]["success"][$i] = $node_title . ': ' . $now . ' were assigned and ' . $already . ' were already assigned.';
        $i++;
      }
      elseif((count($assigned_now) > 0) && (count($already_assigned) == 0)){
        $now = format_plural(count($assigned_now), l('Selected student', 'assignment/list/' . $play_id . '/' . $sub_id), 'All ' . l('@count new students', 'assignment/list/' . $play_id . '/' . $sub_id) . ' were');
        drupal_set_message($node_title . ': ' . $now . ' assigned.');
        // To get confirmation message in mobile services
        $form_state["values"]["success"][$i] = $node_title . ': ' . $now . ' assigned.';
        $i++;
      }
      elseif((count($assigned_now) == 0) && (count($already_assigned) > 0)){
        $already = format_plural(count($already_assigned), l('Selected student', 'assignment/list/' . $play_id . '/' . $sub_id), 'All ' . l('@count students', 'assignment/list/' . $play_id . '/' . $sub_id) . ' were');
        drupal_set_message($node_title . ': ' . $already . ' already assigned.');
        // To get confirmation message in mobile services
        $form_state["values"]["success"][$i] =$node_title . ': ' . $already . ' already assigned.';
        $i++;
      }
      elseif ((count($assigned_now) == 0) && (count($already_assigned) == 0)){
        drupal_set_message($node_title . ': No student Associated with this Community');
        // To get confirmation message in mobile services
        $form_state["values"]["success"][$i] = $node_title . ': No student Associated with this Community';
        $i++;
      }
      unset($assigned_now);
      unset($already_assigned);
      unset($assigned_now_user);
    }
  }
  //clear the cache
  cache_clear_all("playlist_report_list:uid:" . $user->uid . ":", "cache_eb", TRUE);
}

function assignment_entry($sub_id, $userid, $option, $group_id, $message){
  global $user, $base_url;
  $rec = '';
  $output = array();
  if (trim($userid)) {
    //need to optimize logic
    $st_id = db_fetch_array(db_query("SELECT asset,title from curriculum_topics_assets where id = %d", $sub_id));
    $nd_name = '';
    $hrt_aid = '';

    if($option == 'user') {
      $temp_user = user_load(array('mail' => trim($userid)));
      $exist_aid = db_fetch_array(db_query("SELECT aid, to_uid FROM {assignment} WHERE st_id = %d AND from_uid = %d AND to_uid = %d", $sub_id, $user->uid, $temp_user->uid));
    }
    else {
      $temp_user = user_load(array('uid' => trim($userid)));
      $exist_aid = db_fetch_array(db_query("SELECT aid, to_gid FROM {assignment} WHERE st_id = %d AND from_uid = %d AND to_uid = %d", $sub_id, $user->uid, $temp_user->uid));
    }

    if (!$exist_aid['aid']) {
      if (user_access('view assignments', $temp_user)) {
        db_query("INSERT INTO {assignment}
         (st_id, from_uid, to_gid, to_uid, created, changed,  subject, message, link)
          VALUES
        (%d, %d, %d, %d, %d, %d,  '%s', '%s', '%s')", $sub_id, $user->uid, $group_id, $temp_user->uid, time(), time(), $subject, $message, $st_id['asset']);

        $assign_status = ASSIGNED;
        $completion_status = PENDING;

        $tot_result = db_result(db_query("SELECT count(st_id) as total from {assignment_assign} WHERE st_id = %d and uid = %d", $sub_id, $temp_user->uid));
          // If the data doesn't exist in assignment_assign table. The following query will execute.
        if ($tot_result == 0) {
          db_query("INSERT INTO {assignment_assign} (st_id, uid, changed, status, assign_status) VALUES (%d, %d, %d, '%s', '%s')", $sub_id, $temp_user->uid, time(), $completion_status, $assign_status);
        }

        $rec[$temp_user->uid] = $temp_user;

        if (!trim($st_id['title'])) {
            $nd_name = l(node_load($st_id['asset'])->title, 'assignment/view/' . $sub_id . '/' . $temp_user->uid);
        }
        else {
            $nd_name = l($st_id['title'], 'assignment/view/' . $sub_id . '/' . $temp_user->uid);
        }
        if (function_exists("heartbeat_api_log")) {
          $message_id = 'heartbeat_assign_student_assignment';
          $variables = array(
            '@teacher-name' => eb_others_popup_link($user->name, 'user/' . $user->uid),
            '@assigned-status' => 'assigned',
            '@assignment-name' => $nd_name,
          );
          heartbeat_api_log($message_id, $temp_user->uid, $user->uid, $sub_id, 0, $variables);
        }
        // Get node title with link for watchdog notic and confirmation message
        $user_links[] = eb_others_popup_link($val, 'user/' . $temp_user->uid);

        //query for getting assigning node title.
        $query = db_query("SELECT asset, title FROM {curriculum_topics_assets} WHERE id = %d", $sub_id);
        $result = db_fetch_array($query);

        if (is_numeric($result['asset'])) {
          $subject = node_title($result['asset']);
          $type = db_result(db_query("SELECT type FROM {curriculum_topics_assets} WHERE id = %d", $sub_id));
          // To send title with the assignment message.
          if ($type == 'quiz') {
            $nodeobj = node_load($result['asset']);
            // title of the subtopic
            $msg_content = $message . "<br>" . "View Assignments: " . $base_url . "/" . $nodeobj->path;
          }
          else {
            $msg_content = $message . "<br>" . "View Assignments: " . $base_url . "/assignment/view/" . $sub_id ."/" . $temp_user->uid;
          }
        }
        else {
          $subject = $result['title'];
          $msg_content = $message . "<br>" . "View Assignments: " . $result['asset'];
        }
        if (is_array($rec) && (count($rec) > 0)) {
          privatemsg_mail_send($rec, $user, 'Assignment for ' . $subject, $msg_content);          
        }
        $output['assign_now'] = $temp_user->uid;
        $output['assign_now_user'] = l($temp_user->name, 'user/' . $temp_user->uid);
      }
    }
    else{
      $output['already_assigned'] = $temp_user->uid;
    }
  }
  return $output;
  }


function _return_string($no_perm_user) {
  $counter = 0;

  foreach ($no_perm_user as $key => $val) {
    if(trim($val)) {
      $temp_user = $temp_user . trim($val);
    }
    $counter += 1;
  }

  return $temp_user;
}


/**
 * Get the collection of users in autocomplete depends on the sub topic id.
 *
 * @param $string
 *      It contains the letters which typed by the user.
 *
 * @return
 *    Selected usernames in array format.
 *
 */
function assignment_autocomplete($string = '') {
  global $user;
  $names = array();
  // 1: Parse $string and build list of valid user names.
  $fragments = explode(',',  $_GET['term']);
  foreach ($fragments as $index => $name) {
    if ($name = trim($name)) {
      $names[$name] = $name;
    }
  }
  // By using user_validate_user we can ensure that names included in $names are at least logisticaly possible.
  // 2: Find the next user name suggestion.
  $fragment = array_pop($names);
  $matches = array(); 
  //if (user_access("view assignments")) {
  //  $result = db_query("SELECT p.perm FROM {role} r INNER JOIN {permission} p ON p.rid = r.rid WHERE r.rid IN (" . db_placeholders($user->roles) . ")", array_keys($user->roles));
  // 
  //}
  //$rid = " ur.rid IN ('" .  implode("', '", $names) . "')";
  
  if (!empty($fragment)) {
    //This Autocomplete will be work on Assign more page
    if(is_numeric(arg(2))){
    $result = db_query_range("SELECT cp.field_profile_first_name_value, cp.field_profile_last_name_value, u.mail,  u.picture FROM {users} u INNER JOIN {node} n ON (u.uid = n.uid) INNER JOIN {content_type_profile} cp ON (cp.nid = n.nid) LEFT JOIN {users_roles} ur ON u.uid = ur.uid WHERE cp.field_profile_first_name_value LIKE '%s%%' AND (u.mail NOT IN ('" .  implode("', '", $names) . "')) AND ur.rid = %d AND u.uid NOT IN (SELECT to_uid FROM {assignment} a LEFT JOIN {users} u ON u.uid = a.to_uid  WHERE a.from_uid = %d AND a.st_id = %d GROUP BY to_uid ORDER BY u.uid)", $fragment,  4, $user->uid, arg(2), 0, 10);
   
    }
    else{//This Autocomplete will be work on Playlist page
      $result = db_query_range("SELECT cp.field_profile_first_name_value, cp.field_profile_last_name_value, u.mail,  u.picture  FROM {users} u INNER JOIN {node} n ON (u.uid = n.uid) INNER JOIN {content_type_profile} cp ON (cp.nid = n.nid) LEFT JOIN {users_roles} ur ON u.uid = ur.uid WHERE cp.field_profile_first_name_value LIKE '%s%%' AND (u.mail NOT IN ('" .  implode("', '", $names) . "')) AND ur.rid = %d", $fragment, 4, 0, 10); 
    }

    $prefix = count($names) ? implode(", ", $names) .", " : '';
    // 3: Build proper suggestions and print.
    while ($user_res = db_fetch_object($result)) {
      
      //$matches[$prefix . $user_res->mail .", "] = $user_res->name;
      if( $user_res->picture ) {
        $user_pic =   $user_res->picture;
      } else {
        $user_pic =   variable_get('user_picture_default','');
      }

      $user_image = theme('imagecache', 'autocomplete_user_profile_image_32', $user_pic, '', '');
      
      //Call custom function for constructing Autocomplete Users. Written in eb_others.module
      $res = generate_autocomplete_user_name($user_res->mail, check_plain($user_res->field_profile_first_name_value), check_plain($user_res->field_profile_last_name_value), $user_image);
      
      $matches[$prefix . $user_res->mail .", "] = $res;   
    }
  }
  // convert to object to prevent drupal bug, see http://drupal.org/node/175361
  drupal_json($matches);
}




function assignment_block_form() {
  // Commented due to Log entry

  global $base_url;
  $form = array();
  $form['#attributes'] = array('style' => 'display: none');
  $form['mars-content'] = array(
    '#type' => 'markup',
    '#value' => '<div id="assignment-block-content">' . assignment_block_default_content() .'</div>',
  );
  return $form;
}

function assignment_block_default_content() {
  global $user;
  module_load_include('inc', 'assignment', 'includes/assignment_page');
  $assignment_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, ASSIGNMENT_BASKET_PAGER_ID + 1, 0));
  $cache_ouput = cache_get("assignment_basket:uid:" . $user->uid . ":page:" . $assignment_page, "cache_eb");
  if ($cache_ouput->data) {
    return $cache_ouput->data;
  }
  else  {
    //$results['class_active'] = ' title-active';
    $count_query = "SELECT COUNT(*) FROM (SELECT assign.from_uid FROM {assignment} assign INNER JOIN {assignment_assign} aa ON aa.st_id  = assign.st_id INNER JOIN {curriculum_topics_assets} curriculum ON assign.link = curriculum.asset WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d GROUP BY assign.from_uid, assign.to_uid, assign.link) q";
  
    $assignments = pager_query("SELECT assign.from_uid, assign.st_id, assign.to_uid, assign.aid, assign.message, curriculum.asset, curriculum.title, curriculum.description FROM {assignment} assign INNER JOIN {assignment_assign} aa ON aa.st_id  = assign.st_id INNER JOIN {curriculum_topics_assets} curriculum ON assign.link = curriculum.asset WHERE assign.to_uid = %d AND aa.uid = %d AND aa.status = %d   AND aa.assign_status = %d  GROUP BY assign.from_uid, assign.to_uid, assign.link
   ORDER BY assign.created DESC", 5, ASSIGNMENT_BASKET_PAGER_ID, $count_query, $user->uid,$user->uid, 1, 1);
  
    if (db_affected_rows()) {
      while($obj = db_fetch_object($assignments)){
        if(is_numeric($obj->asset)){
          // when the assignment is a node (asset)
          $assign = node_load($obj->asset);
  
          if($assign->type == 'quiz') {
            $items[] = '<div class="assignment-links '. $class_type .'"  content_title="'. $assign->title .'" >' . l(teaser_nodes($assign->title, NULL, NULL, 26, FALSE), $assign->path, array('attributes' => array('title' => 'Click to view content' ))) . '</div>';
          }
          else {
            $items[] = '<div class="assignment-links '. $class_type .'"  content_title="'. $assign->title .'" >' . l(teaser_nodes($assign->title, NULL, NULL, 26, FALSE), 'assignment/view/' . $obj->st_id . '/' . $user->uid, array('attributes' => array('title' => 'Click to view content' ))) . '</div>';
          }
        }
        else {
          // when the assignment is an affiliated partner link
          $items[] = '<div class="assignment-links '. $class_type .'"  content_title="'. $obj->title .'" >' . l(teaser_nodes($obj->title, NULL, NULL, 26, FALSE), 'assignment/view/' . $obj->st_id . '/' . $user->uid, array('attributes' => array('title' => 'Click to view content' ))) . '</div>';
        }
        $i++;
      }
      $output = theme('item_list', $items);
      $pager = theme('pager', NULL, $limit, ASSIGNMENT_BASKET_PAGER_ID);
    }
    else {
      $output = t("<p>No Assignments</p>");
    }
    //SET the Pending Assignment block cache
    cache_set("assignment_basket:uid:" . $user->uid . ":page:" . $assignment_page, $output . $pager, "cache_eb"); 
    return $output . $pager;
  }
}

/**
 * Form Designed for Assignment Completetion.
 *
 * @param $st_id
 *  It contains subtopic id
 *
 * @param $assigned_uid
 *  It contains assigned user id
 *
 * @return
 *   A form to complete the assingmnet
 *
 */
function assignment_form_completion($form_state, $st_id, $assigned_uid) {
  global $user, $base_url;
  //Adding assignment.js for Assignment completion form  validation.
  drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment.js');
  
  // Assignment details
  $content = _construct_assignment_details($st_id, $assigned_uid);
 
  if($content['result']['status'] == 1) {
    $status = UNASSIGNED;
    drupal_add_js(array('assignment' => array('remarks' => '')), 'setting');
  }
  else if($content['result']['status'] == 2) {
    drupal_add_js(array('assignment' => array('remarks' => $content['result']['remarks'])), 'setting');
    drupal_add_js(array('assignment' => array('s_name' => $content['student_name'])), 'setting');
    drupal_add_js(array('assignment' => array('s_image' => $content['student_image'])), 'setting');
    drupal_add_js(array('assignment' => array('s_p_date' => $content['student_post_date'])), 'setting');

    $status = COMPLETED;
  }
  if(!empty($content['result']['feedback'])) {
    drupal_add_js(array('assignment' => array('feedback' => $content['result']['feedback'])), 'setting');
    drupal_add_js(array('assignment' => array('t_name' => $content['teacher_name'])), 'setting');
     drupal_add_js(array('assignment' => array('t_image' => $content['teacher_image'])), 'setting');
    drupal_add_js(array('assignment' => array('t_p_date' => $content['teacher_post_date'])), 'setting');
  }
  $form = array();
  $form['subtopic_id'] = array(
    '#type' => 'hidden',
    '#value' => $st_id,
  );
  $form['assigned_uid'] = array(
    '#type' => 'hidden',
    '#value' => $assigned_uid,
  );
  //in_array("Student", $content['roles'])
  if(user_access("view assignments") && !$content['result']['remarks']) {
    $form['completion_status'] = array(
      '#type' => 'checkbox',
    //  '#default_value' => $status,
      '#required' => TRUE,
      '#title' => t('I have completed this assignment.'),
    );
    $form['completion_remarks'] = array(
      '#type' => 'textarea',
      //'#title' => t('Remarks'),
      '#default_value' => $content['result']['remarks'],
      '#required' => TRUE,
      '#cols' => 60,
      '#rows' => 17,
      '#prefix' => '<div class="listing-common-box-remarks"><div class="discussion-date-time"><label for="edit-completion-remarks">Remarks: *</label></div><div id="edit-completion-remarks-wrapper-box">',
      '#description' => t('Maximum 1000 characters.'),
      '#rules' => array('char_1000'),
    );

    $form['completion_submit'] = array(
      '#prefix' => '<div class="button-main">',
      '#suffix' => '</div></div></div>',
      '#type' => 'submit',
      '#value' => t('Submit'),
    );
  }
  if ($content['result']['remarks']) {
    $form['remarks_completed'] = array(
      '#type' => 'markup',
      '#value' => '<div class="assingment-completion">' . $content['student_name_me'] .' Completed this Assignment!</div><div class="listing-common-box"><div class="discussion-date-time">' . $content['student_name_your'] . ' Remark\'s  </div><div class="common-listing-content clearfix"><div class="float-left image-common assignment-listing"><div class="mem-image">'. $content['student_image'] . '</div><div class="mem-name">' . $content['student_name'] . '</div></div><div class="listing-common-desc"><div class="posted-by">' . $content['student_post_date'] . '</div><p>' . $content['result']['remarks'] . '</p></div></div><div class="listing-common-footer"></div></div>',
    );
  }
  if ($content['result']['feedback']) {
    $form['feedback_completed'] = array(
      '#type' => 'markup',
      '#value' => '<div class="listing-common-box"><div class="discussion-date-time">' . strip_tags($content['teacher_name_me']) . ' Feedback  </div><div class="clearfix common-listing-content"><div class="float-left image-common assignment-listing"><div class="mem-image">' . $content['teacher_image'] . '</div><div class="mem-name">' . $content['teacher_name'] . '</div></div><div class="listing-common-desc"><div class="posted-by">' . $content['teacher_post_date'] .'</div><p>' . $content['result']['feedback'] . '</p></div></div><div class="listing-common-footer"></div></div>',
    );
  }
  return $form;
}

/**
 * Assignment Completetion process done here.
 *
 * @param $form && $form_state
 *
 * @return
 *   It returns success message if everything goes right.
 * @todo: Move to assignment_form.inc
 *
 * @see privatemsg_mail_asset_send() is in eb_others_common.inc
 */
function assignment_form_completion_submit($form, &$form_state) {
  global $user, $from_uid;

  // checking the status weather it is completed or not.
  if($form_state['values']['completion_status'] == 0) {
    $status = PENDING;
  }
  else if($form_state['values']['completion_status'] == 1) {
    $status = COMPLETED;
  }
  // Loading private message module to send messages
  module_load_include('module', 'privatemsg', 'privatemsg');

  // Assigning the remarks to a variable
  $remarks = $form_state['values']['completion_remarks'];
  $flag = 0;
  db_query("UPDATE {assignment_assign} SET status = %d, remarks = '%s', remarks_time = %d WHERE st_id = %d AND uid = %d", $status, trim($remarks), time(), $form_state['values']['subtopic_id'], $form_state['values']['assigned_uid']);
  // for service if some error occurs
  if (!db_affected_rows()) {
    $flag = 1;
  }
  $assigned = db_fetch_array(db_query("SELECT from_uid, link, created, aid FROM {assignment} WHERE st_id = %d AND to_uid = %d" , $form_state['values']['subtopic_id'], $form_state['values']['assigned_uid']));
  //$user_name =   db_result(db_query("SELECT name FROM {users} WHERE uid=%d", $assigned->from_uid));
  $temp_user_list = user_load($assigned['from_uid']);
  // Assigning the users id to an array.
  $arry_receipients[$temp_user_list->uid] = $temp_user_list;

  // to get node title in confirmation message.
  if(is_numeric($assigned['link']) && function_exists("node_title")) {
    $title = node_title(trim($assigned['link']));
  }
  else {
    $title = $assigned['link'];
  }

  //construct email to teacher after the completion of assignment of the student.
  if(is_array($arry_receipients) && (count($arry_receipients) > 0)){
    privatemsg_mail_asset_send($arry_receipients, $user, t('Assignment ' . $title . ' has been completed successfully'), t($form_state['values']['completion_remarks']));    
  }
  //clear the cache
  cache_clear_all("assignment_completed_listing:uid:" . $form_state['values']['assigned_uid'] . ":", "cache_eb", TRUE);
  cache_clear_all("assignment_listing:uid:" . $form_state['values']['assigned_uid'] . ":", "cache_eb", TRUE);
  cache_clear_all("assignment_basket:uid:" . $form_state['values']['assigned_uid'] . ":", "cache_eb", TRUE);
  cache_clear_all("playlist_report_list:uid:" . $assigned['from_uid'] . ":", "cache_eb", TRUE);
  // for mobile clear cache
  cache_clear_all("assignment_mobile:uid:" . $form_state['values']['assigned_uid'] . ":", "cache_eb", TRUE);
  cache_clear_all("completed_assignment_mobile:uid:" . $form_state['values']['assigned_uid'] . ":", "cache_eb", TRUE);
  
  if ($form_state['values']['completion_status'] == 1) {
    // start:: for user points calculation
    // user  defined hook: hook_eb_points;
      $assigned['type']  = 'asset_assignment';
      module_invoke_all('eb_points', 'after save', $assigned);
    // stop
    
    //Setting success message and making entry in watchdog.
    $message = 'Thank you for completing the assignment. An email notification has been sent to your teacher with your remarks.';
    if ($flag != 1) {
      $form_state["values"]["message"]["success"] = $message;
      drupal_set_message($message);
      watchdog('assignment', $message);
    }
    else {
      $form_state["values"]["message"]["failure"] = "Error Occured";
    }
  }
  else if($remarks != '') {
    if ($flag != 1) {
      $message = 'Your remarks have been updated successfully.';
      drupal_set_message($message);
      $form_state["values"]["message"]["success"] = $message;
    }
    else {
      $form_state["values"]["message"]["failure"] = "Error Occured";
    }
  } 
}