<?php
// $Id: views-view-fields--og-members-faces--block.tpl.php, Exp $
/**
 * @file views-view-fields--og-members-faces--block.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>

  <div class="similar-content">
    <div class="views-field-picture">
      <div class="img picture">
        <?php if ($row->users_picture) { ?>
          <?php print theme('imagecache', 'user_profile_image_37', $row->users_picture, $row->users_name . ' Profile Image'); ?>
        <?php } else { ?>
          <?php print theme('imagecache', 'user_profile_image_37', drupal_get_path('theme', 'educationhub') . '/images/icons/avator.jpg', $row->users_name . ' Profile Image'); ?>
        <?php } ?>
      </div>
    </div>
    <div class="views-field-name result-left-image-block ">
      <div class="result-right-inner clearfix ">
          <?php print $fields['name']->content; ?>
      </div>
    </div>
  </div>
