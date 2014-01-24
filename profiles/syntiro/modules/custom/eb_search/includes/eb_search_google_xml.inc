<?php
// $Id: eb_search.module 2011/08/13 2:41:PM Jaffar Exp $
/**
 * @file
 *  To manipulate Google result and federated results.
 *
 */
/**
 * This function gets called in the browser address bar for:
 * http://yourhost/my_module/form" or http://yourhost/?q=my_module/form". It will generate// a page with //this form on it
 *
 * @see _google_cse_get_search_results_manual()
 */
function google_xmlresults() {
  jquery_ui_add(array('ui.widget', 'ui.mouse', 'ui.draggable', 'ui.droppable', 'ui.sortable'));
  drupal_add_js(drupal_get_path('module', 'eb_search') . '/js/eb_search2.js');
  $keywords=$_POST['keyword'];
  $startid=$_POST['startid'];
  $limit=$_POST['limit'];
  $total=$_POST['total'];
  $from=$_POST['from'];
  $to=$_POST['to'];
  $results =array();
  $results = _google_cse_get_search_results_manual($keywords, $limit, $startid-1);
  $results['result_txt'] .=theme('google_cse_xml_results', $results);
  $results['startid']=$startid;
  $results['limit']=$limit;
  $results['keywords']=$keywords;
  $out_federated .=theme('google_xmlresults', $results);
  drupal_json($out_federated);
}

/**
 * It provide federated search results
 *
 * @return
 *   It returns html with themable fedarated results
 *
 * @see _google_cse_get_search_results_manual()
 *
 */
function custom_google_search() {
  $keywords = search_get_keys();
  $sitekey = variable_get('google_cse_cx', '');
  $sitelist = preg_split('/[\n\r]+/', variable_get('google_cse_sitesearch', ''), -1, PREG_SPLIT_NO_EMPTY);
  $resultset = '';
  $results = array();
  $limit = 5;
  $startid = 1;
  $results = _google_cse_get_search_results_manual ( $keywords, $limit, $startid-1);
  $results['startid']=$startid;
  $results['limit']=$limit;
  $results['keywords']=$keywords;
  jquery_ui_add(array('ui.widget', 'ui.mouse', 'ui.draggable', 'ui.droppable', 'ui.sortable'));
  drupal_add_js(drupal_get_path('module', 'eb_search') . '/js/eb_search2.js');
  $results['result_txt'] = theme('google_cse_xml_results', $results);
  return theme('google_xmlresults', $results);
}


/**
 * It generate google search result
 *
 * TODO:Google Key, reset width of iframe $google_key='015733485772070635268:ybaslzvdzaq - fron Shyamala's account
 * OLD KEY:011257867916452160398:i8wyeqw4tuc
 *
 * @return
 *   It returns google result within Iframe
*/
function getGoogleResult($key_words, $total_display, $google_key='014548337352250740750:j3rzaeb0fsw') {
  return '<iframe scrolling="no" frameborder="0" height="280" width="100%"  name="googleSearchFrame" src="http://www.google.com/cse?query='. check_plain($key_words) .'&cx='. $google_key .'&cof=FORID:11&sitesearch=&ad=0&start=0&num='. $total_display .'" vmarginwidth="0" marginheight="0" hspace="0" vspace="0" allowtransparency="true"></iframe>';
}



/**
 * It process the federated result from xml to array
 *
 * @param $keyword
 *   It contains string: search keyword should be passed
 * @param $limit
 *   It contains integer: search limit
 * @param @start
 *   It contains integer: pagination purpose
 *
 * @return
 *   It contains array contains results
 *
 * @see _google_cse_get_search_results_manual()
 *
 */
function _google_cse_get_search_results_manual($keyword, $limit, $start) {
  module_load_include('inc', 'eb_search', 'includes/eb_search');
  // formulate the query for Google
  $url = 'http://www.google.com/search';
  //Do not know where this key is used!?
  //$cx = (variable_get('google_cse_cx', ''))?variable_get('google_cse_cx', ''):'015733485772070635268:ybaslzvdzaq';
  $cx = (variable_get('google_cse_cx', ''))?variable_get('google_cse_cx', ''):'014548337352250740750:onom3vscpwq';
  if (function_exists("google_cse_advanced_settings")) {
    $query = array(
    'q' => $keyword,
    'start' => $start,
    'num' => $limit,
    'client' => 'google-csbe',
    'output' => 'xml_no_dtd',
    'cx' => $cx,
     ) + google_cse_advanced_settings();
  }
    $res = drupal_http_request($url . '?' . drupal_query_string_encode($query));

  if ($res->code != '200') {
    return array();
  }
  // parse results and return them
  return _google_cse_parse_xml_results($res->data);
}
