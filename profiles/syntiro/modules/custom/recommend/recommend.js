Drupal.behaviors.recomment = function() {
  //In Assignment form, when the page is loading we need to hide the Assigned Community block.
  $('#block-assignment-2').hide();

  //Recommend Community Popup form submit function.
  $('.recommend-form-community #edit-submit').live('click', function(e){
    e.preventDefault();
    add_to_text('#edit-rec-groups');
  });
  $('.assignment-form-community #edit-submit').live('click', function(e){
    e.preventDefault();
    add_to_text('#edit-assign-groups');
  });

  // This method is called when the user select option is selected in Assign to Form -Assignment Module
  function if_user_checked() {
    // Will hide the groups drop down box, show the receipients text field in Recommend form.
    $('#edit-rec-groups-wrapper').attr('style','display:none');
    $('.group-search-img').attr('style','display:none');
    $('.rec-groups').attr('style','display:none');
    $('#edit-rec-recipient-wrapper').attr('style','display:block');
    $('.user-search-img').attr('style','display:block');

    // Both users text box and image icon Will shown   - By Shamila
    if($('#edit-assign-recipient-wrapper').attr('style','display:block') && $('.search-img').attr('style','display:block')) {
      $('#edit-assign-subject-wrapper').attr('style','display:block');
      $('#edit-assign-body-wrapper').attr('style','display:block');
      $('.button-main').attr('style','display:block');
    }
    //When we click the Members select option in Assignment form Assigned Groups block will disappear and then Assigned Members block will show.
    $('#block-assignment-1').show();
    $('#block-assignment-2').hide();

    //Set the value as 1 for Assignment option hidden field in Assignment form.
    $('#edit-assign-options').val(1);
    //Set the value as 1 for Recommend option hidden field in Recommend form.
    $('#edit-rec-options').val(1);

    //We need to add class in Assignment form, if User option was seleted. No need to add this class in Recommend form because there is no search icon on User field.
    $('.assignment-new-form').addClass('search-align');

    //clear the selection in Community field, when user field got selected.
    if($('#edit-rec-groups-wrapper .recommend-to-input .auto-to, #edit-assign-groups-wrapper .recommend-to-input .auto-to').length > 0){
      $('.auto-to').remove();
    }

    //We need to add the 'Add More' div when User option got selected.
    if(!($('.add-more').length)){
      var add_More = '<a class="add-more" href="javascript:" title="Add More Members">+ Add more</a>';
      $(add_More).insertBefore('#edit-assign-recipient');
      $(add_More).insertBefore('#edit-rec-recipient');
    }
    //Clear Error, Error classes in User, Community, Subject, Message
    clear_Error();
  }

  // This method is called when the groups select option is checked in Assign to Form -Assignment Module
  function if_group_checked() {
    // Will show the groups drop down box and hide the Receipient text field in Recommend form.
    $('#edit-rec-groups-wrapper').attr('style','display:block');
    $('.group-search-img').attr('style','display:block');
    $('.rec-groups').attr('style','display:block');
    $('#edit-rec-recipient-wrapper').attr('style','display:none');
    $('.user-search-img').attr('style','display:none');

    //Only group text box Will shown   - By Shamila
    if($('#edit-assign-groups').is("input") == true) {
      //$('#edit-assign-subject-wrapper').attr('style','display:none');
      //$('#edit-assign-body-wrapper').attr('style','display:none');
     // $('.button-main').attr('style','display:none');
    }
    // Will hide the users text box and image icon.
    $('#edit-assign-recipient-wrapper').attr('style','display:none');
    //When we click the Groups select option in Assignment form Assigned Members block will disappear and then Assigned Groups block will show.
    $('#block-assignment-1').hide();
    $('#block-assignment-2').show();

    //Set the value as 2 for Assignment option hidden field in Assignment form.
    $('#edit-assign-options').val(2);
    //Set the value as 2 for Recommend option hidden field in Recommend form.
    $('#edit-rec-options').val(2);

    //We need to remove class in Assignment form, if User option was seleted. No need to remove this class in Recommend form because there is no search icon on User field.
    $('.assignment-new-form').removeClass('search-align');

    //clear the selection in User field, when user field got selected.
    if($('#edit-rec-recipient-wrapper .recommend-to-input .auto-to, #edit-assign-recipient-wrapper .recommend-to-input .auto-to').length > 0){
      $('.auto-to').remove();
    }
    //Clear Error, Error classes in User, Community, Subject, Message
    clear_Error();
  }

  if(Drupal.settings.group_value == true) {
    // For Assignment and Recommend form only
    if_group_checked();

    // this if condition will not display the user's text box while community is selected.
    if($('#edit-rec-options-1').is(':checked') == false) {
      $('#edit-rec-recipient-wrapper').attr('style','display:none');
    }
  }

  //When we change the custom select box option we need show/hide the corresponding fields(Users/Communities) in Assignment form, Recommend form
  $('#assign-available-option .user-option').click(function(){
    if_user_checked();
  });
  $('#assign-available-option .group-option').click(function(){
    if_group_checked();
  });

  ////By default we need to hide the available options (User, Communities) in Both Assignment, recommend form
  //$('.selected-list').blur(function(){
  //  $('#assign-available-option').hide();
  //});

  //Show and hide the Assignment, Recommend options (User, Communities) drop down in Assignment form, Recommend form
  $('#assign-available-option').hide();
  $('.selected-dropdown .selected-list').live('click', function(){
    $('#assign-available-option').toggle();
    return false;
  });

  //Hide the Available option Drop down when we click any other div than Drop down list
  $('body').click(function(){
    $('#assign-available-option').hide();
  });

  $('.user-option').click(function(){
     $('.seleted-option').html('Users');
     $('#assign-available-option').hide();
     /*When we select User's option from drop down, we need to clear the Group selection in Group field
       in both Recommed, Assignment form.
     */
     $("#edit-rec-groups option:selected, #edit-assign-groups option:selected").removeAttr("selected");
  });


  $('.group-option').click(function(){
     $('.seleted-option').html('Communities');
     $('#assign-available-option').hide();
     /*When we select Group's option from drop down, we need to clear the User name selection, Span structure in User field
       in both Recommed, Assignment form.
     */
     // for assignment form
     $('#edit-assign-recipient').val('');
     $('#edit-assign-recipient-wrapper span.auto-to').remove();
     // for recommend form
     $('#edit-rec-recipient').val('');
     $('#edit-rec-recipient-wrapper span.auto-to').remove();
  });


  $('.user-option').mouseover(function(){
    $(this).addClass(' active');
    $('.group-option').removeClass(' active');
  });

  $('.group-option').mouseover(function(){
    $(this).addClass(' active');
    $('.user-option').removeClass(' active');
  });

  //Community field popup functionality in Recommend, Assignment form.
  //Click the Select All check box.
  $('#recommend-group-list-form #check-all').click(function(){
    if($('#check-all').attr('checked')){
      $('.recommend-group-block .form-checkbox').attr('checked','checked');
      $('.recommend-group-block .form-checkbox').parent().parent().addClass('active');
     
    }
    else{
      $('.recommend-group-block .form-checkbox').removeAttr('checked');
      $('.recommend-group-block .form-checkbox').parent().parent().removeClass('active');
    }
  });
  

  //When we click the Community list check box, adding the Active class. And Select All Check box functionality.
  $('.recommend-group-block .form-checkbox').click(function(){
    //Check whether all listing communities are checked or not.
    if($('.recommend-group-block .form-checkbox:checked').length  == $('.recommend-group-block .form-checkbox').length){
      $('#check-all').attr('checked', true);
    }
    else{
      $('#check-all').attr('checked', false);
    }
    //Adding active class when check a community in popup.
    if($(this).attr('checked')){
      $(this).parent().parent().addClass('active');
    }
    else{
      $(this).parent().parent().removeClass('active');
    }
  });

  //When we click the Community list check box, adding the Active class. And Select All Check box functionality.
  $('.recommend-group-block .form-checkbox').click(function(){
    //Check whether all listing communities are checked or not.
    if($('.recommend-group-block .form-checkbox:checked').length  == $('.recommend-group-block .form-checkbox').length){
      $('#check-all').attr('checked', true);
    }
    else{
      $('#check-all').attr('checked', false);
    }
    //Adding active class when check a community in popup.
    if($(this).attr('checked')){
      $(this).parents('div.recommend-group-block').addClass('active');
    }
    else{
      $(this).parents('div.recommend-group-block').removeClass('active');
    }
  });

}
function add_to_text(destination) {
  //Declare variables.
  var selectedCommunity = [];
  var communityName = '';
  var communityId = '';
  var spancommunity = '';
  var currentCommunity = [];

  //Get already assigned community array from Recommend community field.
  $('.auto-to .community-nid').each(function(index){
    currentCommunity.push($(this).text());
  });

  //Using .each() we need to get the Checked Community Span structure.
  $('.popups-box .recommend-group-listing input[type="checkbox"]').each(function(index) {
    //Check whether community option is checked or not.
    if($(this).is(':checked')){
      //Get Selected Community Name
      communityName = $(this).parent().next().children('.recommend-group-name').text();
      communityId = $(this).parent().next().next().next().val();

      //Check whether the Checked community is already in Current Community array.
      if($.inArray(communityId, currentCommunity) == -1){
        //Construct Span Structure.
        if(spancommunity == ''){
          spancommunity = '<span class="auto-to"><span class="community-name">' + communityName + '</span><span class="community-nid">' + communityId + '</span><a title="Remove ' + communityName + '" href="javascript:" class="remove">x</a></span>';
        }
        else{
          spancommunity = spancommunity + '<span class="auto-to"><span class="community-name">' + communityName + '</span><span class="community-nid">' + communityId + '</span><a title="Remove ' + communityName + '" href="javascript:" class="remove">x</a></span>';
        }
      }
    }
  });

  //Adding the span structure before the Community input field.
  if(spancommunity){
    $(spancommunity).insertBefore(destination);
  }
  //Closing the Community Popup. @todo: Need to handle the null selection.
  Popups.close();

}
  $(document).ready(function() {
    //Hide the Label for User, Communities, Subject, Message in Assignment, Recommend form.
    $('#edit-assign-recipient-wrapper label, #edit-rec-recipient-wrapper label').hide();
    $('#edit-assign-groups-wrapper label, #edit-rec-groups-wrapper label').hide();
    //$('#edit-assign-subject-wrapper label, #edit-rec-subject-wrapper label').hide();
    //$('#edit-assign-body-wrapper label, #edit-rec-body-wrapper label').hide();

    //Hide Groups field and Group Search Icon for both form.
    $('#edit-rec-groups-wrapper').hide();
    $('.group-search-img').hide();
  });

//For my recommendations page
//Making the type links loads the content via ajax
Drupal.behaviors.recType = function() {
  $('ul#rec-type a').click(recTypeChange);
}

//Recommendation type change ajax call
function recTypeChange() {
  thisLink = $(this);
  thisUrl = this.href;
  target = $("#rec-result-area");

  $.ajax({
    url: thisUrl,
    type: "GET",
    beforeSend: function() {
      target.html("Loading...");
    },
    success: function(data) {
      target.html($(data).find("#rec-result-area").html());
      Drupal.attachBehaviors("#rec-result-area");

      //reset all link's active class and add active class to the current link
      $('ul#rec-type li').removeClass("active");
      thisLink.parent('span').parent().addClass("active");
    }
  });
  return false;
}

//For my recommendations page
//Making the pager functionality in ajax
Drupal.behaviors.recPager = function(context) {
  $('#rec-pager ul.pager li a').click(rPager);
  $('#decline-confirmation-form #edit-submit').click(function(e){
    e.preventDefault();
    del_nid = $('#edit-bid').attr('value');
    // It is used to check if quiz content delete
    base_path = Drupal.settings.bookmark.basepath;
    $.ajax({
      url: base_path + '/recommend/' + del_nid + '/decline/confirm',
      type: "POST",
      success: function(data) {
          location.href = base_path + '/bridge/myrecommendations?del_title=success' ;
          // Closes the popup
          Popups.close();
      }
    });
  });
}
function rPager() {
  thisLink = $(this);
  thisUrl = this.href;
  target = $("#rec-result-area");
  params = thisUrl.substring(thisUrl.indexOf('?'));
  targetUrl = Drupal.settings.bookmark.basepath + "/recommendations/listing" + params;
  $.ajax({
    url: targetUrl,
    type: "GET",
    beforeSend: function() {
      //target.html("Loading...");
      $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').insertAfter(thisLink);
    },
    success: function(data) {
     // This function is in preview-baser.js
      preview_close_pager();
      target.replaceWith(data);
      Drupal.attachBehaviors("#rec-result-area");
      $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
    }
  });
  return false;
}

function clear_Error(){
  //Clear User, Comunity, Subject, Message field  Error class, Error message for both forms(Assignent, Recommend).
  $('#edit-rec-recipient-wrapper').removeClass('edit-rec-recipient-error');
  $('#edit-rec-groups-wrapper').removeClass('edit-rec-groups-error');
  $('#edit-assign-recipient-wrapper').removeClass('edit-assign-recipient-error');
  $('#edit-assign-groups-wrapper').removeClass('edit-assign-groups-error');

  $('#edit-assign-body, #edit-rec-body, #edit-rec-subject').removeClass('error');
  $('#edit-assign-body, #edit-rec-body, #edit-rec-subject').removeClass('error');
  $('label.error').remove();
}
