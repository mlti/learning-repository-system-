<?php
// $Id: assigned-listing.tpl.php, 09/08/2011 9:15:PM Saravana Exp $

/**
 * @file assigned-listing.tpl.php
 * Default theme implementation for listing assignments.
 *
 * This template collects each invocation of theme_assigned_listing().
 *
 * Available variables:
 * - $assignment_result: Contains Assignment contents like Assignment Title, Assigner name, Assigner Message.
 * - $assigner_label : Contains Assigner Label (Assigned by: )
 * - $assignment_null : Contains Null content for Assignment listing page
 * - $pager : Contains Pager content.
 * @see template_preprocess_assigned_listing()
 */
global $base_url;
?>
<div id="assign-result-area" class="result no-content">
    <div class="view-content ">
        <div class="item-list">
            <ul>
                <?php if(!$assignment_result['null_content']){
                    foreach($assignment_result as $key => $value) {
                ?>
                    <li class="assignment-list <?php print $value['selected']; ?>">
                       <div class="result-right">
                          <div class="asset-teaser"><?php print $value['title']; ?></div>
                          <p><?php print $assigner_label . $value['user']; ?></p>
                          <p><?php print $value['body']; ?></p>
                       </div>
                    </li>
                <?php }
                }
                else{ ?>
                 <li><div class="no-content"><p><?php print $assignment_result['null_content']; ?></p></div></li>
                <?php }?>
            </ul>
        </div>
    </div>
    <div id="assign-pager">
      <?php print $pager; ?>
    </div>
</div>
