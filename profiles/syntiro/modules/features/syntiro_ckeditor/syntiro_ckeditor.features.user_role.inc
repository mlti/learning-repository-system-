<?php

/**
 * Implementation of hook_user_default_roles().
 */
function syntiro_ckeditor_user_default_roles() {
  $roles = array();

  // Exported role: Site Admin
  $roles['Site Admin'] = array(
    'name' => 'Site Admin',
  );

  // Exported role: Teacher
  $roles['Teacher'] = array(
    'name' => 'Teacher',
  );

  return $roles;
}
