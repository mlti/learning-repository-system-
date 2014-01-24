<?php
// $Id: bridge-leftside-blocks.tpl.php, 25/08/2011 2:17:PM Jaffar Exp $

/**
 * @file bridge-leftside-blocks.tpl.php
 * Default theme implementation for listing assignments in Left side blocks.
 *
 * This template collects each invocation of theme_bridge_leftside_blocks().
 *
 * Available variables:
 * - $results['assignment']: Contains Assignment contents like Assignment Title
 * - $results['heading'] : Contains Label of this block
 */
?>


<div class="listing-common-box">
  <div class="discussion-date-time"><?php print $results['heading']; ?>  </div>
  <div class="clearfix common-listing-content">
    <div class="float-left image-common assignment-listing">
        <?php if ($results['fields']['picture']) { ?><div class="mem-image"> <?php print $results['fields']['picture']; ?> </div><?php } ?>
        <?php if ($results['fields']['user_name']) { ?><div class="mem-name"><?php print $results['fields']['user_name']; ?></div><?php } ?>
     
    </div>
    <div class="listing-common-desc">
     <?php if($results['fields']['posted_date'] || $results['fields']['body']) { ?><div class="posted-by"><?php print $results['fields']['posted_date']; ?></div><p><?php print $results['fields']['body']; ?></p>
                          
                            
                        <?php } ?>
    </div>
  </div>
  <div class="listing-common-footer"></div>
</div>

