// $Id$
//My bookmarks block - ajax pager script
Drupal.behaviors.bmBlockPager = function() {
  $("#bm-block-content ul.pager a").click(bmBlockPager);
  var user_Role = Drupal.settings.bookmark.roles;
  if(user_Role != 'student'){
    $("#bm-block-content .bm-links").addClass("bm-draggable").draggable({
      cursor: 'move',
      helper: 'clone',
      revert: true,
      iframeFix: true,
      tolerance: "pointer",
      cursorAt: { left: 5 }
    });
    $("#bm-result-area .bm-links").addClass("bm-draggable").draggable({
      cursor: 'move',
      helper: 'clone',
      revert: true,
      iframeFix: true,
      tolerance: "pointer",
      cursorAt: { left: 5 }
    });
  }

}

function bmBlockPager() {
  thisLink = $(this);
  targetArea = $("#bm-block-content");
  targetUrl = $(this).attr('href');
  //get the contents after ? and make the correct call back for block ajax pager
  params = targetUrl.substring(targetUrl.indexOf('?'));
  targetUrl = Drupal.settings.bookmark.basepath + "/bookmarks/block/" + params;

  $.ajax({
    url: targetUrl,
    type: "POST",
    data: {
      'ajaxed': true
    },
    beforeSend: function() {
    $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').insertAfter(thisLink);
  },
  success: function(data) {
    targetArea.html(data);
    Drupal.attachBehaviors("#bm-block-content");
  }
  });
  return false;
}
