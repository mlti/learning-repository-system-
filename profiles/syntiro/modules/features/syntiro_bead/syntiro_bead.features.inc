<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function syntiro_bead_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function syntiro_bead_node_info() {
  $items = array(
    'bead' => array(
      'name' => t('bead'),
      'module' => 'features',
      'description' => t('Bead created by Site admin'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function syntiro_bead_views_api() {
  return array(
    'api' => '2',
  );
}
