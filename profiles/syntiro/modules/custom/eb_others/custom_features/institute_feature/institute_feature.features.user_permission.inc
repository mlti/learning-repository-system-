<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function institute_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: Import Course under Edubridge
  $permissions['Import Course under Edubridge'] = array(
    'name' => 'Import Course under Edubridge',
    'roles' => array(),
  );

  // Exported permission: access administration menu
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: access administration pages
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: access asset reports
  $permissions['access asset reports'] = array(
    'name' => 'access asset reports',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: access bookmark
  $permissions['access bookmark'] = array(
    'name' => 'access bookmark',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
    ),
  );

  // Exported permission: access bridge
  $permissions['access bridge'] = array(
    'name' => 'access bridge',
    'roles' => array(),
  );

  // Exported permission: access ckeditor
  $permissions['access ckeditor'] = array(
    'name' => 'access ckeditor',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: access comments
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      '0' => 'Site Admin',
      '1' => 'Student',
      '2' => 'Teacher',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
      '2' => 'Skill Instructor',
      '3' => 'Student',
      '4' => 'Teacher',
      '5' => 'authenticated user',
    ),
  );

  // Exported permission: access homepage
  $permissions['access homepage'] = array(
    'name' => 'access homepage',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: access mars
  $permissions['access mars'] = array(
    'name' => 'access mars',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
    ),
  );

  // Exported permission: access new layout
  $permissions['access new layout'] = array(
    'name' => 'access new layout',
    'roles' => array(
      '0' => 'Student',
    ),
  );

  // Exported permission: access recommend
  $permissions['access recommend'] = array(
    'name' => 'access recommend',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
    ),
  );

  // Exported permission: access search
  $permissions['access search'] = array(
    'name' => 'access search',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
    ),
  );

  // Exported permission: access site reports
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: access user profiles
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
      '2' => 'Student',
      '3' => 'Teacher',
    ),
  );

  // Exported permission: administer activities
  $permissions['administer activities'] = array(
    'name' => 'administer activities',
    'roles' => array(),
  );

  // Exported permission: administer autologout
  $permissions['administer autologout'] = array(
    'name' => 'administer autologout',
    'roles' => array(),
  );

  // Exported permission: administer bookmark
  $permissions['administer bookmark'] = array(
    'name' => 'administer bookmark',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: administer ckeditor
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(),
  );

  // Exported permission: administer content types
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
  );

  // Exported permission: administer mars
  $permissions['administer mars'] = array(
    'name' => 'administer mars',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: administer menu
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: administer nodes
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: administer permissions
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: administer users
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: allow CKFinder file uploads
  $permissions['allow CKFinder file uploads'] = array(
    'name' => 'allow CKFinder file uploads',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: assign assignments
  $permissions['assign assignments'] = array(
    'name' => 'assign assignments',
    'roles' => array(
      '0' => 'Teacher',
    ),
  );

  // Exported permission: can coauthor node
  $permissions['can coauthor node'] = array(
    'name' => 'can coauthor node',
    'roles' => array(
      '0' => 'Teacher',
    ),
  );

  // Exported permission: can review node
  $permissions['can review node'] = array(
    'name' => 'can review node',
    'roles' => array(
      '0' => 'Teacher',
    ),
  );

  // Exported permission: change own username
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: create assignment
  $permissions['create assignment'] = array(
    'name' => 'create assignment',
    'roles' => array(
      '0' => 'Teacher',
    ),
  );

  // Exported permission: create discussion content
  $permissions['create discussion content'] = array(
    'name' => 'create discussion content',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
    ),
  );

  // Exported permission: create institute content
  $permissions['create institute content'] = array(
    'name' => 'create institute content',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: delete any institute content
  $permissions['delete any institute content'] = array(
    'name' => 'delete any institute content',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: delete any profile content
  $permissions['delete any profile content'] = array(
    'name' => 'delete any profile content',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: delete any reviews content
  $permissions['delete any reviews content'] = array(
    'name' => 'delete any reviews content',
    'roles' => array(),
  );

  // Exported permission: delete own institute content
  $permissions['delete own institute content'] = array(
    'name' => 'delete own institute content',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: delete own profile content
  $permissions['delete own profile content'] = array(
    'name' => 'delete own profile content',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: delete privatemsg
  $permissions['delete privatemsg'] = array(
    'name' => 'delete privatemsg',
    'roles' => array(
      '0' => 'Skill Instructor',
      '1' => 'Student',
      '2' => 'Teacher',
    ),
  );

  // Exported permission: edit any institute content
  $permissions['edit any institute content'] = array(
    'name' => 'edit any institute content',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: edit any profile content
  $permissions['edit any profile content'] = array(
    'name' => 'edit any profile content',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: edit any reviews content
  $permissions['edit any reviews content'] = array(
    'name' => 'edit any reviews content',
    'roles' => array(),
  );

  // Exported permission: edit own bead content
  $permissions['edit own bead content'] = array(
    'name' => 'edit own bead content',
    'roles' => array(
      '0' => 'Site Admin',
    ),
  );

  // Exported permission: edit own institute content
  $permissions['edit own institute content'] = array(
    'name' => 'edit own institute content',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: export bulk nodes
  $permissions['export bulk nodes'] = array(
    'name' => 'export bulk nodes',
    'roles' => array(),
  );

  // Exported permission: export node
  $permissions['export node'] = array(
    'name' => 'export node',
    'roles' => array(),
  );

  // Exported permission: export own nodes
  $permissions['export own nodes'] = array(
    'name' => 'export own nodes',
    'roles' => array(),
  );

  // Exported permission: import users
  $permissions['import users'] = array(
    'name' => 'import users',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: manage campus
  $permissions['manage campus'] = array(
    'name' => 'manage campus',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Site Admin',
    ),
  );

  // Exported permission: post comments
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'Site Admin',
      '1' => 'Student',
      '2' => 'Teacher',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: post comments without approval
  $permissions['post comments without approval'] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: rate content
  $permissions['rate content'] = array(
    'name' => 'rate content',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
    ),
  );

  // Exported permission: read privatemsg
  $permissions['read privatemsg'] = array(
    'name' => 'read privatemsg',
    'roles' => array(
      '0' => 'Skill Instructor',
      '1' => 'Student',
      '2' => 'Teacher',
    ),
  );

  // Exported permission: score own quiz
  $permissions['score own quiz'] = array(
    'name' => 'score own quiz',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
    ),
  );

  // Exported permission: search Google CSE
  $permissions['search Google CSE'] = array(
    'name' => 'search Google CSE',
    'roles' => array(),
  );

  // Exported permission: use PHP for fivestar target
  $permissions['use PHP for fivestar target'] = array(
    'name' => 'use PHP for fivestar target',
    'roles' => array(),
  );

  // Exported permission: use PHP to import nodes
  $permissions['use PHP to import nodes'] = array(
    'name' => 'use PHP to import nodes',
    'roles' => array(
      '0' => 'Teacher',
    ),
  );

  // Exported permission: view activity meter
  $permissions['view activity meter'] = array(
    'name' => 'view activity meter',
    'roles' => array(
      '0' => 'Student',
    ),
  );

  // Exported permission: view assets
  $permissions['view assets'] = array(
    'name' => 'view assets',
    'roles' => array(
      '0' => 'Campus admin',
      '1' => 'Curl',
      '2' => 'Site Admin',
      '3' => 'Student',
      '4' => 'Teacher',
    ),
  );

  // Exported permission: view assignments
  $permissions['view assignments'] = array(
    'name' => 'view assignments',
    'roles' => array(
      '0' => 'Skill Instructor',
      '1' => 'Student',
    ),
  );

  // Exported permission: view own quiz results
  $permissions['view own quiz results'] = array(
    'name' => 'view own quiz results',
    'roles' => array(
      '0' => 'Student',
      '1' => 'Teacher',
    ),
  );

  // Exported permission: write privatemsg
  $permissions['write privatemsg'] = array(
    'name' => 'write privatemsg',
    'roles' => array(
      '0' => 'Skill Instructor',
      '1' => 'Student',
      '2' => 'Teacher',
    ),
  );

  return $permissions;
}
