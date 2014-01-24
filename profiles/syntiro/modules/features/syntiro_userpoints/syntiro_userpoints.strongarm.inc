<?php

/**
 * Implementation of hook_strongarm().
 */
function syntiro_userpoints_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_assignment_completed';
  $strongarm->value = '';
  $export['limits_assignment_completed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_assignment_completed_week';
  $strongarm->value = '';
  $export['limits_assignment_completed_week'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_assignment_not_completed';
  $strongarm->value = '';
  $export['limits_assignment_not_completed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_comment_in_other_discussion';
  $strongarm->value = '5';
  $export['limits_comment_in_other_discussion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_comment_in_own_discussion';
  $strongarm->value = '5';
  $export['limits_comment_in_own_discussion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_community_creation';
  $strongarm->value = '5';
  $export['limits_community_creation'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_discussion_in_other_community';
  $strongarm->value = '2';
  $export['limits_discussion_in_other_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_discussion_in_own_community';
  $strongarm->value = '5';
  $export['limits_discussion_in_own_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_joins_his_community';
  $strongarm->value = '';
  $export['limits_joins_his_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_joins_others_community';
  $strongarm->value = '';
  $export['limits_joins_others_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_leaves_his_community';
  $strongarm->value = '';
  $export['limits_leaves_his_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_login_once';
  $strongarm->value = '';
  $export['limits_login_once'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_participate_begins';
  $strongarm->value = '';
  $export['limits_participate_begins'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_recommend_to_friends';
  $strongarm->value = '10';
  $export['limits_recommend_to_friends'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'limits_unassign_an_assignment';
  $strongarm->value = '';
  $export['limits_unassign_an_assignment'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'max_score_points';
  $strongarm->value = '5000';
  $export['max_score_points'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_assignment_completed';
  $strongarm->value = '10';
  $export['points_assignment_completed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_assignment_completed_week';
  $strongarm->value = '5';
  $export['points_assignment_completed_week'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_assignment_not_completed';
  $strongarm->value = '-10';
  $export['points_assignment_not_completed'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_comment_in_other_discussion';
  $strongarm->value = '10';
  $export['points_comment_in_other_discussion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_comment_in_own_discussion';
  $strongarm->value = '5';
  $export['points_comment_in_own_discussion'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_community_creation';
  $strongarm->value = '5';
  $export['points_community_creation'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_discussion_in_other_community';
  $strongarm->value = '5';
  $export['points_discussion_in_other_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_discussion_in_own_community';
  $strongarm->value = '1';
  $export['points_discussion_in_own_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_joins_his_community';
  $strongarm->value = '1';
  $export['points_joins_his_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_joins_others_community';
  $strongarm->value = '1';
  $export['points_joins_others_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_leaves_his_community';
  $strongarm->value = '-1';
  $export['points_leaves_his_community'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_login_once';
  $strongarm->value = '1';
  $export['points_login_once'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_participate_begins';
  $strongarm->value = '100';
  $export['points_participate_begins'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_recommend_to_friends';
  $strongarm->value = '1';
  $export['points_recommend_to_friends'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'points_unassign_an_assignment';
  $strongarm->value = '10';
  $export['points_unassign_an_assignment'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 're_max_score_points';
  $strongarm->value = '0';
  $export['re_max_score_points'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 're_max_score_points_com';
  $strongarm->value = '0';
  $export['re_max_score_points_com'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_category_default_tid';
  $strongarm->value = '0';
  $export['userpoints_category_default_tid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_category_default_vid';
  $strongarm->value = '1';
  $export['userpoints_category_default_vid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_category_profile_display_tid';
  $strongarm->value = '0';
  $export['userpoints_category_profile_display_tid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_display_message';
  $strongarm->value = '1';
  $export['userpoints_display_message'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_expireafter_date';
  $strongarm->value = '';
  $export['userpoints_expireafter_date'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_expireon_date';
  $strongarm->value = array(
    'month' => '1',
    'day' => '1',
    'year' => '1980',
  );
  $export['userpoints_expireon_date'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_expiry_description';
  $strongarm->value = '';
  $export['userpoints_expiry_description'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_login';
  $strongarm->value = '1';
  $export['userpoints_login'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_login_interval';
  $strongarm->value = '86400';
  $export['userpoints_login_interval'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_login_tid';
  $strongarm->value = '863';
  $export['userpoints_login_tid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_points_moderation';
  $strongarm->value = '0';
  $export['userpoints_points_moderation'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_report_displayzero';
  $strongarm->value = '1';
  $export['userpoints_report_displayzero'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_report_limit';
  $strongarm->value = '10';
  $export['userpoints_report_limit'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_report_usercount';
  $strongarm->value = '30';
  $export['userpoints_report_usercount'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_transaction_timestamp';
  $strongarm->value = 1;
  $export['userpoints_transaction_timestamp'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_trans_lcpoint';
  $strongarm->value = 'point';
  $export['userpoints_trans_lcpoint'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_trans_lcpoints';
  $strongarm->value = 'points';
  $export['userpoints_trans_lcpoints'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_trans_ucpoint';
  $strongarm->value = 'Point';
  $export['userpoints_trans_ucpoint'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_trans_ucpoints';
  $strongarm->value = 'Points';
  $export['userpoints_trans_ucpoints'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'userpoints_trans_uncat';
  $strongarm->value = 'Uncategorized';
  $export['userpoints_trans_uncat'] = $strongarm;

  return $export;
}
