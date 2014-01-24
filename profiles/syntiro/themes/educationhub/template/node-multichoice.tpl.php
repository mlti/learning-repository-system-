<?php
?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">

  <!--Bring the edit link as Hidden one-->
  <?php if (isset($ques_edit_link)) { ?>
    <input type="hidden" id="node-edit-link" value="<?php print $ques_edit_link; ?>">
  <?php } ?>

  <!--Create a link to edit Quiz edit page starts here-->
  <?php if (isset($question_content_edit)) { ?>
    <a href="#" title="Click to Edit this Question" class="ques-edit">
  <?php } ?>
    <div class="content clear-block node-content-common">
      <?php print $content ?>
    </div>
  <?php if (isset($question_content_edit)) { ?>
    </a>
  <?php } ?>
  <!--Create a link to edit Quiz edit page ends here-->
</div>
