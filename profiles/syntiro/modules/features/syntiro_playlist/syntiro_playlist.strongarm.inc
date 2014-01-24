<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_playlist_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_curriculum';
  $strongarm->value = 0;
  $export['comment_anonymous_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_curriculum';
  $strongarm->value = '3';
  $export['comment_controls_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_curriculum';
  $strongarm->value = '2';
  $export['comment_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_curriculum';
  $strongarm->value = '4';
  $export['comment_default_mode_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_curriculum';
  $strongarm->value = '1';
  $export['comment_default_order_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_curriculum';
  $strongarm->value = '50';
  $export['comment_default_per_page_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_curriculum';
  $strongarm->value = '2';
  $export['comment_form_location_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_curriculum';
  $strongarm->value = '0';
  $export['comment_preview_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_curriculum';
  $strongarm->value = '0';
  $export['comment_subject_field_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_curriculum';
  $strongarm->value = array(
    'title' => '7',
    'body_field' => '8',
    'revision_information' => '14',
    'author' => '15',
    'options' => '16',
    'comment_settings' => '18',
    'menu' => '13',
    'taxonomy' => '9',
    'path' => '17',
    'attachments' => '20',
  );
  $export['content_extra_weights_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_curriculum';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_curriculum'] = $strongarm;

  return $export;
}
