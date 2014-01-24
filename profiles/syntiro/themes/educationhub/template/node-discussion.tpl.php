<?php
// $Id: node-discussion.tpl.php,
global $base_url;
?>

<?php if ($page == 1): ?>
 <?php if ($node_edit_link) { ?>
         <input type="hidden" id="node-edit-link" value="<?php print $node_edit_link; ?>">
      <?php } ?>
         <?php if ($tooltip_content) { ?>
         <a class="no-color" href="<?php print $node_edit_link; ?>" title="Click to Edit Description">
      <?php } ?>
 <div class="disscuss_edit_link content clear-block">

    <?php print $content ?>
  </div>

     <?php if (isset($tooltip_content)) { ?>
         </a>
      <?php } ?>
       <div>
        <?php print $created_by; ?>
 </div>
  <div class="clear-block">
    <div class="meta">
    <?php if ($taxonomy): ?>
      <div class="terms"><?php print $terms ?></div>
    <?php endif;?>
    </div>

    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>


<?php if (isset($commentform)): ?>
   <?php print $commentform;  ?>
<?php endif; ?>
<?php endif; ?>
