EB_COMMENTS
-----------

!!!!!! Comments for Asset !!!!!!
Comment settings can be changed in the Asset content type edit page
0 - Disable
1 - Read Only
2 - Read/Write

if Disabled
- Comments Link will not visible in the left tab in Asset pages
- Add New Comment will not be shown in the right top
- Can not add a new comment
- Message on comments page: Asset is not open for comments

If Read Only
- Comments link will be in the left tab
- Can see existing comments
- Add New Comment will not be shown in the right top
- Can not add a new comment
- If no comments - Message: There are no comments, use the Add New Comment option to add comment

If Read/Write
- Comments link in left tab and Add new comment links are available
- Anyone can add a comment with permission node_access
- If no comments - Message: There are no comments, use the Add New Comment option to add comment


!!!!!!!!! Comments for Curriculum !!!!!!!!!!
Comment settings can be changed (For all curriculum) in the Curriculum content type edit page
0 - Disable
1 - Read Only
2 - Read/Write

If Disbled
- No add link and no left side tab link
- Can not add comment
- Page Message: Curriculum is not open for Comments

If Read Only
- Comments tab link will be available
- Comment add link will not be available
- No comments message: Comments are not yet posted

If Read/Write
- Comments tab link will be available
- If comment settings(field_turncommenting) for the particular curriculum is OFF - behave like the Read Only situation above
- If field_turncommenting is ON - Add link will be available, Message on no comments: Comments are not yet posted, use Add New Comment option to add


!!!!!!!!!!!!!!! Menu callbacks !!!!!!!!!!!!!!!!!
When a particular content_type is edited and updated new menu callbacks will be generated according to the comments settings
If a content_type comment settings is switched to Read/Write mode, following menu callbacks will be added
- content_type/%node/comments
- content_type/%node/comments/reply?comment-form
- content_type/%node/comments/edit/%
Edit option will be avilable only to the owner of the comment

If content_type comment settings changed to: Read only
- content_type/%node/comments

If Disabled
- content_type/%node/comments
- content_type/%node/comments/reply?comment-form
- content_type/%node/comments/edit/%
All these menucallbacks will be removed.


?: How this affecting the normal comment behavior of other content types
?: Need to write in a separate module? (Currently wirting in reviews module menu)