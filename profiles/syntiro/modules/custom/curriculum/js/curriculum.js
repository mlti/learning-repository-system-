// $Id$
Drupal.behaviors.curriculum = function() {

   $('#edit-no-submit').click(function() {
    Popups.close();
    return false;
   });

}

Drupal.behaviors.bmBlockDragDrop = function() {
  //only activate droppable if there is the draggable basket available in the right side
  if($(".bm-links, .rec-links, .search-links, .mars-links, .asset-links").length > 0) {
		//making the topic contents sortable
    $('.topic_content').sortable({
      //connectWith: ['.topic_content'],
      handle: '.handle',
      connectWith: ".topic_content",
      update: function(ev, ui){
        topicContainer = $(this);
        order = $(this).sortable('serialize');
        topic_id = $(this).attr('topic_id');
        params = "?mode=order&topic_id=" + topic_id + "&" + order;
        targetUrl = Drupal.settings.bookmark.basepath + "/curriculum/add_edit_content" + params;
        $.ajax({
            url: targetUrl,
            type: "POST",
            dataType: "json",
            data: { "ajaxed": true },
            success: function(data) {
              if(data.status == "ok" && data.mode == "order") {
                displaymsgInside(topicContainer, data.message);
              }
            }
        })
      }
    });
  }
//Open close topic
//$('.open-close-topics').click(opencloseTopics);
$('.open-close-topics-playlist').click(opencloseTopicsPlaylist);
}


function win_open(address) {
	window.open(address,'','width=700,height=500');

}

function opencloseTopics() {
	$(this).parent().next().next().toggle();
	$(this).parent().next().next().next().toggle();
	if ($(this).children().attr('class') == 'open-close-title-collapse') {
		Drupal.attachBehaviors($(this).children().removeClass('open-close-title-collapse'));
		Drupal.attachBehaviors($(this).children().addClass('open-close-title-expand'));
		Drupal.attachBehaviors($(this).parent().parent().parent().removeClass('topic-title-line'));
	}
	else {
		Drupal.attachBehaviors($(this).children().removeClass('open-close-title-expand'));
		Drupal.attachBehaviors($(this).children().addClass('open-close-title-collapse'));
		Drupal.attachBehaviors($(this).parent().parent().parent().addClass('topic-title-line'));
	}
}

function opencloseTopicsPlaylist() {
	$(this).parent().next().next().toggle();
	$(this).parent().next().next().next().toggle();
	if ($(this).children().attr('class') == 'open-close-title-collapse') {
		Drupal.attachBehaviors($(this).children('span').removeClass('open-close-title-collapse'));
		Drupal.attachBehaviors($(this).children('span').addClass('open-close-title-expand'));
		Drupal.attachBehaviors($(this).parent().parent().parent().removeClass('topic-title-line'));
	}
	else {
		Drupal.attachBehaviors($(this).children('span').removeClass('open-close-title-expand'));
		Drupal.attachBehaviors($(this).children('span').addClass('open-close-title-collapse'));
		Drupal.attachBehaviors($(this).parent().parent().parent().addClass('topic-title-line'));
	}
}

//[START] Editing the topics inline
Drupal.behaviors.topicsEdit = function() {
  $('.topic-inline-edit').click(editInline);
	$('.topic-inline-edit2').click(editInline);
	$('#inline_topic_name').blur(submitTopicEdit);
}
function editInline(e) {
  e.preventDefault();
  //if there is already an edit in progree cancell all
  if($('#editTopicForm').length)
    cancelAllEdit();

  //identify the elements
	//find the edit link (a) - coz the topic also can be clicked to edit
	if ($(this).attr('class') == 'topic-inline-edit') {
	  editLink = $(this);
	}
	else if ($(this).attr('class') == 'topic-inline-edit2') {
	  editLink = $(this).next().children('a:first');
	}
  linkSpan = editLink.parent();
	topicParent = linkSpan.parent();
	topicBox = topicParent.parent();
  topicSpan = topicParent.find('span:first');
	curUrl = editLink.attr('href');
  //Hide the current topic and link
  linkSpan.hide();
  topicSpan.hide();
	//hide the sort and delete link
	topicBox.find('.topic-right').hide();
	topicParent.addClass('topics-left-active');

  temp_var = topicSpan.text();
  
  if(temp_var == '<No Title>') {
   temp_var = '';
  }

  //create new edit elements and display them
  topic = temp_var.replace(/\"/g, "&#34;");
  editForm = '<div class="editTopicForm" id="editTopicForm" ><input type="text" value="'+ topic +'" name="inline_topic_name" id="inline_topic_name" style="width: 100%; border: none; background: none;" maxlength=25/></div>';
  topicParent.append(editForm);
  Drupal.attachBehaviors(editForm);
	// click more than one topic immediately then we need unbind those and bind again
	$('.topic-inline-edit2').unbind('click');
	$('.topic-inline-edit').unbind('click');
	//trigger blur event on $('#inline_topic_name')
	$('#inline_topic_name').focus();
}

//Update the topic with the new value
function submitTopicEdit() {
  newTopic = $(this).val();
  targetUrl = curUrl + "?topic=" + newTopic;
  $.ajax({
    url: targetUrl,
    type: "POST",
    dataType: "json",
    data: {"ajaxed": true, "mode": "edit"},
    beforeSend: function() {
      $("#editTopicForm input").hide();
      $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').appendTo('#editTopicForm');
    },
    success: function(data)
    {
      //topic count - no of topics in current node
      var topicCount = data.topic_count;
      //get alltopics id's, subtopics id's through json data object
      $.each(data.topics, function(index, topics) {
	var topics_id = data.topicid;
	var subtopic_id = topics.subtopic;
      for(var i =0; i<subtopic_id.length; i++)
      {
      var selectTopcis = '';
      var subtopic_topic = subtopic_id[i].split('-');
      selectTopcis += '<select id="select_topic_'+subtopic_topic[0]+'" class="form-select selecttopic" name="select_topic_'+subtopic_topic[0]+'">';
      for(var j=1; j <= topicCount; j++){
	if (topics_id[j] == subtopic_topic[1]) {
	  selectTopcis += '<option value="'+topics_id[j]+'" selected="selected">'+[j]+'</option>';
	}
	else{
	  selectTopcis += '<option value="'+topics_id[j]+'">'+[j]+'</option>';
	}     
      }
      selectTopcis += '</select>';
      $("#select_topic_"+subtopic_topic[0]).replaceWith(selectTopcis);
      }
      });
    topicSpan.text(data.new_topic);
    if (newTopic) {
	    drop_box = 'Drop the assets here from Bridge baskets to ' + data.new_topic;
    }
    else {
	    drop_box = 'Drop the assets here from Bridge baskets to &lt;No Title&gt;';
    }
    if (topicBox.next().next().children().length == 0) {
	    if (topicBox.next().parent().children().is('.empty-subtopic')) {
		    topicBox.next().parent().find('.empty-subtopic').replaceWith('<div class="empty-subtopic ui-droppable">'+ drop_box + '</div>');
	    }
	    else {
		    topicBox.next().parent().find('.topic_content').before('<div class="empty-subtopic ui-droppable">' + drop_box + '</div>');
	    }
	    Drupal.attachBehaviors(topicBox);
    }
    else {
	    $(data).find('.title-wrapper h2').html();
	    topicBox.next().parent().find('.empty-subtopic').html('<div class="empty-subtopic ui-droppable">'+ drop_box + '</div>');
	    Drupal.attachBehaviors(topicBox);
    }
    // click more than one topic immediately then we need unbind those and bind again
    $('.topic-inline-edit2').bind('click', editInline);
    $('.topic-inline-edit').bind('click', editInline);
      cancelAllEdit();
    },
    error: function() {
      alert("Error Occured!");
      cancelAllEdit();
    }
  });
}


//handle the keypress events of the new text field
function watchKeys(e) {
	if(e.which == "0") {
		cancelAllEdit();
	}
	else if(e.which == "13") {
		submitTopicEdit();
	}
}

//if any edit is alredy triggered cancel all of them
function cancelAllEdit() {
  $('#editTopicForm').remove();
  $('.topic-left span').show();
	$('.topic-right').show();
	topicParent.removeClass('topics-left-active');

}
//[END] Editing the topics inline


//[START] Add new topic ajax
Drupal.behaviors.topicAdd = function() {
  $('.topic-inline-add').click(addInline);
}
function addInline(e) {
	e.preventDefault();
	addLink = $(this);
  curUrl = this.href;

	$.ajax({
		url: curUrl,
		type: 'POST',
		dataType: 'json',
		data: {'ajaxed': true, 'mode': 'add'},
		beforeSend: function() {
			addLink.hide();
			$('<img src="'+ Drupal.settings.bookmark.loadingImg +'" />').appendTo(addLink.parent());
		},
		success: function(data) {
			topicBox = $(data.topic_box);
			//check - if this is the first topic then overwrite the previous display message
			if($('.curriculum-topic .topics').length < 1) {
				$('.curriculum-topic').html(topicBox);
			}
			else {
				$('.curriculum-topic').append(topicBox);
			}

			Drupal.attachBehaviors(topicBox);
			displaymsgInside(topicBox.children(), data.message);

			//activate inline topic edit
			$(topicBox).find('a.topic-inline-edit').trigger('click');

			addLink.next('img').remove();
			addLink.show();
			baseurl = Drupal.settings.bookmark.basepath;
		},
		error: function() {
			addLink.next('img').remove();
			addLink.show();
			alert("Error Occured!");
		}
	});
}
//[END] Add new topic inline


//[START] Editing the description inline
Drupal.behaviors.descEdit = function() {
  $('.topic-inline-edit-desc').click(descEditInline);
	$('#inline_desc_name').blur(submitDescEdit);
}

function descEditInline(e) {
   // to prevent traversing to other page.
   e.preventDefault();
   temp_var = $('.topic-inline-edit-desc p').text();
   description =temp_var.replace(/\"/g, "&#34;");
   //create new edit elements and display them
   editForm = '<div class="editDescForm" id="editDescForm" ><textarea rows="2" cols="20" name="inline_desc_name" id="inline_desc_name" style="width: 100%; border: none; background: none;" >'+ description +'</textarea></div>'

   // Hiding the current div to show the edit panel.
   $('.topic-inline-edit-desc p, .topic-inline-edit-desc a').hide();

   // inserting the edit panel after the display panel.
   $(editForm).insertAfter('.topic-inline-edit-desc');

   // Adding the class to differntiate the edit and display panel.
   $('#editDescForm').addClass('topics-left-active');

   // In this case we attaching the behaviours to editForm. Else DOM will not consider the new element which we generate. So the functions will not work on editForm.
   Drupal.attachBehaviors(editForm);

   // Once clicking the display panel the cursor should focus on edit panel.
   $('#inline_desc_name').focus();
}

//Update the description with the new value
function submitDescEdit() {
  // assingning the new value to newDesc variable.
  newDesc = $('#inline_desc_name').val();

  // splitting the url to get the curriculum ID.
  pathName = window.location.pathname.split('/');
	nid = Drupal.settings.curriculum.curriculum_id;
	//if no change - cancel the process and do nothing in ajax
	if($('.topic-inline-edit-desc p').html() == newDesc) {
   cancelDescEdit();
   return false;
	}
  //Path which is send to ajax call back. Which is located in curriculum module.
  targetUrl =  Drupal.settings.basePath+"curriculum/"+nid+"/add_edit_desc/"+$('.topic-inline-edit-desc p').html()+ "?nid="+nid+"&descr=" + newDesc;

  // Ajax starts here
  $.ajax({
    url: targetUrl,
    type: "POST",
    dataType: "json",
    data: {"ajaxed": true, "mode": "edit"},
    beforeSend: function() {
      // hiding the edit panel before sending to ajax callback.
			$("#editDescForm input").hide();
      // Loading image will be load until the ajax process is done.
      $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').appendTo('#editDescForm');
    },
    success: function(data) {
      // >> (data.new_desc) : in this case we will get the updated value which will be assigned to the current element. (which is returned from curriculum.inc in json format)
			$('.topic-inline-edit-desc p').text(data.new_desc);
      cancelDescEdit();
    },
    error: function() {
      alert("Error Occured!");
      cancelDescEdit();
    }
  });
  // Ajax ends here.
}



//if any edit is alredy triggered cancel all of them
function cancelDescEdit() {
  // Removing the edit form
  $('#editDescForm').remove();
  // show the display form
  $('.topic-inline-edit-desc p, .topic-inline-edit-desc a').show();
}

//[END] Editing the description inline
