<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function syntiro_community_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function syntiro_community_node_info() {
  $items = array(
    'community_interest_group' => array(
      'name' => t('Community'),
      'module' => 'features',
      'description' => t('Groups'),
      'has_title' => '1',
      'title_label' => t('Community Name'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function syntiro_community_views_api() {
  return array(
    'api' => '2',
  );
}
