<?php
// $Id: assignment-report-view.tpl.php, 06/10/2011 03:30:PM Feroze Exp $

/**
 * @file aassignment-report-view.tpl.php
 *  Default theme implementation for Assignment reports in Right side blocks.
 *
 * This template collects each invocation of theme_assignment_report_view().
 *
 * Available variables:
 * - $results['group_list']: Contains group list
 * - $results['group_list']: Contains status list
 * - $results['$results'] : Contains results
 * - $results['pager'] : Contains Pager
 */

?>

<div class="clearfix user-name-report common-list-wrapper">
  <div class="common-list-drop-preview" style="display:none">
   </div>
   <div class="common-list-drop">  <!-- <a title="results" href="#">Sort</a>--> </div>
   
   <?php if ($results['node_title'] || $results['back']) { ?>
    <div class="clearfix">
      <?php if ($results['node_title']) { ?>
        <div class="node-title float-left">
          <?php print $results['node_title']; ?>
          <?php if ($results['subtopic_title']) { ?>
            <?php print $results['subtopic_title']; ?>
          <?php } ?>
        </div>
      <?php } ?>
      <?php if ($results['back']) { ?>
        <div class="back-to float-right"><?php print $results['back']; ?></div>
      <?php } ?>
    </div>
  <?php } ?>
  <div class="assign-report-left">
    <?php print $results["username_search"] ?>
  </div>
  <div class="username-list">  
  </div>
  

<div class="assign-report-right">

<?php if($results["group_list"]) { ?>
  <div class="assignment-group-list selected-dropdown">
    <?php print $results["group_list"] ?>
  </div>
<?php } ?>
  <div class="selected-dropdown assignment-group-list">
    <?php print $results["status_list"] ?>
  </div>
<?php if($results["topic_list"]) { ?>
  <div class="assignment-group-list selected-dropdown">
    <?php print $results["topic_list"] ?>
  </div>
<?php } ?>
</div>
</div>

<?php if($results["results"]) { ?>
  <div class="assignment-topic-list">
    <div class="assignment-topic report-level-two">
      <?php print $results["results"] ?>
    </div>
    <?php if($results["pager"]) { ?>
      <div class="assignment-topic-pager">
        <?php print $results["pager"] ?>
      </div>
    <?php } ?>
  </div>
<?php } ?>
