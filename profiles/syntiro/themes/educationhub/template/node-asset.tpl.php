<?php
// $Id: node-asset.tpl.php, 2012/01/9 4:42:PM goba Exp $

/**
 * @file node-asset.tpl.php
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
global $base_url;
?>

<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?> node-preview">
   <?php if ($page == 0) { ?>
      <div class='teaser-view'>
         <div class="result-right">
            <div class="result-right-inner clearfix">
               <div>
                  <h3>
                     <a href="<?php print $base_url . '/node/' . $node->nid; ?>" title="<?php print $title ?>"><?php print $title; ?></a>
                  </h3>
               </div>
               <?php if ($name): ?>
                  <div class="author-name">
                     <span>
                       <?php print $name; ?>
                     </span> |
                     <span class="node-relate-type">
                       <?php print node_get_types('name', $node); ?>
                     </span>
                  </div>
               <?php endif; ?>
            </div>
            <div class="content">
               <?php if( $node->field_format[0]['value'] == 'HTML') { ?>
                  <?php print strip_tags($content); ?>
               <?php } else { ?>
                  <?php print strip_tags($field_content); ?>
               <?php } ?>
            </div>
            <div class="discussion-comments">
               <ul class="clearfix">
                   <li class="last"><a href="<?php print $base_url . '/node/' . $node->nid; ?>" > <?php print $comment_count; ?> </a></li>
               </ul>
            </div>

         </div>
      </div>
   <?php } ?>

   <?php if ($page == 1) { ?>
      <?php if ($node_edit_link) { ?>
         <input type="hidden" id="node-edit-link" value="<?php print $node_edit_link; ?>">
      <?php } ?>
      <?php if ($tooltip_content) { ?>
         <div title="Click to Edit this Asset">
      <?php } ?>
      <?php if (!isset($no_record)){ ?>
         <div class="asset-edit-view node-content-common">
            <?php print $content; ?>

            <?php  if (isset($iframe_src)): ?>
               </div>
               <div class="course-image-description metadata-border node-content-common">
                  <span class="iframe-content text-center"><iframe src="<?php print $iframe_src; ?>" height="<?php print $asset_height; ?>" width="100%" ></iframe></span>
               </div>
            <?php endif; ?>
            <?php if (isset($video)): ?>
               <span>
                  <?php print $video; ?>
               </span>
            <?php endif; ?>
            <?php if (isset($video_link)): ?>
               <p>
                  <?php print $video_link; ?>
               </p>
            <?php endif; ?>
            
            <?php if (isset($image)) { ?>
               <span><?php print $image; ?></span>
            <?php } ?>
         <?php  if (!isset($iframe_src)): ?></div><?php endif; ?>
      <?php } ?>
      <?php // To display body only if not equal to empty ?>
      <?php if (isset($no_record)): ?>
       <div class="asset-edit-view node-content-common node-empty-content">
        <?php print $no_record; ?>
       </div>
     <?php endif; ?>
     <?php if (isset($tooltip_content)) { ?>
         </div>
      <?php } ?>
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
