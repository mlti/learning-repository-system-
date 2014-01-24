<?php
// $Id: assignment_reports.inc, 2011/09/21 Jaffar Exp $

/*** @file
 * Handling forms for assignment report level.
 */

/**
 * Level 2 report for any curriculum
 *
 * Lists name,remarks and feedback of the student
 *
 *
 * @param $node
 *   It contains node object
 */

function assignment_report($node){

	drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment.js');
	module_load_include('inc', 'assignment', 'includes/assignment_view_own');
  $result = array();
  if(is_numeric(arg(3))){
    $result =  assignment_report_level2($node);
  }
  else {
		// If there is no sub topic id this method will be called.
    $result =  assignment_report_level1($node);
  }
  return $result;
}


function assignment_report_level2($node) {
	global $user;
	drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment.js');
	module_load_include('inc', 'assignment', 'includes/assignment_view_own');
	$result = array();
	$head = array(
	array('data' => t('Names'), 'class' => 'subtopic-title'),
	array('data' => t('Student Remarks')),
	array('data' => t('Date of Submission')),
	array('data' => t('Feedback')),
	);
	$tablesort = tablesort_sql($head);

		// to get groups list
	$topic_list['group_list'] = theme('group_list_dropdown', get_group_list($node->nid, $user->uid));
	$topic_list['status_list'] = theme('status_list_dropdown', arg(4));
	$topic_list['node_title'] = l($node->title, 'node/' . $node->nid, array('attributes' => array('title' => 'Title')));
  $subtopic_ass_id = db_result(db_query("SELECT asset FROM {curriculum_topics_assets} WHERE id =%d", arg(3)));
	if (is_numeric($subtopic_ass_id) && function_exists("node_title")) {
		$topic_list['subtopic_title'] =  ' - '. check_plain(node_title($subtopic_ass_id));
	}
	else {
		$topic_list['subtopic_title'] =  ' - ' . check_plain($subtopic_ass_id);
	}
	// Get Subtopic List
	// Remove unassigned subtopic and make subtopic list as top most assigned by using arsort() function
	if ($_GET["group_id"] != 0) {
		$query = subtopic_list($node->nid, $_GET["group_id"], $user->uid);
	}
	else {
		$query = subtopic_list($node->nid);
	}

	if (db_affected_rows()) {
		while($check_row = db_fetch_object($query)) {

			$tp_id = subtopic_assingments($node->nid, $check_row->id, NULL, TRUE);
			$object = db_fetch_object($tp_id);
			if($object->cnt > 0) {
				$subtopic_id[$object->id] = $object->cnt;
			}
		}
		arsort($subtopic_id);
	}
	// Assigning the topic's list to this array.
	$topic_list['topic_list'] = theme('topic_list_dropdown_level2', get_topic_list_level2($subtopic_id), arg(3),arg(4));

	// Assigning the value for st_id to get process with the query.
	if ($_GET["st_id"] != '') {
		$st_id = $_GET["st_id"];
	}
	else {
		$st_id = arg(3);
	}
	// Assigning the value for status_id to get process with the query.
	if ($_GET["status_id"] != '') {
		$status_id = $_GET["status_id"];
	}
	else {
		$status_id = arg(4);
	}
	if($_GET['st_id'] != '') {
		$sub_topic_id = $_GET['st_id'];
	}
	else {
		$sub_topic_id = arg(3);
	}
	setcookie("st_id", $sub_topic_id, time()+3600);
	$topic_list['username_search'] = drupal_get_form('username_form');

	$report = get_reports_query($node->nid, $st_id, $user->uid, $status_id, $_GET['gid'], $_GET['uname']);

	if(db_affected_rows()){
		while($obj = db_fetch_object($report)){
				
			// If feedback is empty it will return Post feedback link to post feedbaack by teacher.
			// check if quiz is completed
			if(empty($obj->feedback) && !empty($obj->remarks)) {
				$edit_image = theme_image(drupal_get_path('theme', 'educationhub') . "/images/post_feedback.png");
				$feedback = $edit_image . " " . l('Post Feedback', 'assignment/feedback/'.arg(2).'/'.$obj->st_id.'/'.$obj->uid, array('attributes' => array('class' => 'popups post-feedback')));
			}
			else if (empty($obj->remarks)) {
				$edit_image = theme_image(drupal_get_path('theme', 'educationhub') . "/images/post-edit.png");
				$feedback = $edit_image . " " . '<span class="post-feedback">Post Feedback</span>';
			}
			else {
				$feedback = l(truncate_utf8($obj->feedback, 50, $wordsafe = FALSE, $dots = TRUE), 'assignment/view/' . $obj->st_id . '/' . $obj->uid);
			}

			// If remarks is empty it will return null content.
			if(empty($obj->remarks)) {
				$remarks = 'Remarks not yet posted.';
			}
			else{
				$remarks = l(truncate_utf8($obj->remarks, 100, $wordsafe = FALSE, $dots = TRUE), 'assignment/view/' . $obj->st_id . '/' . $obj->uid);
			}

			// If Remarks Time is empty it will return null content.
			if($obj->remarks_time == '0') {
				$remarks_time = 'Remarks not yet posted.';
			}
			else {
				$remarks_time = l(format_date($obj->remarks_time,'custom','j-M-Y'), 'assignment/view/' . $obj->st_id . '/' . $obj->uid);
			}

      $user_picture = user_load($obj->uid)->picture;

			if($user_picture) {
				$user_picture = $user_picture;
			} else {
				$user_picture = variable_get('user_picture_default', '');
			}
			// Constructing row to include data in table.
			$rows[] = array(
					array('data' => '<div class="img float-left"> ' . theme('imagecache', 'user_profile_image_37', $user_picture) . '</div><div class="reports-names">' . eb_others_popup_link(strip_tags(create_eduauthor($obj->uid, NULL, TRUE)),'user/' . $obj->uid) . '</div>'),
					array('data' => $remarks, 'class' => 'remove-bold'),
					array('data' => $remarks_time, 'class' => 'remarks-time remove-bold'),
					array('data' => $feedback),
			);
		}
	}
	else {
		// If no record exist this case will take care off.
		$rows[] = array(
					array('data' => 'No Records Found', 'class' => 'no-record', 'colspan' => 4),
			);
	}
	if (theme('pager', NULL, $limit, 0)) {
		$rows[] = array(array("data" => theme('pager', NULL, $limit, 0), 'class' => "subtopic-total-count", 'colspan' => 4 ));
	}
	else {
		$rows[] = array(array("data" => '', 'class' => "subtopic-total-count", 'colspan' => 4 ));
	}

	$topic_list["results"] = theme('table', $head, $rows);
	//$topic_list["pager"] = theme('pager', NULL, $limit, 0);

	$result = theme('assignment_report_view', $topic_list);
  return $result;
}
/**
 * Level 1 report for any curriculum
 *
 * Lists all subtopic, for each subtopic the total assignments,
 * pending submission, completed submission are printed.
 * Only subtopics that have assignments get listed here.
 * Subtopics with zero assignments will not get listed here
 * Sorted with most assigned at the TOP!
 * Option to refine this view based on the associated groups is possible
 *
 * @param $node
 *   It contains node object
 *
 * @return $output
 *   It returns themed subtopic list with chart
 *
 * @see theme_assignment_report_chart()
 * @see subtopic_list() in assignment_report.inc
 * @see subtopic_assingments() in assignment_report.inc
 *
 * @see assignment-report-chart.tp.php
 * @todo: Move to assignment_report.inc
 */

function assignment_report_level1($node) {
  global $user;
  $topic_list = array();


  $headers = array(
      array('data' => t('Topic No'), 'class' => 'subtopic-title'),
      array('data' => '<span class="table-line-sort ">' . t('Topics') .'<span></span>', 'field' => 'id', 'class' => 'subtopic-title'),
      array('data' => t('Total Assignments').'<span></span>', 'field' => 'id'),
      array('data' => t('Completed Submission').'<span></span>', 'field' => 'id'),
      array('data' => t('Pending Submission').'<span></span>', 'field' => 'id'),
  );
  $tablesort = tablesort_sql($headers);
	$topic_list['node_title'] = l($node->title, 'node/' . $node->nid, array('attributes' => array('title' => $node->title)));
;
	//$topic_list['back'] = l("Go to Playlist", 'node/' . $node->nid);

  // Get Subtopic List
  // Remove unassigned subtopic and make subtopic list as top most assigned by using arsort() function
  if ($_GET["group_id"] != 0) {
    $query = subtopic_list($node->nid, $_GET["group_id"], $user->uid);
  }
  else {
    $query = subtopic_list($node->nid);
  }

  if (db_affected_rows()) {
    while($check_row = db_fetch_object($query)) {

      $tp_id = subtopic_assingments($node->nid, $check_row->id, NULL, TRUE);
      $object = db_fetch_object($tp_id);
      if($object->cnt > 0) {
        $subtopic_id[$object->id] = $object->cnt;
      }
    }
		if ($subtopic_id) {
    arsort($subtopic_id);
		}
  }
  $sql = "SELECT TA.asset, TA.title, TA.type, TA.id FROM  {curriculum_topics_assets} TA  WHERE TA.id IN (%s)";
  //making the page with pager
  $limit = 10;
  $countquery = "SELECT COUNT(*) FROM {curriculum_topics_assets} TA WHERE TA.id IN (%s)";

  // To display all details of chart in single page - Starts Here
  $chart_query = db_query($sql , $subtopic_id?implode(",",  array_keys($subtopic_id)):0);

  $highest_value = 0;
  $topic_id_no = 1;

  while($record = db_fetch_object($chart_query)) {

    $topic_no =  "T" . $topic_id_no++;
    //$_SESSION['topic_id_no'] = $topic_id_no;

    // Get total Assignment
    $total_assignment = subtopic_assingments($node->nid, $record->id);
    // Get Pending Assignment
    $pending_assignment = subtopic_assingments($node->nid, $record->id, 1);
    // Get Completed Assignment
    $completed_assignment = subtopic_assingments($node->nid, $record->id, 2);
    // Pass Chart data value

    //$info->data[] = array('Completed', $topic_no, $completed_assignment);
    //$info->data[] = array('Pending',$topic_no, $total_assignment);
		$info->data[] = array('Completed', $topic_no, $completed_assignment);
    $info->data[] = array('Pending',$topic_no, $pending_assignment);
    $highest_value = ($highest_value < $total_assignment)? $total_assignment: $highest_value;
  }

  // To display all details of chart in single page - Ends here

  // To display all details in table - Starts Here
  // Query is seprated because to display all details in chart in single page as well as to display details
  // using paging.
  $query = pager_query($sql . $tablesort, $limit, 0, $countquery, $subtopic_id?implode(",",  array_keys($subtopic_id)):0);

  if (db_affected_rows()) {
    $rows = array();

    $topic_id_no = 1;
    $quiz_topic_no = 1;

    //Define Headings
    if (!empty($_GET["page"])) {
      $topic_id_no = $_GET["page"] * $limit + 1;
      $quiz_topic_no = $_GET["page"] * $limit + 1;
    }

    $k = 1;

    $topic_list["group_list"] = theme('group_list_dropdown', get_group_list($node->nid, $user->uid));

    while($record = db_fetch_object($query)) {

      $row = array();

      $topic_no =  "T" . $topic_id_no;
      //$_SESSION['topic_id_no'] = $topic_id_no;
      $topic_id_no++;

      // Get SubTopic Name
      $topic_title = l(is_numeric($record->asset)? node_title($record->asset):$record->title, "assignment/reports/" . $node->nid . "/" . $record->id);
      // Get total Assignment
      $total_assignment = subtopic_assingments($node->nid, $record->id);
      $total_assignment = l($total_assignment, "assignment/reports/" . $node->nid . "/" . $record->id);
      // Get Pending Assignment
      $pending_assignment = subtopic_assingments($node->nid, $record->id, 1);
      $pending_assignment = l($pending_assignment, "assignment/reports/" . $node->nid . "/" . $record->id . "/1");
      // Get Completed Assignment
      $completed_assignment = subtopic_assingments($node->nid, $record->id, 2);
      $completed_assignment = l($completed_assignment, "assignment/reports/" . $node->nid . "/" . $record->id . "/2");

      $row[] = array("data" => $topic_no, "class" => "row-col-first subtopic-title" );
      $row[] = array("data" => $topic_title, "class" => "subtopic-title");
      $row[] = array("data" => $total_assignment, "class" => "assignment-number");
      $row[] = array("data" => $completed_assignment, "class" => "assignment-number");
      $row[] = array("data" => $pending_assignment, "class" => "row-col-last assignment-number");
      $rows[] = $row;
      $k++;
    }

    // To display all details in table - Ends Here

    // Construct chart based on Report Level 1
    $info->chart_type = 'Stacked Column 3D';
    $info->settings = array('Caption' => '', 'bgcolor' => 'ffffff', 'bgAlpha' => 70, 'canvasBgColor' => 'ffffff', 'canvasBorderColor' => '000000', 'canvasBorderThickness' => 1, 'canvasBaseColor' => 'ffffff', 'showCanvasBg' => 1, 'showCanvasBase' => 1, 'yAxisMaxValue' => $highest_value, 'shownames' => 1, 'showValues'=> 1, 'animation' => 1,  'showLimits' => 0, 'rotateNames' => 0, 'showLegend' => 1, 'baseFont' => 'Arial', 'baseFontSize' =>11, 'baseFontColor'=> 'cdcdcd', 'outCnvBaseFont' => 'Arial', 'outCnvBaseFontSze' => 11, 'outCnvBaseFontColor' => '416b7c', 'showhovercap' => 1, 'hoverCapBgColor' => '7E7F7F',  'hoverCapBorderColor' => '7E7F7F',    'zeroPlaneColor' => '000000', 'zeroPlaneShowBorder' => 1,  'formatNumber' =>1, 'formatNumberScale' =>1, 'decimalSeparator' =>'.', 'thousandSeparator' =>',', 'decimalPrecision' =>0, 'divLineDecimalPrecision' =>1, 'limitsDecimalPrecision' =>0, 'divlinecolor' => 'f0f0f0', 'showDivLineValue' =>0,  'showAlternateHGridColor' =>0, 'alternateHGridColor' => '#999');

    /*$info->attributes = array(
                       'color' => array('007500', '368ed8', '8BBA00', 'FF8E46', '008E8E', 'D64646', '8E468E', '588526', 'B3AA00', '008ED6', '9D080D', 'A186BE', '32cf40', '59e2e2', 'b61ff3', '7a29d5', 'fd4cf1', 'f21a92',  'e76fdf',  '462c4',  '66d93b', 'e847ca', 'c95399', 'ee5fe', 'f55ee6', '6172f1', 'a573a8', '807aac', 'b0423b', '522f0', '43f615', 'c16876', '226e2', 'fd602e', 'ea8467', 'ba7782',  '504982', 'f0b394', '6246a7', 'd2f07b', 'c5bc84', '72489', 'f4e35c', 'f29b87', '862e4f', 'ea3af6', '68848f', '81bf4e', '1e87ab', 'c0fe42',  '5d1c7', '6724f9', '9331e1', '31f755', '93f1d', 'e1330',  '6d11b9',  '662e99', '5c8ce8', '5b5419', 'b5917a') //no # in front of color
                       );*/
		$info->attributes = array(
                       'color' => array('007500', '368ed8', '8BBA00', 'FF8E46', '008E8E', 'D64646', '8E468E', '588526', 'B3AA00', '008ED6', '9D080D', 'A186BE', '32cf40', '59e2e2', 'b61ff3', '7a29d5', 'fd4cf1', 'f21a92',  'e76fdf',  '462c4',  '66d93b', 'e847ca', 'c95399', 'ee5fe', 'f55ee6', '6172f1', 'a573a8', '807aac', 'b0423b', '522f0', '43f615', 'c16876', '226e2', 'fd602e', 'ea8467', 'ba7782',  '504982', 'f0b394', '6246a7', 'd2f07b', 'c5bc84', '72489', 'f4e35c', 'f29b87', '862e4f', 'ea3af6', '68848f', '81bf4e', '1e87ab', 'c0fe42',  '5d1c7', '6724f9', '9331e1', '31f755', '93f1d', 'e1330',  '6d11b9',  '662e99', '5c8ce8', '5b5419', 'b5917a'),
											 'hoverText' => array(0 => "fdaf"),'scalemode' =>"noscale"
                       );
    $info->width = 500;
    $info->height = 300;
		if (theme('pager', NULL, $limit, 0)) {
			$rows[] = array(array("data" => theme('pager', NULL, $limit, 0), 'class' => "subtopic-total-count", 'colspan' => 5 ));
		}
		else {
			$rows[] = array(array("data" => '', 'class' => "subtopic-total-count", 'colspan' => 5 ));
		}
    $topic_list["chart"] = theme('fusionchart', $info);
    //$rows[] = array(array("data" =>  $k-1 . " of " . count($subtopic_id), "class" => "subtopic-total-count", "colspan" =>5));
    $topic_list["results"] = theme('table', $headers, $rows);
    //$topic_list["pager"] = theme('pager', NULL, $limit, 0);
  }
  else {
    $topic_list["no_content"] = "There are no Assignments for this playlist.";
  }
  $output = theme('assignment_report_chart', $topic_list);

  return $output;
}


/**
 * It generate a form to post feedback.
 *
 * Location : View assingment page - Student.
 *
 * @return
 *   It returns the form in a popup with yes and no options
 *
 */
function assignment_feedback() {
  global $user;

	// Including the assignment.js here
	drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment.js');

	// Constructing FORM
  $form = array();

	$form['node_id'] = array(
    '#type' => 'hidden',
    '#value' => arg(2),
    '#id' => 'node_id',
  );
	$form['st_id'] = array(
    '#type' => 'hidden',
    '#value' => arg(3),
    '#id' => 'st_id',
  );
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => arg(4),
    '#id' => 'uid',
  );

  $form['feedback'] = array(
	  '#type' => 'textarea',
		'#rows' => 5,
		'#required' => TRUE,
		'#title'=> 'Feedback',
		'#prefix' => '<div class="feedback-lable-hide">',
		'#suffix' => '</div>',
	);


  return confirm_form($form, 'Post Feedback', $_SERVER['HTTP_REFERER'], ' ', 'Yes', 'No');
}

/**
 * Posting the feedback for assignment by teacher.
 *
 * All values here are submitted through POST method. So no need of getting through using parameters.
 * @param $_POST['feedback']
 *   It contains feedback
 * @param $_POST['uid']
 *   It contains user id
  * @param $_POST['st_id']
 *   It contains sub topic id
 *
 * @return
 *   It returns the success message if everything goes right.
 *
 */
function assignment_feedback_post() {
  global $user;
	// Updating the feedback in assignment_assign table.
  db_query("UPDATE {assignment_assign} SET feedback = '%s', feedback_time = %d WHERE uid = %d AND st_id = %d ", $_POST['feedback'], time(), $_POST['uid'], $_POST['st_id']);
  $node_id = db_fetch_object(db_query("SELECT asset,title FROM {curriculum_topics_assets} WHERE id = %d", $_POST['st_id']));
  $node_title = is_numeric($node_id->asset)?node_title($node_id->asset): $node_id->title;
	// Getting the user details to send private message and to use in success message.
  $user_obj = user_load(array('uid' => $_POST['uid']));
  $user_name = $user_obj->name;
  $rec[$user_obj->uid] = $user_obj;
	if (is_array($rec) && (count($rec) > 0)) {
	  privatemsg_mail_send($rec, $user, t(' Feedback Posted for Assignment: !title', array('!title'=> $node_title)), t($_POST['feedback']));		
	}
  drupal_set_message("Feedback posted sucessfully for ".$user_name.". A message has been sent to the member.");
}

/**
 * Get Topic List
 *
 * @param $subtopic_id
 *   It contains sub topic id
 *
 * @return
 *   It returns Sub Topic list
 */
function get_topic_list_level2($subtopic_id) {

     $query = db_query("SELECT TA.asset, TA.title, TA.type, TA.id FROM  {curriculum_topics_assets} TA  WHERE TA.id IN (%s)", implode(",",  array_keys($subtopic_id)));

  if (db_affected_rows()) {

    $rows = array();
    while($record = db_fetch_object($query)) {
      $row = array();
      $topic_title = is_numeric($record->asset)? node_title($record->asset):$record->title;
      $row[] = array("data" => truncate_utf8(check_plain($topic_title), 16, $wordsafe = FALSE, $dots = TRUE));
			$row[] = array("data" => $record->id);
      $rows[] = $row;
    }
    return $rows;
	}
}
/*
 * function used to theme the topic dropdown list in Report level 2
 *
 * @param $status_id
 *  It contains sub assignment status ID
 *
 * @return
 *  It contains themed
 */
function theme_status_list_dropdown($status_id = NULL) {

	$div_selected = '<div class="list-one status-list-one selected-list"><div class="status-list seleted-option">All</div></div>';
	// Including the assignment_report.js
  drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment_report.js');

	$output = '<ul class="custom-status-replaced-list" style="display:none" id ="assign-available-option">';
	// if status id and key value is same it will be selected.
	if (!empty($status_id) &&  $status_id == 1) {
			$div_selected = '<div class="list-one status-list-one selected-list" ><div class="status-list seleted-option" id="1">Pending</div></div>';
	} else if (!empty($status_id) &&  $status_id == 2) {
			$div_selected = '<div class="list-one status-list-one selected-list"><div class="status-list seleted-option" id="2">Completed</div></div>';
	}

	$output .=  '<li value="0">All</li><li value="1">Pending</li><li value="2">Completed</li>';
 	$output .= '</ul>';

  return $div_selected . $output;
}


/*
 * function used to theme the topic dropdown list in Report level 2
 *
 * @param $values
 *  It contains collection of group id in an array
 *
 * @param $st_id
 *  It contains sub topic id.
 *
 * @return
 *  It contains themed
 */
function theme_topic_list_dropdown_level2($values, $st_id = NULL) {
	$div_selected = '<div class="list-one topic-list-one selected-list"><div class="topic-list seleted-option">Select</div></div>';

	// Including the assignment_report.js
  drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment_report.js');

	$output = '<ul class="custom-topic-replaced-list" id ="assign-available-option" style="display:none">';

  foreach($values as $key) {
		// if sub topic id and key value is same it will be selected.
		if (!empty($st_id) &&  $st_id == $key[1]['data']) {
			$div_selected = '<div class="list-one topic-list-one selected-list"><div class="topic-list-selected seleted-option"  id=' . trim($key[1]['data']) . '>' . $key[0]['data'] . '</div></div>';
		}
		$output .= '<li value=' . trim($key[1]['data']) . '>' . $key[0]['data'] . '</li>';
	}
	$output .= '</ul>';
	// Concatenating the outputs.
  return $div_selected . $output;
}

/**
 * It generate users first name and last in auto completed
 *
 * Location : report-level 2.
 *
 * @return
 *   It returns the username autocomplete text box.
 *
 */
function username_form() {

//  if($_GET['st_id'] != '') {
//		$sub_topic_id = $_GET['st_id'];
//	}
//	else {
//		$sub_topic_id = arg(3);
//	}
	$st_id = $_COOKIE['st_id'];

	drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment_report.js');
	drupal_add_js(array("assignment" => array("cookie_st_id" => $st_id)), "setting");

	$form = array();

	$form['report_users'] = array(
		'#type' => 'textfield',
		'#prefix' => '<label for="edit-report-users" class="element-invisible">Enter assignee name to find</label>',
		'#autocomplete_path' => 'assignment/report-users-autocomplete/' . arg(2) . '/' . arg(3),
		'#default_value' => "Enter assignee's name to find",
    '#size' => 1550,
  );

	return $form;

}
/**
 * It generate names,feedback and remarks for that curriculum based on curriculum id
 *
 * @param $cid
 *   It contains curriculum id
 *
 * @param $topic_id
 *   It contains topic Id
 *
 * @param $uid
 *   It contains user id
 *
 * @param $status
 *   It contains status of the assignment weather it is pending or completed.
 *
 * @param $gid
 *   It contains group id
 *
 * @param $uname
 *   It contains users first name and last name.
 *
 * @return
 *   It returns query to assignment_report function
 *
 */
function get_reports_query($cid, $topic_id, $uid, $status = 0, $gid = 0, $uname = NULL){
  global $user;

	$limit = 10;
	//user status from assignment_assign
	$user_assign_status = 1;
	//Storing the query parameters in an array.
  $arguments = array($cid, $user_assign_status);
	// Count query
	$countquery = "SELECT COUNT(*) FROM (SELECT AA.uid FROM {curriculum_topics} OGA INNER JOIN {curriculum_topics_assets} TA ON TA.topic_id = OGA.topic_id INNER JOIN {assignment} A ON A.st_id = TA.id INNER JOIN {assignment_assign} AA ON AA.st_id = A.st_id INNER JOIN node n ON n.uid = AA.uid INNER JOIN content_type_profile CTP ON CTP.nid = n.nid WHERE OGA.cid = %d  AND AA.assign_status = %d";
	// Query to display results
	$query = "SELECT  AA.st_id, AA.uid, A.from_uid, AA.uid, AA.remarks, AA.feedback, AA.remarks_time, AA.status, TA.type FROM {curriculum_topics} OGA INNER JOIN {curriculum_topics_assets} TA ON TA.topic_id = OGA.topic_id INNER JOIN {assignment} A ON A.st_id = TA.id INNER JOIN {assignment_assign} AA ON AA.st_id = A.st_id INNER JOIN node n ON n.uid = AA.uid INNER JOIN content_type_profile CTP ON CTP.nid = n.nid WHERE OGA.cid = %d  AND AA.assign_status = %d";

	// If topic id != 0 this condition will append with the query. Else it won't
	if($topic_id != 0) {
    $query .= " AND AA.st_id = %d ";
		$countquery .= " AND AA.st_id = %d ";
		//appending the query parameters in an array.
		array_push($arguments, $topic_id);
	}
	// If $status != 0 this condition will append with the query. Else it won't
	if($status != 0) {
	  $query .= " AND AA.status = %d ";
		$countquery .= " AND AA.status = %d ";
		//appending the query parameters in an array.
		array_push($arguments, $status);
	}
	// If $gid != 0 this condition will append with the query. Else it won't
	if($gid != 0) {
	  $query .= " AND A.to_gid = %d ";
		$countquery .= " AND A.to_gid = %d ";
		//appending the query parameters in an array.
		array_push($arguments, $gid);
	}
	// If $uname != '' this condition will append with the query. Else it won't
	if($uname != '') {
		$query .= " AND LOWER(CONCAT_WS(' ', trim(CTP.field_profile_first_name_value), trim(CTP.field_profile_last_name_value))) LIKE LOWER('%s%') ";
		$countquery .= " AND LOWER(CONCAT_WS(' ', trim(CTP.field_profile_first_name_value), trim(CTP.field_profile_last_name_value))) LIKE LOWER('%s%') ";
		//appending the query parameters in an array.
		array_push($arguments, $uname);
	}
	$query .= " GROUP BY AA.uid";
	$countquery .= " GROUP BY AA.uid) q";
	$query = pager_query($query, $limit, 0, $countquery, $arguments);

  return $query;
}

/**
 * It generate subtopic list for that curriculum based on curriculum id
 *
 * @param $cid
 *   It contains curriculum id
 *
 * @param $subtopic_id
 *   It contains subtopic Id
 *
 * @param $status
 *   It contains status for that subtopic has been completed or not
 *
 * @param $fields
 *   (Optional) it contains TRUE or FALSE
 *
 *
 * @return
 *   It contains subtopic list in an object
 *
 */
function subtopic_assingments($cid, $subtopic_id, $status = NULL, $fields = FALSE, $assign_status = 1) {
  $extra_cond = !empty($status)? ' AND A.status = %d ':'';
  $fields_value = ($fields == TRUE)?" TA.id, ":"";
  $query = "SELECT " . $fields_value . " COUNT(*) as cnt FROM {curriculum_topics} OGA INNER JOIN {curriculum_topics_assets} TA
ON TA.topic_id = OGA.topic_id INNER JOIN {assignment_assign} A ON A.st_id = TA.id WHERE OGA.cid = %d AND A.st_id = %d AND assign_status = %d  " . $extra_cond;

  if($fields == TRUE) {
    return db_query($query, $cid, $subtopic_id, $assign_status, $status);
  }
  else {
    return db_result(db_query($query, $cid, $subtopic_id, $assign_status, $status));
  }
}


/**
 * Get the collection of users in autocomplete depends on the sub topic id in page report level 2.
 *
 * @param $string
 *      It contains the letters which typed by the user.
 *
 * @return
 *    Selected usernames in array format.
 *
 */
function report_users_autocomplete($string = '') {
  global $user;
  // The user enters a comma-separated list of users. We only autocomplete the last user.
  $array = drupal_explode_tags($string);
  // Fetch last user
  $last_string = trim(array_pop($array));
  $matches = array();

  if ($last_string) {
      // This query will get the user ids who are related to the corresponding node id's
      $result = db_query("SELECT AA.uid FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id INNER JOIN assignment_assign AA ON AA.st_id = A.st_id WHERE OGA.cid = %d AND AA.st_id = %d AND A.from_uid = %d AND AA.assign_status = %d GROUP BY AA.uid", arg(2), arg(3), $user->uid, 1);
      while ($obj = db_fetch_array($result)) {
        $ids[] = $obj['uid'];
      }
      // Imploding the user id's in to comma seperated values
      $uid_list = implode(', ', $ids);
      // This query will match the entire records which get matched with first name and last name.
      $user_result = db_query("SELECT title, field_profile_first_name_value AS fname, field_profile_last_name_value AS lname FROM {content_type_profile} ctp INNER JOIN {node} n ON ctp.nid = n.nid WHERE LOWER(CONCAT_WS(' ', field_profile_first_name_value, field_profile_last_name_value)) LIKE LOWER('%s%%') AND n.uid IN(%s)", $last_string, $uid_list);
      while ($obj = db_fetch_object($user_result)) {
        // Concatenating Firstname and Last name
        $matches[$obj->fname." ".$obj->lname] = check_plain(trim($obj->fname)." ".trim($obj->lname));
      }
  }
  drupal_json($matches);
}

/**
 * Get playlist list with assigned records
 *
 * @return
 *  It returns themed structure
 *
 * @see _playlist_listing
 */
function assignment_report_list() {
	global $user;
	// include the files
	drupal_add_js(drupal_get_path('module', 'assignment') .'/js/assignment_report.js');
	module_load_include('inc', 'assignment', 'includes/assignment_common_block');
	$limit = 10;
	$result = array();
	$head = array(
		array('data' => t('Playlist')),
		array('data' => t('Total Assignments')),
		array('data' => t('Completed Submission')),
		array('data' => t('Pending Submission')),
	);
	$tablesort = tablesort_sql($head);
	$arguments = array('curriculum', $user->uid);
	$playlist_report_list_page = isset($_GET['page']) ? $_GET['page'] : implode(',', array_fill(0, PLAYLIST_REPORT_LIST_PAGER_ID + 1, 0));
	// get playlist cache
	$cache_ouput = cache_get("playlist_report_list:uid:" . $user->uid . ":page:" . $playlist_report_list_page, "cache_eb");
	if ($cache_ouput->data) {
	  return $cache_ouput->data;
	}
	$page_result = _playlist_listing($limit, $arguments, $tablesort, PLAYLIST_REPORT_LIST_PAGER_ID);
  if (db_affected_rows()) {
    $i = 0;
    while($record = db_fetch_object($page_result)) {
      $rows[] = array(
											array("data" => l($record->node_title, 'assignment/reports/' . $record->nid), "class" => "row-col-first subtopic-title" ),
											array("data" => count_assignments($record->nid)),//Total Assignment
											array("data" => count_assignments($record->nid, 2)),//Completed Assignment
											array("data" => count_assignments($record->nid, 1), "class" => "row-col-last")// Pending Assignment
										);
		}

	}
	else {
		$rows[] = array(
					array('data' => 'No Records Found', 'class' => 'no-record', 'colspan' => 4)
			);
	}
	$pager = theme('pager', NULL, $limit, PLAYLIST_REPORT_LIST_PAGER_ID);
	if ($pager) {
		$rows[] = array(array("data" => $pager, 'class' => "subtopic-total-count", 'colspan' => 4 ));
	}
	else {
		$rows[] = array(array("data" => '', 'class' => "subtopic-total-count", 'colspan' => 4 ));
	}
	$output['result'] = theme('table', $head, $rows);
	$results = theme('assignment_report_list', $output);
	//set the Playlist report listing cache
  cache_set("playlist_report_list:uid:" . $user->uid . ":page:" . $playlist_report_list_page, $results, "cache_eb"); 
  return $results;

}
/**
 * It executes the playlist query
 *
 * @param $limit
 *  It contains integer limits the query
 *
 * @param $arguments
 *  It contains array of arguments passed
 *  
 * @param $pager_id
 *  It contains pager id. It avoid pager colluisions.
 *
 * @return
 * It returns execution of query
 */
function _playlist_listing($limit = 5, $arguments = NULL, $tablesort = NULL, $pager_id = 0) {
  $count_query = "SELECT COUNT(DISTINCT(node.nid)) FROM {node} node INNER JOIN {users} users ON node.uid = users.uid INNER JOIN  {content_field_published} content_field_published ON node.vid = content_field_published.vid LEFT JOIN {node_revisions node_revisions} ON node.vid = node_revisions.vid WHERE (node.type in ('%s')) AND (users.uid = %d)";

  $query = "SELECT DISTINCT(node.nid) AS nid, node.title AS node_title, node_revisions.body AS node_revisions_body, node_revisions.format AS node_revisions_format, node.type AS node_type, node.vid AS node_vid,  node.uid AS node_uid, node.created AS node_created, users.name as user_name, content_field_published.field_published_value,  node_revisions.teaser as teaser, node.comment as comment_setting FROM {node} node INNER JOIN {users} users ON node.uid = users.uid INNER JOIN  {content_field_published} content_field_published ON node.vid = content_field_published.vid LEFT JOIN {node_revisions node_revisions} ON node.vid = node_revisions.vid WHERE (node.type in ('%s')) AND ((users.uid = %d)) ORDER BY node.changed DESC";

  return pager_query($query . $tablesort, $limit, $pager_id, $count_query, $arguments);
}


/*
 * function used to theme the topic dropdown list in Report level 2
 *
 * @param $values
 *  It contains collection of group id in an array
 *
 * @param $st_id
 *  It contains sub topic id.
 *
 * @return
 *  It contains themed
 */
function theme_assignment_report_list($values) {
	// include two div structure for ajax replacing
	$output = '<div class="assignment-report-listing"><div class="assignment-report-listing-table">';
	$output .= $values['result'] . '</div></div>';
  return  $output;
}


function assignment_report_list_ajax() {
	print_r(assignment_report_list());
	exit;
}
