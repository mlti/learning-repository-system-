<?php
// $Id: user-picture.tpl.php,v 1.2 2007/08/07 08:39:36 goba Exp $

/**
 * @file user-picture.tpl.php
 * Default theme implementation to present an picture configured for the
 * user's account.
 *
 * Available variables:
 * - $picture: Image set by the user or the site's default. Will be linked
 *   depending on the viewer's permission to view the users profile page.
 * - $account: Array of account information. Potentially unsafe. Be sure to
 *   check_plain() before use.
 * - $social_link: Display social network link for user added
 * - $contact: Display contact icon on profile view page of other user
 * - $quiz_result: It shows myresult page link. It will display myresults in popups
 *
 * @see template_preprocess_user_picture()
 */

?>
<div class="picture">
<div class="img">
 <?php if ($image) {  print $image; } ?>
</div>

  <?php if ($contact) { ?>
  <div class="contact-icon">
      <?php print $contact; ?>
  </div>
 <?php } ?>
  <?php if ($quiz_result) { ?>
   <div class="quiz-result text-center">
      <?php  print $quiz_result; ?>
  </div>
  <?php } ?>
  <?php if ($social_link) { ?>
    <div class="contact-links-small">
      <ul>
        <?php print $social_link; ?>
      </ul>
    </div>
  <?php } ?>
</div>
