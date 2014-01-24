// $Id$
//This is for mycurriculum page - making the pager in ajax format
Drupal.behaviors.curPager = function(context) {
  $('#mycurriculum-pager ul.pager li a').click(myCurPager);
  $('#mycurriculum-basket-form ul.pager li a').click(myCurPager);
}

function myCurPager(e) {
  e.preventDefault();
  thisLink = $(this);
  thisUrl = this.href;
  if ($(this).parent().parent().parent().parent().is('#mycurriculum-pager')) {
    target = $("#mycurriculum-result-area");
    target_attach = "#mycurriculum-result-area";
    params = thisUrl.substring(thisUrl.indexOf('?'));
    targetUrl = Drupal.settings.bookmark.basepath + "/playlist/listing" + params;
    flag = 1;
  }
  else {
    target = $("#curriculum-block-content");
    target_attach = "#curriculum-block-content";
    params = thisUrl.substring(thisUrl.indexOf('?'));
    targetUrl = Drupal.settings.bookmark.basepath + "/playlist/block" + params;
    flag = 0;
  }
  $.ajax({
    url: targetUrl,
    type: "GET",
    beforeSend: function() {
      //target.html("Loading...");
      $('<img src="'+ Drupal.settings.curriculum.loadingImg +'"/>').insertAfter(thisLink);
    },
    success: function(data) {
      // for playlist listing page only
      if (flag == 1) {
        // preview section bottom div
        if ($('.common-list-drop-preview').length > 0) {
          $('.common-list-drop-preview').attr("style", {display:"none"});
        }
        // Preview section div
        if ($(".preview-content").length > 0) {
          $(".preview-content").hide();
        }
        //  teaser listing class removal for grey color
        if ($('.listing-teaser').length > 0) {
          $('.listing-teaser').removeClass('listing-teaser');
          
        }
        // For line removal in preview section
        if ($('.common-list-wrapper-clone').length > 0) {
          $('.common-list-wrapper-clone').removeClass('common-list-wrapper-clone');
          
        }
        // close button on top right of the preview section
        if ($('.close-preview').length > 0) {
          $('.close-preview').hide();
        }
        target.replaceWith(data);
      }
      else {
        target.html(data);
      }
     $("fieldset legend").click(function() {
                var fieldset = $(this.parentNode);
                var content = $("> form:not(.action)", fieldset);
                if ($(fieldset).is(".collapsed")) {
                  content.show();
                  $(fieldset).removeClass("collapsed");
                }else{
                  content.hide();
                  $(fieldset).addClass("collapsed");
                } 
                });
      Drupal.attachBehaviors(target_attach);
      $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
    }
  });
  return false;
}
