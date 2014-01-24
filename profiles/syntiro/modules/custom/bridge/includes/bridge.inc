<?php
// $Id: bridge.inc,  25/08/2011 4:51:PM Exp Jaffar $

/**
 * @file
 * Handling appropriate action of bridge.
 */


function bridge_frontpage() {
  global $base_url, $user;
  if ($user->uid == 0) {
    drupal_goto('user');
  }
  else {
    drupal_goto('bridge');
  }
}

function bridge_home() {
  global $user;
  if($user->uid) {
    if (!user_access("create asset content")) {
      drupal_add_js(array('bridge_basket_assignment' => TRUE), 'setting');
    }
  }
  drupal_add_js(drupal_get_path('module', 'recommend') .'/recommend.js');
  drupal_add_js(array('bridge_basket' => TRUE), 'setting');
  return '';
}

/**
 * Setting to change email notification
 *
 */
function user_preference_list(&$form_state) {
  global $user;
  if (module_exists("privatemsg")) {
    if (privatemsg_user_access('read privatemsg')) {
      $form['pm_send_notifications'] = array(
        '#type' => 'checkbox',
        '#title' => t('Receive email notification for incoming private messages'),
        '#default_value' => _pm_email_notify_is_enabled($user->uid),
      );
    }
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('submit'),
    '#weight' => 15,
  );
  $form['#redirect'] = url('user/' . $user->uid);
  return $form;
}
/**
 * Form submit 
 *
 */
function user_preference_list_submit($form, &$form_state) {
  global $user;
  if (isset($form_state['values']['pm_send_notifications']) && module_exists("privatemsg") && privatemsg_user_access('read privatemsg')) {
    $pm_email_enabled = $form_state['values']['pm_send_notifications'];
    // Update database entry with user preference.
    $exists = db_result(db_query("SELECT 1 FROM {pm_email_notify} WHERE user_id = %d", $user->uid));
    if ($exists) {
      // If there is an existing entry, update.
      db_query("UPDATE {pm_email_notify} SET email_notify_is_enabled = %d WHERE user_id = %d", $pm_email_enabled, $user->uid);
    }
    else {
      // If not, create a new one.
      db_query("INSERT INTO {pm_email_notify} (email_notify_is_enabled, user_id) VALUES (%d, %d)", $pm_email_enabled, $user->uid);
    }
  }
  //$profile = content_profile_load('profile', $user->uid);
  $nodeobj = node_load(array('type' => 'profile', 'uid' => $user->uid));
  $nodeobj->field_tooltip_switch[0]['value']  = $form_state['values']['field_tooltip_switch'];
  node_save($nodeobj);
  drupal_set_message("Changes has been updated.");
}
