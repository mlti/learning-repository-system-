<?php
// $Id: assignment-report-block.tpl.php, 21/09/2011 7:13:PM Jaffar Exp $

/**
 * @file assignment-report-block.tpl.php
 *  Default theme implementation for Assignment reports in Right side blocks.
 *
 * This template collects each invocation of theme_assignment_report_block().
 *
 * Available variables:
 * - $results['total_assignment']: Contains Total assignments 
 * - $results['completed_assignment'] : Contains Completed assignments
 * - $results['pending_assignment'] : Contains Pending assignments
 */
?>
<div class="sidebar-info-block" >
  <div class="view-header">
<div class="title-bg title-arrow-bg clearfix"><h2> Reports </h2>
      <?php print $results['link']; ?>
</div>
  </div>
  <div class="view-content">
<div class="report-list text-center">
        <ul class="clearfix">
            <li>
          <div class="assignment-list-title float-left">Total Assignments</div>
          <div class="report-count float-right"><?php print $results['total_assignment']; ?></div>
            </li>
            <li>
          <div class="assignment-list-title float-left">Completed Submissions</div>
          <div class="report-count float-right"><?php print $results['completed_assignment']; ?></div>
            </li>
            <li>
          <div class="assignment-list-title float-left">Pending Submissions</div>
          <div class="report-count float-right"><?php print $results['pending_assignment']; ?></div>
            </li>
        </ul>
    </div>
  </div>
</div>