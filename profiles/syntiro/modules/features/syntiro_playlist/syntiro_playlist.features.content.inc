<?php

/**
 * Implementation of hook_content_default_fields().
 */
function syntiro_playlist_content_default_fields() {
  $fields = array();

  // Exported field: field_author
  $fields['curriculum-field_author'] = array(
    'field_name' => 'field_author',
    'type_name' => 'curriculum',
    'display_settings' => array(
      'weight' => '10',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
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
    'type' => 'userreference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'userreference',
    'active' => '1',
    //'referenceable_roles' => array(
    //  '3' => 3,
    //  '5' => 5,
    //  '2' => 0,
    //  '6' => 0,
    //  '7' => 0,
    //  '4' => 0,
    //),
    'referenceable_roles' => array(
      '6' => 6,
      '9' => 9,
      '2' => 0,
      '4' => 0,
      '7' => 0,
      '8' => 0,
    ),
    'referenceable_status' => '',
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'reverse_link' => 0,
      'default_value' => array(
        '0' => array(
          'uid' => NULL,
          '_error_element' => 'default_value_widget][field_author][0][uid][uid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Author',
      'weight' => '10',
      'description' => '',
      'type' => 'userreference_autocomplete',
      'module' => 'userreference',
    ),
  );

  // Exported field: field_coauthor
  $fields['curriculum-field_coauthor'] = array(
    'field_name' => 'field_coauthor',
    'type_name' => 'curriculum',
    'display_settings' => array(
      'weight' => '11',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
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
    'type' => 'userreference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'userreference',
    'active' => '1',
    //'referenceable_roles' => array(
    //  '3' => 3,
    //  '5' => 5,
    //  '2' => 0,
    //  '6' => 0,
    //  '4' => 0,
    //),
    'referenceable_roles' => array(
      '6' => 6,
      '9' => 9,
      '2' => 0,
      '4' => 0,
      '8' => 0,
    ),
    'referenceable_status' => '',
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'reverse_link' => 0,
      'default_value' => array(
        '0' => array(
          'uid' => NULL,
          '_error_element' => 'default_value_widget][field_coauthor][0][uid][uid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Co Author',
      'weight' => '11',
      'description' => '',
      'type' => 'userreference_autocomplete',
      'module' => 'userreference',
    ),
  );

  // Exported field: field_institute
  $fields['curriculum-field_institute'] = array(
    'field_name' => 'field_institute',
    'type_name' => 'curriculum',
    'display_settings' => array(
      'weight' => '12',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
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
      'institute' => 'institute',
      'asset' => 0,
      'community_interest_group' => 0,
      'discussion' => 0,
      'multichoice' => 0,
      'page' => 0,
      'curriculum' => 0,
      'profile' => 0,
      'quiz' => 0,
      'story' => 0,
      'bead' => 0,
      'reviews' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Institute',
      'weight' => '12',
      'description' => '',
      'type' => 'nodereference_select',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_published
  $fields['curriculum-field_published'] = array(
    'field_name' => 'field_published',
    'type_name' => 'curriculum',
    'display_settings' => array(
      'weight' => '19',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
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
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '1|Yes',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => NULL,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Published',
      'weight' => '19',
      'description' => 'Publish playlist to have them search-able. You can not unpublish or delete a published playlist',
      'type' => 'optionwidgets_buttons',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_reviewers
  $fields['curriculum-field_reviewers'] = array(
    'field_name' => 'field_reviewers',
    'type_name' => 'curriculum',
    'display_settings' => array(
      'weight' => '6',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
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
    'type' => 'userreference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'userreference',
    'active' => '1',
    //'referenceable_roles' => array(
    //  '5' => 5,
    //  '3' => 3,
    //  '2' => 0,
    //  '6' => 0,
    //  '7' => 0,
    //  '4' => 0,
    //),
    'referenceable_roles' => array(
      '9' => 9,
      '6' => 6,
      '2' => 0,
      '4' => 0,
      '7' => 0,
      '8' => 0,
    ),
    'referenceable_status' => '',
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'reverse_link' => 0,
      'default_value' => array(
        '0' => array(
          'uid' => NULL,
          '_error_element' => 'default_value_widget][field_reviewers][0][uid][uid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Reviewers ',
      'weight' => '6',
      'description' => '',
      'type' => 'userreference_autocomplete',
      'module' => 'userreference',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Author');
  t('Co Author');
  t('Institute');
  t('Published');
  t('Reviewers ');

  return $fields;
}
