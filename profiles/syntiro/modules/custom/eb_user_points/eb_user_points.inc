<?php

/**
 * @file
 */
 
/*
 * Check points to GIVE or NOT
 * @param $nodetype  : required
 * @param $limit  : required
 * @param $time_stamp  : required
 * @param $waiting_period  : required
 * @param $comment_flag  : [optional]  if its 0 then its node. if it is 1 then its comment
 * @return
 *     TRUE OR FALSE
 */
function eb_check_points($nodetype, $limit, $time_stamp, $waiting_period = 1, $comment_flag = 0, $author = 1) {
  global $user; 
  $waiting_period = $waiting_period * 3600;
  $count = db_result(db_query('SELECT count(id) as count FROM {eb_user_points} WHERE uid = %d AND type = "%s" AND flag = %d AND author = %d', $user->uid, $nodetype, $comment_flag, $author)); 
  if ($count >= $limit) {
    $diff = eb_check_point_check_timeout($user->uid, $nodetype, $time_stamp,$waiting_period, $comment_flag, $author);
    if ($diff < $waiting_period) {
      return FALSE;
    }
    else {
      return TRUE;
    } 
  }
  else {
    if (is_numeric($count) && $count) {
      eb_check_point_check_timeout($user->uid, $nodetype, $time_stamp, $waiting_period, $comment_flag, $author);     
    }
    return TRUE;
  } 
}


/*
 * Check points to GIVE or NOT
 * This is not a direct function
 * @param $uid  : required
 * @param $nodetype  : required
 * @param $time_stamp  : required
 * @param $waiting_period  : required
 * @param $comment_flag  : [optional]  if its 0 then its node. if it is 1 then its comment
 * @return
 *     Integer : Time difference amount
 */
function eb_check_point_check_timeout($uid, $nodetype, $time_stamp, $waiting_period, $comment_flag, $author = 1) {
  $first_timestamp = db_result(db_query('SELECT timestamp FROM {eb_user_points} WHERE uid = %d AND type = "%s" AND flag = %d AND author = %d ORDER BY id LIMIT 0, 1', $uid, $nodetype, $comment_flag, $author));
    $diff = $time_stamp - $first_timestamp; 
    if ($diff < $waiting_period) {
      return $diff;
    }
    else    { 
      db_query('DELETE FROM {eb_user_points} WHERE uid = %d AND type = "%s" AND flag = %d AND author = %d', $uid, $nodetype, $comment_flag, $author);
      return $diff;
    }
}


/*
 * Check points to GIVE or NOT
 * @$param array : required
 * @return
 *     Success => TRUE else FALSE
 * ******************************    
 *   :: sample array for community and discussion ::
 *     $param[uid] = 1;
 *     $param[type] = node type;
 *     $param[nid] = node id;
 *     $param[author] = default = 1 OR assign 0;
 *     $param[timestamp] = node time stamp
 
 *   :: sample array for comment ::
 *     $param[uid] = 1;
 *     $param[type] = node type;
 *     $param[nid] = node id;
 *     $param[author] = default = 1 OR assign 0;
 *     $param[cid] = cid 
 *     $param[flag] = 1;
 *     $param[timestamp] = comment time stamp
 */
function eb_check_points_insert($param) {
  global $user;
  if (is_array($param) && count($param) > 0) {
    if (!isset($param['nid']) && !isset($param['type'])) {
      return FALSE;
    }
    else  if (!isset($param['nid']) && !isset($param['type']) && isset($param[cid]) && $param['flag'] == 1) {
      return FALSE;
    }
    if (!isset($param['uid'])) {
      $param['uid'] = $user->uid;  
    }
    drupal_write_record('eb_user_points', $param);
    return TRUE;
  }
  else {
    return FALSE;
  } 
}



/*
 * Check recommendations points to GIVE or NOT
 * @param $limit  : required
 * @param $time_stamp  : required
 * @param $waiting_period  : required
 * @return
 *     TRUE OR FALSE
 */
function eb_recomm_check_points($limit, $time_stamp, $waiting_period = 1) {
  global $user; 
  $waiting_period = $waiting_period * 3600;
  $count = db_result(db_query('SELECT count(id) as count FROM {eb_recomm_user_points} WHERE from_uid = %d', $user->uid)); 
  if ($count >= $limit) {
    $diff = eb_recomm_check_point_check_timeout($user->uid, $time_stamp,$waiting_period);
    if ($diff < $waiting_period) {
      return FALSE;
    }
    else {
      return TRUE;
    } 
  }
  else {
    if (is_numeric($count) && $count) {
      eb_recomm_check_point_check_timeout($user->uid, $time_stamp,$waiting_period);
    }
    return TRUE;
  } 
}

/*
 * Check recommendations points to GIVE or NOT
 * This is not a direct function
 * @param $uid  : required
 * @param $time_stamp  : required
 * @param $waiting_period  : required
 * @return
 *     Integer : Time difference amount
 */
function eb_recomm_check_point_check_timeout($uid, $time_stamp, $waiting_period) {
  $first_timestamp = db_result(db_query('SELECT timestamp FROM {eb_recomm_user_points} WHERE from_uid = %d ORDER BY id LIMIT 0, 1', $uid));
    $diff = $time_stamp - $first_timestamp; 
    if ($diff < $waiting_period) {
      return $diff;
    }
    else { 
      db_query('DELETE FROM {eb_recomm_user_points} WHERE from_uid = %d', $uid);
      return $diff;
    }
}

/*
 *  
 * This is not a direct function
 * @$param array : required
 * @return
 *     Success => TRUE else FALSE
 * ******************************    
 *   :: sample array for community and discussion ::
 *     $param[from_uid] = 1;
 *     $param[to_uid] = node type;
 *     $param[timestamp] = node time stamp 
 */
function eb_recomm_check_points_insert($param) {
  global $user;
  if (is_array($param) && count($param) > 0) {
    if (!isset($param['uid'])) {
      $param['from_uid'] = $user->uid;  
    }
    drupal_write_record('eb_recomm_user_points', $param);
    return TRUE;
  }
  else {
    return FALSE;
  } 
}