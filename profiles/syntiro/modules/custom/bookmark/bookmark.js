// $Id$
function bClick(){
  curLink = $(this);
  // Perform the ajax request
  $.ajax({
    type: "POST",
    url: curLink.attr('href'),
    
    data: {
      'ajaxed' : true
    },
    dataType: "json",
    beforeSend: function() {
      curLink.parent().find('span').remove();
      curLink.after('<span id="tempDisplay1"><img src="'+ Drupal.settings.bookmark.loadingImg +'"/></span>').hide();
    },
    success: function (data) {
      curLink.parent().find('span').remove();
      if(data.status == "added" || data.status == "removed") {
        // Title name also change
        curLink.attr('title', data.title);
        if(data.status == "removed") {
          curLink.attr('href', Drupal.settings.basePath + data.href).html(data.link_text).before('<span id="tempDisplay-remove"><span class="bookmark-tooltip"> '+ data.message +'</span></span>').show();
        }
        else {
          curLink.attr('href', Drupal.settings.basePath + data.href).html(data.link_text).before('<span id="tempDisplay"><span class="bookmark-tooltip"> '+ data.message +'</span></span>').show();
        }
      }
      else {
        curLink.before('<span id="tempDisplay"><span class="bookmark-tooltip"> '+ data.message +'</span></span>').show();
      }
      setTimeout(closeTempDisplay, 2000);
    },
    error: function (xmlhttp) {
      curLink.parent().find('span').remove();
      curLink.after('<span id="tempDisplay"><span class="bookmark-tooltip"> Error occured.</span></span>').show();
    }
  });
  return false;
}

function closeTempDisplay() {
  if ($('#tempDisplay').length > 0) {
    $('#tempDisplay').animate({
      'opacity': 0
    },
    {
      duration: 1000,
      complete: function() {
        $(this).remove();
      }
    });
  }
  if ($('#tempDisplay-remove').length > 0) {
    $('#tempDisplay-remove').animate({
      'opacity': 0
    },
    {
      duration: 1000,
      complete: function() {
        $(this).remove();
      }
    });
  }
}

//This binds the ajax calls to the Bookmark/Remove bookmark links
//Function separately written because other attachBehaviors (in other js files) attach behaviors in this fucntion
//If separately wriiten - behavior binding problem will not occur
Drupal.behaviors.bookmark = function(context) {
  $('a.ajaxified:not(.bm-processed)').addClass('.bm-processed').click(bClick);
  $('a.ajaxified2:not(.bm-processed2)').addClass('.bm-processed2').click(bClick);
  $('a.ajaxified3:not(.bm-processed3)').addClass('.bm-processed3').click(bClick);
  $('#remove-confirmation-form  #edit-submit').click(bmdelete);
};
function bmdelete(e) {
  e.preventDefault();
  del_nid = $('#edit-bid').attr('value');
  // It is used to check if quiz content delete
  base_path = Drupal.settings.bookmark.basepath;
  $.ajax({
    url: base_path + '/bookmark/remove/' + del_nid,
    type: "POST",
    success: function(data) {
      location.href = base_path + '/bridge/mybookmarks?del_title=success' ;
      // Closes the popup
      Popups.close();
    }
  });
}
//This is for the mybookmarks page
//making the type changing action into ajax
//function written separately to prevent ajax
Drupal.behaviors.bmType = function(context) {
  $('ul#bm-type a').click(bmTypeChange);
}

//Bookmark type change ajax call
function bmTypeChange() {
  thisLink = $(this);
  thisUrl = this.href;
  target = $("#bm-result-area");

  $.ajax({
    url: thisUrl,
    type: "GET",
    beforeSend: function() {
      target.html("Loading...");
    },
    success: function(data) {
      target.html($(data).find("#bm-result-area").html());
      Drupal.attachBehaviors("#bm-result-area");

      //reset all link's active class and add active class to the current link
      $('ul#bm-type li').removeClass("active");
      thisLink.parent('span').parent().addClass("active");
    }
  });
  return false;
}

//This is for mybookmarks page - making the pager in ajax format
Drupal.behaviors.bmPager = function(context) {
  $('#bm-pager ul.pager li a').click(bPager);
}
function bPager() {
  thisLink = $(this);
  thisUrl = this.href;
  target = $("#bm-result-area");
//get the contents after ? and make the correct call back for block ajax pager
  params = thisUrl.substring(thisUrl.indexOf('?'));
  targetUrl = Drupal.settings.bookmark.basepath + "/bookmarks/listing/" + params;
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
      Drupal.attachBehaviors("#bm-result-area");
      $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
    }
  });
  return false;
}