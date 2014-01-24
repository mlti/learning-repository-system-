
//Define global variable, which will be used in Affiliated Recommend functionality.
var show;
$(document).ready(function(){
	show = $('.affiliated-recommend-form').html();
});

Drupal.behaviors.eb_search = function (context) {
  $('.custom-popup').width(650);
  // Error message will not hide only warning and confirmation message will hide
  if ($('.display-messages .status').length >= 1) {
    setTimeout(function clearMessages(){$('.display-messages').hide('slow');}, 20000);
  }
	$('.search-dropdown-list').click(cckfilter_list);
	$('body').click(clickAllhide_ccklist);
  if ($('.dropdown-cck-list').length > 0 ) {
		$('.dropdown-cck-list').hide();
	}
//	$('#edit-searchtype-0').click(function () {
//    $('#powerfind-asset').hide();
//    $('#powerfind-profile').show();
//  })

	if (!!Drupal.jsAC) { // this condition tests if autocomplete has been enabled
		/**
		 * Handler for the "keydown" event
		 *
		 * To search while press enter button
		 */
		Drupal.jsAC.prototype.onkeydown = function (input, e) {

			if (!e) {
				e = window.event;
			}
			switch (e.keyCode) {
				case 40: // down arrow
					this.selectDown();
					return false;
				case 38: // up arrow
					this.selectUp();
					return false;
				case 13: // enter
					base_path = Drupal.settings.bookmark.basepath;
					// check cck dropdown list
					if ($('.dropdown-cck-list').length > 0 ) {
						$('.dropdown-cck-list').hide();
					}
					// This condition is for basket: In that basket page two search box will come
					if ($('#edit-username-search-text').length > 0 && $('input[id="edit-username-search-text"]').val().length > 0 &&  jQuery.trim($('input[id="edit-username-search-text"]').val()) != '') {
						clickSearch(e); // This function is in eb_search_popup.js

					}
					// left side basket search box
					if ($('#getSolrSearchform-right').length > 0 && $('input[id="edit-searchText-right"]').val().length > 0 &&  jQuery.trim($('input[id="edit-searchText-right"]').val()) != '' ) {
						clickFind(); // This function is in eb_search2.js

					}
					
					// if the author text field is empty then we call this function
					if (($('#edit-search-author-filter').length > 0 &&  jQuery.trim($('input[id="edit-search-author-filter"]').val()) == '') ||
							($('#edit-search-coauthor-filter').length > 0 &&  jQuery.trim($('input[id="edit-search-coauthor-filter"]').val()) == '') ||
							($('#edit-search-reviewer-filter').length > 0 &&  jQuery.trim($('input[id="edit-search-reviewer-filter"]').val()) == '') ||
							($('#edit-search-subject-filter').length > 0 &&  jQuery.trim($('input[id="edit-search-subject-filter"]').val()) == '')||
							($('#edit-search-academic-filter').length > 0 &&  jQuery.trim($('input[id="edit-search-academic-filter"]').val()) == '')||
							($('#edit-search-institute-filter').length > 0 &&  jQuery.trim($('input[id="edit-search-institute-filter"]').val()) == '')||
							($('input[id="edit-searchText"]').length > 0 &&  jQuery.trim($('input[id="edit-searchText"]').val()) == '') ||
							($('#edit-search-mlrstandard-filter').length > 0 &&  jQuery.trim($('input[id="edit-search-mlrstandard-filter"]').val()) == '')) {
						
						return false;
					}
					
					//if (($('#edit-search-author-filter').length > 0 && (jQuery.trim($('input[id="edit-search-author-filter"]').val()) == ''|| (jQuery.trim($('input[id="edit-search-author-filter"]').val()).length == 1 && jQuery.trim($('input[id="edit-search-author-filter"]').val()).indexOf('"') == 0))) ||
					//		($('#edit-search-coauthor-filter').length > 0 && (jQuery.trim($('input[id="edit-search-coauthor-filter"]').val()) == ''|| (jQuery.trim($('input[id="edit-search-coauthor-filter"]').val()).length == 1 && jQuery.trim($('input[id="edit-search-coauthor-filter"]').val()).indexOf('"') == 0))) ||
					//		($('#edit-search-reviewer-filter').length > 0 && (jQuery.trim($('input[id="edit-search-reviewer-filter"]').val()) == ''|| (jQuery.trim($('input[id="edit-search-reviewer-filter"]').val()).length == 1 && jQuery.trim($('input[id="edit-search-reviewer-filter"]').val()).indexOf('"') == 0))) ||
					//		($('#edit-search-subject-filter').length > 0 && (jQuery.trim($('input[id="edit-search-subject-filter"]').val()) == ''|| (jQuery.trim($('input[id="edit-search-subject-filter"]').val()).length == 1 && jQuery.trim($('input[id="edit-search-subject-filter"]').val()).indexOf('"') == 0)))||
					//		($('#edit-search-academic-filter').length > 0 && (jQuery.trim($('input[id="edit-search-academic-filter"]').val()) == ''|| (jQuery.trim($('input[id="edit-search-academic-filter"]').val()).length == 1 && jQuery.trim($('input[id="edit-search-academic-filter"]').val()).indexOf('"') == 0)))||
					//		($('#edit-search-institute-filter').length > 0 && (jQuery.trim($('input[id="edit-search-institute-filter"]').val()) == ' '|| (jQuery.trim($('input[id="edit-search-institute-filter"]').val()).length == 1 && jQuery.trim($('input[id="edit-search-institute-filter"]').val()).indexOf('"') == 0) ))||
					//		($('input[id="edit-searchText"]').length > 0 &&  (jQuery.trim($('input[id="edit-searchText"]').val()) == '' || (jQuery.trim($('input[id="edit-searchText"]').val()).length == 1 && jQuery.trim($('input[id="edit-searchText"]').val()).indexOf('"') == 0))) ||
					//		($('#edit-search-mlrstandard-filter').length > 0 && (jQuery.trim($('input[id="edit-search-mlrstandard-filter"]').val()) == '' || (jQuery.trim($('input[id="edit-search-mlrstandard-filter"]').val()).length == 1 && jQuery.trim($('input[id="edit-search-mlrstandard-filter"]').val()).indexOf('"') == 0)))) {
					//	alert("true d");
					//	return false;
					//}
					
					// For search author textfield
					if ($('#edit-search-author-filter').length > 0 && $('input[id="edit-search-author-filter"]').val().length > 0 &&  jQuery.trim($('input[id="edit-search-author-filter"]').val()) != '' && $('input[id="edit-search-author-filter"]').val() != 'Search Author' ) {
						clicksearchfilter('name', $('#edit-search-author-filter').attr('value'));
						return false;
					}
					// For coauthor search
					if ($('#edit-search-coauthor-filter').length > 0 && $('input[id="edit-search-coauthor-filter"]').val().length > 0 &&  jQuery.trim($('input[id="edit-search-coauthor-filter"]').val()) != '' && $('input[id="edit-search-coauthor-filter"]').val() != 'Search Co Author' ) {
						clicksearchfilter('tm_coauthor', $('#edit-search-coauthor-filter').attr('value'));
						return false;
					}
					// for reviewer search
					if ($('#edit-search-reviewer-filter').length > 0 && $('input[id="edit-search-reviewer-filter"]').val().length > 0 &&  jQuery.trim($('input[id="edit-search-reviewer-filter"]').val()) != '' && $('input[id="edit-search-reviewer-filter"]').val() != 'Search Reviewers' ) {
						clicksearchfilter('tm_reviewer', $('#edit-search-reviewer-filter').attr('value'));
						return false;
					}
					// for subject search
					if ($('#edit-search-subject-filter').length > 0 && $('input[id="edit-search-subject-filter"]').val().length > 0 &&  jQuery.trim($('input[id="edit-search-subject-filter"]').val()) != '' && $('input[id="edit-search-subject-filter"]').val() != 'Search Subject' ) {
						clicksearchfilter('tm_subject', $('#edit-search-subject-filter').attr('value'));
						return false;
					}
					// for academic level search
					if ($('#edit-search-academic-filter').length > 0 && $('input[id="edit-search-academic-filter"]').val().length > 0 &&  jQuery.trim($('input[id="edit-search-academic-filter"]').val()) != '' && $('input[id="edit-search-academic-filter"]').val() != 'Search Academic Level' ) {
						clicksearchfilter('tm_academiclevel', $('#edit-search-academic-filter').attr('value'));
						return false;
					}
					// for Mlr standard search
					if ($('#edit-search-mlrstandard-filter').length > 0 && $('input[id="edit-search-mlrstandard-filter"]').val().length > 0 &&  jQuery.trim($('input[id="edit-search-mlrstandard-filter"]').val()) != '' && $('input[id="edit-search-mlrstandard-filter"]').val() != 'Search MLR Standard' ) {
						clicksearchfilter('tm_mlrstandard', $('#edit-search-mlrstandard-filter').attr('value'));
						return false;
					}
					// for institute search
					if ($('#edit-search-institute-filter').length > 0 && $('input[id="edit-search-institute-filter"]').val().length > 0 &&  jQuery.trim($('input[id="edit-search-institute-filter"]').val()) != '' && $('input[id="edit-search-institute-filter"]').val() != 'Search Institute' ) {
						clicksearchfilter('tm_institution', $('#edit-search-institute-filter').attr('value'));
						return false;
					}
				
					// check if search basket page and also header search is available
					if ($('.header-right  .search-type #edit-searchText').length > 0  && $('input[id="edit-searchText"]').val() != '' &&  $('input[id="edit-searchText"]').val() != 'Enter the topic and find' &&  jQuery.trim($('input[id="edit-searchText"]').val()) != '' && ($('#edit-username-search-text').length == 0 )) {
						$('#getSolrSearchform').unbind('submit'); // replace '#search-theme-form' with your search form id
						$('#getSolrSearchform').submit();
					}
				default: // all other keys
					return true;
			}
		};


		/**
		 * Performs a cached and delayed search
		 *
		 * To avoid alert message
		 */
		Drupal.ACDB.prototype.search = function (searchString) {
			var db = this;
			this.searchString = searchString;
			// See if this key has been searched for before
			if (this.cache[searchString]) {
				return this.owner.found(this.cache[searchString]);
			}

			// Initiate delayed search
			if (this.timer) {
				clearTimeout(this.timer);
			}
			this.timer = setTimeout(function() {
				db.owner.setStatus('begin');

				// Ajax GET request for autocompletion
				$.ajax({
					type: "GET",
					url: db.uri +'/'+ Drupal.encodeURIComponent(searchString),
					dataType: 'json',
					success: function (matches) {
						if (typeof matches['status'] == 'undefined' || matches['status'] != 0) {
							db.cache[searchString] = matches;
							// Verify if these are still the matches the user wants to see
							if (db.searchString == searchString) {
								db.owner.found(matches);
							}
							db.owner.setStatus('found');
						}
					}
				});
			}, this.delay);
		};
 }

  // for federated link
  $('.my-pager').click(federated_paging);
 

 // for default set default text
	$('#edit-search-coauthor-filter , #edit-search-subject-filter, #edit-search-academic-filter, #edit-search-author-filter, #edit-search-reviewer-filter, #edit-search-institute-filter , #edit-search-mlrstandard-filter').focus(function() {
    if($(this).val() == 'Search Subject' || $(this).val() == 'Search Academic Level' || $(this).val() == 'Search Author' ||$(this).val() == 'Search Co Author' || $(this).val() == 'Search Reviewers' || $(this).val() == 'Search Institute' || $(this).val() == 'Search MLR Standard') {
			$('#edit-search-coauthor-filter').val('Search Co Author');
			$('#edit-search-subject-filter').val('Search Subject');
			$('#edit-search-academic-filter').val('Search Academic Level');
			$('#edit-search-mlrstandard-filter').val('Search MLR Standard');
			$('#edit-search-author-filter').val('Search Author');
			$('#edit-search-reviewer-filter').val('Search Reviewers');
			$('#edit-search-institute-filter').val('Search Institute');
			$(this).val('');

    }


  });
 // For home page search box
  $('#edit-searchText, #edit-searchText-1, #edit-username-search-text,  #edit-searchText, #edit-searchText-right').focus(function() {
    if($(this).val() == 'Enter the topic and find' || $(this).val() == 'Enter People Name' || $(this).val() == 'Search User') {
      $(this).val('');
    }
		$('#edit-search-coauthor-filter').val('Search Co Author');
		$('#edit-search-subject-filter').val('Search Subject');
		$('#edit-search-academic-filter').val('Search Academic Level');
		$('#edit-search-author-filter').val('Search Author');
		$('#edit-search-reviewer-filter').val('Search Reviewers');
		$('#edit-search-institute-filter').val('Search Institute');
		// hide drop down list
		$('.dropdown-cck-list').hide();
  });

  $(' #edit-searchText, #edit-searchText-right').blur(function() {
		if($(this).val() == '' ) {
			$(this).val('Enter the topic and find');
			return false;
		}
		else {
			return true;
		}
  });
	// Popup up search box in username
	$('#edit-username-search-text').blur(function(){
		if($(this).val() == '') {
				$(this).val('Search User');
				return false;
			} else {
				return true;
			}
  });

	//Affiliated Recommend functionality.
	$('li.affiliated-recommend a').click(affiliated_recommend);

	//when click the Recommend Close icon
	$('.google-search .assign-form-block .close').click(function(){
		$('.assign-form-block').remove();
	});
	// search box search icon click event it execute this function
	$('.search-submit-link img').click(search_submit);

}
 function federated_paging() {
    var bpath = Drupal.settings.basePath;
    var keyword = $('#keywords').val();
    var startid = $('#startid').val();
    var limit= $('#limit').val();
    var from= $('#fromid').val();
    var to= $('#toid').val();
    var total= $('#total').val();
    var start=1;
    if(($(this).attr("title"))==">>"){
			start=parseInt(from)+parseInt(limit);
    }
    else {
			start=parseInt(from)-parseInt(limit);
    }
    Drupal.attachBehaviors('.affiliate-google');
    $.ajax ({
      type: 'POST',
      data: {keyword:keyword, startid:start,limit:limit,from:from,to:to,total:total},
      url: bpath+'google_xmlresults',
      global: true,
      success: function (content) {
        if(content) {
          $('.affiliate-google').html(eval(content));
          Drupal.attachBehaviors('.affiliate-google');
        }
      }
    });
    return false;
  }
/**
 *
 * It submit the search form
 */
function search_submit(e) {
	if (($('.header-right .search-type #edit-searchText').length > 0  && $('input[id="edit-searchText"]').val() != '' &&  $('input[id="edit-searchText"]').val() != 'Enter the topic and find' &&  jQuery.trim($('input[id="edit-searchText"]').val()) != '') && ($('#edit-username-search-text').length == 0 )) {
		$('#getSolrSearchform').submit();
	}
	else if ($('#edit-username-search-text').length > 0 && $('input[id="edit-username-search-text"]').val() != '' &&  $('input[id="edit-username-search-text"]').val() != 'Search User' &&  jQuery.trim($('input[id="edit-username-search-text"]').val()) != '' ) {
		clickSearch(e);
	}
}

//Show affiliated recommend form.
function affiliated_recommend(e){
	e.preventDefault();
	var rec_Subject = $(this).parents('div.links').siblings('.result-right-inner').find('a').text();
	var rec_desc = $(this).parents('div.links').siblings('p').text();
  var rec_Link = $(this).parents('div.links').siblings('div.external-link').find('a').text();
	//Recommended by User name. @see in eb_search.module
	var rec_User = Drupal.settings.search_recommend.user_name;
	rec_Message = rec_Link + "\n\nRecommend by,\n" + rec_User;

	$('.art-actions-block').hide();
	var target = $(this).parents('div.aff-result');

  //Check whether the current affiliated result having the Recommend form.
	if($(this).parents('div.aff-result').next('.assign-form-block').length == 1){
		$('.results .assign-form-block').remove();
	}
	else{
	  //Check whether all other affiliated result having the Recommend form.
		if($('.results .assign-form-block').length == 1){
		  $('.results .assign-form-block').remove();
		}
		//Adding Recommend form for corresponding Affiliated search result.
		Drupal.attachBehaviors($(show).insertAfter(target));
		//Remove the Original Recommend form. Because it will affect Auto complete functionality.
		$('.affiliated-recommend-form').remove();
		//
		reset_User();
		//Remove the default User browse icon, and attach it explicitly
		$('.user-search-img').remove();
		var user_Browse = $('<div class="user-search-img" style="display:block"><a class="popups user-search-img-link" href="/popupsearch/recommend" title=""><img height="23" width="27" title="Browse" alt="Browse" src="/sites/all/themes/educationhub/images/browse-button.png"></a></div>').insertAfter('#edit-rec-recipient-wrapper');
		Drupal.attachBehaviors(user_Browse);
		//Remove the default Group browse icon, and attach it explicitly
		$('.group-search-img').remove();
		var group_Browse = $('<div class="group-search-img" style="display:none"><a title="Community Browse " class="popups group-search-img-link" href="/group/recommendation"><img height="22" width="27" title="Browse" alt="Browse" src="/sites/all/themes/educationhub/images/browse-button.png"></a></div>').insertAfter('#edit-rec-groups-wrapper');
		Drupal.attachBehaviors(group_Browse);
	}

	//Assign Recommend Subject, Recommend Message.
	$('.rec-detail #edit-rec-subject').val(rec_Subject);
	$('.rec-detail #edit-rec-body').val(rec_Message);

	//Assign hidden values.
	$('#edit-rec-node-type').attr('value', 'federated');
	$('#edit-rec-asset').attr('value', rec_Link);
	$('#edit-rec-link-title').attr('value', rec_Subject);
	$('#edit-rec-link').attr('value', rec_Link);
	$('#edit-rec-link-desc').attr('value', rec_desc);
  //Display the Recommend form.
	$('.results .assign-form-block').css("display", "block");
}

function cckfilter_list(e) {
	e.preventDefault();
	$('.dropdown-cck-list').toggle();
	return false;
}


//Function which is used to hide the Drop down if it was visibled in Assignment list page.
function clickAllhide_ccklist(){
	// If visible it will hide the selectbox-(group) drop down.
  if($(".dropdown-cck-list").is(':visible')) {
		$(".dropdown-cck-list").hide();
  }
}

//Reset the User field when we show the recommend form.
function reset_User(){
	$('.seleted-option').text('Users');
	// Will hide the groups drop down box, show the receipients text field in Recommend form.
	$('#edit-rec-groups-wrapper').attr('style','display:none');
	$('.group-search-img').attr('style','display:none');
	$('.rec-groups').attr('style','display:none');
	$('#edit-rec-recipient-wrapper').attr('style','display:block');
	$('.user-search-img').attr('style','display:block');

	//Hide the Users, Community Labels.
	$('#edit-rec-recipient-wrapper label,	#edit-rec-groups-wrapper label').hide();
}
