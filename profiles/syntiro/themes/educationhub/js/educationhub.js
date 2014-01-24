$(document).ready(function() {
  // For footer menu block depends upon block it will increase the width
  if ($('#footer .footer-menu-links .block').length > 0 ) {
    footer_menu_count = $('#footer .footer-menu-links .block').length;
    $('#footer .footer-menu-links').attr('style', 'width:'+ (footer_menu_count*140) + 'px');
  }
});
