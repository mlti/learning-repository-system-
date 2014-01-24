<?php

/**
 * Implementation of hook_node_info().
 */
function reviews_features_node_info() {
  $items = array(
    'reviews' => array(
      'name' => t('reviews'),
      'module' => 'features',
      'description' => t('Reviews '),
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
