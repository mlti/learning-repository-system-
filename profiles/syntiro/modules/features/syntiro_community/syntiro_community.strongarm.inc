<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_community_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_community_interest_group';
  $strongarm->value = 0;
  $export['comment_anonymous_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_community_interest_group';
  $strongarm->value = '0';
  $export['comment_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_community_interest_group';
  $strongarm->value = '3';
  $export['comment_controls_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_community_interest_group';
  $strongarm->value = '4';
  $export['comment_default_mode_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_community_interest_group';
  $strongarm->value = '2';
  $export['comment_default_order_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_community_interest_group';
  $strongarm->value = '50';
  $export['comment_default_per_page_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_community_interest_group';
  $strongarm->value = '0';
  $export['comment_form_location_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_community_interest_group';
  $strongarm->value = '1';
  $export['comment_preview_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_community_interest_group';
  $strongarm->value = '1';
  $export['comment_subject_field_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_community_interest_group';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '4',
    'author' => '3',
    'options' => '5',
    'comment_settings' => '8',
    'menu' => '-3',
    'path' => '6',
    'attachments' => '7',
    'og_description' => '-4',
    'og_selective' => '0',
    'og_register' => '-2',
    'og_directory' => '-1',
    'og_private' => '1',
  );
  $export['content_extra_weights_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_community_interest_group';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_community_interest_group';
  $strongarm->value = '1';
  $export['upload_community_interest_group'] = $strongarm;

  return $export;
}
