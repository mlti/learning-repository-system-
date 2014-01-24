<?php
// $Id: view-collaboration-custom.tpl.php,v 1.1 2011/8/8 9:15:AM Exp $
/**
 * @file view-collaboration-custom.tpl.php
 * Default theme implementation for displaying Community interest group listing page.
 *
 * This template collects each invocation of theme_view_collaboration_custom(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 *
 * Available variables:
 * - $results: All results as it is rendered through
 *   view-discussion-custom.tpl.php
 *
 *
 * @see template_preprocess_view_collaboration_custom()
 */
?>
<div class='community-top-image'><?php print $results['top_image']; ?></div>
<div class="result" id="comments-result-area">
  <?php if ($results['create_button']) { ?>
    <div class="create-button-right text-right">
      <span class="btn-center">
        <?php print $results['create_button']; ?>
      </span>
    </div>
  <?php } ?>
   <?php if (!$results['no_group_content'] ):?>
       <?php foreach ($results['fields'] as $value) {?>
           <div class="community-main-discussion<?php print $value['class']; ?>">
               <div class="community-list-page">
                   <div class="result-right-inner clearfix">
                       <div class="communitylist">
                           <?php print $value['title']; ?>
                       </div>
                   </div>
               </div>
           </div>
       <?php } ?>
       <div id="comments-pager">
          <?php print $results['pager']; ?>
       </div>
   <?php else :?>
       <div class="no-content"><?php print $results['no_group_content']; ?></div>
   <?php endif; ?>
</div>
