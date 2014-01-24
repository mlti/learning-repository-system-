// $Id$
//This is for assets content page -
Drupal.behaviors.assetDragDrop = function(context) {

  $(".body-field-wrapper").droppable({
    accept: '.bm-links, .rec-links, .mars-links, .search-links, .asset-links',
    drop: function(ev, ui) {
      
      //this is the current dragging element
      draggingDiv = $(".ui-draggable-dragging");

      //check the editor mode - if in source mode retrun
      //oEditor = CKEDITOR.currentInstance;
     // alert( CKEDITOR.instances.editor1.name );
      //console.log(CKEDITOR.instances['edit-body'].name);
      //FCKeditorAPI.GetInstance('edit-body');
     // if (oEditor.EditMode != FCK_EDITMODE_WYSIWYG) {
      //if (typeof(CKEDITOR.instances) != 'undefined' && typeof(CKEDITOR.instances['edit-body']) != 'undefined') {
      ////  alert("Change to HTML mode");
      //  alert("defined");
      //  return false;
      //} else {
      //     alert("undefined");
      //}

      //get the link and descrition from the dragging element
      alt_value = ui.draggable.html();
      insertLink = '<br/><h3>' + alt_value.replace("Click to preview", "View Original Document") + '</h3><br/>';
      contentType = ui.draggable.attr('content_type');
      assetType = ui.draggable.attr('class_type');
      contentAsset = ui.draggable.attr('content_asset');
      insert_link(alt_value, contentType, assetType, contentAsset, insertLink, ev.pageX, ev.pageY);
    }
  });

  $('#drop_options').hover(function(){
    cancelOptTimer();
  }, function(){
    strartOptClose();
  });

  $('#drop_options div').click(processOption);
}


//hiding the options
function cancelOptTimer() {
  if(ddTimer) {
    window.clearTimeout(ddTimer);
    ddTimer = null;
  }
}

function strartOptClose() {
  ddTimer = window.setTimeout(closeOptMenu, 2000);
}

function closeOptMenu() {
  $('#drop_options').slideUp();
}


function processOption() {
  selectedOption = $(this).attr('id');
    if(selectedOption == "insert-link") {
    CKEDITOR.instances['edit-body'].insertHtml(insertLink);
    //save details for asset tracking after adding
    asset_tracking_call(contentAsset, Drupal.settings.asset.thisAsset);
  }
  else if(selectedOption == "insert-embed") {
    targetUrl = Drupal.settings.bookmark.basepath + "/asset/edit/get-embed?asset=" + contentAsset;
    //alert(targetUrl);
    $.ajax({
      url: targetUrl,
      type: 'POST',
      data: {'ajaxed': true, mode: 'embed'},
      dataType: 'json',
      //beforeSend: function() {
      //},
      success: function(data) {
        if(data.body == "") {
          // If condition added to display the independent alert message for quiz. By Fero on July 16
          if(assetType == 'quiz-nodoc') {
            alert("Embed failed: There is no content in that Quiz.");
          }
          else {
            alert("Embed failed: There is no content in that Asset.");
          }
        }
        else {
          CKEDITOR.instances['edit-body'].insertHtml(data.body);
          //save details for asset tracking after adding
          asset_tracking_call(contentAsset, Drupal.settings.asset.thisAsset);
        }
      },
      error: function() {
        alert("Error Occured!");
      }
    });
  }
  closeOptMenu();
  
}

function asset_tracking_call(asset_id, parent_id) {
  trackingUrl = Drupal.settings.bookmark.basepath + "/asset/asset_tracking?asset_id=" + asset_id + "&parent_id=" + parent_id;
  $.ajax({
    url: trackingUrl,
    type: 'POST',
    data: {'ajaxed': true, mode: 'track'},
    dataType: 'json',
    success: function(data) {
      asset_tracking = data.status;
    }
  });
}
