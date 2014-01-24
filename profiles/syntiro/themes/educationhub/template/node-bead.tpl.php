<?php
// $Id: node-bead.tpl.php,v 1.4.2.1 2009/08/10 10:48:33 goba Exp $

/**
 * @file node-bead.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 *
 * Node status variables:
 * - $page: Flag for the full page state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $commentform: Add new comments form of the node.
 *
 * @see template_preprocess_node()
 */
?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?> node-preview">
   <?php if (!$page): ?>
      <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
   <?php endif; ?>

   <?php  if ($iframe_src && $node->field_format[0]['value'] == 'PDF'): ?>
      <div class="course-image-description metadata-border node-content-common">
         <span><iframe src="<?php print $iframe_src; ?>" height="650px" width="600px" ></iframe></span>
      </div>
   <?php endif; ?>

  <?php if ($video  && $node->field_format[0]['value'] == 'VIDEO'): ?>
      <div class="asset-video">
          <span>
              <!--<embed height="100%" width="100%" name="plugin" src="" type="video/quicktime">-->
              <?php print $video; ?>
          </span>
      </div>
  <?php endif; ?>
  <?php if ($image && $node->field_format[0]['value'] == 'IMAGE') { ?>
    <div class="course-image-description metadata-border node-content-common">
      <span><?php print $image; ?></span>
    </div>
  <?php } ?>
  <?php // To display body only if iframe & video & image equal to empty ?>
  <?php if($body != '' && $node->field_format[0]['value'] == 'HTML') { ?>
    <div class="asset-edit-view node-content-common">
      <?php print $body; ?>
    </div>
  <?php } ?>

  <?php if ($no_record): ?>
    <div class="asset-edit-view node-content-common">
      <?php print $no_record; ?>
    </div>
  <?php endif; ?>
  <!--Print Adobe Prompt message -->
  <?php if (isset($adobe_message)) {?>
    <?php print $adobe_message; ?>
  <?php } ?>
  <!--Print Actions Buttons -->
  <?php if (isset($actions)) {?>
      <div class="art-actions">
         <div class="clearfix">
            <!-- Five Star Ratings  -->
            <?php if (isset($fivestar_label) && $fivestar_widget){ ?>
               <div class="rating float-left clearfix">
                  <span><?php print $fivestar_label; ?></span>
                  <?php print $fivestar_widget; ?>
               </div>
            <?php } ?>
            <?php if (isset($actions_options)): ?>
              <div class="action-main float-left">
                 <div class="action-main-button">
                    <?php if (isset($actions)): ?>
                       <?php print $actions; ?>
                    <?php endif; ?>
                 </div>
                 <div class="action-buttons element-invisible">
                    <?php if (isset($actions_options)): ?>
                       <?php print $actions_options; ?>
                    <?php endif; ?>
                 </div>
              </div>
            <?php endif; ?>
            <?php if (isset($view_count)): ?>
               <div class="views-count float-right"><?php print $view_count; ?></div>
            <?php endif; ?>
         </div>
         <?php if (isset($share_form)) { ?>
            <div class="art-actions-block share-form-block" style="display: none">
               <a class="close" title="Close" href="#">Close</a>
               <div class="clearfix">
                 <?php print $share_form; ?>
               </div>
            </div>
         <?php } ?>
         <?php if (isset($recommend_form)) { ?>
            <div class="art-actions-block assign-form-block" style="display: none">
               <?php print $recommend_form; ?>
            </div>
         <?php } ?>
      </div>
   <?php } ?>
</div>


<?php if ($page == 1): ?>
 <?php if($commenttab || $reviewstab): ?>
   <div class="clear-block" id="tabs-wrapper">
    <ul class="comment-review-tabs primary tabs">
      <?php if(isset($commenttab)): ?>
        <li class="comment-tab"><?php print $commenttab; ?></li>
      <?php endif; ?>
      <?php if(isset($reviewstab)): ?>
        <li class="review-tab"><?php print $reviewstab; ?></li>
      <?php endif; ?>
    </ul>
   </div>
 <?php endif; ?>
<?php endif; ?>

<!-- Display Add new comments for this content type -->
<?php if ($page == 1 && isset($commentform)): ?>
   <?php print $commentform;  ?>
<?php endif; ?>


<?php if ($page == 1 && isset($reviewsform)): ?>
 <div class="review-box">
  <div class="content">
   <?php print $reviewsform;  ?>
  </div>
 </div>
<?php endif; ?>

<?php if($reviews_listing): ?>
 <div id="reviews">
   <div class="reviews-list">
     <?php print $reviews_listing; ?>
   </div>
 </div>
<?php endif; ?>
