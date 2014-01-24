<!-- Community Interest Group Full page view start-->
<?php if ($page == 1): ?>
    <div class="content clear-block">
        <?php if (isset($node_edit_link)) { ?>
            <a class="no-color" href="<?php print $node_edit_link; ?>" title="Click to Edit">
        <?php } ?>
        <p><?php print $og_description ?></p>
        <?php if (isset($node_edit_link)) { ?>
            </a>
        <?php } ?>
		<?php if ($content) { ?>
          <?php print $content; ?>
        <?php } ?>    
    </div>
<?php endif; ?>
