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
<div class="title-bg title-arrow-bg clearfix"><h2>Assigned Members</h2>
 <span><a title="More Members" href="<?php print $more_link; ?>"><img src="<?php print $more_link_image; ?>/images/title-arrow.gif"></a></span>
</div>
<?php if ($assignment_members_block) { ?>
  <div class="item-list">
    <div class="member-lists">
      <div class="members-right-block">

              <ul class="clearfix">
              <?php foreach($assignment_members_block as $key => $value) {
               //Generate odd or even class for <td> tag.
               if($key % 2 == 0){
                $class = 'even';
               }
               else{
                $class = 'odd';
               }
               if($key < 6){
               ?>
               <li class="<?php print $class; ?>">
                <div class="similar-content small-image-block">
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
                  </div>
                </div>
                </li>
              <?php }
              }?>
              </ul>
      </div>
    </div>
  </div>
<?php }
else{ ?>
  <div class="no-content"><?php print $assignment_member_block_null; ?></div>
<?php }  ?>
