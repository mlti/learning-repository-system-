<?php

// $Id: eb_school.inc, 2011/12/26 Exp $

/**
* @file
* Handling forms for eb_school module
*/
/**
 * Form constructor for the teacher-asset-mapping.
 *
 *
 * @see map_teacher_edubridge_asset_form_submit()
 * @ingroup forms
 */
function map_teacher_edubridge_asset_form($form_state) {
  $form = array();
  drupal_set_title ("Map Teachers to Edubridge Assets");
  // Get Last time Value
  $last_timestamp = db_result(db_query("SELECT start_timestamp FROM {school_log} WHERE activity = 1 ORDER BY id desc LIMIT 0, 1"));
  $last_timestamp = $last_timestamp?$last_timestamp:time();
  $form['result'] = array(
    '#type' => 'markup',
    '#value' => format_date($last_timestamp) . ' updated assets since last synch',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update Now'),
    '#weight' => 10,
  );
  return $form;
}

/**
 * Form submission handler for map_teacher_edubridge_asset_form().
 *
 * @see map_teacher_edubridge_asset_form()
 */
function map_teacher_edubridge_asset_form_submit($form, &$form_state) {
  global $user;
 
  // Get list of Edubridge user only on teacher
  $edubridge_user_query = db_query("SELECT nid FROM {content_type_profile} WHERE field_profile_institution_value='EduBridge'");
  $edubridge_user_nid = NULL;
  $edubridge_user_count = NULL;
  $edubridge_user_count = db_affected_rows();
  if ($edubridge_user_count) {
    $i = 1;
    // Get the user list based on teacher
    while($edubridge_user_query_row = db_fetch_object($edubridge_user_query)) {
      if ($edubridge_user_count == $i) {
        // Get user id based on node id
        $edubridge_user_nid .= db_result(db_query("SELECT uid FROM {node} WHERE nid = %d", $edubridge_user_query_row->nid ));
      }
      else {
        // Get user id based on node id
        $edubridge_user_nid .= db_result(db_query("SELECT uid FROM {node} WHERE nid = %d", $edubridge_user_query_row->nid )) . ', ';
      }
      $i++;
    }
  }
  $i = 0;
  // Get list of user only on Teacher 
  $teachers = db_query("SELECT U.uid FROM {users} U LEFT JOIN {users_roles} R ON U.uid=R.uid WHERE R.rid=%d AND U.uid !=1", TEACHER_ROLE);
  while($row = db_fetch_object($teachers)) {
    $user_subject_first = '';
    $user_subject_second = '';
    // Get the user profile 
    $user_details = content_profile_load('profile', $row->uid);
    // load the taxonomy
    foreach ($user_details->taxonomy as $key1 => $value1) {
      if ($value1->vid == NEW_TAXONOMY_SUBJECT) {
        $j = 0;
        // For first value in an field has been separated by class keyword
        $subject_class = explode("class", strtolower($value1->name));
        $user_subject_first = $subject_class[0];
        $user_subject_second = '';
        foreach($subject_class as $key2 => $value2) {
          if ($key2 != 0) {
            $user_subject_second .= $value2 . ' ';
          }
          else {
            $user_subject_second .=  'class';
          }
        }
        // Get first taxonomy term id
        $term_first = get_taxonomy_tid($user_subject_first, NEW_TAXONOMY_SUBJECT);
        // Get Second taxonomy term id
        $term_second = get_taxonomy_tid($user_subject_second, NEW_TAXONOMY_ACADEMICLEVEL);

        // Get Last time updated timestamp
        $last_timestamp = db_result(db_query("SELECT start_timestamp FROM {school_log} WHERE activity = 1 ORDER BY id desc LIMIT 0, 1"));
        $extra_cond = NULL;
        // Check if timestamp does not have value
        if (!$last_timestamp) {
          $extra_cond = ' AND N.changed >= %d';
        }
        // Get node id based on first term data
        $assets = db_query("SELECT N.nid FROM {node} N  LEFT JOIN {term_node} TN ON TN.vid = N.vid WHERE TN.tid = %d  AND N.uid IN (" . $edubridge_user_nid . ") AND N.type='asset' AND N.status = 1 $extra_cond  GROUP BY nid", $term_first, $last_timestamp);
        if (db_affected_rows()) {
          while ($row2 = db_fetch_object($assets)) {
            // Get node id based on second term data
            $assets2 = db_query("SELECT N.nid FROM {node} N  LEFT JOIN {term_node} TN ON TN.vid = N.vid  WHERE TN.tid = %d  AND N.nid=%d GROUP BY nid", $term_second, $row2->nid);
            if (db_affected_rows()) {
              while ($row3 = db_fetch_object($assets2)) {
                $flag = 0;$flag2 = 0;
                $node = NULL;
                $node = node_load($row3->nid, NULL, TRUE);
                // Check if the user is co author
                if ($node->field_coauthor) {
                  foreach ($node->field_coauthor as $k =>$v) {
                    if ($v['uid'] == $user_details->uid) {
                      $flag = 1;
                    }
                    $jk++;
                  }
                }
                // Check if the user is author
                if ($node->uid == $user_details->uid) {
                  $flag2 = 1; 
                }
                // Check if ther user is not a co author and author
                if ($flag == 0 && $flag2 == 0) {
                  $node->field_coauthor[] = array('uid' => $user_details->uid);
                  node_save($node);
                  watchdog("teacher-asset-mapping", $user_details->name . 'is assigned as coauthor to ' . $row2->title . ', by ' . $user->uid);
                  $j++;$i++;
                }
              }
            }
            
          }
        }
        if ($j) {
          // Set the message count
          drupal_set_message($j . ' Asset Added to ' . $user_details->name);
        }
      }
    }
  }
  // check if co author is added then make the entry in school_log table
  if ($i > 0) {
    db_query("INSERT INTO {school_log} SET activity = %d, uid = %d, start_timestamp = %d", 1, $user->uid, time());
  }
  else {
    // Set the message 
    drupal_set_message('No assets found');
  }
}


/**
 * Form constructor for the asset export .
 *
 *
 * @see node_export_asset_form_submit()
 * @ingroup forms
 */
function node_export_asset_form($form_state) {
  $form = array();
  drupal_set_title ("Export Asset");
  // Get Last time Value
  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('User Name'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
    '#weight' => 10,
  );
  return $form;
}
/**
 * Form validate handler for node_export_asset_form().
 *
 * @see node_export_asset_form()
 */
function node_export_asset_form_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#post']['username']) {
    $user_name = explode(", ", $form_state['clicked_button']['#post']['username']);
    foreach($user_name as $key => $value) { 
      // Get list of user only on Teacher
      $user_name = NULL;
      $user_name = db_result(db_query("SELECT uid FROM {users} WHERE name='%s'", $value));
      if (!$user_name) {
        form_set_error('username', t('Please Enter Valid username.'));
      }
    }
  }
  else {
    form_set_error('username', t('Please enter the username.'));
  }
}
/**
 * Form submission handler for node_export_asset_form().
 *
 * @see node_export_asset_form()
 * @see node_export_node_bulk().
 */
function node_export_asset_form_submit($form, &$form_state) {
  global $user;
  $export_new = ($form_state['clicked_button']['#value'] == 'Export For New Version')?TRUE:FALSE;
  $export_node = NULL;
  // Seperate username 
  $user_name = explode(", ", $form_state['clicked_button']['#post']['username']);
  // Check if user name is available
  if ($user_name) {
    foreach($user_name as $key => $value) { 
      // Get list of user only on Teacher 
      $query = db_query("SELECT nid FROM {node} WHERE uid=%d AND type='asset' AND status=1", db_result(db_query("SELECT uid FROM {users} WHERE name='%s'", $value)));
      if (db_affected_rows()) {
        while ($user_node = db_fetch_object($query)) {
          $export_node[] = $user_node->nid;
        }
      }
    }
  }
  // check node_export_node_bulk function and export node values to be set
  if (function_exists("node_export_node_bulk") && $export_node) {
    module_load_include('inc', 'eb_school', 'includes/eb_school_export_import');
    node_export_node_bulk_export_playlist($export_node, FALSE, NULL, $export_new, TRUE);
    //node_export_node_bulk($export_node);
  }
}

/**
 * Form constructor for the teacher-asset-mapping.
 *
 *
 * @see map_teacher_edubridge_asset_form_submit()
 * @ingroup forms
 */
function map_teacher_edubridge_playlist_form($form_state) {
  $form = array();
  drupal_set_title ("Map Teachers to Edubridge Assets");
  // Get Last time Value
  $last_timestamp = db_result(db_query("SELECT start_timestamp FROM {school_log} WHERE activity = 2 ORDER BY id desc LIMIT 0, 1"));
  $last_timestamp = $last_timestamp?$last_timestamp:time();
  $form['result'] = array(
    '#type' => 'markup',
    '#value' => format_date($last_timestamp) . ' updated playlist since last synch',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update Now'),
    '#weight' => 10,
  );
  return $form;
}

/**
 * Form submission handler for map_teacher_edubridge_asset_form().
 *
 * @see map_teacher_edubridge_asset_form()
 */
function map_teacher_edubridge_playlist_form_submit($form, &$form_state) {
  global $user;
 
  // Get list of Edubridge user only on teacher
  $edubridge_user_query = db_query("SELECT nid FROM {content_type_profile} WHERE field_profile_institution_value='EduBridge'");
  $edubridge_user_nid = NULL;
  $edubridge_user_count = NULL;
  $edubridge_user_count = db_affected_rows();
  if ($edubridge_user_count) {
    $i = 1;
    // Get the user list based on teacher
    while($edubridge_user_query_row = db_fetch_object($edubridge_user_query)) {
      if ($edubridge_user_count == $i) {
        // Get user id based on node id
        $edubridge_user_nid .= db_result(db_query("SELECT uid FROM {node} WHERE nid = %d", $edubridge_user_query_row->nid ));
      }
      else {
        // Get user id based on node id
        $edubridge_user_nid .= db_result(db_query("SELECT uid FROM {node} WHERE nid = %d", $edubridge_user_query_row->nid )) . ', ';
      }
      $i++;
    }
  }
  $i = 0;
  // Get list of user only on Teacher 
  $teachers = db_query("SELECT U.uid FROM {users} U LEFT JOIN {users_roles} R ON U.uid=R.uid WHERE R.rid=%d AND U.uid !=1", TEACHER_ROLE);
  while($row = db_fetch_object($teachers)) {
    $user_subject_first = '';
    $user_subject_second = '';
    // Get the user profile 
    $user_details = content_profile_load('profile', $row->uid);
    // load the taxonomy
    foreach ($user_details->taxonomy as $key1 => $value1) {
      if ($value1->vid == NEW_TAXONOMY_SUBJECT) {
        $j = 0;
        // For first value in an field has been separated by class keyword
        $subject_class = explode("class", strtolower($value1->name));
        $user_subject_first = $subject_class[0];
        $user_subject_second = '';
        foreach($subject_class as $key2 => $value2) {
          if ($key2 != 0) {
            $user_subject_second .= $value2 . ' ';
          }
          else {
            $user_subject_second .=  'class';
          }
        }
        // Get first taxonomy term id
        $term_first = get_taxonomy_tid($user_subject_first, NEW_TAXONOMY_SUBJECT);
        // Get Second taxonomy term id
        $term_second = get_taxonomy_tid($user_subject_second, NEW_TAXONOMY_ACADEMICLEVEL);

        // Get Last time updated timestamp
        $last_timestamp = db_result(db_query("SELECT start_timestamp FROM {school_log} WHERE activity = 2  ORDER BY id desc LIMIT 0, 1"));
        $extra_cond = NULL;
        // Check if timestamp does not have value
        if (!$last_timestamp) {
          $extra_cond = ' AND N.changed >= %d';
        }
        // Get node id based on first term data
        $assets = db_query("SELECT N.nid FROM {node} N  LEFT JOIN {term_node} TN ON TN.vid = N.vid WHERE TN.tid = %d  AND N.uid IN (" . $edubridge_user_nid . ") AND N.type='curriculum' AND N.status = 1 $extra_cond  GROUP BY nid", $term_first, $last_timestamp);
        if (db_affected_rows()) {
          while ($row2 = db_fetch_object($assets)) {
            // Get node id based on second term data
            $assets2 = db_query("SELECT N.nid FROM {node} N  LEFT JOIN {term_node} TN ON TN.vid = N.vid  WHERE TN.tid = %d  AND N.nid=%d GROUP BY nid", $term_second, $row2->nid);
            if (db_affected_rows()) {
              while ($row3 = db_fetch_object($assets2)) {
                $flag = 0;$flag2 = 0;
                $node = NULL;
                $node = node_load($row3->nid, NULL, TRUE);
                // Check if the user is co author
                if ($node->field_coauthor) {
                  foreach ($node->field_coauthor as $k =>$v) {
                    if ($v['uid'] == $user_details->uid) {
                      $flag = 1;
                    }
                    $jk++;
                  }
                }
                // Check if the user is author
                if ($node->uid == $user_details->uid) {
                  $flag2 = 1; 
                }
                // Check if ther user is not a co author and author
                if ($flag == 0 && $flag2 == 0) {
                  $node->field_coauthor[] = array('uid' => $user_details->uid);
                  node_save($node);
                  watchdog("teacher-playlist-mapping", $user_details->name . 'is assigned as coauthor to ' . $row2->title . ', by ' . $user->uid);
                  $j++;$i++;
                }
              }
            }
            
          }
        }
        if ($j) {
          // Set the message count
          drupal_set_message($j . ' Playlist Added to ' . $user_details->name);
        }
      }
    }
    
  }
  // check if co author is added then make the entry in school_log table
  if ($i > 0) {
    db_query("INSERT INTO {school_log} SET activity = %d, uid = %d, start_timestamp = %d", 2, $user->uid, time());
  }
  else {
    // Set the message 
    drupal_set_message('No Playlist found');
  }
}

