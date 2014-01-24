<?php

/**
 * Implementing the Myasset View Page
 *
 * My asset Listing Page
 *
 * @param $basket
 *  (Optional), Default is False It is use to display in Blocks
 *
 * @return
 *  It returns themed html
 *
 *
 * @see theme_asset_basket()
 * @see theme_item_list()
 * @see theme_myasset_view()
 * @see teaser_nodes() is in eb_others.module
 * @see removing_whitespace() is in eb_others_common.inc
 * @see playlist_query() is in curriculum.module
 */
function myasset_view($basket = 'false', $mobile_flag = FALSE, $scroll_count = FALSE, $tcount_flag = FALSE) {
  global $user;
 
  $total_count = "";
  //If coming from asset delete popup - by asset-info.js - with del_title, then set message and reload again
  if (isset($_GET['del_title'])) {
    drupal_goto('bridge');
  }
  // Include Js for pager, Bookmark features,
  // Create asset dropdown feature is in asset-ddmenu.js
  drupal_add_js(drupal_get_path('module', 'bookmark') .'/bookmark.js');
  drupal_add_js(drupal_get_path('module', 'asset').'/js/asset-pager.js');
  drupal_add_js(drupal_get_path('module', 'asset').'/js/asset-ddmenu.js');
  drupal_add_js(drupal_get_path('module', 'asset') . "/js/asset-info.js");
  drupal_add_js(drupal_get_path('module', 'curriculum') . "/js/baskets.js");
  drupal_add_js(drupal_get_path('module', 'asset') . "/js/asset.js");
  // $item will be only for Myasset basket for Curriculum and Asset Overview page
  // Set the Limit for basket and Listing page
  if ($basket == 'true') {
    $items = array();
    $limit = 5;
  }  
  else {
    if (arg(0) == 'bridge' && arg(1) != "myassets") {
      drupal_add_js(array('bridge_basket' => TRUE), 'setting');
    }
    $limit = 5;
  }
  //check the mobile flag
  if ($mobile_flag) {
    $start_limit = $scroll_count * 10;
    $limit_query = " LIMIT ". $start_limit .", 10";
  }
  $i=1;
  // count query is used to pass the pager_query to get exact count
  // Purpose of count query is used to get exact pager
  $count_query = "SELECT COUNT(DISTINCT(node.nid)) AS nid
          FROM {node} node
          INNER JOIN {users} users ON node.uid = users.uid
          LEFT JOIN {node_revisions} node_revisions ON node.vid = node_revisions.vid
          LEFT JOIN  {content_field_reviewers} content_field_reviewers ON node.vid = content_field_reviewers.vid
          LEFT JOIN  {content_field_coauthor} content_field_coauthor ON node.vid = content_field_coauthor.vid
          LEFT JOIN  {content_field_author} content_field_author ON node.vid = content_field_author.vid
          WHERE node.type IN ('asset', 'quiz') AND ((users.uid = %d) OR (content_field_reviewers.field_reviewers_uid=%d) OR (content_field_coauthor.field_coauthor_uid=%d) OR (content_field_author.field_author_uid=%d)) $exta_cond ";
          
  $query = "SELECT DISTINCT(node.nid) AS nid, node.vid as vid, node.title AS node_title, node_revisions.body AS node_revisions_body, node_revisions.format AS node_revisions_format, node.type AS node_type, node.vid AS node_vid,  node.uid AS node_uid, node.created AS node_created, users.name as user_name, content_field_author.field_author_uid, node_revisions.teaser as teaser
          FROM {node} node
          INNER JOIN {users} users ON node.uid = users.uid
          LEFT JOIN {node_revisions} node_revisions ON node.vid = node_revisions.vid
          LEFT JOIN  {content_field_reviewers} content_field_reviewers ON node.vid = content_field_reviewers.vid
          LEFT JOIN  {content_field_coauthor} content_field_coauthor ON node.vid = content_field_coauthor.vid
          LEFT JOIN  {content_field_author} content_field_author ON node.vid = content_field_author.vid
          WHERE node.type IN ('asset', 'quiz') AND ((users.uid = %d) OR (content_field_reviewers.field_reviewers_uid=%d) OR (content_field_coauthor.field_coauthor_uid=%d) OR (content_field_author.field_author_uid=%d)) ORDER BY node.changed DESC";
          
  $arguments = array($user->uid, $user->uid, $user->uid, $user->uid);
  if(!$mobile_flag) {
    if ($basket == 'true') {
      $asset_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, ASSET_BASKET_PAGER_ID + 1, 0));
      // get recommend cache
      if (module_exists("cache_eb")) {
        $cache_ouput = cache_get("asset_basket:uid:" . $user->uid . ":page:" . $asset_page, 'cache_eb');
        if ($cache_ouput->data) {
          return $cache_ouput->data;
        }
      }
      $pager_id = ASSET_BASKET_PAGER_ID;
    }
    else {
      $asset_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, ASSET_LISTING_PAGER_ID + 1, 0));
      // get recommend cache
      if (module_exists("cache_eb")) {
        $cache_ouput = cache_get("asset_listing:uid:" . $user->uid . ":page:" . $asset_page, 'cache_eb');
        if ($cache_ouput->data) {
          return $cache_ouput->data;
        }
      }
      $pager_id = ASSET_LISTING_PAGER_ID;
    }
    // check playlist available in playlist basket if available then only add dragable links to listing
    if (function_exists("playlist_query")) {
      $playlist_arguments = array('curriculum', $user->uid, $user->uid, $user->uid, $user->uid);
      $playlist_count = playlist_query(NULL, NULL, $playlist_arguments, TRUE);
    }
    //check if user have rights to drag and drop to playlist or asset
    $drop_tooltip = FALSE;
    if (user_access("create curriculum content") || user_access("create asset content")) {
      $drop_tooltip = TRUE;
    }
    $page_result = pager_query($query, $limit, $pager_id, $count_query, $arguments);
  }
  else {
    $mobile_asset_page = ($scroll_count) ? $scroll_count : 0;
     // get recommend cache
    if (module_exists("cache_eb")) {
      $cache_ouput = cache_get("asset_mobile:uid:" . $user->uid . ":page:" . $mobile_asset_page, 'cache_eb');
      if ($cache_ouput->data) {
        return $cache_ouput->data;
      }
    }
    $page_result = db_query($query . $limit_query, $arguments);
    if($tcount_flag == TRUE) {
      $total_count = db_affected_rows(db_query($query, $arguments));
    }
  }
  // Check if it has a results
  if(db_affected_rows()) {
    while ($obj = db_fetch_object($page_result)) {
      // Get format value of the asset cck,
      $query = db_query("SELECT  F.field_format_value FROM {content_type_asset} A, {content_field_format} F WHERE F.vid=%d and  A.vid=%d", $obj->vid, $obj->vid);
      $format_value = db_fetch_object($query);
      // $item []will be only for Myasset basket for Curriculum and Asset Overview page
      if ($basket == 'true') {
        // Condition is used to change the content_type, class, class_type and url
        if (function_exists("drag_drop_make_link")) {
          $drag_class = "asset-links";
          if ($playlist_count == 0 || !$drop_tooltip) {
            $drag_class = NULL;
          }
          $items[] = drag_drop_make_link_left_block( $obj->nid, truncate_utf8($obj->node_title, 26, TRUE, TRUE), $obj->node_type, truncate_utf8(strip_tags($obj->teaser), 200, $wordsafe = FALSE, $dots = TRUE), $obj->node_title, $drag_class, TRUE);
        }
      }
      else {
        // added to get the drag and drop for listing pages.
        $output['fields']['nid'] = $obj->nid;
        $output['fields']['node_type'] = $obj->node_type;
        $output['fields']['node_title'] = truncate_utf8(check_plain($obj->node_title), 40, $wordsafe = FALSE, $dots = TRUE);
        $output['fields']['class_type'] = ($node_type == 'quiz')?'quiz-nodoc':'asset-' . strtolower($format_value->field_format_value);
        if (function_exists("drag_drop_make_link")) {
          if ($playlist_count == 0 || !$drop_tooltip) {
            $output['fields']['title'] = drag_drop_make_link($obj->nid, $obj->node_title, $obj->node_type, truncate_utf8(strip_tags($obj->teaser), 200, $wordsafe = FALSE, $dots = TRUE), NULL, "float-left");
          }
          else {
            $output['fields']['title'] = drag_drop_make_link($obj->nid, $obj->node_title, $obj->node_type, truncate_utf8(strip_tags($obj->teaser), 200, $wordsafe = FALSE, $dots = TRUE), 'Drag to Drop into your playlists', "asset-links float-left");
          }
        }
        // For removing whitespaces in teaser
        if (function_exists('removing_whitespace')) {
          $output['fields']['body_content'] = removing_whitespace($obj->teaser);
        }
        // To Check if he is a Co-Author
        $coauthor_flag = 0;
        $node = node_load($obj->nid);
        if ($node->field_coauthor) {
          foreach($node->field_coauthor as $value) {
            if ($value['uid'] == $user->uid ) {
              $coauthor_flag = 1;
            }
          }
        }
        // Set the comment  value defulat to NULL
        if (function_exists("bookmark_this_link") && (($node->field_published[0]['value'] == 1 && $node->type == "asset") || ($node->status == 1 && ($node->type == "bead" || $node->type == "quiz")))) {
          // bookmark_this_link Function are in bookmark.inc
          
          $output['fields']['bookmark'] = bookmark_this_link($obj->nid, $obj->node_type, $obj->node_title, $obj->node_revisions_body);
        }
        // For Default it Should be Null
        $output['fields']['delete'] = NULL;
        // Check it user have rights to delete
        if ($obj->node_uid == $user->uid || $obj->field_author_uid == $user->uid) {
          $output['fields']['delete'] = l(theme_image(drupal_get_path('theme', 'educationhub') . "/images/icons/delete_icon.png", 'Delete ' . $obj->node_title, 'Delete'),  "node/" . $obj->nid . "/delete", array('attributes' => array('class' => 'popups-form-reload', 'on-popups-options' => '{hijackDestination:"FALSE"}'), 'html' => TRUE));
        }
        else if($coauthor_flag == 1){
          $output['fields']['delete'] = l(theme_image(drupal_get_path('theme', 'educationhub') . "/images/icons/delete_icon.png", 'Remove Me as Co-Author' . $obj->node_title, 'Remove Me as Co-Author'),  "node/" . $obj->nid . "/custom/removal/coauthor", array('attributes' => array('class' => 'popups-form-reload', 'on-popups-options' => '{hijackDestination:"FALSE"}'), 'html' => TRUE));
        }
        if (function_exists("searchimagefiles") && function_exists("teaser_nodes")) {
          // searchimagefiles Function are in eb_search.inc
          $format = searchimagefiles($obj->node_type, $format_value->field_format_value);
          $output['fields']['picture'] = l(teaser_nodes(NULL, 'dis_rev_com_image2', $format), 'node/' . $obj->nid ,array('html' => TRUE));
        }
        // Author Name
        $output['fields']['author'] = function_exists("create_eduauthor")?create_eduauthor($obj->node_uid):NULL;
        // For flag content generation
        if ($node->field_institute[0]['nid'] && function_exists("institution_flag")) {
          $output['fields']['flag_content'] = NULL;
          $output['fields']['flag_content'] = institution_flag($node->field_institute[0]['nid']);
        }
        $output['fields']['fivestar_widget'] = NULL;
        //check the average voting - if zero then dont display the stars
        if (module_exists('fivestar')) {
          $avg_vote = fivestar_get_votes('node', $node->nid);
          if (isset($avg_vote['average']['value']) > 0 && ($node->field_published[0]['value'] == 1 || ($node->status == 1 && $node->type == 'bead')) ) {
            $output['fields']['fivestar_widget'] = theme('fivestar_static', $avg_vote['average']['value']);
          }
        }
        $output['fields']['links'] = NULL;
        $output['fields']['links'] = l('More', 'node/' . $node->nid,  array('attributes' => array('nodetype' => $node->type, 'title' => 'Click to Preview', 'tabindex' => "0")));
        // Each and every asset teaser should get themed by using this asset_teaser
        $results['fields'][$i]['teaser_asset_view'] = theme('asset_teaser', $output);
      }
      //check the mobile access
      if($mobile_flag){
        $result_mobile[$i] = $output;
      }
      //$node->nid = '';
      $i++;
    }
  }
  else {
     // $item []will be only for Myasset basket for Curriculum and Asset Overview page
    if ($basket == 'true') {
      $items[] = 'No Record Found';
    }
    //check the mobile access
    else if($mobile_flag){
      $result_mobile['no_record'] = 'There is no Asset Associated with you, Click on the Create Asset to get started.';
    }
    else {
     $results['no_record'] = 'There is no Asset Associated with you, Click on the Create Asset to get started.';
    }
  }
 //Check the mobile access
  if($mobile_flag){
    if($tcount_flag == TRUE){
      $result_mobile['total_count'] = $total_count;
    }
    //set the asset listing cache
    if (module_exists("cache_eb")) {
      cache_set("asset_mobile:uid:" . $user->uid . ":page:" . $mobile_asset_page, $result_mobile, 'cache_eb'); 
    }
    return $result_mobile;
  }
  else {
    // $basket_result will be only for Myasset basket for Curriculum and Asset Overview page
    if ($basket == 'true') {
      $basket_result = theme('item_list', $items);
      $basket_result .= theme('pager', NULL, $limit, $pager_id);
      //set the asset basket cache
      if (module_exists("cache_eb")) {
        cache_set("asset_basket:uid:" . $user->uid . ":page:" . $asset_page, $basket_result, 'cache_eb');
      }
      return $basket_result;
    }
    else  {
      $results['pager'] = theme('pager', NULL, $limit, $pager_id);
      $results = theme('myasset_view', $results);
       //set the asset listing cache
      if (module_exists("cache_eb")) {
        cache_set("asset_listing:uid:" . $user->uid . ":page:" . $asset_page, $results, 'cache_eb');
      }
      return $results;
    }
  }
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
function theme_asset_basket($nid, $node_type, $node_title, $node_format = NULL) {
  if(is_numeric(arg(1))) {
    $node = node_load(arg(1));
  }
}

/**
 *Getting body to embed in the asset edit page
 *From ajax call - when drag drop
 */
function asset_get_embed() {
  if($_POST['ajaxed'] && $_POST['mode'] == "embed") {
    $nid = $_REQUEST['asset'];
    $nodeObj = node_load($nid);
    if ($nodeObj->field_format[0]['value']=='HTML') {
      $body = $nodeObj->body;
    }
    elseif($nodeObj->field_format[0]['value']=='IMAGE' || $nodeObj->field_format[0]['value']=='image/jpeg') {
      if($nodeObj->field_custom_file_upload[0]['filename']) {
        $image_path = $nodeObj->field_custom_file_upload[0]['filepath'];
        $body = theme('imagecache', 'assetimage', $image_path);
      }
      else {
        $body = "can not get image.";
      }
    } // Elseif condition for quiz added by Fero on july 16 to embed content in HTML format.
    elseif($nodeObj->type == 'quiz'){
      $body = $nodeObj->body;
    }
    $ret_msg = array(
      "status" => "ok",
      "body" => $body,
    );
    drupal_json($ret_msg);
  }
  else {
    $ret_msg = array(
      "status" => "error",
    );
    drupal_json($ret_msg);
  }
}

/**
 * Menu callback function - for saving tha asset tracking -
 * from asset html overview edit page - after insert - from ajax call
 */
function asset_tracking_asset() {
  if($_POST['ajaxed'] && $_POST['mode'] == 'track') {
    asset_tracking_add($_REQUEST['asset_id'], 'asset', $_REQUEST['parent_id']);
    $ret_msg = array(
      'status' => 'ok'
    );
    drupal_json($ret_msg);
  }
}

/**
 * Remove one entry in asset tracking table when a content reemoved from the curriculum overview page
 * aid: asset id
 * pid: parent id (curriculum id)
 */
function asset_tracking_remove($aid, $pid) {
  $result = db_query("DELETE FROM {asset_tracking} WHERE asset_id=%d AND parent_id=%d LIMIT 1", $aid, $pid);
}

/**
 * Asset tracking statistics page - for admin
 */
function asset_tracking_report() {
  drupal_set_title("Asset Tracking Statistics");
  if (isset($_REQUEST['type'])) {
    $parent_type = $_REQUEST['type'];
  }
  $form = array();
  $form['track_filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter by type'),
  );
  $form['track_filter']['parent_type'] = array(
    '#type' => 'select',
    '#title' => t('Select Type'),
    '#default_value' => $parent_type,
    '#options' => array(
      'both' => 'Both',
      'curriculum' => t('Playlist'),
      'asset' => 'Asset',
    ),
  );
  $form['track_filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['#validate'][] = 'asset_tracking_report_validate';
  //make the table having sortable headers
  $headers = array(
    array('data' => t('Asset')),
    array('data' => t('Used Type'), 'field' => 'parent_type'),
    array('data' => t('By Teacher'), 'field' => 'teachers'),
    array('data' => t('By Student'), 'field' => 'students'),
    array('data' => t('Total'), 'field' => 'cnt', 'sort' => 'desc'),
  );
  $tablesort = tablesort_sql($headers);
  $limit = 10;
  if (isset($parent_type) && $parent_type != 'both') {
    //get the results
    //to use multiple count in a single table - sigle query - we can use SUM function
    $sql = "SELECT
            asset_id, parent_type, SUM(if(rid=3,1,0)) AS teachers, SUM(if(rid=4,1,0)) AS students, COUNT(*) AS cnt
            FROM {asset_tracking}
            WHERE parent_type='%s'
            GROUP BY asset_id";
    $countquery = sprintf("SELECT COUNT(DISTINCT(asset_id)) FROM {asset_tracking} WHERE parent_type='%s'", $parent_type);
    $result = pager_query($sql . $tablesort, $limit, 0 , $countquery, $parent_type);
  }
  else {
    $sql = "SELECT
            asset_id, parent_type, SUM(if(rid=3,1,0)) AS teachers, SUM(if(rid=4,1,0)) AS students, COUNT(*) AS cnt
            FROM {asset_tracking}
            GROUP BY asset_id";
    $countquery = "SELECT COUNT(DISTINCT(asset_id)) FROM {asset_tracking}";
    $result = pager_query($sql . $tablesort, $limit, 0 , $countquery);
  }
  $rows = array();
  while ($row = db_fetch_object($result) ) {
    $rows[] = array(
      'data' => array(
        //using function from bookmark module to make link from asset id
        array('data' => function_exists("bookmark_make_link") ? bookmark_make_link($row->asset_id, $row->title, $row->type) : l($row->asset_id, 'node/' . $row->asset_id)),
        array('data' => $row->parent_type),
        array('data' => $row->teachers),
        array('data' => $row->students),
        array('data' => $row->cnt),
      )
    );
  }
  //insert the table in to the form as markup type
  $form['result'] = array(
    '#type' => 'markup',
    '#title' => t('Result'),
    '#value' => theme('table', $headers, $rows) . theme('pager', NULL, $limit, 0),
  );
  return $form;
}

function asset_tracking_report_validate($form, &$form_state) {
  global $base_url;
  drupal_goto("admin/reports/asset-tracking", "type=" . $form_state['values']['parent_type']);
}

/**
 * Dispplaying title and content for stringable beads - beads with same sequence number
 * 
 */
function beads_stringable($node, $seq_no, $title_list = FALSE) {
  global $base_url;
  $results = array();
  $i = 0;
  $doc_id = $node->field_source_id[0]['value'];
  $sql = db_query("SELECT nr.nid, nr.title, nr.body
                  FROM {node_revisions} nr
                  INNER JOIN {content_type_bead} ctb ON nr.vid = ctb.vid
                  INNER JOIN {node} n ON n.vid = ctb.vid
                  WHERE  ctb.field_source_id_value = '%s'",  $doc_id);
  while ($row = db_fetch_object($sql)) {
    $node = node_load($row->nid);
    if (!$title_list)  {
      $output2['fields'][$i]['title'] = l(function_exists("teaser_nodes") ? teaser_nodes($node->title) : $node->title, 'node/' . $row->nid, array('html' => TRUE));
      $output2['fields'][$i]['body_content'] = $node->body;

      $output2['fields'][$i]['recommend'] = l(theme_image(drupal_get_path('theme', 'educationhub') . "/images/recommend.png"), "recommend/" . $node->nid, array('attributes' => array('title' => 'Recommend'),'html' => TRUE));;
      $output2['fields'][$i]['bookmark'] = function_exists("bookmark_this_link") ? bookmark_this_link($node->nid, $node->type, $node->title, $node->body) : NULL;
      $comment_plural = ($node->comment_count == 1)?' Comment':' Comments';
      $comments = l($node->comment_count . $comment_plural, 'node/' . $node->nid);
      $output2['fields'][$i]['comments'] = $comments;
      $url = function_exists("searchimagefiles") ? searchimagefiles($node->type, $node->field_format[0]['value']) : NULL;
      $output2['fields'][$i]['picture'] = function_exists("teaser_nodes") ? l(teaser_nodes(NULL, 'dis_rev_com_image2', $url), $node->path, array('html' => TRUE)) : NULL;
      $output2['fields'][$i]['source'] = $node->field_source[0]['value'];
      $output2['fields'][$i]['nid'] = $node->nid;
      if ($node->uid == $user->uid || $user->uid == 1) {
        $output2['fields'][$i]['delete'] = l(theme_image( drupal_get_path('theme', 'educationhub') . "/images/trash.png"),  "node/" . $obj->nid . "/delete", array('attributes' => array('class' => 'popups-form-reload '), 'html' => TRUE));;
      }
    }
    else {
      // For id to be print for each title 
      $output2['title'][$i]['node_title'] = '<a href=#title-' . $node->nid . '>' . function_exists("teaser_nodes") ? teaser_nodes($node->title, NULL, NULL, 20) : NULL . '</a>';
      $output2['title'][$i]['nid'] = $node->nid;
    }
    $i++;
  }
  if (!$title_list)  {
    return theme('beads_stringable', $output2);
  }
  else {
    return theme('beads_stringable_title', $output2['title']);
  }
}


/**
 * Return autocomplete results for usernames.
 *
 * Prevents usernames from being used and/or suggested twice.
 */
function autocomplete_users($string) {
  $names = array();
  // 1: Parse $string and build list of valid user names.
  $fragments = explode(',', $string);
  foreach ($fragments as $index => $name) {
    if ($name = trim($name)) {
      $names[$name] = $name;
    }
  }
  // By using user_validate_user we can ensure that names included in $names are at least logisticaly possible.
  // 2: Find the next user name suggestion.
  $fragment = array_pop($names);
  $matches = array();
  if (!empty($fragment)) {
    $co_authors = NULL;
    $reviewers = NULL;
    if (arg(2) == 'coauthor') {
      $perm1 = db_query("SELECT rid FROM permission WHERE perm LIKE '%can coauthor node%'");
      if (db_affected_rows()) {
        while($row = db_fetch_object($perm1)) {
          $co_authors_list[] = $row->rid;
        }
        $co_authors = implode(', ', $co_authors_list);
      }
    }
    else {
      $perm2 = db_query("SELECT rid FROM permission WHERE perm LIKE '%can review node%'");
      if (db_affected_rows()) {
        while($row = db_fetch_object($perm2)) {
          $reviewers_list[] = $row->rid;
        }
        $reviewers = implode(', ', $reviewers_list);
      }
    }
    $user_not_in = !empty($names)?implode("','", $names):NULL;
    $query['query'] = "SELECT cp.field_profile_first_name_value, cp.field_profile_last_name_value, U.mail,  U.picture FROM {users} U INNER JOIN {node} n ON (U.uid = n.uid) INNER JOIN {content_type_profile} cp ON (cp.nid = n.nid) LEFT JOIN users_roles R ON U.uid = R.uid WHERE (cp.field_profile_first_name_value  LIKE '$fragment%%') AND (U.status <> 0) AND U.mail  NOT IN ('$user_not_in') AND R.rid IN (" . $reviewers . $co_authors . ")";
    $result = db_query_range($query['query'], $fragment, 0, 10);
    $prefix = count($names) ? implode(", ", $names) .", " : '';
    // 3: Build proper suggestions and print.
    while ($user = db_fetch_object($result)) {
      // $matches[$prefix . $user->name .", "] = $user->name;
      if( $user->picture ) {
        $user_pic =   $user->picture;
      }
      else {
        $user_pic =   variable_get('user_picture_default','');
      }

      $user_image = theme('imagecache', 'autocomplete_user_profile_image_32', $user_pic, '', '');
      //Call custom function for constructing Autocomplete Users. Written in eb_others.module
      $res = function_exists("generate_autocomplete_user_name") ? generate_autocomplete_user_name($user->mail, check_plain($user->field_profile_first_name_value), check_plain($user->field_profile_last_name_value), $user_image) : NULL;
      $matches[$prefix . $user->mail .", "] = $res;
    }
  }
  // convert to object to prevent drupal bug, see http://drupal.org/node/175361
  drupal_json((object)$matches);
}

/**
 * Asset basket block pager in ajax load.
 *
 */
function asset_block_ajax() {
  print_r(myasset_view(TRUE));
  exit;
}
/**
 * Asset listing page pager in ajax load.
 *
 */
function asset_listing_ajax() {
  $_GET['q'] = 'bridge/myassets';
  print_r(myasset_view());
  exit;
}