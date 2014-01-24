<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_eb_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_eb';
  $strongarm->value = 0;
  $export['cache_flush_cache_eb'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eb_admin_option';
  $strongarm->value = '2';
  $export['eb_admin_option'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eb_admin_role_type';
  $strongarm->value = '2';
  $export['eb_admin_role_type'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eb_assignment_days';
  $strongarm->value = '7';
  $export['eb_assignment_days'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eb_assingment_days';
  $strongarm->value = '7';
  $export['eb_assingment_days'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eb_self_reg';
  $strongarm->value = '2';
  $export['eb_self_reg'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eb_services_resources';
  $strongarm->value = 0;
  $export['eb_services_resources'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eb_term_policy_nid';
  $strongarm->value = 3008;
  $export['eb_term_policy_nid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eb_user_register';
  $strongarm->value = '1';
  $export['eb_user_register'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_admin_role';
  $strongarm->value = array(
    3 => 3,
    6 => 0,
    9 => 0,
    7 => 0,
    4 => 0,
    5 => 0,
  );
  $export['notifi_admin_role'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_admin_user';
  $strongarm->value = 'arunkumar@unimity.com';
  $export['notifi_admin_user'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_admin_pass_reset_body';
  $strongarm->value = 'Dear Admin,

!firstlastname, !rolename of the !institutename, has already been registered with !institutename, but he forgot his/her login credentials. The instruction and one time link has been sent to the user.

The EOS Team.';
  $export['notifi_mail_to_admin_pass_reset_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_admin_pass_reset_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_admin_pass_reset_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_admin_pass_reset_subject';
  $strongarm->value = 'Request to Reset Password';
  $export['notifi_mail_to_admin_pass_reset_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_admin_reg_body';
  $strongarm->value = 'Dear Admin,
Greetings!

!firstlastname, !rolename of the !institutename, would like to register. Below are the associated details:

First Name: !firstname
Last Name: !lastname
Role: !rolename
Email ID: !ebmail
Notes: !eb_notes

To approve this user, !click_here. To reject user, !click_here. 
Or visit: !edit_uri  to manage registrations.

The EOS Team.';
  $export['notifi_mail_to_admin_reg_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_admin_reg_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_admin_reg_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_admin_reg_subject';
  $strongarm->value = 'Registration request for !institutename';
  $export['notifi_mail_to_admin_reg_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_blocked_admin_body';
  $strongarm->value = 'Dear Admin
!firstlastname, !rolename  of the Institute !institutename, has tried to resubmit his details with !institutename.  He has been notified through email that his registration is queued for Administrator’s review and approval. 

The EOS Team.';
  $export['notifi_mail_to_already_register_blocked_admin_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_blocked_admin_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_already_register_blocked_admin_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_blocked_admin_subject';
  $strongarm->value = 'Attempt to Re-register with !institutename';
  $export['notifi_mail_to_already_register_blocked_admin_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_blocked_user_body';
  $strongarm->value = ' Dear !firstlastname,

You have already submitted your details in !institutename. Your registration details is queued for Administrator’s review and approval. For further information contact your institution’s Administrator.

The EOS Team';
  $export['notifi_mail_to_already_register_blocked_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_blocked_user_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_already_register_blocked_user_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_blocked_user_subject';
  $strongarm->value = 'You are already a Member with !institutename';
  $export['notifi_mail_to_already_register_blocked_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_user_body';
  $strongarm->value = 'Dear !firstlastname

You have already registered with !institutename, If you have forgotten your login credentials, Please use the one-time login link given below to login to !site  and change your password.

!login_url

The EOS Team.';
  $export['notifi_mail_to_already_register_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_user_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_already_register_user_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_already_register_user_subject';
  $strongarm->value = 'You are already a Member with !institutename';
  $export['notifi_mail_to_already_register_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_create_user_body';
  $strongarm->value = 'Thanks for registering with AcrossWorld EducationHub!

Your registration has been queued for moderation. You will hear from our Admin team shortly.

The EOS Team.';
  $export['notifi_mail_to_create_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_create_user_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_create_user_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_create_user_subject';
  $strongarm->value = 'Account details for !firstlastname, at !site (pending admin approval)';
  $export['notifi_mail_to_create_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_accept_body';
  $strongarm->value = 'Dear !firstlastname,

Congratulations!

Thanks for registering with AcrossWorld EducationHub!

You have been added as part of !institutename. Please use the one-time login link given below to login to !site  and change your password.

!login_url

This is a one-time login, so it can only be used One time only. It will expire after 24 hours.

The EOS Team.';
  $export['notifi_mail_to_user_accept_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_accept_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_user_accept_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_accept_subject';
  $strongarm->value = 'Your Registration is Accepted with  !institutename';
  $export['notifi_mail_to_user_accept_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_reject_body';
  $strongarm->value = 'Dear !firstlastname,

Greetings!

Thanks for your interest in registering with AcrossWorld EducationHub!

Your registration to !institutename  is not accepted

The EOS Team.';
  $export['notifi_mail_to_user_reject_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_reject_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_user_reject_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_reject_subject';
  $strongarm->value = 'Your registration to !institutename is not accepted.';
  $export['notifi_mail_to_user_reject_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_reset_pass_body';
  $strongarm->value = 'Hi !firstlastname,

Thank you for changing your password. If you did not initiate this change, please contact our helpdesk at !eb_site_mail

The EOS Team.';
  $export['notifi_mail_to_user_reset_pass_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_reset_pass_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_user_reset_pass_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_reset_pass_subject';
  $strongarm->value = 'Password reset';
  $export['notifi_mail_to_user_reset_pass_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_second_institute_admin_body';
  $strongarm->value = 'Dear Admin,

!firstlastname, !rolename  of the  !institutename, would like to register has requested registration with !secondinstitutename. He can not be associated with 2 institutions & has been notified through email.

The EOS Team.';
  $export['notifi_mail_to_user_second_institute_admin_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_second_institute_admin_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_user_second_institute_admin_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_second_institute_admin_subject';
  $strongarm->value = 'Attempt to Re-register with !secondinstitutename';
  $export['notifi_mail_to_user_second_institute_admin_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_second_institute_body';
  $strongarm->value = 'Dear !firstlastname

You are already a member with !institutename, hence you cannot register again with other institutions. 

Please !uri/user/login here to login to your institution.

The EOS Team.';
  $export['notifi_mail_to_user_second_institute_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_second_institute_mail';
  $strongarm->value = 1;
  $export['notifi_mail_to_user_second_institute_mail'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifi_mail_to_user_second_institute_subject';
  $strongarm->value = 'Your Registration will not be accepted!';
  $export['notifi_mail_to_user_second_institute_subject'] = $strongarm;

  return $export;
}
