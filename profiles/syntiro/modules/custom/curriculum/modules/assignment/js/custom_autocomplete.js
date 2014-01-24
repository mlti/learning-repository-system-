// $Id$
//This is for Recommendation form Autocomplete functionality.

Drupal.behaviors.recommend_autocomplete = function (context) {
  //Default Base path from Drupal.
  var base_path = Drupal.settings.bookmark.basepath;

  //Variable Define for Form types.
  var formType = ''; //Variable for Recommend, Assignment Input Id.
  var formTypeMain = ''; //Variable for Recommend, Assignment Form Id.
  var unbindSubmit = '';
  var formTypeSubmit = ''; //Variable for Recommend, Assignment Form Submit Id.
  var formTypeSpanNames = ''; //Variable for Recommend, Assignment Input Span class.
  var communityformType = ''; //Variable for Recommend, Assignment Community Input Id.
  var communityformTypeSpanNames = ''; //Variable for Recommend, Assignment Community Input Span class.
  var touserType = ''; //While submitting the form, we need to check based on this variable.
  var tocommType = ''; //While submitting the form, we need to check based on this variable.
  var userInput = '';//Mouser Over variable for Recommend, Assignment form User fields.
  var subInput = '';
  var bodyInput = '';
  var loading = false;//Variable for loading status.

  //Declaration of defined variables
  if($('#recommend-form').length){//For Recommend form
    formType = '#edit-rec-recipient';
    formTypeMain = '#recommend-form';
    unbindSubmit = '#recommend-form #edit-rec-submit:not(.already-clicked)';
    formTypeSubmit = '#recommend-form #edit-rec-submit';
    formTypeSpanNames = '#recommend-form #edit-rec-recipient-wrapper span.auto-to';
    userInput = '.recommend-to-input';
    subInput = '#edit-rec-subject';
    bodyInput = '#edit-rec-body';
    communityformType = '#edit-rec-groups';
    communityformTypeSpanNames = '#recommend-form #edit-rec-groups-wrapper span.auto-to span.community-nid';
    touserType = '#edit-rec-recipient-wrapper';
    tocommType = '#edit-rec-groups-wrapper';
  }
  else{//For Assignment form
    formType = '#edit-assign-recipient';
    formTypeMain = '#assignment-form';
    unbindSubmit = '#assignment-form #edit-assign-submit:not(.already-clicked)';
    formTypeSubmit = '#assignment-form #edit-assign-submit';
    formTypeSpanNames = '#assignment-form #edit-assign-recipient-wrapper span.auto-to';
    userInput = '.assign-to-input';
    subInput = '#edit-assign-subject';
    bodyInput = '#edit-assign-body';
    communityformType = '#edit-assign-groups';
    communityformTypeSpanNames = '#assignment-form #edit-assign-groups-wrapper span.auto-to span.community-nid';
    touserType = '#edit-assign-recipient-wrapper';
    tocommType = '.rec-groups';
  }

  //Mouse over tooltip for Recommend, Assignment fields.
  $(formType).attr('title', 'Add Users');
  $(communityformType).attr('title', 'Browse to add communities');
  
  $(subInput).attr('title', 'Subject');
  //For Message field we need to check.
  if(bodyInput == '#edit-rec-body'){
    $(bodyInput).attr('title', 'Recommendation Message');
  }
  else{
    $(bodyInput).attr('title', 'Assignment Instructions');
  }

  //When form is loading to bring the Add more link in User's field
  show_addmore(formType);

  //Remove the Add more link on To fiels focus event for User's Field
  $(formType).focus(function(){
    $('.add-more').remove();
  });

  //Implementation of .autocomplete() for Recommend form
  if($('#recommend-form').length || $('#assignment-form').length ){
    $(formType).autocomplete({
       autoFocus: true,
       delay: 0,
       source: function(req, add){
          loading = true;
          names = span_names(formTypeSpanNames);
          if($.trim(req.term) != ''){
            req.term = names + req.term;
            //Need to specify the Form Type Input for Autocomplete callback
            if(formType == '#edit-rec-recipient'){
              $.getJSON(base_path + '/messages/user-name-autocomplete/' + req.term, req, function(data) {
                loading = false;
                //create array for response objects
                var suggestions = [];
                j = 0;
                for(var i in data){
                  j++;
                }
  
                if(j > 0){
                  //process response
                  $.each(data, function(i, val){
                    suggestions.push(val);
                  });
  
                  //pass array to callback
                  if($('.add-more').length == 0){
                    add(suggestions);
                  }
                }
                else{//When we enter wrong keywords we need to hide the dropdown.
                  $("ul.ui-autocomplete").hide();
                }
              });
            }
            else{
              $.getJSON(base_path + '/assignment/users-name-autocomplete/' + Drupal.settings.nid, req, function(data) {
                loading = false;
                //create array for response objects
                var suggestions = [];
                j = 0;
                for(var i in data){
                  j++;
                }
  
                if(j > 0){
                  //process response
                  $.each(data, function(i, val){
                    suggestions.push(val);
                  });
  
                  //pass array to callback
                  if($('.add-more').length == 0){
                    add(suggestions);
                  }
                }
                else{//When we enter wrong keywords we need to hide the dropdown.
                  $("ul.ui-autocomplete").hide();
                }
              });
            }
          }
       },
      focus: function(event, ui) {
        return false;
      },
      select: function(e, ui) {
          var activeUser = getActiveusername();
          entercomma('', activeUser, formType, formTypeSpanNames, loading);
          //Need to remove the 'input-show', due to alignment of To field.
          $(formType).val('').removeClass('input-show');
       },
       change: function(e, ui) {
          //After selecting every User we need to hide the To User field.
          $(formType).val('').removeClass('input-show');
       }
    }).data("autocomplete")._renderItem = function(ul, item) {
          return $("<li></li>").data("item.autocomplete", item).append(
                  "<a>" + item.value + "</a>")
                  .appendTo(ul);
                   };
  }

 
        
  //Implementation of .keypress()
  $(formType).keypress(function(event) {
    //Check whether the Pressed key is commma(44)
    if(event.which == 44){
      var activeUser = getActiveusername();
      entercomma(event.which, activeUser, formType, formTypeSpanNames, loading);
     }
    //Check whether the Pressed key is enter(13)
    if(event.which == 13){
      var activeUsers = getActiveusername();
      if(!activeUsers){
        var activeUser = getActiveusername();
        entercomma(event.which, activeUser, formType, formTypeSpanNames, loading);
        $(formType).hide();
        $(formType).val('').removeClass('input-show').focus();
        show_addmore(formType);

        event.preventDefault();
      }
    }
  });

  //Implementation of .blur()
  $(formType).blur(function(){
    //Check whether the Add More link is already there or not. If no, then we need to add the Add More link.
    if(!$('.add-more').length){
      show_addmore(formType);
    }
    //Need to remove the 'input-show', due to alignment of To field.
    $(formType).removeClass('input-show').val('');
  });

  //When we click the Remove link in User's widget.
  $(".remove", document.getElementById(formType + "-wrapper")).live("click", function(){
    //Remove clicked User span.
    $(this).parent().remove();

    //When we delete all selected user, we need to show the To user's field. Then only clientside validation working fine.
    if($(formType + "-wrapper span.auto-to").length == 0) {
      $(formType).val('');
      $(formType).show();
    }
    else{
      $(formType).hide();
    }
    $(formType).val('').removeClass('input-show');
    show_addmore(formType);
  });


  /*
   * When click the Add more link.
   * We need to remove the Add more link.
   * And show and focus the Users input field with null value
   */
  $(".add-more", document.getElementById(formType + "-wrapper")).live("click", function(){
    $('.add-more').remove();
    $(formType).val('').addClass('input-show').show().focus();
  });

  //Recommend form submit function.
  //$(unbindSubmit).addClass('already-clicked').click(function(e){
  $(formTypeSubmit).unbind("click").click(function(e){
    e.preventDefault();
    //Set Selected Suptopic ids in hidden field
    if(formTypeSubmit == '#assignment-form #edit-assign-submit'){
      var selectedSubtopics = '';
      //For Single Assignment
      if(Drupal.settings.nid){
        selectedSubtopics = Drupal.settings.nid;
      }
      else{//For multiple assignment
        $('.curriculum-topic .form-checkbox:checked').each(function(){
            var selectSubtopic = $(this).parent().next().val();
            if(selectedSubtopics == ''){
                selectedSubtopics += selectSubtopic;
            }
            else{
                selectedSubtopics += ',' + selectSubtopic;
            }
        });
        
      }
      $('#edit-assign-subtopics').val(selectedSubtopics);
    }
    //For User field value
    if($(tocommType).css('display') == 'none'){
      var activeUsers = getActiveusername();
      var names = span_names(formTypeSpanNames);
      var array = [];
      array = names.split(', ');

      //Check whether atleast one user are active in Autocomplete dropdown option.
      if(activeUsers && $.inArray(activeUsers, array) == -1){
        adding_span(activeUsers, formType);
        var names = span_names(formTypeSpanNames);
        $(formType).val(names);
        $(formTypeMain).submit();
      }
      else{
        var names = span_names(formTypeSpanNames);
        if(names){
          $(formType).val(names);
          $(formType).css('display', 'none');
          $(formTypeMain).submit();
        }
        else{
          $(formTypeMain).submit();
        }
      }
    }
    //For Community field value
    else if($(touserType).css('display') == 'none'){
      var communityIds = span_ids(communityformTypeSpanNames);
      if(communityIds.length > 0){
        $(communityformType).val(communityIds);
        $(communityformType).css('display', 'none');
        $(formTypeMain).submit();
      }
      else{
        $(formTypeMain).submit();
      }
    }
    return false;
  });


  //When recommend page is loaded, if there is any Users in User's field we need to bring the <span> structure. It's also applicable, when form got error in submit.
  //if($(formType).val() != ''){
  //  var array = [];
  //  var error_users = '';
  //
  //  blur_Users = $(formType).val();
  //  array = blur_Users.split(', ');
  //
  //  //Construct Span structured username.(Single/Multiple)
  //  $.each(array, function(index, value) {
  //    if($.trim(value).length != 0){
  //      error_users += '<span class="auto-to">' + value + '<a class="remove" href="javascript:" title="Remove ' + value + '">x</a></span>';
  //    }
  //  });
  //
  //  if($('.auto-to').length){
  //    $('.auto-to').remove();
  //  }
  //
  //  //Append Span structured username in Input field
  //  $(error_users).insertBefore(formType);
  //
  //  show_addmore(formType);
  //}

  //Hide and show the Subject, Body field content of Assignment form.
  $('#edit-assign-body, #edit-assign-subject').focus(function(){
    if($(this).val() == 'Please drop your instructions here..'){
      $(this).val('');
    }
    else if($(this).val() == 'Please type a subject.'){
      $(this).val('');
    }
  });
  //Hide and show the Subject, Body field content of Assignment form.
  $('#edit-assign-body, #edit-assign-subject').blur(function(){
    if($('#edit-assign-body').val() == ''){
      $(this).val('Please drop your instructions here..');
    }
    else if($('#edit-assign-subject').val() == ''){
      $(this).val('Please type a subject.');
    }
  });

}

//Main funcion deals with When comma or enter key was pressed.
function entercomma(key, currentUsername, formType, formTypeSpanNames, loading, event){
  //Check whether the entered value is valid or not

  if(currentUsername.length > 0){
    var names = span_names(formTypeSpanNames);
    var array = [];
    array = names.split(', ');

    //console.log($.inArray(rec_users, array));
    if($.inArray(currentUsername, array) == -1){
      adding_span(currentUsername, formType);
      if(!loading){
        $(formType).hide();
      }
      if(key != 44){
        show_addmore(formType);
      }
    }
  }
  else{
    if(key != 44){
      show_addmore(formType);
    }
    if(!loading){
      $(formType).hide();
    }
  }

  //For Comma event we need to hide the Input field, and remove the input-show class
  if(key == 44){
    $("ul.ui-autocomplete li").children().removeClass('ui-state-hover');
    $("ul.ui-autocomplete").hide();
    $(formType).hide();
    $(formType).val('').removeClass('input-show').focus();
    show_addmore(formType);
  }
}


//Function for adding 'Add more' link in User's input field.
function show_addmore(formType){
  //Check whether the Add more link is already there or not. If yes remove it.
  if($('.add-more').length){
    $('.add-more').remove();
  }
  //Adding 'Add more' text in Users input field.
  add_more = $('<a>').addClass("add-more").attr({href: "javascript:", title: "Add More Members"}).text('+ Add more');
  add_more.insertBefore(formType);

  $(formType).val('');
}


//Function for adding single 'Span structure' in User's input field.
function adding_span(username, formType){
  //Construct Span structure to adding in User's input field
  if($.trim(username) != ''){
    span_users = '<span class="auto-to">' + username + '<a class="remove" href="javascript:" title="Remove ' + username + '">x</a></span>';
    if($('.add-more').length){
      $(span_users).insertBefore('.add-more');
    }
    else{
      $(span_users).insertBefore(formType);
    }
  }
  //While adding Span names we need to remove Error message, Error classes.
  $('#edit-rec-recipient-wrapper').removeClass('edit-rec-recipient-error');
  $('#edit-rec-recipient-wrapper label.error').remove();
  $('#edit-rec-recipient').removeClass('error');
}

            //var selectSubtopic = $(this).parent().next().val();
            //if(selectedSubtopics == ''){
            //    selectedSubtopics += selectSubtopic;
            //}
            //else{
            //    selectedSubtopics += ',' + selectSubtopic;
            //}

//Function for getting all names from whole 'Span structure' in User's input field.
function span_names(formTypeSpanNames){
  //Get whole name string like as (Student1xStudent2x..)
  var names = '';
  $(formTypeSpanNames).each(function(index){
    var name = $(this).text();
      names += name + '>';
  });
  //Replace the string (Student1x>Student2x>Student3x>..) as this (Student1, Student2, ..)
  while(names.indexOf("x>") != -1)
    names = names.replace("x>", ", ");

  return names;
}

//Function for getting all names from whole 'Span structure' in User's input field.
function span_ids(communityformTypeSpanNames){
  var ids = [];
  $(communityformTypeSpanNames).each(function(index) {
    ids.push($(this).text());
  });

  return ids;
}


//Function to get Acitve user from Autocomplete drop down
function getActiveusername(){
  var activeUser = '';
  //Need to check whether drop down is hide or not. If hide, no need to get the 'activeUser' name.
  if($('ul.ui-autocomplete').css('display') != 'none'){
    //Get active(in ul li.acitve) User name.
    activeUser = $(".ui-autocomplete .ui-menu-item a.ui-state-hover #eb-user-mail-id").text();
  }

  return activeUser;
}
