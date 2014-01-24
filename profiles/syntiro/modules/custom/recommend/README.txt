== Description ==

This module allows you to recommend a node to

    * any other user in the site
    * set of users associated with a group
     (prerequisite  OG module)


A link is inserted in the each node (configurable in the content type
settings), that provides this functionality.

== Configuration ==

- There are several settings that can be configured in the following places:

  Administer > Site building > Modules (admin/build/modules)
    Enable or disable the module. (default: disabled)

  Administer > User management > Permissions (admin/user/permissions)
    Under recommend module
    administer recommend: Enable access to the recommend mail settings page

  Administer > Content management > Content types (admin/content/types)
    For each content type it is possible to enable or disable the PF link
    via the "Recommend" checkbox. (default: disabled)
   
  Administer > Site configuration > Recommend (admin/settings/recommend)
    Provides a form to set the Default Subject and Body for the Recommend mail content.

== TODO ==

1. - Install Recommend Table Recommend: assetID, from_uid, from_rid, to_gid, to_uid, Status

     // Table Creation "Recommend"

     "CREATE TABLE recommend(asset_id int(15), from_uid int(15), from_rid int(15), to_gid int(15), to_uid int(15), status int(2))";
     


2. - Node Link Definition: By Default should read + Recommend. A user can Recommend an Asset multiple times. 


3. - 
 A)  On Form Submit update Recommend table:
     Menucallback:recommend/<nid>
     Form Title: Recommend
     Radio Button: User or Group, Select User (autocompelete field), Select Group: Drop down of My Groups, Subject, Body
     Validation: All fields Mandatory
        
     Confirmation Message: Your Recommendation for <asset-name> has been sent to <user-name> OR <group-name>.
     Redirection: To the page from which the user recommended the asset
     
     USER OBJECT
     "SELECT rid FROM user_roles  WHERE uid = %d", $user->uid;

     $status = 1;

     "INSERT INTO (recommend) (asset_id, from_uid, from_rid, to_uid, status) VALUES (%d, %d, %d, %d, %d)", $form_state['values']['rec_nid'], $user->uid, $from_rid, $to_uid, $status;

 B) Menucallback: recommend/decline/<nid>
    
    Confirmation popup: Are you sure you want to Decline this Recommendation? Yes| No
    Yes: "DELETE"
    No:  Page will refresh.


4. - Recommend Block, Page

     Menucallback: recommendations, decline/<nid>
     Title: Recommendations
     Null Content: You have no recommendations.
     Query to list Recommendations ordered by last recommended.
     The User to have an option to + Decline Recommendations on page.


     Create Menu Call Back...
     Create Hook Block...        AJAX for pagination..

     Query -> Select
     
     "SELECT n.title n.nid FROM {node} n INNER JOIN {recommend} r ON r.asset_id = n.nid WHERE to_uid = %d", $user->uid;


5. -Recommend Statistics : Asset ID | Teacher recommendations | Student Recommendation | Total Recommendations
     Menucallback: admin/reports/recommendations
     Title: Top Recommendations
     Null Content: There are no recommendations.

     Create Menu Call Back...

     Query-> Select

     "SELECT asset_id, count(from_uid) from {recommend} WHERE from_rid='4'";
     "SELECT asset_id, count(from_uid) from {recommend} WHERE from_rid='5'";
    
