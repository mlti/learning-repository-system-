Drupal.behaviors.lom = function (context) {
  
    $("#import-course-submit").click(function () {      
      $('.loding-image').show();
     });   
  
    $('.node .content .field-type-filefield .field-items .filefield-file a').attr('target', '_blank');
}