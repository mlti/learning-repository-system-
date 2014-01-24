Drupal.behaviors.bridge = function (context) {
  // Left Side Bar Toggle for Student Home page
  $('.left-discussion-content').hide();
  $('.left-private-message-content').hide();

  $('.discussion-heading .filter-plus-symbol').click(leftblockToggle);
  $('.private-message .filter-plus-symbol').click(leftblockToggle);

  var path = window.location.pathname;
  var explode = path.split('/');

  // To load the corresponding content.
  if(explode[2] == 'mybookmarks' || explode[2] == 'myrecommendations' || explode[2] == 'mymars' ) {
    plusminus_image = $('.discussion-heading .leftsidebar-title .filter-plus-symbol img').attr('src');
    $('.left-discussion-content').show();
    $('.discussion-heading .leftsidebar-title').addClass('title-active');
  } else if(explode[1] == 'messages') {
    plusminus_image = $('.private-message .leftsidebar-title .filter-plus-symbol img').attr('src');
    $('.left-private-message-content').show();
    $('.private-message .leftsidebar-title').addClass('title-active');
  }

};


function leftblockToggle() {
   // for arrow image change
   plusminus_image = $(this).children().attr('src');

   // To make visible either one's.
   if($(this).closest(".left-activity-block").attr("class") == 'left-activity-block discussion-heading') {
      $('.left-private-message-content').hide();
      $('.private-message .leftsidebar-title').removeClass('title-active');
      $('.private-message .leftsidebar-title .filter-plus-symbol img').attr('src', plusminus_image.replace("expand", "collapse"));

   } else if($(this).closest(".left-activity-block").attr("class") == 'left-activity-block private-message ') {
      $('.left-discussion-content').hide();
      $('.discussion-heading .leftsidebar-title').removeClass('title-active');
      $('.discussion-heading .leftsidebar-title .filter-plus-symbol img').attr('src', plusminus_image.replace("expand", "collapse"));
   }

   if ($(this).parent().next().css("display") != "block") {
     $(this).parent().next().show();
     //adding class to the titles
     $(this).parent().addClass('title-active');
     //relpacing the collapse icon to expand icon
     $(this).children().attr('src', plusminus_image.replace("collapse", "expand"));
   } else {
     $(this).parent().next().hide();
     //adding class to the titles
     $(this).parent().removeClass('title-active');
     //relpacing the expand icon to collapse icon
     $(this).children().attr('src', plusminus_image.replace("expand", "collapse"));
   }
}
