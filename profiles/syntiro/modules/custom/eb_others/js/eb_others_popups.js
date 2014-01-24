Drupal.behaviors.eb_others_popups = function (context) {
	// For delete process in popups
  $('.popups-box #node-delete-confirm  #edit-submit').click(function(e){
    e.preventDefault();
    del_nid = $('#node-delete-confirm #edit-node-id').val();
    base_path = Drupal.settings.bookmark.basepath;
    redirect_path = $('#node-delete-confirm #edit-redirect-path').val();
    $.ajax({
      url: base_path+'/node/'+del_nid+'/delete/confirm',
      type: "POST",
      success: function(data) {
        location.href = base_path + '/' +redirect_path;
        Popups.close();
      }
    });
  });
	
	$("#publish-node-form  #edit-ok").click(node_publish);
  
  //While click the Plus button we need to show Input box for Playlist creation.
  $('.bridge-actions-block .bridge-actions .action-add').click(function(e){
    e.preventDefault();
    $('.no-playlists').hide();
    var insertTarget = $('.my-playlist-block ul.expand-coll-list-playlist li.playlist-content');
    var insertBox = '<div class="addPlayForm" id="addPlayForm" ><span class=""></span><input type="text" maxlength="40" value="Type Playlist Title..." name="inline_play_name" id="inline_play_name" style="background:#FFFFD9; border:none; padding:5px;"/></div>';
    if(!$('.addPlayForm').length){
      Drupal.attachBehaviors($(insertBox).insertBefore(insertTarget));
    }
  });
  //When we click the Playlist input field we need to null the content.
  $('#inline_play_name').click(function(){
    if($(this).val() == 'Type Playlist Title...'){
	    $(this).val('');
    }
  });
  //On blur we need to create Playlist ans a topic under the Playlist.
	$('#inline_play_name').blur(addPlaylist);

  //For Co Author Removal process in popup
  $('#coauthor-reviewer-remove-form .button-main #edit-yes-submit').click(function(e){
		e.preventDefault();
    del_nid = $('#coauthor-reviewer-remove-form #edit-node-id').val();
    user_uid = $('#coauthor-reviewer-remove-form #edit-user-id').val();
    base_path = Drupal.settings.bookmark.basepath;
    redirect_path = $('#coauthor-reviewer-remove-form #edit-redirect-path').val();
    $.ajax({
      url: base_path + '/node/' + del_nid + '/removed/' + user_uid,
      type: "POST",
      success: function(data) {
				location.href= base_path + '/' + redirect_path;
        Popups.close();
      }
    });
  });
  // For popup close only
  $('.popups-box #edit-cancel').click(function(e){
    e.preventDefault();
    Popups.close();
  });

  // for dynamic we need to add width for user name in heartbeat activity listing page
  $('#heartbeat-stream-privateheartbeat .popups').attr('on-popups-options','{width:"670px"}');


  // to hide preview button in compose and reply message page.
	var pathname = window.location.pathname;
	var arg = pathname.split("/");

	if(arg[1] == 'messages' && arg[2] == 'view') {
		$('.contact-icon').attr('style','display:none');
		$("label[for='edit-body']").hide();
		// to hide preview button in compose and reply message page.
		$('#edit-preview').attr('style','display:none');
	}
	if(arg[1] == 'messages' && arg[2] == 'new') {
		$('#edit-preview').attr('style','display:none');
	}
	// to hide comments text in discussion comment-list
	//$('label[for="edit-comment"]').hide();
	$('label[for="edit-comment"]').addClass("element-invisible");
	

}

$(document).ready(function(){
	//Header Users details dropdown action
	$('.account-arrow').click(function(){
		//$('.header-drop-down').toggle();
		if($('.header-drop-down').hasClass("element-invisible")) {
		   $('.account-arrow').addClass('account-active');
		   $('.header-drop-down').removeClass("element-invisible");
		}
		else{
		  $('.account-arrow').removeClass('account-active');
		  $('.header-drop-down').addClass("element-invisible");
		}
		return false;
	});

	$('body').click(function(){
		//$('.header-drop-down').hide();
		$('.header-drop-down').addClass("element-invisible");
		$('.account-arrow').removeClass('account-active');
	});

});

// It redirect to edit page
//function edit_link_common(e) {
//  e.preventDefault();
//  location.href = $('#node-edit-link').attr('value');
//}

function node_publish(e) {
	e.preventDefault();
	nid = $('#publish-node-form #edit-publish-node').val();
	base_path = Drupal.settings.bookmark.basepath;
	$.ajax({
		url: base_path+'/node/'+nid+'/publish/confirm',
		type: "POST",
		success: function(data) {
			location.reload();
			Popups.close();
		}
	});
}

function addPlaylist(){
	var newTopic = $('#inline_play_name').val();

	if(newTopic == 'Type Playlist Title...' || $.trim(newTopic) == ''){
		newTopic = 'Untitled';
	}

	base_path = Drupal.settings.bookmark.basepath;
	targetUrl = base_path + '/curriculum/quickadd_save';
	targetPlace = $('#curriculum-block-content ul.play-lists li.first');

	$.ajax({
    url: targetUrl,
    type: "POST",
    dataType: "json",
    data: {"ajaxed": true, "title": newTopic},
    beforeSend: function() {
			$("#addPlayForm").remove();
      $('<img class="loading" src="'+ Drupal.settings.bookmark.loadingImg +'"/>').insertBefore('.playlist-content');
    },
		success: function(data) {
			var addedContent = '<li><h4 class="title-exp-coll title-collapse"><span class="exp-coll"></span><a href="/node/' + data.nid + '">' + data.title + '</a></h4><ul><li topic_id="' + data.topic_id + '" class="subtopic-drop ui-droppable"><h5>' + data.topic_title + '</h5><ul class="asset-list"></ul></li></ul></li>';
      Drupal.attachBehaviors($(addedContent).insertAfter(targetPlace));
			$('img.loading').remove();
    }
	});

}
