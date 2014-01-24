<?php
// $Id$

/**
 * @file
 * Themeable functions for Google Custom Search Engine.
 */

/**
 * The search results page can be themed/customized. This is the
 * function for theming the JavaScript/Frame version of results page.
 */
function template_preprocess_google_cse_results(&$variables) {
  $query = array(
    'q' => isset($_GET['query']) ? $_GET['query'] : '',
    'cx' => variable_get('google_cse_cx', ''),
    'cof' => variable_get('google_cse_cof_google', 'FORID:0'),
    'sitesearch' => google_cse_sitesearch_default(),
  ) + google_cse_advanced_settings();

  $variables['results_searchbox_form'] = $variables['form'] ? drupal_get_form('google_cse_results_searchbox_form', $variables['self']) : '';
  $variables['noscript'] = t('!google, or enable JavaScript to view them here.', array('!google' => l(t('View the results at Google'), 'http://'. variable_get('google_cse_domain', 'www.google.com') .'/cse', array('query' => $query))));
  $variables['prefix'] = filter_xss_admin(variable_get('google_cse_results_prefix', ''));
  $variables['suffix'] = filter_xss_admin(variable_get('google_cse_results_suffix', ''));

  $settings = array(
    'googleCSE' => array(
      'resultsWidth' => intval(variable_get('google_cse_results_width', 600)),
      'domain' => variable_get('google_cse_domain', 'www.google.com'),
    ),
  );
  drupal_add_js($settings, 'setting');
}

/**
 * The search results page can be themed/customized. This is the
 * function for theming the Business search results page. 
 *
 * The input is a "results" array.
 *
 * Component 'items' is an array of search results, 
 * where each item is an array with the
 * following components (not all are displayed in this default function):
 *   'url' - URL of search result
 *   'title' - Title of search result
 *   'crawldate' - Date page was last indexed by Google
 *   'excerpt' - Excerpt of page with search terms highlighted
 *   'lang' - Google's guess as to the language of the search result
 *   'crowd_host' - Indicates that lots more results were found on this
 *      host, and you could do another query on this host to find more
 *      results (value is a URL-encoded host name to be used in a query)
 *
 * Components 'from', 'to', and 'total' 
 * indicate "Viewing results [from] to [to] of approximately [total]'.
 *
 *
 */
function template_preprocess_google_cse_xml_results(&$variables) {
  $results = $variables['form'];

  $variables['prefix'] = filter_xss_admin(variable_get('google_cse_results_prefix', ''));
  $variables['suffix'] = filter_xss_admin(variable_get('google_cse_results_suffix', ''));
  $variables['results_searchbox_form'] = $variables['form'] ? drupal_get_form('google_cse_results_searchbox_form', $variables['self']) : '';

  $variables['header'] = check_plain(variable_get('google_cse_results_title', t('Search Results')));

  $variables['has_results'] = !(empty($results) || empty($results['items']));
  $variables['no_results'] = $variables['form']['noresult_txt'];

  $variables['pager_status'] = t('!from to !to of !total',
           array(
             '!from' => intval($results['from']),
             '!to' => intval($results['to']),
             '!total' => intval($results['total'])
             )
           );

  $perpage = variable_get('google_cse_results_num', 10);
  $query = array('query' => $_GET['query']);

  if ($results['from'] > 1) {
    $newstart = intval($results['from']) - $perpage - 1;
    if ($newstart < 0) {
      $newstart = 0;
    }
    $query['start'] = $newstart;

    $variables['pager_prev'] = l(t('Previous page'), 
                                 variable_get('google_cse_results_path', 'search/google'),
                                 array('query' => drupal_query_string_encode($query)));
  }

  if ($results['to'] < $results['total']) {
    $query['start'] = intval($results['to']);

    $variables['pager_next'] = l(t('Next page'),
                                 variable_get('google_cse_results_path', 'search/google'),
                                 array('query' => drupal_query_string_encode($query)));
  }

  $variables['original_query'] = preg_replace('/ more:[^&]*/', '', $_GET['query']);
  $variables['has_refinements'] = count($results['labels']) == TRUE;
  
  if ($variables['has_refinements']) {
    $variables['refinements_label'] = t('Refine results for');
    $variables['refinements'] = array();
    
    preg_match('/ more:([^&]*)/', $_GET['query'], $selected_label);
    $selected_label = $selected_label[1];

    foreach ($results['labels'] as $label => $title) {
      $selected = ($label == $selected_label) ? ' selected' : '';
      $classes = "google-cse-refinements-label" . $selected;
      $attributes = drupal_attributes(array('class' => $classes));
      $new_query['query'] = $variables['original_query'] . " more:$label";
      $link =  l(t($title),
               variable_get('google_cse_results_path', 'search/google'),
               array('query' => drupal_query_string_encode($new_query)));
      $variables['refinements'][] = array('link' => $link, 'attributes' => $attributes);
    }
  }
  
  $variables['results'] = array();
  foreach ($results['items'] as $item) {
    $link = l($item['title'], $item['url'], array('html' => TRUE, 'attributes' => array('target' => '_blank', 'class' => 'modalframe-processed')));
    $filtered_excerpt = filter_xss_admin(preg_replace('/<br>/', '', $item['excerpt']));
    //$url = l($item['url'], $item['url']);
	$url = t($item['url']);
    $variables['results'][] = array('title' => $link, 'excerpt' => $filtered_excerpt, 'url' => $url);
  }
}

/**
 * Display an Add-to-Google button.
 */
function template_preprocess_google_cse_results_gadget(&$variables) {
  $cx = explode(':', variable_get('google_cse_cx', ''));
  $variables['creator'] = drupal_urlencode($cx[0]);
  $variables['id'] = isset($cx[1]) ? drupal_urlencode($cx[1]) : '';
}
