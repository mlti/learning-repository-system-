<?php
// $Id: comment.tpl.php,v 1.10 2008/01/04 19:24:24 goba Exp $
?>
<div class="comment<?php print ($comment->new) ? ' comment-new' : ''; print ' '. $status; print ' '. $zebra; ?>">
  <div class="clear-block">
    <div class="author-image float-left">
      <?php print $picture ?>
    </div>
    <div class="review-right">
      <?php if ($submitted): ?>
        <span class="submitted"><?php print $submitted; ?></span>
      <?php endif; ?>
      <div class="content">
        <?php print $content ?>
      </div>
      <?php if ($links): ?>
        <div class="links"><?php print $links ?></div>
      <?php endif; ?>
    </div>
  </div>
</div>
