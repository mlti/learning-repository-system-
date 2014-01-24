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
<?php if($content3 == '') { ?>
<div class="clearfix">
<div class="members-list-assignment float-right">
  <div class="unassign float-left"><?php print $content1; ?></div>
  <div class="dropdown float-right"><?php print $content2; ?></div>
</div>
</div>

<div class="item-list">
  <div  class="member-list-view">
    <div class="views-view-grid assigned-to-member">
      <ul class="clearfix">

      <?php print $content; ?>

      </ul>
    </div>
  </div>
</div>
<?php } else { ?>
<?php print $content3; ?>
<?php } ?>
