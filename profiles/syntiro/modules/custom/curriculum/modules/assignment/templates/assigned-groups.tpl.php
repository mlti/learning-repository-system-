<?php
// $Id: assigned-groups.tpl.php, 28/09/2011 3:00:PM Feroze Exp $
/**
 * @file assigned-groups.tpl.php
 * Default theme implementation for displaying assigned groups.
 *
 * This template collects each invocation of theme_assigned_member(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 * @see template_preprocess_assigned_group()
 */
//echopre($content2);
?>
<?php if($content2 == '') { ?>
<div class="clearfix">
<div class="members-list-assignment">
  <div class="unassign"><?php print $content1; ?></div>
</div>
</div>

<?php print $content; ?>
<?php } else { ?>
<?php print $content2; ?>
<?php } ?>
