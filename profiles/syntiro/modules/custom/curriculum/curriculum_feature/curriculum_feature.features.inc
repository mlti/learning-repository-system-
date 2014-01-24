<?php

/**
 * Implementation of hook_node_info().
 */
function curriculum_feature_node_info() {
  $items = array(
    'curriculum' => array(
      'name' => t('Playlist'),
      'module' => 'features',
      'description' => t('Please update information about your Playlist here. Using proper Description and tags will better search enable your playlist in Edubridge.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => t('Please update information about your Playlist here. Using proper Description and tags will better search enable your playlist in Edubridge.'),
    ),
  );
  return $items;
}
