// $Id$
//My mars block - ajax pager script
Drupal.behaviors.marsBlockPager = function() {
  $("#mars-block-content ul.pager a").click(function(){
    targetArea = $("#mars-block-content");
    //get the contents after ? and make the correct call back for block ajax pager
    targetUrl = $(this).attr("href");
    params = targetUrl.substring(targetUrl.indexOf('?'));
    targetUrl = Drupal.settings.bookmark.basepath + "/mars/block" + params;

    $.ajax({
      url: targetUrl,
      type: "POST",
      data: {
        'ajaxed': true
      },
      beforeSend: function() {
      targetArea.html("Loading...");
    },
    success: function(data) {
     // targetArea.html(data);
      targetArea.html(data);
      Drupal.attachBehaviors("#mars-block-content");
    }
    });
    return false;
  });

  var user_Role = Drupal.settings.bookmark.roles;
  if(user_Role != 'student'){
    $("#mars-block-content .mars-links").addClass("mars-draggable").draggable({
      cursor: 'move',
      helper: 'clone',
      revert: true,
      iframeFix: true,
      tolerance: "pointer",
      cursorAt: { left: 5 }
    });
    $("#mars-result-area .mars-links").addClass("mars-draggable").draggable({
      cursor: 'move',
      helper: 'clone',
      revert: true,
      iframeFix: true,
      tolerance: "pointer",
      cursorAt: { left: 5 }
    });
  }
  $('#mars-pager ul.pager li a').click(mPager);
}
function mPager() {
  thisLink = $(this);
  thisUrl = this.href;
  target = $("#mars-result-area");
  params = thisUrl.substring(thisUrl.indexOf('?'));
  targetUrl = Drupal.settings.bookmark.basepath + "/mars/listing" + params;
  $.ajax({
    url: targetUrl,
    type: "GET",
    beforeSend: function() {
      //target.html("Loading...");
      $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').insertAfter(thisLink);
    },
    success: function(data) {
      // This function is in preview-baser.js
      preview_close_pager();
      target.replaceWith(data);
      Drupal.attachBehaviors("#mars-result-area");
      $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
    }
  });
  return false;
}