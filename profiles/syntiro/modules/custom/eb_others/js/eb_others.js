Drupal.behaviors.eb_others = function (context) {

  $('#privatemsg-new .form-submit').click(function(){
    //Set comment body field as empty
    if($('#privatemsg-new #edit-body').val() == 'Type your message here'){
      $('#privatemsg-new #edit-body').val('');
    }
  });
  // In reply message page text
  url = window.location.href;
  explode  = url.split("/");
  if(explode[3] == 'messages' && (explode[4] == 'new' || explode[4] == 'view')) {
    $('#edit-body').val('Type your message here');
    $('#edit-body').click(reply_message_click);
    $('#edit-body').blur(reply_message_blur);
  }

  $("span.exp-coll").click(expand_collapse);

  //to remove title in profile view page.

  $('#content-profile-title-profile').hide();
  $('.submitted').hide();
 
  // Asset and Playlist Edit Content page
  $(".tip-close").click(closeTip);
  $(".tip-open").click(closeTip);
  // For bridge basket ajax process
  $("ul.expand-coll-list .title-exp-coll a").click(listingPage);
  // set the cookie for recommendation, bookmark delete popups
  if (($('.popups-box #decline-confirmation-form').length > 0 || $('.popups-box #remove-confirmation-form').length > 0)  && $('ul.expand-coll-list li h4.active').length > 0) {
    setCookie('bridge_redirect',$('ul.expand-coll-list li h4.active').children().next().attr('href'));
    setCookie('bridge_basket_form', $('ul.expand-coll-list li h4.active').next().attr("id"));
  }
  // flag mouse over should open the campus details
  $('.flag-campus').hover(campusDetailsOpen);
  $('.flag-campus').mouseout(campusDetailsClose);

}
/**
 * Implementing the campus details on mouse over
 */
function campusDetailsOpen(e) {
  e.preventDefault();
  $(this).next().show();
}
/**
 * close the campus details on mouse out
 *
 */
function campusDetailsClose(e) {
  e.preventDefault();
   $(this).next().hide();
}
/**
 * Implementing the bridge listing page
 */
function listingPage(e) {
  e.preventDefault();
  // check if it is not myasset, mymars, mybookmark, myrecommendation page
  if (Drupal.settings.bridge_basket != true ) {
    base_path = Drupal.settings.bookmark.basepath;
    setCookie('bridge_redirect', this.href);
    // Set active class in cookie
    setCookie('bridge_basket_form', $(this).parent().next().attr("id"));
    window.location = base_path + "/" + "bridge";
  }
  else {
    thisLink = $(this);
    thisUrl = this.href;
    target = $(".main-content-wrapper");
    setCookie('bridge_redirect', this.href);
    // Set active class in cookie
    setCookie('bridge_basket_form', $(this).parent().next().attr("id"));
    //remove active class for bridge basket
    $(".expand-coll-list li").children("h4").removeClass("active");
    ajaxBridge(thisUrl, target, null, thisLink, true);
  }
  return false;
}
/**
 * For hide and show tip
 */
function closeTip(e) {
  e.preventDefault();
  $(".edit-helptext").toggle();
  $(".tip-close").toggle();
  $(".tip-open").toggle();
}

function reply_message_click() {
  if($('#edit-body').val() == 'Type your message here') {
    $('#edit-body').val('');
  }
}
function reply_message_blur() {
  if(jQuery.trim($('#edit-body').val()) == ''){
    $('#edit-body').val('Type your message here');
  }
}
/**
 * Set the cookie value
 */
function setCookie(name,value,days) {
  if (days) {
    var date = new Date();
    date.setTime(date.getTime()+(days*24*60*60*1000));
    var expires = "; expires="+date.toGMTString();
  }
  else var expires = "";
    document.cookie = name+"="+value+expires+"; path=/";
}
/**
 * Get the cookie value
 */
function getCookie(name) {
  var nameEQ = name + "=";
  var ca = document.cookie.split(';');
  for(var i=0;i < ca.length;i++) {
    var c = ca[i];
    while (c.charAt(0)==' ') c = c.substring(1,c.length);
    if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
  }
  return null;
}
/**
 *  Delete the cookie value
 */
function deleteCookie(name) {
  setCookie(name,"",-1);
}
/**
 * Implementing the ajax process for bridge baskets
 */
function ajaxBridge(redirect_path, target, set_active_class, active_link, loading_display) {
  $.ajax({
    url: redirect_path,
    type: "GET",
    beforeSend: function() {
      // check if image has to be displayed
      if (loading_display) {
				$('<img src="'+ Drupal.settings.bookmark.loadingImg +'" class="image-loading"/>').insertAfter(thisLink);
      }
    },
    success: function(data) {
      target.html($(data).find(".main-content-wrapper").html());
      Drupal.attachBehaviors(".main-content-wrapper");
      //check if the active class basket link is enabled
      if (set_active_class) {
				$('#' + set_active_class).parent().children().addClass('active');
      }
      if (active_link) {
				active_link.parent().addClass('active');
      }

    },
    complete: function() {
      // check if image has to be displayed
      if (loading_display) {
				$('.image-loading').remove();
      }
    },
  });
}
$(document).ready(function() {
  // If cookie set from myasset, mymars, myrecommendation, mybookmarks
  url = window.location.href;
  explode  = url.split("/");
  if (getCookie("bridge_redirect") != 'undefined'  && getCookie("bridge_redirect") != null && explode[3] == 'bridge'  && explode[4] == null && explode[4] != 'undefined' ) {
    redirect_path = getCookie("bridge_redirect");
    target = $(".main-content-wrapper");
    set_active_class = getCookie("bridge_basket_form");
    $(".expand-coll-list li").children("h4").removeClass("active");
    ajaxBridge(redirect_path, target, set_active_class);

  }
  else if (Drupal.settings.bridge_basket == true ) {
    base_path = Drupal.settings.bookmark.basepath;
    if (Drupal.settings.bridge_basket_assignment == true) {
      $('body').addClass('common-content-border');
      redirect_path = base_path + "/bridge/myassignments";
      set_active_class = "assignment-block-form";
    }
    else {
      redirect_path = base_path + "/bridge/myassets";
      set_active_class = "myasset-basket-form";
    }

    target = $(".main-content-wrapper");
    ajaxBridge(redirect_path, target, set_active_class);
  }


  if ($('.assign-form-block').length > 0) {
    $('.assign-form-block').hide();
  }
  if ($('.share-form-block').length > 0) {
    $('.share-form-block').hide();
  }

  //By Default we need to hide the Acions dropdown.
  if($('.action-buttons').length > 0){
    //$('.action-buttons').hide();
    $('.action-buttons').addClass("element-invisible");
  }

  var pathname = window.location.pathname;
  var arg = pathname.split("/");
  // to load the div for corresponding pages. TODO : NEED TO MINIMIZE THE CODE
  if(arg[1] == 'bridge' && arg[2] == 'mymars') {
    $(".expand-coll-list li:first").children("h4").addClass("active");
  }
  else if(arg[1] == 'bridge' && arg[2] == 'mybookmarks') {
    $(".expand-coll-list li:nth-child(2)").children("h4").addClass("active");
  }
  else if(arg[1] == 'bridge' && arg[2] == 'myrecommendations') {
    $(".expand-coll-list li:nth-child(3)").children("h4").addClass("active");
  }
  else if(arg[2] == 'myassets') {
    $(".expand-coll-list li:nth-child(4)").children("h4").addClass("active");
  }
  else if(arg[1] == 'bridge' && arg[2] == 'mycurriculum') {
    $(".my-playlist-block .expand-coll-list li:first").children('div, p, form').slideDown('slow');
    $(".my-playlist-block .expand-coll-list li:first").children("h4").removeClass("title-collapse").addClass("title-expand active");
  }
  else if(arg[1] == 'bridge' && arg[2] == 'myassignments') {
    $(".expand-coll-list li:nth-child(4)").children("h4").addClass("active");
  }
  $(".my-playlist-block .expand-coll-list li:first").children('div, p, form').slideDown('slow');
  $(".my-playlist-block .expand-coll-list li:first").children("h4").removeClass("title-collapse").addClass("title-expand active");

  $('.exp-coll-playlist').live('click', openclosePlaylist);
  $(".topic-list").hide();
});


function openclosePlaylist() {
  $(this).parent().next().toggle();
  if ($(this).parent().hasClass('active')) {
    $(this).parent().removeClass("title-expand active").addClass("title-collapse");
  }
  else {
    $(this).parent().addClass('active');
    $(this).parent().removeClass("title-collapse").addClass("title-expand active");
  }
}

function expand_collapse() {
  flag = $(this).parent("h4").hasClass("title-expand");
  if(flag){
    $(this).parents('li').children('div, p, form').slideUp('slow');
    $(this).parents("h4").removeClass("title-expand active").addClass("title-collapse");
    flag = false;
  }
  else{
    $(this).parents('li').children('div, p, form').slideDown('slow');
    $(this).parents("h4").removeClass("title-collapse").addClass("title-expand active");
    flag = true;
  }
}
