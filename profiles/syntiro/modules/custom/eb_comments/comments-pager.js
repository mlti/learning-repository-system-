// $Id$
//This is for mycurriculum page - making the pager in ajax format
Drupal.behaviors.curPager = function(context) {
  $('#comments-pager ul.pager li a').click(function(){
    thisLink = $(this);
    thisUrl = this.href;
    target = $("#comments-result-area");
    
    $.ajax({
      url: thisUrl,
      type: "GET",
      beforeSend: function() {
        //target.html("Loading...");
        $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').insertAfter(thisLink);
      },
      success: function(data) {
        target.html($(data).find("#comments-result-area").html());
        Drupal.attachBehaviors("#comments-result-area");
        $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
      }
    });
    return false;
  });
}