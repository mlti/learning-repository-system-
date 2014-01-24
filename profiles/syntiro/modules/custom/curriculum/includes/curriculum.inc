<?php
// $Id$
/**
 *
 *This function construct the contents in the topics
 *with drag handle and remove link - used in both ajax calling and curriculum view
 *
 */
function curriculum_content_build($content_id, $title, $link, $class_type, $cid, $basket = false, $topicid, $tid) {
  global $base_url;
  if ($basket == "true")  {
    if (is_numeric($link)){
      $content_div = '<li><div> <a href="' . $base_url .'/node/'. $link . '" title="Click to view">'. $title .'</a></div></li>';
    }
    else {
      $content_div = '<li><div> <a href="' . $link . '" target="_blank">'. $title .'</a></div></li>';
    }
  }
  else {
    //while dropping an asset to Playlist we need to bring the Check box immediately.
    $check_box = drupal_get_form('curriculum_select_all_form', $content_id);
    if (is_numeric($link)) {
      $more_div = '<a title="More" nodetype="asset" href="/node/'.$link.'">More</a>';
    }
    else {
      $more_div = '<a title="More" nodetype="federated" node_title = "'.$title .'" href="'.$link.'">More</a>';
    }
    //$weight_div = drupal_get_form('curriculum_weight_form', $content_id);
    //$topic_div = drupal_get_form('curriculum_select_topic_form', $topicid, $tid, $content_id);
$content_div = '<div class="clearfix assign-edit-icons topic-single-content ' . $class_type . '" id="content_' . $content_id . '"><span class="handle" title="Sort this content"></span> <div class="float-left sub-topics">' . $check_box . '</div><div class="sub-topics playlist-action">
    <div class="more-icon">' . $more_div .'</div>
</div><div class="float-left sub-topics" content_title="' . $title. '" class_type="' . $class_type .'"  content_type="' . $class_type .'" content_asset=" ' . $link . '"><span class="handle"><div class="asset-teaser">';
 
    $delete_link = $base_url.'/curriculum/delete_content_confirm/' . $content_id;
    $body = NULL;
    if(is_numeric($link)) {
      $body = db_result(db_query("SELECT body FROM {node_revisions} WHERE nid=%d", $link));
    }
    else {
      $body = db_result(db_query("SELECT description FROM {curriculum_topics_assets} WHERE id=%d", $content_id));
    }
    
    $body = function_exists("removing_whitespace") ? truncate_utf8(removing_whitespace($body), 75, TRUE, TRUE) : NULL;
    $content_div .= check_plain($title);
    $content_div .= "</div><p>" . $body . "</p></div></span>";
    $image_url = $base_url . "/" . drupal_get_path('theme', 'educationhub') . "/images/small_close_icon.png";
    $content_div .= l($image_tag,
                      $delete_link,
                      array('attributes' => array(
                                                  'class' => 'popups-form-reload',
                                                  'title' => 'Delete this topic',
                                                  ),
                            'html' => TRUE,
                            )
                      );
    $content_div .= '</div>';
  }
  return $content_div;
}

/**
 *order the weight of the topics - fromajax call
 *
 */
function curriculum_order_topics() {
  $subtopic_id = arg(5);
  $sub_topic_weights = arg(7);
  $topicid= arg(9);
  
  $subtopic_id = explode(",", $subtopic_id);
  $weight = explode(",", $sub_topic_weights);
  $topicid = explode(",", $topicid);

  for( $i=0; $i<count($subtopic_id); $i++ )
  {
   $result = db_query("UPDATE {curriculum_topics_assets} SET weight = %d , topic_id = %d WHERE id= %d ",  $weight[$i], $topicid[$i], $subtopic_id[$i]);
  }
  drupal_set_message('Asset Order Updated');
}

/**
 * Delete content - confirmation form - popup
 *
 */
function delete_content_confirm_form(){
  $form = array();
  $form['remove_content'] = array(
    '#type' => 'markup',
    '#value' => t('Are you sure you want to remove this content?'),
    '#prefix' =>'<div class="result"><div class="confirm-text">',
    '#suffix' =>'</div></div>',
  );

  $form['yes_submit'] = array(
    '#prefix' => '<div class="button-main">',
    '#type' => 'submit',
    '#value' => t('Yes'),
  );
  $form['no_submit'] = array(
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('No'),
  );
  return $form;
}

/**
 * Reorder  curriculum topics- confirmation form - popup
 *
 */
function reorder_curriculum_topics_confirm_form(){
  $form = array();
  $form['save_reorder'] = array(
    '#type' => 'markup',
    '#value' => t('Are you sure you want to reorder this topics?'),
    '#prefix' =>'<div class="result"><div class="confirm-text">',
    '#suffix' =>'</div></div>',
  );

  $form['yes_submit'] = array(
    '#prefix' => '<div class="button-main">',
    '#type' => 'submit',
    '#value' => t('Yes'),
  );
  $form['no_submit'] = array(
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('No'),
  );
  return $form;
}

/**
 * clone the node.
 *
 * @param $node
 *  It contains node object.
 *
 * @return $original_node
 *  It contains cloned node object
 *
 */
function node_clone($node) {
  if(!is_object($node)) {
    return FALSE;
  }
  global $user;
  $clone_node   = drupal_clone($node);
  $clone_node->nid                = NULL;
  $clone_node->name               = $user->name;
  $clone_node->created            = time();
  $clone_node->changed            = time();
  $clone_node->revision_uid       = '';
  $clone_node->revision_timestamp = '';
  $clone_node->uid                = $user->uid;
  switch($clone_node->type) {
    case 'quiz':
      $clone_node->field_published[0]['value'] = 0;
      $clone_node->title = 'Clone '. $clone_node->title;
      // Save quiz clone node.
      node_save($clone_node);
      $messages = drupal_get_messages(NULL, FALSE);
      $msg = $messages['status'][0];
      if (strpos($msg, 'You just created a new quiz. Now you have to add questions to it. This page is for adding and managing questions. Here you can create new questions or add some of your already created questions. If you want to change the quiz settings, you can use the "edit" tab.')) {
        $messages = drupal_get_messages();
      }       
      //Insert clone tracking table
      db_query('INSERT INTO {clone_tracking}
              (original_id, clone_id, uid, type, created)
              VALUES(%d, %d, %d, "%s", %d)', $node->nid, $clone_node->nid, $user->uid, $node->type, time());
      // Find quiz original questions.
      $sql = 'SELECT child_nid, child_vid, question_status, weight, max_score
              FROM {quiz_node_relationship}
              WHERE parent_vid = %d';
      $res = db_query($sql, $node->vid);
      while ($res_o = db_fetch_object($res)) {
        $original_question = node_load($res_o->child_nid);
        // Save the relationship between the new question and the quiz.
        $sql = 'INSERT INTO {quiz_node_relationship}
                (parent_nid, parent_vid, child_nid, child_vid, question_status, weight, max_score)
                VALUES(%d, %d, %d, %d, %d, %d, %d)';
        db_query($sql, $clone_node->nid, $clone_node->vid, $original_question->nid, $original_question->vid, $res_o->question_status, $res_o->weight, $res_o->max_score);
      }
    break;
    case 'asset':
      $clone_node->status = 0;
      $clone_node->field_published[0]['value'] = 0;
      $clone_node->field_author[0]['uid'] = $user->uid;
      // Save quiz clone node.
      node_save($clone_node);
      drupal_set_message('Asset "' . check_plain($node->title) . '" has been cloned successfully!');
      drupal_goto('node/' . $clone_node->nid);
    break;
    case 'curriculum':
      $clone_node->status = 0;
      $clone_node->field_published[0]['value'] = 0;
      $clone_node->field_author[0]['uid'] = $user->uid;
      if ($clone_node->field_reviewers) {
        $i = 0;
        foreach($clone_node->field_reviewers as $value) {
          $clone_node->field_reviewers[$i]['uid'] = NULL;
          $i++;
        }
      }
      if ($clone_node->field_coauthor) {
        $i = 0;
        foreach($clone_node->field_coauthor as $value) {
          $clone_node->field_coauthor[$i]['uid'] = NULL;
          $i++;
        }
      }
      if(playlist_clone_access($node)) {
        // Saving the clone record of existing curriculum.
        node_save($clone_node);
        // Delete topic because while add playlist by default add new topic itself
        db_query("DELETE FROM {curriculum_topics} WHERE cid=%d", $clone_node->nid);
        //Insert clone tracking table
        db_query('INSERT INTO {clone_tracking}
                (original_id, clone_id, uid, type, created)
                VALUES(%d, %d, %d, "%s", %d)', $node->nid, $clone_node->nid, $user->uid, $node->type, time());
        // Finding curriculum topic and topic_assets records for original node.
        $res = db_query('SELECT * FROM {curriculum_topics} OGA WHERE OGA.cid = %d order by OGA.weight asc', $node->nid);
        // Insert clone record to curriculum related tables.
        if (db_affected_rows()) {
          while ($result = db_fetch_object($res)) {
            db_query('INSERT INTO {curriculum_topics}
                      (cid, topic_title, weight, created, changed, topic_type)
                      VALUES(%d, "%s", "%s", %d, %d, "%s")', $clone_node->nid, $result->topic_title, $result->ct_weight, time(), time(), $result->topic_type);
            $last_insert_id = db_last_insert_id('curriculum_topics', 'topic_id');
            $query = db_query('SELECT * FROM {curriculum_topics_assets} TA  WHERE TA.topic_id = %d order by weight asc', $result->topic_id);
            if (db_affected_rows()) {
              while($result_subtopic = db_fetch_object($query)) {
                db_query('INSERT INTO {curriculum_topics_assets}
                          (topic_id, asset, type, title, description, weight, is_admin, created, changed)
                          VALUES(%d, "%s", "%s", "%s", "%s", "%s", %d, %d, %d)',
                          $last_insert_id, $result_subtopic->asset, $result_subtopic->type, $result_subtopic->title, $result_subtopic->description, $result_subtopic->cta_weight, $result_subtopic->is_admin, time(), time());
              }
            }
          }
        }
        // Apache Solr Index Purpose
        if (function_exists('_apachesolr_nodeapi_update')) {
          _apachesolr_nodeapi_update($clone_node);
        }
        drupal_set_message('Playlist "' . check_plain($node->title) . '" has been cloned successfully!');
        drupal_goto('node/' . $clone_node->nid);
      }
      else {
        drupal_set_message('Playlist cloned Failed');
        drupal_goto('node/' . $node->nid);
      }
    break;

    default :
      $clone_node = FALSE;
    break;
  }
  return $clone_node;
}


/**
 * Implementing Curriculum View Page for My Curriculum
 *
 * @param $basket
 *  It contains flag value to set for baket or listing page
 *
 * @see removing_whitespace()
 *  is in eb_others_common.inc
 */
function mycurriculum_view($basket = 'false', $mobile_flag = FALSE, $scroll_count = 0, $tcount_flag = FALSE) {
  global $user, $base_url;
  $total_count = "";
  // To Set message while deleting the Curiculum... by using popups.... The Get method to receive value from curriculum-info.js
  if ($_GET['del_title'] || is_null(arg(1))) {
    !empty($_GET['del_title']) ? drupal_set_message('Playlist has been Removed') : NULL;
  }
  drupal_add_js(drupal_get_path('module', 'bookmark') .'/bookmark.js');
  drupal_add_js(drupal_get_path('module', 'curriculum') . "/js/curriculum-info.js");

  drupal_add_js(array("curriculum" => array("loadingImg" => $base_url . "/" . drupal_get_path("module", "curriculum") . "/images/loading.gif")), "setting");
  $limit = 5;
  // Set the Limit for basket and Listing page
  if ($basket == 'true') {
    $items = array();
  }
  if ($mobile_flag) {
    $start_limit = $scroll_count * 10;
    $limit_query = " LIMIT ". $start_limit .", 10";
  }
  $i = 1;
  $arguments = array('curriculum', $user->uid, $user->uid, $user->uid, $user->uid);
  $count_query = "SELECT COUNT(DISTINCT(node.nid)) FROM {node} node INNER JOIN {users} users ON node.uid = users.uid LEFT JOIN {node_revisions}  node_revisions ON node.vid = node_revisions.vid
          LEFT JOIN  {content_field_reviewers} content_field_reviewers ON node.vid = content_field_reviewers.vid
          LEFT JOIN  {content_field_coauthor} content_field_coauthor ON node.vid = content_field_coauthor.vid
          LEFT JOIN  {content_field_author} content_field_author ON node.vid = content_field_author.vid
        WHERE (node.type in ('%s')) AND ((users.uid = %d) OR (content_field_reviewers.field_reviewers_uid=%d) OR (content_field_coauthor.field_coauthor_uid=%d) OR (content_field_author.field_author_uid=%d))";

  $query = "SELECT DISTINCT(node.nid) AS nid, node.title AS node_title, node_revisions.body AS node_revisions_body, node_revisions.format AS node_revisions_format, node.type AS node_type, node.vid AS node_vid,  node.uid AS node_uid, node.created AS node_created, users.name as user_name,  content_field_author.field_author_uid, node_revisions.teaser as teaser, node.comment as comment_setting FROM {node} node
          INNER JOIN {users} users ON node.uid = users.uid
          LEFT JOIN {node_revisions} node_revisions ON node.vid = node_revisions.vid
          LEFT JOIN  {content_field_reviewers} content_field_reviewers ON node.vid = content_field_reviewers.vid
          LEFT JOIN  {content_field_coauthor} content_field_coauthor ON node.vid = content_field_coauthor.vid
          LEFT JOIN  {content_field_author} content_field_author ON node.vid = content_field_author.vid
          WHERE (node.type in ('%s')) AND ((users.uid = %d) OR (content_field_reviewers.field_reviewers_uid=%d) OR (content_field_coauthor.field_coauthor_uid=%d) OR (content_field_author.field_author_uid=%d)) ORDER BY node.changed DESC";
  // For Mobile
  if(!$mobile_flag) {
    $playlist_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, PLAYLIST_LISTING_PAGER_ID + 1, 0));
     // get playlist cache
     $cache_ouput = cache_get("playlist_listing:uid:" . $user->uid . ":page:" . $playlist_page, "cache_eb");
    if ($cache_ouput->data) {
      return $cache_ouput->data;
    }
    $page_result = pager_query($query, $limit, PLAYLIST_LISTING_PAGER_ID, $count_query, $arguments);
  }
  else {
    $mobile_playlist_page = ($scroll_count) ? $scroll_count : 0;
    // get Playlist cache
    $cache_ouput = cache_get("playlist_mobile:uid:" . $user->uid . ":page:" . $mobile_playlist_page, "cache_eb");
    if ($cache_ouput->data) {
      return $cache_ouput->data;
    }
    if($tcount_flag == TRUE){
      $total_count = db_affected_rows(db_query($query, $arguments));
    }     
    $page_result = db_query($query.$limit_query, $arguments);
  }
  if (db_affected_rows()) {
    $i = 0;
    while($row = db_fetch_object($page_result)) {
      // $item []will be only for Myasset basket for Curriculum and Asset Overview page
      if ($basket == 'true') {
        // Condition is used to change the content_type, class, class_type and url
        $items[] = theme('curriculum_basket', $row->nid, $row->node_type, $row->node_title, strtolower($format_value->field_format_value));
      }
      else {
        $output['fields']['nid'] = $row->nid;
        $output['fields']['node_title'] = check_plain($row->node_title);
        $output['fields']['title'] = l(truncate_utf8($row->node_title, 40, $wordsafe = TRUE, $dots = FALSE), 'node/' . $row->nid, array('attributes' => array("title" => "Click to view content")));
        // For removing whitespaces in teaser is in eb_others_common.inc
        if (function_exists('removing_whitespace')) {
          $output['fields']['body_content'] = removing_whitespace($row->teaser);
        }
        $output['fields']['author'] = function_exists("create_eduauthor") ? create_eduauthor($row->node_uid) : NULL;
        // bookmark_this_link Function are in bookmark.inc
        $output['fields']['bookmark'] = function_exists("bookmark_this_link") ? bookmark_this_link($row->nid,"asset",$row->node_title, $row->node_revisions_body) : NULL;
        $node = node_load($row->nid);
        if ($node->field_coauthor) {
          $coauthor_flag = 0;
          foreach ($node->field_coauthor as $users) {
            if ($users['uid'] == $user->uid) {
              $coauthor_flag = 1;
            }
          }
        }
        // For flag content generation
        if ($node->field_institute[0]['nid'] && function_exists("institution_flag")) {
          $output['fields']['flag_content'] = NULL;
          $output['fields']['flag_content'] = institution_flag($node->field_institute[0]['nid']);
        }
        $output['fields']['delete'] = '';
        // Check it author have rights to delete
        if (($row->node_uid == $user->uid || $row->field_author_uid == $user->uid) && $node->field_published[0]['value'] == 0) {
          $output['fields']['delete'] = l(theme_image(drupal_get_path('theme', 'educationhub') . "/images/icons/delete_icon.png", 'Delete ' . $output['fields']['node_title'], 'Delete'),  "node/" . $node->nid . "/delete", array('attributes' =>array('class' => 'popups-form-reload', 'on-popups-options' => '{hijackDestination:"FALSE"}'), 'html' => TRUE));
        }
        else if ($coauthor_flag == 1) {
          // check if co author have right to remove co author
          $output['fields']['delete'] = l(theme_image(drupal_get_path('theme', 'educationhub') . "/images/icons/delete_icon.png", 'Remove Me as Co-Author ' . $output['fields']['node_title'], 'Remove Me as Co-Author'),  "node/" . $node->nid . "/custom/removal/coauthor", array('attributes' => array('class' => 'popups-form-reload', 'on-popups-options' => '{hijackDestination:"FALSE"}'), 'html' => TRUE));
        }
        $output['fields']['links'] = NULL;
        $output['fields']['links'] = l('More', 'node/' . $row->nid,  array('attributes' => array('nodetype' => $row->node_type, 'title' => 'More', 'title' => 'Click to Preview')));
        $output['fields']['fivestar_widget'] = NULL;
        //check the average voting - if zero then dont display the stars
        if (module_exists('fivestar')) {
          $avg_vote = fivestar_get_votes('node', $node->nid);
          if (isset($avg_vote['average']['value']) > 0 && ($node->field_published[0]['value'] == 1 || ($node->status == 1 && $node->type == 'bead')) ) {
            $output['fields']['fivestar_widget'] = theme('fivestar_static', $avg_vote['average']['value']);
          }
        }
        $results['fields'][$i]['teaser_curriculum_view'] = theme('curriculum_teaser', $output);
      }
      $i++;
      //check the mobile access
      if($mobile_flag){
        $result_mobile[$i] = $output;
      }
    }
  }
  else {
    // $item []will be only for Myasset basket for Curriculum and Asset Overview page
    if($mobile_flag) {
      $result_mobile['no_curriculum'] = 'There is no Playlist Associated with you, Click on the Create Playlist to get started.';
    }
    else {
      $results['no_curriculum'] = "There is no Playlist Associated with you, Click on the Create Playlist to get started.";
    }
  }
  //Check the mobile access
  if($mobile_flag) {
    if($tcount_flag == TRUE) {
      $result_mobile['total_count'] = $total_count;
    }
    if (module_exists("cache_eb")) {
      //set the asset listing cache
      cache_set("playlist_mobile:uid:" . $user->uid . ":page:" . $mobile_playlist_page, $result_mobile, "cache_eb");
    }
    return $result_mobile;
  }
  else {
   // $basket_result will be only for Myasset basket for Curriculum and Asset Overview page
    $results['pager_links'] = theme('pager', NULL, $limit, PLAYLIST_LISTING_PAGER_ID);
    $results = theme('mycurriculum_view', $results);
    //set the recommend listing cache
    if (module_exists("cache_eb")) {
      cache_set("playlist_listing:uid:" . $user->uid . ":page:" . $playlist_page, $results, "cache_eb");
    }
    return $results;
  }
}

/**
 * adding content to a particular topic - from ajax call
 *
 */
function curriculum_edit_content() {
  
  //set default message - if nothing happened this will be returned
  $ret_msg = array(
    "status" => "default",
    "mode" => "none",
    "message" => t("Nothing happened"),
  );

  if($_POST['ajaxed'] && $_REQUEST['mode'] == "add") {
    //Check for duplicate entry with this topic id and asset
    //$content = db_result(db_query("SELECT id FROM {curriculum_topics_assets} WHERE topic_id = %d AND asset = '%s'", $_REQUEST['topic_id'], $_REQUEST['asset']));
    // Asset topic_id removed as per on every curriculum only one topic is needs to add.
    $node_curr = node_load($_REQUEST['cid']);
    $content = db_result(db_query("SELECT cta.id FROM {curriculum_topics} ct INNER JOIN {curriculum_topics_assets} cta ON ct.topic_id = cta.topic_id WHERE ct.cid = %d AND cta.asset = %s LIMIT 1", $_REQUEST['cid'], $_REQUEST['asset']));
    if($node_curr->field_published[0]['value'] == 1) {
      //content already exist, so do not add
      //set default message - if nothing happened this will be returned
      $ret_msg = array(
          "status" => "exist",
          "mode" => "add",
          "message" => t("Cannot edit published playlist"),
      );
    }
    else if($content) {
      //content already exist, so do not add
      //set default message - if nothing happened this will be returned
      $ret_msg = array(
          "status" => "exist",
          "mode" => "add",
          "message" => t("Asset already exists in Playlist"),
      );
    }
    else {
      //find the maximum weight of the content in this topic
      $result = db_query("SELECT MAX(weight) AS max_weight FROM {curriculum_topics_assets} WHERE topic_id = %d", $_REQUEST['topic_id']);
      $content = db_fetch_array($result);
      $new_weight = $content['max_weight'];
      $new_weight++;
      //find the different titles
      $display_title = $_REQUEST['title'];
      $flag = 0;
      //If the type is asset then store the asset id
      //for others store the link as asset, title and description
      if($_REQUEST['type'] == "google" || $_REQUEST['type'] == "federated") {
        $result = db_query("INSERT INTO {curriculum_topics_assets}
                         (topic_id, asset, type, title, description, weight, created, changed)
                         VALUES
                         (%d, '%s', '%s', '%s', '%s', %d, %d, %d)", $_REQUEST['topic_id'], $_REQUEST['asset'], $_REQUEST['type'], $display_title, $_REQUEST['desc'], 0, time(), time());
        $flag = 1;
      }
      else {
        $subtopic_node = node_load($_REQUEST['asset']);
        // check if that node is published means only it will get inserted
        if (($subtopic_node->field_published[0]['value'] == 1 && ($subtopic_node->type == 'asset' || $subtopic_node->type == 'curriculum' ) && ($subtopic_node->type != 'quiz')) || ($subtopic_node->status == 1 && $subtopic_node->type == 'bead')) {
          $result = db_query("INSERT INTO {curriculum_topics_assets}
                         (topic_id, asset, type, weight, created, changed)
                         VALUES
                         (%d, '%s', '%s', %d, %d, %d)", $_REQUEST['topic_id'], $_REQUEST['asset'], $_REQUEST['type'], $new_weight, time(), time());
          //call to asset tracking code - to save data in asset_tracking table
          if (function_exists("asset_tracking_add")) {
            asset_tracking_add($_REQUEST['asset'], 'curriculum', $_REQUEST['cid']);
          }
          $flag = 1;
        }
        //For Content type "Quiz" we clone the original Quiz content.
        else if($subtopic_node->status == 1 && $subtopic_node->type == 'quiz'){
          //Quiz clone.
          $clone = node_clone($subtopic_node);
          $result = db_query("INSERT INTO {curriculum_topics_assets}
                       (topic_id, asset, type, weight, created, changed)
                       VALUES
                       (%d, '%s', '%s', %d, %d, %d)", $_REQUEST['topic_id'], $clone->nid, $_REQUEST['type'], $new_weight, time(), time());
          //call to asset tracking code - to save data in asset_tracking table
          if (function_exists("asset_tracking_add")) {
            asset_tracking_add($clone->nid, 'curriculum', $_REQUEST['cid']);
          }
          $flag = 1;
        }
      }
      // Once row inserted into table then only will get success message
      if ($flag == 1) {
        // Get Curriculum Node id from that topic
        $nid = db_result(db_query("SELECT cid FROM {curriculum_topics} WHERE topic_id=%d", $_REQUEST['topic_id']));
        
        $node = node_load($nid);
        // Apache Solr Index Purpose
        if (function_exists('_apachesolr_nodeapi_update')) {
          _apachesolr_nodeapi_update($node);
        }
        //set the return message
        $new_id = db_result(db_query("SELECT MAX(id) as max_id FROM {curriculum_topics_assets}"));
        $tid = db_query("SELECT topic_id FROM {curriculum_topics} WHERE cid= %d", $nid);
        while (($row = db_fetch_array($tid))) {
           $alltopicid[] = $row['topic_id'];
          }

        //If the content type is Quiz we need to change the link from original node nid to Cloned node nid.
        if($subtopic_node->type == 'quiz'){
          $ret_msg = array(
           "status" => "ok",
           "mode" => "add",
           "content_id" => $new_id,
           "content_div" => curriculum_content_build($new_id, $display_title, $clone->nid, $_REQUEST['class_type'], $_REQUEST['cid'], $_REQUEST['basket'],$alltopicid, $_REQUEST['topic_id']),
           "message" => t("Asset added to Topic"),
          );
        }
        else{
          $ret_msg = array(
           "status" => "ok",
           "mode" => "add",
           "content_id" => $new_id,
           "content_div" => curriculum_content_build($new_id, $display_title, $_REQUEST['asset'], $_REQUEST['class_type'], $_REQUEST['cid'], $_REQUEST['basket'],$alltopicid, $_REQUEST['topic_id']),
           "message" => t("Asset added to Topic"),
          );
        }
      }
      else {
        //content not yet published, so do not add
        //set default message - if nothing happened this will be returned
        $ret_msg = array(
            "status" => "exist",
            "mode" => "not_published",
            "message" => t(check_plain($subtopic_node->title) . " not yet published"),
        );
      }
    }
  }
  elseif($_POST['ajaxed'] && $_REQUEST['mode'] == "order") {
    $topic_id = $_REQUEST['topic_id'];
    foreach($_REQUEST['content'] as $weight => $content_id) {
      $result = db_query("UPDATE {curriculum_topics_assets} SET topic_id= %d, weight = %d WHERE id = %d", $topic_id, $weight, $content_id);
    }
    $ret_msg = array(
        "status" => "ok",
        "mode" => "order",
        "message" => t("Asset Order Updated"),
    );
  }
  
  drupal_json($ret_msg);
}

/*
 * Returns HTML for a asset_basket
 *
 * @param   $nid
 *  It contains Node id
 * @param $node_type
 *  It contains Node type
 * @param $node_title
 *  It contains Node Title
 * @param $node_format
 *  (optional) Default is NULL, It contains Format of the node (eg: html, pdf, image, video, audio)
 *
 * @return
 *  it return HTML format
 */
function theme_curriculum_basket($output) {
  if (is_array($output['fields'])) {
    $class = ($node_type == 'quiz')?'quiz-nodoc':'curriculum-' . $node_format;
    $node =& $output['fields'];
    if ($node['node_title']) {
      $items = '<fieldset class="collapsible collapsed ' . $node['topic_bg_color'] . '">';
      $items .= '<legend class="collapse-processed">' . $node['node_title'] . '</legend>';
      if(is_array($node['main_topic'])) {
        foreach($node['main_topic'] as $main) {
          if ($main['topic_title']) {
            $items .= "<li class='subtopic-drop ui-droppable' topic_id=" . $main['topic_id']. "  nid=" . $main['row_id']. "><div class='playlist-headings'>".$main['topic_title']."</div>";
            if(is_array($main['subfield'])) {
              foreach($main['subfield'] as $asset) {
                if (!empty($asset['asset_title'])) {
                  $items .= '<div class="asset-list"> '.$asset['asset_title'].'</div>';
                }
              }
            }
            $items .= '</li>';
          }
       }
      }
       $items .= '</fieldset>';
    }
  }
  return $items;
}

/**
 * Custom function to delete selected Sub topic in Playlist through jquery
 *
 */
function delete_content_ajax(){
  //Get Sub topics ids.
  $subtopic_ids = $_POST['ids'];
  //Get Topics Ids
  $selected_topic_ids = $_POST['topic_ids'];

  //This will work when user's select Sub topic check box seperately.
  if($subtopic_ids){
    $ids = array();
    if($subtopic_ids){
      $ids = explode(',', $subtopic_ids);
    }
    $topic_ids = array();
    if(count($ids) > 0){
      foreach($ids as $key => $val){
        $topic_ids[] = db_result(db_query("SELECT topic_id FROM {curriculum_topics_assets} WHERE id = %d", $val));
        db_query("DELETE FROM {curriculum_topics_assets} WHERE id = %d", $val);
      }
      //Merge duplicate array elements.
      $topic_unique_ids = array_unique($topic_ids);
      if(db_affected_rows()){
        print 'Sub topics deleted';
        drupal_set_message('Selected Sub Topics are Deleted.');
      }
      else{
        print '';
      }
      //Check whether Topic Id having Sub topic in DB.
      foreach($topic_unique_ids as $key => $val){
        db_result(db_query("SELECT id FROM {curriculum_topics_assets} WHERE topic_id = %d", $val));
          //No other Sub topic associated with current topic id, we need to delete the Topic Id from DB.
        if(!db_affected_rows()){
          db_query("DELETE FROM {curriculum_topics} WHERE topic_id = %d", $val);
          drupal_set_message('Selected Sub Topics related Topics also Deleted.');
        }
      }
    }
    else{
      print '';
    }
  }
  else if($selected_topic_ids){//This will work when check "Select all" check box
    $topics = array();
    if($selected_topic_ids){
      $topics = explode(',', $selected_topic_ids);
    }
    if(count($topics) > 0){
        foreach($topics as $key => $val){
            db_query("DELETE FROM {curriculum_topics_assets} WHERE topic_id = %d", $val);
            db_query("DELETE FROM {curriculum_topics} WHERE topic_id = %d", $val);
        }
        if(db_affected_rows()){
            print 'Topics deleted';
            drupal_set_message('All topics got Deleted.');
        }
        else{
            print '';
        }
    }
    else{
      print '';
    }
  }
}

/**
 * Playlist basket block pager in ajax load.
 *
 */
function playlist_block_ajax() {
  $_SESSION['playlist'] = $_GET['page'];
  print_r(curriculum_bridge_listing());
  exit;
}

/**
 * Playlist listing page pager in ajax load.
 *
 */
function playlist_listing_ajax() {
  $_GET['q'] = 'bridge/mycurriculum';
  print_r(mycurriculum_view());
  exit;
}