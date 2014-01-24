<?php
// $Id: eb_others_common.inc,v 1 2010/10/23 13:17:00 bala Exp $

/* Function for get the New Messages count*/
function privatenewmessages_menu() {
  if (variable_get('privatemsg_display_loginmessage', TRUE) && privatemsg_user_access()) {
    $count = privatemsg_unread_count();
    if ($count) {
     return format_plural($count, '1', '@count', array('@messages' => url('messages')));
    }
  }
}

/**
 *
 * Send Private Message It sends mail to users
 * @param $receipients
 *   It contains to user details
 * @param $user
 *   It contains from user details
 * @param $subject
 *  It contains mail subject details
 * @param $body
 *  It contains mail body content
 *
 */
function privatemsg_mail_asset_send($receipients, $user, $subject, $body) {
  $message['recipients'] = $receipients;
  $message['author'] = $user;
  $message['subject'] = $subject;
  $message['body'] = $body;
  $message['format'] = filter_resolve_format(FILTER_FORMAT_DEFAULT);
  $message['read_all'] = '';
  $message['timestamp'] = time();

  if(is_array($message['recipients'])){
    if ((module_exists('privatemsg')) && (count($message['recipients']) > 0)) {
      _privatemsg_send($message);
    }
  }
}
// Send Private Message
function privatemsg_mail_send($receipients, $user, $subject, $body) {
  if (function_exists("_privatemsg_send")) {
    $message['recipients'] = $receipients;
    $message['author'] = $user;
    $message['subject'] = $subject;
    $message['body'] = $body;
    $message['format'] = filter_resolve_format(FILTER_FORMAT_DEFAULT);
    $message['read_all'] = '';
    $message['timestamp'] = time();
    if(is_array($message['recipients'])){
      if(count($message['recipients']) > 0){
        _privatemsg_send($message);
      }
    }
  }
}
/**
 * Get Heartbeat activty ids
 *
 * @param $nid
 *   It contains node id
 * @param $message_id
 *  It contains heartbeat message id
 * @param $uid
 *  It contains User id
 *
 * @return
 *  It contains query results.
 *
 */
function heartbeat_ids($nid, $message_id, $uid = NULL) {
  $extra_cond = ($uid)?' AND uid = %d':'';
  return db_query("SELECT uaid FROM {heartbeat_activity} WHERE nid=%d AND message_id='%s'" . $extra_cond, $nid, $message_id, $uid);
}

/**
 * To get node title
 *
 * @param $nid
 *  It contains node id
 * @param $type
 *  (Optional) If it true means, it will send type for the specific node id
 * @param $uid
 *  (Optional) If it true means, it will send nid for the specific node id
 *
 * @return
 *   It returns specified node title, type, uid
 */
function node_title($nid, $type = NULL, $uid = NULL) {
  if (!empty($type)) {
    return db_result(db_query("SELECT type FROM {node} WHERE nid=%d", $nid));
  }
  else if ((!empty($uid))){
    return db_result(db_query("SELECT uid FROM {node} WHERE nid=%d", $nid));
  }
  else {
    return db_result(db_query("SELECT title FROM {node} WHERE nid=%d", $nid));
  }
}


/**
 * Display Group details with Group Title, Group Description, No of members, No of Discussions.
 *
 */
function group_detail($gid){
  global $base_url;
  $output = array();
  $group = node_load($gid);
  $output['title'] = l($group->title, 'node/' . $gid);
  $output['gid'] = $gid;
  $output['desc'] = db_result(db_query("SELECT og_description FROM {og} WHERE nid = %d", $gid));

  $output['members'] = db_result(db_query("SELECT COUNT(*) FROM {og_uid} ou INNER JOIN {users} u ON ou.uid = u.uid WHERE ou.nid = %d AND u.status > 0 AND ou.is_active >= 1 AND ou.is_admin >= 0", $gid));
  $output['members'] = $output['members'] > 0 ? l($output['members'] . ' Members', 'og/users/' . $gid . '/faces') : $output['members'] . ' Member';

  $output['dis'] = db_result(db_query("SELECT COUNT(n.nid) FROM {node} n INNER JOIN {og_ancestry} oga ON n.nid = oga.nid WHERE n.status = 1 AND oga.group_nid = %d", $gid));
  $output['dis'] = $output['dis'] > 0 ? l($output['dis'] . ' Discussions', 'node/' . $gid) : $output['dis'] . ' Discussion';
  return $output;
}

/**
 * Display Members details with Profile Image, First Name, Last Name, Contact link.
 *
 */
function member_detail($uid, $assign_status, $type, $image, $mobile_flag = FALSE){
  global $user, $base_url;
  $output = array();
  if($uid){
    $ed_user_array = function_exists("content_profile_load") ? content_profile_load('profile',$uid) : NULL;
    
    //If the request came from site we need to truncate the Firstname, Lastname.
    if(!$mobile_flag){
      $ed_name = ucfirst(truncate_utf8($ed_user_array->field_profile_first_name[0]['value'].' '.$ed_user_array->field_profile_last_name[0]['value'], 10, $wordsafe = FALSE, $dots = TRUE));      
    }
    else{
      $ed_name = ucfirst($ed_user_array->field_profile_first_name[0]['value'].' '.$ed_user_array->field_profile_last_name[0]['value']);      
    }
    switch($image){
      case 'small':
        if($ed_user_array->picture){
          $image = theme('imagecache', 'members_28', $ed_user_array->picture);
          $output['image'] = l($image, "user/" . $uid, array('attributes' => array('class' => 'popups'), 'html' => TRUE));
        }
        else {
          $image = theme('imagecache', 'members_28', variable_get('user_picture_default', ''));
          $output['image'] = l($image, "user/" . $uid, array('attributes' => array('class' => 'popups'), 'html' => TRUE));
        }
      break;
      case 'large':
        if($ed_user_array->picture){
          $image = theme('imagecache', 'members_87', $ed_user_array->picture);
          $output['image'] = l($image, "user/" . $uid, array('attributes' => array('class' => 'popups'), 'html' => TRUE));
        }
        else {
          $image = theme('imagecache', 'members_87', variable_get('user_picture_default', ''));
          $output['image'] = l($image, "user/" . $uid, array('attributes' => array('class' => 'popups'), 'html' => TRUE));
        }
      break;
    }

    if(trim($ed_name)){
      $output['name'] = eb_others_popup_link($ed_name, "user/" . $uid);
    }
    else{
      $ed_name = db_result(db_query('SELECT name FROM {users} WHERE uid = %d', $uid));
      $output['name'] = eb_others_popup_link($ed_name, "user/" . $uid);
    }

    //Contact link text depends on Assigned to Listing Page.
    if(arg(0) == 'assignment' && arg(1) == 'assign'){
      $path  = url("messages/new?cid=" . $uid);
      $output['contact'] =  l('Contact', "messages/new", array('query' => "cid=" . $uid));
    }
    //Contact link text depends on Assigned to Block.
    else if(arg(0) == 'assignment' && arg(1) == 'list'){
      $output['contact'] =  l(' ', "messages/new", array('query' => "cid=" . $uid . '&destination=assignment/list/' . arg(2) . '/' . arg(3)));
    }
    //Contact link text for remaining page.
    else{
      $output['contact'] =  l(' ', "messages/new", array('query' => "cid=" . $uid));
    }

    $output['uid'] = $uid;

    $output['assign_status'] = $assign_status;


    switch($type){
      case 'undo-assign':
        $output['undo'] = l('ReAssign', "assignment/reassign/" . $uid ."/". arg(3) ."/". arg(2), array('attributes' => array('class' => 'popups')));
      break;

    }

    $output['delete'] = l('Delete', "assignment/delete/" . $uid ."/". arg(3) ."/". arg(2), array('attributes' => array('class' => 'popups', 'on-popups-options' => '{hijackDestination:"FALSE"}')));

    return $output;
  }
  else{
    return '';
  }
}

// Teaser Asset Display
function teaser_nodes($title = NULL,  $imagecache_name = NULL, $format = NULL, $length = 40, $check_plain = TRUE, $alt = NULL) {
  if ($title && $check_plain) {
    return truncate_utf8(check_plain($title), $length, $wordsafe = FALSE, $dots = TRUE);
  }
  if ($title && !$check_plain){
    return truncate_utf8($title, $length, $wordsafe = FALSE, $dots = TRUE);
  }
  if ($format) {
    return theme('imagecache', $imagecache_name, $format, $alt, $alt);
  }
}
/**
 * Implementation to get user first and last name
 *
 * @param $ed_uid
 *  It contains user id
 * @param $ed_firstname
 *  IT contains users firstname and last name
 * @param $check_plain
 *  It is optional (default: false). it displays user name without links
 *  
 * @return
 *  It contains links or without links with user name
 *
 */
function create_eduauthor($ed_uid, $ed_firstname = NULL, $check_plain = FALSE){
  // this code for popups the corresponding values.
  if($ed_uid && !trim($ed_firstname)){
    $ed_user_array = content_profile_load('profile',$ed_uid);
    if (isset($ed_user_array)) {
      $ed_name = NULL;
      if (isset($ed_user_array->field_profile_first_name[0]['value'])) {
        $ed_name = $ed_user_array->field_profile_first_name[0]['value'].' ';
      }
      if (isset($ed_user_array->field_profile_last_name[0]['value'])) {
       $ed_name = ($ed_name)? $ed_name . $ed_user_array->field_profile_last_name[0]['value']:$ed_user_array->field_profile_last_name[0]['value'];
      }
    }
    if(trim($ed_name)){
      if($check_plain){
        return $ed_name;
      }
      else{
        return l($ed_name, "user/$ed_uid", array('attributes' => array('class' => 'popups','title' => $ed_name, 'title' => $ed_name,'on-popups-options' => '{width: "670px"}', 'id'=>'user_popup')));
      }
    }
    else{
      $ed_name = db_result(db_query('SELECT name FROM {users} WHERE uid = %d', $ed_uid));
      if($check_plain){
        return $ed_name;
      }
      else{
        return l($ed_name, "user/$ed_uid", array('attributes' => array('class' => 'popups','title' => $ed_name, 'on-popups-options' => '{width: "670px"}')));
      }
    }
  }
  elseif($ed_uid && trim($ed_firstname)) {
    $ed_name = $ed_firstname;
    if($check_plain){
      return $ed_name;
    }
    else{
      return l($ed_name, "user/$ed_uid", array('attributes' => array('class' => 'popups', 'title' => $ed_name, 'on-popups-options' => '{width: "670px"}')));
    }
  }
  else{
    return NULL;
  }
}
/**
 *
 *Building link from id and type of networking website
 *
 */
function get_network_link($id, $type) {
  $new_win_options = array(
    'external' => TRUE,
    'attributes' => array(
      'target' => '_blank'
    )
  );
  switch ($type) {
    case 'skype':
      drupal_set_html_head('<script type="text/javascript" src="http://download.skype.com/share/skypebuttons/js/skypeCheck.js"></script>');
      $link = '<li class="skype"><a href="skype:' . $id . '?call">' . $id . '</a></li>';
      break;
    case 'msn':
      $link = '<li class="msn"><a href="msnim:chat?contact=' . $id . '">' . $id . '</a></li>';
      break;
    case 'twitter':
      $link = '<li class="twitter">' . l($id, 'http://twitter.com/' . $id, $new_win_options) . '</li>';
      break;
    case 'facebook':
      $link = '<li class="facebook">' . l($id, 'http://facebook.com/' . $id, $new_win_options) . '</li>';
      break;
    case 'linkedin':
      $link = '<li class="linkedin">' . l($id, 'http://linkedin.com/in/' . $id, $new_win_options) . '</li>';
      break;
    default:
      $link = '';
      break;
  }
  return $link;
}



function get_profile_name($puser) {
  if ($puser['uid']) {
    $profile_name = db_fetch_object(db_query("SELECT field_profile_first_name_value, field_profile_last_name_value FROM {node} n, {content_type_profile} ctp WHERE n.uid = %d AND n.nid = ctp.nid", $puser['uid']));
  }
  return $profile_name;
}
/**
 * process of reviewers permissions
 *
 * It is used to check whether that node have permission to access (create, delete, update) and that associated node is published, open for reviews, specific user are available for that reviewers list
 *
 * @param
 *  $node
 *   It contains node object
 *  $review_permission
 *   It contains string of the specific file (eg: view, create, update)
 *  $type
 *   It contains string of the spscific content type name (eg: review, asset, curriculum)
 *  $node_review
 *   It contains node object: It used to check the node_access permission for that node
 *
 * @return
 *   true for if he have rights otherwise it returns false
 *
 */
function reviewer_access($node, $review_permission, $type = null, $node_review = null ) {
  global $user;
  if ($user->uid) {
    $node_check = ($type) ? $type:$node_review;
    // check node_access permission for the specific node_object
    if (node_access($review_permission, $node_check)) {
      // check if the node is open for review and published
      if($node->field_openforreview[0]['value'] == 1 && $node->field_published[0]['value'] == 1) {
        // check if user is coauthor
        if ($node->field_coauthor) {
          $flag = 0;
          foreach ($node->field_coauthor as $key => $value) {
            if ($user->uid == $value['uid']) {
              $flag = 1;
            }
          }
        }
        // Check if user is a reviewer
        if($node->field_reviewers) {
          $flag2 = 0;
          foreach($node->field_reviewers as $value) {
            if($value['uid'] == $user->uid) {
              $flag2 = 1;
            }
          }
        }
        $flag3 = 0;
        if ($user->uid == $node->uid) {
          $flag3 = 1;
        }
      }
      if ($flag == 1 || $flag2 == 1 || $flag3 == 1 || $review_permission == 'view') {
        return true;
      }

    }
  }

  return false;
}


/**
 * Implementing the Co Author Access Permission
 */

function delete_asset_curriculum_access($node, $asset_group = FALSE, $group = FALSE, $edit_asset_curri = FALSE, $tab = FALSE ) {
  if ($tab == FALSE) {
    if ($node->type == 'curriculum' || $node->type == 'asset') {
      return _access_check($node, $asset_group, $group, $edit_asset_curri);
    }
    else {
      return node_access('delete', $node);
    }
  }
  else {
    if ($node->type == 'curriculum' || $node->type == 'asset' || $node->type == 'bead') {
      return _access_check($node, $asset_group, $group, $edit_asset_curri);
    }
  }
}
/**
 * Implementing the Co Author Access Permission
 */
function view_asset_curriculum_access($node, $asset_group = FALSE, $group = FALSE, $edit_asset_curri = FALSE, $tab = FALSE, $publish = FALSE) {
  if ($tab == FALSE) {
    if ($node->type == 'curriculum' || $node->type == 'asset') { 
      $access = _access_check($node, $asset_group, $group, $edit_asset_curri); 
      // publish state for asset and curriculum
      if ($publish == TRUE && $access) {
        if ($node->field_published[0]['value'] == 1) {
          return FALSE;
        }
      }
      return $access; 
    }
    else {
      return node_access('update', $node);
    }
  }
  else {
    if ($node->type == 'curriculum' || $node->type == 'asset' || $node->type == 'bead') {
      return _access_check($node, $asset_group, $group, $edit_asset_curri);
    }
  }
  return true;
}
/**
 * Check whether user have rights to access
 *
 * @param $node
 *  It contains node object
 * @param $asset_group
 *
 * @param $group
 *   It contains true or false
 * @param $edit_asset_curri
 *  It contains true or false
 *  
 */
function _access_check($node, $asset_group, $group, $edit_asset_curri) {
  global $user;
  if ($user->uid && user_access("access content")) {
    if ($node->type == 'bead') {
      return true;
    }
    else {
      
      if ((($node->type == 'curriculum') && user_access('view curriculum content')) || ($node->type == 'asset'   && user_access('view assets')) || user_access("administrator") || user_access("administer nodes") ) { //&& $asset_group == 'true'
        if ($group == 'true'  && $node->uid != $user->uid && !user_access("administrator") && !user_access("administer nodes") ) {
          foreach ($node->og_groups as $gid) {
            if (og_is_group_member($gid, FALSE, $user->uid) && $node->field_published[0]['value'] == 1 ) {
              return true;
            }
          }
          return false;
        }
        if ($node->field_coauthor) {
          $flag = 0;
          foreach ($node->field_coauthor as $key => $value) {
            if ($user->uid == $value['uid']) {
              $flag = 1;
            }
          }
        }
        if (($node->field_published[0]['value'] == 1 && $edit_asset_curri == FALSE  )|| $node->uid == $user->uid  || user_access("administrator") || user_access("administer nodes")  || $flag == 1 || $node->field_author[0]['uid'] == $user->uid) {
          return true;
        }
      }
    }
  }
  return false;
}

/*
* Notification Email will Send to the associated users when the asset is edited.
*
*/
function notification_mail_edit($node) {
  global $user;

  // Notification Mail will send to associated Users if the asset is edited.
  $edit_query = db_query("SELECT to_uid FROM {assignment} WHERE link=%d", $node->nid);
  if (db_affected_rows()) {
    $arry_receipients = array();
    while ($edit_result = db_fetch_object($edit_query)) {
      $user_name =   db_result(db_query("SELECT name FROM {users} WHERE uid=%d", $edit_result->to_uid));
      $temp_user_list = user_load(array('name' => trim($user_name)));
      $arry_receipients[$temp_user_list->uid] = $temp_user_list;
    }
    $subject =  $node->title . '  has been edited';
    $body = 'Your associated ' . $node->type . " " . $node->title . '  has been edited';
    if(is_array($arry_receipients) && (count($arry_receipients) > 0)){
      privatemsg_mail_asset_send($arry_receipients, $user, $subject, $body);
    }
  }

  // mail to the owner of the associated curriculum
  $get_cur_author = db_query("SELECT ct.cid FROM {curriculum_topics_assets} cta LEFT JOIN {curriculum_topics} ct ON ct.topic_id = cta.topic_id WHERE cta.asset = %d GROUP BY cid ", $node->nid);
  if (db_affected_rows()) {
    $arry_curr_owners = array();
    while ($curr_result = db_fetch_object($get_cur_author)) {
      $temp_user_list = node_load($curr_result->cid);
      $user_list = user_load($temp_user_list->uid);
      $arry_receipients[$user_list->uid] = $user_list;
    }
    $subject =  $node->title . '  has been edited';
    $body = 'Your associated ' . $node->type . " " . $node->title . '  has been edited';
    if(is_array($arry_receipients) && (count($arry_receipients) > 0)){
      privatemsg_mail_asset_send($arry_receipients, $user, $subject, $body);
    }
  }
}

/**
 * It will remove all og related record for the associated community interest group
 *
 * @param $nid
 *  It contains node id
 *
 *
 * @see heartbeat_ids() in eb_others.module
 * @see _heartbeat_activity_delete() in heartbeat module
 */
function delete_all($node) {
  // Check if heart beat module exits
  $discusion = db_query ("select nid from {og_ancestry} where group_nid=%d", $node->nid);
  if (db_affected_rows()) {
    while ($row = db_fetch_object($discusion)) {
      node_delete($row->nid);
    }
  }
  $sql = "DELETE FROM {og} WHERE nid = %d";
  db_query($sql, $node->nid);
  $sql = "DELETE FROM {og_ancestry} WHERE nid = %d";
  db_query($sql, $node->nid);
  $sql = "DELETE FROM {og_uid} WHERE nid = %d";
  db_query($sql, $node->nid);

  node_delete($node->nid);
}
/**
 * Delete messages from heart beat
 *
 * @param $nid
 *  It contains node id
 *
 * @param $message_id
 *  It contains message id
 *
 * @param $uid
 *  It contains user id
 *
 */
function heartbeat_delete($nid, $message_id, $uid) {
  // Will delete the unassigned user in hearbeat_activity table
  if (module_exists('heartbeat')) {
    $query = heartbeat_ids($nid, $message_id, $uid);
    if (db_affected_rows()) {
      while($row = db_fetch_object($query)) {
        _heartbeat_activity_delete($row->uaid);
      }
    }
  }
}
/**
 * It is used to check co author 
 *
 */
function check_coauthor($coauthor) {
  global $user;
  $flag = 0;
  if (!empty($coauthor)) {
    foreach ($coauthor as $k =>$v) {
      $authors[] = link_to_user($v['uid']);
      if ($v['uid'] == $user->uid) {
        $flag = 1;
      }
    }
  }
  return  $flag;
}
function eb_edit_content($node) {
  if ($node->type == 'curriculum') {
    return node_page_view($node);
  }
  elseif ($node->type == 'asset' || $node->type == 'bead') {
    return node_page_edit($node);
  }
  
  else {
    return drupal_access_denied();
  }
}

/**
 * Co Author, Reviewer confirm form
 */
function coauthor_reviewer_remove_form(){
  global $user;
  $form = array();
  $node = node_load(arg(1));
  drupal_set_title(teaser_nodes($node->title, NULL, NULL, 40));
  if($node->type == 'curriculum'){
    $title = 'Playlist';
  }
  else if($node->type == 'asset'){
    $title = 'Asset';
  }

  $form['remove_content'] = array(
    '#type' => 'markup',
    '#value' => t('Are you sure you want to be removed as Co-author from this !title?', array('!title' => $title)),
    '#prefix' =>'<div class="result"><div class="confirm-text">',
    '#suffix' =>'</div></div>',
  );

  $form['node_id'] = array(
   '#type' => 'hidden',
   '#value' => arg(1),
  );
  $form['removal_type'] = array(
   '#type' => 'hidden',
   '#value' => arg(4),
  );
  $form['user_id'] = array(
   '#type' => 'hidden',
   '#value' => $user->uid,
  );

  //Get redirect path after successful removal.
  if($node->type == 'asset' || $node->type == 'quiz'){
    $redirect_path = 'bridge/myassets';
  }
  else if($node->type == 'curriculum'){
    $redirect_path = 'bridge/mycurriculum';
  }
  $form['redirect_path'] = array(
   '#type' => 'hidden',
   '#value' => $redirect_path,
  );

  $form['yes_submit'] = array(
    '#prefix' => '<div class="button-main">',
    '#type' => 'submit',
    '#value' => t('Yes'),
  );

  return $form;
}

/**
 *
 */
function coauthor_removed($node){
  global $user;
  clear_listing_cache($node);
  clear_listing_cache($node, "playlist_listing", "playlist_basket", "playlist_mobile");
  //Remove Corresponding CoAuthor uid from Node object
  if($node->field_coauthor){
    foreach($node->field_coauthor as $key => $val){
      if($val['uid'] == $user->uid){
        unset($node->field_coauthor[$key]);
        $node->field_coauthor = array_values($node->field_coauthor);
        //After removing the Logged in user from Co Author array do node save.
        node_save($node);
        //Set status message
        $reviewer_flag = 0;
        if($node->field_reviewers){
          foreach($node->field_reviewers as $key => $val){
            if($val['uid'] == $user->uid){
              $reviewer_flag = 1;
            }
          }
        }
        //Type of Node.
        if($node->type == 'curriculum'){
          $type = 'playlist';
        }
        else if($node->type == 'asset'){
          $type = 'asset';
        }
        if($reviewer_flag){
          drupal_set_message(t('You have been removed as Co-Author. But you are a reviewer for the !type - "!node_title"', array('!type' => $type, '!node_title' => $node->title)));
        }
        else{
          drupal_set_message(t('You have been removed as Co-Author from the !type - "!node_title"', array('!type' => $type, '!node_title' => $node->title)));
        }

        //Removal Notification mail to Node Author.
        $rec[$node->uid] = user_load($node->uid);
        //Get user's first name, last name without link
        $user_author = create_eduauthor($user->uid, NULL, TRUE);
        $node_link = l($node->title, 'node/' . $node->nid);
        $regards = '<br>Regards,<br>EducationHub Team';

        $subject = t('!user_name has removed himself as Co-Author', array('!user_name' => $user_author));
        $message = t('!user_name has removed himself as Co-Author from your !type "!node_link" !regards', array('!type' => $type, '!user_name' =>  $user_author, '!node_link' => $node_link, '!regards' => $regards));

        if (is_array($rec) && (count($rec) > 0)) {
          privatemsg_mail_send($rec, $user, $subject, $message);
        }
        //Watch Dog entry regarding Removal of co-author.
        watchdog('coauthor removal', t('!coauthor_user removed as co author from !node_title', array('!coauthor_user' => $user->name, '!node_title' => $node->title)));
      }
    }
    
  }
}



/**
 * Assign Messages
 *
 * for asset and curriculum we need to assign message
 *
 * @param $addedorremove
 *   It contains add or remove string
 *
 * @param $content
 *  It contains message content
 *
 * @param $coauthor_url
 *  it contains coauthor url
 *
 *  @param $node_title
 *   It contains node title
 *
 *  @param $uid
 *   It contains user id
 *
 *  @param $node_nid
 *   It contains node nid.
 *
 *  @param $from_to
 *   It contains from or to word
 *
 * @return $assign_msg
 *  It returns assigned message
 *
 */
function privatemsg_assign_message($addedorremove, $content, $coauthor_url, $node_title, $uid, $node_nid, $from_to = 'to') {
  $assign_msg = array();
  $assign_msg['subject'] = t('You have been !addedorremove as !content !from_to playlist', array('!addedorremove' => $addedorremove,'!content' => $content, '!from_to' => $from_to));
  $assign_msg['body'] = t('You have been !addedorremove as !content !from_to playlist, ' . l($node_title, 'node/' . $node_nid, array('html' => TRUE)) . ' by ' . create_eduauthor($uid) . '<br> Regards,<br> Edubridge Admin', array('!addedorremove' => $addedorremove, '!content'=>  $content, '!from_to' => $from_to));
  return $assign_msg;
}

/**
 * link_to_user function creates link from user id
 */
function link_to_user($uid) {
  $query = db_query("SELECT uid FROM users WHERE uid=%d", $uid);
  $rows = db_fetch_object($query);
  $link = eb_others_popup_link(create_eduauthor($rows->uid),  "user/" . $uid);
  return $link;
}

/**
 * This function stores data in asset trackign table - called from curriculum overview and asset htm editing
 * aid: asset id used
 * ptype: type: curriculum/asset
 * pid: parent curriculum/asset id where this asset being used
 */
function asset_tracking_add($aid, $ptype, $pid) {
  global $user;
  $uid = $user->uid;
  if ($user->roles[4]) {
    $rid = '4';
  }
  elseif ($user->roles[3]) {
    $rid = '3';
  }

  $result = db_query("INSERT into {asset_tracking}
           (asset_id, uid, rid, parent_type, parent_id, created)
           VALUES
           (%d, %d, %d, '%s', %d, %d)", $aid, $uid, $rid, $ptype, $pid, time());
}

/**
 * create stringable beads link
 * check if the bead has connected beads (with seq. no.) and return link
 * if not return null
 * - Beschi
 */
function beads_stringable_link($nid, $bead_seq_no, $bead_source_id = NULL, $link_set = FALSE) {
  global $base_url;
  $link = NULL;
  $alt = db_result(db_query("SELECT `title` FROM node WHERE `nid` = %d", array($nid)));
  $sql = db_query("SELECT nid FROM {content_type_bead} WHERE field_source_id_value = '%s'", $bead_source_id);
  if(db_affected_rows($sql) > 1) {
    if ($link_set) {
      $link = 'beads/stringable/' . $nid . '/' . $bead_seq_no;
    }
    else {
      $link = l(theme_image(drupal_get_path('theme', 'educationhub') . '/images/full-sequence.png', 'View full sequence for ' . $alt , 'View full sequence'), 'beads/stringable/' . $nid . '/' . $bead_seq_no , array('attributes' => array('class' => 'stringable-beads-page', 'title' => 'View full sequence'), 'query' => '#title-' . $nid , 'html' => TRUE));
    }
  }
  return $link;
}
/**
 * for popup up link we need to fix width
 *
 * @param $name
 *  It contains link name
 *
 * @param $link
 *  It contains links
 *
 * @param $class
 *  It contains class for that links
 *
 * @param $option
 *  It contains options for that links
 *
 * @return
 *  It contains link.
 *
 */
function eb_others_popup_link($name, $link, $class = NULL, $option = NULL) {
  return l($name,  $link, array('attributes'=>array('class' => 'popups' . $class, 'on-popups-options' => '{width: "670px"}')));

}
/**
 *
 *  It is used to load the node on specific pages
 *
 *  @return
 *   It contains node object.
 *
 */
function custom_node_load() {
  if (is_numeric(arg(1)) && (arg(0) == 'node' || arg(0) == "review_listing" )) {
    $node = node_load(arg(1));
  }
  else if(arg(0) == 'og' && is_numeric(arg(2))) {
    $node = node_load(arg(2));
  }
  if (isset($node)) {
    return $node;
  }
}
/**
 * Implementing to check coauthor
 **/
function co_authorcheck($arry_diff) {
  $arry_receipients = '';
  if ($arry_diff) {
    foreach ($arry_diff as $key => $value) {
      if ($value) {
        $user_name =   db_result(db_query("SELECT name FROM {users} WHERE uid=%d", $value));
        $temp_user_list = user_load(array('name' => trim($user_name)));
        $arry_receipients[$temp_user_list->uid] = $temp_user_list;
      }
    }
  }

  return $arry_receipients;
}

/**
 *
 *  It is used to check curriculum view permission for user
 *
 * @param $node
 *  It contain node object
 *
 *  @return
 *   It contains node object.
 *
 */
function node_page_change_view($node) {
  if ($node->type == 'curriculum' || $node->type == 'asset') {
    return _node_view_access($node);
  }
  else if ($node->type == 'page') {
    if (user_access('access homepage')) {
      return true;
    }
    else {
      return node_access('view', $node);
    }
  }
  else {
    return node_access('view', $node);
  }
}
/**
 * check if it is asset or curriculum then check author && co author
 *
 */
function _node_view_access($node) {
  if ($node->type == 'curriculum') {
    if (user_access('view curriculum content')) {
      if (view_asset_curriculum_access($node) && arg(2) != 'edit') {
        return true;
      }
      else {
        return false;
      }
    }
  }
  elseif ($node->type == 'asset') {  
    if (view_asset_curriculum_access($node)) { 
      return true;
    }
    else { 
      return false;
    }
  }
}
function share_embed($form) {
  $form = array();
  $form['embed'] = array(
    '#type' => 'textfield',
    '#name' => 'embed',

  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Embed',
  );
  return $form;
}





function _upload_file_limits_custom($user) {
  $file_limit = variable_get('upload_uploadsize_default', 1);
  $user_limit = variable_get('upload_usersize_default', 1);
  $all_extensions = explode(' ', variable_get('upload_extensions_default', 'jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp'));
  foreach ($user->roles as $rid => $name) {
    $extensions = variable_get("upload_extensions_$rid", variable_get('upload_extensions_default', 'jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp'));
    $all_extensions = array_merge($all_extensions, explode(' ', $extensions));

    // A zero value indicates no limit, take the least restrictive limit.
    $file_size = variable_get("upload_uploadsize_$rid", variable_get('upload_uploadsize_default', 1)) * 1024 * 1024;
    $file_limit = ($file_limit && $file_size) ? max($file_limit, $file_size) : 0;

    $user_size = variable_get("upload_usersize_$rid", variable_get('upload_usersize_default', 1)) * 1024 * 1024;
    $user_limit = ($user_limit && $user_size) ? max($user_limit, $user_size) : 0;
  }
  $all_extensions = implode(' ', array_unique($all_extensions));
  return array(
    'extensions' => $all_extensions,
    'file_size' => $file_limit,
    'user_size' => $user_limit,
    'resolution' => variable_get('upload_max_resolution', 0),
  );
}
/**
 * function to return a link from the asset, type and title
 * If the type is asset then return the link with the title and link of that node
 * If external - return the link with the title and asset as link with target = _blank
 * Used in baskets & stats for admin pages
 */
function drag_drop_make_link($asset, $title, $type, $desc = '', $tool_text = NULL, $class_name = NULL, $block = FALSE) {
  //check if this is a external link of asset link
  if(is_numeric(arg(1))) {
    $node = node_load(arg(1));
  }

  if ($type == "google" || $type == "federated") {
    $link = $asset;
    $content_title = $title;
    $options = array(
      'attributes' => array(
        'title' => $tool_text,
        'target' => '_blank'
      )
    );
    if (strpos($asset, 'curriki.org') !== false) {
      $class_type = "external-curriki";
    }
    elseif (strpos($asset, 'merlot.org') !== false) {
      $class_type = "external-merlot";

    }
    elseif (strpos($asset, 'oercommons.org') !== false) {
      $class_type = "external-oercommons";    }
    elseif (strpos($asset, 'free.ed.gov') !== false) {
       $class_type = "external-free-ed";
    }
    elseif (strpos($asset, 'cnx.org') !== false) {
      $class_type = "external-cnx";
    }
    elseif (strpos($asset, 'khanacademy.org') !== false) {
      $class_type = "external-khanacademy";
    }
    else {
      $class_type = "external-nodoc";
    }
  }
  else {
    //set the default node/id as path, if path alias is enabled (using path module) - change to that path
    $link = "node/" . $asset;
    $nodeobj = node_load($asset);
    if ($nodeobj->taxonomy) {
      $taxonomy = end($nodeobj->taxonomy);
    }
    else {
      $taxonomy = "";
    }
    $desc = htmlentities($nodeobj->teaser);

    if ($nodeobj->path) {
      $link = ('node/'.$nodeobj->nid);

    // $link = $nodeobj->path;
    }
    $tip_text = ($tool_text) ? $tool_text : $nodeobj->title;
    $options = array('attributes' => array('title' => $tip_text));
    $title = ($block)?truncate_utf8($nodeobj->title, 26, TRUE, TRUE):$nodeobj->title;
    $content_title = $nodeobj->title;
    if ($type == "asset") {
      $class_type = "asset-". drupal_strtolower($nodeobj->field_format[0]['value']);
    }
    else if ($type == "bead") {
      //$title = $nodeobj->title;
      $class_type = "bead-". drupal_strtolower($nodeobj->field_format[0]['value']);
    }
     else if ($type == "quiz") {
      $class_type = "quiz-nodoc";
    }
    else {
      $class_type = "curriculum-nodoc";
    }
  }
  return '<div class="'. $class_name . ' ' .$class_type .'" content_asset="'. $asset .'" content_type="'. $type .'" class_type="'. $class_type .'" content_title="'. check_plain($content_title) .'" content_desc="' . $desc .'">' . l($title, $link, $options) . '</div>';

}

/**
 * function to return a link from the asset, type and title
 * If the type is asset then return the link with the title and link of that node
 * If external - return the link with the title and asset as link with target = _blank
 * Used in baskets & stats for admin pages
 */
function drag_drop_make_link_left_block($asset, $title, $type, $desc = '', $tool_text = NULL, $class_name = NULL, $block = FALSE) {
  //check if this is a external link of asset link
  if(is_numeric(arg(1))) {
    $node = node_load(arg(1));
  }

  if ($type == "google" || $type == "federated") {
    $link = $asset;
    $content_title = $title;
    $options = array(
      'attributes' => array(
        'title' => "Drag and drop or click this ". $tool_text ." to embed in the editor",
        'target' => '_blank'
      )
    );
    if (strpos($asset, 'curriki.org') !== false) {
      $class_type = "external-curriki";
    }
    elseif (strpos($asset, 'merlot.org') !== false) {
      $class_type = "external-merlot";

    }
    elseif (strpos($asset, 'oercommons.org') !== false) {
      $class_type = "external-oercommons";    }
    elseif (strpos($asset, 'free.ed.gov') !== false) {
       $class_type = "external-free-ed";
    }
    elseif (strpos($asset, 'cnx.org') !== false) {
      $class_type = "external-cnx";
    }
    elseif (strpos($asset, 'khanacademy.org') !== false) {
      $class_type = "external-khanacademy";
    }
    else {
      $class_type = "external-nodoc";
    }
  }
  else {
    //set the default node/id as path, if path alias is enabled (using path module) - change to that path
    $link = "node/" . $asset;
    $nodeobj = node_load($asset);
    if ($nodeobj->taxonomy) {
      $taxonomy = end($nodeobj->taxonomy);
    }
    else {
      $taxonomy = "";
    }
    $desc = htmlentities($nodeobj->teaser);

    if ($nodeobj->path) {
      $link = ('node/'.$nodeobj->nid);

    // $link = $nodeobj->path;
    }
    $tip_text = ($tool_text) ? $tool_text : $nodeobj->title;
    if(arg(2) == 'content') {
      $options = array('attributes' => array('title' => "Drag to Drop or Click this ". $tip_text ." to embed in the editor"));
    }
    else{
      $options = array('attributes' => array('title' => $tip_text));
    }
    $title = ($block)?truncate_utf8($nodeobj->title, 26, TRUE, TRUE):$nodeobj->title;
    $content_title = $nodeobj->title;
    if ($type == "asset") {
      $class_type = "asset-". drupal_strtolower($nodeobj->field_format[0]['value']);
    }
    else if ($type == "bead") {
      //$title = $nodeobj->title;
      $class_type = "bead-". drupal_strtolower($nodeobj->field_format[0]['value']);
    }
     else if ($type == "quiz") {
      $class_type = "quiz-nodoc";
    }
    else {
      $class_type = "curriculum-nodoc";
    }
  }
  return '<div class="'. $class_name . ' ' .$class_type .'" content_asset="'. $asset .'" content_type="'. $type .'" class_type="'. $class_type .'" content_title="'. check_plain($content_title) .'" content_desc="' . $desc .'">' . l($title, $link, $options) . '<div class="preview_icon" id="preview_icon">' . l(theme_image(drupal_get_path('theme', 'educationhub') . '/images/preview.png', 'Preview this '.$title, 'Preview this '.$title) ,$link, array('html' => TRUE)). '</div></div>';

}
/**
 *
 */
function title_change($node) {
  if ($node->type == 'curriculum' || $node->type == 'asset' || $node->type == 'bead') {
    return 'Info';
  }
  else {
    return 'Edit';
  }

}
/**
 * Implementing follow us links
 *
 */
function follow_us() {
  return "<div class='followus'><span class='font-bold'>Follow us</span><ul><li>" . l(theme_image(drupal_get_path('theme', 'educationhub') . '/images/facebook.png', 'Facebook Homepage', 'Facebook'), ' https://www.facebook.com/Syntiro', array('attributes' => array('target' => '_blank'), 'html' => TRUE)) . "</li>
<li>" . l(theme_image(drupal_get_path('theme', 'educationhub') . '/images/twitter.png', 'Twitter Homepage', 'Twitter'), ' https://twitter.com/syntiro', array('html' => TRUE)) . "</li>
</ul></div>";
}

/**
 * Implementing global study group block
 *
 */
function bridge_global() {
  global $user;
  return  l(theme_image(drupal_get_path('theme', 'educationhub') . '/images/open-study.jpg', NULL, 'Global Study Group'), 'collaboration/globalstudygroup', array('attributes' => array('title' => 'Global Study Group'), 'html' => TRUE));

}
/**
 * To Remove white spaces
 *
 * @param $content
 *  It contains string
 *
 */
function removing_whitespace($content) {
  $converted = NULL;
  $content = strip_tags($content);
  $content = str_replace('&nbsp;'," ",$content);
  $converted = trim($content);
  return $converted;
}


/**
 *
 * Implementing the campus flag
 *
 * @param $institute_id
 *  It contains institute node id
 *
 */ 
function institution_flag($institute_id) {
  global $user;
  
  if (isset($user->eb_user_institute)) {
    $profile = $user->eb_user_institute;
  }
  else {
    $profile = content_profile_load('profile', $user->uid);
  }
  if ($profile->field_institute[0]['nid'] !=  $institute_id && !empty($institute_id)) {
    if ($node_institute = cache_get("ins_" . $institute_id, "cache_eb")->data) {
    }
    else {
      $node_institute = node_load($institute_id);
      cache_set("ins_" . $node_institute->nid, $node_institute, "cache_eb");
    }
    if(isset($node_institute->field_institute_logo[0]['filename'])) {
      $file_path = $node_institute->field_institute_logo[0]['filepath'];
    }
    return '<div class="campus-flag float-left">
       ' . theme_image(drupal_get_path("theme", "educationhub") . "/images/icons/flag-icon.png", NULL, NULL, array('class' => 'flag-campus') ) .'
        <span class="campus-det" style="display:none;">
                <span class="campus-title">' . $node_institute->title . '</span>
        </span>
    </div>';
  }
  return false;
}
/**
 * Return subtopic l
 */
function subtopic_load($st_id = 0) {
  return $st_id;
}
/**
 * To check coauthor and reviewer should be valid user
 *
 * @param $node
 *  It contains node object
 *
 */
function validation_check($node) {
  if ($node->coauthor) {
    $co_author_list = explode(",", $node->coauthor);
    if ($co_author_list) {
      foreach($co_author_list as $key => $value) {
        if (trim($value)) {
          $user_name = NULL;
          $user_name = db_result(db_query("SELECT uid FROM {users} WHERE mail='%s'", trim($value)));
          // check if not a valid user then throw the error message
          if (!$user_name) {
            form_set_error('coauthor', t('Please Enter Valid Co Author name.'));
          }
        }
      }
    }
  }
  if ($node->reviewers) {
    $co_author_list = explode(",", $node->reviewers);
    if ($co_author_list) {
      foreach($co_author_list as $key => $value) {
        $user_name = NULL;
        if (trim($value)) {
          $user_name = db_result(db_query("SELECT uid FROM {users} WHERE mail='%s'", trim($value)));
          // check if not a valid user then throw the error message
          if (!$user_name) {
            form_set_error('reviewers', t('Please Enter Valid Reviewers name.'));
          }
        }
      }
    }
  }
}

/**
 * Validate the mail id
 *
 * @param $email
 *  It contains email id
 *
 * @return
 *  It contains true or false
 *
 * Ref: http://roshanbh.com.np/2008/02/email-validation-php.html
 */
function validateEmail($email) {
  if(eregi('^[a-zA-Z0-9._-]+@[a-zA-Z0-9-]+\.[a-zA-Z]{2,4}(\.[a-zA-Z]{2,3})?(\.[a-zA-Z]{2,3})?$', $email))
    return true;
  else
    return false;
}



/**
 * echopre function
 */
function echopre($value) {
  echo '<pre>';
  print_r($value);
  echo '</pre>';
}
