// $Id$
//This is for curriculum info page - making the fieldset collapsable
Drupal.behaviors.course_group = function(context) {
  $('.community-info legend span').click(function(){
    $(this).parent().next().slideToggle();
    $(this).toggleClass('info-status-closed');
  });

}
