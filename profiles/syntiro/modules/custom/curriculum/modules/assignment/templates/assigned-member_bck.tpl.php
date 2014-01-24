<?php
// $Id: assigned-members.tpl.php, 09/08/2011 3:17:PM Jaffar Exp $

/**
 * @file assigned-member.tpl.php
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_assigned_member(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *

 *
 * Available variables:
 * - $assigned_result:
 *
 *
 * @see template_preprocess_assigned_member()
 */

?>
<?php if ($assigned_result) { ?>
  <div class="item-list">
    <div  class="member-list-view">
      <div class="views-view-grid assigned-to-member">
          <ul class="clearfix">
            <?php foreach($assigned_result as $key => $value) { ?>
              <li>
                <div class="similar-content">
                  <div class="result-left">
                    <div class="img">
                      <?php print $value['image']; ?>
                    </div>
                  </div>
                  <div class="result-right result-left-image-block ">
                    <div class="result-right-inner clearfix ">
                      <h3>
                        <?php print $value['name']; ?>
                      </h3>
                    </div>
                    <div class="contact-icon">
                      <?php print $value['contact']; ?>
                    </div>
                    <!--<div class="undo-icon">
                      <?php //print $value['undo']; ?>
                    </div>-->
                  </div>
                </div>
              </li>
            <?php } ?>
          </ul>
      </div>
    </div>
  </div>
<?php }
else{ ?>
  <div class="no-content"><?php print $assigned_member_null;?></div>
<?php }  ?>
<div id="rec-pager">
  <?php print $pager; ?>
</div>
