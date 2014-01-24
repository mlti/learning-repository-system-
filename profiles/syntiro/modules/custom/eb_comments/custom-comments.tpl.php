<?php
// $Id$
/**
 * @file
 * Displaying comments for particular content type - custom display - template file
 */
?>
     <div class="result" id="comments-result-area">
        <?php if (!$results['no_record'] && !$results['no_comment_content'] ): ?>
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
                            <?php if ($value['edit_comment']) { ?>
                                <div class="links">
                                   <ul class="clearfix">
                                      <li>
                                         <?php print $value['edit_comment']; ?>
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
            <div id="comments-pager">
               <?php print $results['pager']; ?>
            </div>
        <?php else :?>
            <span><?php print $results['no_record']?$results['no_record']:$results['no_comment_content']; ?></span>
        <?php endif; ?>
     </div>
