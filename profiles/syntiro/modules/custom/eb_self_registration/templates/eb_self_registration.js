Drupal.behaviors.eb_self_registration = function(context) {
  $('.eb-password-change .info-content').scroll(function () {
    if ($(this).scrollTop() >= ($(this)[0].scrollHeight - $(this).height() - 1)) {
      $('.eb-password-change #edit-submit').removeAttr('disabled');
      $('.eb-password-change #edit-submit').css({
         color: '#4F4F4F'
      });
    }
    else {
      $('.eb-password-change #edit-submit').attr({
        disabled: 'disabled' 
      });
      $('.eb-password-change #edit-submit') .css({
        color : '#8b8b8b'
      });
    }
  });
}