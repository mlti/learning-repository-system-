<?php
// $Id: eb_search_setting.module 2011/08/13 3:44:PM Jaffar Exp $
/**
 * @file
 *  To manipulate administration setting of apache solr.
 *
 */
/**
 * Form constructor for the Setting of custom table indexing
 *
 * @see apachesolr_edubridge_settings_form_submit()
 * @ingroup forms
 */
function apachesolr_edubridge_settings_form() {
  $form = array();
  $form['topic'] = array(
    '#title' => t('Enable indexing of topics'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('edubridge_setting_topic', 0),
    '#return_value' => 1,
  );
  $form['associated_asset'] = array(
    '#title' => t('Enable indexing of associated Assets'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('edubridge_setting_assoc_asset', 0),
    '#return_value' => 1,
  );
  $form['eb_setting_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}
/**
 * Form submission handler for apachesolr_edubridge_settings_form().
 *
 * On submit for Setting of custom table indexing.
 *
 * @see apachesolr_edubridge_settings_form()
 */
function apachesolr_edubridge_settings_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#post']['topic'] == 1) {
    variable_set('edubridge_setting_topic', 1);
  }
  else {
    variable_set('edubridge_setting_topic', 0);
  }

  if ($form_state['clicked_button']['#post']['associated_asset'] == 1) {
    variable_set('edubridge_setting_assoc_asset', 1);
  }
  else {
    variable_set('edubridge_setting_assoc_asset', 0);
  }
}

/**
 * Configure ranking setting in apache solr interface
 *
 * @param $form
 *  It contains reference object of form_alter
 *
 * @return $form
 *   It returns array
 *
 */
function ranking_configuration(&$form) {
  $recommend_teacher_settings = variable_get('apachesolr_recommend_teacher_boost','0');
  $recommend_student_settings = variable_get('apachesolr_recommend_student_boost', '0');
  $bookmark_teacher_settings = variable_get('apachesolr_bookmark_teacher_boost', '0');
  $bookmark_student_settings = variable_get('apachesolr_bookmark_student_boost','0');

  //$asset_used_settings = variable_get('apachesolr_asset_used_boost', '0');
  $asset_used_curri_settings = variable_get('apachesolr_asset_used_curri_boost', '0');
  $rating_teacher_settings = variable_get('apachesolr_rating_teacher_boost','0');
  $rating_student_settings = variable_get('apachesolr_rating_student_boost', '0');
  $options = array(
    '30' => '3.0',
    '25' => '2.5',
    '20' => '2.0',
    '15' => '1.5',
    '10' => '1.0',
    '0' => t('Normal'),
  );
  $form['biasing']['apachesolr_recommend_teacher_boost'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t("Recommended by Teacher"),
    '#default_value' => $recommend_teacher_settings,
    '#description' => t('This setting will change the result scoring so that nodes with better Recommend may appear before those with higher keyword matching.'),
    '#weight' => -2,
  );
  $form['biasing']['apachesolr_recommend_student_boost'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t("Recommended by Student"),
    '#default_value' => $recommend_student_settings,
    '#description' => t('This setting will change the result scoring so that nodes with better Recommend may appear before those with higher keyword matching.'),
    '#weight' => -2,
  );
  $form['biasing']['apachesolr_rating_teacher_boost'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t("Rated by Teacher"),
    '#default_value' => $rating_teacher_settings,
    '#description' => t('This setting will change the result scoring so that nodes with better average Rating scores may appear before those with higher keyword matching.'),
    '#weight' => -2,
  );
  $form['biasing']['apachesolr_rating_student_boost'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t("Rated by Student"),
    '#default_value' => $rating_student_settings,
    '#description' => t('This setting will change the result scoring so that nodes with better average Rating scores may appear before those with higher keyword matching.'),
    '#weight' => -2,
  );
  $form['biasing']['apachesolr_bookmark_teacher_boost'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t("Bookmarked By Teacher"),
    '#default_value' => $bookmark_teacher_settings,
    '#description' => t('This setting will change the result scoring so that nodes with better average Bookmark scores may appear before those with higher keyword matching.'),
    '#weight' => -2,
  );
  $form['biasing']['apachesolr_bookmark_student_boost'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t("Bookmarked By Student"),
    '#default_value' => $bookmark_student_settings,
    '#description' => t('This setting will change the result scoring so that nodes with better average Bookmark scores may appear before those with higher keyword matching.'),
    '#weight' => -2,
  );
  $form['biasing']['apachesolr_asset_used_curri_boost'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t("Asset used in playlist and new asset"),
    '#default_value' => $asset_used_curri_settings,
    '#description' => t('This setting will change the result scoring so that nodes with better average Asset used in Course Group scores may appear before those with higher keyword matching.'),
    '#weight' => -2,
    );

  return $form;
}
/**
 * It assign contact username
 *
 * @param $form
 *  It contains reference object of form_alter
 *
 * @return $form
 *   It returns array
 *
 */
function assign_contact_user_value(&$form) {
  if ($_GET['cid'] && is_numeric($_GET['cid'])) {
    $userLoad = user_load($_GET['cid']);
    $form['privatemsg']['recipient'] = array(
      '#type'               => 'textfield',
      '#title'              => t('To'),
      '#default_value'      => $userLoad->name,
      '#required'           => TRUE,
      '#weight'             => -10,
      '#size'               => 50,
      '#autocomplete_path'  => 'messages/user-name-autocomplete',
    );
  }
  return $form;
}
