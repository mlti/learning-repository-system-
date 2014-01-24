// $Id$
//This is for Assignment completion form validation.

Drupal.behaviors.assignment = function (context) {
   //It is used to hide the value of the default text box when clickin on it.
   $('#edit-report-users').focus(function() {
    if($(this).val() == "Enter assignee's name to find") {
      $(this).val('');
    }
   });

   // It will place the default value if nothing entered there.
   $('#edit-report-users').blur(function() {
		if($(this).val() == '' ) {
			$(this).val("Enter assignee's name to find");
			return false;
		} else {
			return true;
		}
   });

	// This function is used to reassign the users.
	$('#assigned-members-reassign-form .button-main #edit-submit').click(reassignUsers);

	// This function is used to delete the users.
  $('#assigned-members-delete-form .button-main #edit-submit').click(deleteUsers);
  // For popup close only
  //$('.popups-box #assigned-members-delete-form #edit-cancel').click(function(e){
  //  e.preventDefault();
  //  Popups.close();
  //});
  // This function is used to post the feedback.
  $('#assignment-feedback #edit-submit').click(postFeedback);

  $("#assigned-members-form .selected-dropdown .seleted-option").click(clickSelect);
  $("#assigned-members-form .selected-dropdown #assign-available-option div").click(clickSelectedItem);

	//To hide the Drop down if it was visibled in Assignment list page.
	$('body').click(clickAllhide);


  if($('#assignment-form-completion').length != 0) {
		var completed_remarks = Drupal.settings.assignment;
		if(completed_remarks.remarks){
			$('.page-assignment #assignment-form-completion #edit-completion-status-wrapper input').attr("disabled", true);
			$('.page-assignment #assignment-form-completion #edit-completion-remarks-wrapper-box textarea').attr("disabled", true);
		}
  }

  //Get the Completed check box status, whether it's checked or not.
  var completed_status = $('#edit-completion-status').is(':checked');

  ////When page reload we need to check whether the check box is checked or not.
  if(completed_status == true){ 
    $('.page-assignment #assignment-form-completion .listing-common-box-remarks').show();
  }
  else{
    $('.page-assignment #assignment-form-completion .listing-common-box-remarks').hide();
  }

  //Depending upon we click the check box, need to hide or show the Remarks textarea.
  $('.page-assignment #assignment-form-completion #edit-completion-status').click(function(){
    $('.page-assignment #assignment-form-completion .listing-common-box-remarks').toggle('slow');
  });

	//Replacing the form div when no group was selected.
	if($('.group-result').length > 0) {
		var groups_ids = [];
		$.each($('.form-checkbox:checked'), function() {
		  groups_ids.push($(this).parent().next().attr("value"));
		});
		if (groups_ids.length == 0) {
		  $('.group-result').html('<div class="popup-text">Please select atleast one group.</div>');
		}
		//Assignment Delete functionality for Group page.
		$('#assigned-group-delete #edit-submit').click(function(e) {
			e.preventDefault();
			//Getting Group ID's.
			var group_ids = [];
			$.each($('.form-checkbox:checked'), function() {
				group_ids.push($(this).parent().next().attr("value"));
			});
			//Getting Curriculum Id.
			var cid = $('#assigned-group-delete input#uid').attr("value");
			//Getting Sub Tpoic ID
			var st_id = $('#assigned-group-delete input#st_id').attr("value");
			base_path =Drupal.settings.bookmark.basepath;

			$.ajax({
			 //When click the yes option we call the assignment group delete function
			 data: {'gid[]':group_ids, 'st_id':st_id},
			 url: base_path+'/assignment/group/delete/' + cid + '/' + st_id,
			 type: "POST",
			 success: function(data) {
				if (data) {
					success = true;
				}
				else {
					success = false;
				}

				// After successfull compeltetion it will be redirected to this url.
				location.href= base_path+'/assignment/list/' + cid + '/' + st_id + '/groups?success='+ success;
				// Closes the popup
         Popups.close();
			 }
			});
			//return false;
		});
	}
  if ($('#assignment-form .edit-assign-recipient-error').length > 0 && $('#assignment-form #edit-assign-recipient-wrapper .error').length > 0) {
    $('#assignment-form #edit-assign-recipient-wrapper').removeClass('edit-assign-recipient-error');
  }


  //Hide the Available option Drop down when we click any other div than Drop down list
  $('body').click(function(){
    $('#assigned-members-form #assign-available-option').hide();
  });

  $('#assigned-members-form #1').click(function(){
     $('.seleted-option').html('<a href="javascript:;">Assigned</a>');
     $('#assign-available-option').hide();
  });
  $('#assigned-members-form #2').click(function(){
     $('.seleted-option').html('<a href="javascript:;">UnAssigned</a>');
     $('#assign-available-option').hide();
  });
  $('#assigned-members-form #3').click(function(){
     $('.seleted-option').html('<a href="javascript:;">All</a>');
     $('#assign-available-option').hide();
  });
}

// This function is used to reassign the users.
function reassignUsers(e){

	e.preventDefault();

	st_id = $('#st_id').val(); //sub-topic id
	uid   = $('#uid').val(); //user id
	node_id   = $('#node_id').val(); //node id

	base_path =Drupal.settings.bookmark.basepath;

	$.ajax({
		 // will redirect to the menu call back where the corresponding function will be done
		 url: base_path+'/assignment/reassign/info/'+uid+'/'+st_id,
		 type: "POST",
		 success: function(data) {
			 // After successfull compeltetion it will be redirected to this url.
			 location.href= base_path+'/assignment/list/'+node_id+'/'+st_id;
			 // Closes the popup
       Popups.close();
		 }
	 });
}

// This function is used to delete the users.
function deleteUsers(e){

	e.preventDefault();
	st_id = $('#st_id').val(); //sub-topic id
	uid   = $('#uid').val(); //user id
	node_id   = $('#node_id').val(); //node id

	base_path =Drupal.settings.bookmark.basepath;

	$.ajax({
		// will redirect to the menu call back where the corresponding function will be done
		url: base_path+'/assignment/delete/info/'+uid+'/'+st_id,
		type: "POST",
		success: function(data) {
			// After successfull compeltetion it will be redirected to this url.
			location.href= base_path+'/assignment/list/'+node_id+'/'+st_id;
			// Closes the popup
			Popups.close();
		}
	});
}

// This function is used to post the feedback.
function postFeedback(e){

	e.preventDefault();

	node_id   = $('#node_id').val(); //node id
	st_id = $('#st_id').val(); //sub-topic id
	uid   = $('#uid').val(); //user id
	feedback   = $('#edit-feedback').val(); // Feeback value
	base_path =Drupal.settings.bookmark.basepath;
  if (feedback.length > 0) {
   $.ajax({
     // will redirect to the menu call back where the corresponding function will be done
     // hence it is POST method no need of passing the arguments in URL.
     url: base_path+'/assignment/feedback/post',
     // using post method we are appending the values to their corresponding paramenter.
     type: "POST",
     data: {
       "ajaxed": true,
       "node_id":node_id,
       "uid":uid,
       "st_id":st_id,
       "feedback":feedback
     },
     success: function(data) {
       // After successfull compeltetion it will be redirected to this url.
       location.href= base_path+'/assignment/reports/'+node_id+'/'+st_id;
       // Closes the popup
       Popups.close();
     }
   });
  }
  else {
    $('#assignment-feedback').submit();
  }
}

//Function which is used to hide the Drop down if it was visibled in Assignment list page.
function clickAllhide(){
	// If visible it will hide the selectbox-(group) drop down.
  if($(".custom-selectboxes-replaced-list").is(':visible')) {
		$(".custom-selectboxes-replaced-list").hide();
  }
}

// Filter Results Paginations
function clickSelect() {
  $("#assigned-members-form .members-list-assignment  #assign-available-option").toggle();
	return false;
}


function clickSelectedItem() {

  $(".selectbox-list").html($(this).html());
  $("#assigned-members-form .members-list-assignment  #assign-available-option").toggle();

  target = $(".asset-edit-border .item-list");
  cur_url = window.location.pathname;
  base_path = Drupal.settings.bookmark.basepath;

  $('.no-mess').remove();

   if($(this).attr('id') == 1){
      // for assigned members
      $('#edit-own-validate-submit').show();
      $('.assigned-to-member li').hide();
      var assigned = $('.assigned-to-member li input');

      if(assigned.length > 0) {
         assigned.parents('li').show();
      } else if (assigned.length == 0) {
         $('<div class="no-mess">You have not assigned any member!</div>').insertAfter($('.members-list-assignment'))
      }
   } else if($(this).attr('id') == 2){
      // for un-assigned members
      $('#edit-own-validate-submit').hide();
      $('.assigned-to-member li').hide();
      var unassigned = $('.assigned-to-member li:not(:has(input))');
      if(unassigned.length > 0) {
       unassigned.show();
      } else if (unassigned.length == 0) {
         $('<div class="no-mess">You have not Un-assigned any member!</div>').insertAfter($('.members-list-assignment'));
      }
   } else if($(this).attr('id') == 3){
      // for all members
      $('#edit-own-validate-submit').show();
      $('.assigned-to-member li').show();
   }
  return false;
}
