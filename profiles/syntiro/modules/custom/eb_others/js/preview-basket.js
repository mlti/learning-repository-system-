// $Id$
//View preview on mouse over on baskets on overview edit page (asset and curriculum)
var xhr = null;

Drupal.behaviors.previewOverview = function(context) {
  $('.common-list-drop-preview').click(preview_close);
  $('.close-preview').live('click', preview_close);
  $( ".popup-playlist" ).click(select_curriculum);
  $('.view-content .more-icon #preview_icon a, .result .more-icon #preview_icon a, .topic_content .more-icon #preview_icon a, .topic-content-view .more-icon #preview_icon a, #bridge-preview #mars-block-content .mars-links #preview_icon a, #bridge-preview #bm-block-content .bm-links #preview_icon a, #bridge-preview #rec-block-content .rec-links #preview_icon a, #bridge-preview #asset-block-content .asset-links #preview_icon a, #bridge-preview #getSolrSearchform-right .search-links #preview_icon a').click(Previewsection);
  
  $('.view-content .more-icon a, .result .more-icon a, .topic_content .more-icon a, .topic-content-view .more-icon a, #bridge-preview #mars-block-content .mars-links a, #bridge-preview #bm-block-content .bm-links a, #bridge-preview #rec-block-content .rec-links a, #bridge-preview #asset-block-content .asset-links a, #bridge-preview #getSolrSearchform-right .search-links a').click(insertembed);
  
   $('.view-content .more-icon a, .result .more-icon a, .topic_content .more-icon a, .topic-content-view .more-icon a, #bridge-preview #mars-block-content .mars-links a, #bridge-preview #bm-block-content .bm-links a, #bridge-preview #rec-block-content .rec-links a, #bridge-preview #asset-block-content .asset-links a, #bridge-preview #getSolrSearchform-right .search-links a').click(insertplaylist);
}

function select_curriculum(e) {
  var cur_title = $(this).find("a").html();
  var content_type = $(this).attr('content_type');
  var curriculum_id = $(this).attr('curriculum_id');
  var class_type = $(this).attr('class_type');
  var content_asset = $(this).attr('content_asset');
  var content_desc = $(this).attr('desc');
  var content_title = $(this).attr('content_title');
  var topic_id = $(this).attr('topic_id');
  var curriculum_id = $(this).attr('curriculum_id');
  var title = $(this).attr('title');
  var droppingDiv = $(this).attr('droppingDiv');
  var basket = "false";
  $('#drop_options_playlist').remove();
  params = "?mode=add&topic_id=" + topic_id + "&asset=" + content_asset + "&type=" + content_type + "&title=" + title + "&desc=" + content_desc + "&class_type=" + class_type + "&cid=" + curriculum_id + "&basket=" + basket;
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
              var div = $('.topics');
              div.each(function(index) {
                var heading = $(this).find('.topic-inline-edit2').text();
                if(cur_title == heading) {
                  var droppingDiv = $(this).find('.topic_content');
                  newContent = data.content_div;
                  droppingDiv.append(newContent);
                  displaymsgInside(droppingDiv, data.message);
                  //and add behavior to enable remove process
                  Drupal.attachBehaviors(newContent);
                 return true;
                }
              });
             
            }
            else if(data.status == "exist" && data.mode == "add") {
               var div = $('.topics');
               div.each(function(index) {
                var heading = $(this).find('.topic-inline-edit2').text();
                if(cur_title == heading) {
                  var droppingDiv = $(this).find('.topic_content');
                  newContent = data.content_div;
                  displaymsgInside(droppingDiv, data.message);
                }
              });  
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
}

function insertplaylist(e) {
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
    if($('.topic_content, .subtopic-drop, .empty-subtopic').length > 0) {
     if($('.node-type-curriculum .topic-title-inline').length > 0) {
      var span = $('.topic-inline-edit2').html();
      var div = $('.topics');
      droppingOptions = '<div id="drop_options_playlist" tabindex="0">';
      var droppingDiv = $(this).parent().html().replace(/"/g, "\\'");
      var contentType = $(this).parent().attr('content_type').replace(/"/g, "\\'");
      var assetType = $(this).parent().attr('class_type').replace(/"/g, "\\'");
      var contentAsset = $(this).parent().attr('content_asset').replace(/"/g, "\\'");
      var content_desc = $(this).parent().attr('content_desc').replace(/"/g, "\\'");
      var content_title = $(this).parent().attr('content_title').replace(/"/g, "\\'");
      var basket = "false";
      //var replaced = droppingOptions.replace(/"/g, "\\'");
      div.each(function(index) {
       var id = $(this).attr('id');
       var topic_id = $(this).attr('topic_id');
       curriculum_id =Drupal.settings.curriculum.curriculum_id;
       var heading = $(this).find('.topic-inline-edit2').text();
       droppingOptions += '<div style="display: block; padding: 2px; cursor: pointer;" class="popup-playlist" id="' + id + '" topic_id="' + topic_id + '" curriculum_id="' + curriculum_id + '" content_asset="' + contentAsset + '" content_type="' + contentType + '"  droppingDiv="' + droppingDiv + '" title="' + content_title + '" desc="' + content_desc + '" basket="' + basket + '"  class_type="' + assetType + '"><a href="javascript:;" tabindex="0" id="' + heading + '">' + heading + '</a></div>';
       
      });
      droppingOptions += '</div>';
      return displayallheadings(droppingOptions);
     }
    }
  }  
}

function displayallheadings(droppingOptions) {
  
   $(droppingOptions).appendTo('body').css({'left': 600, 'top': 600}).slideDown();
          Drupal.attachBehaviors(droppingOptions);
          $(".popup-playlist a:first").focus();
          return false;
  
}

function insertembed(e) {
     if($('.node-type-curriculum .topic-title-inline').length == 0) {
      id = $(this).parent().attr('id');
        if(id != 'preview_icon') {
          alt_value = $(this).parent().html();
          contentType = $(this).parent().attr('content_type');
          assetType = $(this).parent().attr('class_type');
          contentAsset = $(this).parent().attr('content_asset');
          insertLink = '<br/><h3>' + alt_value.replace("Click to preview", "View Original Document") + '</h3><br/>';
          //check the content type - if it is asset show options - else insert link
         // remove_preview_icon = $(insertLink).find(".preview_icon").remove();
          return insert_link(alt_value, contentType, assetType, contentAsset, insertLink, 700, 500);
        }
    }
}


function insert_link(alt_value, contentType, assetType, contentAsset, insertLink, pageX, pageY) {
  
  if (contentType == "asset" || contentType == "bead" || contentType == "quiz") {
      //if this asset id is same as the editing asset id - can not process
      
        if (contentAsset == Drupal.settings.asset.thisAsset) {
          alert("Can not add same asset!");
          return false;
        }
        if (assetType == "asset-image" || assetType == "asset-html" || assetType == "quiz-nodoc" ||  assetType == "bead-html"  ||  assetType == "bead-image" ) {
           if (assetType == "asset-html" || assetType == "quiz-nodoc" || assetType == "bead-html") {
            htmlOption = "Embed Content";
          }
          else {
            htmlOption = "Embed Image";
          }
          $('#drop_options').remove();
          droppingOptions = $('<div id="drop_options" tabindex="0"><div id="insert-embed" style="display: block; padding: 2px; cursor: pointer;"><a href="javascript:;" tabindex="0" id="embed">' + htmlOption + '</a></div><div id="insert-link" style="display: block; padding: 2px; cursor: pointer;"><a href="javascript:;" tabindex="0" id="insertlink">Insert Link</a></div></div>');

          droppingOptions.appendTo('body').css({'left': pageX, 'top': pageY}).slideDown();
          Drupal.attachBehaviors(droppingOptions);
          $("#embed").focus();
          ddTimer = 0;
        }
        else {
          CKEDITOR.instances['edit-body'].insertHtml(insertLink);
          //save details for asset tracking after adding
          asset_tracking_call(contentAsset, Drupal.settings.asset.thisAsset);
        }
      }
      else {
        CKEDITOR.instances['edit-body'].insertHtml(insertLink);
      }
      return false;
}

function Previewsection(e) {
  e.preventDefault();
  // to add the class for preivew pages.
  if (xhr && xhr.readyState != 4) {
    //if previous ajax is working then cancel it
    xhr.abort();
  }
  // for success 
  flag = 0;
  // Check if it is playlist view page
  if($('.topic_content').length > 0 || ($('.topic-content-view').length > 0 && $('.node-type-curriculum').length > 0)) {
    flag = 1;
  }
  curLink = $(this);
  targetLink = this.href + '?status=ajax';
  //check if is called from basket
  var parent = $(this).parent();
  var parentParent = $(parent).parent();
  if (parentParent.is('.mars-links') || parentParent.is('.asset-links') || parentParent.is('.bm-links') || parentParent.is('.rec-links') || parentParent.is('.search-links')) {
    contentType = parentParent.attr('content_type');
    external_link_text = $(this).text();
  }
  else {
    external_link_text = $(this).attr('node_title');
    contentType = $(this).attr('nodetype');
  }
  if (contentType == 'asset' || contentType == 'curriculum' || contentType == 'bead' || contentType == 'discussion' || contentType == 'quiz') {
    targetLink  = this.href + '?status=ajax&preview=true';
    xhr = $.ajax({
      url: targetLink,
      beforeSend: function() {
        $('.preview-content').html('<img src="'+ Drupal.settings.eb_others.loadingImg +'"/>');
      },
      success: function(content) {
        // for Asset page user .node-preview class
        // class is in node-asset.tpl.php
        if($(content).find('.node-preview').html()!= 'null') {
          title = $(content).find('.title-wrapper h2').html();
          data = '<div class="preview-title clearfix"><div class="float-left similar-assets-title">' + title + '</div><div class="close-preview float-right" style=""><a href="javascript:;"><img src="'+ Drupal.settings.eb_others.close_image +'" title="Close"/></a></div></div>' + $(content).find('.node-preview').html();

        }
        else {
          data = 'There is no content in this Asset';
        }
        // this function is to add classes
        _preview_addclass(curLink, data, flag);
      },
      error: function(xmlhttp) {
        $('.preview-content').html('Error On Loading.');
      }
    });
    
  }
  else {  
    data = '<div class="preview-title"><h3 class="float-left">' + external_link_text + '</h3><div class="close-preview float-right" style=""><img src="'+ Drupal.settings.eb_others.close_image +'" title="Close" /></div></div>'+ '<iframe src="' + targetLink + '" width="100%" height="200px"></iframe>';
    _preview_addclass(curLink, data, flag);
  }
}
// For preview section in associated class
function _preview_addclass(curLink, data, flag) {
  // check if it is playlist view page
  if (flag == 1) {
    $('.curriculum-preview').show();
  }
  else {
    $('.common-list-wrapper').addClass("common-list-wrapper-clone")
  }
  // preview section bottom div
  $('.common-list-drop-preview').show();
  // Preview section div
  $(".preview-content").show();
  // close button on top right of the preview section
  $('.close-preview').show();
  //more-icon-readonly.png
  if (curLink.parent().parent().is("li")) {
    $('.more-icon a').parent().parent().removeClass('listing-teaser');
    curLink.parent().parent().addClass('listing-teaser');
  }
  else {
    $('.more-icon a').parent().parent().parent().removeClass('listing-teaser');
    curLink.parent().parent().parent().addClass('listing-teaser');
  }
  $('.preview-content').html(data);
  Drupal.attachBehaviors(".preview-content");
}
/**
 * For pager closing the preview section
 */
function preview_close_pager() {
  // preview section bottom div
  if ($('.common-list-drop-preview').length > 0) {
    $('.common-list-drop-preview').hide();
  }
  // Preview section div
  if ($(".preview-content").length > 0) {
    $(".preview-content").hide();
  }
  //  teaser listing class removal for grey color
  if ($('.listing-teaser').length > 0) {
    $('.listing-teaser').removeClass('listing-teaser');
  }
  // For line removal in preview section
  if ($('.common-list-wrapper-clone').length > 0) {
    $('.common-list-wrapper-clone').removeClass('common-list-wrapper-clone');
    
  }
  // close button on top right of the preview section
  if ($('.close-preview').length > 0) {
    $('.close-preview').hide();
  }
}
function preview_close(e) {
  e.preventDefault();
  // close button on top right of the preview section
  $('.close-preview').hide();
  //while closing remove the preivew class
  $('div').removeClass('common-list-wrapper-clone');
  $('.curriculum-preview').hide();

  // Preview section div
  $(".preview-content").hide();
  // preview section bottom div
  $('.common-list-drop-preview').hide();
  // content listing background color removed
  if ($('.more-icon a').parent().parent().is("li")) {
    $('.more-icon a').parent().parent().removeClass('listing-teaser');
  }
  else {
    $('.more-icon a').parent().parent().parent().removeClass('listing-teaser');
  }
   // For line removal in preview section
  if ($('.more-icon-readonly').length > 0) {
    $('.more-icon-readonly').removeClass('more-icon-readonly').addClass('more-icon');
  }
  $('.title-wrapper').show();
  $('.node-preview .titlespace, .common-list-wrapper .titlespace').hide();
}

