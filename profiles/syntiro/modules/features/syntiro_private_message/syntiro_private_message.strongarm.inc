<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_private_message_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pm_email_notify_body';
  $strongarm->value = 'Hi !ed_first_name !ed_last_name, 

This is an automatic reminder from the site !site. You have received a new private message from !author.

To read your message, follow this link:
!message

If you don\'t want to receive these emails again, change your preferences here:
!settings';
  $export['pm_email_notify_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pm_email_notify_default';
  $strongarm->value = 1;
  $export['pm_email_notify_default'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pm_email_notify_subject';
  $strongarm->value = 'New private message at !site.';
  $export['pm_email_notify_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_display_fields';
  $strongarm->value = array(
    'participants' => 'participants',
    'thread_started' => 0,
    'count' => 0,
    'tags' => 0,
  );
  $export['privatemsg_display_fields'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_display_loginmessage';
  $strongarm->value = 1;
  $export['privatemsg_display_loginmessage'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_filter_default_list';
  $strongarm->value = '0';
  $export['privatemsg_filter_default_list'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_flush_days';
  $strongarm->value = '30';
  $export['privatemsg_flush_days'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_flush_enabled';
  $strongarm->value = 0;
  $export['privatemsg_flush_enabled'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_flush_max';
  $strongarm->value = '200';
  $export['privatemsg_flush_max'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_per_page';
  $strongarm->value = '10';
  $export['privatemsg_per_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_view_default_amount';
  $strongarm->value = '10';
  $export['privatemsg_view_default_amount'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_view_max_amount';
  $strongarm->value = '10';
  $export['privatemsg_view_max_amount'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'privatemsg_view_use_max_as_default';
  $strongarm->value = 0;
  $export['privatemsg_view_use_max_as_default'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'private_message_view_template';
  $strongarm->value = 'privatemsg-view';
  $export['private_message_view_template'] = $strongarm;

  return $export;
}
