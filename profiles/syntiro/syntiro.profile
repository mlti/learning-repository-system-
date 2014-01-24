<?php

/**
 * Return an array of the modules to be enabled when this profile is installed.
 *
 * @return
 *  An array of modules to be enabled.
 */
function syntiro_profile_modules() {
  $modules = array(
  //Drupal Core
   'color', 
   'comment', 
   //'dblog', 
   'menu', 
   'path', 
   'ping', 
   'statistics',
   'search', 
   'taxonomy', 
   'update', 
   'block', 
   'filter',
   'php', 
   'node', 
   'system', 
   'user', 
   'number',
   'syslog',
   
  //Contrib
  //Access Control
  'content_access', 
   
  //Administration
  'admin_menu',
  
  //Apache Solr
  'apachesolr', 
  'apachesolr_autocomplete',
  
  //CCk
  'autocomplete_widgets', 
  'content', 
  'content_copy', 
  'content_taxonomy', 
  'fieldgroup', 
  'filefield', 
  'imagefield', 
  'nodereference', 
  'number', 
  'optionwidgets', 
  'text', 
  'userreference',
  
  //CTools
  'ctools',
  
  //Clientside Validation
  'clientside_validation',
  'clientside_validation_fapi',
  'clientside_validation_form', 
  
  //Content Profile
  'content_profile',
  'content_profile_registration',
  
  //Date/Time
  'date_api',
  'date_timezone', 
  
  //Development
  'fapi_validation', 
  'node_import',
  
  //Features
  'features',
  'reviews_features', 
  
  //Form Elements
  'hierarchical_select',
  'hs_content_taxonomy',
  'hs_flatlist',
  'hs_menu',
  'hs_smallhierarchy',
  'hs_taxonomy',
  'hs_taxonomy_views',
  
  //Fusion Charts
  'fusioncharts',
  'fusioncharts_test', 
  'fusioncharts_system',
  
  //Imagecache
  'imageapi',
  'imageapi_gd',
  'imageapi_imagemagick',
  'imagecache',
  'imagecache_ui',
  
  //Mail
  'pm_block_user',
  'privatemsg',
  'pm_email_notify',
  'privatemsg_filter',
  'smtp',
  
  //Organic Groups
  'og',
  'og_access',
  'og_actions',
  'og_views',
  
  //Other
  'autoload', 
  'autologout', 
  'auto_nodetitle', 
  'block_class', 
  'flowplayer',
  'diff', 
  
  //'google_cse',
  'diff',  
  'node_export',
  'node_export_file',
  'pathauto',
  'r4032login',
  'remember_me',
  'strongarm',
  'synonyms',
  'token',
  'user_import',
    
  //Quiz Core
  'quiz',
  'quiz_question',
  
  //Quiz Question
  'multichoice',
  
  //Rules
  'rules', 
  'rules_admin',
  'rules_forms',
  'rules_scheduler',
  'rules_test',
  
  //Spam Control
  'captcha',
  'image_captcha',
  
  //Taxonomy
  'taxonomy_csv',
  
  //User Interface
  'ckeditor',
  'jquery_ui',
  'jquery_update',
  'popups',
  'popups_admin',
  'popups_test',
  
  //Userpoints
  'userpoints',
  'userpoints_login', 
  
  //Views
  'views',
  'views_customfield',
  'views_ui',
  
  //Voting
  'fivestar', 
  'fivestar_comment',
  'votingapi',
  
  //Custom
  'mars',
  'asset',
 
  'bookmark',
  'bridge',
  'cache_eb',
  'comment_location',
  'curriculum',
  'eb_hierarchical_select_ext',
  'eb_node_actions',
  'eb_others',
  'eb_search',
  'eb_user_points',
  'eb_group',
  //'eb_self_registration',
  'lom',
  'privatemsg_ext',
  'recommend',
  'reviews',
  'login_register',
  'eb_school',
  'assignment',
   
  //custom features
  'syntiro_apachesolr',
  'syntiro_asset',
  'syntiro_autologout', 
  'syntiro_bead',
  'syntiro_captcha',
  'syntiro_ckeditor',
  'syntiro_clientside_validation',
  'syntiro_community',
  'syntiro_date',
  'syntiro_discussion',
  'syntiro_eb', 
  'syntiro_fivestar',
  'syntiro_imagecache',
  'syntiro_institute',
  'syntiro_menu',
  'syntiro_node_export',
  'syntiro_og', 
  'syntiro_others',
  'syntiro_playlist',
  'syntiro_popups',
  'syntiro_private_message', 
  'syntiro_profile',
  'syntiro_theme',
  'syntiro_taxonomoy', 
  'syntiro_userpoints',
  'syntiro_user_settings', 
    
  );
  return $modules;
}

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile,
 *   and optional 'language' to override the language selection for
 *   language-specific profiles.
 */
function syntiro_profile_details() {
  return array(
    'name' => 'Syntiro',
    'description' => 'Select this profile to create My Custom Website.'
  );
}

/**
 * Reimplementation of system_theme_data(). The core function's static cache
 * is populated during install prior to active install profile awareness.
 * This workaround makes enabling themes in profiles/[profile]/themes possible.
 */
function _syntiro_system_theme_data() {
  global $profile;
  $profile = 'syntiro';

  $themes = drupal_system_listing('\.info$', 'themes');
  $engines = drupal_system_listing('\.engine$', 'themes/engines');

  $defaults = system_theme_default();

  $sub_themes = array();
  foreach ($themes as $key => $theme) {
    $themes[$key]->info = drupal_parse_info_file($theme->filename) + $defaults;

    if (!empty($themes[$key]->info['base theme'])) {
      $sub_themes[] = $key;
    }

    $engine = $themes[$key]->info['engine'];
    if (isset($engines[$engine])) {
      $themes[$key]->owner = $engines[$engine]->filename;
      $themes[$key]->prefix = $engines[$engine]->name;
      $themes[$key]->template = TRUE;
    }

    // Give the stylesheets proper path information.
    $pathed_stylesheets = array();
    foreach ($themes[$key]->info['stylesheets'] as $media => $stylesheets) {
      foreach ($stylesheets as $stylesheet) {
        $pathed_stylesheets[$media][$stylesheet] = dirname($themes[$key]->filename) .'/'. $stylesheet;
      }
    }
    $themes[$key]->info['stylesheets'] = $pathed_stylesheets;

    // Give the scripts proper path information.
    $scripts = array();
    foreach ($themes[$key]->info['scripts'] as $script) {
      $scripts[$script] = dirname($themes[$key]->filename) .'/'. $script;
    }
    $themes[$key]->info['scripts'] = $scripts;

    // Give the screenshot proper path information.
    if (!empty($themes[$key]->info['screenshot'])) {
      $themes[$key]->info['screenshot'] = dirname($themes[$key]->filename) .'/'. $themes[$key]->info['screenshot'];
    }
  }

  foreach ($sub_themes as $key) {
    $themes[$key]->base_themes = system_find_base_themes($themes, $key);
    // Don't proceed if there was a problem with the root base theme.
    if (!current($themes[$key]->base_themes)) {
      continue;
    }
    $base_key = key($themes[$key]->base_themes);
    foreach (array_keys($themes[$key]->base_themes) as $base_theme) {
      $themes[$base_theme]->sub_themes[$key] = $themes[$key]->info['name'];
    }
    // Copy the 'owner' and 'engine' over if the top level theme uses a
    // theme engine.
    if (isset($themes[$base_key]->owner)) {
      if (isset($themes[$base_key]->info['engine'])) {
        $themes[$key]->info['engine'] = $themes[$base_key]->info['engine'];
        $themes[$key]->owner = $themes[$base_key]->owner;
        $themes[$key]->prefix = $themes[$base_key]->prefix;
      }
      else {
        $themes[$key]->prefix = $key;
      }
    }
  }

}


/**
 * Return a list of tasks that this profile supports.
 *
 * @return
 *   A keyed array of tasks the profile will perform during
 *   the final stage. The keys of the array will be used internally,
 *   while the values will be displayed to the user in the installer
 *   task list.
 */
function syntiro_profile_task_list() {
}

/**
 * Perform any final installation tasks for this profile.
 *
 * The installer goes through the profile-select -> locale-select
 * -> requirements -> database -> profile-install-batch
 * -> locale-initial-batch -> configure -> locale-remaining-batch
 * -> finished -> done tasks, in this order, if you don't implement
 * this function in your profile.
 *
 * If this function is implemented, you can have any number of
 * custom tasks to perform after 'configure', implementing a state
 * machine here to walk the user through those tasks. First time,
 * this function gets called with $task set to 'profile', and you
 * can advance to further tasks by setting $task to your tasks'
 * identifiers, used as array keys in the hook_profile_task_list()
 * above. You must avoid the reserved tasks listed in
 * install_reserved_tasks(). If you implement your custom tasks,
 * this function will get called in every HTTP request (for form
 * processing, printing your information screens and so on) until
 * you advance to the 'profile-finished' task, with which you
 * hand control back to the installer. Each custom page you
 * return needs to provide a way to continue, such as a form
 * submission or a link. You should also set custom page titles.
 *
 * You should define the list of custom tasks you implement by
 * returning an array of them in hook_profile_task_list(), as these
 * show up in the list of tasks on the installer user interface.
 *
 * Remember that the user will be able to reload the pages multiple
 * times, so you might want to use variable_set() and variable_get()
 * to remember your data and control further processing, if $task
 * is insufficient. Should a profile want to display a form here,
 * it can; the form should set '#redirect' to FALSE, and rely on
 * an action in the submit handler, such as variable_set(), to
 * detect submission and proceed to further tasks. See the configuration
 * form handling code in install_tasks() for an example.
 *
 * Important: Any temporary variables should be removed using
 * variable_del() before advancing to the 'profile-finished' phase.
 *
 * @param $task
 *   The current $task of the install system. When hook_profile_tasks()
 *   is first called, this is 'profile'.
 * @param $url
 *   Complete URL to be used for a link or form action on a custom page,
 *   if providing any, to allow the user to proceed with the installation.
 *
 * @return
 *   An optional HTML string to display to the user. Only used if you
 *   modify the $task, otherwise discarded.
 */
function syntiro_profile_tasks(&$task, $url) {
 
  syntiro_config_roles();

  // Insert default user-defined node types into the database. For a complete
  // list of available node type attributes, refer to the node type API
  // documentation at: http://api.drupal.org/api/HEAD/function/hook_node_info.
  $types = array(
    array(
      'type' => 'page',
      'name' => st('Page'),
      'module' => 'node',
      'description' => st("A <em>page</em>, similar in form to a <em>story</em>, is a simple method for creating and displaying information that rarely changes, such as an \"About us\" section of a website. By default, a <em>page</em> entry does not allow visitor comments and is not featured on the site's initial home page."),
      'custom' => TRUE,
      'modified' => TRUE,
      'locked' => FALSE,
      'help' => '',
      'min_word_count' => '',
    ),
    array(
      'type' => 'story',
      'name' => st('Story'),
      'module' => 'node',
      'description' => st("A <em>story</em>, similar in form to a <em>page</em>, is ideal for creating and displaying content that informs or engages website visitors. Press releases, site announcements, and informal blog-like entries may all be created with a <em>story</em> entry. By default, a <em>story</em> entry is automatically featured on the site's initial home page, and provides the ability to post comments."),
      'custom' => TRUE,
      'modified' => TRUE,
      'locked' => FALSE,
      'help' => '',
      'min_word_count' => '',
    ),
  );

  foreach ($types as $type) {
    $type = (object) _node_type_set_defaults($type);
    node_type_save($type);
  }

  // Default page to not be promoted and have comments disabled.
  variable_set('node_options_page', array('status'));
  variable_set('comment_page', COMMENT_NODE_DISABLED);

  // Don't display date and author information for page nodes by default.
  $theme_settings = variable_get('theme_settings', array());
  $theme_settings['toggle_node_info_page'] = FALSE;
  variable_set('theme_settings', $theme_settings);

  // Clear caches.
  drupal_flush_all_caches();
 
  // Enable the right theme. This must be handled after drupal_flush_all_caches()
  // which rebuilds the system table based on a stale static cache,
  // blowing away our changes.
  _syntiro_system_theme_data();
  db_query("UPDATE {system} SET status = 0 WHERE type = 'theme'");
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' AND name = 'garland'");
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' AND name = 'educationhub'");
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' AND name = 'tao'");
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' AND name = 'rubik'");
  db_query("UPDATE {blocks} SET region = '' WHERE theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'footer_upper_right' WHERE module = 'eb_others' AND delta = '0' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'header_login' WHERE module = 'block' AND delta = '5' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'header_middle' WHERE module = 'eb_search' AND delta = '1' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'footer' WHERE module = 'menu' AND delta = 'menu-footer-menu' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'footer' WHERE module = 'menu' AND delta = 'menu-bridge' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'content_bottom' WHERE module = 'eb_search' AND delta = '4' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'right' WHERE module = 'eb_search' AND delta = '5' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'bridge' AND delta = '0' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'eb_search' AND delta = '3' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'views' AND delta = 'curriculum_info_new_block_1' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'views' AND delta = 'bead_info_block_1' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'assignment' AND delta = '3' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'views' AND delta = 'communityinterest_info_block_1' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'eb_group' AND delta = '0' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'bridge' AND delta = '1' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'block' AND delta = '8' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'block' AND delta = '9' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'block' AND delta = '10' AND theme = 'educationhub'");
  db_query("UPDATE {blocks} SET status = 1, region = 'left' WHERE module = 'views' AND delta = 'og_members_faces_block_1' AND theme = 'educationhub'"); 
  
  //Insert block-class table
  db_query("INSERT INTO {block_class} (`module`, `delta`, `css_class`) VALUES ('bridge',9,'sidebar-info-block')");
  db_query("INSERT INTO {block_class} (`module`, `delta`, `css_class`) VALUES ('eb_others',3,'followus-link')");
  db_query("INSERT INTO {block_class} (`module`, `delta`, `css_class`) VALUES ('bridge',0,'sidebar-info-block')");
  db_query("INSERT INTO {block_class} (`module`, `delta`, `css_class`) VALUES ('eb_others',0,'followus-link')");
  
  //Insert block-roles table
  db_query("INSERT INTO {blocks_roles} (`module`, `delta`, `rid`) VALUES ('user',0,1)");
  db_query("INSERT INTO {blocks_roles} (`module`, `delta`, `rid`) VALUES ('og',0,6)");
  db_query("INSERT INTO {blocks_roles} (`module`, `delta`, `rid`) VALUES ('bridge',1,9)");
  db_query("INSERT INTO {blocks_roles} (`module`, `delta`, `rid`) VALUES ('bridge',0,9)");
  db_query("INSERT INTO {blocks_roles} (`module`, `delta`, `rid`) VALUES ('bridge',1,8)");
  db_query("INSERT INTO {blocks_roles} (`module`, `delta`, `rid`) VALUES ('bridge',0,8)");
  db_query("INSERT INTO {blocks_roles} (`module`, `delta`, `rid`) VALUES ('block',5,1)");
  
  variable_set('theme_default', 'educationhub');
  variable_set('admin_theme', 'rubik');
  variable_set('node_admin_theme', 0);
 
}
//INSERT INTO permission (rid, perm, tid) VALUES (5, 'view assets', 0)
/**
 * Configure roles and permissions
 */
function syntiro_config_roles() {
   // New Register
  //db_query("INSERT INTO {role} (rid, name) VALUES (3, 'new register')");
  // Campus Admin
  db_query("INSERT INTO {role} (rid, name) VALUES (4, 'Campus admin')");
   // Curl
  db_query("INSERT INTO {role} (rid, name) VALUES (5, 'Curl')");
   // Site Admin
  db_query("INSERT INTO {role} (rid, name) VALUES (6, 'Site Admin')");
   // Skill Instructor
  db_query("INSERT INTO {role} (rid, name) VALUES (7, 'Skill Instructor')");
   // Student
  db_query("INSERT INTO {role} (rid, name) VALUES (8, 'Student')");
   // Teacher
  db_query("INSERT INTO {role} (rid, name) VALUES (9, 'Teacher')");
  
  // Make sure first user is a "Teacher"
  db_query("INSERT INTO {users_roles} (uid, rid) VALUES (1, 9)");
  
  // Configure default permissions for each role
  db_query("UPDATE {permission} SET perm = 'access homepage, administer mars, search content' WHERE rid = 1");
  db_query("UPDATE {permission} SET perm = 'access homepage, access ckeditor, allow CKFinder file uploads, access comments, post comments, post comments without approval, administer mars, access content, access quiz, search content' WHERE rid = 2");

  //Insert Permissions

  $ca_array = array('access administration menu, view assets, manage campus, access content, create institute content, delete any institute content, delete own institute content, edit any institute content, edit own institute content, access administration pages, access user profiles, administer permissions, administer users, import users');
  $campus_admin = implode(",", $ca_array);
  
  $curl_array = array('view assets');
  $curl = implode(",",$curl_array);
  
  $sa_array = array('access administration menu, access asset reports, view assets, administer bookmark, access comments, post comments, view curriculum content, manage campus, delete own reviews content, edit own reviews content, administer menu, access content, administer nodes, create asset content, create bead content, create community_interest_group content, create curriculum content, create institute content, create profile content, create story content, delete any asset content, delete any institute content, delete any page content, delete any profile content, delete any story content, delete own asset content, delete own community_interest_group content, delete own curriculum content, delete own institute content, delete own page content, delete own profile content, delete own story content, edit any asset content, edit any bead content, edit any institute content, edit any page content, edit any profile content, edit any story content, edit own asset content, edit own bead content, edit own community_interest_group content, edit own curriculum content, edit own institute content, edit own page content, edit own profile content, edit own story content, access quiz, administer recommend, access administration pages, access site reports, administer taxonomy, access user profiles, administer permissions, administer users, change own username, import users');
  $site_admin = implode(",",$sa_array);
  
  $si_array = array('view assignments, access content, delete privatemsg, read privatemsg, write privatemsg');
  $skill_instructor = implode(",",$si_array);
  
  $student_array = array('view assets, view assignments, access bookmark, access new layout, access ckeditor, allow CKFinder file uploads, access comments, post comments, access search, view activity meter, rate content, access mars, access content, create community_interest_group content, create discussion content, create profile content, delete own community_interest_group content, delete own page content, edit own community_interest_group content, edit own discussion content, edit own profile content, delete privatemsg, read privatemsg, write privatemsg, private message list, filter private messages, score own quiz, view own quiz results, access recommend, access user profiles, earn login points');
  $student = implode(",",$student_array);
  
  $teacher_array = array('can coauthor node, can review node, view assets, assign assignments, create assignment, access bookmark, access ckeditor, allow CKFinder file uploads, access comments, post comments, view curriculum content, access search, create reviews content, delete own reviews content, edit own reviews content, rate content, access mars, access content, create asset content, create bead content, create community_interest_group content, create curriculum content, create discussion content, create profile content, delete any bead content, delete any story content, delete own asset content, delete own bead content, delete own community_interest_group content, delete own curriculum content, delete own page content, edit own asset content, edit own community_interest_group content, edit own curriculum content, edit own discussion content, edit own profile content, use PHP to import nodes, delete privatemsg, read privatemsg, write privatemsg, private message list, filter private messages, access quiz, administer quiz configuration, assign any action to quiz events, create quiz, delete own quiz, delete results for own quiz, edit own quiz, edit question titles, score own quiz, view own quiz results, view quiz question outside of a quiz, view results for own quiz, access recommend, administer recommend, access user profiles, earn login points');
  $teacher = implode(",",$teacher_array);
  
  
  db_query("INSERT INTO {permission} (rid, perm, tid) VALUES (4,'$campus_admin',0)");
  db_query("INSERT INTO {permission} (rid, perm, tid) VALUES (5,'$curl',0)");
  db_query("INSERT INTO {permission} (rid, perm, tid) VALUES (6,'$site_admin',0)");
  db_query("INSERT INTO {permission} (rid, perm, tid) VALUES (7,'$skill_instructor',0)");
  db_query("INSERT INTO {permission} (rid, perm, tid) VALUES (8,'$student',0)");
  db_query("INSERT INTO {permission} (rid, perm, tid) VALUES (9,'$teacher',0)");
}

/**
 * Alter the install profile configuration form and provide timezone loc
 
/**
 * Implementation of hook_form_alter().
 *
 * Allows the profile to alter the site-configuration form. This is
 * called through custom invocation, so $form_state is not populated.
 */
function syntiro_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'install_configure') {
    // Set default for site name field.
    $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
  }
}
