<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function syntiro_asset_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function syntiro_asset_node_info() {
  $items = array(
    'asset' => array(
      'name' => t('Asset'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => t('Please take the time to fill all relevant meta information into this form. This information will be useful when the content is being searched in the system.'),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function syntiro_asset_views_api() {
  return array(
    'api' => '2',
  );
}
