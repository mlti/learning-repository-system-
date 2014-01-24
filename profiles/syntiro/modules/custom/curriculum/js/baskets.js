// $Id$
//Variable to define Playlist Published or not.
var playlist_Publish = '';
$(document).ready(function(){
    $("#sidebar-right div.block").each(activateToggle);

    //show the first block
    $("#sidebar-right div.block:first div.title-exp-coll").html("[-]");
    $("#sidebar-right div.block:first div.content").show();

    $('.title-exp-coll').click(activateToggle);

    //While page reloading we need to uncheck the Select all check box in playlist edit page
    $('.curriculum-overall #check-all-0-wrapper #check-all-0').removeAttr('checked');

    if(!$('.curriculum-topic .topics').length){
        $('.curriculum-overall #check-all-0-wrapper #check-all-0').attr("disabled","disabled");
    }

    //By default we need to hide the Assignment Active Icon and Assignment form.
    $('.curriculum-assignment-form, .assign-more-form').hide();

    playlist_Publish = Drupal.settings.published;

    if(!playlist_Publish){
        $('.assign-inactive').hide();
        $('.assign-unpublished').show();
    }
});

function activateToggle() {
    $(this).find("div.content").hide();
    $(this).find("div.title-exp-coll").html("[+]").css('cursor','pointer').click(showHide);
}

function showHide() {
    $(this).parent().next().slideToggle();
    $(this).html(($(this).html() == "[+]")?"[-]":"[+]");
}

//displaying an message after a particular element
//before displaying remove all the previous messages
function displaymsgAfter(element, message) {
  //remove the message box if already exist
  if($(".custom_message").length > 0) {
    $(".custom_message").remove();
  }

  //display the message and close after a particular time interval
  $('<div class="custom_message">').html(message).insertAfter(element.parent());
  setTimeout(closemsg, 3000);
}
function displaymsgBefore(element, message) {
  //remove the message box if already exist
  if($(".custom_message").length > 0) {
    $(".custom_message").remove();
  }

  //display the message and close after a particular time interval
  $('<div class="custom_message">').html(message).insertBefore(element.parent());
  setTimeout(closemsg, 3000);
}
function displaymsgInside(element, message) {
  //remove the message box if already exist
  if($(".custom_message").length > 0) {
    $(".custom_message").remove();
  }

  //display the message and close after a particular time interval
  $('<div class="custom_message">').html(message).prependTo(element.parent());
  setTimeout(closemsg, 3000);
}

function closemsg() {
  $(".custom_message").hide('normal',
                            function() {
                              $(this).remove();
                            });
}

Drupal.behaviors.curriculumBasket = function(context) {
  // publish and unpublish hide and show in playlist drag and drop page
  if($('.node-type-curriculum .topic-single-content').length > 0) {
    $('.unpublish-link').hide();
    $('.publish-link').show();
  }
  else if ($('.node-type-curriculum .topic-single-content').length < 0) {
    $('.publish-link').hide();
    $('.unpublish-link').show();
  }
  //only activate droppable if there is the draggable basket available in the right side
  if($(".bm-links, .rec-links, .search-links, .mars-links, .asset-links").length > 0) {

    //making the topic contents area droppable elements
    $('.topic_content, .subtopic-drop, .empty-subtopic').droppable({
      accept: ".bm-draggable, .rec-draggable, .search-draggable, .mars-draggable, .asset-draggable",
      hoverClass: "ui-state-active",
      over: function(event, ui) {
        //console.log($(this).attr('class'));
        if($(this).hasClass('.subtopic-drop-playlist')) {
            $(this).find('.topic-list').toggle();
            $(this).find('.title-exp-coll').removeClass('title-collapse');
            $(this).find('.title-exp-coll').addClass('active title-expand');
        }
      },
      out: function(event, ui) {
        if($(this).hasClass('.subtopic-drop-playlist')) {
            $(this).find('.topic-list').toggle();
            $(this).find('.title-exp-coll').removeClass('active title-expand');
            $(this).find('.title-exp-coll').addClass('title-collapse');
        }
      },
      drop: function(ev, ui) {
        ev.preventDefault();

        //find the dragging dropping elements
        draggingDiv = $(".ui-draggable-dragging");
        draggingDiv.attr("content_type");
        if(draggingDiv.attr("content_type") == 'curriculum') {
            alert("You can't add playlist as sub topics.");
            return false;
        }
        var ti = draggingDiv.attr("content_title");
        if(draggingDiv.attr("content_type") == 'quiz') {
          ti = 'Clone ' + ti;
        }
      	var basket = "false";
        droppingDiv = $(this);

        if($(this).is('.subtopic-drop')){
          basket="true";
          // for the palylist block -> define explicitly that the droppable is with in the ul
          // & not below the topic title
          if ($(this).children('ul').is('ul')) {
            droppingDiv = $(this).children('ul');
          }
          topic_id = $(this).attr("topic_id");
          curriculum_id = $(this).attr('nid');
        } else if($(this).is('.empty-subtopic')){
            topic_id = $(this).next().attr("topic_id");
            droppingDiv = $(this).next();
            curriculum_id = Drupal.settings.curriculum.curriculum_id;
        } else if($(this).is('.subtopic-drop-playlist')){
          topic_id = $(this).find('.subtopic-drop').attr('topic_id');
          curriculum_id = $(this).find('.subtopic-drop').attr('nid');
        } else {
          //droppingDiv = $(this).parent();
          topic_id = $(this).attr("topic_id");
          curriculum_id =Drupal.settings.curriculum.curriculum_id;
        }
        //Define the call back to insert data into DB and initiate ajax call

        params = "?mode=add&topic_id=" + topic_id + "&asset=" + draggingDiv.attr("content_asset") + "&type=" + draggingDiv.attr("content_type") + "&title=" + ti + "&desc=" + draggingDiv.attr("content_desc") + "&class_type=" + draggingDiv.attr("class_type") + "&cid=" + curriculum_id + "&basket=" + basket;
        targetUrl = Drupal.settings.bookmark.basepath + "/curriculum/add_edit_content" + params;
        $.ajax({
          url: targetUrl,
          type: "POST",
          dataType: "json",
          data: {
            'ajaxed': true
          },
          success: function(data) {
            if(data.status == "ok" && data.mode == "add") {
              newContent = data.content_div;
              droppingDiv.append(newContent);
              displaymsgInside(droppingDiv, data.message);

              //and add behavior to enable remove process
              Drupal.attachBehaviors(newContent);
            }
            else if(data.status == "exist" && data.mode == "add") {
              displaymsgInside(droppingDiv, data.message);
            }
            else if(data.status == "exist" && data.mode == "not_published") {
              displaymsgInside(droppingDiv, data.message);
            }
            if($(this).is('.empty-subtopic') || $(this).is('.topic_content')) {
                $('.unpublish-link').hide();
                $('.publish-link').show();
            }
          }
        });
        //Hide the draggable element after dropping
        draggingDiv.fadeOut();
      }
    });
    }

    //Click the Close button of Assignment form
    $('.close').click(function(e){
        e.preventDefault();
        assign_form_hide();
    });

    //Click the Assignment Icon
    $('.assign-active').click(function(){
        assign_form_show();
        subjectSelected();
    });

    //Click the Assign Later Icon
    $('.assign-form-active').click(function(){
        assign_form_hide();
    });
//    $( ".topic-inline-add" ).click(function() {
//      params = "?mode=addtopics";
//      contentUrl = Drupal.settings.bookmark.basepath + "/curriculum/add_edit_content" + params;
//      $.ajax({
//          url: contentUrl,
//          type: "POST",
//          dataType: "json",
//          data: {
//            'ajaxed': true
//	  },
//	success: function(data) {
//            if(data.status == "ok" && data.mode == "addtopics") {
//	    }
//	},
//          });
//    });
    //Click the Select all check box in Palylist page.
    $('.curriculum-overall #check-all-0-wrapper #check-all-0').click(function(){
        if($(this).attr('checked')){
          $('.form-checkbox').attr('checked','checked');
          //Check whether Playlist are published or not.
          if(!playlist_Publish){
            $('.delete-disable, .assign-active, .assign-inactive, .assign-form-active, .topic-active').hide();
            $('.delete-active, .assign-unpublished, .topic-inactive').show();
        }
        else{
            $('.delete-disable, .assign-inactive, .topic-active').hide();
            $('.delete-active, .assign-active, .topic-inactive').show();
          }
          subjectSelected();
        }
        else{
          assign_form_hide();
        }
        //While we click Select all check box we need to show initial stage of the form.
        if($('.curriculum-assignment-form').css('display') == 'block'){
            $('.assign-active, .assign-inactive, .assign-unpublished, .delete-active, .delete-inactive, .topic-active').hide();
            $('.assign-form-active, .delete-form-active, .topic-inactive').show();
        }
    });

    //When we click the Sub topic check box do Select All Check box functionality.
    $('.curriculum-topic .form-checkbox').click(function(){
        if($('.curriculum-topic .form-checkbox:checked').length){
          subjectSelected();
          if(!playlist_Publish){
            $('.delete-disable, .assign-active, .assign-inactive, .assign-form-active, .topic-active').hide();
            $('.delete-active, .assign-unpublished, .topic-inactive').show();
        }
        else{
            $('.delete-disable, .assign-inactive, .topic-active').hide();
            $('.delete-active, .assign-active, .topic-inactive').show();
          }
        }
        else{
          assign_form_hide();
        }
        //While we click Subtopics check box we need to show initial stage of the form.
        if($('.curriculum-assignment-form').css('display') == 'block'){
            $('.assign-active, .assign-inactive, .assign-unpublished, .delete-active, .delete-inactive, .topic-active').hide();
            $('.assign-form-active, .delete-form-active, .topic-inactive').show();
        }
        //Check whether all sub topics are checked or not.
        if($('.curriculum-topic .form-checkbox:checked').length  == $('.curriculum-topic .form-checkbox').length){
          $('#check-all-0').attr('checked', true);
        }
        else{
          $('#check-all-0').attr('checked', false);
        }
    });

    var thisUrl;
    
    $('#delete-content-confirm-form #edit-yes-submit').click(function(e){
        e.preventDefault();
        selectedAlltopics = '';
        selectedSubtopics = '';
        if($('.curriculum-overall #check-all-0-wrapper #check-all-0').attr('checked')){
            $('.curriculum-topic .topics').each(function(){
              var selectTopic = $(this).attr('topic_id');
              if(selectedAlltopics == ''){
                selectedAlltopics += selectTopic;
              }
              else{
                selectedAlltopics += ',' + selectTopic;
              }
            });
        }
        else{
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
        
        base_path = Drupal.settings.bookmark.basepath;
        if(selectedSubtopics){
            $.ajax({
              type: "POST",
              data: {ids:selectedSubtopics},
              url: base_path + '/curriculum/ajax/delete/' + selectedSubtopics,
              success: function(data) {
                location.reload();
                Popups.close();
              }
            });
        }
        else if(selectedAlltopics){
            $.ajax({
              type: "POST",
              data: {topic_ids:selectedAlltopics},
              url: base_path + '/curriculum/ajax/delete/' + selectedAlltopics,
              success: function(data) {
		
                location.reload();
                Popups.close();
              }
            });
        }
    });
    
    //reorder the curriculum topics
    $( '#reorder-curriculum-topics-confirm-form #edit-yes-submit').click(function(e) {
	e.preventDefault();
        selectedAlltopicsId = '';
        selectedSubtopicsId = '';
	selectedAlltopicsWeight = '';
        selectedSubtopicsWeight = '';
	selectedAllSubtopicsId = '';
	selectedSubTopicsId = '';
	
	if($('.curriculum-overall #check-all-0-wrapper #check-all-0').attr('checked')){
            $('.curriculum-topic .topics').each(function(){
	      //topic id, sub topic id, weight
              var selectTopicId = $(this).attr('topic_id');
	      $('.curriculum-topic .form-checkbox:checked').each(function(){
	      var AllSubTopicsId = $(this).parent().next().val();
	      var selectedTopicsWeight = $('#weight-'+ AllSubTopicsId ).val();
	       var selectTopicId = $('#select_topic_'+ AllSubTopicsId + ' option:selected').val();
	        if(selectedAlltopicsId == ''){
                selectedAlltopicsId += selectTopicId;
		selectedAllSubtopicsId += AllSubTopicsId;
	        selectedAlltopicsWeight += selectedTopicsWeight; 

              }
              else{
                selectedAlltopicsId += ',' + selectTopicId;
		selectedAllSubtopicsId += ',' + AllSubTopicsId;
		selectedAlltopicsWeight += ',' + selectedTopicsWeight;
              }
	      });
            });
        }
        else {
            $('.curriculum-topic .form-checkbox:checked').each(function(index){		
	      var selectSubtopic = $(this).parent().next().val();		
	      var selectTopicId = $(this).closest('form').find('input').eq(2).val();		
	      var selectedTopicsWeight = $('#weight-'+ selectSubtopic ).val();	      
	      var selectTopicId = $('#select_topic_'+ selectSubtopic + ' option:selected').val();
	      if(selectedSubtopicsId == ''){
                selectedAlltopicsId += selectTopicId;
		selectedSubtopicsId += selectSubtopic;
	        selectedAlltopicsWeight += selectedTopicsWeight; 
              }
              else{
                selectedAlltopicsId += ',' + selectTopicId;
		selectedSubtopicsId += ',' + selectSubtopic;
		selectedAlltopicsWeight += ',' + selectedTopicsWeight;
              }
            });  
	}
	
	base_path = Drupal.settings.bookmark.basepath;
	if(selectedSubtopicsId){
           $.ajax({
              type: "POST",
              data: {subtopicid : selectedSubtopicsId, weight  : selectedAlltopicsWeight},
              url: base_path + '/curriculum/ajax/update/curriculum/subtopicid/' + selectedSubtopicsId + '/weight/' + selectedAlltopicsWeight + '/topicid/' + selectedAlltopicsId,
              success: function(data) {
		$('input[type=checkbox]').attr('checked',false);
                location.reload();
                Popups.close();
              }
            });
        }
        else if(selectedAlltopicsId){
            $.ajax({
              type: "POST",
              data: {topicid : selectedAlltopicsId, subtopicid : selectedAllSubtopicsId, weight  : selectedAlltopicsWeight },
            url: base_path + '/curriculum/ajax/update/curriculum/subtopicid/' + selectedAllSubtopicsId +'/weight/' + selectedAlltopicsWeight  + '/topicid/' + selectedAlltopicsId,
              success: function(data) {
		//$("#curriculum-select-all-form-3")[0].reset();
		$('input[type=checkbox]').attr('checked',false);
                location.reload();
                Popups.close();
              }
            });
        }     
	
    });    
    //Click Assign more Button
    $('.compose-assign').click(function(e){
        e.preventDefault();
        $('.compose-assign').hide();
        $('.assign-more-form').show();
    });
		// For playlist basket active playlist highlight has been enabled
		$(".node-" + Drupal.settings.curriculum.curriculum_id).removeClass("exp-coll-playlist").addClass("topic-title-readonly");
		$(".node-" + Drupal.settings.curriculum.curriculum_id).parent().addClass("active");
		$(".topic-title-readonly").next().click(function(e) {
				e.preventDefault();
		});
}

function subjectSelected(){
    var subjectSubtopics = '';
    $('.curriculum-topic .form-checkbox:checked').each(function(){
        //var subjectSubtopic = $(this).parents('.sub-topics').siblings('.topic_content span h3').text();
        var subjectSubtopic = $(this).parents('.assign-edit-icons').find('h3').text();
        if(subjectSubtopics == ''){
            subjectSubtopics += subjectSubtopic;
        }
        else{
            subjectSubtopics += ', ' + subjectSubtopic;
        }
        $('.curriculum-assignment-form span.assign-heading').text('Topics Selected: ' + subjectSubtopics);
    });
}

function assign_form_show(){
    //Show Assignment form.
    $('.curriculum-assignment-form').show();
   //Check whether Playlist are published or not.
   if(!playlist_Publish){
        //Show Assign later icon, Delete Disable with No tool tip
        $('.assign-unpublished, .delete-form-active, .topic-inactive').show();
        //Hide Assign now icon, Delete now icon
        $('.assign-active, .assign-inactive, .assign-form-active, .delete-active, .delete-disable, .topic-active').hide();
    }
    else{
        //Show Assign later icon, Delete Disable with No tool tip
        $('.assign-form-active, .delete-form-active, .topic-inactive').show();
        //Hide Assign now icon, Delete now icon
        $('.assign-active, .assign-inactive, .delete-active, .delete-disable, .topic-active').hide();
    }
}

function assign_form_hide(){
   //Hide Assignment form
   $('.curriculum-assignment-form, .assign-more-form').hide();
   //Show assign more Icon
   $('.compose-assign').show();
   assignment_form_clearance();
   //Un check all Check box
   $('.form-checkbox').attr('checked', false);
   //Check whether Playlist are published or not.
   if(!playlist_Publish){
    //Show Assign later icon, Delete Disable with No tool tip
    $('.assign-unpublished, .delete-disable, .topic-active').show();
    //Hide Assign now icon, Delete now icon
    $('.assign-active, .assign-inactive, .assign-form-active, .delete-active, .delete-form-active, .topic-inactive').hide();
   }
   else{
    //Show Assign later icon, Delete Disable with No tool tip
    $('.assign-inactive, .delete-disable, .topic-active').show();
    //Hide Assign now icon, Delete now icon
    $('.assign-active, .assign-form-active, .delete-active, .delete-form-active, .topic-inactive').hide();
   }

}

function assignment_form_clearance(){
   //We need to clear the Selection on Assignment form hide
   $('#assignment-form #edit-assign-body').val('Please drop your instructions here..');
   $('#assignment-form .recommend-to-input span.auto-to').remove();
   //Set Assignment type as Users.
   $('.assignment-options .selected-dropdown .seleted-option').text('Users');
   //Hide Groups field
   $('.rec-groups').hide();
   //Show Users field
   $('#edit-assign-recipient-wrapper, .user-search-img').show();
   if(!($('.add-more').length)){
     $('<a class="add-more" href="javascript:" title="Add More Members">+ Add more</a>').insertBefore('#edit-assign-recipient');
   }
   //Remove Error classes, Error Messages
   $('#edit-assign-recipient-wrapper').removeClass('edit-assign-recipient-error');
   $('#edit-assign-groups-wrapper').removeClass('edit-assign-groups-error');
   $('#edit-assign-body').removeClass('error');
   $('label.error').remove();
}