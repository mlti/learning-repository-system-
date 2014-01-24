<?php
// $Id: comment-discussion.tpl.php,v 1.10 2012/02/17 19:24:24 goba Exp $
?>

<div class="listing-common-box">
  <div class="discussion-date-time clearfix"> <span class="float-left"><?php print $date;  ?></span> <span class="float-right"> <?php print $edit;  ?></span></div>
  <div class="clearfix common-listing-content">
    <div class="float-left image-common discussion-listing">
      <div class="clearfix">
        <div class="float-left"> <?php print $picture ?> </div>

      </div>
      <div class="posted-by">
          <p><div class="mem-name"><?php print $submitted; ?></div></p>
          <p><?php print $created_time; ?></p>
          <p><?php print $total; ?></p>
        </div>
    </div>
    <div class="listing-common-desc">
      <p> <?php print $content ?> </p>
    </div>
  </div>
  <div class="listing-common-footer"></div>
</div>
