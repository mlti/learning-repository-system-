= Description ==

This module creates Bridge Page, Footer Block, Content Navigation Block for My Assets, My MARS, etc.

 get_recommend_text -- What does this function do?

== TODO ==

Bring MARS links form MARS module... Private Messages Dynamic


== PHASE II Student Login 22/08/2011 ==

== Student Dashboard ==

I) Left pane

hook_block() - Left side

       A) Bridge Assignment block
       B) Bridge Community block
       C) Bridge Discussion block
       D) Bridge Profile block

     A) Create function bridge_assignment_block()
        USE: assignment_page.inc: move query as a support-function _my_assignments($limit=10;){}
        PERMISSIONS: user_access(view assignment)
        NULL MESSAGES: No Assignments

     B) Create function bridge_community_block()
        USE: eb_group.inc: move query and count to support function _my_communities($limit=10;){}
        PERMISSIONS: user_access(create community_interest_group content) && user_access(view assignment)
        NULL MESSAGE: No Communities yet! Create Yours Now.

     C) Create function bridge_discussion_block()
        USE: _my_discussions($limit=10){};
        PERMISSIONS: user_access(create discussion content) && user_access(view assignment)
        NULL MESSAGE: No discussions yet! Start Discussion.


        BLOCK FUNCTION as below:

        if user_access(permission){
          if(notnull){
            ARRAY STRUCTURE
            $rows[block_title]
            $rows[assignment_title][i][title] (provide title with link)
            $rows[more] (if empty, link to the more page)
          } else {
              NULL MESSAGES
            }
        else {No result return NULL}

     D) Create function bridge_profile_block()
     // @todo Discuss with Jaffar~!
        USE: user_load ($user->uid)

Theme Functions

        Theme bridge_leftside_blocks.tpl.php

        $vars[title]
        $vars[link][i]
        $var[more]
        Theme bridge_leftside_user.tpl.php


 II) $content, Activity Meter, Permission


Header Drop Down actions are written in eb_others_popups.js
