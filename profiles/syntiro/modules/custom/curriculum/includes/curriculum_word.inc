<?php
// $Id: curriculum_word.inc,v 1.0 2011/08/19 Exp $

/**
 * @file
 * This module implements the Convert to Word functionality for Curriculum
 */

function curriculum_overview_word($node_obj) {
global $base_url;
$file_name = str_replace(" ","",$node_obj->title);
header("Content-type: application/vnd.ms-word");
header("Content-Disposition: attachment;Filename=$file_name.doc");

  // Check for Co Author if found display Co Author in the cover page
  if($node_obj->field_coauthor) {
    $flag = 0;
    foreach($node_obj->field_coauthor as $users) {
      $user_authorlinks[] = $users['uid']?theme('username_underline', create_eduauthor($users['uid'], NULL, TRUE)):'';
    }
    $coauthor = $user_authorlinks?implode(', ' ,$user_authorlinks):'';
  }

  // Check for Reviewes if found display reviewers in the cover page
  if ($node_obj->field_openforreview[0]['value'] == 1) {
    if ($node_obj->field_reviewers){
      foreach($node_obj->field_reviewers as $users) {
        $user_links[] = theme('username_underline', create_eduauthor($users['uid'], NULL, TRUE));
      }
      $reviewers = $user_links?implode(', ' ,$user_links):'';
    }
  }


 $html = '<html>
          <head>
          <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
          <title>HTML TO WORD</title>
          </head>
          <style type="text/css">
          .hr {
           page-break-after: always;
          }
          </style>
          <body>
          <table width="600" border="1">
          <tr>
          <td height="200">&nbsp;</td>
          </tr>
          <tr>
          <td style="text-align:center; font-size:40px;color:#ed6500;"><b>'.$node_obj->title.'</b></td>
          </tr>
          <tr>
              <td style="text-align:center; color:#595959;">Author: <span style="color:#9d402b; text-decoration:underline;">'.$node_obj->name.'</span></td>
          </tr>';
  if ($coauthor) {
    $html .=  '<tr>
              <td style="text-align:center; color:#595959;">Author:
              <span style="color:#9d402b; text-decoration:underline;">'.$coauthor.'</span></td>
              </tr>';
  }
  if ($reviewers) {
    $html .=  '<tr>
               <td style="text-align:center; color:#595959;">Reviewers:
               <span style="color:#9d402b; text-decoration:underline;">'.$reviewers.'</span></td>
               </tr>';
  }

  $html .= '</table>';

  $html .= '<br clear="all" style="page-break-before:always" />
            <table width="600" border="1">
            <tr>
            <td>Table Of Contents</td>
            </tr>
            <tr>
            <td>&nbsp;</td>
            </tr>';

  $check_query = db_query('SELECT oga.topic_id,oga.topic_title,oga.weight FROM {curriculum_topics} oga WHERE oga.cid = %d order by oga.weight asc',arg(1));
if (db_affected_rows()) {

  //$html .= '<p style="font-size:32px;"><b>Table of Contents</b></p><br>';

	while ($object = db_fetch_object($check_query)) {
		$output['fields'][$i]['topic_id'] = $object->topic_id;
		$output['fields'][$i]['topic_title'] = $object->topic_title;

		$count = $i+1;
		$html .= '<p style="font-size:32px;"><b>Topic '.$count.':'.$output['fields'][$i]['topic_title'].'</b><br>';

    //$html = "";
		$query = db_query('SELECT TA.asset,TA.id,TA.title,TA.description,TA.id FROM {curriculum_topics_assets} TA  WHERE
						   TA.topic_id = %d order by weight asc',$object->topic_id);

		if (db_affected_rows()) {
			$j = 1;
			while ($curriculum = db_fetch_object($query)) {
			if (is_numeric($curriculum->asset)) {
			$node = node_load($curriculum->asset);

			$output['fields'][$i]['subfield'][$j]['curriculum_id'] = $curriculum->id;
			$output['fields'][$i]['subfield'][$j]['asset_title'] = l(t($node->title/*." | ".$taxonomy->name*/), $node->path);

			$html .= '<p style="font-size:32px;">'.$output['fields'][$i]['subfield'][$j]['asset_title'].'</p><br>';

  		} else {
			$output['fields'][$i]['subfield'][$j]['curriculum_id']=$curriculum->id;
			$output['fields'][$i]['subfield'][$j]['asset_title']=l(t($curriculum->title),$curriculum->asset);

			$html .= '<p style="font-size:32px;">'.$output['fields'][$i]['subfield'][$j]['asset_title'].'</p><br>';

		}
		$j++;
		}
		}
		$i++;
	}
} else {
	//separate messages for student and teacher roles
	if ($user->roles[4]) {
		$output['no_topic'] = "This Playlist has no Topics.";
	}elseif ($user->roles[3]) {
		$output['no_topic'] = "This Playlist has no Topics, Click on the Add New Topic link to get started.";
	}
}
echo $html .= '<br clear="all" style="page-break-before:always" />';


  // Get Curriculum Topic
  $check_query = db_query('SELECT oga.topic_id,oga.topic_title,oga.weight FROM {curriculum_topics} oga WHERE oga.cid = %d order by oga.weight asc',arg(1));
  if (db_affected_rows()) {
    $x = 0;
    $count_topic = 0;
    $j = 0;
    while ($object = db_fetch_object($check_query)) {
    if ($j != 0)  {
      //$html .= '<br clear="all" style="page-break-before:always" />';
    }
      $j++;

       // HTML CONTENT HERE To Display Topic
      $html .= '<tr><td><p style="font-size:60px; color:#26556a; font-weight:bold;"><b>' . $object->topic_title . '</b></td></tr>';



      // Get Curriculum Sub Topic
	 $query = db_query('SELECT TA.asset,TA.id,TA.title,TA.description,TA.id FROM {curriculum_topics_assets} TA  WHERE TA.topic_id = %d order by weight asc',$object->topic_id);
 	 if (db_affected_rows()) {
	   $j = 1;
     $count_topic1 = 1;
	   while ($curriculum = db_fetch_object($query)) {
		 if (is_numeric($curriculum->asset)) {
            $node = node_load($curriculum->asset);
            // HTML CONTENT HERE To Display Sub - Topic
             $html .= '<tr>
          <td style="padding-left:30px;"><p style="font-size:32px; color:#265a79; text-decoration:underline;">' . $node->title . '</p></td>
          </tr>';

            if($node->field_custom_file_upload[0]['filename']) {

              if ($node->field_format[0]['value'] == 'PDF') {

                $html .= '<p style="font-size:32px;">View PDF Reference: ' . l($node->title, $base_url . '/node/' . $node->nid , array('attributes' => array('target' => '_blank'))) . '</p><br>';

              }
              else {
                if ($node->field_format[0]['value'] == 'VIDEO') {

                  $html .= '<p style="font-size:32px;">View Video Reference: ' . l($node->title, $base_url . '/node/' . $node->nid , array('attributes' => array('target' => '_blank'))) . '</p><br>';

                }
                elseif ($node->field_format[0]['value'] == 'AUDIO') {
                  $html .= '<p style="font-size:32px;">Listen to Audio Reference: ' . l($node->title, $base_url . '/node/' . $node->nid, array('attributes' => array('target' => '_blank'))) . '</p><br>';

                }
                else {

                  $html = $node->field_custom_file_upload[0]['filepath'];
                  $html .= "<img src='.$base_url.$html.'  />";


                }
              }
            }
            elseif ($node->field_format[0]['value'] == 'HTML') {
              if ($node->body) {

                $htm = $node->body;
                $html .= '<div style="font-size:40px !important;">'.$htm.'</div>';

              }
            }
            echo $html .= '</table>';
  		} else {
            // For External Links
 $html .= '<tr>
          <td style="padding-left:30px;"><p style="font-size:32px; color:#265a79; text-decoration:underline;">' . $node->title . '</p></td>
          </tr>';
            $html_out = '<p style="font-size:32px; color:#265a79; text-decoration:underline;">' . $curriculum->title . '</p><br>';
            $html_out = '<p style="font-size:32px;">Reference: ' . l($curriculum->title, $curriculum->asset,  array('attributes' => array('target' => '_blank')) ) . '</p><br>';

   $html .= '</table>';
		}
          $html = '';
          $j++;
          $count_topic++;
          $count_topic1++;

        }

      }
      $i++;
      $x++;
    }
  }

}
