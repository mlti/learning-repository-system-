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
//echopre($row);
?>

<div id="comments-result-area" class="result group-result-area">
  <div class="clearfix groups-checkbox">
    <div class="result-left"> <?php print $row['chk']; ?><?php print $row['hide'];  ?> </div>
    <div class="result-right">
      <div class="result-right-inner clearfix">
        <h3>
          <?php print $row['title']; ?>
        </h3>
      </div>
      <p><?php print $row['desc']; ?></p>
      <div class="discussion-comments">
        <ul class="clearfix">
          <li><?php print $row['members']; ?></li>
          <li class="last"><?php print $row['dis']; ?></li>
        </ul>
      </div>
    </div>
    <!--<div class="undo-icon">
      <?php //print $undo_assigned_group; ?>
    </div>-->
  </div>
</div>
