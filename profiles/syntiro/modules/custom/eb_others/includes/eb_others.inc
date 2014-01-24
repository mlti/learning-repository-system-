<?php
// $Id: eb_others.inc,v 1 2011/10/18 5:00:PM Jaffar Exp $

/**
 * Creating Static table for score policy in student login.
 *
 *
 */
function user_score_policy() {
	// Constructing header to include data in table activity.
	$head_activity = array(
    array('data' => t('Activities')),
    array('data' => t('Points')),
	);
  // Constructing row to include data in table activity.
  $rows_activity[] = array(
      array('data' => 'Begin to participate in edubridge'),
      array('data' =>  variable_get('edubridge_participate', 0)),
  );
  $rows_activity[] = array(
      array('data' => 'Creation of community'),
      array('data' => variable_get('edubridge_create_group', 0)),
  );
  $rows_activity[] = array(
      array('data' => 'Creation of discussion in your own community'),
      array('data' => variable_get('edubridge_discussion_own_group', 0)),
  );
  $rows_activity[] = array(
      array('data' => 'Creation of discussion in other community'),
      array('data' => variable_get('edubridge_discussion_other_group', 0)),
  );
  $rows_activity[] = array(
      array('data' => 'Completion of Assignment'),
      array('data' => variable_get('edubridge_complete_assignment', 0)),
  );
  $rows_activity[] = array(
      array('data' => 'Completion of Quiz'),
      array('data' => variable_get('edubridge_complete_quiz', 0)),
  );
  $rows_activity[] = array(
      array('data' => 'Post Comments to Own discussion'),
      array('data' => variable_get('edubridge_comment_own_discussion', 0)),
  );
  $rows_activity[] = array(
      array('data' => 'Post Comments to Others discussion'),
      array('data' => variable_get('edubridge_comment_other_discussion', 0)),
  );
  $rows_activity[] = array(
      array('data' => 'Login to Edubridge daily once'),
      array('data' => variable_get('edubridge_login_daily_once', 0)),
  );
	// Constructing header to include data in table grade.
  $head_grade = array(
    array('data' => t('Grade Level')),
    array('data' => t('Points Required')),
	);
  // Constructing row to include data in table grade
  $rows_grade[] = array(
      array('data' => 'Expert'),
      array('data' => '> 5000'),
  );
  $rows_grade[] = array(
      array('data' => 'Master'),
      array('data' => '2501 - 5000'),
  );
  $rows_grade[] = array(
      array('data' => 'Intermediate'),
      array('data' => '1001 - 2500'),
  );
  $rows_grade[] = array(
      array('data' => 'Learner'),
      array('data' => '1 - 1000'),
  );
  $topic_list = theme('table', $head_activity, $rows_activity);
	$topic_list .= theme('table', $head_grade, $rows_grade );
	return theme('user_score_policy', $topic_list);
}

/**
 * theme function to add class for the score policy table.
 *
 */
function theme_user_score_policy($values) {
	// addding class for score policy table.
  $output  = '<div class="score-policy">';
	$output .= $values;
 	$output .= '</div>';

  return $output;
}

/**
 * To display confirmation message while publish node
 *
 * @param $node
 *  It contains node object
 *
 * @return
 *  It returns form
 *
 */
function publish_node_form($form_state, $node) {
  $form = array();
	if ($node->type == "asset") {
    //This content "Publishing your asset help them indexed in search results"  has been changed to new content 
		$text = '<p>Publishing your assets to have them indexed in search results. Click on OK to proceed with Publishing.</p>';
	}
	else {
    $text = '<p>Publishing your playlist to have them indexed in search results. You can also assign the topics to students and get their remarks.</p>';
		$notes = '<p>Note: You can not Unpublish  or Delete a published playlist Click Ok to proceed publishing</p>';
	}
  //Select All Check Box.
  $form['publish_text'] = array(
    '#type' => 'markup',
		'#prefix' => '<div class="result">',
    '#value' => $text
  );
  $form['publish_node'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
	if ($notes) {
		$form['publish_note'] = array(
		  '#type' => 'markup',
		  '#value' => $notes,
		);
	}
  $form['ok'] = array(
      '#type' => 'submit',
      '#value' => t('Ok'),
			'#prefix' => '<div class="button-main">',
    );
  $redirect_url = url('node/' . $node->nid);
	$form['#redirect'] = url('node/' . $node->nid);
  $form['cancel'] = array(
    '#type' => 'markup',
    '#value' => '<input type="button"  class="form-submit popups-close" value="Cancel" name="cancel">',
    '#suffix' => '</div></div>'
  );
  return $form;
}
/**
 * To display confirmation message while publish node
 *
 * @param $node
 *  It contains node object
 *
 * @return
 *  It returns form
 *
 */
function publish_node_form_submit($form, $form_state) {
  if ($form_state['clicked_button']['#post']['op'] == 'Ok') {
    $node = node_load($form_state['clicked_button']['#post']['publish_node']);
    $node->field_published[0]['value'] = 1;
    $node->status = 1;
    node_save($node);
		$success_msg = ($node->type == "asset")?"Asset":"Playlist";
		drupal_set_message($success_msg . " has been Published Successfully!");
  }
}
/**
 * To display confirmation message while publish node in Ajax
 *
 * @param $node
 *  It contains node object
 *
 * @return
 *  It returns form
 *
 */
function publish_node_confirm($node) {
	$node->field_published[0]['value'] = 1;
	$node->status = 1;
	node_save($node);
	$success_msg = ($node->type == "asset")?"Asset":"Playlist";
	drupal_set_message($success_msg . " has been Published Successfully!");
}
/**
 * To update Taxonomy ID in Variable Table.
 *
 */
function update_taxonomy_pool_form(){
	$form = array();

  $form['taxo_content'] = array(
    '#type' => 'markup',
    '#value' => t('Update Taxonomy Pool. This creates an array that assign values to Taxonomy terms TAGS, Academic Level, Asset Category, Subject.'),
  );

	$form['taxo_list'] = array(
    '#type' => 'value',
    //'#value' => array('Tags', 'Academic Level', 'Asset Category', 'Subject'),
		'#value' => array(0 => 'Tags', 1 => 'Academic Level', 2 => 'Asset Category', 3 => 'Subject', 4 => 'Class/Grade', 5 => 'Discipline'),
  );

  $form['taxo_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update Now'),
    '#weight' => 10,
  );

	return $form;

}


function update_taxonomy_pool_form_submit($form, &$form_state) {
	//Get All Vocabularies in our site.
	$vocabs = taxonomy_get_vocabularies(NULL);
	$voca_list = array();

	foreach($vocabs as $key => $val){
    foreach($form_state['values']['taxo_list'] as $key => $value){
			if($value == $val->name){
				$voca_list[$val->name] = $val->vid;
			}
	  }
	}
  //Set Taxonomy Pool Variable.
	if(variable_set('taxo_pool', 0) == 0){
	  variable_set('taxo_pool', $voca_list);
		drupal_set_message('Taxonomy Pool has been updated.');
	}
}

