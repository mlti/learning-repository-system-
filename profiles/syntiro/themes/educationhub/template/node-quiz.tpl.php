<?php
// $Id: node-asset.tpl.php,v 1.4.2.1 2009/08/10 10:48:33 goba Exp $

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
                     <a href="<?php print $node_url; ?>" title="<?php print $title ?>"><?php print $title; ?></a>
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
                  <?php print strip_tags($content); ?>
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
         <div class="asset-edit-view node-content-common">
            <!-- Check whether was viewed in Preview mode or not -->
            <?php if (isset($quiz_link)): ?>
              <p>
                 <?php print $quiz_link; ?>
              </p>
            <?php else: ?>
              <?php print $content; ?>
            <?php endif; ?>
         </div>
   <?php } ?>

</div>

<!-- Display Add new comments for this content type -->
<?php if ($page == 1): ?>
   <?php print $commentform;  ?>
   <!--Print Actions Buttons Starts here-->
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
   <!--Print Actions Buttons Ends here-->
<?php endif; ?>
