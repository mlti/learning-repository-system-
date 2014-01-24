// $Id$
//This is for myassets page - dropdown menu on add new asset
Drupal.behaviors.assetsDD = function(context) {
  var timeout = 1000, ddTimer = 0, ddTimer2 = 0;

  $('#main-asset-create').click(function(){
    cancelTimer();
    //$('.asset-buttons').stop(true, true).slideDown();
    if($('.asset-buttons').hasClass("element-invisible")) {
	 $('.asset-buttons').removeClass("element-invisible");
    }
    else{
	 $('.asset-buttons').addClass("element-invisible");
    }
  }, function(){
    startClose();
  });


  function cancelTimer() {
    if(ddTimer) {
      window.clearTimeout(ddTimer);
      ddTimer = null;
    }
  }

  function startClose() {
    ddTimer = window.setTimeout(closeMenu, timeout);
  }

  function closeMenu() {
   $('.asset-buttons').slideUp();
  }
}
