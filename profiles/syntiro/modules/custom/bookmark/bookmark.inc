<?php
// $Id$
/**
 * @file
 * supporting functions for bookmark module
 */

/**
 * Save the bookmark into database - for saving internal links
 * return changed link: Remove Bookmark thro' ajax
 * @todo change: Need to merge or relooka at bookmark function
 * for node/external link
 */
function bookmark_add_process($nid) {
  global $user;

  /*Check whether the request is came from Our site or from Mobile Apps*/
  if(arg(0) == 'bookmark' && arg(1) == 'add'){
    $node = node_load(arg(2));
  }
  else {
    //Access from Mobile apps.
    $node = node_load($nid);
  }
  /* Get User's Role ID */
  if ($user->roles[4]) {
    $rid = '4';
  }
  elseif ($user->roles[3]) {
    $rid = '3';
  }

  //Do not add if already exists
  if (!check_bookmark($node->nid, $user->uid)) {
    $insert_obj = new stdClass();
    $insert_obj->asset = $node->nid;
    $insert_obj->type = $node->type;
    $insert_obj->title = $node->title;
    $insert_obj->description = '';
    $insert_obj->uid = $user->uid;
    $insert_obj->rid = $rid;
    $insert_obj->timestamp = time();
    drupal_write_record('bookmark', $insert_obj);

    $bid = $insert_obj->id;
    if (function_exists("_apachesolr_nodeapi_update")) {
      _apachesolr_nodeapi_update($node);
    }
    if (arg(3)) {
      $bookmark_options = 'Bookmarked';
      $href = "bookmark/remove/" . $bid . "/Bookmarked";
    }
    else {
      $bookmark_options = NULL;
      $href = "bookmark/remove/" . $bid;
    }

    //@todo construct link_text
    if($node->type == 'curriculum'){
      $node->type = 'playlist';
    }
    $ret_msg = _message_construct("added", $node->nid, ucfirst($node->type) . " Bookmarked", $href, "bookmarked_icon.png", "Remove Bookmark", $bookmark_options);
    //apache solr Index
    //clear the cache
    cache_clear_all("bookmark_listing:uid:" . $user->uid . ":", "cache_eb", TRUE);
    cache_clear_all("bookmark_basket:uid:" . $user->uid . ":", "cache_eb", TRUE);
    // for mobile clear cache
    cache_clear_all("bookmark_mobile:uid:" . $user->uid . ":", "cache_eb", TRUE);
  }
  else {
    $ret_msg = array("status" => "exist", "message" => "Already Bookmarked");
  }

  //check if called using ajax
  //if ajax call - return json data
  //if not, redirect to previous page
  if ($_POST['ajaxed']) {
    drupal_json($ret_msg);
  }
  else {
    /*Return value is based on whether the request is came from Our site or from Mobile apps*/
    if(arg(0) != 'bookmark' && arg(1) != 'add'){
      return $ret_msg;
    }
    else{
      return $ret_msg['message'];
    }
  }
}

/**
 * Save the bookmark into database - for saving external links
 *
 */
function bookmark_add_process_external() {
  global $user;
  $uid = $user->uid;
  /* Get User's Role ID */
  if ($user->roles[4]) {
    $rid = '4';
  }
  elseif ($user->roles[3]) {
    $rid = '3';
  }
  $asset = $_GET['link'];
  $title = str_replace('&amp;#39;', "'", check_plain($_GET['title']));
  $description = str_replace('&amp;#39;', "'", $_GET['desc']);
  $title = str_replace('&#39;', "'", $title);
  $description = str_replace('&#39;', "'", $description);
  $type = $_GET['type'];
  //Do not add if already exists


  if (!check_bookmark($asset, $uid)) {
    $insert_obj = new stdClass();
    $insert_obj->asset = $asset;
    $insert_obj->type = $type;
    $insert_obj->title = $title;
    $insert_obj->description = $description;
    $insert_obj->uid = $uid;
    $insert_obj->rid = $rid;
    $insert_obj->timestamp = time();
    drupal_write_record('bookmark', $insert_obj);
    $bid = $insert_obj->id;
    $ret_msg =_message_construct("added", $asset, "Link Bookmarked", "bookmark/remove/" . $bid, 'bookmarked_icon.png', 'Remove this bookmark');
     //clear the cache
    cache_clear_all("bookmark_listing:uid:" . $user->uid . ":", "cache_eb", TRUE);
    cache_clear_all("bookmark_basket:uid:" . $user->uid . ":", "cache_eb", TRUE);
    // for mobile clear cache
    cache_clear_all("bookmark_mobile:uid:" . $user->uid . ":", "cache_eb", TRUE);

  }
  else {
    $ret_msg = array("status" => "exist", "message" => "This External link has been previously bookmarked.");
  }
  //check if called using ajax
  //if ajax call - return json data
  //if not, redirect to previous page
  if ($_POST['ajaxed']) {
    drupal_json($ret_msg);
  }
  else {
    return $ret_msg['message'];
  }
}
/**
 * It generate the array
 *
 * @param $stauts
 *  It contains status message
 * @param $link
 *  It contains node link or external link
 * @param $message
 *  It contains Message
 * @param $href
 *  It contains url to redirect
 * @param $link_text
 *  It contains text are image name
 * @param $title
 *  It contains Title
 * @param $text
 *  It contains word for bookmark
 *
 * @return
 *  It contains array structure
 *
 */
function _message_construct($status, $link, $message, $href, $link_text = NULL, $title, $text = FALSE) {
  if ($text == TRUE) {
    $link_text_image = $text;
  }
  else {
    $link_text_image = theme_image(drupal_get_path('theme', 'educationhub') . "/images/icons/" . $link_text);
  }
  return  array("status" => $status, "asset" => $link, "message" => $message, "href" => $href, "link_text" => $link_text_image, "title" => $title);
}

/**
 *Remove the bookmark - calling from ajax links
 *
 */
function bookmark_remove_process($bid) {
  global $user;
  $uid = $user->uid;

  /*Check whether the request is came from Our site or from Mobile Apps*/
  if(arg(0) == 'bookmark' && arg(1) == 'remove'){
    $bookmark = bookmark_load(arg(2));
  }
  else{
    $bookmark = bookmark_load($bid);
  }

  //Only do delete process if already data exist
  if (check_bookmark($bookmark->id)) {
      if (arg(3)) {
        $bookmark_options = 'Bookmark';
        $href = "bookmark/add/" . $bookmark->asset . '/Bookmark';
      }
      else {
        $href = "bookmark/add/" . $bookmark->asset;
        $bookmark_options = NULL;
      }
    if ($bookmark->type == "google" || $bookmark->type == "federated") {
      //if it is a external link then add link will be bookmark/add/external?link=...&title=...&desc=...
      db_query("DELETE FROM {bookmark} WHERE id = %d", $bookmark->id);

      $ret_msg = _message_construct("removed", $asset, " Bookmark Removed", "bookmark/add/external?link=" . $bookmark->asset . "&title=" . check_plain($bookmark->title) . "&desc=" . $bookmark->description . "&type=" . $bookmark->type, 'bookmark_icon.png', "Bookmark this", $bookmark_options);
    }
    else {
      // Apache Solr Index
      $q_assetid = db_result(db_query("select asset FROM {bookmark} WHERE id = %d", $bookmark->id));
      $node = node_load($q_assetid);
      if (function_exists("_apachesolr_nodeapi_update")) {
        _apachesolr_nodeapi_update($node);
      }
      //if it is a asset then add link will be bookmark/add/%asset_id
      db_query("DELETE FROM {bookmark} WHERE id = %d", $bookmark->id);
      $ret_msg = _message_construct("removed", $bookmark->asset,  "Bookmark Removed", $href, 'bookmark_icon.png', "Bookmark this", $bookmark_options);
    }
    //clear the cache
    cache_clear_all("bookmark_listing:uid:" . $user->uid . ":", "cache_eb", TRUE);
    cache_clear_all("bookmark_basket:uid:" . $user->uid . ":", "cache_eb", TRUE);
    // for mobile clear cache
    cache_clear_all("bookmark_mobile:uid:" . $user->uid . ":", "cache_eb", TRUE);

  }
  else {
    $ret_msg = array("status" => "not-exist", "message" => "Bookmark doesnot exist");
  }
  //check if called using ajax
  //if ajax call - return json data
  //if not, redirect to previous page
  if ($_POST['ajaxed']) {
    drupal_json($ret_msg);
  }
  else {
    /*Return value is based on whether the request is came from Our site or from Mobile apps*/
    if(arg(0) != 'bookmark' && arg(1) != 'remove'){
      return $ret_msg;
    }
    else{
      drupal_goto(get_session_url());
    }
  }
}

/**
 * Remove the bookmark - confirmation form - from mybookmarks page
 *
 */
function remove_confirmation_form($bookmark) {
  drupal_add_js(drupal_get_path('module', 'bookmark') . '/bookmark.js');

  $form['bid'] = array(
    '#type' => 'hidden',
    '#value' => arg(2),
  );

  $title = db_result(db_query("SELECT N.title FROM {node} N INNER JOIN {bookmark} B on B.asset = N.nid WHERE B.id=%d", arg(2)));
  if (empty($title)) {
    $title = db_result(db_query("SELECT title FROM {bookmark} WHERE id=%d", arg(2)));
  }
  return confirm_form(
    $form,
    teaser_nodes($title),
    'bridge/mybookmarks',
    t('Are you sure want to remove this bookmark?'),
    'Yes',
    'No'
  );

  return $form;
}

/**
 * Remove bookmark
 *
 */
function remove_confirmation_form_submit($form, &$form_state) {
  global $user;
  if ($form_state['values']['confirm']) {
    $bid = $form_state['values']['bid'];
    db_query("DELETE FROM {bookmark} WHERE id = %d", $bid);
     //clear the cache
    cache_clear_all("bookmark_listing:uid:" . $user->uid . ":", "cache_eb", TRUE);
    cache_clear_all("bookmark_basket:uid:" . $user->uid . ":", "cache_eb", TRUE);
    // for mobile clear cache
    cache_clear_all("bookmark_mobile:uid:" . $user->uid . ":", "cache_eb", TRUE);
  }
  /* Redirect to which page it comes from */
  //drupal_goto("bridge/mybookmarks");
  drupal_set_message('The Bookmark has been Removed.');
}


/**
 * Function For Bookmarks Statistics Listing Page - only for admin
 *
 */
function bookmarks_statistcis_page() {
  //make the table having sortable headers
  $headers = array(
    array('data' => t('Asset/Link'), 'field' => 'asset'),
    array('data' => t('Teacher Bookmarks'), 'field' => 'teachers'),
    array('data' => t('Student Bookmarks'), 'field' => 'students'),
    array('data' => t('Total Bookmarks'), 'field' => 'cnt', 'sort' => 'desc'),
  );
  $tablesort = tablesort_sql($headers);

  //get the results - asset and count of bookmarks by teacher and students
  //to use multiple count in a single table - sigle query - we can use SUM function
  $sql = "SELECT
          asset, title, type, SUM(if(rid=3,1,0)) AS teachers, SUM(if(rid=4,1,0)) AS students, COUNT(*) AS cnt
          FROM {bookmark}
          GROUP BY asset";

  //making the page with pager
  $limit = 10;
  $countquery = "SELECT COUNT(DISTINCT(asset)) FROM {bookmark}";
  $result = pager_query($sql . $tablesort, $limit, 0 , $countquery);

  $rows = array();
  while ($row = db_fetch_object($result) ) {
    if (function_exists("drag_drop_make_link")) {
      $rows[] = array(
        'data' => array(
          array('data' => drag_drop_make_link($row->asset, check_plain($row->title), $row->type)),
          array('data' => $row->teachers),
          array('data' => $row->students),
          array('data' => $row->cnt),
        )
      );
    }
  }

  $output .= theme('table', $headers, $rows);
  $output .= theme('pager', NULL, $limit, 0);

  return $output;
}

/**
 *Building the block form
 *
 */
function bookmark_block_form($form_state) {
  if (function_exists("jquery_ui_add")) {
    jquery_ui_add(array('ui.widget', 'ui.mouse', 'ui.draggable', 'ui.droppable', 'ui.sortable'));
  }
  drupal_add_js(drupal_get_path('module', 'bookmark') . '/bookmark_block.js');
  drupal_add_css(drupal_get_path('module', 'bookmark') . '/bookmark.css');

  $form = array();
  $form['#attributes'] = array('style' => 'display: none');
  $form['bm-content'] = array(
    //'#type' => 'submit',
    '#type' => 'markup',
    '#value' => '<div id="bm-block-content">' . bookmark_block_default_content() .'</div>',
  );

  return $form;
}



function bookmark_block_default_content() {
  global $user;
  $uid = $user->uid;
  $limit = 5;
  // this condition is executed when bookmark listing page
  //if ($_GET['bookmark_basket']) {
  //  return NULL;
  //}
  
  
  $bookmark_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, BOOKMARK_BASKET_PAGER_ID + 1, 0));
  $cache_ouput = cache_get("bookmark_basket:uid:" . $user->uid . ":page:" . $bookmark_page, "cache_eb");
  if ($cache_ouput->data) {
    return $cache_ouput->data;
  }
  else  {
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
    
    $total_count = "SELECT COUNT(*) FROM {bookmark} WHERE uid = %d";
    $result = pager_query("SELECT * FROM {bookmark} WHERE uid = %d ORDER BY timestamp DESC", $limit, BOOKMARK_BASKET_PAGER_ID, $total_count, $uid);
    $items = array();
    while ($rows = db_fetch_object($result)) {
      if (function_exists("drag_drop_make_link")) {
        $drag_class = "bm-links";
        if ($playlist_count == 0 || !$drop_tooltip) {
          $drag_class = NULL;
        }
        $items[] = drag_drop_make_link_left_block($rows->asset, truncate_utf8($rows->title, 26, TRUE, TRUE), $rows->type, $rows->description, $rows->title, $drag_class, TRUE);
      }
    }

    //If no bookmarks - nothing to do more
    if (!count($items)) {
      $output =  "<p>You have no bookmarks.</p>";
    }
    else {
      $output = theme('item_list', $items);
      $pager = theme('pager', NULL, $limit, BOOKMARK_BASKET_PAGER_ID);
    }
    //SET the bookmark block cache
    cache_set("bookmark_basket:uid:" . $user->uid . ":page:" . $bookmark_page, $output . $pager, "cache_eb");

    return $output . $pager;
  }
}

/**
 * Check the bookmark table if a particular node id has been
 * bookmarked by user id.
 * Returns bookmark ID if exists.
 * Null if there is no Bookmark.
 */

function check_bookmark($asset, $uid = 0) {
  if ($uid == 0) {
    //if second argument is missing then the first argument is bookmark id - here checking table using bookmark id
    // @todo delete: need to check & remove the same.
    $result = db_query("SELECT id from {bookmark} where id = %d", $asset);
  }
  else {
    //if 2 arguments are passed then checking table using asset and user id
    $result = db_query("SELECT id from {bookmark} where asset = '%s' AND uid = %d", $asset, $uid);
  }
  $bookmark = db_fetch_array($result);

  //If exist return the id of the bookmark, else return 0
  $bid = 0;
  if (db_affected_rows())
    $bid = $bookmark['id'];
  return $bid;
}



/**
 * Function to determine bookmark link near any node/external link
 * if not exist - returning bookmark this link
 * for internal links bookmark_this_link($asset, $type)
 * asset: node_id, $type: node_type
 * for external bookmark_this_link($node_nid, $type, $title, $desc)
 * $asset: url, $type: google/federated, $title: title of the url, $des: description
 * @todo change: use varibale title & link_title, construct link at the end.
 */

function bookmark_this_link($node_nid, $type, $title = NULL, $desc = NULL, $text = FALSE) {
  global $user;
  if(is_numeric($node_nid)) {
   $alt = db_result(db_query("SELECT `title` FROM node WHERE `nid` = %d", array($node_nid)));
  }
  else {
    $alt = $title;
  }
  
  if((variable_get('bookmark_'. $type, 0) == 1 || $type == "google" || $type == "federated") && user_access("access bookmark")) {
    $uid = $user->uid;
    $query = NULL;
    if ($bid = check_bookmark($node_nid, $uid)) {
      //Already exist - return remove bookmark link
      if($text) {
        $link_title = 'Bookmarked';
        $href_link = "bookmark/remove/$bid/bookmark";
      }
      else{
        $link_title = theme_image(drupal_get_path('theme', 'educationhub') . "/images/icons/bookmarked_icon.png", 'Remove Bookmark for ' . $alt, 'Remove Bookmark');
        $href_link = "bookmark/remove/$bid";
      }
      $title = 'Remove Bookmark';
    }
    else {
      if($text) {
        $link_title = 'Bookmark';
        $href_link = "bookmark/add/$node_nid/Bookmark";
      }
      else {
        $link_title = theme_image(drupal_get_path('theme', 'educationhub') . "/images/icons/bookmark_icon.png", "Add Bookmark for " . $alt, "Add Bookmark");
        $href_link = "bookmark/add/$node_nid";
      }

      if ($type == "google" || $type == "federated") {
        //for google and federated type
        $href_link = "bookmark/add/external";
        $query = "link=$node_nid&title=" . rawurlencode(strip_tags($title)) . "&desc=" . rawurlencode(strip_tags($desc)) . "&type=$type";
        $title = 'Bookmark this';
      }
      else {
        $title = 'Bookmark this';
        //For internal links
        //$href_link = "bookmark/add/$node_nid";
      }
    }
    $link = l($link_title,  $href_link,
                  array(
                    'attributes' => array(
                      'class' => 'ajaxified',
                      'title' => $title
                    ),
                    'query' => $query,
                    'html' => TRUE
                  )
                  );
    $node_nid = null;
    return $link;
  }
  else {
    $node_nid = null;
    return NULL;
  }
}

/**
 *save the current page url in session for later use
 *
 */
function set_session_url() {
  global $base_url;
  $_SESSION['pre_url'] = $base_url . request_uri();
}
/**
 *get the page url saved in the session - clear the session variable after getting
 *
 */
function get_session_url() {
  $saved_url = $_SESSION['pre_url'];
  unset($_SESSION['pre_url']);

  return $saved_url;
}



/**
 *Load the data for a single bookmark
 *
 */
function bookmark_load($id) {
  $bookmark = db_fetch_object(db_query("SELECT * FROM {bookmark} WHERE id = %d", $id));
  return empty($bookmark) ? FALSE : $bookmark;
}

/**
 * Bookmark basket block pager in ajax load.
 *
 */
function bookmark_block_ajax() {
  print_r(bookmark_block_default_content());
  exit;
}
/**
 * Bookmark listing page pager in ajax load.
 *
 */
function bookmarks_listing_ajax() {
  $_GET['q'] = 'bridge/mybookmarks';
  print_r(bookmarks_listing());
  exit;
}