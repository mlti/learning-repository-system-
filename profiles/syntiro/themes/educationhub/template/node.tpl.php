<?php
// $Id: node.tpl.php,v 1.5 2007/10/11 09:51:29 goba Exp $
?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">

<?php print $picture ?>

<?php if ($page == 0): ?>
  <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
<?php endif; ?>

  <?php if ($submitted): ?>
    <span class="submitted"><?php print $submitted; ?></span>
  <?php endif; ?>

  <div class="content clear-block">
    <?php print $content ?>
  </div>

<!--  <div class="clear-block">
    <div class="meta">
    <?php if ($taxonomy): ?>
      <div class="terms"><?php print $terms ?></div>
    <?php endif;?>
    </div>

    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>-->


<?php if ($page == 1): ?>
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
                  <div class="action-buttons">
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
            <div class="art-actions-block share-form-block">
               <a class="close" title="Close" href="#">Close</a>
               <div class="clearfix">
                 <?php print $share_form; ?>
               </div>
            </div>
         <?php } ?>
         <?php if (isset($recommend_form)) { ?>
            <div class="art-actions-block assign-form-block">
               <?php print $recommend_form; ?>
            </div>
         <?php } ?>
      </div>
  <?php } ?>

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


</div>
