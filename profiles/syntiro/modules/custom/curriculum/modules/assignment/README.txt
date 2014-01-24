Important!!!!
Assignment Table: NID column changed from Integer(int) to Text(varchar).

Assignment Phase II

1) create view page for assignment
   - remarks from student
   - message from teacher as block
2) Pending and Completed as tabs
   - visited link tracking

0: UNASSIGNED, 1: PENDING, 2: COMPLETED

Assignment Phase I

Add New table assignment

1. - Install assignment Table: aid, ta_id, from_uid, to_gid, to_uid, created, changed

     // Table Creation "assignment"

     "CREATE TABLE assignment(
     Auto increment ID: aid int(15) auto_increment,
     Sub Topic ID: st_id int(15),
     From User ID: from_uid int(15),
     To Group ID:to_gid int(15),
     To User ID:to_uid int(15),
     created int(15),
     changed int(15),
     status enum,
     subject
     message,
     remarks,
     Asset ID: nid)";

    - Install assignment_statistics Table: as_id, aid, uid, access_time, created_time, count

     // Table Creation "assignment_statistics"

     "CREATE TABLE assignment_statistics(as_id int(15), uid int(15), aid int(15), access_time int(15), created_time int(15), count int(15))";



2. - Permissions

     create curriculum content
     view assignments (custom permission)
     administer assignment (custom permission)

3. -
 A) Menucallback: assignment/assign/<curriculumid>/<topicid>
    Permission: Create Curriculum
    Form Title: Assign
    Radio Button: User or Group, Select User (autocompelete field), Select Group: Drop down of My Groups, Subject, Body
    //Todo Search pop up link
    Function: assignment_form()

    Validation: All fields Mandatory
     Function: assignment_validate($form, &$form_state)

    On Form Submit update Assign table:
      Function: assignment_form_submit($form, &$form_state)


    Confirmation Message: Your Assignment for <asset-name> has been sent to <user-name> OR <group-name>.
    Redirection: To the curriculum Page

    Condition:
      - Subtopic can be assign to specific student or specific group, once it assigned to Student. Subtopic will listed in student login My Assignment page
      - Assigned user cannot assign again in the same subtopics.

 B) Menucallback: assignment/members/<curriculumid>/<topicid>
    Permission: Create Curriculum
    Title: Assiged to
    Function: assigned_member(topic_id)
    Template: assigned_member.tpl.php
    Query_function:
    Individual[] = Select to_uid from assignment where st_id = %topic_id and to_gid = ''
    Groups[] = Select distinct(to_gid) from assignment where st_id = %topic_id and to_gid !=''

    To get group user

      SELECT users.uid AS uid, users.name AS users_name FROM users users  LEFT JOIN og_uid og_uid ON users.uid = og_uid.uid WHERE (users.status <> 0) AND (og_uid.is_active <> 0) AND (og_uid.nid = %group_id) ORDER BY og_uid_is_admin DESC, users_name ASC


 C) Menucallback: content/myassignment
    Permission: view_assignment_access
    Title: Assignments
    Function: assignment_view(),
              view_assignment_access()
    Template: assignment_view.tpl.php
    Query_function:
         SELECT * FROM {assignment} WHERE to_uid = %d
         Using join query to get assignment

     Condition:
       - Student have My Assignment page, Teacher have My Curriculum page

 D)  Function: assignment_tracking(),
              hook_nodeapi()
    Query_function:
      Check if it is set SELECT * FROM {assignment} WHERE to_uid = %d Using join query to get assignment
           INSERT INTO {assignment_statistics} (nid,uid,topic_id, access_time) VALUES (%d,%d,%d,%d)

 E) Menucallback: admin/assignment/tracking
    Permission: administer assignment
    Function: assignment_tracked_view()
               Using Theme_table() to display view
    Query_function:
          SELECT * FROM {assignment_statistics}

 F) Menucallback: admin/settings/assignment
    Permission: administer assignment
    Function: assignment_settings_form()

    Return: system_settings_form()

    Message:
             Hi
             !url
             Assigned by,
             !name


 G) Menucallback: popupsearch/results
    Permission:access search
    Function: username_search(),
              apachesolr_search_execute()
              username_search_form(),
    Template: username_search.tpl.php

 G) hook_block:

    block Name = 'Assigned Member';
    Show_visibility =  assignment/assign,
    Function: assigned_member(curriculumid, topic_id)

    Template: assigned_member.tpl.php
