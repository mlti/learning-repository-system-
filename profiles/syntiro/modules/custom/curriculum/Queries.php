<?php
//Reports Block on Curriculum page

  #check total assignments > 0

//Total Assignments

"SELECT COUNT(*) FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241";

//Completed Assignments

"SELECT COUNT(*) FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8223 and A.status=2";

//Pending Assignments

"SELECT COUNT(*) FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8223 and A.status=1";

/**********************************************************************************************************************************/

//Report Level 1

//Query to get all subtopics for the curriculum

"SELECT asset FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA ON TA.topic_id = OGA.topic_id WHERE OGA.cid = 8241";

//Loop find:

//Total Assignments/Completed Assignments/Pending Assignments over all or topic wise

  //Total Assignments

  "SELECT COUNT(*) FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241 AND A.st_id = 577";

  //Completed Assignments

  "SELECT COUNT(*) FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241 and A.status=2  AND A.st_id = 577";

  //Pending Assignments

  "SELECT COUNT(*) FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8223 and A.status=1 AND A.st_id = 577";

  //Group list

 "SELECT to_gid FROM assignment WHERE from_uid = 6 AND to_gid != 0 AND st_id =573 GROUP BY to_gid";

 "SELECT A.to_gid FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241
AND A.to_gid != 0 AND A.from_uid = 6";

  //Filter subtopic list

  "SELECT A.to_gid FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241
AND  A.from_uid = 6 AND A.to_gid LIKE '%6012%'";




/**********************************************************************************************************************************/
//Report Level 2

  //Query to get all assignment member list  for that subtopic

  "SELECT to_uid, remarks, remarks_time, feedback FROM assignment WHERE from_uid = 6
AND st_id =573";

  //Subtopic list in Dropdown

  "SELECT asset FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241";

  //Filter subtopic list

  "SELECT A.to_uid, A.remarks FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241 AND A.st_id=573 AND A.from_uid = 6 GROUP BY to_gid";


  //Group list

  "SELECT to_gid FROM assignment WHERE from_uid = 6 AND to_gid != 0 AND st_id =573 GROUP BY to_gid";

  //Filter Group list

  "SELECT A.to_uid, A.remarks, A.to_gid FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241 AND A.st_id=573
 AND A.from_uid = 6  AND A.to_gid LIKE '%8227%'";


  //Filter by Status

  "SELECT A.to_uid, A.remarks, A.to_gid FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241 AND A.st_id=573
 AND A.from_uid = 6  AND A.to_gid LIKE '%8227%' AND A.status=2";


  //Find Member autocomplete, result query

   $uid_list =  "SELECT to_uid, remarks, remarks_time, feedback FROM assignment WHERE from_uid = 6 AND st_id =573";

  //Syntax:
     "select name,uid from users where name LIKE 's%' AND uid IN ($uid_list)";

  //Eg:
    "select name,uid from users where name LIKE 's%' AND uid IN (11,1,13,12)";


  //Filter by search

    "<search id> = select uid from users where name = <search keyword>";


    "SELECT A.to_uid, A.remarks, A.to_gid FROM curriculum_topics OGA INNER JOIN curriculum_topics_assets TA
ON TA.topic_id = OGA.topic_id INNER JOIN assignment A ON A.st_id = TA.id WHERE OGA.cid = 8241 AND A.st_id=573
 AND A.from_uid = 6  AND A.to_gid LIKE '%8227%' AND A.status=2  AND A.to_uid =<search id>";
