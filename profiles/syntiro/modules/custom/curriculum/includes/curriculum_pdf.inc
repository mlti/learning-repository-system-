<?php
// $Id: curriculum_word.inc,v 1.0 2011/08/19 Exp $

/**
 * @file
 * This module implements the Convert to PDF functionality for Curriculum
 */

/**
 * Curriulum as pdf output
 */
function curriculum_overview_pdf($node_obj) {
  global $base_url;
  //inlcuding TCPDF files
  $tcpdf_path = drupal_get_path('module', 'curriculum') .'/tcpdf';
  require_once($tcpdf_path .'/config/lang/eng.php');
  require_once($tcpdf_path .'/tcpdf.php');

  // Extend the TCPDF class to create custom Header and Footer
  class MYPDF extends TCPDF {
    //Page header
    public function Header() {
      // Logo
      $tcpdf_path = drupal_get_path('module', 'curriculum') . '/tcpdf';
      $image_file = $tcpdf_path . '/images/edu.jpg';
      //$this->Image($image_file, '10', '10', '190', '', '', '', 'T', FALSE, 300, '', FALSE, FALSE, 0, FALSE, FALSE, FALSE);
    }

  	// Page footer
    public function Footer() {
      // Position at 15 mm from bottom
      $this->SetY(-15);
      // Set font
      $this->SetFont('helvetica', '', 8);
      // Page footer
      $html = '&copy; 2012. EducationHub. All Rights Reserved.';
      // print a block of text using Write()
      $this->writeHTML($html, TRUE, FALSE, FALSE, FALSE, '');
    }
  }

  // create new PDF document
  $pdf = new MYPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);
  // set document information
  $pdf->SetCreator(PDF_CREATOR);
  $pdf->SetAuthor('Nicola Asuni');
  $pdf->SetTitle('TCPDF Example 003');
  $pdf->SetSubject('TCPDF Tutorial');
  $pdf->SetKeywords('TCPDF, PDF, example, test, guide');

  // set default header data
  $pdf->SetHeaderData(PDF_HEADER_LOGO, PDF_HEADER_LOGO_WIDTH, PDF_HEADER_TITLE, PDF_HEADER_STRING);

  // set header and footer fonts
  $pdf->setHeaderFont(Array(PDF_FONT_NAME_MAIN, '', PDF_FONT_SIZE_MAIN));
  $pdf->setFooterFont(Array(PDF_FONT_NAME_DATA, '', PDF_FONT_SIZE_DATA));

  // set default monospaced font
  $pdf->SetDefaultMonospacedFont(PDF_FONT_MONOSPACED);

  //set margins
  $pdf->SetMargins(PDF_MARGIN_LEFT, 40, PDF_MARGIN_RIGHT);
  $pdf->SetHeaderMargin(PDF_MARGIN_HEADER);
  $pdf->SetFooterMargin(PDF_MARGIN_FOOTER);

  //set auto page breaks
  $pdf->SetAutoPageBreak(TRUE, PDF_MARGIN_BOTTOM);

  //set image scale factor
  $pdf->setImageScale(PDF_IMAGE_SCALE_RATIO);

  //set some language-dependent strings
  $pdf->setLanguageArray($l);

  // set font
  $pdf->SetFont('trebucbd', 'B', '');
  // set Axis
  $pdf->SetY(500);
  // add a page
  $pdf->AddPage();

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
	$node_author = create_eduauthor($node_obj->uid, NULL, TRUE);
  // Set Cover Page Design
  $html = <<<EOD
              <table width="600">
                <tr>
                  <td height="105">&nbsp;</td>
                </tr>
                <tr>
                  <td style="text-align:left; font-size:70px;color:#ed6500;">$node_obj->title</td>
                </tr>
                <tr>
                  <td style="text-align:left; color:#595959;">Author: <span style="color:#9d402b; text-decoration:underline;">$node_author</span></td>
                </tr>
EOD;
  if ($coauthor) {
    $html .= <<<EOD
        <tr>
          <td style="text-align:left; color:#595959;">Co-Author: $coauthor</td>
        </tr>
EOD;
  }
  if ($reviewers) {
    $html .= <<<EOD
        <tr>
          <td style="text-align:left; color:#595959;">Reviewers: $reviewers</td>
        </tr>
EOD;
  }
  $html .= <<<EOD
            </table>
EOD;

  // print a block of text using Write()
  $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');

  // Add a page
  $pdf->AddPage();

  // Set some content to print
  $pdf->SetFont('trebucbd', 'B', '');
  // To Dispaly Description of the Curriculum
  if ($node_obj->body) {
    // This bookmark method is used to navigate between pages.
    $pdf->Bookmark("Description", 0, 0, '', 'B', array(0,64,128));
     $html = <<<EOD
      <span style="font-size:60px; color:#26556a; font-weight:bold;">Description</span>
EOD;
    $html .= '<p><b>' . $node_obj->body . '</b></p><br>';
    $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
    $pdf->AddPage();
  }
  // Get Curriculum Topic
  $check_query = db_query('SELECT oga.topic_id,oga.topic_title,oga.weight FROM {curriculum_topics} oga WHERE oga.cid = %d order by oga.weight asc',arg(1));
  if (db_affected_rows()) {
    $x = 0;
    $count_topic = 0;
    $j = 0;
    while ($object = db_fetch_object($check_query)) {
			if ($j != 0)  {
				$pdf->AddPage();
			}
      $j++;
      //$pdf->SetFont('trebuchet', '', 10, '', true);
      // set a bookmark for the current position
      $pdf->Bookmark($object->topic_title, 0, 0, '', 'B', array(0,64,128));
      $html = '<p style="font-size:60px; color:#26556a; font-weight:bold;"><b>'.$object->topic_title . '</b><br>';
      $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
      $html = "";
      // Get Curriculum Sub Topic
			$query = db_query('SELECT TA.asset,TA.id,TA.title,TA.description,TA.id FROM {curriculum_topics_assets} TA  WHERE TA.topic_id = %d order by weight asc',$object->topic_id);
			if (db_affected_rows()) {
				$j = 1;
        $count_topic1 = 1;
				while ($curriculum = db_fetch_object($query)) {
					if (is_numeric($curriculum->asset)) {
            $node = node_load($curriculum->asset);

            if ($node->field_format[0]['value'] == 'IMAGE') {
              $pdf->AddPage();
            }
            $html = '<div style="font-size:50px !important; color:#265a79; text-decoration:underline;">' . $node->title . '</div><br>';
            // This writeHTML method will print the contents in PDF.
            $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
            if($node->field_custom_file_upload[0]['filename']) {
              if ($node->field_format[0]['value'] == 'PDF') {
                $html = '<p style="font-size:32px;">View PDF Reference: ' . l($node->title, $base_url .'/' . $node->path , array('attributes' => array('target' => '_blank'))) . '</p><br>';
                $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
              }
              else {
                if ($node->field_format[0]['value'] == 'VIDEO') {
                  $html = '<p style="font-size:32px;">View Video Reference: ' . l($node->title,  $base_url . '/' . $node->path, array('attributes' => array('target' => '_blank'))) . '</p><br>';
                  $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
                }
                elseif ($node->field_format[0]['value'] == 'AUDIO') {
                  $html = '<p style="font-size:32px;">Listen to Audio Reference: ' . l($node->title,   $base_url . '/' . $node->path, array('attributes' => array('target' => '_blank'))) . '</p><br>';
                  $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
                }
								elseif ($node->field_format[0]['value'] == 'DOCUMENT') {
                  $html = '<p style="font-size:32px;">View Document Reference: ' . l($node->title, $base_url . '/' . $node->path, array('attributes' => array('target' => '_blank'))) . '</p><br>';
                  $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
                }
								elseif ($node->field_format[0]['value'] == 'EXCEL') {
                  $html = '<p style="font-size:32px;">View Excel Reference: ' . l($node->title, $base_url . '/' . $node->path, array('attributes' => array('target' => '_blank'))) . '</p><br>';
                  $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
                }
								elseif ($node->field_format[0]['value'] == 'PRESENTATION') {
                  $html = '<p style="font-size:32px;">View Presentation Reference: ' . l($node->title, $base_url . '/' . $node->path, array('attributes' => array('target' => '_blank'))) . '</p><br>';
                  $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
                }
                else {
                  $html = $node->field_custom_file_upload[0]['filepath'];
                  $pdf->Image($html, '', '', '', '', '', '', 'T', TRUE, 300, '', FALSE, FALSE, 0, FALSE, FALSE, TRUE);
                  $pdf->AddPage();
                }
              }
            }
						elseif ($node->field_format[0]['value'] == 'HTML') {
              if ($node->body) {
                $html = preg_replace("/<(?!table|img)([a-z][a-z0-9]*)[^>]*?(\/?)>/i",'<$1$2>', $node->body);
                $html = '<div style="font-size:40px !important;">'.$html.'</div>';
                $pdf->writeHTML($html, TRUE, TRUE, TRUE, FALSE, '');
                $pdf->AddPage();
              }
            }
						else {
              if ($node->body) {
                $html = preg_replace("/<(?!table)([a-z][a-z0-9]*)[^>]*?(\/?)>/i",'<$1$2>', $node->body);
                $html = '<div style="font-size:40px !important;">'.$html.'</div>';
                $pdf->writeHTML($html, TRUE, TRUE, TRUE, FALSE, '');
                $pdf->AddPage();
              } else {
                $html = '<div style="font-size:40px !important;">No Content</div>';
                $pdf->writeHTML($html, TRUE, TRUE, TRUE, FALSE, '');
                $pdf->AddPage();
              }
            }
          }
					else {
            // For External Links
            $pdf->SetFont('trebuchet', '', 4, '', true);
            $pdf->Bookmark($curriculum->title, 1, 0, '', '', array(128,0,0));
            $html = '<p style="font-size:32px; color:#265a79; text-decoration:underline;">' . $curriculum->title. '</p><br>';
            $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
            $html = '<p style="font-size:32px;">Reference: ' . l($curriculum->title, $curriculum->asset,  array('attributes' => array('target' => '_blank')) ) . '</p><br>';
            $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
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

  $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
  $pdf->addPage();
  // write the TOC title
  $pdf->SetFont('trebucbd', 'B', '');
  $html = <<<EOD
            <table width="500">
              <tr>
                <td height="35" style="font-size:60px;color:#355f91;">Table Of Contents</td>
              </tr>
          </table>
EOD;
	
  $pdf->writeHTML($html, TRUE, FALSE, TRUE, FALSE, '');
  $i=0;


  // A monospaced font for the page number is mandatory to get the right alignment
  $bookmark_templates[0] = '<table border="0" cellpadding="0" cellspacing="0"><tr><td width="155mm" height="10mm"><span style="font-family:trebucbd;font-weight:bold;font-size:14pt;color:#26556a;">#TOC_DESCRIPTION#</span></td></tr></table>';
  $pdf->addHTMLTOC(2, 'INDEX', $bookmark_templates, true, '', array(128,0,0));//
  $output_file = $node_obj->title . '.pdf';

  /*Second argument of the following function $pdf->Output(), having four options.
	I: send the file inline to the browser.
  D: send to the browser and force a file download with the name given by name.
  F: save to a local file with the name given by name.
  S: return the document as a string.*/

	$pdf->Output($output_file, 'D');

}
