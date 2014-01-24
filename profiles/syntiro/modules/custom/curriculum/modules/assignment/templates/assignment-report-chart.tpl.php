<?php
// $Id: assignment-report-chart.tpl.php, 22/09/2011 11:30:AM Jaffar Exp $

/**
 * @file aassignment-report-chart.tpl.php
 *  Default theme implementation for Assignment reports in Right side blocks.
 *
 * This template collects each invocation of theme_assignment_report_chart().
 *
 * Available variables:
 * - $results['total_assignment']: Contains Total assignment
 * - $results['completed_assignment'] : Contains Completed assignment
 * - $results['pending_assignment'] : Contains Pending assignment
 */
?>
<div class="assignment-border common-list-wrapper">
    <div class="common-list-drop-preview" style="display:none">
   </div>
   <div class="common-list-drop">  <!-- <a title="results" href="#">Sort</a>--> </div>
 <?php if ($results['node_title'] || $results["group_list"]) { ?>
    <div class="clearfix">
      <?php if ($results['node_title']) { ?>
         <div class="node-title float-left">
           <?php print $results['node_title']; ?>
         </div>
       <?php } ?>
       <?php if($results["back"]) { ?>
         <div class="back-to float-right">
           <?php print $results["back"] ?>
         </div>
       <?php } ?>
  <?php if($results["group_list"]) { ?>
         <div class="assignment-group-list selected-dropdown float-right">
      <?php print $results["group_list"] ?>
    </div>
  <?php } ?>
    </div>
  <?php } ?>

  <div class="assignment-reports-level1">
    <?php if($results["results"]) { ?>
      <div class="assignment-chart">
      <?php if($results["chart"]) { print $results["chart"]; } ?>
      </div>
      <div class="assignment-topic-list">
        <div class="assignment-topic">
          <?php print $results["results"] ?>
        </div>
        <?php if($results["pager"]) { ?>
        <div class="assignment-topic-pager">
        <?php print $results["pager"] ?>
        </div>
        <?php } ?>
      </div>
    <?php } else { ?>
      <div>
        <?php print $results['no_content']; ?>  
      </div>
    <?php } ?>
  </div>
</div>
