== Description ==

This module allows you to track Assets used in Curriculum or in Creating Assets.

== TODO ==

I) - Install asset_tracking TABLE: assetID, uid, rid, type (curriculum or asset), timestamp, changed

Final:
asset_tracking  CREATE TABLE `asset_tracking` (
                  `id` int(11) NOT NULL auto_increment,
                  `asset_id` int(11) default NULL,
                  `uid` int(11) default NULL,
                  `rid` int(11) default NULL,
                  `parent_type` varchar(20) default NULL COMMENT 'Where this asset is being used (curriculum/asset)',
                  `parent_id` int(11) default NULL,
                  `created` int(11) default NULL,
                  PRIMARY KEY  (`id`)
                ) ENGINE=MyISAM DEFAULT CHARSET=latin1
    QUERY:
    CREATE TABLE

II) - Asset Tracking Statistics :
     Form: Select: In Curriculum, In Asset, Both
     Asset ID | Used Type | Used by Teacher | Used by Students | Total
     Menucallback: admin/reports/asset-tracking
     Title: Asset Trackign Reports
     Null Content: No Assets have been used.

     Create Menu Call Back...

     Query-> Select

III) My Asset
     --------

    -- Create a view to display all his asset
    -- Display Asset title, Asset teaser

    Introduce the following tabs using hook_block in left side

    * Overview
    * Info
    * Comments

     Use the same tpl which we created for curriculum

   1) Overview (Use Exisisting)

      Display Content Depend on the format HTML, PDF, IMAGE & VIDEO

      Any theming related functions to be handled here.

   2) Info (Use Exisisting)

       Title :
       Description :
       Asset Category :
       Format :
       Language :
       Creative Commons option :
       Tags :

       Display Five star rating and recommend link

       Option to turn editing on/ off for edit functionality

       Any theming related functions to be handled here.

   3) Comments
     Display Asset related comments
     Link to create the comments