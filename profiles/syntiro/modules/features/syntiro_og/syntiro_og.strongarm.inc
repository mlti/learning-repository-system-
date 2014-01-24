<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_og_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_admin_email_body';
  $strongarm->value = '@body

--
This message was sent by an administrator in the \'@group\' group at @site. To visit this group, browse to !url_group. To unsubscribe from this group, visit !url_unsubscribe';
  $export['og_admin_email_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_approve_user_body';
  $strongarm->value = 'You may now post messages in this group located at !group_url';
  $export['og_approve_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_approve_user_subject';
  $strongarm->value = 'Membership request approved for \'@title\'';
  $export['og_approve_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_checkboxes';
  $strongarm->value = 0;
  $export['og_audience_checkboxes'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_required';
  $strongarm->value = '0';
  $export['og_audience_required'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_asset';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_asset'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_bead';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_bead'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_community_interest_group';
  $strongarm->value = 'group';
  $export['og_content_type_usage_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_curriculum';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_discussion';
  $strongarm->value = 'group_post_standard';
  $export['og_content_type_usage_discussion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_institute';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_institute'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_page';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_profile';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_profile'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_quiz';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_quiz'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_deny_user_body';
  $strongarm->value = 'Sorry, your membership request was denied.';
  $export['og_deny_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_deny_user_subject';
  $strongarm->value = 'Membership request denied for \'@title\'';
  $export['og_deny_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_notification_pattern';
  $strongarm->value = '@user_name  <@site_mail>';
  $export['og_email_notification_pattern'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_home_page_view';
  $strongarm->value = 'og_ghp_ron';
  $export['og_home_page_view'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_invite_user_body';
  $strongarm->value = 'Hi. I\'m a member of \'@group\' and I welcome you to join this group as well. Please see the link and message below.

@group
@description
Join: @group_url
@body';
  $export['og_invite_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_invite_user_subject';
  $strongarm->value = 'Invitation to join the group \'@group\' at @site';
  $export['og_invite_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_asset';
  $strongarm->value = '';
  $export['og_max_groups_asset'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_bead';
  $strongarm->value = '';
  $export['og_max_groups_bead'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_community_interest_group';
  $strongarm->value = '';
  $export['og_max_groups_community_interest_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_curriculum';
  $strongarm->value = '';
  $export['og_max_groups_curriculum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_discussion';
  $strongarm->value = '';
  $export['og_max_groups_discussion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_institute';
  $strongarm->value = '';
  $export['og_max_groups_institute'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_page';
  $strongarm->value = '';
  $export['og_max_groups_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_profile';
  $strongarm->value = '';
  $export['og_max_groups_profile'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_quiz';
  $strongarm->value = '';
  $export['og_max_groups_quiz'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_new_admin_body';
  $strongarm->value = '@username, you are now an administrator for the group \'@group\'.

You can administer this group by logging in here:
 !group_url';
  $export['og_new_admin_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_new_admin_subject';
  $strongarm->value = 'You are now an administrator for the group \'@group\'';
  $export['og_new_admin_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_new_node_body';
  $strongarm->value = '@type \'@subject\' by @username

@node_teaser

!read_more: !content_url
Post reply: !reply_url

--
You are subscribed from the group \'@group\' at @site.
To manage your subscription, visit !group_url';
  $export['og_new_node_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_new_node_subject';
  $strongarm->value = '@group: \'@title\' at @site';
  $export['og_new_node_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_private_groups';
  $strongarm->value = '3';
  $export['og_private_groups'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_request_user_body';
  $strongarm->value = 'To instantly approve this request, visit !approve_url.
You may deny this request or manage members at !group_url. 

Personal message from @username:
------------------

@request';
  $export['og_request_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_request_user_subject';
  $strongarm->value = 'Membership request for \'@group\' from \'@username\'';
  $export['og_request_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility';
  $strongarm->value = '2';
  $export['og_visibility'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility_directory';
  $strongarm->value = '1';
  $export['og_visibility_directory'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility_registration';
  $strongarm->value = '0';
  $export['og_visibility_registration'] = $strongarm;

  return $export;
}
