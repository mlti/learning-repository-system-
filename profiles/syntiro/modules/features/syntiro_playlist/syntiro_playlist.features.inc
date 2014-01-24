<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function syntiro_playlist_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function syntiro_playlist_node_info() {
  $items = array(
    'curriculum' => array(
      'name' => t('Playlist'),
      'module' => 'features',
      'description' => t('Please update information
 about your Playlist here. Using proper Description and tags will better search enable your playlist in Edubridge.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => t('Please update information about your Playlist here. Using proper Description and tags will better search 
enable your playlist in Edubridge.'),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function syntiro_playlist_views_api() {
  return array(
    'api' => '2',
  );
}
