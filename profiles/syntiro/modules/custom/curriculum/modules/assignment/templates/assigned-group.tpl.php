<?php
// $Id: assigned-listing.tpl.php, 09/08/2011 9:15:PM Saravana Exp $

/**
 * @file assigned-listing.tpl.php
 * Default theme implementation for listing assignments.
 *
 * This template collects each invocation of theme_assigned_listing().
 *
 * Available variables:
 * - $assignment_result: Contains Assignment contents like Assignment Title, Assigner name, Assigner Message.
 * - $assigner_label : Contains Assigner Label (Assigned by: )
 * - $assignment_null : Contains Null content for Assignment listing page
 * - $pager : Contains Pager content.
 * @see template_preprocess_assigned_listing()
 */
?>
<?php if($assigned_group_result){ ?>
<div id="comments-result-area" class="result group-result-area">
 <?php foreach($assigned_group_result as $key => $value){ ?>
  <div class="main-discussion mycurriculum-not-image clearfix main-review">
    <div class="result-right">
      <div class="result-right-inner clearfix">
        <h3>
          <?php print $value['title']; ?>
        </h3>
      </div>
      <p><?php print $value['desc']; ?></p>
      <div class="discussion-comments">
        <ul class="clearfix">
          <li><?php print $value['members']; ?></li>
          <li class="last"><?php print $value['dis']; ?></li>
        </ul>
      </div>
    </div>
    <!--<div class="undo-icon">
      <?php //print $undo_assigned_group; ?>
    </div>-->
  </div>
<?php } ?>
</div>
<?php } else { ?>
  <div class="no-content"><?php print $assigned_group_null;?></div>
<?php } ?>
<div id="rec-pager">
  <?php print $pager; ?>
</div>
