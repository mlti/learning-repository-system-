<?php
// $Id$
/**
 * @file
 * Template file for the Reviews module - displaying reviews for a particular node
 */
?>
     <div class="result" id="reviews-result-area">
        <?php if (!$results['no_record'] && !$results['no_review_content'] ): ?>
            <?php foreach ($results['fields'] as $value) {?>
                <div class="main-discussion clearfix main-review">
                    <div class="result-left">
                        <div class="img">
                          <?php print $value['user_picture']; ?>
                        </div>
                    </div>
                    <div class="result-right">
                        <div class="result-right-inner clearfix">
                            <h3>
                                <?php print $value['title']; ?>
                            </h3>
                            <?php if ($value['edit_review'] || $value['delete_review']) { ?>
                                <div class="links">
                                   <ul class="clearfix">
                                      <li>
                                         <?php print $value['edit_review']; ?>
                                      </li>
                                      <li>
                                         <?php print $value['delete_review']; ?>
                                      </li>
                                   </ul>
                                </div>
                            <?php } ?>
                        </div>
                        <p>
                           <?php print $value['body']; ?>
                        </p>
                    </div>
                </div>
            <?php } ?>
            <div id="reviews-pager">
               <?php print $results['pager']; ?>
             </div>
        <?php else :?>
            <span><?php print $results['no_record']?$results['no_record']:$results['no_review_content']; ?></span>
        <?php endif; ?>
     </div>
