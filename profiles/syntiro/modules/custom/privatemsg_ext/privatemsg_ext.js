Drupal.behaviors.privatemsg_ext = function (context) {
  $("div.privatemsg-operation-button").hide();

  $('#alert-message-form #edit-operation').change(function () {
    $('#edit-submit').click();
  });

  $('.inbox-operation-class').change(function () {
    $('.privatemsg-inbox-submit').click();
  });

  $('#quicktabs_tabpage_1_1 .sent-operation-class').change(function () {
    $('.privatemsg-sent-submit').click();
  });

  $('#popups-close img').click(function (){
    location.reload();
  });
  // For private message in Ajax
  $('#privatemsg-list ul.pager li a').click(PvtMessPager);  
 
  $('#privatemsg-new .button-main-message #edit-cancel').click(clearmsg);
  
};
/**
 * Private message list in Ajax
 */
function PvtMessPager(e) {
  e.preventDefault();
  thisLink = $(this);
  thisUrl = this.href;

  target = $("#content-section");
  $.ajax({
    url: thisUrl,
    type: "GET",
    beforeSend: function() {
      $('<img src="'+ Drupal.settings.curriculum.loadingImg +'"/>').insertAfter(thisLink);
    },
    success: function(data) {
      target.html($(data).find("#content-section").html());
      Drupal.attachBehaviors(target);
      $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
    }
  });
  return false;
}

function clearmsg(e) {
  e.preventDefault();
  $('#edit-body').val('Type your message here');
}