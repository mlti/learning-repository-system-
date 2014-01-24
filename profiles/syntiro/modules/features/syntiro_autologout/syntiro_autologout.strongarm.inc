<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_autologout_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout';
  $strongarm->value = array(
    'enabled' => 1,
    'timeout' => '1200',
    'use_watchdog' => 1,
    'authenticated user' => '2',
    'Campus admin' => '0',
    'Curl' => '0',
    'New register' => '0',
    'Site Admin' => '2',
    'Skill Instructor' => '0',
    'Student' => '2',
    'Teacher' => '2',
    'logout_message' => 'You have been automatically logged out due to inactivity',
    'redirect_url' => 'user/login',
    'refresh_delta' => '0',
  );
  $export['autologout'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_one_session';
  $strongarm->value = array(
    'authenticated user' => '0',
    'Campus admin' => '0',
    'Curl' => '0',
    'New register' => '0',
    'Site Admin' => '0',
    'Skill Instructor' => '0',
    'Student' => '0',
    'Teacher' => '0',
  );
  $export['autologout_one_session'] = $strongarm;

  return $export;
}
