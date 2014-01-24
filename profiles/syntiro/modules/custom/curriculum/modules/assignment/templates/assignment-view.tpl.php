<?php
// $Id: assigned-listing.tpl.php, 09/08/2011 9:15:PM Saravana Exp $

/**
 * @file assigned-listing.tpl.php
 * Default theme implementation for listing assignments.
 *
 * This template collects each invocation of theme_assigned_listing().
 *
 * Available variables:
 * - $content: Contains Assignment contents like Assignment Title, Assigner name, Assigner Message.
 * - $assigner_label : Contains Assigner Label (Assigned by: )
 * - $content_null : Contains Null content for Assignment listing page
 * - $pager : Contains Pager content.
 * - $completion_form
 * @see template_preprocess_assigned_listing()
 */
?>
<div id="rec-result-area" class="result">
    <div class="view-content ">
        <?php if (!isset($no_record)){ ?>
         <div class="asset-edit-view node-content-common">
           <?php print $content; ?>

            <?php  if (isset($iframe_src)): ?>
               <div class="course-image-description metadata-border node-content-common">
                  <span class="iframe-content text-center"><iframe src="<?php print $iframe_src; ?>" height="570px" width="100%" ></iframe></span>
               </div>
            <?php endif; ?>
            <?php if (isset($video)): ?>
               <span>
                  <?php print $video; ?>
               </span>
            <?php endif; ?>
            <?php if (isset($image)) { ?>
               <span><?php print $image; ?></span>
            <?php } ?>
         <?php // if (!isset($iframe_src)): ?><!--</div>--><?php// endif; ?>
         <?php  if ($original_link): print $original_link; endif; ?>
         </div>
        <?php }else{ ?>
          <div class="no-content"><?php print $content_null; ?></div>
        <?php }?>

    </div>
    <div class="docs-content">
      <?php print $docs_link; ?>
    </div>
    <div class="message-teacher-content">
      <?php print $message_teacher_list; ?>
    </div>
    <?php print $completion_form; ?>

</div>
