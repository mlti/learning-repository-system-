<?php


/**
 * Form constructor for the search keyword textbox in search pages.
 *
 * @param $node
 *   It contains node object
 *
 * @see getSolrSearchform_submit()
 * @ingroup forms
 */
function getSolrSearchform($form_state, $username_popup = NULL, $filter_options = NULL, $defaulsearchtext_val = NULL) {
  $form = array();

  drupal_add_js(drupal_get_path('module', 'eb_search') . '/js/eb_search.js');
	drupal_add_js(drupal_get_path('module', 'eb_search') .'/js/eb_search2.js');
  if (arg(0) == 'ebsearch')  $currentForm = TRUE;
  if ((isset($currentForm)) && (arg(2) != '')) {
    $defaultsearchText = checkquotes(search_get_keys(), TRUE);
	}
  else {
    $defaultsearchText = 'Enter the topic and find';
  }

  // Generate autocomplete in that textbox
	if (function_exists("_apachesolr_autocomplete_class")) {
		$autocomplete_settings = _apachesolr_autocomplete_class();
	}
  $search_text = 'searchText';
  // Check if it is in header search box or others
  // view activity meter permission is for student login home page
	$display = NULL;
  // Check if search text box in popup
	if (is_string($username_popup)) {
		$defaultsearchText = 'Search User';
		$search_text = $username_popup;
		$display = 'style =display:none';
	}
	if ($filter_options) {
		$defaultsearchText = $defaulsearchtext_val;
		$search_text = $filter_options;
		//$class_value = 'search-text-filter';
		$display = 'style =display:none';
	}
	//$search_icon = 'header-search-button.jpg';
	$div = NULL;

  $form[$search_text] = array(
    '#title' => '',
    '#type' => 'textfield',
	
    '#default_value' => $defaultsearchText ? $defaultsearchText : 'Find & Discover',
    '#size' => 25,
    '#attributes' => $autocomplete_settings['custom_class'],
    '#autocomplete_path' => $autocomplete_settings['path'],
    '#prefix' => '<div class="search-box "><label for="edit-' . $search_text .'" class="element-invisible">Search text</label>',
		//'#suffix' => '</div>',
  );
  $form['search-filter'] = array(
    '#type' => 'image_button',
    '#title' => "Search",
    '#name' => "Search",
    '#value' => "Search",
    '#src' => drupal_get_path('theme','educationhub') . '/images/select-drop.jpg',
		'#attributes' =>	array('alt' => 'Search result filter'),
		'#prefix' => '<div style="display:none"><label for="edit-search-filter" class="element-invisible">Search Filter</label>',
    '#suffix' => '</div></div>',
  );
	if (!$filter_options && arg(0) == 'ebsearch') {
			$form['search_image'] = array(
				'#type' => 'markup',
				'#value' => theme_image(drupal_get_path('theme','educationhub') . '/images/select-drop.jpg', "Select Dropdown", "Select Dropdown"),
				'#prefix' => '<div class="search-dropdown-list" ' . $display . '><a tabindex="0" href="#">',
				'#suffix' => '</div></a>',
			);
			
		if(user_access('view assets')){
			$form['asset'] = array(
				'#type' => 'markup',
				'#title' => t(''),
				'#prefix' => '<div class="dropdown-cck-list" style="display:none"><ul><li>',
				'#suffix' => '</li>',
				'#value' => l('Asset', 'ebsearch/results/' . arg(2), array('attributes' => array('type' => 'asset'))),
			);
		}
		if(user_access('create curriculum content')) {
			$form['playlist'] = array(
				'#type' => 'markup',
				'#title' => t(''),
				'#prefix' => '<li>',
				'#suffix' => '</li>',
				'#value' => l('Playlist', 'ebsearch/results/' . arg(2), array('attributes' => array('type' => 'curriculum'))),
			);
		}
		$form['profile'] = array(
			'#type' => 'markup',
			'#title' => t(''),
			'#prefix' => '<li>',
			'#suffix' => '</li>',
			'#value' => l('Profile', 'ebsearch/results/' . arg(2), array('attributes' => array('type' => 'profile'))),
		);
		$form['community'] = array(
			'#type' => 'markup',
			'#title' => t(''),
			'#prefix' => '<li>',
			'#suffix' => '</li>',
			'#value' => l('Community', 'ebsearch/results/' . arg(2), array('attributes' => array('type' => 'community_interest_group'))),
		);
		$form['discussion'] = array(
			'#type' => 'markup',
			'#title' => t(''),
			'#prefix' => '<li>',
			'#suffix' => '</li></ul></div>',
			'#value' => l('Dicussion', 'ebsearch/results/' . arg(2), array('attributes' => array('type' => 'discussion'))),
		);
	}
	if (!$filter_options) {
		$form['search_submit_image'] = array(
			'#type' => 'submit',
			//'#value' => theme_image(drupal_get_path('theme','educationhub') . '/images/searchicon.png', 'Search', 'Search'),
			'#value' => 'Search',
			'#attributes' =>	array('class' => 'search-icon'),
			'#prefix' => '<div class="search-submit-link">',
			'#suffix' => '</div>',
		);
	}
  return $form;
}
/**
 * Assign apache solr autocomplete class
 *
 * Check if the user enable apache solr autocomplete and assign class and autocomplete path to that search textbox
 *
 * @return
 *  It contains array object.
 *
 * @see getSolrSearchform().
 *
 */
function _apachesolr_autocomplete_class(){
    // Check Apachesolr Autocomplete Module Enable
  $autocomplete_settings = null;
  if (module_exists('apachesolr_autocomplete')) {
    if (apachesolr_autocomplete_variable_get_widget() == 'custom') {
	 $autocomplete_settings['custom_class'] = array('class' => ' apachesolr-autocomplete unprocessed');
    }
    else {
	 $autocomplete_settings['path'] = 'apachesolr_autocomplete';
    }
  }
  return $autocomplete_settings;
}

/**
 * Form submission handler for getSolrSearchform().
 *
 * @see getSolrSearchform()
 */
function getSolrSearchform_submit($form, &$form_state) {
  $type = 'solrsort=ps_score_content desc';
  $qryString = $form_state['clicked_button']['#post']['searchText'];
  // Check if it is in header search box submit or others
  if (arg(0) != 'ebsearch'  && arg(0) != 'bridge'  ) {
    if (arg(0) == 'search_user') {
			drupal_goto('search_user/results/' . $qryString);
    }
  }
  drupal_goto('ebsearch/results/' . $qryString, $type);

}

/**
 * display the result from solr, google and federated result based on search keywords
 *
 * @return
 *  It returns html for the search results
 *
 * @see eb_search_view()
 * @see custom_google_search()
 * @see getGoogleResult()
 */
function eb_search_results() {
  $results = array();
	$keywords = checkquotes(search_get_keys());
  $results['search_view'] = eb_search_view($keywords);
  $results['result_keyword'] = $keywords;
  $output = theme('custom_search', $results);
  return $output;
}
/**
 * Google search and fedarated results
 *
 * @return
 *  It contains html structed results
 *
 */
function google_federated() {
	module_load_include('inc', 'eb_search', 'includes/eb_search_google_xml');
	$results = array();
	$keywords = checkquotes(search_get_keys());
  $results['federated_search'] = custom_google_search();
  $results['google_search'] = getGoogleResult($keywords, 2);
  $output = theme('custom_search', $results);
  return $output;
}

/**
 * Re-implementation of search_view().
 *
 * Collect the search results from Search module: after apply individual reult theme + search page theme;
 * No result also handled here
 *
 * @param $keys
 *  (Optional) It contains string: search keyword. Default is NULL
 *
 * @return
 *   It returns html of a search result with themed format
 *
 * @see search_data_searchall()
 * @see apachesolr_search_noresults()
 *
 */
function eb_search_view($keys = NULL) {
  if (arg(0) == 'ebsearch' && arg(2)=='') {
    $results = theme('box', t('Your search yielded no results'), variable_get('apachesolr_search_noresults', apachesolr_search_noresults()));
  }
  // this code for popups the corresponding values.
  popups_add_popups();
  $type = 'apachesolr_search';
  // Construct the search form.  If the user submits POST data, this will
  // redirect to a GET request before the search actually runs.
  if (isset($_POST['form_id']) && $_POST['form_id'] == 'search_form') {
    $form = drupal_get_form('search_form', NULL, $keys, $type);
  }
  // We did not redirect, so run the search if needed.
  $results = '';
  $filters = '';
  if (isset($_GET['filters'])) {
    $filters = trim($_GET['filters']);
  }
  // Only perform search if there is non-whitespace search term or filters:
    // Log the search keys:
	if ($keys || $filters) {
    $log = $keys;
    if ($filters) {
      $log .= 'filters='. $filters;
    }
    watchdog('search', '%keys (@type).', array('%keys' => $log, '@type' => t('Search')), WATCHDOG_NOTICE, l(t('results'), 'search/'. $type .'/'. $keys));

    // Reference: search.pages.inc
    $results = search_data_searchall($keys, $type);
		if (!$results) {
			$results =  theme('ebsearch_results', $results,$type);
		}
	}
	else {
		$results =  theme('ebsearch_results', $results, $type);
	}
  return $results;
}
/**
 * Form constructor for the search result filter page for format
 *
 * @param $results_filter
 *   It contains associative array
 *
 * @ingroup forms
 */
function filterbyformat_form(&$form_state,  $results_filter) {
  $form = array();
  $format = array();
  if ($results_filter) {
    foreach ($results_filter as $value) {
			if ($value['fields']['format']) {
				$format[$value['fields']['format']] = $value['fields']['format'];
	 		}
			if ($value['fields']['type'] == 'quiz') {
				$format[$value['fields']['type']] = $value['fields']['type'] ;
				$quiz_count++;
			}
	  }
  }
  if ($format) {
    $form['filterbyformat'] = array(
	 '#type' => 'checkboxes',
	 '#attributes' => array("class" => "format-type"),
	 '#options' => $format,
    );
		return $form;
  }
  return false;
}
/**
 * Form constructor for the search result filter page for creative common
 *
 * @ingroup forms
 */
function creativecommon_form(&$form_state) {
  $form = array();
  $content_field = content_fields('field_creative_commons_options');
	$allowed_values = content_allowed_values($content_field);

  if ($allowed_values) {
    $form['filterbycreativecommon'] = array(
	 '#type' => 'checkboxes',
	 '#options' => $allowed_values,
    );
  }
  return $form;
}

/**
 * Filter by date option is generated
 *
 * @ingroup forms
 */
function filterbydate_form(&$form_state, $keywords) {
  $form = array();
  $form['filterbydate_new'] = array(
    '#title' => 'Sort By',
    '#type' => 'markup',
    '#value' => l('Newest', 'ebsearch/results/' . $keywords, array('attributes' => array('type' => 'desc'),'query' => 'solrsort=created desc')),
  );
	$form['filterbydate_old'] = array(
    '#title' => 'Sort By',
    '#type' => 'markup',
    '#value' => l('Oldest', 'ebsearch/results/' . $keywords, array('attributes' => array('type' => 'asc'),'query' => 'solrsort=created asc')),
  );

  return $form;
}

/**
 * It assign pager count to 10000.
 *
 * It calls apache solr results page filter count to 10000 so only we can get all results
 *
 * @param $query
 *  It contains string
 *
 * @return $params
 *   It returns array with specific details
 *
 */
function apachesolr_search_basic_custom_params($query) {
  $params = array(
    'fl' => 'id,nid,title,comment_count,type,created,changed,score,path,url,uid,name',
    'rows' => 100000,
    'facet' => 'true',
    'facet.mincount' => 1,
    'facet.sort' => 'true'
  );
  return $params;
}

/**
 * It execute apache solr search by custom
 *
 * It execute search results from apache solr by manually call those function
 *
 * @param $keys
 *  It contains string: search keyword
 * @param $filterstring
 *  It contains string: filter string
 * @param $solrsort
 *  It contains string: whether need to sort
 * @param $base_path
 *  (Optional) it contains string for the path specific. Default is to empty
 * @param $page
 *  (0ptional) it contains pager count. Default to 0
 * @param $caller
 *   (Optional) it contains string. Default is apachesolr_search
 *
 * @return
 *  It returns process results
 *
 * @see apachesolr_drupal_query()
 * @see apachesolr_search_basic_custom_params()
 * @see apachesolr_search_highlighting_params()
 * @see apachesolr_search_spellcheck_params()
 * @see apachesolr_search_add_facet_params()
 * @see apachesolr_search_add_boost_params()
 * @see apachesolr_do_query()
 * @see apachesolr_has_searched()
 * @see apachesolr_process_response()
 * @ingroup apachesolr_search
 *
 */
function apachesolr_search_execute_custom($keys, $filterstring, $solrsort, $base_path = '', $page = 0, $caller = 'apachesolr_search') {
  $params = array();
  // This is the object that knows about the query coming from the user.
  $query = apachesolr_drupal_query($keys, $filterstring, $solrsort, $base_path);

  if (empty($query)) {
    throw new Exception(t('Could not construct a Solr query in function apachesolr_search_search()'));
  }

  $params += apachesolr_search_basic_custom_params($query);
  if ($keys) {
    $params += apachesolr_search_highlighting_params($query);
    $params += apachesolr_search_spellcheck_params($query);
  }
  else {
    // No highlighting, use the teaser as a snippet.
    $params['fl'] .= ',teaser';
  }
  if (module_exists('upload')) {
    $params['fl'] .= ',is_upload_count';
  }
  apachesolr_search_add_facet_params($params, $query);
  apachesolr_search_add_boost_params($params, $query, apachesolr_get_solr());

  list($final_query, $response) = apachesolr_do_query($caller, $query, $params, $page);
  apachesolr_has_searched(TRUE);

  // Add search terms and filters onto the breadcrumb.
  // We use the original $query to avoid exposing, for example, nodeaccess
  // filters in the breadcrumb.
  drupal_set_breadcrumb(array_merge(menu_get_active_breadcrumb(), $query->get_breadcrumb()));
  return apachesolr_process_response($response, $final_query, $params);
}

/*
 * It calls apache solr search and theme function
 *
 * It process apache solr search function and get the result and send that result to theme function
 *
 * @param  $key
 *  	It contains search keyword
 * @param $type
 *   It contains string whether apache sol search or default drupal search
 *
 * @return
 *   It returns themed search results
 *
 * @see eb_search_apachesolr_modify_query() for filter
 *
 */
function search_data_searchall($keys = NULL, $type = 'node') {
  if (isset($keys)) {
    if (module_hook($type, 'search')) {
			// Filter type is asset means we can call apache solr by custom
			// because of filter type asset or bead or quiz cck
			// we call apachesolr_search_execute() function without filter so that we can add filter dynamically
			if (($_GET['filters'] == 'type:asset' || (arg(1) == 'asset')) && ($_GET['filtertype_asset'] != 'asset' &&  $_GET['filtertype_curriculum'] != 'curriculum' && $_GET['filtertype_profile'] != 'profile' && $_GET['filtertype_community_interest_group'] != 'community_interest_group' && $_GET['filtertype_discussion'] != 'discussion')) {
				$custom_path = $keys;
				$solrsort = isset($_GET['solrsort']) ? $_GET['solrsort'] : '';
				$page = isset($_GET['page']) ? $_GET['page'] : 0;
				try {
					
					$results = apachesolr_search_execute($keys, '', $solrsort, $custom_path, $page);
					$response = apachesolr_static_response_cache();
				}
				catch (Exception $e) {
					watchdog('Apache Solr', nl2br(check_plain($e->getMessage())), NULL, WATCHDOG_ERROR);
					apachesolr_failure(t('Solr search'), $keys);
				}
				return theme('ebsearch_results', $results, $type, $response);
			}
			else {
				$custom_path = 'multiple_filters';
				$solrsort = isset($_GET['solrsort']) ? $_GET['solrsort'] : '';
				$page = isset($_GET['page']) ? $_GET['page'] : 0;
				try {
					$results = apachesolr_search_execute($keys, '', $solrsort, $custom_path, $page);
					$response = apachesolr_static_response_cache();
				}
				catch (Exception $e) {
					watchdog('Apache Solr', nl2br(check_plain($e->getMessage())), NULL, WATCHDOG_ERROR);
					apachesolr_failure(t('Solr search'), $keys);
				}
				return theme('ebsearch_results', $results, $type, $response);
			}
    }
  }
}

/**
 * It is used to filter the search result in right side basket
 *
 * @return $bid
 *  It returns search result form with results
 *
 * @see apachesolr_search_execute_custom()
 * @see filterbydate_ranking_form()
 * @ingroup form
 */
function rightside_search_filters() {
  $results_filter = apachesolr_search_execute_custom(arg(2), $_GET['filters'], '', '');
  return drupal_get_form('filterbydate_ranking_form');
}
/*
 * Display results of similar asset using apache solr search
 *
 * Using Taxonomy tag values as the keyword and search using apache solr search and it returns 3 similar asset results.
 *
 * @param $search_value
 *   A string contains search keyword.
 *
 * @return
 *   It returns results of the search keyword
 */
function similar_assets($search_value, $similar_assets = 0) {
  // apachesolr_search_execute() function returns search search of the specific keyword
  $variables =  apachesolr_search_execute($search_value, '', 'ps_score_content desc','similar_asset');
  if ($variables) {
    foreach ($variables as $result) {
			if ($similar_assets == 1) {
				$result['similar_assets_block'] = 1;
			}
			$variables['search_assets'] .= theme('ebsearch_result', $result, $variables['type']); // result will theme by using this theme function
    }
  }
  return $variables['search_assets'];
}


/*
 * It generate a checkbox with form
 *
 * It is used to select the username from the search results (It uses hook_form)
 *
 * @param  $uid
 *    It contains user id
 *
 *  @return
 *    It returns the checkbox within form
 */
function username_search_form($form_state, $user_mail, $user_uid, $disable = FALSE) {
  global $base_url;
  $form = array();
  $form['type'] = array(
    '#type' => 'checkbox',
    '#disabled' => $disable,
    '#prefix' => '<label class="element-invisible" for=edit-type-' .$user_uid .'>edit-type-' . $user_uid .'</label>',
    '#id'=>'edit-type-'.$user_uid,
  );
  $form['username'] = array(
    '#type' => 'hidden',
    '#value' => $user_mail,

  );
  return $form;
}
/*
 * It generate a checkbox with form
 *
 * It is used to select the username from the search results (It uses hook_form)
 *
 * @param  $uid
 *    It contains user id
 *
 *  @return
 *    It returns the checkbox within form
 */
function username_submit_form($form_state, $popup = FALSE) {
  global $base_url;
  $form = array();
  //Check whether this submit form buttons are used in Assignment and Recommend form's.
	if($popup == FALSE){
		$form['select'] = array(
			'#type' => 'button',
			'#id' => 'selected_user',
			'#value' => 'Select',
		);
		$form['cancel'] = array(
			'#type' => 'button',
			'#value' => 'Cancel',
		);
	}
	else{
		$form['select'] = array(
			'#type' => 'button',
			'#id' => 'selected_user',
			'#value' => 'Add',
		);
	}

  return $form;
}
/*
 *  Searches the username
 *
 *  Using apache solr search it search username by using keyword and return themed results
 *
 *  @return
 *   It returns themed search results
 */
function username_search_results() {
  //In new design we need to Remove the popup title.
	drupal_set_title("");
  $search_result = array();

  drupal_add_js(drupal_get_path('module', 'eb_search') .'/js/eb_search_popup.js');

  $search_result['search_box'] = drupal_get_form('getSolrSearchform', 'username-search-text');
	$keywords = checkquotes(search_get_keys());
  //@todo saravana set username_search based on argument: assignment/recommend
  //Check whether the User Search popup for Recommend or Assignment form
	if(arg(1) == 'assignment'){
	  $username_search = 'assignment';
	}

  $search_result['username_results'] = apachesolr_search_execute($keywords, 'type:profile', 'created desc', $username_search, $_GET['page']);

  $username_result = theme('username_search_results', $search_result);
  if ($keywords) {
    return $username_result;
  }
  else {
    return $username_result;
  }
}

/**
 * Check Assignment Access Permission
 *
 * @param $access
 *  It contains permissions
 *
 * @return
 *  It returns user roles
 */
function _view_assignment_roles($access) {
  $roles = NULL;
  $query = db_query("SELECT r.name FROM {permission} P INNER JOIN {role} r ON r.rid = P.rid WHERE P.perm LIKE '%" . $access . "%'");
  if (db_affected_rows()) {
    while($row = db_fetch_object($query)) {
		  $roles[] = $row->name;
    }
  }
  return $roles;
}

/*
 * It filters author name from array variables for search
 *
 * It construct array of author name and pass pagination to that constructed array for search
 *
 * @param $variables
 *     It contains array variable for filter
 * @param $type
 *     It contains content type
 * @param $class_page
 *     It contains strings for class name to pass pagination function
 * @param  $ajax_page
 *     It contains string for pagination function
 * @param $display
 *     It contains string for none or block for define specific div will display or not
 *
 * @return
 *    It returns author name with pagination
 *
 */
function filterbyauthor($variables, $type, $class_page = '', $ajax_page, $display = 'none') {
  $i = 1;
  foreach ($variables['results'] as $value) {
    if ($value['fields']['uid']) {
      $author[] = $value['fields']['name'];
      $variables['author_top'][$value['fields']['name']] = l(strip_tags($value['user']), 'ebsearch/results/' . arg(2), array('query' => 'filters=type:' . $type . ' AND name:' . $value['fields']['name']));

    }
  }
 $variables['author'] = pagination_facet_list($author, $variables['author_top'], $class_page, $ajax_page,  $display);
 return $variables['author'];
}

/*
 * It generate a select and cancel button with form
 *
 * It is used to submit the selected the username from the popup search results
 *
 * @param $uid
 *    It contains user id
 *  @return
 *    It returns the select and cancel button within form
 */
function username_select_form($uid) {
  global $base_url;
  $form = array();
  $form['search'] = array(
    '#type' => 'submit',
    '#value' => 'Select',
  );
   $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
  );
  return $form;

}

/**
 * It list weight for asset or bead
 *
 * It display weight list for asset or bead. while this weightage used as a score in search results
 *
 * @param $node
 *    It contains node object
 *
 * @return
 *   It return html format table structure
 */
function weight_age($node) {
  // The score value will from the Content Bias Setting
  if ($node->type == 'asset' || $node->type == 'bead') {
    // Calculate score
    $value = _calc_score($node);
    $ps_score_content = ( $value > 0 ) ? $value : 0;
    $rows[] = array(0 => 'Weight-age of used asset and curriculum', 1 => 'Recommend by Teacher', 2 => 'Recommend by Student', 3 => 'Bookmarked by Teacher', 4 => 'Bookmarked by Student', 5 => 'Rated by Teacher', 6 => 'Rated by Student', 7 => 'Score');    array_push($rows, array(0 => $asse_used_curri_cnt, 1 => $recommend_used_cnt_teacher, 2 => $recommend_used_cnt_student, 3 => $book_used_cnt_teacher, 4 => $book_used_cnt_student, 5 => $voting_teacher, 6 => $voting_student, 7 => $ps_score_content));
    return theme('table', array(), $rows);
  }
}

/*
 * It returns pager for an constructed array
 *
 * @param $facet
 *    It contains array of strings
 * @param $facet_value
 *   It contains facet value to push in that constructed value
 * @param $class_page
 *     It contains strings for class name to pass pagination function
 * @param  $ajax_page
 *     It contains string for pagination function
 * @param $display
 *     It contains string for none or block for define specific div will display or not
 * @param $nocount
 *     It contains string of true or false
 *
 * @return
 *   It returns themed result with paginations
 *
 */
function pagination_facet_list($facet, $facet_value, $class_page, $ajax_page, $display = 'none', $nocount = false) {
	global $base_url;
  $output = '';
  if ($facet) {
    $i = 1;
    $variable = array();
    $j=0;
    foreach (array_count_values($facet) as $id => $value ) {
      $co_author_page[$j] = $id;
      if ($nocount == false) {
        $variables['facet_top'][$id] = $facet_value[$id] . ' (' . $value . ')';
      }
      else {
        $variables['facet_top'][$id] = $facet_value[$id];
      }
      $j++;
    }
    $pagenum = $_REQUEST['pagenum'];
    if (!(isset($pagenum))) {
      $pagenum = 1;
    }
    $rows = count($facet_value);
    //This is the number of results displayed per page
    $page_rows = 10;
    //This tells us the page number of our last page
    $last = ceil($rows / $page_rows);
    //this makes sure the page number isn't below one, or more than our maximum pages
    if ($pagenum < 1) {
      $pagenum = 1;
    }
    elseif ($pagenum > $last) {
      $pagenum = $last;
    }
    //This sets the range to display in our query
   // $max = 'limit ' .($pagenum - 1) * $page_rows .',' .$page_rows;

    $j = (($pagenum - 1) * $page_rows);
    $k = 0;
    for ($i=$j;$i < ($page_rows +$j);$i++) {
      $co_author_page_1[$i] =  $co_author_page[$i] ;
      $variables['facet_result'][$co_author_page[$i]] = $variables['facet_top'][$co_author_page[$i]] ;
    }
    if ($pagenum == 1)  {
    }
    else  {
      $previous = $pagenum-1;
			$page .= l(theme_image(drupal_get_path('theme','educationhub') . '/images/icons/left-arrow.png'), $base_url . $_SERVER["REQUEST_URI"], array('attributes' => array('class' => $ajax_page . ' pager-filter page-result-left'),'query' => '&pagenum=' . $previous, 'html' =>true));
    }
    //This does the same as above, only checking if we are on the last page, and then generating the Next and Last links
    if ($pagenum == $last) {
    }
    else {
      $next = $pagenum + 1;
      $page .= l(theme_image(drupal_get_path('theme','educationhub') . '/images/icons/right-arrow.png'), $base_url . $_SERVER["REQUEST_URI"], array('attributes' => array('class' => $ajax_page . ' pager-filter page-result-right'), 'query' => '&pagenum=' . $next, 'html' =>true));
    }
    $output = theme('facet_list', $variables['facet_result'], $page, $class_page, $display, $ajax_page);
  }
  return $output;
}
/**
 * Form constructor for the search from block
 *
 * Reason: if we put in getSolrSearchform() itself means while calling ajax in basket we need to check conditions and autocomplete ajax also
 *
 * @see getSolrSearchform_right_submit()
 * @see apachesolr_autocomplete_variable_get_widget()
 * @ingroup forms
 */
function getSolrSearchform_right($form_state) {
  $node = node_load(arg(1));

  $form = array();
	drupal_add_js(drupal_get_path('module', 'eb_search') .'/js/eb_search.js');
  drupal_add_js(drupal_get_path('module', 'eb_search') .'/js/eb_search2.js');
	$form['#attributes'] = array('style' => 'display: none');
  $autocomplete_settings = _apachesolr_autocomplete_class();
  $form['searchText_right'] = array(
    '#title' => '',
    '#type' => 'textfield',
    '#default_value' => $defaultsearchText?$defaultsearchText:'',
    '#size' => 25,
    '#attributes' => $autocomplete_settings['custom_class'],
    '#autocomplete_path' => $autocomplete_settings['path'],
    '#prefix' => '<div class="search-box clearfix">',
  );
  $form['search'] = array(
   '#type' => 'markup',
   '#value' =>'<div class="btn-main"><div class="search-box-block-search"></div></div></div>',
   '#suffix' => '<div id="search-box-block-search-results"></div>',
  );
  return $form;
}
/**
 * It execute search using apachesorl and print result
 *
 * @see mysearch_view()
 */
function mysearch_results() {
	$keywords = checkquotes(search_get_keys());
	$results = mysearch_view($keywords);
  if (isset($_GET['filters'])) {
    $filters = trim($_GET['filters']);
  }
  if(!$results) {
		$keywords = checkquotes(search_get_keys(), TRUE);
    if($filters=='type:asset'){
      $results = '<div class="search-empty-result">Your search - <b>'. check_plain($keywords) .'</b> - does not have any Results under Assets. Please  make sure all words are spelled correctly or try different topic.</div>';
    }
    else {
      $results = '<div class="search-empty-result">Your search - <b>'. check_plain($keywords).'</b> - does not have any Results.  Please  make sure all words are spelled correctly or try different topic.</div>';
    }
  }
  print_r($results);exit;
}

/**
 * Re-implementation of  custom search path.
 *
 * Collect the search results from Search module: after apply individual reult theme + search page theme;
 * No result also handled here
 *
 * @param $keys
 *  (Optional) It contains string: search keyword. Default is NULL
 *
 * @return
 *   It returns html of a search result with themed format
 *
 * @see search_data_mysearch()
 * @see popups_add_popups()
 *
 */
function mysearch_view($keys=NULL) {
  // Search form submits with POST but redirects to GET.
  $results = '';
  $filters = '';

  popups_add_popups();
  $type = 'apachesolr_search';
  if (!isset($_POST['form_id'])) {

    if (isset($_GET['filters'])) {
      $filters = trim($_GET['filters']);
    }
    // Only perform search if there is non-whitespace search term or filters:
    if ($keys || $filters) {
      // Log the search keys:
      $log = $keys;
      if ($filters) {
        $log .= 'filters='. $filters;
       }
       watchdog('search', '%keys (@type).', array('%keys' => $log, '@type' => t('Search')), WATCHDOG_NOTICE, l(t('results'), 'mysearch/results/'. $type .'/'. $keys));

      // Collect the search results.
      //  In this custom function we are searching regardless of whether or not there are $keys
      // which there won't be whenever this function is used

      $results = search_data_mysearch($keys, $type);
    }
  }
  // Construct the search form.
  return $results;
}
/*
 * It calls apache solr search and theme function
 *
 * It process apache solr search function and get the result and send that result to theme function
 *
 * @param  $key
 *  	(Optional) it contains search keyword
 * @param $type
 *   It contains string whether apache sol search or default drupal search
 *
 * @return
 *   It returns themed search results
 *
 * @see apachesolr_search_execute()
 * @see mysearch_search_results()
 * @ingroup apachesolr_search
 *
 */
function search_data_mysearch($keys = NULL, $type = 'node') {
  if (isset($keys)) {
    if (module_hook($type, 'search')) {
			if ($_GET['filters'] == 'type:asset') {
				$custom_path = $keys;
				$solrsort = isset($_GET['solrsort']) ? $_GET['solrsort'] : '';
				$page = isset($_GET['page']) ? $_GET['page'] : 0;
				try {
				  $results = apachesolr_search_execute($keys, $filters, $solrsort, $custom_path, $page);
	 
				}
				catch (Exception $e) {
					watchdog('Apache Solr', nl2br(check_plain($e->getMessage())), NULL, WATCHDOG_ERROR);
					apachesolr_failure(t('Solr search'), $keys);
				}
				return theme('mysearch_search_results', $results, $type);
			}
			else {
				$results = module_invoke($type, 'search', 'search', $keys);
			}
      if (isset($results) && is_array($results) && count($results)) {
        if (module_hook($type, 'search_page')) {
          return module_invoke($type, 'search_page', $results);
        }
        else {
          return theme('mysearch_search_results', $results, $type);
        }
      }
    }
  }
}
/**
 * It is used to segregate the given values
 *
 * @param $filters_value
 *  It contains string
 *
 * @return
 *  It contains array
 *
 * @see eb_search_preprocess_ebsearch_results()
 */
function _filter_value($filters_value) {
  $filters = explode('AND', $filters_value);
  if (count($filters) > 1) {
    foreach($filters as $val) {
      $values = explode(':', $val);
      $default[trim($values[0])] = trim(str_replace('*', '', $values[1]));
    }
  }
  else {
    foreach($filters as $val) {
      $values = explode(':', $val);
      $default[trim($values[0])] = trim(str_replace('*', '', $values[1]));
    }
  }
  return $default;
}


/**
 * generate search filters
 *
 * @return
 *  It contains themed filter results
 *
 */
function filter_search_results() {
	$solrsort = isset($_GET['solrsort']) ? $_GET['solrsort'] : '';
	$page = isset($_GET['page']) ? $_GET['page'] : 0;
	$keywords = checkquotes(search_get_keys());
	
  // to get filter value in search
  $results_filter = apachesolr_search_execute_custom($keywords, '', $solrsort, 'multiple_filters', $page);
  return theme('filterbyauthorasset', $results_filter, $default['type']);
}
/**
  * Custom form for Select all functionality in User, Community Search popup.
  */
function select_all_form(){
	//Select All Check Box.
	$form['field']['select_all'] = array(
		'#type' => 'checkbox',
		'#prefix' => '<label class="element-invisible" for="check-all">Select All</label>',
		'#id' => 'check-all',
	);
	$form['field']['select_all_markup'] = array(
		'#type' => 'markup',
		'#value' => t('Select all'),
	);
	return $form;
}

