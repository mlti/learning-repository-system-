<?php
// $Id: assignment_common_block.inc, 2011/09/21 Jaffar Exp $
/**
 * @file
 * Handling report for assignment module
 */


/**
 * It contains assignment reports
 *
 * The block function displays the total, completed and pending assignments.
 *
 * @param $cid
 *   It Contains the curriculum ID
 *
 * @return $results
 *   It contains Themed output.
 *
 * @see theme_assignment_report_block().
 *
 */
function assignment_report_block() {
   global $base_url;
  $cid = arg(1);
  $assignment['total_assignment'] = count_assignments($cid);
  $assignment['completed_assignment'] = count_assignments($cid, 2);
  $assignment['pending_assignment'] = count_assignments($cid, 1);
  $arrow_image = theme_image(drupal_get_path('theme', 'educationhub') . "/images/title-arrow.gif");
  $assignment['link'] =  l('Go',  'assignment/reports/' . $cid, array('attributes' => array('class' => 'manual-report-link'),'html' => TRUE));
 //Theme function for assignment-report-block
  $results = theme('assignment_report_block', $assignment);
  return $results;
}

