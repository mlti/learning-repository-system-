<?php
/*
 * Community interest group list page
 *
 * It list community list
 *
 *
 * @return
 *  It return HTML format community interest group teaser
 *
 * @see view_community_list()
 * @see _my_communities()
 **/
function communities_list($limit = 12, $mobile_flag = FALSE, $tcount_flag = FALSE) {
  global $user;
  if ($mobile_flag) {
    $mobile_community_page = isset($_GET['page']) ? $_GET['page'] : 0;
    // get recommend cache
    $cache_ouput = cache_get("mobile_community_list:uid:" . $user->uid . ":page:" . $mobile_community_page, "cache_eb");
    if  ($cache_ouput->data) {
      return $cache_ouput->data;
    }
    $page_result = _my_communities(0, $limit, $user->uid);
    if ($tcount_flag) {
      global $pager_total_items;
      $output['total_count'] = $pager_total_items;
    }
    if (db_affected_rows()) {
      $i = 1;
      while ($obj = db_fetch_object($page_result)) {
        if($obj->node_type == 'community_interest_group') {
          $output['fields'][$i]['title'] = truncate_utf8(check_plain($obj->node_title), 40, $wordsafe = FALSE, $dots = TRUE);
          $output['fields'][$i]['title_id'] = $obj->nid;
        }
        $member_plural = ($obj->member_count == 1)?' Member':' Members';
        $output['fields'][$i]['member_count'] = $obj->member_count . $member_plural;
        $discussion_plural = ($obj->post_count == 1)?' Discussion':' Discussions';
        $output['fields'][$i]['post_count'] = $obj->post_count. $discussion_plural;
        if($obj->post_count == 0){
        }
        else{
          $output['fields'][$i]['post_count_id'] = $obj->nid;
        }
        $output['fields'][$i]['body'] = check_plain($obj->og_og_description);
        $i++;
      }
    }
    else{
      $output['no_group_content'] = t("Yet you have Collaborations."); /*Null Content for My Communitites Page*/
    }
     //set the asset listing cache
    cache_set("mobile_community_list:uid:" . $user->uid . ":page:" . $mobile_community_page, $output, "cache_eb"); 
    return $output;
  }
  else {
    $community_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, COMMUNITY_LISTING_PAGER_ID + 1, 0));
    // get recommend cache
    $cache_ouput = cache_get("community_listing:uid:" . $user->uid . ":page:" . $community_page, "cache_eb");
    drupal_set_title('Communities');
    drupal_add_js(drupal_get_path('module', 'eb_group') . "/js/eb_group.js");
    if  ($cache_ouput->data) {
      return $cache_ouput->data;
    }
    // Get Community interest group list from the query
    $communities = _my_communities(0, $limit, 0, COMMUNITY_LISTING_PAGER_ID);
    if (db_affected_rows()) {
      $i = 1;
      while ($obj = db_fetch_object($communities)) {
        $output['fields'][$i]['title'] = l(truncate_utf8($obj->node_title, 20, $wordsafe = FALSE, $dots = TRUE), 'node/'.$obj->nid);
        if(!($i % 3)) {
          $output['fields'][$i]['class'] = ' pad-class';
        }
        $i++;
      }
    }
    else {
      $output['no_group_content'] = t("You are not a member of any Community!"); /*Null Content for My Communitites Page*/
    }
    $output['top_image']= theme_image(drupal_get_path('theme', 'educationhub') . "/images/welcome.png", "Welcome to learning Communities", NULL);
    $output['pager'] = theme('pager', NULL, $limit, COMMUNITY_LISTING_PAGER_ID);
    $results = theme('view_community_list', $output);
    //set the asset listing cache
    cache_set("community_listing:uid:" . $user->uid . ":page:" . $community_page, $results, "cache_eb"); 
    return $results;
  }
}

/*
 * It displays discussion list page
 *
 * It list discussion teaser list
 *
 *
 * @return
 *  It return HTML format discussion teaser
 *
 * @see view_discussion_custom()
 *
 **/
function recentdiscussion_view() {
  drupal_add_js(drupal_get_path('module', 'recommend') . '/recommend.js');
  drupal_add_js(drupal_get_path('module', 'bookmark') . '/bookmark.js');

  // @todo change both count and Query to support functions
  global $user;

  $discussions = _my_discussions();
  $i = 1;
  if (db_affected_rows()) {
    while ($obj = db_fetch_object($discussions)) {
      /*Get Title of Course group*/
      $group_load = node_load($obj->og_ancestry_nid);
      $cg_link = array_shift($group_load->og_groups);
      $cg_title = array_shift($group_load->og_groups_both);

      $curr_obj = db_fetch_object(db_query("SELECT o.nid, n.type FROM {node} n INNER JOIN {og_ancestry} o ON o.nid = n.nid  WHERE n.type = '%s' AND o.group_nid = %d", 'curriculum', $cg_link));

      $output['fields'][$i]['title'] = l(truncate_utf8($obj->node_title, 40, $wordsafe = FALSE, $dots = TRUE), 'node/' . $obj->nid);
      $output['fields'][$i]['course_group'] = l($cg_title, 'node/' . $cg_link );

      $output['fields'][$i]['body'] = truncate_utf8($obj->node_revisions_teaser, 300, $wordsafe = TRUE, $dots = FALSE);
      // Comments Plural we used 's' for more than one other wise it should be comment
      // Check if comment is enabled for each node
      if ($obj->comment != COMMENT_NODE_DISABLED) {
        if($obj->node_comment_statistics_comment_count == 0) {
          $comment_value = 'Be the first to comment!';
        }
        else if($obj->node_comment_statistics_comment_count == 1) {
          $comment_value=  $obj->node_comment_statistics_comment_count.' comment';
        }
        else {
          $comment_value = $obj->node_comment_statistics_comment_count.' comments';
        }
        $output['fields'][$i]['comment_plural'] = l($comment_value, 'node/' . $obj->nid, array('html'=>true));
      }
      $output['fields'][$i]['bookmark'] = bookmark_this_link($obj->nid, $obj->node_type, $obj->node_title, $obj->node_revisions_teaser);
      $output['fields'][$i]['recommend']=l(theme_image(drupal_get_path('theme', 'edubridge_fluid') . "/images/recommend.png", NULL, 'Recommend this'), "recommend/" . $obj->nid, array('html' => TRUE));

      /*Check whether the discussion is already visited or not..*/
      $visited = db_result(db_query("SELECT dis_id FROM {eb_group_discussion_statistics} WHERE uid = %d AND dis_nid = %d", $user->uid, $obj->nid));
      if($visited){
        $output['fields'][$i]['visited'] = ' selected-author';
      }
      $i++;
    }
  }
  else {
    $output['no_comment_content'] = t("There are no Discussions.");
  }

  $output['pager'] = theme('pager', NULL, $limit, 0);
  $results = theme('view_discussion_custom', $output);

  return $results;
}

/**
 * It display external website http://openstudy.com/ using IFrame
 *
 * @return
 *  It return IFrame with that specific website
 *
 */
function globalstudygroup_view() {

  $heading = NULL;

  return '<div class="curriculum-info">' . $heading . '<iframe height="650px" width="99%"  name="googleSearchFrame" src="http://openstudy.com/" ></iframe></div>';
}

/**
 * support dunction for count_query and pager_query for communities
 * Adding the third argument $uid for Mobile access.
 *
 * @param $bridge_limit
 *  (optional) It contains 0 or 1
 * @param $limit
 *  It contains query limit value Default is to 10
 * @param $uid
 *  It contains user id. Default is 0
 *
 * @return
 *  It contains query result value
 *
 */
function _my_communities($bridge_limit = 0, $limit = 10, $uid = 0, $pager_id = 0) {
  global $user;
  if ($bridge_limit != 0) {
    $page_result = db_query("SELECT DISTINCT node.nid AS nid,
                      node.title AS node_title, node.type AS node_type, og_uid.is_admin AS is_admin,
                      (SELECT COUNT(*) FROM {og_uid} ou INNER JOIN {users} u ON ou.uid = u.uid WHERE ou.nid = og.nid AND
                      u.status > 0 AND ou.is_active >= 1 AND ou.is_admin >= 0 ) AS member_count,
                      (SELECT COUNT(n.nid) FROM {node} n INNER JOIN {og_ancestry} oga ON n.nid = oga.nid WHERE n.status = 1
                      AND oga.group_nid = og.nid) AS post_count,
                      og.og_description AS og_og_description,
                      node.changed AS node_changed
                    FROM {node} node
                    LEFT JOIN {og_uid} og_uid ON node.nid = og_uid.nid
                    LEFT JOIN {og} og ON node.nid = og.nid
                    WHERE (node.type in ('community_interest_group')) AND (og_uid.uid = %d) AND (node.status <> 0)
                      ORDER BY node_changed DESC LIMIT 0, %d", $user->uid, $bridge_limit);
  }
  else {
/*Built Count Query for passing in the Pager Query*/
    $count_query = "SELECT COUNT(DISTINCT(node.nid)) AS nid
                    FROM {node} node
                    LEFT JOIN {og_uid} og_uid ON node.nid = og_uid.nid
                    LEFT JOIN {node} node_og_uid ON og_uid.nid = node_og_uid.nid
                    LEFT JOIN {og} og ON node.nid = og.nid
                    WHERE node.type in ('community_interest_group') AND (og_uid.uid = %d)";

    //Check whether the function request is comes from Mobile apps or from site.
    if($uid != 0) {
      /*Query For get the Listing Communities Associated with the Current User for Mobile Apps.*/
      $page_result = pager_query("SELECT DISTINCT node.nid AS nid,
                                  node.title AS node_title, node.type AS node_type, og_uid.is_admin AS is_admin,
                                  (SELECT COUNT(*) FROM {og_uid} ou INNER JOIN {users} u ON ou.uid = u.uid WHERE ou.nid = og.nid
                                  AND u.status > 0 AND ou.is_active >= 1 AND ou.is_admin >= 0 ) AS member_count,
                                  (SELECT COUNT(n.nid) FROM {node} n INNER JOIN {og_ancestry} oga ON n.nid = oga.nid WHERE
                                  n.status = 1 AND oga.group_nid = og.nid AND n.type = 'discussion') AS post_count,
                                  og.og_description AS og_og_description,
                                  node.changed AS node_changed
                                FROM {node} node
                                LEFT JOIN {og_uid} og_uid ON node.nid = og_uid.nid
                                LEFT JOIN {og} og ON node.nid = og.nid
                                WHERE (node.type in ('community_interest_group')) AND (og_uid.uid = %d) AND (node.status <> 0)
                                  ORDER BY node_changed DESC", $limit, $pager_id, $count_query, $uid);
    }
    else{
      /*Query For get the Listing Communities Associated with the Current User*/
      $page_result = pager_query("SELECT DISTINCT node.nid AS nid,
                              node.title AS node_title, node.type AS node_type, og_uid.is_admin AS is_admin,
                              (SELECT COUNT(*) FROM {og_uid} ou INNER JOIN {users} u ON ou.uid = u.uid WHERE ou.nid = og.nid AND
                              u.status > 0 AND ou.is_active >= 1 AND ou.is_admin >= 0 ) AS member_count,
                              (SELECT COUNT(n.nid) FROM {node} n INNER JOIN {og_ancestry} oga ON n.nid = oga.nid WHERE
                              n.status = 1 AND oga.group_nid = og.nid) AS post_count,
                              og.og_description AS og_og_description,
                              node.changed AS node_changed
                            FROM {node} node
                            LEFT JOIN {og_uid} og_uid ON node.nid = og_uid.nid
                            LEFT JOIN {og} og ON node.nid = og.nid
                            WHERE (node.type in ('community_interest_group')) AND (og_uid.uid = %d) AND (node.status <> 0)
                              ORDER BY node_changed DESC", $limit, $pager_id, $count_query, $user->uid);
    }
  }
  return $page_result;
}
/**
 * support function for page_result for recent discussion for both disuccion and bridge module
 *
 *
 * @param $bridge_limit
 *  (optional) It contains 0 or 1
 * @param $limit
 *  It contains query limit value Default is to 10
 * @param $uid
 *  It contains user id. Default is 0
 * @param $group_id
 *  It contains Group node id. Default is 0
 *
 *
 * @return
 *  It contains query result value
 *
 */
function _my_discussions($bridge_limit = 0 , $limit = 10, $uid = 0, $group_id = 0) {
  global $user;

  /*Query for getting Groups nid which are associated to the Logged In user.*/
  if($uid != 0) {
    $res = db_query("SELECT DISTINCT n.nid FROM {node} n INNER JOIN {og_uid} ou ON ou.nid = n.nid WHERE ou.uid = %d AND n.type in ('community_interest_group') AND status = %d", $uid, 1);
  }
  else {
    $res = db_query("SELECT DISTINCT n.nid FROM {node} n INNER JOIN {og_uid} ou ON ou.nid = n.nid WHERE ou.uid = %d AND n.type in ('community_interest_group') AND status = %d", $user->uid, 1);
  }
  if (db_affected_rows()) {
    while ($row = db_fetch_object($res)) {
      $nids_arr[] = $row->nid;
    }
  }
  //Check whether the User didn't belongs to any Community groups.
  if(isset($nids_arr)){
    $og_group = implode(',', $nids_arr);

    if($bridge_limit != 0){
      $page_result = db_query("SELECT node.nid AS nid,
                              users.picture AS users_picture,
                              users.uid AS users_uid,
                              users.name AS users_name,
                              users.mail AS users_mail,
                              node.type AS node_type,
                              node.title AS node_title,
                              node_revisions.teaser AS node_revisions_teaser,
                              node_revisions.format AS node_revisions_format,
                              node_comment_statistics.comment_count AS node_comment_statistics_comment_count,
                              og_ancestry.nid AS og_ancestry_nid,
                              node.changed AS node_changed, node.comment as comment
                            FROM {node} node
                            LEFT JOIN {og_uid} og_uid ON node.nid = og_uid.nid
                            LEFT JOIN {node} node_og_uid ON og_uid.nid = node_og_uid.nid
                            LEFT JOIN {og_ancestry} og_ancestry ON node.nid = og_ancestry.nid
                            INNER JOIN {users} users ON node.uid = users.uid
                            LEFT JOIN {node_revisions} node_revisions ON node.vid = node_revisions.vid
                            INNER JOIN {node_comment_statistics} node_comment_statistics ON node.nid = node_comment_statistics.nid
                            WHERE (node.type in ('discussion')) AND (og_ancestry.group_nid IN (%s))
                              ORDER BY node_changed DESC LIMIT 0, %d", $og_group, $bridge_limit);
    }
    elseif($group_id != 0) {//Access this function from mobile apps when we indicated the Whole group id or single group id.
      $page_result = db_query("SELECT node.nid AS nid,
                              users.picture AS users_picture,
                              users.uid AS users_uid,
                              users.name AS users_name,
                              users.mail AS users_mail,
                              node.type AS node_type,
                              node.title AS node_title,
                              node_revisions.teaser AS node_revisions_teaser,
                              node_revisions.format AS node_revisions_format,
                              node_comment_statistics.comment_count AS node_comment_statistics_comment_count,
                              og_ancestry.nid AS og_ancestry_nid,
                              node.changed AS node_changed, node.comment as comment
                            FROM {node} node
                            LEFT JOIN {og_uid} og_uid ON node.nid = og_uid.nid
                            LEFT JOIN {node} node_og_uid ON og_uid.nid = node_og_uid.nid
                            LEFT JOIN {og_ancestry} og_ancestry ON node.nid = og_ancestry.nid
                            INNER JOIN {users} users ON node.uid = users.uid
                            LEFT JOIN {node_revisions} node_revisions ON node.vid = node_revisions.vid
                            INNER JOIN {node_comment_statistics} node_comment_statistics ON node.nid = node_comment_statistics.nid
                            WHERE (node.type in ('discussion')) AND (og_ancestry.group_nid IN (%s))
                              ORDER BY node_changed DESC", $group_id);
    }
    else {
      if ($uid != 0) {
        $page_result = db_query("SELECT node.nid AS nid,
                                  users.picture AS users_picture,
                                  users.uid AS users_uid,
                                  users.name AS users_name,
                                  users.mail AS users_mail,
                                  node.type AS node_type,
                                  node.title AS node_title,
                                  node_revisions.teaser AS node_revisions_teaser,
                                  node_revisions.format AS node_revisions_format,
                                  node_comment_statistics.comment_count AS node_comment_statistics_comment_count,
                                  og_ancestry.nid AS og_ancestry_nid,
                                  node.changed AS node_changed, node.comment as comment
                                FROM {node} node
                                LEFT JOIN {og_uid} og_uid ON node.nid = og_uid.nid
                                LEFT JOIN {node} node_og_uid ON og_uid.nid = node_og_uid.nid
                                LEFT JOIN {og_ancestry} og_ancestry ON node.nid = og_ancestry.nid
                                INNER JOIN {users} users ON node.uid = users.uid
                                LEFT JOIN {node_revisions} node_revisions ON node.vid = node_revisions.vid
                                INNER JOIN {node_comment_statistics} node_comment_statistics ON
                                node.nid = node_comment_statistics.nid
                                WHERE (node.type in ('discussion')) AND (og_ancestry.group_nid IN (%s))
                                  ORDER BY node_changed DESC", $og_group);

      }
      else {
        drupal_set_title('Collaborations');
        $page_result = pager_query("SELECT node.nid AS nid,
                                    users.picture AS users_picture,
                                    users.uid AS users_uid,
                                    users.name AS users_name,
                                    users.mail AS users_mail,
                                    node.type AS node_type,
                                    node.title AS node_title,
                                    node_revisions.teaser AS node_revisions_teaser,
                                    node_revisions.format AS node_revisions_format,
                                    node_comment_statistics.comment_count AS node_comment_statistics_comment_count,
                                    og_ancestry.nid AS og_ancestry_nid,
                                    node.changed AS node_changed, node.comment as comment
                                  FROM {node} node
                                  LEFT JOIN {og_uid} og_uid ON node.nid = og_uid.nid
                                  LEFT JOIN {node} node_og_uid ON og_uid.nid = node_og_uid.nid
                                  LEFT JOIN {og_ancestry} og_ancestry ON node.nid = og_ancestry.nid
                                  INNER JOIN {users} users ON node.uid = users.uid
                                  LEFT JOIN {node_revisions} node_revisions ON node.vid = node_revisions.vid
                                  INNER JOIN {node_comment_statistics} node_comment_statistics ON
                                  node.nid = node_comment_statistics.nid
                                  WHERE (node.type in ('discussion')) AND (og_ancestry.group_nid IN (%s))
                                    ORDER BY node_changed DESC", $limit, 0, NULL, $og_group);
      }
    }
  }
  return $page_result;
}
