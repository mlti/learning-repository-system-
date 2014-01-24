// $Id$
//My recommendations block - ajax pager script
Drupal.behaviors.recBlockPager = function() {
  $("#rec-block-content ul.pager a").click(function(){
    targetArea = $("#rec-block-content");
    //get the contents after ? and make the correct call back for block ajax pager
    targetUrl = $(this).attr("href");
    params = targetUrl.substring(targetUrl.indexOf('?'));
    targetUrl = Drupal.settings.bookmark.basepath + "/recommendations/block/" + params;
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
      targetArea.html(data);
      Drupal.attachBehaviors("#rec-block-content");
    }
    });
    return false;
  });
  var user_Role = Drupal.settings.bookmark.roles;
  if(user_Role != 'student'){
    $("#rec-block-content .rec-links").addClass("rec-draggable").draggable({
      cursor: 'move',
      helper: 'clone',
      revert: true,
      iframeFix: true,
      tolerance: "pointer",
      cursorAt: { left: 5 }
    });
     $("#rec-result-area .rec-links").addClass("rec-draggable").draggable({
      cursor: 'move',
      helper: 'clone',
      revert: true,
      iframeFix: true,
      tolerance: "pointer",
      cursorAt: { left: 5 }
    });
  }
}
