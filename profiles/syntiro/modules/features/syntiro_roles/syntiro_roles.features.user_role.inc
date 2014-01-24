<?php

/**
 * Implementation of hook_user_default_roles().
 */
function syntiro_roles_user_default_roles() {
  $roles = array();

  // Exported role: Campus admin
  $roles['Campus admin'] = array(
    'name' => 'Campus admin',
  );

  // Exported role: Curl
  $roles['Curl'] = array(
    'name' => 'Curl',
  );

  // Exported role: Site Admin
  $roles['Site Admin'] = array(
    'name' => 'Site Admin',
  );

  // Exported role: Skill Instructor
  $roles['Skill Instructor'] = array(
    'name' => 'Skill Instructor',
  );

  // Exported role: Student
  $roles['Student'] = array(
    'name' => 'Student',
  );

  // Exported role: Teacher
  $roles['Teacher'] = array(
    'name' => 'Teacher',
  );

  return $roles;
}
