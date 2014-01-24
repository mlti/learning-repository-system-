/**
 * @file
 * Clientside Validation custom rule implementation.
 */
/**
 * It speaks for itself that Clientside Validation cannot provide javascript
 * validation codes for custom validation rules defined in php. So if you want
 * to support Clientside Validation you will have to code the javascript
 * equivalent of your custom php validation rule and make it available for
 * Clientside validation. Below is an example of how you would do this.
 */
//Define a Drupal behaviour with a custom name
Drupal.behaviors.edubridgeBehavior = function (context) {

  //Add an eventlistener to the document reacting on the
  //'clientsideValidationAddCustomRules' event.
  $(document).bind('clientsideValidationAddCustomRules', function(event){

    //Add your custom method with the 'addMethod' function of jQuery.validator
    //http://docs.jquery.com/Plugins/Validation/Validator/addMethod#namemethodmessage
    jQuery.validator.addMethod("chars_count", function(value, element, param) {
      //let an element match an exact value defined by the user
      //alert(value.length);
      if(value.length <= 1000) {
        return true;
      }
      else {
        return false;
      }
      //var intRegex = /^.{0,1000}$/;
      //return intRegex.test(value);
      //return value == param;
    //Enter a default error message, numbers between {} will be replaced
    //with the matching value of that key in the param array, enter {0} if
    //param is a value and not an array.
    }, jQuery.format('Value must enter only 1000 jquery'));


    jQuery.validator.addMethod("auth_check", function(value, element, param) {
      $.ajax({
        type: 'POST',
        data: {user:value},
        url:Drupal.settings.basePath+'check/user',
        global: true,
        success: function (content) {
          //When we entered already exisiting email, error will throw.
          if(content){
            return false;
          }
          else {
            return true;
          }
        }
      });
    });

    //Custom Rule for Recommend Community field.
    jQuery.validator.addMethod("check_community", function(value, element, param) {
      if(!value) {
        //Hide the Error tag after 10 sec.
        setTimeout(function(){
          $('label.error').hide();
          //Remove the custom error class for alignment.
          $('#edit-rec-subject').removeClass('error');
          $('#edit-rec-body').removeClass('error');
          $('#edit-rec-groups').removeClass('error');
          }, 10000);
        return false;
      }
      else {
        return true;
      }
    });

    //Custom Rule for Recommend User field.
    jQuery.validator.addMethod("check", function(value, element, param) {
      if(!value || $.trim(value) == '' || value == 'Type your message here') {
        if ($('#recommend-form #edit-rec-recipient-wrapper').css('display') != 'none') {
          $('#recommend-form #edit-rec-recipient-wrapper').addClass('edit-rec-recipient-error');
          $('#edit-rec-recipient').val('');
        }
        if ($('#recommend-form #edit-rec-groups-wrapper').css('display') != 'none') {
          $('#recommend-form #edit-rec-groups-wrapper').addClass('edit-rec-groups-error');
        }
        //Hide the Error tag after 10 sec.
        setTimeout(function(){
          $('label.error').hide();
          //Remove the custom error class for alignment.
          $('#recommend-form #edit-rec-recipient-wrapper').removeClass('edit-rec-recipient-error');
          $('#recommend-form #edit-rec-groups-wrapper').removeClass('edit-rec-groups-error');
          $('#edit-rec-subject').removeClass('error');
          $('#edit-rec-body').removeClass('error');
          }, 10000);
        //Hide the add more link on Error.
        setTimeout(function(){
          $('.add-more').remove();
        }, 0);
        return false;
      }
      else {
        return true;
      }
    });

    //Custom Rule for Assignment User field.
    jQuery.validator.addMethod("user_check", function(value, element, param) {
      var hasError = true;
      if(!value || $.trim(value) == '') {
        if ($('#assignment-form #edit-assign-recipient-wrapper').css('display') != 'none') {
          $('#assignment-form #edit-assign-recipient-wrapper').addClass('edit-assign-recipient-error');
          $('#edit-assign-recipient').val('');
        }
        if ($('#assignment-form .rec-groups').css('display') != 'none') {
          $('#assignment-form #edit-assign-groups-wrapper ').addClass('edit-assign-groups-error');
        }
        //Hide the Error tag after 10 sec.
        setTimeout(function(){
          $('label.error').hide();
          //Remove the custom error class for alignment.
          $('#assignment-form #edit-assign-recipient-wrapper').removeClass('edit-assign-recipient-error');
          $('#assignment-form #edit-assign-groups-wrapper').removeClass('edit-assign-groups-error');
          $('#edit-assign-subject').removeClass('error');
          $('#edit-assign-body').removeClass('error');
          }, 10000);
        //Hide the add more link on Error.
        setTimeout(function(){
          $('.add-more').remove();
        }, 0);
        return false;
      }
      else
      {
        return true;
      }
    }, jQuery.format('Value must enter only integer jquery'));

    //Custom Rule for Assignment Community field.
    jQuery.validator.addMethod("check_community_assignment", function(value, element, param) {
      if (!value) {
        //Hide the Error tag after 10 sec.
        setTimeout(function(){
          $('label.error').hide();
          //Remove the custom error class for alignment.
          $('#edit-assign-subject').removeClass('error');
          $('#edit-assign-body').removeClass('error');
          $('#edit-assign-groups').removeClass('error');
          }, 10000);
        return false;
      }
      else {
        return true;
      }
    }, jQuery.format('Select community on Assign Page'));

    jQuery.validator.addMethod("check_subject", function(value, element, param) {
      if (!value || value == 'Please type a subject.') {
        if ($('#assignment-form .edit-assign-recipient-error').length > 0 && $('#assignment-form #edit-assign-recipient-wrapper .error').length > 0 && $('#assignment-form #edit-assign-recipient-wrapper .auto-to').length > 0) {
          $('#assignment-form #edit-assign-recipient-wrapper').removeClass('edit-assign-recipient-error');
        }
        return false;
      }
      else {
        return true;
      }
    }, jQuery.format('Enter any text except Subject text.'));

    jQuery.validator.addMethod("check_body", function(value, element, param) {
      if (!value || value == 'Please drop your instructions here..') {
        if ($('#assignment-form .edit-assign-recipient-error').length > 0 && $('#assignment-form #edit-assign-recipient-wrapper .error').length > 0  && $('#assignment-form #edit-assign-recipient-wrapper .auto-to').length > 0) {
          $('#assignment-form #edit-assign-recipient-wrapper').removeClass('edit-assign-recipient-error');
        }
        return false;
      }
      else {
        return true;
      }
    }, jQuery.format('Enter any text except Drop your Instructions text.'));

    jQuery.validator.addMethod("check_message_assignment", function(value, element, param) {
      if(value.length > 100) {
        return true;
      }
      else {
        return false;
      }
    }, jQuery.format('Select community on Assign Page'));

  });

  jQuery.event.trigger('clientsideValidationAddCustomRules');
}
