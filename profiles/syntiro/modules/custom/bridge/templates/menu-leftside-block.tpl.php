<?php
// $Id: menu-leftside-blocks.tpl.php, 9/02/2012 2:17:PM Jaffar Exp $

/**
 * @file menu-leftside-blocks.tpl.php
 * Default theme implementation for listing assignments in Left side blocks.
 *
 * This template collects each invocation of theme_menu_leftside_blocks().
 *
 * Available variables:
 * - $results['assignment']: Contains Assignment contents like Assignment Title
 * - $results['heading'] : Contains Label of this block
 */
?>
<div class="sidepanel-menu">
    <ul>
    <?php if(isset($results['menu_list'])) { ?>
      <?php foreach($results['menu_list'] as $key => $value) { ?>
        <li> <?php print $value; ?></li>
      <?php } ?>
      <?php } ?>
    </ul>
</div>
