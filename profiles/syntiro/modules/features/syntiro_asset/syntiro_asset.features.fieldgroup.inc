<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function syntiro_asset_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_mlr_standard
  $groups['asset-group_mlr_standard'] = array(
    'group_type' => 'standard',
    'type_name' => 'asset',
    'group_name' => 'group_mlr_standard',
    'label' => 'MLR Standard',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
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
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '3',
    'fields' => array(
      '0' => 'field_mlr',
    ),
  );

  // Exported group: group_type
  $groups['asset-group_type'] = array(
    'group_type' => 'standard',
    'type_name' => 'asset',
    'group_name' => 'group_type',
    'label' => 'Type',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
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
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '4',
    'fields' => array(
      '0' => 'field_type',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('MLR Standard');
  t('Type');

  return $groups;
}
