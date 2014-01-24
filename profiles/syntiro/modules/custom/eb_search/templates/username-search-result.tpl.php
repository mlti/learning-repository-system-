
<?php
// $Id: username-search-result.tpl.php,v 1.1 2010/7/15 10:12:AM dries Exp $
/**
 * @file username-search-result.tpl.php
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   username-search-result.tpl.php
 * - $type: The type of search, e.g., "node" or "user".
 *
 *
 * @see template_preprocess_username_search_result()
 */
global $base_url;

?>
<div class="<?php if ($assigned_user) { print $assigned_user; }?> recommend-group-block clearfix">
      <?php print $checkbox_form; ?>
      <div class="recommend-group-img">
            <?php print $image_url; ?>
      </div>
      <div class="recommend-group-detail">
          <?php if ($firstlastname) : ?>
            <div class="recommend-group-name">
              <?php if($mail): ?>
                <span id="eb-user-name">
                  <?php print $firstlastname; ?>
                </span>
              <?php endif; ?>
              <?php if($mail): ?>
                <span id="eb-user-mail">
                  <?php print $mail;?>
                </span>
              <?php endif; ?>
            </div>
          <?php endif; ?>
        <?php if ($institution) : ?>
          <div class="recommend-group-mem-count"><?php print $institution; ?></div>
        <?php endif; ?>

        <?php if ($certifications) : ?>
          <div class="recommend-group-mem-count"><?php print $certifications; ?></div>
        <?php endif; ?>
      </div>
</div>
