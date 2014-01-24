== Description ==

This module Provides for all Curriculum Related Features, js, AJAX functionalities on the Curriculum Page
Sub module to manage course group. 

== Configuration ==

Requires Feature : curriculum


Introduce the following tabs using hook_block in left side

 -- Overview
 -- Info
 -- Reviews
 -- Discussions
 -- Comments 
 -- Discussions
 -- Members
     
==  Curriculum Management ==

I) My Curriculum

CONFIG: Requires Feature: CCK curriculum

1. - Create Curriculum

Fields
     ------
     Description
     Tags
     Author (Must be == Instructor of the Coursegroup as created by admin/teacher)
     Co-Author (Auto complete comma separated field)
     Reviewers (Auto complete comma separated field)
     
    (Check boxes)
     Open for Review
     Published 
     Turn on Commenting
     
  Confirmation Message: Your Curriculum has been successfully created. Redirect to info Page
     
2. - View, Save and Edit Curriculum PAGE
     Menucallback: og/<nid>/curriculum/edit
     Permission: Create curriculum (specific to OG??)
     
     Menucallback: og/<nid>/curriculum/view
     Permission: View curriculum (specific to OG??)
     
     Once published, can be viewed by anyone on Edubridge.          
     
     Title: Curriculum
    
     Description: The Curriculum page provides and interface for a Teacher/admin to     Create a curriculum.     

     ‘Please update Curriculum Info’ If all the fields here are empty. 
On Publish: All fields except Co-Author and Reviewers are Mandatory before Publish.

If Open for Review is checked, check if there are Reviewers, else Error: ‘Please add Reviewers.’ 

Turn on Commenting only after Curriculum is published.
     
     
     If there is an associated Curriculum:
     Create Curriculum page based on number of Topics with the baskets displayed on the right side of the Curriculum page. The Page can toggle between Edit and View mode (Refer Moodle admin login)

I) – Info TAB
     When there are no topics, take user to the Curriculum INFO page. The Info page has to capture the below information:

  
II) – Overview TAB:   
     
     A) Add topic
        Default Topic title: New Topic
        Permissions: Create curriculum
        QUERY: INSERT INTO og_curriculum_topics VALUES (gid, topic_title, order)        

        NEW ENTRY in CUSTOM TABLE (ORDER at TOP)
        
     B) Delete topic
        Prompt in Pop up: Are you sure you want to delete this Topic? Yes | No
        Permissions: Create curriculum
        QUERY: DELETE FROM og_curriculum_topics WHERE topic_id
        
     C) Edit topic title
        Permissions: Create curriculum
        QUERY: UPDATE og_curriculum_topics SET topic_title = WHERE topic_id
        
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
        Query og_curriculum_topics and og_curriculum_topics_assets to display Topics and associated assets??
        
     I) We should be able to reorganize the TOPICs using up-down arrow that can be located at the right top corner of each Topic zone. 
        Need to move entire set of topic to down if click down arrow
        Need to move entire set of topic to up if click down up
        No need to display UP arrow in the first topic and DOWN arrow in the last topic
        
        QUERY : update og_curriculum_topics set weight where topic_id
        
     J) There must be an option to Delete Topics as well along side the same        
         
        QUERY : delete og_curriculum_topics where topic_id
        QUERY : delete og_curriculum_topics_assets where topic_id
        
     K) Turn editing ON & Off - Display the topics and assets without any editing options or the rightside bar.
        A form to display Turn editing ON
        Permission : Create curriculum
        Functionality : In submit set the variable -- curriculum_editing_mode , on/off
        
        
     
     Curriculum-Topic-TABLES
     
     og_curriculum_topics: topic_id,  gid (of course_group), topic_title, weight, created, changed
     og_curriculum_topics_assets: id, topics_id, asset, type, title, description, weight, uid, is_admin, created, changed (member specific assets and use some special tag for all users here)
     
III) Reviews:

This is a new content type. Need to build a Review coursegroup relationship.

Review for a curriculum is active only before a curriculum is published and after it is open for Review. It is open only to the Reviewers. The Reviewers can either create a new review or comment on existing reviews.

    Menucallback: og/<nid>/reviews
    Permission: view reviews content

IV) Commenting TAB:

These will comments to the Curriculum CCK on publish if enabled!
     