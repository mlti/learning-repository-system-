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
global $base_url;
?>
<div class="title-bg title-arrow-bg clearfix">
 <h2>Assigned Communities</h2>
 <span><a title="Members" href="<?php print $more_link; ?>"><img src="<?php print $more_link_image; ?>/images/title-arrow.gif"></a></span>
</div>
<?php if($assignment_group_block){ ?>
<div id="comments-result-area" class="result group-result-area">
 <?php foreach($assignment_group_block as $key => $value){
  if($key < 6){?>
  <div class="main-discussion mycurriculum-not-image clearfix main-review">
    <div class="result-right">
      <div class="result-right-inner member-count clearfix">
        <h3>
          <?php print $value['title']; ?>
        </h3>
        <div class="group-members-count">
          <?php print $value['members']; ?>
        </div>
      </div>
     </div>
    <!--<div class="undo-icon">
      <?php //print $undo_assigned_group; ?>
    </div>-->
  </div>
<?php }
}?>
</div>
<?php } else { ?>
  <div class="no-content"><?php print $assignment_group_block_null;?></div>
<?php } ?>
