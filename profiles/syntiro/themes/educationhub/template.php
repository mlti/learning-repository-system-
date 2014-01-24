<?php
// $Id: template.php,v 1.16.2.3 2010/05/11 09:41:22 goba Exp $

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function phptemplate_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    return '<div class="breadcrumb">'. implode(' › ', $breadcrumb) .'</div>';
  }
}

/**
 * Remove undesired local task tabs.
 * Related to yourthemename_removetab() in yourthemename_preprocess_page().
 *
 */
function educationhub_removetab($label, &$vars) {
  $tabs = explode("\n", $vars['tabs']);
  $vars['tabs'] = '';

  foreach ($tabs as $tab) {
    if (strpos($tab, '>' . $label . '<') === FALSE) {
      $vars['tabs'] .= $tab . "\n";
    }
  }
}

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function educationhub_preprocess_page(&$vars) {
  global $user, $base_url;
  if(function_exists("custom_node_load")){
    $node = custom_node_load();
  }
  // to hide title tag in login page
  if(arg(0) == 'user' && arg(1) == '' && $user->uid == 0 ) {
    unset($vars['title']);
  }
  
  //variable generate for site name
  $vars['hub_sitename'] = variable_get('site_name', '');

  if((arg(0) == 'user' && arg(1) != '') || (arg(0) == 'user' && arg(1) == $user->uid && (arg(2) == 'edit' || arg(2) == 'preferences')) ) {
    $vars['tabs'] = NULL;
    //to border the content...
    if(arg(1) != 'login' && arg(1) != 'password' && arg(1) != 'register') { 
      $vars['body_classes'] .= ' common-content-border'; 
    }
    if(arg(0) == 'user' && arg(1) != '' ) {
      // to theme the profile image in view page.
      //$vars['body_classes'] .= ' profile-view-image';
      if(arg(0) == 'user' && arg(1) == $user->uid && arg(1) != 0 && arg(2) == '' || user_access("administrator")) {
        $vars['create_link'] = l('Edit Profile', 'user/'. arg(1) .'/edit', array('attributes' => array('class' => ' float-right'), 'html' => TRUE));
      }
      if(arg(2) == 'preferences' || arg(2) == 'edit') {
        $vars['create_link'] = l('Back to Profile', 'user/' . arg(1), array('attributes' => array('class' => ' float-right'), 'html' => TRUE));
      }
    }
  }
  
  if($node->type == 'community_interest_group' || $node->type == 'discussion' ) {
    if(arg(0) != 'og') {
      // to remove the tabs in og related thing.
      $vars['tabs'] = NULL;
    }
  }
  if (arg(0) == 'content' && arg(1) == "myassignments") {
    $vars['body_classes'] .= " assignment-view-list";
  }
  if (arg(0) == 'assignment'&& arg(1) == "list") {
      $vars['body_classes'] .= " common-content-border";
  }

  $vars['tabs2'] = menu_secondary_local_tasks();
  // to remove compose message tab in messages
  if ($vars['tabs']) {
    educationhub_removetab('Write new message', $vars);
  }
  // adding compose message text in page.tpl
  if(arg(0) == 'messages' && $user->uid) {
    $vars['body_classes'] .= ' common-content-border';
   $vars['compose_message'] = l("Compose message", "messages/new", array('attributes' => array('class' => 'create-button'), 'query' => 'destination=messages'));
  }
  //Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }

  // to change the page title
  if(arg(0) == 'messages' && arg(1) != 'new' && $user->uid) {
    $vars['title'] = 'Messages' ;
  }
  if(user_access("read privatemsg")) {
     //unread message count
		 
    $vars['unread'] = function_exists("privatemsg_unread_count") ? privatemsg_unread_count() : '';

  } else {
    $vars['primary_links'] = NULL;
  }
  // to hide page title in selected pages based on arguments
  if((arg(0) == 'user' && arg(1) == 'password') || (arg(0) == 'user' && arg(1) == 'login') ) {
    $vars['title'] = NULL;
  }

  $node = NULL;
  if (is_numeric(arg(1)) && (arg(0) == 'node' || arg(0) == "review_listing" )) {
    $node = node_load(arg(1));

    if((arg(0) == 'node' && is_numeric(arg(1)) && arg(2) == 'edit') && $node->type == 'reviews') {
      $vars['tabs']   = NULL;
    }

    // to move create discussion button right

    if($node->type == 'discussion') {
        $nid = $node->og_groups;
        $vars['create_link'] = l('Back to Community', 'node/'. key($nid), array('attributes' => array('class' => ' float-right'), 'html' => TRUE));
    }
    if($node->type == 'community_interest_group') {
       if (module_exists('og')) {
          $nid = $node->nid;
          // if author means it show create and invite
          if (og_is_group_admin($node)) {
            $vars['create_link'] = l('Create Discussion', 'node/add/discussion', array('attributes' => array('class' => 'create-button margin-right float-right'), 'html' => TRUE, 'query' => 'gids[]='.$nid));
          }
          elseif (og_is_group_member($nid, FALSE, $user->uid)) {
            // if user is group member
            $vars['create_link'] = l('Create Discussion', 'node/add/discussion', array('attributes' => array('class' => 'create-button margin-right float-right'), 'html' => TRUE, 'query' => 'gids[]='.$nid));
          }
      }
    }
  }
  if((arg(0) == 'og' && arg(1) == 'users') || arg(0) == 'og' && (arg(1) == 'unsubscribe' || arg(1) == 'subscribe')) {
    $vars['create_link'] = l('Back to Community', 'node/'.arg(2), array('attributes' => array('class' => ' float-right'), 'html' => TRUE));
    if((arg(0) == 'og' && arg(1) == 'users')) {
      //$vars['body_classes'] .= ' common-content-border profile-view-image';
      $vars['body_classes'] .= ' common-content-border';
    }
  }
	else if((arg(0) == 'node' && arg(1) == 'add' && arg(2) == 'discussion')) {
    $vars['create_link'] = l('Back to Community', 'node/'.$_GET['gids'][0], array('attributes' => array('class' => ' float-right'), 'html' => TRUE));
  }
  // For asset edit and view page tab should be hide
  if ($vars['tabs'] && arg(0) == 'node' && (arg(2) == NULL  || arg(2) == 'edit') && ($node->type == 'asset' || $node->type == 'curriculum') ) {
    $vars['tabs'] = NULL;
  }
  // to remove tabs in register page
  if((arg(0) == 'user' && arg(1) == '') || (arg(0) == 'user' && arg(1) == 'register') || (arg(0) == 'user' && arg(1) == 'password') || (arg(0) == 'user' && arg(1) == 'login') )  {
    $vars['tabs'] = NULL;
    $vars['footer'] = NULL;
  }

  if (arg(0) == 'bridge' && arg(1) == 'myassets') {
    $vars['body_classes'] .= ' listing-page';
  }
  if (arg(1) == 'add' && arg(2) == 'asset') {
    $vars['body_classes'] .= ' asset-add';
  }
  if (function_exists("delete_asset_curriculum_access") && delete_asset_curriculum_access($node) && $node->type == 'asset') {
    $vars['body_classes'] .= ' access-edit';
  }
  if (arg(0) == 'messages' && arg(1) == 'new' && $user->uid) {
    $vars['body_classes'] .= ' private-message-new-compose';
  }
  if (arg(0) == 'messages' && arg(1) == 'view' && $user->uid) {
    $vars['body_classes'] .= ' private-message-view';
  }
  if(arg(0) == 'bridge' && arg(1) == 'myassets') {
    if (user_access('create asset content')) {
      $vars['create_link'] = '<div id="main-asset-create">';
     // $vars['create_link'] .= l('Create Asset', 'node/add/asset', array('attributes' => array('class' => 'create-button float-right create-asset-button')));
      $vars['create_link'] .= '<a class="create-button float-right create-asset-button" href="javascript:;">Create Asset</a>';
      $create_link = array(l('HTML', 'node/add/asset'), l('QUIZ', 'node/add/quiz'));
      $vars['drop_link'] = '<div class="asset-buttons element-invisible"><div style="display: block;" id="asset-available-option">';
      $vars['drop_link'] .= theme_item_list($create_link, NULL, 'ul', NULL);
      $vars['drop_link'] .= '</div></div>';
      $vars['drop_link'] .= '</div>';
    }
  }
  if(arg(0) == 'bridge' && arg(1) == 'mycurriculum') {
    if (user_access('create curriculum content')) {
     $vars['create_link'] = l('Create Playlist', 'node/add/curriculum', array('attributes' => array('class' => 'create-button float-right')));
    }
  }
  if(arg(0) == 'communities' && arg(1) == 'list') {
    if (user_access('create community_interest_group content')) {
     $vars['create_link'] = l('Create Community', 'node/add/community-interest-group', array('attributes' => array('class' => 'create-button float-right')));
    }
  }

  // for login page this class added is used for warning message width
  if (arg(0) == 'user' && arg(1) == 'login') {
    $vars['body_classes'] .= ' login-warnings';
  }
  //Adding Common content border class for Quiz Pages
  if($node->type == 'quiz'){
    $vars['body_classes'] .= ' common-content-border';
    //For QuizInfo page we bring out the Actions div from Node Div,
    // so need to add a new class for this tab only.
    if(arg(2) == ''){
      $vars['body_classes'] .= ' common-border-actions';
    }
  }

  //Adding a body class for Multi Choice Question creation page
  if(arg(1) == 'add' && arg(2) == 'multichoice'){
    $vars['body_classes'] .= ' multichoice-node';
  }
  if (arg(0) == "bridge" && (arg(1) == 'mymars' || arg(1) == 'mybookmarks'|| arg(1) == 'myrecommendations'|| arg(1) == 'myassets' || arg(1) == 'myassignments'|| is_null(arg(1)))) {
    $vars['message_listing'] = $vars['messages'];
    $vars['messages'] = NULL;
  }
  
  if ($node->field_institute[0]['nid']) {
    if (function_exists('institution_flag')) {
      $vars['flag_view'] = institution_flag($node->field_institute[0]['nid']);  
    }
    
  }
  // For footer Title
  $vars['footer_title'] = "Acrossworld";
	
	
	if(arg(0) == 'page-not-found')	{
		$vars['template_files'][] = 'page-not-found';
	}
	if (arg(0) == "recommend") {
		$vars['template_files'][] = 'page-widget';
	}
}

/**
 * Add a "Comments" heading above comments except on forum pages.
 */
function educationhub_preprocess_comment_wrapper(&$vars) {
  if ($vars['node']->type == 'discussion') {
    $vars['content'] = '<div class="comment-list-disc">'.  $vars['content'] . '</div>';
  }
  else {
    $vars['content'] = '<div class="comment-list">'.  $vars['content'] . '</div>';
  }
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

/**
 * Returns the themed submitted-by string for the comment.
 */
function phptemplate_comment_submitted($comment) {
  return t('!username',
    array(
      '!username' => theme('username', $comment)
    ));
}


/**
 * Returns the themed submitted-by string for the node.
 */
function phptemplate_node_submitted($node) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $node),
      '!datetime' => format_date($node->created),
    ));
}

/**
 * Generates IE CSS links for LTR and RTL languages.
 */
function phptemplate_get_ie_styles() {
  global $language;
  $iecss = '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . path_to_theme() .'/ie.css" />';
  if ($language->direction == LANGUAGE_RTL) {
    $iecss .= '<style type="text/css" media="all">@import "'. base_path() . path_to_theme() .'/fix-ie-rtl.css";</style>';
  }

  return $iecss;
}

function educationhub_form_element($element, $value) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  $output = '<div class="form-item"';
  if (!empty($element['#id'])) {
    $output .= ' id="' . $element['#id'] . '-wrapper"';
  }
  $output .= ">\n";
  $required = !empty($element['#required']) ? '<span class="form-required" title="' . $t('This field is required.') . '">*</span>' : '';

  if (!empty($element['#title'])) {
    $title = $element['#title'];
    if (!empty($element['#id'])) {
      $output .= ' <label for="' . $element['#id'] . '">' . $t('!required!title: ', array('!title' => filter_xss_admin($title), '!required' => $required)) . "</label>\n";
    }
    else {
      $output .= ' <label>' . $t('!required!title: ', array('!title' => filter_xss_admin($title), '!required' => $required)) . "</label>\n";
    }
  }

  $output .= " $value\n";

  if (!empty($element['#description'])) {
    $output .= ' <div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}


/**
 * override theme pager here...
 */
function educationhub_pager($tags = array(), $limit = 5, $element = 0, $parameters = array(), $quantity = 4) {
  global $pager_page_array, $pager_total, $base_url;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', (isset($tags[0]) ? $tags[0] : "first"), $limit, $element, $parameters);
  $li_previous = theme('pager_previous', (isset($tags[1]) ? $tags[1] : "previous"), $limit, $element, 1, $parameters);
  $li_next = theme('pager_next', (isset($tags[3]) ? $tags[3] : "next"), $limit, $element, 1, array('html' => TRUE));
  $li_last = theme('pager_last', (isset($tags[4]) ? $tags[4] : "last"), $limit, $element, $parameters);
  //echopre($li_next);
  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => 'pager-first',
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => 'pager-previous',
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => 'pager-ellipsis',
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => 'pager-item',
            'data' => theme('pager_previous', $i, $limit, $element, ($pager_current - $i), $parameters),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => 'pager-current',
            'data' => $i,
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => 'pager-item',
            'data' => theme('pager_next', $i, $limit, $element, ($i - $pager_current), $parameters),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => 'pager-ellipsis',
          'data' => '…',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => 'pager-next',
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => 'pager-last',
        'data' => $li_last,
      );
    }
    return theme('item_list', $items, NULL, 'ul', array('class' => 'pager', 'html' => TRUE));
  }
}


/**
 * Format a link to a specific query result page.
 *
 * @param $page_new
 *   The first result to display on the linked page.
 * @param $element
 *   An optional integer to distinguish between multiple pagers on one page.
 * @param $parameters
 *   An associative array of query string parameters to append to the pager link.
 * @param $attributes
 *   An associative array of HTML attributes to apply to a pager anchor tag.
 * @return
 *   An HTML string that generates the link.
 *
 * @ingroup themeable
 */
function educationhub_pager_link($text, $page_new, $element, $parameters = array(), $attributes = array()) {
  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query[] = drupal_query_string_encode($parameters, array());
  }
  $querystring = pager_get_querystring();
  if ($querystring != '') {
    $query[] = $querystring;
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('« first') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('next ›') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    else if (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  return l($text, $_GET['q'], array('attributes' => $attributes, 'html' => TRUE, 'query' => count($query) ? implode('&', $query) : NULL));
}



/**
 * Define the participants column.
 *
 * @see theme_privatemsg_list_header()
 */
function educationhub_privatemsg_list_header__participants() {
  if (arg(0) == 'messages') {
    if (arg(1) == 'sent') {
      return array(
        'data'    => t('To'),
        'key'     => 'participants',
        'class'   => 'privatemsg-header-participants',
        '#weight' => -30,
      );
    }
    elseif (arg(1) == 'list') {
      return array(
        'data'    => t('From/To'),
        'key'     => 'participants',
        'class'   => 'privatemsg-header-participants',
        '#weight' => -30,
      );
    }
    else  {
      return array(
        'data'    => t('From'),
        'key'     => 'participants',
        'class'   => 'privatemsg-header-participants',
        '#weight' => -30,
      );
    }
  }
  else {
    return array(
      'data'    => t($_SESSION['parti']),
      'key'     => 'participants',
      'class'   => 'privatemsg-header-participants',
      '#weight' => -30,
    );
  }
}

/**
 * Theme the participants field.
 *
 * @see theme_privatemsg_list_field()
 */
function educationhub_privatemsg_list_field__participants($thread) {
  global $user;
  if ((arg(1) == 'inbox' && arg(0) == 'messages') || (!arg(1) && arg(0) == 'messages') || ($_SESSION['parti'] == 'From') || (arg(1) == 'list' && arg(0) == 'messages')) {
    $msg = privatemsg_message_load($thread['thread_id'], $account = NULL);
    $participants[$msg[$msg['author']->uid]] = $msg['author'];
  }
  elseif ((arg(1) == 'sent' && arg(0) == 'messages') || ($_SESSION['parti'] == 'To')) {
    global $user;
    $participants = _privatemsg_generate_user_array($thread['participants'], -4);
    unset($participants[$user->uid]);
  }

  $field = $to = array();
  $limited = FALSE;

  if ($participants) {
    foreach ($participants as $account) {

      if (count($to) >= 1) {
        $limited = TRUE;
      }
      $to = get_profile_name(array('uid' => $account->uid));
      if($to->field_profile_first_name_value && $to->field_profile_last_name_value) {
        $dis_name = drupal_ucfirst($to->field_profile_first_name_value) .' '. drupal_ucfirst($to->field_profile_last_name_value);
      }
      else {
        $dis_name = drupal_ucfirst($account->name);
      }
      $pname[] = $dis_name;
      $plink[] = 'user/'. $account->uid;
    }
  }
  // This else do the magic of the displaying the user name.
  else {
    $to = get_profile_name(array('uid' => $user->uid));
    if($to->field_profile_first_name_value && $to->field_profile_last_name_value) {
      $dis_name = drupal_ucfirst($to->field_profile_first_name_value) .' '. drupal_ucfirst($to->field_profile_last_name_value);
    }
    else {
      $dis_name = drupal_ucfirst($account->name);
    }
    $pname[] = $dis_name;
    $plink[] = 'user/'. $account->uid;
  }

  $limit_string = '';
  if ($limited) {
    $limit_string = t(' and others');
  }
  if(count($pname)>0){
  $implodeVal = implode(', ', $pname);

    if(strlen($dis_name) > 10 && $_SESSION['parti']) {
      $textName = truncate_utf8($implodeVal, 10, FALSE, TRUE);
    } else {
      $textName = truncate_utf8($implodeVal, 35, FALSE, TRUE);
    }
    $explodeNameArray = explode(',',$textName);
    foreach($explodeNameArray as $key => $value){
      $splitedText[] = l($value,$plink[$key], array('attributes' => array('class' => 'popups', 'on-popups-options' => '{width: "670px"}', 'title' => $value)));
    }

    $finalParticipants = implode(', ',$splitedText);
    $field['data'] = $finalParticipants;
  }
  $field['class'] = 'privatemsg-list-participants';
  return $field;
}

/**
 * Theme the subject of the thread.
 *
 * @see theme_privatemsg_list_field()
 */
function educationhub_privatemsg_list_field__subject($thread) {
  $field = array();
  $options = array();
  $is_new = '';
  if (!empty($thread['is_new'])) {
    $is_new = theme_mark(MARK_NEW);
    //$options['fragment'] = 'new';
  }
  $options['attributes'] = array('html' => TRUE);
  if(strlen($thread['subject']) > 15 && $_SESSION['parti']) {
    $subject = truncate_utf8($thread['subject'], 15, FALSE, TRUE);
  }
  else {
    $subject = $thread['subject'];
  }
  $field['data'] = l($subject, 'messages/view/' . $thread['thread_id'], $options);
  $field['class'] = 'privatemsg-list-subject';
 return $field;

}

/**
 * Theme the subject of the thread.
 *
 * @see theme_privatemsg_list_field()
 */
function educationhub_privatemsg_list_field__last_updated($thread) {
  $diff_seconds  = time() - $thread['last_updated'];
  $diff_days     = floor($diff_seconds/86400);
  if ($diff_days >= 1) {
    $thread['last_updated'] = date("d M Y",$thread['last_updated']);
  }
  else {
    $thread['last_updated'] = date("H",$thread['last_updated']) . ':' . date("i",$thread['last_updated']) . ' ' . date("a",$thread['last_updated']);
  }

 return $thread['last_updated'];

}

/**
 * Theme to display the privatemsg list.
 *
 * This theme builds a table with paging based on the data which has been built
 * by the header and field theme patterns.
 */
function educationhub_privatemsg_list($form) {
  $has_posts = !empty($form['#data']);

  drupal_add_css(drupal_get_path('module', 'privatemsg') .'/styles/privatemsg-list.css');

  // Load the table columns.
  $columns = array_merge(array('subject', 'last_updated'), array_filter(variable_get('privatemsg_display_fields', array('participants'))));

  // Load the themed list headers based on the available data.
  $headers = _privatemsg_list_headers(!empty($form['#data']), $columns);

  // Changing the weight of the participants field in order to display the section in google type.
  $headers['participants']['#weight'] = -50;
  // sort the headers array based on the #weight property.
  usort($headers, 'element_sort');

  $themed_rows = array();
  // Check if there is atleast a single thread.
  if ($has_posts) {
    foreach ($form['#data'] as $thread_id => $data) {
      // Theme the row.
      $row = _privatemsg_list_thread($data);
			$form['threads'][$thread_id]['#title'] = '<span class="element-invisible"> Check message ' . strip_tags($row['data']['subject']['data']) . '</span>';
      $data = array();
      // Render the checkbox.
      $data[] = array('data' => drupal_render($form['threads'][$thread_id]), 'class' => 'privatemsg-list-select');

      // Store the #rows data in the same order as the header is, the key property of the header refers to the field that belongs to it.
      foreach ($headers as $header) {
        if (!empty($header['key'])) {
          if (isset($row['data'][$header['key']])) {
            $data[] = $row['data'][$header['key']];
          }
          else {
            // Store a empty value so that the order is still correct.
            $data[] = '';
          }
        }
      }
      // Replace the data
      $row['data'] = $data;
      $themed_rows[] = $row;
    }
		$catpion = '<span class="element-invisible">Message list</span>';
  }
  else {
    // Display a message if now messages are available.
    $themed_rows[] = array(array('data' => t('No messages available.'), 'colspan' => count($headers)));
		$catpion = '<span class="element-invisible">No messages available.</span>';
  }
	

  // Remove any data in header that we don't need anymore.
  foreach ($headers as $id => $header) {
    unset($headers[$id]['key']);
    unset($headers[$id]['#weight']);
  }
	$headers[0]['data'] = '<span class="element-invisible">Select All</span>';

  // Theme the table, pass all generated information to the table theme function.
  $form['list'] = array('#value' => theme('table', $headers, $themed_rows, array('class' => 'privatemsg-list'), $catpion), '#weight' => 5);
  return drupal_render($form);
}

/**
 * Define the last updated column.
 *
 * @see theme_privatemsg_list_header()
 */
function educationhub_privatemsg_list_header__last_updated() {
  return array(
    'data'    => t('Date AND Time'),
    'field'   => 'last_updated',
    'key'     => 'last_updated',
    'sort'    => 'desc',
    'class'   => 'privatemsg-header-lastupdated',
    '#weight' => -20,
  );
}

/**
 * Overwriting theme_links()
 */
function educationhub_links($links, $attributes = array('class' => 'links')){
  //Reset Comment Reply link.
  if (isset($links['comment_reply'])) {
    unset($links['comment_reply']);
  }
  return theme_links($links, $attributes);
}


/**
 * Process variables for user-profile.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $account
 *
 * @see user-profile.tpl.php
 * @see get_network_link() is in eb_others_common.inc
 */
function educationhub_preprocess_user_profile(&$variables) {
  $profile = content_profile_load("profile", $variables["account"]->uid);
  if (!isset($_REQUEST['destination'])) {
		$variables['display_mode'] = 'normal';
    $pf_skype_id = $profile->field_profile_skype_id[0]['value'];
		$pf_twitter_id = $profile->field_profile_twitter_id[0]['value'];
		$pf_facebook_id = $profile->field_profile_facebook_id[0]['value'];
		$pf_linkedin_id = $profile->field_profile_linkedin_id[0]['value'];
		$variables['account']->skype_link = ($pf_skype_id) ? get_network_link($pf_skype_id, 'skype') : NULL;
		$variables['account']->twitter_link = ($pf_twitter_id) ? get_network_link($pf_twitter_id, 'twitter') : NULL;
		$variables['account']->facebook_link = ($pf_facebook_id) ? get_network_link($pf_facebook_id, 'facebook') : NULL;
		$variables['account']->linkedin_link = ($pf_linkedin_id) ? get_network_link($pf_linkedin_id, 'linkedin') : NULL;	
  }
 
	$pf_first_name = $profile->field_profile_first_name[0]['value'];
	$pf_last_name =  $profile->field_profile_last_name[0]['value'];
	$first_last_name = $pf_first_name . ' ' . $pf_last_name;
	drupal_set_title(check_plain(create_eduauthor($variables["account"]->uid, $first_last_name, TRUE)));	
	if ($variables['account']->skype_link) :
		$variables['social_link'] .= '<li>' . $variables['account']->skype_link . '</li>';
  endif;
  if ($variables['account']->im_link) :
    $variables['social_link'] .= '<li>' . $variables['account']->im_link . '</li>' ;
  endif;
  if ($variables['account']->twitter_link) :
    $variables['social_link'] .= '<li>' . $variables['account']->twitter_link . '</li>';
  endif;
  if ($variables['account']->facebook_link) :
    $variables['social_link'] .= '<li>' . $variables['account']->facebook_link . '</li>' ;
  endif;
  if ($variables['account']->linkedin_link) :
    $variables['social_link'] .= '<li>' . $variables['account']->linkedin_link . '</li>';
  endif;
}


/**
 * Process variables for user-picture.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $account
 *
 * @see user-picture.tpl.php
 * @see get_network_link() is in eb_others_common.inc
 */
function educationhub_preprocess_user_picture(&$variables) {
  global $user;
  //displaying the network links below the picture if this is a popup display
  if (isset($_REQUEST['destination'])) {
      $variables['display_mode'] = 'popup';
      $result = db_query("SELECT ctp.field_profile_skype_id_value, ctp.field_profile_twitter_id_value, ctp.field_profile_facebook_id_value, ctp.field_profile_linkedin_id_value
                         FROM {content_type_profile} ctp
                         INNER JOIN {node} ON node.vid = ctp.vid
                         WHERE node.uid = %d AND node.type = 'profile'", $variables['account']->uid);
      $profile_data = db_fetch_object($result);
      $variables['account']->skype_link = ($profile_data->field_profile_skype_id_value) ? get_network_link($profile_data->field_profile_skype_id_value, 'skype') : NULL;
      $variables['account']->twitter_link = ($profile_data->field_profile_twitter_id_value) ? get_network_link($profile_data->field_profile_twitter_id_value, 'twitter') : NULL;
      $variables['account']->facebook_link = ($profile_data->field_profile_facebook_id_value) ? get_network_link($profile_data->field_profile_facebook_id_value, 'facebook') : NULL;
      $variables['account']->linkedin_link = ($profile_data->field_profile_linkedin_id_value) ? get_network_link($profile_data->field_profile_linkedin_id_value, 'linkedin') : NULL;
  }


  if ((arg(0) == 'user') && (arg(2) == 'edit')) {
    $variables['class_val'] = "photo-top";
    $variables['sub_class_val'] = 'photo';
  }
  else {
    $variables['class_val'] = 'photo';
    $variables['sub_class_val'] = '';
  }

  $variables['image'] = $variables['account']->picture?theme('imagecache', 'user_profile_image_123', $variables['account']->picture, 'My Profile', 'My Profile'):theme('imagecache','user_profile_image_123', drupal_get_path('theme', 'educationhub') . '/images/icons/avator.jpg', 'My Profile', 'My Profile');

}

/**
 * customizing theme_username().
 */
function educationhub_username($object) {
  global $user;

  /** displaying first name and last name instead of username - Beschi **/
  // arg(0)!=search  => purpose : while searching apachesolr will call theme_username() default.. to avoid this by using condition
  if ($object->uid && arg(0) != 'ebsearch' && arg(0) != 'mysearch') {
    $userfl = db_fetch_object(db_query("SELECT ctp.field_profile_first_name_value, ctp.field_profile_last_name_value
                                       FROM {content_type_profile} ctp
                                       INNER JOIN {node} on node.vid = ctp.vid
                                       WHERE node.uid = %d AND node.type = 'profile'", $object->uid));
    if ($userfl->field_profile_first_name_value == "" && $userfl->field_profile_last_name_value == "") {
      $flname = $object->name;
    } else {
      $flname = trim(ucwords($userfl->field_profile_first_name_value . " " . $userfl->field_profile_last_name_value));
    }
  }
  else {
    $flname = $object->name;
  }
  /** displaying first name and last name instead of username - Beschi **/
  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables. also: no need to truncate for search result combo boxes

    if (arg(0) != 'ebsearch' && drupal_strlen($flname) > 15) {
      $name = drupal_substr($flname, 0, 13) .'...';

    }
    else {
      $name = $flname;
    }
    if (user_access('access user profiles')) {
      if($user->uid == $object->uid) {
        $output = l($name, 'user/'. $object->uid, array('attributes' => array('title' => t('My Profile'))));
      }
      else {
        $output = l($name, 'user/'. $object->uid, array('attributes' => array('class' => 'popups', 'on-popups-options' => '{width: "670px"}', 'title' => t('View profile'))));
      }
    }
    else {
      $output = check_plain($name);
    }
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if (!empty($object->homepage)) {
      $output = l($flname, $object->homepage, array('attributes' => array('rel' => 'nofollow')));
    }
    else {
      $output = check_plain($flname);
    }
    $output .= ' ('. t('not verified') .')';
  }
  else {
    $output = check_plain(variable_get('anonymous', t('Anonymous')));
  }
  return $output;
}

// tell Drupal what template to use for the user profile form
function educationhub_theme(&$existing, $type, $theme, $path) {
  $items['user_profile_form'] = array(
    'arguments' => array('form' => NULL),
    'template' => 'template/user-profile-edit',
  );
  return $items;
}
