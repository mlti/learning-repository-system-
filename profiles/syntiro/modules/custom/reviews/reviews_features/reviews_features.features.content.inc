<?php

/**
 * Implementation of hook_content_default_fields().
 */
function reviews_features_content_default_fields() {
  $fields = array();

  // Exported field: field_review_reference
  $fields['reviews-field_review_reference'] = array(
    'field_name' => 'field_review_reference',
    'type_name' => 'reviews',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'asset' => 'asset',
      'curriculum' => 'curriculum',
      'community_interest_group' => 0,
      'course_group' => 0,
      'discussion' => 0,
      'news' => 0,
      'page' => 0,
      'profile' => 0,
      'story' => 0,
      'reviews' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_review_reference][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Review Reference',
      'weight' => '31',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Review Reference');

  return $fields;
}
