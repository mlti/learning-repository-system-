<?php

/**
 * Implementation of hook_hierarchical_select_default_configs().
 */
function syntiro_others_hierarchical_select_default_configs() {
$configs = array();
$config = array(
  'config_id'       => 'content-taxonomy-field_mlr',
  'save_lineage'    => 1,
  'enforce_deepest' => 0,
  'entity_count'    => 0,
  'require_entity'  => 0,
  'resizable'       => 1,
  'level_labels' => array(
    'status' => 0,
    'labels' => array(
      0 => 'Select',
      1 => 'Select',
      2 => 'Select',
    ),
  ),
  'dropbox' => array(
    'status'    => 1,
    'title'     => 'All selections',
    'limit'     => 0,
    'reset_hs'  => 0,
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
    'max_levels'       => 0,
  ),
);

$configs['content-taxonomy-field_mlr'] = $config;
return $configs;
}
