<?php
/**
 * @file views-view-fields.tpl.php
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
global $user;
if($row->users_picture == ''){
  $row->users_picture = variable_get('user_picture_default', 0);
}
?>

<div class="clearfix review-detail">
  <div class="author-image float-left">
    <?php print l(theme_imagecache('dis_rev_com_image2', $row->users_picture, 'View user profile', 'View user profile'), 'user/' . $row->users_uid, array('html' => TRUE)); ?>
  </div>
  <div class="review-right">
    <span class="submitted">
      <?php print l($row->users_name, 'user/' . $row->users_uid); ?>
    </span>
    <div class="content">
      <p><?php print $row->node_revisions_body; ?></p>
    </div>
    <?php $account = user_load($user->uid);?>
    <?php if(user_access('edit own reviews content', $account, $reset = FALSE)) :?>
      <?php if($user->uid == $row->node_uid) :?>
        <div class="links">
          <ul class="links-list">
            <li class="review-edit-link">
              <?php print l('edit', 'node/' . $row->nid . '/edit'); ?>
            </li>
          </ul>
        </div>
      <?php endif; ?>
    <?php endif; ?>
  </div>
</div>
