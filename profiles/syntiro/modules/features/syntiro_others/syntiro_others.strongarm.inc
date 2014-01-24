<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_others_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache';
  $strongarm->value = '1';
  $export['cache'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hs_config_content-taxonomy-field_mlr';
  $strongarm->value = array(
    'config_id' => 'content-taxonomy-field_mlr',
    'save_lineage' => '1',
    'enforce_deepest' => '0',
    'entity_count' => '0',
    'require_entity' => '0',
    'resizable' => '1',
    'level_labels' => array(
      'status' => 0,
      'labels' => array(
        0 => 'Select',
        1 => 'Select',
        2 => 'Select',
      ),
    ),
    'dropbox' => array(
      'status' => 1,
      'title' => 'All selections',
      'limit' => '0',
      'reset_hs' => '0',
    ),
    'editability' => array(
      'status' => 0,
      'item_types' => array(
        0 => '',
        1 => '',
        2 => '',
      ),
      'allowed_levels' => array(
        0 => 1,
        1 => 1,
        2 => 1,
      ),
      'allow_new_levels' => 0,
      'max_levels' => '0',
    ),
  );
  $export['hs_config_content-taxonomy-field_mlr'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hs_menu_resizable';
  $strongarm->value = '0';
  $export['hs_menu_resizable'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_compression_type';
  $strongarm->value = 'none';
  $export['jquery_update_compression_type'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_replace';
  $strongarm->value = TRUE;
  $export['jquery_update_replace'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_cache_max_age';
  $strongarm->value = '0';
  $export['page_cache_max_age'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_compression';
  $strongarm->value = '0';
  $export['page_compression'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_asset';
  $strongarm->value = 1;
  $export['recommend_asset'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_bead';
  $strongarm->value = 1;
  $export['recommend_bead'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_body';
  $strongarm->value = '!url

Recommended by,
!name';
  $export['recommend_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_community_interest_group';
  $strongarm->value = 0;
  $export['recommend_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_curriculum';
  $strongarm->value = 0;
  $export['recommend_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_discussion';
  $strongarm->value = 0;
  $export['recommend_discussion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_institute';
  $strongarm->value = 0;
  $export['recommend_institute'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_page';
  $strongarm->value = 0;
  $export['recommend_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_profile';
  $strongarm->value = 0;
  $export['recommend_profile'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_quiz';
  $strongarm->value = 1;
  $export['recommend_quiz'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_reviews';
  $strongarm->value = 0;
  $export['recommend_reviews'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recommend_subject';
  $strongarm->value = '!title';
  $export['recommend_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'remember_me_checkbox';
  $strongarm->value = 1;
  $export['remember_me_checkbox'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'remember_me_lifetime';
  $strongarm->value = '604800';
  $export['remember_me_lifetime'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'remember_me_managed';
  $strongarm->value = 1;
  $export['remember_me_managed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'remember_me_phantom_session';
  $strongarm->value = 0;
  $export['remember_me_phantom_session'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_footer';
  $strongarm->value = '<div class="copyright">&copy;Syntiro 2013</div>';
  $export['site_footer'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_offline_message';
  $strongarm->value = '<div class="site-ofline-block"><img src="/profiles/syntiro/themes/educationhub/images/site-ofline-img.png" title="Site Under Maintenance" alt="Site Under Maintenance" />
<h2>Site Under Maintenance</h2>
<p>We will return shortly!</p>
</div>';
  $export['site_offline_message'] = $strongarm;

  return $export;
}
