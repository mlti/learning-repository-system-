<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function syntiro_profile_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_educational_info
  $groups['profile-group_educational_info'] = array(
    'group_type' => 'standard',
    'type_name' => 'profile',
    'group_name' => 'group_educational_info',
    'label' => 'Educational Info',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '3',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '3',
    'fields' => array(
      '0' => 'field_institute',
      '1' => 'field_department',
      '2' => 'field_profile_certifications',
      '3' => 'field_profile_publications',
      '4' => 'field_profile_interests',
      '5' => 'field_profile_previous_school',
      '6' => 'field_profile_affiliations',
      '7' => 'field_profile_degree',
      '8' => 'field_resume',
      '9' => 'field_occupation',
    ),
  );

  // Exported group: group_personal_info
  $groups['profile-group_personal_info'] = array(
    'group_type' => 'standard',
    'type_name' => 'profile',
    'group_name' => 'group_personal_info',
    'label' => 'Personal Info',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '2',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '2',
    'fields' => array(
      '0' => 'field_profile_first_name',
      '1' => 'field_profile_last_name',
      '2' => 'field_street',
      '3' => 'field_city',
      '4' => 'field_state',
      '5' => 'field_profile_phone',
      '6' => 'field_country',
      '7' => 'field_postal_code',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Educational Info');
  t('Personal Info');

  return $groups;
}
