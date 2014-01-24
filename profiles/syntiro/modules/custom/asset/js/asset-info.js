// $Id$
//Get Default Recommend Subject, Message on Document Ready
var rec_Subject = '';
var rec_Message = '';
$(document).ready(function() {
  rec_Subject = $('#edit-rec-subject').val();
	rec_Message = $('#edit-rec-body').text();
});

//This is for asset delete page from asset edit form
Drupal.behaviors.assetDelete = function(context) {
	
  // to show help text for file upload in asset VIDEO and IMAGE - START
  var pathname = window.location.pathname;
  arg = pathname.split("/");
  if(arg.length >= 5) {
    var last_arg = arg[4].split(",");
    if(last_arg == 'video') {
      $('#edit-field-custom-file-upload-0-upload-wrapper .description').append('Allowed extensions: <em>mov flv</em>');
    }
		if(last_arg == 'image') {
      $('#edit-field-custom-file-upload-0-upload-wrapper .description').append('Allowed extensions: <em>png gif jpg jpeg</em>');
    }
  }

 
  // change Add another items to Add another in co-author fields
  if ($('.page-asset').length > 0 &&  $('#edit-field-coauthor-field-coauthor-add-more').length > 0) {
    $('#edit-field-coauthor-field-coauthor-add-more').attr('value', 'Add Another');
  }

  $('#edit-field-format-value').change(format_content);
  if ($("#edit-field-custom-file-upload-0-filefield-remove").length > 0 ) {
    $("#hide_remove_upload").attr("style", {display:"block"});
  }
  if ($("#edit-field-custom-file-upload-0-filefield-upload").length > 0 ) {
    $("#hide_remove_upload").hide();
  }

  // Asset info block on asset page right side
  // More Option link
  $('.more-info-open').click(toggle_info);

  // open of review show and close
  //$('#edit-field-openforreview-value-1').click(for_reviewers);

  // Categories open and show
  $('.hide-cat').click(for_categories);

	// For recommend button show and hide in asset view page
  $('.recommend-button').click(recommend_toggle);
    // For recommend button show and hide in asset view page
  $('.share-link').click(share_toggle);

  //Click the Actions dropdown. Show/Hide of Actions dropdown.
	$('.action-main .action-main-button').click(function(){
		//$('.action-buttons').toggle();
		if($('.action-buttons').hasClass("element-invisible")) {
		        $('.action-buttons').removeClass("element-invisible");
		}
		else{
			$('.action-buttons').addClass("element-invisible");
		}
		
    return false;
	});

	//Hide the Actions dropdown, when we cick outside the Actions option.
	$('body').click(function(){
		//$('.action-buttons').hide();
		$('.action-buttons').addClass("element-invisible");
	});

	//When we select an option from Action dropdown, we need to replace the Main option with Selected option
	$('#actions-available-option ul li').click(function(){
		var selectedOption = $(this).text();
		if(selectedOption == 'Share' || selectedOption == 'Recommend'){
		$('.action-main-button .selected-list .seleted-action-option').text(selectedOption);
		}
    else{
			$('.action-main-button .selected-list .seleted-action-option').text('Actions');
		}

		if(selectedOption == 'Share'){
      $('.assign-form-block').hide();
			clear_Error();
		}
		else if(selectedOption == 'Recommend'){
      $('.share-form-block').hide();
		}
		else{
			$('.share-form-block').hide();
			$('.assign-form-block').hide();
			clear_Error();
		}
	});
  $('.action-main .action-main-button').blur(function(){
		$('.action-main-button .selected-list .seleted-action-option').text('Actions');
	});
	// to hide preview button in compose and reply message page.
	var pathname = window.location.pathname;
	var arg = pathname.split("/");

	if(arg[1] == 'node' && arg[2] != '') {
 			$('label[for="edit-comment"]').hide();
      $('.textarea-identifier').hide();
	}

	$('.share-form-block .close').click(share_close);
	$('.assign-form-block .close').click(recommend_close);
	//$('.node-content-common').lionbars();

	// to call the function onclicking the image.
	//$("span.exp-coll").click(expand_collapse);
}


//Function is used to set Recommend option as 'User', and Show User's field, User's search icon.
function show_rec_users(){
	$('.selected-list .seleted-option').text('Users');
	$('#edit-rec-groups-wrapper').hide();
	$('.group-search-img').hide();
	$('#edit-rec-recipient-wrapper').show();
	$('.user-search-img').show();
}

//Closing the Recommend div
function recommend_close(e){
	e.preventDefault();
	$('.assign-form-block').hide();
	clear_Error();
	//When we close the Recommend form we need to set the Main Action Option as "Actions"
	$('.action-main-button .selected-list .seleted-action-option').text('Actions');
	show_rec_users();
}

//Closing the Share div
function share_close(e){
	e.preventDefault();
	$('.share-form-block').hide();
	//When we close the Share form we need to set the Main Action Option as "Actions"
  $('.action-main-button .selected-list .seleted-action-option').text('Actions');
}

// show and hide option  for share content in asset view page (Toggle function)
  function share_toggle(e) {
    e.preventDefault();
    // hide assign form content
    $('.assign-form-block').hide();
		clear_Error();
    $('.share-form-block').toggle();
    remove_error();
		show_rec_users();
  }
 // More and Close option Toggle function
  function recommend_toggle(e) {
    e.preventDefault();
    // hide share content
    $('.share-form-block').hide();
    $('.assign-form-block').toggle();
		remove_error();
  }
 //Show and hide Actions Drop down.
  function action_toggle(){

	}
 //Fucntion to remove Error Message and Error classes when we toggle the Share and Recommend button.
  function remove_error(){
		if($('.edit-rec-recipient-error').length){
			$('.edit-rec-recipient-wrapper').removeClass('edit-rec-recipient-error');
		}
		$('input.error').removeClass('error');
		$('textarea.error').removeClass('error');
		$('label.error').remove();
	}

  // More and Close option Toggle function
  function toggle_info(e) {
    e.preventDefault();
    if ($('.collapse').length >= 1) {
      $('.collapse').addClass('expanded');
      $('.expanded').removeClass('collapse');
      $('.more-info-open').children().text('Close');
    }
    else {
      $('.expanded').addClass('collapse');
      $('.collapse').removeClass('expanded');
      $('.more-info-open').children().text('More');
    }
  }

  // To hide reviewers while clicking the checkbox Open for review.
  function for_reviewers() {
    if ($("#field-reviewers-items").css("display") != "none" && $('input[id=edit-field-openforreview-value-1]:checked').val() != 1) {
      $("#field-reviewers-items").fadeOut('slow');
      // To remove error class in textbox while un checking the review checkbox.
      $("#field-reviewers-items input").each(function() {
        $(this).removeClass('error');
      })

    }
    else {
      $("#field-reviewers-items").fadeIn('slow');
    }
  }

  // To hide categories while clicking the image in the left end.
  function for_categories() {
    // for arrow image change
    arrow_image = $('.hide-cat').children().next().children().attr('src');
    if ($(".hide-categories").css("display") != "none") {
      $(".hide-categories").fadeOut('slow');
      $('.hide-cat').children().next().children().attr('src', arrow_image.replace("arrow_down", "arrow"));
    }
    else {
      $(".hide-categories").fadeIn('slow');
      $('.hide-cat').children().next().children().attr('src', arrow_image.replace("arrow", "arrow_down"));
    }
  }

  // Based on Field format field content should hide and show
  function format_content() {
    if ($('#edit-field-format-value').val() == 'HTML') {
      $('#format-check').hide();
    }
    else {
      $('#format-check').show();
    }
  }
function clear_Error(){
  //Clear User, Comunity, Subject, Message field  Error class, Error message for both forms(Assignent, Recommend).
  $('#edit-rec-recipient-wrapper').removeClass('edit-rec-recipient-error');
  $('#edit-rec-groups-wrapper').removeClass('edit-rec-groups-error');

  $('#edit-rec-body, #edit-rec-subject').removeClass('error');
  $('#edit-rec-body, #edit-rec-subject').removeClass('error');
  $('label.error').remove();

	//We need to add the 'Add More' div when User option got selected.
	if(!($('.add-more').length)){
		var add_More = '<a class="add-more" href="javascript:" title="Add More Members">+ Add more</a>';
		$(add_More).insertBefore('#edit-rec-recipient');
	}

	//Set Default Subject, Message on Recommend form close.
	$('#edit-rec-subject').val(rec_Subject);
	$('#edit-rec-body').val(rec_Message);
  }
