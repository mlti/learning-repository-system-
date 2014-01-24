Drupal.behaviors.searchpopup = function (context) {
	//define variables for User search popup sunmit in Assignment, REcommend form
	var spanCurrentval = '';
	var toUser = '';

	//If recommend form.
	if($('#recommend-form').length > 0){
		spanCurrentval = '#recommend-form #edit-rec-recipient-wrapper span.auto-to';
		toUser = '#edit-rec-recipient';
	}
	else if($('#assignment-form').length > 0){
		spanCurrentval = '#assignment-form #edit-assign-recipient-wrapper span.auto-to';
		toUser = '#edit-assign-recipient';
	}

  // Search textbox
  $('.username-result-pager ul.pager li a').click(searchpopup_pager);
  // Search buttton
  $('.popup-username-search-box #getSolrSearchform #edit-search').click(clickSearch);
  // Select button
  $('#username-submit-form #selected_user').click(function(event){
		event.preventDefault();
		clickSubmit(spanCurrentval, toUser);
	});
  // Cancel button
  //$('#username-submit-form #edit-cancel').click(Drupal.popups.close);

  $('.username-popup #assignment-form .search-img a').click(initiauser);
	$('.username-popup #privatemsg-new .search-img a').click(initiauser);
	$('.username-popup #og-invite-form .search-img a').click(initiauser);
  $('#recommend-form .user-search-img a').click(initiauser);

	$('#username-results .form-checkbox').click(regeruser);
	//User field search popup functionality in Recommend, Assignment form.
  //Click the Select All check box.
  $('#select-all-form #check-all').click(function(e){
    if($('#check-all').attr('checked')){
      $('.recommend-group-block .form-checkbox').attr('checked','checked');
      $('.recommend-group-block .form-checkbox').parents('div.recommend-group-block').addClass('active');
			// add the value to ed_search_userselect
      $('.recommend-group-block .form-checkbox:checked').each(function(){
				addvalues_Array(this.id, $(this).parent().next().attr('value'));
      });
    }
    else{
      $('.recommend-group-block .form-checkbox').removeAttr('checked');
      $('.recommend-group-block .form-checkbox').parents('div.recommend-group-block').removeClass('active');
			// remove the value to ed_search_userselect
			$('.recommend-group-block .form-checkbox:unchecked').each(function(){
				removevalues_Array(this.id);
      });
    }
  });
};


// Filter Results Paginations
function searchpopup_pager(e) {
    e.preventDefault();
    thisLink = $(this);
    thisUrl = this.href;
    target = $("#username-results");
     $.ajax({
      url: thisUrl,
      type: "GET",
      beforeSend: function() {
				$('<img src="'+ Drupal.settings.bookmark.loadingImg +'" id="img_check"/>').insertAfter(thisLink);
      },
      success: function(content) {
        target.html($(content).find("#username-results").html());
        Drupal.attachBehaviors("#username-results");
				var i = 0;
				var j =0;
        $('.popups-box #username-results input[type="checkbox"]').each(function() {
					if(typeof Drupal.settings.ed_search_userselect[this.id] != "undefined") {
						$("#"+this.id).attr('checked', true);
						$("#"+this.id).parent().closest('.recommend-group-block').addClass('active');
						i++;
					}
					j++;
        });
				if (i == j) {
					$('#check-all').attr('checked', true);
				}
				else {
					$('#check-all').attr('checked', false);
				}
				
        $('#img_check').remove();
      }
    });
    return false;
}

function initiauser(e) {
	Drupal.settings.ed_search_userselect = new Object();
}
/**
 * add ed_search_userselect values
 *
 */
function regeruser() {
  var usr_chk_id = this.id;
  var usr_chk_uname = $(this).parent().next().attr('value');
	if(this.checked) {
		addvalues_Array(usr_chk_id, usr_chk_uname);
		$(this).parents('div.recommend-group-block').addClass('active');
	}
	else {
		removevalues_Array(usr_chk_id);
		$(this).parents('div.recommend-group-block').removeClass('active');
	}
}
function addvalues_Array(usr_chk_id, usr_chk_uname){
	var usr_json_value = json_parse('{"'+usr_chk_id+'":"'+usr_chk_uname+'"}');
	$.extend(Drupal.settings.ed_search_userselect, usr_json_value);
}

function removevalues_Array(usr_chk_id) {
	delete Drupal.settings.ed_search_userselect[usr_chk_id];
}
//Function to calculate Json Object
function getObjectSize(myObject) {
  var count=0
  for (var key in myObject)
    count++
  return count
}


// Submit the user and post in to the textarea
function clickSubmit(spanCurrentval, toUser) {
  var selectedUsers = [];
  // checked username will get added to selected users array
  /*$('#popups input[type="checkbox"]:checked').each(function() {
      selectedUsers.push($(this).parent().next().attr('value'));
  });*/

  var clicked_User = getObjectSize(Drupal.settings.ed_search_userselect);
  //Check whether the User select object having value or not.
	if(clicked_User != 0){
		val_temp = Drupal.settings.ed_search_userselect;
    for(i in val_temp) {
			selectedUsers.push(val_temp[i]);
			removevalues_Array(i);
		}
		 
	}
	else{//Manual calculation of selected User's
		$('.recommend-group-block .form-checkbox:checked').each(function(){
			var selectAllUsers = $(this).parent().next().val();
			selectedUsers.push(selectAllUsers);
		});
	}
	var currentUsers = '';

	// in this we will get the current users who are avail in textbox.
	if (toUser) {
		//Get whole name string like as (Student1xStudent2x..)
		currentUsers = $(spanCurrentval).text();

		//Replace the string (Student1xStudent2x..) as this (Student1, Student2, ..)
		while(currentUsers.indexOf("x") > -1){
			currentUsers = currentUsers.replace("x", ", ");
		}
	}
	else if ($("#edit-recipient").length > 0) {
		currentUsers = $("#edit-recipient").val();
	}
	else {
		currentUsers = $("#edit-mails").val();
	}
  var regex;
	var currentUserswidget = '';
	var selectedInput = '';
  for (var i = 0; i < selectedUsers.length; i++) { 
    // make regex for this selectedUser so we can search to see if it's already there
    regex = new RegExp("(^|, )" + selectedUsers[i] + "(,|$)", "i");
    // if this username not found in the current string, then we can add it
		if (currentUsers.search(regex) == -1) {
			
			//For Assignment form we need to construct the span structure for appending
			if($(toUser).length > 0){
				currentUserswidget += '<span class="auto-to">' + selectedUsers[i] + '<a title="Remove ' + selectedUsers[i] + '" href="javascript:" class="remove">x</a></span>';
				selectedInput += selectedUsers[i] + ", ";
			}
			else{//Construct the User list for other forms
				if (currentUsers.length != 0) {
					currentUsers += ", ";
				}
				currentUsers += selectedUsers[i];
			}
    }
	}

  //Append the User list in Assignment To form
  if (toUser) {
    if(currentUserswidget){
			// Appending the Selected Users name in Assignment To User's field textbox.
			//Check atleast one user got selected.
			target = $(currentUserswidget).insertBefore(toUser);
			//Check whether the Add more link is already there or not. If yes remove it.
			if($('.add-more').length){
				$('.add-more').remove();
			}
			//After changing every User we need to append Add more link before the Input tag.
			add_more = $('<a>').addClass("add-more").attr({
				 href: "javascript:",
				 title: "Add more Users"
			}).text('+ Add more');
			add_more.insertBefore(toUser);

			$(toUser).hide();
			//Assign the User names in input field.
			$(toUser).val(currentUsers + selectedInput);
		}
  }
	else if ($("#edit-recipient").length > 0) {
		target = $("#edit-recipient").val(currentUsers);
	}
	else {
    target = $("#edit-mails").val(currentUsers);
  }

	//Check wether atleast one user got selected, Otherwise we didn't close the popup
  if(selectedUsers.length > 0){
    Popups.close();
  }

  return false;
}
// Search result will generate
function clickSearch(e) {
  e.preventDefault();
  searchtext = $('.popup-username-search-box #getSolrSearchform #edit-username-search-text').val();
  searchtype = 'filters=type:profile&solrsort=created desc';
  target = $("#username-results");
  $.ajax ({
      type: 'POST',
      url: Drupal.settings.basePath + 'popupsearch/results/'+searchtext+'?'+searchtype,
      global: true,
      success: function (content) {
        target.html($(content).find("#username-results").html());
        Drupal.attachBehaviors('#username-results');

        $('.popups-box input[type="checkbox"]').each(function() {
            if(typeof Drupal.settings.ed_search_userselect[this.id] != "undefined") {
              $("#"+this.id).attr('checked', true);
            }
        });
      }
  });
}
