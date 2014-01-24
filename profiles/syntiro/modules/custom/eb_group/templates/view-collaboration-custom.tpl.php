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
           <div class="main-discussion mycurriculum-not-image clearfix main-review">

               <div class="result-right">
                   <div class="result-right-inner clearfix">
                       <h3>
                           <?php print $value['title']; ?>
                       </h3>
                       <div class="links">
                            <ul class="clearfix">
                               <li><?php print $value['delete']; ?></li>
                            </ul>
                       </div>
                   </div>

                   <p>
                      <?php print $value['body']; ?>
                   </p>
                  
                   <div class="discussion-comments">
                      <ul class="clearfix">
                        <li><?php print $value['member_count']; ?></li>
                        <li class="last"><?php print $value['post_count']; ?></li>
                      </ul>
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
