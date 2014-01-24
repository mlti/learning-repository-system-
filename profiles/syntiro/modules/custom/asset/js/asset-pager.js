// $Id$
//This is for myasset page - making the pager in ajax format
Drupal.behaviors.assetsPager = function(context) {
  $('#asset-pager ul.pager li a').click(myAssetsPager);
}

function myAssetsPager() {
  thisLink = $(this);
  thisUrl = this.href;
  target = $("#asset-result-area");
  params = thisUrl.substring(thisUrl.indexOf('?'));
  targetUrl = Drupal.settings.bookmark.basepath + "/asset/listing" + params;
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
      Drupal.attachBehaviors("#asset-result-area");
      $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
    }
  });
  return false;
}
