<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_theme_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_educationhub_settings';
  $strongarm->value = array(
    'toggle_logo' => 1,
    'toggle_name' => 0,
    'toggle_slogan' => 0,
    'toggle_mission' => 1,
    'toggle_node_user_picture' => 0,
    'toggle_comment_user_picture' => 0,
    'toggle_search' => 0,
    'toggle_favicon' => 1,
    'toggle_primary_links' => 1,
    'toggle_secondary_links' => 1,
    'default_logo' => 0,
    'logo_path' => 'profiles/syntiro/themes/educationhub/images/educationhub_logo.jpg',
    'logo_upload' => '',
    'default_favicon' => 0,
    'favicon_path' => 'profiles/syntiro/themes/educationhub/images/educationhub_favicon.ico',
    'favicon_upload' => '',
    'popups_content_selector' => '#content-section',
    'popups_theme' => 'educationhub',
  );
  $export['theme_educationhub_settings'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_rubik_settings';
  $strongarm->value = array(
    'toggle_logo' => 1,
    'toggle_name' => 1,
    'toggle_slogan' => 0,
    'toggle_mission' => 1,
    'toggle_node_user_picture' => 0,
    'toggle_comment_user_picture' => 0,
    'toggle_search' => 0,
    'toggle_favicon' => 1,
    'toggle_primary_links' => 1,
    'toggle_secondary_links' => 1,
    'default_logo' => 0,
    'logo_path' => 'profiles/syntiro/themes/educationhub/images/educationhub_logo.jpg',
    'logo_upload' => '',
    'default_favicon' => 0,
    'favicon_path' => 'profiles/syntiro/themes/educationhub/images/educationhub_favicon.ico',
    'favicon_upload' => '',
    'popups_content_selector' => 'div.left-corner > div.clear-block:last',
    'popups_theme' => 'rubik',
  );
  $export['theme_rubik_settings'] = $strongarm;

  return $export;
}
