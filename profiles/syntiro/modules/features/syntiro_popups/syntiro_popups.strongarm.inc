<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_popups_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'popups_always_scan';
  $strongarm->value = 1;
  $export['popups_always_scan'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'popups_autoclose_final_message';
  $strongarm->value = 0;
  $export['popups_autoclose_final_message'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'popups_educationhub_content_selector';
  $strongarm->value = '#content-section';
  $export['popups_educationhub_content_selector'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'popups_popup_final_message';
  $strongarm->value = 0;
  $export['popups_popup_final_message'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'popups_rubik_content_selector';
  $strongarm->value = 'div.left-corner > div.clear-block:last';
  $export['popups_rubik_content_selector'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'popups_skin';
  $strongarm->value = 'Basic';
  $export['popups_skin'] = $strongarm;

  return $export;
}
