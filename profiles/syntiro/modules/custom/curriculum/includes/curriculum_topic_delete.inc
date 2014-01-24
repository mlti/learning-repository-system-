<?php
// $Id: curriculum_topic_delete.inc, 2011/08/19  Exp $

/**
 * @file
 *  Delete Topic and Subtopic on Curriculum Edit pages
 */


//Delete topic - confirmation form - popup
function delete_topic_confirm_form(){
  $form = array();

  $form['remove_content'] = array(
    '#type' => 'markup',
    '#value' => t('Are you sure you want to delete this Topic?'),
    '#prefix' =>'<div class="result"><div class="confirm-text">',
    '#suffix' =>'</div></div>',
  );

  $form['yes_submit'] = array(
    '#prefix' => '<div class="button-main">',
    '#type' => 'submit',
    '#value' => t('Yes'),
  );
  $form['no_submit'] = array(
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('No'),
  );
  return $form;
}

/* Delete topic  */
function delete_topic_confirm_form_submit($form, &$form_state){
  global $user;
  //echo arg(2);
 // die;
  if($form_state['clicked_button']['#value'] == 'Yes'){
    // Get Curriculum Node id from that topic
    $nid = db_result(db_query("SELECT cid FROM {curriculum_topics} WHERE topic_id=%d", arg(2)));
    $node = node_load($nid);
    // Apache Solr Index Purpose
    if (function_exists('_apachesolr_nodeapi_update')) {
      _apachesolr_nodeapi_update($node);
    }
    //delete all contents in the topic
    db_query("DELETE FROM {curriculum_topics_assets} WHERE topic_id = %d", arg(2));

    //delete the topic
    db_query("DELETE FROM {curriculum_topics} WHERE topic_id = %d", arg(2));
  }

}

function curriculum_edit_topic_form() {
    global $base_url;
	//if this an ajax call then process and return json output
	
	    $topicid = db_query("SELECT topic_id FROM {curriculum_topics} WHERE cid= %d", arg(1));
                while (($row = db_fetch_array($topicid))) {		  
		  //sub topic ids		
		  $sub_topic_query = db_query("SELECT id FROM {curriculum_topics_assets} WHERE topic_id= %d",$row['topic_id']);
		  $subtopic_id = array();
		  while (($row1 = db_fetch_array($sub_topic_query))) {
		    $subtopic_id[] = $row1['id'] . "-" . $row['topic_id'];
		  }
		 $topic[] = array("subtopic"=> $subtopic_id, "selected_topicid" => $row['topic_id']);
		 $alltopic_id[] = $row['topic_id'];
		 $topic_id = @array_combine(range(1, count($alltopic_id)), $alltopic_id);
		} 

		$topic_count = count($all_topic_id);
  if($_POST['ajaxed'] && $_REQUEST['mode'] == "edit") {
		$new_topic = $_REQUEST['topic'];

		if ($new_topic == '') {
			$new_topic = '<No Title>';
		}

		if(db_query("UPDATE {curriculum_topics} SET topic_title='%s', changed=%d where topic_id=%d", $new_topic, time(), arg(3))) {
                $node = node_load(arg(1));
		//topic count
		
                // Apache Solr Index Purpose
                if (function_exists('_apachesolr_nodeapi_update')) {
                  _apachesolr_nodeapi_update($node);
                }
		
                $ret_msg = array(
                          "status" => "ok",
                          "new_topic" => $new_topic,
			  "topics" => $topic,
			   "topicid" => $topic_id,
			  "topic_count" => $topic_count,
                );
		
		}
		else {
                $ret_msg = array(
                          "status" => "error",
                          "new_topic" => arg(4),
                );
		}
		drupal_json($ret_msg);
		exit;
	}
	elseif($_POST['ajaxed'] && $_REQUEST['mode'] == "add") {
		$curriculum = arg(1);

    $node = node_load(arg(1));
    if($node->type == 'assignment') {
        $new_topic = "New Resource Set";
    } else {
        $new_topic = "";
    }


		$weight = db_query("SELECT MAX(weight) as weight from {curriculum_topics} where cid = %d", $curriculum);
    $obj = db_fetch_object($weight);
    $weight_value = ($obj->weight)?$obj->weight:0;
    $new_weight = $weight_value + 1;


		if(db_query("INSERT INTO {curriculum_topics} SET cid = %d, topic_title='%s', created=%d, changed=%d, weight=%d", $curriculum, $new_topic, time(), time(), $new_weight)) {

            $new_topic_id = db_last_insert_id('curriculum_topics','topic_id');
            $node = node_load($curriculum);
            // Apache Solr Index Purpose
            if (function_exists('_apachesolr_nodeapi_update')) {
              _apachesolr_nodeapi_update($node);
            }
						//$popupoption = "{updateSource:'final'}";
            $popupoption = '{hijackDestination:"FALSE"}';
				$ret_msg = array(
						"status" => "ok",
						"topics" => $topic,
						"topic_count" => $topic_count,
						"topicid" => $topic_id,
						"topic_box" => '
                <div order_weight="'. $new_weight .'" topic_id="'. $new_topic_id .'" id="topic_'. $new_topic_id .'" class="topics">
								<div class="common-list-wrapper">
								<div class="common-list-drop topic-title-inline">

								<div class="topic-left"><span title="Click To Edit" class="topic-inline-edit2">'. check_plain($new_topic) .'</span>

								<span>
									<a title="Edit this topic" alt="Edit this topic" class="topic-inline-edit" href="' . $base_url . '/curriculum/' . $curriculum . '/add_edit_topic/' . $new_topic_id . '/' . $new_topic . '">  <img src="' . $base_url . '/' . drupal_get_path('theme', 'educationhub') . '/images/edit_icon.png" class="edit-topic-title-hidden "></a></span></div>

								<span class="open-close-topics"> <span class="open-close-title-expand"></span></span>
                              <span>  <a class="popups-form-reload" on-popups-options=' . $popupoption . '  href="'.$base_url.'/curriculum/delete_topic_confirm/'. $new_topic_id . $new_topic . '" alt="Delete" title="Delete"><img src="'.$base_url.'/' . drupal_get_path('theme', 'educationhub') . '/images/small_close_icon.png"  title="Delete this topic" alt="Delete this topic" class=" "></a>
                           </span>

                     </div>
                    <div class="clearfix topics-top-content">
                        <div class="topic-left">

                            <span>

                            </span>
                        </div>

                        <div class="topic-right">
                            <span class="topic-handle topic-handle-up" title="Move This Up">

                            </span>
                            <span class="topic-handle topic-handle-down" title="Move This Down">

                            </span>

                        </div>

                    </div>
                    <div style="min-height: 50px;" class="topic_content ui-droppable ui-sortable" topic_id="'. $new_topic_id .'" id="content_'. $new_topic_id .'"
                    </div>
										</div>
                </div>
            ',
            "message" => "New Topic has been created, Please update the title",
				);
		}
		else {

				$ret_msg = array(
						"status" => "error",
				);
		}
		drupal_json($ret_msg);
		exit;
	}
	$form=array();
  $form['topic'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value'=>(arg(4))?arg(4):'New Topic',
  );
  $form['submit'] = array(
    '#value' => t('Submit'),
    '#type' => 'submit',
    '#submit' => array('curriculum_edit_topic_form_submit'),
  );
  return $form;
}


function curriculum_edit_topic_form_submit($form, $form_state){
  if(arg(3)) {
     $qry =db_query("update {curriculum_topics} set topic_title='%s',changed=%d where topic_id=%d",$form_state['values']['topic'],time(),arg(3));
  }
  else  {
    $weight=db_query("select max(weight) as weight from {curriculum_topics} where cid = %d", arg(1));
    $obj=db_fetch_object($weight);
    $weight_value=($obj->weight)?$obj->weight:0;
    $qry =db_query("insert into {curriculum_topics} set cid = %d,topic_title='%s',created=%d,changed=%d, weight=%d",arg(1),$form_state['values']['topic'],time(),time(),$weight_value+1);
  }
    $node = node_load(arg(1));
    // Apache Solr Index Purpose
    if (function_exists('_apachesolr_nodeapi_update')) {
      _apachesolr_nodeapi_update($node);
    }

}

function curriculum_edit_desc_form() {
  global $base_url;
  //if this an ajax call then process and return json output
  if($_POST['ajaxed'] && $_REQUEST['mode'] == "edit") {
    $new_desc = $_REQUEST['descr'];
    $no_desc = "Please write the description here..";
		$node = new stdClass();
		$nid = $_REQUEST['nid'];
		$node = node_load($nid);
    $node->body = $new_desc;
		//$node->teaser = NULL;
		//$node->teaser = node_teaser($node->body, isset($node->format) ? $node->format : NULL);
    //$node->timestamp = time();

		//node_submit($node);
    node_save($node);

    if($_REQUEST['descr'] != '') {
        $ret_msg = array(
            "status" => "ok",
            "new_desc" => $new_desc,
        );
    }  else {
        $ret_msg = array(
            "status" => "ok",
            "new_desc" => $no_desc,
        );
    }
	   drupal_json($ret_msg);
	   exit;
	}
}


function playlist_quickadd(){
	global $user;

	if($_POST['ajaxed']) {
    $node = new stdClass();
    $node->uid = $user->uid;
    $node->created = time();
    $node->type = 'curriculum';
		$node->field_author[0]['uid'] = $user->uid;
    $node->title = html_entity_decode($_POST['title']);
    $node->form_token = '4c60e8bf3858e93064639c24042118b4';
    $node->form_id = 'curriculum_node_form';
    $node->comment = 2;
		node_save($node);

		if($node->nid){
			$topic_details = db_query("SELECT topic_id, topic_title FROM {curriculum_topics} WHERE cid = %d", $node->nid);
			while($result = db_fetch_object($topic_details)){
				$topic_id = $result->topic_id;
				$topic_title = $result->topic_title;
			}
			$output = array(
					"status" => "ok",
					"nid" => $node->nid,
					"title" => $node->title,
					"topic_id" => $topic_id,
					"topic_title" => $topic_title
			);
		}
		drupal_json($output);
		exit;
	}
}
