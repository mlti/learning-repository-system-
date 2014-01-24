<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function syntiro_discussion_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function syntiro_discussion_node_info() {
  $items = array(
    'discussion' => array(
      'name' => t('Discussion'),
      'module' => 'features',
      'description' => t('Discussion'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
