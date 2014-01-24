// $Id$
//This is for myassets page - dropdown menu to print asset content in word or pdf
Drupal.behaviors.assetsDD = function(context) {
  var timeout = 1000, ddTimer = 0;

  //$('#download-pdf a').hover(function(){
  //  cancelTimer();
  //  $('#asset-download-list').stop(true, true).slideDown();
  //}, function(){
  //  strartClose();
  //});

  function cancelTimer() {
    if(ddTimer) {
      window.clearTimeout(ddTimer);
      ddTimer = null;
    }
  }

  function strartClose() {
    ddTimer = window.setTimeout(closeMenu, timeout);
  }

  function closeMenu() {
    $('#asset-download-list').slideUp();
  }

  //$('#download-pdf .click-arrow').click(function(){
  //  $('#asset-download-list').slideUp();
  //});


}
