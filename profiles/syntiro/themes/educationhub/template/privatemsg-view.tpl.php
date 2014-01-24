<?php
// $Id: privatemsg-view.tpl.php,v 1.1.2.8 2010/03/10 12:35:34 berdir Exp $
// Each file loads it's own styles because we cant predict which file will be
// loaded.
?>
<?php //print $anchors; ?>

  <div class="privatemsg-box-fb <?php print $zebra; ?>" id="privatemsg-mid-<?php print $mid; ?>">
  <div class="message-subject"><?php print $message[subject]; ?></div>
    <div class="user-profile-main profile clearfix">
      <?php print $author_picture; ?>
      <div id="content-profile-display-profile" class="content-profile-display">
        <div class="node" >
          <div class="content clear-block">
            <div class="clearfix field field-type-text field-field-profile-previous-school">
              <div class="field-items">
                <div class="field-item odd">
                  <div class="message-body">
                    <?php if (isset($new)) : ?>
                      <!--<span class="new"><?php print $new ?></span>-->
                    <?php endif ?>
                    <div class="timestamp"><?php print $message_timestamp; ?></div>
                    <?php print $message_body; ?>
                  </div>
                  <?php if ( isset($message_actions)) : ?>
                    <?php //print $message_actions ?>
                  <?php endif ?>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="clear-both bottom-border"></div>
  </div>
