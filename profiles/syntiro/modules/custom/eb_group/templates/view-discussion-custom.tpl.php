<?php
// $Id: view-discussion-custom.tpl.php,v 1.1 2011/8/8 9:15:AM Exp $
/**
 * @file view-discussion-custom.tpl.php
 * Default theme implementation for displaying discussion results.
 *
 * This template collects each invocation of theme_view_discussion_custom(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 *
 * Available variables:
 * - $results: All results as it is rendered through
 *   view-discussion-custom.tpl.php
 *
 *
 * @see template_preprocess_view_discussion_custom(()
 */
?>
     <div class="result" id="comments-result-area">
        <?php if (!$results['no_comment_content'] ):?>
            <?php foreach ($results['fields'] as $value) {?>
                <div class="main-discussion mycurriculum-not-image clearfix main-review<?php print $value['visited'] ?>">
                     <div class="result-right">
                        <div class="result-right-inner clearfix">
                            <h3>
                                <?php print $value['title']; ?>
                            </h3>
                            <div class="links">
                               <ul class="clearfix">
                                <li><?php print $value['bookmark']; ?></li>
                                <li><?php print $value['recommend']; ?></li>
                               </ul>
                            </div>
                        </div>

                        <p>
                           <?php print $value['body']; ?>
                        </p>

                        <div class="discussion-comments">
                           <ul class="clearfix">
                             <li><?php print $value['comment_count'] . $value['comment_plural']; ?></li>
                             <li class="last group-link"><?php print $value['course_group']; ?></li>
                           </ul>
                        </div>
                    </div>
                </div>
            <?php } ?>
            <div id="comments-pager">
               <?php print $results['pager']; ?>
            </div>
        <?php else :?>
            <div class="no-content"><?php print $results['no_comment_content']; ?></div>
        <?php endif; ?>
     </div>
