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
///echopre($row);
?>
<li class="<?php print $zebra;?>">
  <div class="similar-content assigned-members-content">
    <div class="member-img">
      <div class="img">
        <?php print $row['img'];?>
      </div>
    </div>
    <div class="member-detail">
      <div class="member-detail-inner clearfix ">
          <?php print $row['chk'];?>
          <span>
            <?php print $row['name'];?>
          </span>
          <?php if($row['contact']): ?>
        <span class="contact-icon-user">
          <?php print $row['contact'];?>
        </span>
      <?php endif; ?>
      </div>
      
      <?php if($row['reassign'] || $row['delete']): ?>
        <div class="undo-icon clearfix">
         <?php print $row['reassign'];?>
         <span class="delete-icon"><?php print $row['delete'];?></span>
        </div>
      <?php endif; ?>
   </div>
  </div>
</li>
