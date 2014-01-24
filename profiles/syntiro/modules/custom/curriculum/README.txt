// Last updated on 8-08-2011
== Description ==

This module Provides for all Curriculum Related Features, js, AJAX functionalities on the Curriculum Page

== Response Text ==
.MODULE
- The Asset has been added to the Topic.
- This Asset is already a part of the Topic.
- The Asset order has been updated.
- This Curriculum has no Topics, Click on the Add New Topic link to get started.
- Are you sure you want to delete Topic: test?
- Assignment has been Assigned

INC
- Are you sure you want to remove this asset?

== Configuration ==

TODO: Feature : curriculum CCK and My Curriculum


TODO: Get back on what happens if a coursegroup is deleted
TODO: How does the admin assign a teacher a co-admin

==  Curriculum Management ==

I) My Curriculum

CONFIG: Requires Feature: CCK curriculum

1. - Create Curriculum

Fields
     ------
     Title
     Description
     Tags
     Author (Must be == Instructor of the Coursegroup as created by admin/teacher)
     Co-Author (Auto complete comma separated field)
     Reviewers (Auto complete comma separated field)

    (Check boxes)
     Open for Review
     Published

  Confirmation Message: Your Curriculum has been successfully created. Redirect to info Page

2. - View, Save and Edit Curriculum PAGE
     Menucallback: curriculum/<nid>/edit/content
     Permission: Create curriculum

     Menucallback: curriculum/<nid>/edit/info
     Permission: Create curriculum

     Once published, can be viewed by anyone on Edubridge.

     Title: Curriculum

     Description: The Curriculum page provides and interface for a Teacher/admin to     Create a curriculum.

     ‘Please update Curriculum Info’ If all the fields here are empty.
On Publish: All fields except Co-Author and Reviewers are Mandatory before Publish.

If Open for Review is checked, check if there are Reviewers, else Error: ‘Please add Reviewers.’

     If there is an associated Curriculum:
     Create Curriculum page based on number of Topics with the baskets displayed on the right side of the Curriculum page. The Page can toggle between Edit and View mode (Refer Moodle admin login)

3 – Curriculum View page

  Check if curriculum is published then show assign link in subtopics

   * Assign Icon:

   if($node->field_published[0]['value'] == 1) {
    // Display Assign  Icon Here.
   }

  * Assigned Icon:

  - Get Count of topicid in assigment table.

  - if(count(topicid) != 0 ) {
 	// Display Assigned  Icon Here.
    }

I) – Content TAB:

     A) Add topic
        Default Topic title: New Topic
        Permissions: Create curriculum
        QUERY: INSERT INTO curriculum_topics VALUES (gid, topic_title, order)

        NEW ENTRY in CUSTOM TABLE (ORDER at TOP)

     B) Delete topic
        Prompt in Pop up: Are you sure you want to delete this Topic? Yes | No
        Permissions: Create curriculum
        QUERY: DELETE FROM curriculum_topics WHERE topic_id

     C) Edit topic title
        Permissions: Create curriculum
        QUERY: UPDATE curriculum_topics SET topic_title = WHERE topic_id

     D) Drag and drop ADD Assets from Various Baskets -> Adds asset to the bottom of the assets for a particular topic.
        Permissions: View curriculum + Member of Group

     E) Delete Assets
        Prompt in Pop up: Are you sure you want to delete this Asset? Yes | No
        Permissions: Create curriculum
        Permissions: To Delete his own Assets should be available.
        QUERY: ??

     F) Organise Assets
        Permissions: Create curriculum

     G) Auto Save-****
        Save all changes to the form. Discuss how???
        Any New Asset added to curriculum: Call asset_curriculum_tracking()


     H) Build Topic Page (edit and view)
        Query curriculum_topics and curriculum_topics_assets to display Topics and associated assets??

     I) We should be able to reorganize the TOPICs using up-down arrow that can be located at the right top corner of each Topic zone.
        Need to move entire set of topic to down if click down arrow
        Need to move entire set of topic to up if click down up
        No need to display UP arrow in the first topic and DOWN arrow in the last topic

        QUERY : update curriculum_topics set weight where topic_id

     J) There must be an option to Delete Topics as well along side the same

        QUERY : delete curriculum_topics where topic_id
        QUERY : delete curriculum_topics_assets where topic_id

     K) Turn editing ON & Off - Display the topics and assets without any editing options or the rightside bar.
        A form to display Turn editing ON
        Permission : Create curriculum
        Functionality : In submit set the variable -- curriculum_editing_mode , on/off

     L) Assign Link: Menu callback: popupsearch/results

     M) Assigned User:


     Curriculum-Topic-TABLES

     curriculum_topics: topic_id,  cid (of curriculum nid), topic_title, weight, created, changed
     curriculum_topics_assets: st_id, topic_id, asset, type, title, description, weight, uid, is_admin, created, changed (member specific assets and use some special tag for all users here)


II) Into Tab:

    This is to edit the information of curriculum.

III) Reviews:

This is a new content type. Need to build a Review in relationship.

Review for a curriculum is active only before a curriculum is published and after it is open for Review. It is open only to the Reviewers. The Reviewers can either create a new review or comment on existing reviews.

    Menucallback: curriculum/<nid>/reviews/<nid>
    Permission: reviewer_access() custom function

    Menucallback: curriculum/<nid>/add/reviews
    Permission: reviewer_access() custom function

    Menucallback: curriculum/<nid>/delete/reviews/<nid>
    Permission: Delete own curriculum content

IV) Commenting:

 These will comments to the Curriculum CCK on publish if enabled!
