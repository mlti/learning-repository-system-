== Description ==

- We should be able to Add the Review TAB to any CCK, extendable.

  If enabled  

  Curriculum edit need to show the fields
  node reference depend on the content type
  

- With the Review TAB comes 2 fields that get added to the INFO TAB: Reviewers and Open to Review.

- The Review TAB:
 -- If not open to Review should display text: The $Content-type, $Content-name, is not open for Review.
 -- If opened and no Reviews
            --- right to post review message: There are no review, use the Create Review option to post a review.
            --- right only to view review: There are no reviews for this $Content-type, $Content-name.
            --- The content dispalyed should be review title and description, no link to the individual review page. Just list 10 reviews with pagination.
            
- Create Review should open with the curriculum
 -- Review description body field to be half the height and must be word limit of 300 characters.
 -- Thank you for posting a review and redirect to the review TAB.
 
- View any Review node should redirect to the associated noderefernce's Review TAB! (Do we need to have a case here based on the node type)

- Delete ICON next to the review for the author of the Curriculum, and author of the Review.

- The Create Review option to be visible only for Reviewers and Teachers/Admin and only after the content is opened for Review.


Update by Beschi
-----------------
-> Messages:
On adding new review: 
On editing review: 
On deleting review:

On Error: Only 300 characters allowed maximum in body
Field Description: 300 characters max

-> When activating review for a content_type - 2 cck fields OpenToReview(checkbox) and Reviewers(User Reference) will be added to that content type.
-> On deactivating these fields will be deleted
-> On these operations the menu_rebuild() will rebuild the menu constructed in the reviews_menu() according to the review activation settings

-> Viewing node redirection code is on eb_others module
-----------------