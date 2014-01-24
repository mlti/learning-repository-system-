<?php

// $Id: eb_school_export_import.inc, 2012/1/20 Exp $

/**
* @file
* Handling export and import for eb_school module
*/
/**
 * Form constructor for the Export playlist.
 *
 * @see export_playlist_form_validate()
 * @see export_playlist_form_submit()
 * @ingroup forms
 */
function export_playlist_form($form_state) {
  $form = array();
  // Get username
  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('User Name'),
  );
  // Academic level in taxonomy
  $form['academic_level'] = array(
    '#type' => 'textfield',
    '#title' => t('Academic Level'),
  );
  // subject in taxonomy
  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
  );
  $form['from'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'Y-m-d',
    '#title' => t('From Date'),
  );
  $form['to'] = array(
    '#type' => 'date_popup',
     '#date_format' => 'Y-m-d',
    '#title' => t('To Date'),
  );
  $form['submit_new'] = array(
    '#type' => 'submit',
    '#value' => t('Export For New Version'),
    '#weight' => 10,
  );
  $form['submit_old'] = array(
    '#type' => 'submit',
    '#value' => t('Export for Old Version'),
    '#weight' => 10,
  );
  return $form;
}

/**
 * Form validate handler for export_playlist_form().
 *
 */
function export_playlist_form_validate($form, &$form_state) {

  // check if entered user is valid
  if ($form_state['clicked_button']['#post']['username']) {
    $user_name = explode(", ", $form_state['clicked_button']['#post']['username']);
    foreach($user_name as $key => $value) { 
      // Get list of user only on Teacher
      $user_name = NULL;
      $user_name = db_result(db_query("SELECT uid FROM {users} WHERE name='%s'", $value));
      // check if not a valid user then throw the error message
      if (!$user_name) {
        form_set_error('username', t('Please Enter Valid username.'));
      }
      //
      $user_role = db_result(db_query("SELECT rid FROM {users_roles} WHERE uid=%d", $user_name));
      $result = db_result(db_query("SELECT perm FROM {permission} WHERE rid=%d", $user_role));
      // Set permission for edit own bead content to site admin
      $check = strpos($result, 'create curriculum content');
      if ($check != TRUE) {
        form_set_error('username', t($value . ' does not have playlist'));
      }
    }
  }
  else if($form_state['clicked_button']['#post']['academic_level'] == NULL && $form_state['clicked_button']['#post']['subject'] == NULL && $form_state['clicked_button']['#post']['username'] == NULL) {
    // Check all field are blank
    form_set_error('username', t('Please Enter the username.'));
  }
  
}
/**
 * Form submission handler for export_playlist_form().
 *
 * @see node_export_node_bulk_export_playlist().
 * @see get_taxonomy_tid().
 * @see node_title(). in eb_others_common.inc
 */
function export_playlist_form_submit($form, &$form_state) {
  global $user;
  $term_id = NULL;
  $export_new = ($form_state['clicked_button']['#value'] == 'Export For New Version')?TRUE:FALSE;
 
  // Get academic level list
  if ($form_state['clicked_button']['#value']['academic_level']) {
    $academic_level = explode(", ", $form_state['clicked_button']['#post']['academic_level']);
    foreach($academic_level as $key => $value) { 
      $term = NULL;
      // Get tid based on term value
      $term = get_taxonomy_tid($value, NEW_TAXONOMY_ACADEMICLEVEL);
      if ($term != NULL) {
        $term_id[] = $term;
      }
    }
  }
  // Get subject list
  if ($form_state['clicked_button']['#post']['subject']) {
    $subject = explode(", ", $form_state['clicked_button']['#post']['subject']);
    foreach($subject as $key => $value) { 
      $term = NULL;
       // Get tid based on term value
      $term = get_taxonomy_tid($value, NEW_TAXONOMY_SUBJECT);
      if ($term != NULL) {
        $term_id[] = $term;
      }
    }
  }
  // Get user name list
  if ($form_state['clicked_button']['#post']['username']) {
    $user_name = explode(", ", $form_state['clicked_button']['#post']['username']);
    foreach($user_name as $key => $value) { 
      $uid = NULL;
      $uid = db_result(db_query("SELECT uid FROM {users} WHERE name='%s'", $value));
      if ($uid) {
        $user_name_list[] = $uid;
      }
    }
  }
  $from_date = NULL;
  $from = NULL;
  // check if from date is given then add this condition to query
  if ($form_state['clicked_button']['#post']['from']['date']) {
    $from = strtotime($form_state['clicked_button']['#post']['from']['date'] . ' ' . date('h:i:s', time()));
    $from_date = $from? ' AND N.created >=%d ':NULL;
  }
  $to_date = NULL;
  $to = NULL;
  // check if to date is given then add this condition to query
  if ($form_state['clicked_button']['#post']['to']['date']) {
    $to = strtotime($form_state['clicked_button']['#post']['to']['date'] . ' ' . date('h:i:s', time()));
    $to_date = $to?' AND N.created >=%d ':NULL;
  }
  // Get user list
  $username = $user_name_list?implode(', ', $user_name_list):'';
  $username_include = $username?' N.uid IN (' . $username . ') AND': NULL;
  // get taxonomy term ids
  $extra_cond = $term_id ?' TN.tid IN (' . implode(', ', $term_id) . ') AND': NULL;
  // for playlist nid index value
  $i = 0;
  // For associated subtopic count 
  $k = 0;
  // for playlist count
  $playlist = 0;
  if ($extra_cond || $username_include || $from_date || $to_date) {
    // get playlist id
    $query = db_query("SELECT N.nid FROM node N  LEFT JOIN term_node TN ON TN.vid = N.vid WHERE $extra_cond $username_include  N.type='%s' AND N.status=1 $from_date $to_date GROUP BY N.nid", curriculum, $from, $to);
    if (db_affected_rows()) {
      while($row = db_fetch_object($query)) {
        $k = 0;
        // for external link count
        $external = 0;
        // for asset count
        $asset = 0;
        // for bead count
        $bead = 0;
        // for quiz count
        $quiz = 0;
        // assign playlist id
        $export_node[$i]['nid'] = $row->nid;
        // get playlist topics
        $topics = db_query('SELECT OGA.topic_title, OGA.weight, OGA.cid, OGA.topic_id FROM {curriculum_topics} OGA WHERE OGA.cid = %d', $row->nid);
        if (db_affected_rows()) {
          while($row2 = db_fetch_object($topics)) {
            // get playlist subtopics based on associated.
            $sub_topics = db_query('SELECT TA.topic_id, TA.id, TA.asset, TA.type, TA.title, TA.description, TA.weight FROM {curriculum_topics_assets} TA  WHERE TA.topic_id = %d', $row2->topic_id);
            if (db_affected_rows()) {
              while($row3 = db_fetch_object($sub_topics)) {
                // check if external link
                if (is_numeric($row3->asset)) {
                  $status = db_result(db_query("SELECT status FROM {node} WHERE nid=%d", $row3->asset));
                  if ($status == 1) {
                    ++$i; $k++;
                    if ($row3->type == 'asset') {
                      $asset++;
                    }
                    if ($row3->type == 'bead') {
                      $bead++;
                    }
                    if ($row3->type == 'quiz') {
                       // Find quiz original questions.
                      $sql = 'SELECT child_nid
                              FROM {quiz_node_relationship}
                              WHERE parent_nid = %d';
                      $res = db_query($sql, $row3->asset);
                      if (db_affected_rows()) {
                        while ($res_o = db_fetch_object($res)) {
                          $already_exists = NULL;
                          $already_exists = array_find_value($export_node, $res_o->child_nid);
                          if (empty($already_exists)) { 
                            $export_node[$i]['nid'] =  $res_o->child_nid;
                            $i++;
                          }
                        }
                      }
                      
                      $quiz++;
                    }
                    $export_node[$i]['nid'] =  $row3->asset;
                    $export_node[$i]['subtopic_id'] =  $row3->id;
                  }
                }
                else {
                  ++$i; $k++;
                  $external++;
                  $export_node[$i]['nid'] =  $row3->asset;
                  $export_node[$i]['subtopic_id'] =  $row3->id;
                }
              }
            }
          }
        }
        // check if subtopic node id is added to $export_node
        //if ($k == 0) {
          $i++;
        //}
        $playlist++;
        // get node title based on nid
        $playlist_title = node_title($row->nid);
        // set the message
        drupal_set_message($playlist_title . ", exported by ". $user->name . " with " . $asset . " assets, " . $bead . " Beads, " . $quiz . " Quiz, " . $external . " External Links successfully!");
        watchdog("playlist-export", $playlist_title . ", exported by ". $user->name . " with " . $asset . " assets, " . $bead . " Beads, " . $quiz . " Quiz, " . $external . " External Links successfully!");
        
      }
      // check node_export_node_bulk function and export node values to be set
      if (module_exists("node_export") && $export_node) {
        node_export_node_bulk_export_playlist($export_node, FALSE, NULL, $export_new);
      }
    }
  }
  // set the message
  drupal_set_message($playlist  ." Playlist, exported by " . $user->name . " successfully!");
}
/**
 * Find value in multidimension array
 *
 * @param $array_value
 *  It contains multidimension array value
 *
 * @param $find_value
 *  It contains search key value
 *
 * @return
 *  It returns true or false
 */
function array_find_value($array_value, $find_value = NULL) {
  if ($array_value) {
    foreach($array_value as $key => $value){
      if ($value['nid'] == $find_value) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * Callback for 'node_export' node operation.
 */
function node_export_node_bulk_export_playlist($nids, $return_code = FALSE, $format = NULL, $export_new = FALSE, $export_asset = FALSE) {
  $nodes = array();
  foreach ($nids as $key => $nid) {
    $node_temp =  NULL;
    // For Asset export also we call this function
    if (!$export_asset) {
      // check if external links
      if (is_numeric($nid['nid'])) {
        $node_temp = node_load($nid['nid']);
        if ($node_temp->type == 'quiz') {
          $sql = 'SELECT child_nid, question_status, weight, max_score
                  FROM {quiz_node_relationship}
                  WHERE parent_nid = %d';
          $res = db_query($sql, $node_temp->nid);
          if (db_affected_rows()) {
            while ($res_o = db_fetch_object($res)) {
              $node_temp->associated_questions[] = $res_o->child_nid;
              $node_temp->associated_question_status[] = $res_o->question_status;
              $node_temp->associated_weight[] = $res_o->weight;
              $node_temp->associated_max_score[] = $res_o->max_score; 
            }
          }
        }
        $node_temp->subtopic_id = $nid['subtopic_id'];
        $nodes[] = $node_temp;
      }
      else {
        $node_temp = new stdClass();
        $node_temp->nid = $nid['nid'];
        $node_temp->subtopic_id = $nid['subtopic_id'];
        $nodes[] = $node_temp;
      }
    }
    else {
      $nodes[] = node_load($nid);
    }
  }
  // Let other modules do special fixing up.
  // The function signature is: hook_node_export_node_bulk_alter(&$nodes, $op).
  // Where $op is 'export'.
  drupal_alter('node_export_node_bulk', $nodes, 'export', $format);

  // Allow other modules to take over this entire process. Typically the module
  // would respond if $format was set to something it recognises.
  $node_code = FALSE;
  drupal_alter('node_export_node_bulk_encode', $node_code, $nodes, $format);

  // Default handling of bulk node code.
  if ($node_code === FALSE) {
    $node_codes = array();
    foreach ($nodes as $node) {
      $node_codes[] = node_export_node_export_playlist($node, TRUE, 1, NULL, $export_new);
    }
    $node_code = "array(\n  ". implode(",\n  ", $node_codes) .",\n)";
  }

  if ($return_code) {
    return $node_code;
  }
  if (variable_get('node_export_bulk_code', 'copy') == 'copy') {
    drupal_set_message(drupal_get_form('node_export_form', $node_code));
  }
  else {
    node_export_get_file_playlist($nids, $node_code, TRUE);
  }
}



/**
 *  Exports a node - populate a node code form
 *  set $return_code to TRUE to not return form but the code instead.
 *  set $format to some string if encoding should be handled by some module that
 *  will recognise the string.
 */
function node_export_node_export_playlist($original_node, $return_code = FALSE, $iteration = 0, $format = NULL, $export_new = FALSE) {
  // check if external links
  if (is_numeric($original_node->nid)) {
    if (isset($original_node->nid)) {
      global $user;
      if (node_export_is_permitted($original_node->type)) {
        $node = drupal_clone($original_node);
        drupal_set_title(t('Export of !title', array('!title' => check_plain($node->title))));
        // Fix taxonomy array
        if (isset($node->taxonomy) && count($node->taxonomy)) {
          $vocabularies = taxonomy_get_vocabularies();
          $new_taxonomy = array();
          foreach ($node->taxonomy as $term) {
            // Free-tagging vocabularies need a different format
            if ($vocabularies[$term->vid]->tags) {
              $new_taxonomy['tags'][$term->vid][] = $term->name;
            }
            else {
              $new_taxonomy[$term->vid][$term->tid] = $term->tid;
            }
          }
          if (isset($new_taxonomy['tags']) && count($new_taxonomy['tags'])) {
            // Comma seperate the tags
            foreach ($new_taxonomy['tags'] as $vid => $tags) {
              $new_taxonomy['tags'][$vid] = implode(', ', $tags);
            }
            // For Old instance we construct taxonomy
            if ($new_taxonomy['tags'] && !$export_new) {
              foreach ($new_taxonomy['tags'] as $vid => $tags) {
                if ($vid == NEW_TAXONOMY_ACADEMICLEVEL) {
                  $new_taxonomy_new['tags'][TAXONOMY_ACADEMICLEVEL] = $tags;
                }
                if ($vid == NEW_TAXONOMY_SUBJECT ) {
                  $new_taxonomy_new['tags'][TAXONOMY_SUBJECT] = $tags;
                }
                if ($vid == NEW_TAXONOMY_TAGS ) {
                  $new_taxonomy_new['tags'][TAXONOMY_TAGS] = $tags;
                }
                if ($vid == NEW_TAXONOMY_ASSETCATEGORY) {
                  $new_taxonomy_new['tags'][TAXONOMY_ASSETCATEGORY] = $tags;
                }
              }
            }
            
          }
          // For Old instances
          $node->taxonomy = (!$export_new)?$new_taxonomy_new:$new_taxonomy;
        }
        // For curriculum need to include more that one topic
        if ($original_node->type == 'curriculum') {
          $topics = db_query('SELECT OGA.topic_title, OGA.topic_id, OGA.weight, OGA.cid FROM {curriculum_topics} OGA WHERE OGA.cid = %d', $original_node->nid);
          if (db_affected_rows()) {
            while($row = db_fetch_object($topics)) {
              $topics_title[] = $row->topic_title;
              $topics_weight[] = $row->weight;
              $topics_id[] =$row->topic_id;
            }
          }
          if ($topics_title) {
            $node->topics_title = $topics_title;
          }
          if ($topics_weight) {
            $node->topics_weight = $topics_weight;
          }
          if ($topics_id) {
            $node->topic_id = $topics_id;
          }
        }
        else  {
          // include topic id, weight in associated node
          $sub_topics = db_query('SELECT TA.topic_id, TA.weight FROM {curriculum_topics_assets} TA  WHERE TA.id = %d ', $original_node->subtopic_id);
          if (db_affected_rows()) {
            $row = db_fetch_object($sub_topics);
            $node->topic_id = $row->topic_id;
            $node->weight = $row->weight;
          }
        }
        // check if playlist or asset then clear the coauthor, reviewers
        if ($original_node->type == 'curriculum' || $original_node->type == 'asset') {
          $node->field_author[0]['uid'] = $original_node->uid;
          $node->field_coauthor = array('0' => array('uid' => NULL));
          $node->field_reviewers = array('0' => array('uid' => NULL));
          // For New instances
          if (!$export_new) {
            $node->field_openforreview[0]['value'] = NULL;
          }
          if (!$export_new && $original_node->type == 'asset' && ($original_node->field_format[0]['value'] == "IMAGE" || $original_node->field_format[0]['value'] == "PDF" || $original_node->field_format[0]['value'] == "VIDEO" || $original_node->field_format[0]['value'] == "AUDIO")) {
            $node->field_content[0]['value'] = $node->body;
            $node->body = NULL;
          }
        }
        // Fix menu array
        $node->menu = node_export_get_menu($original_node);
  
        // Let other modules do special fixing up.
        // The function signature is: hook_node_export_node_alter(&$node, $original_node, $method)
        // Where $method is 'export'
        drupal_alter('node_export_node', $node, $original_node, 'export', $format);
        $node = node_export_remove_recursion($node);
        $node_code = node_export_node_encode($node, $iteration, $format);
        if ($return_code) {
          return $node_code;
        }
        if (variable_get('node_export_node_code', 'copy') == 'copy') {
          return drupal_get_form('node_export_form', $node_code);
        }
        else {
          node_export_get_file_playlist(array($original_node->nid), $node_code);
        }
      }
    }
  }
  else {
    // separate external link as individual node
    $sub_topics = db_query('SELECT TA.topic_id, TA.id, TA.asset, TA.type, TA.title, TA.description, TA.weight FROM {curriculum_topics_assets} TA  WHERE TA.id = %d ', $original_node->subtopic_id);
    if (db_affected_rows()) {
      $row = db_fetch_object($sub_topics);
      $node = new stdClass();
      $node->nid = $row->asset;
      $node->topic_id = $row->topic_id;
      $node->type = $row->type;
      $node->title = $row->title;
      $node->description = $row->description;
      $node->weight = $row->weight;
      $node = node_export_remove_recursion($node);
      $node_code = node_export_node_encode($node, $iteration, $format);
      return $node_code;
    }
  }
}

/**
 * Generate text file.
 * @param $nodes
 *   An array of nids.
 * @param $node_code
 *   The text output.
 */
function node_export_get_file_playlist($nodes, $node_code, $bulk = FALSE) {
  global $base_url;
  $filename_data = array();
  $filename_data['count'] = count($nodes);
  $filename_data['time'] = time();

  if ($bulk) {
    $name = variable_get('node_export_bulk_filename', 'node-export([node-count]-nodes).[timestamp].export');
  }
  else {
    $name = variable_get('node_export_node_filename', 'node-export.[timestamp].export');
  }
  if (module_exists('token')) {
    $name = token_replace($name, 'Node export filename', $filename_data, '[', ']');
  }
  else {
    // So it works without token.
    $name = str_replace('[node-count]', $filename_data['count'], $name);
    $name = str_replace('[timestamp]', $filename_data['time'], $name);
  }
  // For export the file we concatenate sitename
  $sitename = explode('//', $base_url);
  $name =  $name . '.' . $sitename[1];
  //echopre(explode('.', $name));
  
  header('Content-type: text/plain');
  header('Content-Disposition: attachment; filename="'. $name .'"');
  print($node_code);
  // Clean exit.
  module_invoke_all('exit');
  exit;
 
}


/**
 * Form constructor for the Export playlist.
 *
 * @see export_playlist_form_validate()
 * @see export_playlist_form_submit()
 * @ingroup forms
 */
function import_playlist_form($form_state) {
  $form = array();
  $form['#attributes'] = array(
    'enctype' => "multipart/form-data",
  );
  $form['upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload file'),
  );
  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('User Name'),
    '#required' => TRUE
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#weight' => 10,
  );
  $_REQUEST['destination_import'] = 'admin/school_management/import_playlist';
  return $form;
}

/**
 * Form validate handler for import_playlist_form().
 *
 */
function import_playlist_form_validate($form, &$form_state) {
  $i = 0;
  // check if valid user id
  if ($form_state['clicked_button']['#post']['username']) {
    $user_name = explode(", ", $form_state['clicked_button']['#post']['username']);
    foreach($user_name as $key => $value) { 
      // Get list of user only on Teacher
      $user_name = NULL;
      $user_name = db_result(db_query("SELECT uid FROM {users} WHERE name='%s'", $value));
      if (!$user_name) {
        form_set_error('username', t('Please Enter Valid username.'));
      }
      $user_role = db_result(db_query("SELECT rid FROM {users_roles} WHERE uid=%d", $user_name));
      $result = db_result(db_query("SELECT perm FROM {permission} WHERE rid=%d", $user_role));
      // Set permission for edit own bead content to site admin
      $check = strpos($result, 'create curriculum content');
      if ($check != TRUE) {
        form_set_error('username', t($value . ' is not authourised to import playlist'));
      }
      
      $i++;
    }
    // check if multiple username
    if ($i > 1) {
      form_set_error('username', t('Please Enter Single username.'));
    }
  }// check if files uploaded
  else if(!$_FILES['files']['name']['upload']) {
    drupal_set_message(t('Please upload a file to import.'), 'error');
    form_set_error('', NULL);
  }
}


/**
 * Submit function for import_playlist_form.
 *
 * @see node_export_import_playlist().
 */
function import_playlist_form_submit($form, &$form_state) {
  global $user;
  if ($_FILES['files']['name']['upload']) { 
    $original = $_FILES['files']['name']['upload'];
    $directory = file_directory_path() .'/'. NODE_EXPORT;
    
    if (file_check_directory($directory, FILE_CREATE_DIRECTORY)) {
      $save = file_save_upload('upload', array(), $directory, FILE_EXISTS_RENAME);
      if (!$save) {
        drupal_set_message(t('Error: Node export could not save file.'), 'error');
      }
      else {
        $save->original = $original;
        form_set_value($form['upload'], serialize($save), $form_state);
      }
    }
    else {
      drupal_set_message(t('Error: Node export could not access files directory.'), 'error');
    }
  }
 // Assign
  $form_state['storage']['values'] = $form_state['values'];
  if (isset($form_state['storage']['values'])) {
    $values = &$form_state['storage']['values'];
    if ($values['upload']) {
      $file = unserialize($values['upload']);
      if (file_exists($file->filepath)) {
        $node_code = file_get_contents($file->filepath);
        unlink($file->filepath);
      }
    }
    elseif ($values['code']) {
      $node_code = trim($values['code']);
    }
  }
  if (isset($node_code)) {
    $filename_list = explode('export.', $_FILES['files']['name']['upload']);
    
    //$sitename = explode('.', $_FILES['files']['name']['upload']);
    $sitename = $filename_list[1];
    $result = node_export_import_playlist($node_code, NULL, TRUE, 'drupal_set_message', 't', $form_state['clicked_button']['#post']['username'], $sitename);
    if (!empty($result)) {
      return $result;
    }
  }
  
}
/**
 * Import Function for playlist
 *
 * @param $node_code
 *   The string of node code.
 * @param $method
 *   If set will override the variable table settings
 * @param $redirect
 *   Whether to allow redirects
 * @param $msg_func
 *   Function used to output status message
 * @param $msg_t
 *   Function used to translate
 * @param $to_username
 *  It contains user id
 * @param $sitename
 *  It contains sitename name from which site 
 * @return
 *   FALSE is the types check failed
 *   Returns the HTML of a node form if required to prepopulate
 *   Otherwise returns TRUE, or may redirect.
 */
function node_export_import_playlist($node_code, $method = NULL, $redirect = TRUE, $msg_func = 'drupal_set_message', $msg_t = 't', $to_username = NULL, $site_name = NULL) {
  global $user;
  $import = node_export_node_decode($node_code);
  $import = node_export_restore_recursion($import);
  //$types_exist = node_export_import_types_check_playlist($import);
  //if ($types_exist) {
    $count = 0;
    if (is_array($import)) {
      // This is a bulk import.
      $total = count($import);
      // Let other modules do special fixing up.
      // The function signature is: hook_node_export_node_bulk_alter(&$nodes, $op).
      // Where $op is 'import'.
      drupal_alter('node_export_node_bulk', $import, 'import');
      $playlist_count = 0;
      $new_nodes = array();
      foreach ($import as $new_node) {
        if (node_get_types('name', $new_node) == TRUE || $new_node->type == "federated" ) {
          
          $new_nid = node_export_node_save_playlist($new_node, $to_username, $site_name);
          $new_node->nid = $new_nid;
          if ($new_node->type == 'curriculum'){
            $playlist_count++;
          }
          $new_nodes[] = $new_node;
          $count++;
        }
      }
      $playlist = 0;
      
      //After import all node the associate to playlist
      $query = db_query("SELECT * FROM {curriculum_topics_import}");
      if (db_affected_rows()) {
        while($row = db_fetch_object($query)) {
          db_query('INSERT INTO {curriculum_topics}
                      (cid, topic_title, weight, created, changed)
                      VALUES(%d, "%s", "%s", %d, %d)', $row->new_id, $row->topic_title, $row->weight, time(), time());
          $last_insert_id = db_last_insert_id('curriculum_topics', 'topic_id');
          // get subtopic list
          $sub_query = db_query('SELECT * FROM {curriculum_topics_assets_import} TA  WHERE TA.topic_id = %d', $row->topic_id);
          if (db_affected_rows()) {
            while($sub_row = db_fetch_object($sub_query)) {
              db_query('INSERT INTO {curriculum_topics_assets}
                          (topic_id, asset, type, title, description, weight, created, changed)
                          VALUES(%d, "%s", "%s", "%s", "%s", "%s", %d, %d)',
                          $last_insert_id, $sub_row->new_id, $sub_row->type, $sub_row->title, $sub_row->description, $sub_row->weight,  time(), time());
            }
          }
        }
      }
      if (db_table_exists("quiz_node_relationship")) {
       //After import all node the associate to playlist
        $query = db_query("SELECT * FROM {quiz_node_relationship_import}");
        if (db_affected_rows()) {
          while($row = db_fetch_object($query)) {
            $get_child = db_query("SELECT new_nid, new_vid from {quiz_node_relationship_questions_import} WHERE child_nid=%d", $row->child_nid);
            $child = db_fetch_object($get_child);
             db_query('INSERT INTO {quiz_node_relationship}
                        (parent_nid, parent_vid, child_nid, child_vid, question_status, weight, max_score)
                        VALUES(%d, %d, %d, %d, %d, %d, %d)', $row->new_nid, $row->new_vid, $child->new_nid, $child->new_vid,  $row->question_status, $row->weight, $row->max_score);
          }
        }
      }

      // after associated playlist then clear this table
      db_query("TRUNCATE TABLE {curriculum_topics_import}");
      db_query("TRUNCATE TABLE {curriculum_topics_assets_import}");
      db_query("TRUNCATE TABLE {quiz_node_relationship_import}");
      db_query("TRUNCATE TABLE {quiz_node_relationship_questions_import}");
      
      drupal_alter('node_export_node_bulk', $new_nodes, 'after import');
      //set the message
      drupal_set_message($playlist_count . " Playlists imported by " . $user->name  . " successfully!");
      watchdog("playlist-import", $playlist_count . " Playlists imported by " . $user->name  . " successfully!");
      
      return TRUE;
    }
    else {
      // We are importing a single node.
      $node = &$import;
      $total = 1;
      $method = !is_null($method) ? $method : variable_get('node_export_method', 'save-edit');

      if ($method == 'save-edit') {
        $new_nid = node_export_node_save_playlist($node, $to_username);
        $msg_func($msg_t("Imported node !nid: !node", array('!nid' => $new_nid, '!node' => l($new_node->title, 'node/'. $new_nid))));
        $count++;
        $msg_func($msg_t("!count of !total nodes were imported.  Some values may have been reset depending on Node Export's configuration", array('!total' => $total, '!count' => $count)));
        if ($redirect) {
          drupal_goto('node/'. $new_nid .'/edit');
        }
        return TRUE;
      }
      else if ($method == 'prepopulate') {
        include_once(drupal_get_path('module', 'node') .'/node.pages.inc');
        return node_export_node_prepopulate($node);
      }
    }
  //}
  return FALSE;
}
/**
 *  Check if all types in the import exist.  Return TRUE/FALSE.
 */
function node_export_import_types_check_playlist($import) {
  $types_exist = TRUE;
  if (is_array($import)) {
    foreach ($import as $new_node) {
      // Include new type external link
      if (node_get_types('name', $new_node) == FALSE && is_numeric($new_node->nid)) { 
        $types_exist = $new_node->type;
      }
    }
  }
  else {
    $new_node = $import;
    if (node_get_types('name', $new_node) == FALSE) {
      $types_exist = $new_node->type;
    }
  }
  if ($types_exist !== TRUE) {
    drupal_set_message(t('Error encountered during import.  Node type %t unknown on this site.  No nodes imported.', array('%t' => $types_exist)), 'error');
    $types_exist = FALSE;
  }
  return $types_exist;
}
/**
 * Exports a node by directly saving it.
 */
function node_export_node_save_playlist($original_node, $to_username = NULL, $site_name = NULL) {
  global $user, $base_url;
  // check for external links
  if (is_numeric($original_node->nid)) {
    // check if given node type is avaliable
    if (node_export_is_permitted($original_node->type)) {
      if ($original_node->type != 'quiz' && $original_node->type != 'long_answer' && $original_node->type != 'matching' && $original_node->type != 'multichoice' && $original_node->type != 'quiz_directions' && $original_node->type != 'quiz_question' && $original_node->type != 'scale' && $original_node->type != 'short_answer' && $original_node->type != 'truefalse') {
        // check for bead if already in site
        if ($original_node->type != 'bead') {
          $node = node_export_node_clone_playlist($original_node, "save-edit", $to_username, $site_name);
          node_export_save($node);
          // if not playlist then set the message. Playlist should display only count 
          if ($original_node->type != 'curriculum') {
            drupal_set_message(l($node->title, 'node/' . $node->nid) . ", imported by " . $user->name  . " successfully!");
            watchdog("playlist-import", l($node->title, 'node/' . $node->nid) . ", imported by " . $user->name  . " successfully!");
          }
        }
        else {
          // check for bead is already exists.
          $nid = db_result(db_query("SELECT nid FROM {content_type_bead} WHERE field_source_id_value = '%s' AND field_bead_seq_no_value ='%s'", $original_node->field_source_id[0]['value'], $original_node->field_bead_seq_no[0]['value']));
          // if exists
          if (db_affected_rows()){
            $node = NULL;
            $node->nid = $nid;
            drupal_set_message("Bead already exists!");
            watchdog("playlist-import", "Bead already exists!");
          }
          else {
            // create bead content with site admin author
            $node = node_export_node_clone_playlist($original_node, "save-edit", 'siteadmin', $site_name);
            node_export_save($node);
            // set the message
            drupal_set_message(l($node->title, 'node/' . $node->nid) . ", imported by " . $user->name  . " successfully!");
            watchdog("playlist-import", l($node->title, 'node/' . $node->nid) . ", imported by " . $user->name  . " successfully!");
          }
        }
        // if playlist then add the topic title to temp curriculum_topics_import table
        if ($original_node->type == 'curriculum') {
          // For new version when we create playlist by default topic1 is added automatically to avoid those issues we need to delete the topic1
          db_query("DELETE FROM {curriculum_topics} WHERE cid=%d", $node->nid);
          // check if topic title have more that than one.
          if ($original_node->topics_title) {
            for ($i = 0; $i < count($original_node->topics_title); $i++) {
              db_query("INSERT INTO {curriculum_topics_import} SET cid = %d, topic_title='%s', created=%d, changed=%d, weight=%d, topic_id=%d, new_id = %d", $original_node->nid,  $original_node->topics_title[$i], time(), time(), $original_node->topics_weight[$i], $original_node->topic_id[$i], $node->nid);
            }
          }
        }
        else {
          // other than playlist then add the subtopic details to temp curriculum_topics_assets_import table
           db_query('INSERT INTO {curriculum_topics_assets_import}
                            (topic_id, asset, type, title, weight, is_admin, created, changed, new_id)
                            VALUES(%d, "%s", "%s", "%s", "%s", "%s", %d, %d, "%s")',
                            $original_node->topic_id, $original_node->nid, $original_node->type, $original_node->title, $original_node->weight, 0, time(), time(), $node->nid);
        }
      }
      else {
        if ($original_node->type == 'quiz') {
          
          $node = node_export_node_clone_playlist($original_node, "save-edit", $to_username, $site_name);
          node_export_save($node);
          if ($original_node->associated_questions) {
            for ($i = 0; $i < count($original_node->associated_questions); $i++) {
              db_query('INSERT INTO {quiz_node_relationship_import}
                      (parent_nid, child_nid, question_status, weight, max_score, new_nid, new_vid)
                      VALUES(%d, %d, %d, %d, %d, %d, %d)', $original_node->nid, $original_node->associated_questions[$i], $original_node->associated_question_status[$i], $original_node->associated_weight[$i], $original_node->associated_max_score[$i], $node->nid, $node->vid);
            }
          }
          // other than playlist then add the subtopic details to temp curriculum_topics_assets_import table
          db_query('INSERT INTO {curriculum_topics_assets_import}
                           (topic_id, asset, type, title, weight, is_admin, created, changed, new_id)
                           VALUES(%d, "%s", "%s", "%s", "%s", "%s", %d, %d, "%s")',
                           $original_node->topic_id, $original_node->nid, $original_node->type, $original_node->title, $original_node->weight, 0, time(), time(), $node->nid);
        }
        else {
          $node = node_export_node_clone_playlist($original_node, "save-edit", $to_username, $site_name);
          node_export_save($node);
          db_query('INSERT INTO {quiz_node_relationship_questions_import}
                  (child_nid, new_nid, new_vid)
                  VALUES(%d, %d, %d)', $original_node->nid, $node->nid, $node->vid);
        }
      }
    }
  }
  else {
    //if external links
    db_query('INSERT INTO {curriculum_topics_assets_import}
                    (topic_id, asset, type, title, description, weight, created, changed, new_id)
                    VALUES(%d, "%s", "%s", "%s", "%s", "%s", %d, %d, "%s")',
                    $original_node->topic_id, $original_node->nid, $original_node->type, $original_node->title, $original_node->description, $original_node->weight, time(), time(), $original_node->nid);
    $node = NULL;
    $node->nid = $original_node->nid;
    // set the message
    drupal_set_message(l($original_node->title, $original_node->nid) . ", imported by " . $user->name  . " successfully!");
    watchdog("playlist-import", l($original_node->title, $original_node->nid) . ", imported by " . $user->name  . " successfully!");
  }
  $nid = NULL;
  // get sitename from where we export
  $site_ownname = explode('//', $base_url);
  // check if the node is already exists in current site
  if ($site_ownname[1] == $site_name && $original_node->type != 'curriculum' && $original_node->type != 'federated' && $original_node->type != 'bead') {
    $nid = db_result(db_query("SELECT nid FROM {node} WHERE nid=%d", $original_node->nid));
  }
  else {
    // check if the node is already exists in current site
    $nid = db_result(db_query("SELECT IM.new_nid FROM {import_track} IM INNER JOIN {node} N ON IM.new_nid = N.nid WHERE IM.sitename='%s' AND IM.nid=%d AND IM.type='%s'", $site_name, $original_node->nid, $original_node->type));
  }
  // check if the node is already exists otherwise we track the data
  if ($original_node->type != 'curriculum' && $original_node->type != 'federated' && $original_node->type != 'bead'  && empty($nid)) {
    db_query("INSERT INTO {import_track} SET sitename='%s', nid=%d, new_nid=%d, type='%s', created=%d, changed=%d", $site_name, $original_node->nid, $node->nid, $original_node->type, time(), time());
  }
  else {
    // update the data
    db_query("UPDATE {import_track} IM SET IM.changed=%d WHERE IM.sitename='%s' AND IM.nid=%d AND IM.type='%s'", time(), $site_name, $original_node->nid, $original_node->type);
  }
  return $node->nid;
}
/**
 * Prepare a clone of the node during import.
 */
function node_export_node_clone_playlist($original_node, $mode, $to_username = NULL, $site_name = NULL) {
    global $user, $base_url;
    $nid = NULL;
    // get sitename from where we export
    $site_ownname = explode('//', $base_url);
    // check if the node is already exists in current site
    if ($site_ownname[1] == $site_name && $original_node->type != 'curriculum' && $original_node->type != 'federated' && $original_node->type != 'bead') {
      $nid = db_result(db_query("SELECT nid FROM {node} WHERE nid=%d", $original_node->nid));
    }
    else {
      // check if the node is already exists in current site
      $nid = db_result(db_query("SELECT IM.new_nid FROM {import_track} IM INNER JOIN {node} N ON IM.new_nid = N.nid WHERE IM.sitename='%s' AND IM.nid=%d AND IM.type='%s'", $site_name, $original_node->nid, $original_node->type));
    }
    // if the node does not exists 
    if (empty($nid)) {
      $node = drupal_clone($original_node);
      $node->nid = NULL;
      $node->vid = NULL;
      // assign given username to node
      $node->name = !empty($to_username)?$to_username:$user->name;
      if (!empty($to_username)) {
        $user_id = db_result(db_query("SELECT uid FROM {users} WHERE name='%s'", $to_username));
      }
      
      $node->uid = !empty($user_id)?$user_id:$user->uid;
      if ($node->type == 'asset' || $node->type == 'curriculum') {
        $node->field_author[0]['uid'] = !empty($user_id)?$user_id:$user->uid;
      }
  
      if (variable_get('node_export_reset_created_'. $node->type, TRUE)) {
        $node->created = NULL;
      }
  
      if (variable_get('node_export_reset_changed_'. $node->type, TRUE)) {
        $node->changed = NULL;
      }
  
      if (variable_get('node_export_reset_menu_'. $node->type, TRUE)) {
        $node->menu = NULL;
      }
  
      if (variable_get('node_export_reset_path_'. $node->type, TRUE)) {
        $node->path = NULL;
      }
      elseif (module_exists('pathauto')) {
        // Prevent pathauto from creating a new path alias.
        $node->pathauto_perform_alias = FALSE;
      }
  
      if (variable_get('node_export_reset_book_mlid_'. $node->type, TRUE) && isset($node->book['mlid'])) {
        $node->book['mlid'] = NULL;
      }
  
      $node->files = array();
      if (variable_get('node_export_reset_'. $node->type, FALSE)) {
        $node_options = variable_get('node_options_'. $node->type, array('status', 'promote'));
        // Fill in the default values.
        foreach (array('status', 'moderate', 'promote', 'sticky', 'revision') as $key) {
          $node->$key = in_array($key, $node_options);
        }
      }
      // Let other modules do special fixing up.
      // The function signature is: hook_node_export_node_alter(&$node, $original_node, $method)
      // Where $method is either 'prepopulate' or 'save-edit'.
      drupal_alter('node_export_node', $node, $original_node, $mode);
      
    }
    else {
      // To update the existing node
      $custom_node = node_load($nid);
      $node = drupal_clone($original_node);
      $node->nid = $nid;
      $node->vid = $custom_node->vid;
      $node->created =  $custom_node->created;
      $node->changed =  $custom_node->changed;
      $node->menu =  $custom_node->menu;
      $node->path =  $custom_node->path;
      if (module_exists('pathauto')) {
        $node->pathauto_perform_alias =  $custom_node->pathauto_perform_alias;
      }
      $node->status =  $custom_node->status;
      $node->promote =  $custom_node->promote;
      $node->sticky =  $custom_node->sticky;
      $node->revision =  $custom_node->revision;
      $node->field_author[0]['uid'] =  $custom_node->field_author[0]['uid'];
      $node->name =  $custom_node->name;
      $node->uid = $custom_node->uid;
      // Let other modules do special fixing up.
      // The function signature is: hook_node_export_node_alter(&$node, $original_node, $method)
      // Where $method is either 'prepopulate' or 'save-edit'.
      drupal_alter('node_export_node', $node, $original_node, $mode);
    }
    return $node;

}