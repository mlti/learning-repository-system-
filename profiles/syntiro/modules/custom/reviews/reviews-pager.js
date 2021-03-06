// $Id$
//This is for mycurriculum page - making the pager in ajax format
Drupal.behaviors.curPager = function(context) {
  $('#reviews-pager ul.pager li a').click(function(){
    thisLink = $(this);
    thisUrl = this.href;
    target = $("#reviews-result-area");
    
    $.ajax({
      url: thisUrl,
      type: "GET",
      beforeSend: function() {
        //target.html("Loading...");
        $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').insertAfter(thisLink);
      },
      success: function(data) {
        target.html($(data).find("#reviews-result-area").html());
        Drupal.attachBehaviors("#reviews-result-area");
        $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
      }
    });
    return false;
  });
}