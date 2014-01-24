<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function syntiro_institute_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function syntiro_institute_imagecache_default_presets() {
  $items = array(
    'members_87' => array(
      'presetname' => 'members_87',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '87',
            'height' => '87',
            'upscale' => 0,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function syntiro_institute_node_info() {
  $items = array(
    'institute' => array(
      'name' => t('Institute'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name of Institute'),
      'has_body' => '1',
      'body_label' => t('About Institute'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
