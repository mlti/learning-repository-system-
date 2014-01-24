<?php
// My Pending & Completed Assignments
// based on the status it will act for both pending and completed.
// NEED TO CHANGE field name from nid to link

"SELECT assign.from_uid, assign.aid, assign.message, curriculum.asset, curriculum.title, curriculum.description FROM {assignment} assign INNER JOIN {curriculum_topics_assets} curriculum ON assign.nid = curriculum.asset WHERE assign.to_uid = %d AND assign.status =%d GROUP BY assign.from_uid, assign.to_uid, assign.nid
ORDER BY assign.created DESC";

//Remarks and mark as completed

"UPDATE {assignment_groups} SET status = '%s', remarks = '%s' WHERE st_id = %d  AND uid = %d";

//Assign to Individual

"INSERT INTO {assignment} (st_id, from_uid, to_gid, to_uid, created, changed, subject, message, link)            VALUES (%d, %d, %d, %d, %d, %d,  %d, '%s', '%s', '%s')";

//#TODO: Need to write a check query wheather it is already exist.

"INSERT INTO {assignment_groups} (st_id, uid, changed, status, assign_status, remarks, feedback) VALUES (%d, %d, %d, '%s', '%s', '%s', '%s')";

//Assign to Community

"INSERT INTO {assignment} (st_id, from_uid, to_gid, to_uid, created, changed, subject, message, link)            VALUES (%d, %d, %d, %d, %d, %d,  %d, '%s', '%s', '%s')";

// #TODO: Need to write a check query wheather it is already exist.

"INSERT INTO {assignment_groups} (st_id, uid, changed, status, assign_status, remarks, feedback) VALUES (%d, %d, %d, '%s', '%s', '%s', '%s')";

//Member Listing

//All

"SELECT to_uid FROM {assignment} WHERE from_uid = %d AND to_uid != %d AND st_id = %d GROUP BY to_uid ORDER BY created DESC";

//Assigned

"SELECT to_uid FROM {assignment} a LEFT JOIN {assignment_groups} ag ON a.st_id = ag.st_id WHERE a.from_uid = %d AND a.to_uid != %d AND a.st_id = %d AND a.assign_status = 'Assigned' GROUP BY a.to_uid ORDER BY created DESC";

//UnAssinged

"SELECT to_uid FROM {assignment} a LEFT JOIN {assignment_groups} ag ON a.st_id = ag.st_id WHERE a.from_uid = %d AND a.to_uid != %d AND a.st_id = %d AND a.assign_status = 'UnAssigned' GROUP BY a.to_uid ORDER BY created DESC";

//UnAssign to Individual
"UPDATE assignment_groups SET assign_status = 'UnAssigned' WHERE st_id = %d and uid = %d";

//ReAssign to Individual
"UPDATE assignment_groups SET assign_status = 'Assigned' WHERE st_id = %d and uid = %d";

//Delete Individual
// step:1
"SELECT st_id, uid FROM assingment WHERE to_uid = %d AND aid = %d";
// step:2
"DELETE FROM assignment_groups WHERE st_id = %d AND uid  = %d";
// step:3
"DELETE FROM assignment WHERE to_uid = %d AND aid = %d";

//Community Listing
//No Need to change query. But need to change the display settings in code.
"SELECT to_gid FROM {assignment} WHERE from_uid = %d AND to_gid != %d AND st_id = %d GROUP BY to_gid ORDER BY created DESC";


//Delete Community
// step:1
"SELECT st_id, uid FROM assingment WHERE to_gid = %d AND aid = %d";
// step:2
"DELETE FROM assignment_groups WHERE st_id = %d AND uid  = %d";
// step:3
"DELETE FROM assignment WHERE to_gid = %d AND aid = %d";


//Feedback
"UPDATE {assignment_groups} SET feedback = %s WHERE st_id = %d  AND uid = %d";

//Install Query
function assignment_groups_schema() {
 $schema = array();
 $schema['assignment_groups'] = array(
   'description' => t('assignment_groups table to maintain unique assignments'),
   'fields' => array(
     'st_id' => array(
       'description' => t('Subtopic ID'),
       'type' => 'int',
       'unsigned' => TRUE,
       'not null' => TRUE,
     ),
     'uid' => array(
       'description' => t('User ID'),
       'type' => 'int',
       'unsigned' => TRUE,
       'not null' => TRUE,
     ),
     'changed' => array(
       'description' => t('changed date time - timestamp'),
       'type' => 'timestamp',
       'unsigned' => TRUE,
       'not null' => TRUE,
     ),
     'status' => array(
       'description' => t('status for pending/completed'),
       'type' => 'varchar',
       'length' => 255,
       'not null' => TRUE,
     ),
     'assign_status' => array(
       'description' => t('status for assign/unassign'),
       'type' => 'varchar',
       'length' => 255,
       'not null' => TRUE,
     ),
     'remarks' => array(
       'description' => t('remarks posted by student'),
       'type' => 'varchar',
       'length' => 1000,
       'not null' => TRUE,
     ),
     'feedback' => array(
       'description' => t('feedback posted by teacher'),
       'type' => 'varchar',
       'length' => 1000,
       'not null' => TRUE,
     ),
   ),
 );
}

//changing assignment table structure
function assignment_update_6204() {
 $ret = array();
 // To delete remarks field from assignment table.
 db_drop_field($ret, 'assignment', 'remarks');

 // To delete aid field from assignment_statistics table.
 db_drop_field($ret, 'assignment_statistics', 'aid');

// adding new field st_id in assignment_statistics table
 db_add_field($ret, 'assignment_statistics', 'st_id',
   array(
       'description' => t('Subtopic ID'),
       'type' => 'int',
       'unsigned' => TRUE,
       'not null' => TRUE,
       )
  );

 // changing the field name form nid to link
 db_change_field($ret, 'assignment', 'nid', 'link', array(
    'description' => t('Node ID'),
    'type' => 'int',
    'unsigned' => TRUE,
    'not null' => TRUE,
  ));

 return $ret;
}

//Move existing content to...

"INSERT INTO assignment_assign (st_id,uid,changed,status,assign_status,remarks, feedback)
SELECT st_id,from_uid,now(),'Pending','Assigned','', ''
FROM assignment";

?>
