== Description ==

This module allows you to Bookmark Assets

== Configuration ==

- There are several settings that can be configured in the following places:

  Administer > Site building > Modules (admin/build/modules)
    Enable or disable the module. (default: disabled)

  Administer > User management > Permissions (admin/user/permissions)
    Under recommend module:
    view bookmark stats: Enable access to the bookmark stats page

  Administer > Content management > Content types (admin/content/types)
    For each content type it is possible to enable or disable the PF link
    via the "bookmark" checkbox. (default: disabled)

 == TODO ==

1. INSTALL bookmark table: assetid, uid, rid, timestamp

 // Table Creation "bookmark"

2. - Node Link Definition: By Default should read + Bookmark. If already in my bookmarks: - Remove

ON + Bookmark:
Menucallback: AJAX bookmark/add/nid
Access control?

USER OBJ
Query -> Insert
Response: AJAX: The Asset has been Bookmarked.

ON - Remove
Menucallback: AJAX bookmark/remove/nid
Access control ?

USER OBJ
Query -> Delete
ResponsThe Asset has been Removed from you Bookmark.

3. - Block, Page
To dispaly my Bookmarks

Menucallback: bookmarks
     Title: Bookmarks
     Null Content: You have no bookmarks.
     Query to list bookmarks ordered by last recommended.
     The User to have an option to - Remove on page.


     Create Menu Call Back...
     Create Hook Block...

     Query -> Select

4. -Bookmark Statistics : Asset ID | Bookmarked  by Teacher| Bookmarked by Student | Total Bookmarks
     Menucallback: admin/reports/bookmarks
     Title: Top Bookmarks
     Null Content: There are no bookmarks.

      Create Menu Call Back...

     Query-> Select


/** TODO and recommendatio by Kamalakannan **/
Please use Drupal Write Record for insert and update in database.
Reduce the number of lnes in the function for example

  /* In bookmark.module line no 148
  * $limit = 10;
  * $output = pager_query($sql, $limit);
  */
  In the above snippet $limit variable is not used else where so $limit is not required instead use the 10 directly in the function

  In line no 159 $variables is not declared or initiated anywhere so this is a bug fix it.

//Beschi
Change the statistics page