<?php
// $Id: bridge_block.inc,  25/08/2011 4:09:PM Exp Jaffar $
/**
 * @file
 * Handling left side block for Student home page.
 */

/**
 *  It contains left side menu
 *
 * @see theme_menu_left_side_block().
 * @todo Bring MARS links form MARS module... Private Messages Dynamic
 */
function menu_leftside_block() {
  global $user;
  $results = array();
  
  if (user_access('create community_interest_group content')) {
    $results['menu_list'][] = l('Communities','communities/list');
  }
  if (user_access('create curriculum content')) {
    $results['menu_list'][] = l('Reports','assignment/reports/list');
  }
  if (user_access('read privatemsg')) {
    $results['menu_list'][] = l('Messages','messages/inbox');
  }
  if (user_access('access mars') && function_exists("mars_block_form")) {
    $results['menu_list'][] = l('MARS','bridge/mymars');
  }
  if (user_access('access bookmark') && function_exists("bookmark_block_form")) {
    $results['menu_list'][] = l('Bookmarks','bridge/mybookmarks');
  }
  if (user_access('access recommend') && function_exists("recommend_block_form")) {
    $results['menu_list'][] = l('Recommendations','bridge/myrecommendations');
  }
  if (user_access('create asset content') && function_exists("myasset_basket_form")) {
    $results['menu_list'][] = l('Assets','bridge/myassets');
  }
  module_load_include('inc', 'assignment', 'includes/assignment_form');
  if (user_access('view assignments')  && function_exists("assignment_block_form")) {
    $results['menu_list'][] = l('Assignments','bridge/myassignments');
  } 
  return theme('menu_leftside_block', $results);
}

/**
 * It contians My bridge Basket list
 *
 *
 * @see theme_my_bridge().
 */
function my_bridge() {
  global $user;
  // to check weather a function exist or not to avoid function error.
  $results = array();
  $flag = 0;
  $node = node_load(arg(1));
  //Adding preview class for Asset content, Curriculum content edit page.
  drupal_add_js('jQuery(document).ready(function () { jQuery("fieldset legend").click(function() {
                var fieldset = $(this.parentNode);
                var content = $("> form:not(.action)", fieldset);
                if ($(fieldset).is(".collapsed")) {
                  content.show();
                  $(fieldset).removeClass("collapsed");
                }else{
                  content.hide();
                  $(fieldset).addClass("collapsed");
                } 
                }); });', 'inline');
  if(($node->type == 'asset' && arg(2) == 'content') || ($node->type == 'curriculum' && function_exists("view_asset_curriculum_access") && view_asset_curriculum_access($node))){
    $results['preview_class'] = 'bridge-preview';
  }
  if (user_access('access mars') && function_exists("mars_block_form")) {
    $results['mybridge_list'][0]['active_class'] = NULL;
    $results['mybridge_list'][0]['title'] = '<a href="#">MARS</a>';
    $results['mybridge_list'][0]['content'] = drupal_get_form("mars_block_form");
    $flag = 1;
  }
  if (user_access('access bookmark') && function_exists("bookmark_block_form")) {
    $results['mybridge_list'][1]['active_class'] = NULL;
    $results['mybridge_list'][1]['title'] = '<a href="#">Bookmarks</a>';
    $results['mybridge_list'][1]['content'] = drupal_get_form("bookmark_block_form");
    $flag = 1;
  }
  if (user_access('access recommend') && function_exists("recommend_block_form")) {
    $results['mybridge_list'][2]['active_class'] = NULL;
    $results['mybridge_list'][2]['title'] = '<a href="#">Recommendations</a>';
    $results['mybridge_list'][2]['content'] = drupal_get_form("recommend_block_form");
    $flag = 1;
  }
  if (user_access('create asset content') && function_exists("myasset_basket_form")) {
    module_load_include('inc', 'asset', 'includes/asset');
    $results['mybridge_list'][3]['active_class'] = NULL;
    $results['mybridge_list'][3]['title'] = '<a href="#">Assets</a>';
    $results['mybridge_list'][3]['content'] = drupal_get_form("myasset_basket_form");
    $flag = 1;
  }
  $node = function_exists("custom_node_load")?custom_node_load():NULL;
  if ((function_exists("view_asset_curriculum_access") && $node->type == "curriculum") || ($node->type == "asset" && arg(2) == "content")) {
    if (view_asset_curriculum_access($node)) {
      $results['bridge_bg'] = 'drag-drop-bg';
    }
  }
  module_load_include('inc', 'eb_search', 'includes/eb_search');
  if ((($node->type == 'asset' || ($node->type == 'bead' && arg(3) == 'html')) && arg(2) == 'content')  || ($node->type == 'curriculum' && function_exists("view_asset_curriculum_access") && view_asset_curriculum_access($node)) && user_access('access search') && function_exists("getSolrSearchform_right")) {
    $results['mybridge_list'][4]['title'] = '<a href="#" class="search-basket">Find</a>';
    $results['mybridge_list'][4]['content'] =  drupal_get_form('getSolrSearchform_right');
    $flag = 1;
  }
  module_load_include('inc', 'assignment', 'includes/assignment_form');
  if (user_access('view assignments')  && function_exists("assignment_block_form")) {
    drupal_add_js(drupal_get_path('module', 'assignment') . '/js/assignment_report.js');
    $results['mybridge_list'][5]['active_class'] = NULL;
    $results['mybridge_list'][5]['title'] = '<a href="#">Assignments</a>';
    $results['mybridge_list'][5]['content'] = drupal_get_form("assignment_block_form");
    $flag = 1;
  }
  if ($flag == 1) {
    $results['title']['mybridge'] = 'Bridge';
  }
  if (user_access('view curriculum content') && function_exists("mycurriculum_basket_form")) {
    module_load_include('inc', 'curriculum', 'includes/curriculum');
    $results['title']['myplaylist'] = 'Playlists';
    $results['mybridge_list2']['mycurriculum'] = l('Recently Added','bridge/mycurriculum');
    $results['mybridge_list2']['curriculum_content'] = drupal_get_form("mycurriculum_basket_form");
     $node = node_load(arg(1));
    if($node->type == 'curriculum' && ($node->uid == $user->uid || $node->field_author[0]['uid'] == $user->uid) && $node->field_published[0]['value'] == 0 && !user_access("administer nodes")) {
      $results['mybridge_list2']['bridge_actions'] = l("Add",'', array("attributes" => array("class" => "action-add", "title" => "add"))) . l("Remove","node/". $node->nid . '/delete', array("attributes" => array("class" => "action-remove popups-form-reload", "on-popups-options" => "{hijackDestination:'FALSE'}", "title" => "Remove" ))) ;
    }
    else {
      $results['mybridge_list2']['bridge_actions'] = l("Add",'', array("attributes" => array("class" => "action-add", "title" => "add"))) . '<span class="action-remove action-remove-disable">Remove</span>';
    }
  }
  // for active class
  if (arg(0) == "bridge") {
    switch (arg(1)) {
      case 'mymars':
        $results['mybridge_list'][0]['active_class'] = "active";
        break;
      case 'mybookmarks':
        $results['mybridge_list'][1]['active_class'] = "active";
        break;
      case 'myrecommendations':
        $results['mybridge_list'][2]['active_class'] = "active";
        break;
      case 'myassets':
        $results['mybridge_list'][3]['active_class'] = "active";
        break;
      case 'myassignments':
        $results['mybridge_list'][5]['active_class'] = "active";
        break;
    }
  }
  if (!user_access("create curriculum content") && !user_access("create asset content")) {
    $results['drag_disable'] = ' drag-disable';
  }
  return theme('my_bridge', $results);
}
