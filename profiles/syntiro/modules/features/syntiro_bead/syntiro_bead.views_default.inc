<?php

/**
 * Implementation of hook_views_default_views().
 */
function syntiro_bead_views_default_views() {
  $views = array();

  // Exported view: bead_info
  $view = new view;
  $view->name = 'bead_info';
  $view->description = 'Bead Information';
  $view->tag = '';
  $view->base_table = 'node';
  $view->core = 0;
  $view->api_version = '2';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
    ),
  ));
  $handler->override_option('arguments', array(
    'nid' => array(
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('css_class', 'sidebar-info-block');
  $handler->override_option('header', '<?php
$edit_link = NULL;
if (arg(0) == \'node\' && is_numeric(arg(1))) {
  $node = node_load(arg(1));
  if (view_asset_curriculum_access($node)) {
  $edit_link = l("Edit", \'node/\' . arg(1) . \'/edit\', array(\'attributes\' =>array(\'class\' => \' manual-edit\', \'on-popups-options\' => \'{updateSource:"final"}\')));
}
} else if (arg(0) == \'comment\' && arg(1) == \'edit\' && is_numeric(arg(2))) {
$nid = db_result(db_query("SELECT nid FROM comments WHERE cid=%d", arg(2)));
$node = node_load($nid);
if (view_asset_curriculum_access($node)) {
  $edit_link = l("Edit", \'node/\' . $nid . \'/edit\', array(\'attributes\' =>array(\'class\' => \' manual-edit\', \'on-popups-options\' => \'{updateSource:"final"}\')));
}
}

print "<div class=\'title-bg\'><h2>Info</h2>" . $edit_link  . "</div>";

?>');
  $handler->override_option('header_format', '3');
  $handler->override_option('header_empty', 0);
  $handler->override_option('row_plugin', 'node');
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_source_id_value' => array(
      'label' => 'Document ID',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_source_id_value',
      'table' => 'node_data_field_source_id',
      'field' => 'field_source_id_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_source_value' => array(
      'label' => 'Source',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_source_value',
      'table' => 'node_data_field_source',
      'field' => 'field_source_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_format_value' => array(
      'label' => 'Format',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_format_value',
      'table' => 'node_data_field_format',
      'field' => 'field_format_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_language_value' => array(
      'label' => 'Language',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_language_value',
      'table' => 'node_data_field_language',
      'field' => 'field_language_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'tid' => array(
      'label' => 'Tags',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'ebsearch/results/[tid] /?filters=type:bead&solrsort=ps_score_content desc',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'link_to_taxonomy' => 0,
      'limit' => 1,
      'vids' => array(
        4 => 4,
        9 => 0,
        1 => 0,
        3 => 0,
        8 => 0,
        6 => 0,
        5 => 0,
        7 => 0,
      ),
      'exclude' => 0,
      'id' => 'tid',
      'table' => 'term_node',
      'field' => 'tid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'tid_1' => array(
      'label' => 'Academic Level',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'ebsearch/results/[tid_1]?filters=type:bead&solrsort=ps_score_content%20desc',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'link_to_taxonomy' => 0,
      'limit' => 1,
      'vids' => array(
        9 => 9,
        1 => 0,
        3 => 0,
        8 => 0,
        6 => 0,
        5 => 0,
        4 => 0,
        7 => 0,
      ),
      'exclude' => 0,
      'id' => 'tid_1',
      'table' => 'term_node',
      'field' => 'tid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'tid_2' => array(
      'label' => ' Asset Category',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'ebsearch/results/[tid_2]?filters=type:bead&solrsort=ps_score_content%20desc',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'link_to_taxonomy' => 0,
      'limit' => 1,
      'vids' => array(
        1 => 1,
        9 => 0,
        3 => 0,
        8 => 0,
        6 => 0,
        5 => 0,
        4 => 0,
        7 => 0,
      ),
      'exclude' => 0,
      'id' => 'tid_2',
      'table' => 'term_node',
      'field' => 'tid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'tid_3' => array(
      'label' => 'Subject',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'ebsearch/results/[tid_3]?filters=type:bead%20AND%20tm_subject:[tid_1]',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'link_to_taxonomy' => 0,
      'limit' => 1,
      'vids' => array(
        7 => 7,
        9 => 0,
        1 => 0,
        3 => 0,
        8 => 0,
        6 => 0,
        5 => 0,
        4 => 0,
      ),
      'exclude' => 0,
      'id' => 'tid_3',
      'table' => 'term_node',
      'field' => 'tid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_bead_author_value' => array(
      'label' => 'Author',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_bead_author_value',
      'table' => 'node_data_field_bead_author',
      'field' => 'field_bead_author_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'php',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        2 => 0,
        3 => 0,
        4 => 0,
        5 => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => 'if (is_numeric(arg(1)) && arg(0) == \'node\') {
$nid = arg(1);
return $nid;
} else if (arg(0) == \'comment\' && arg(1) == \'edit\' && is_numeric(arg(2))) {
 $nid = db_result(db_query("SELECT nid FROM comments WHERE cid=%d", arg(2)));
return $nid;
}',
      'validate_argument_node_type' => array(
        'reviews' => 0,
        'asset' => 0,
        'bead' => 0,
        'community_interest_group' => 0,
        'curriculum' => 0,
        'discussion' => 0,
        'page' => 0,
        'profile' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        7 => 0,
        5 => 0,
        6 => 0,
        2 => 0,
        4 => 0,
        3 => 0,
        1 => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
      'validate_argument_group_node_type' => array(
        'community_interest_group' => 0,
      ),
      'validate_argument_php' => '',
      'default_taxonomy_tid_term_page' => 0,
      'default_taxonomy_tid_node' => 0,
      'default_taxonomy_tid_limit' => 0,
      'default_taxonomy_tid_vids' => array(
        7 => 0,
        5 => 0,
        6 => 0,
        2 => 0,
        4 => 0,
        3 => 0,
        1 => 0,
      ),
    ),
  ));
  $handler->override_option('header', '<div class=\'title-bg\'><h2>Info</h2></div>');
  $handler->override_option('row_plugin', 'fields');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);

  $views[$view->name] = $view;

  return $views;
}
