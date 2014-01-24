Drupal.behaviors.asset = function(context) {
	 $('#asset-block-content ul.pager li a').click(assetBlockPager);

  var user_Role = Drupal.settings.bookmark.roles;
   if(user_Role != 'student'){
      $("#asset-block-content .asset-links").addClass("asset-draggable").draggable({
	cursor: 'move',
	helper: 'clone',
	revert: true,
	iframeFix: true,
	tolerance: "pointer",
	cursorAt: { left: 5 }
      });
   }
  // asset Edit section
  if ($("#node-edit-link").length > 0) {
     $('.access-edit .asset-edit-view').click(edit_link);
     $('.access-edit .title').click(edit_link);
     var str = ' <a class="edit-pen" href='+edit_link+'>Edit</a>';
     if ($(".access-edit .title").find('.edit-pen').length == 0) {
         $(".access-edit .title").append(str);
     }
     
   }
 

  //Multi choice edit section
  $('.ques-edit').click(edit_link);

  $('.asset-listing-move').hover(add_class_on_hover);
  $('.asset-listing-move').mouseleave(remove_class_on_leave);
  // Bead sequence move to specif title
  //$('.sidebar-beadtitle ul.bead-title-list li a').click(beadSequenceTitle);
  $(document).ready(function(){
    $('.sidebar-beadtitle ul.bead-title-list li').localScroll({
		   target:'#bead-result-sequence',
       hash:true,
	onAfter:function( anchor, settings ){
	  // The 'this' contains the scrolled element (#content)
	  beadSequenceTitle(anchor);
	  //return false;
	}
		});

    $.localScroll.hash({
      target: '#bead-result-sequence', // Could be a selector or a jQuery object to
      //queue:true,
      duration:1500
    });
  });


};

/**
 * Bead Sequence Travel to specific title
 */
function beadSequenceTitle(anchor_e) {
  scroll_id = '#'+anchor_e.id;
  scroll_id_chk = scroll_id.split('-');
  scroll_link_id = scroll_id_chk[1];
  // For Removing Gray shade
  $('#limit-scroll').find('.selected-author').removeClass('selected-author');
  // Adding Gray shade to selected title
  $(scroll_id).addClass('selected-author');
  // For Removing Gray shade
  $('.sidebar-beadtitle .bead-scroll').find('.active').removeClass('active');
  // Adding Gray shade to selected title
  $('#'+scroll_link_id+' a').addClass('active');
  $('.sidebar-beadtitle .bead-scroll').find('.bead-active').removeClass('bead-active');
  // Adding Gray shade to selected title
   $('#'+scroll_link_id).addClass('bead-active');
  //$('#bead-result-sequence').scrollTo(scroll_id);
  // Move to specific location in the same page itself
  //$("html, body").animate({scrollTop: $(scroll_id).offset().top},'slow');

}

/**
 * Bead Sequence Travel to specific title
 */
function beadSequenceTitle_bck(e) {
  e.preventDefault();
  scroll_id = '#title-' + $(this).parent().attr('id');
  // For Removing Gray shade
  $('#limit-scroll').find('.selected-author').removeClass('selected-author');
  // Adding Gray shade to selected title
  $(scroll_id).addClass('selected-author');
  // For Removing Gray shade
  $('.sidebar-beadtitle .bead-scroll').find('.active').removeClass('active');
  // Adding Gray shade to selected title
  $(this).addClass('active');
  $('.sidebar-beadtitle .bead-scroll').find('.bead-active').removeClass('bead-active');
  // Adding Gray shade to selected title
  $(this).parent().addClass('bead-active');
  //$('#bead-result-sequence').scrollTo(scroll_id);
  // Move to specific location in the same page itself
  //$("html, body").animate({scrollTop: $(scroll_id).offset().top},'slow');

}
function add_class_on_hover() {
   $(this).addClass('asset-list-to-move');
}
function remove_class_on_leave() {
  $(this).removeClass('asset-list-to-move');
}
// It redirect to edit page
function edit_link(e) {
   e.preventDefault();
  location.href = $('#node-edit-link').attr('value');
}
function assetBlockPager() {
	 thisLink = $(this);
	 thisUrl = this.href;
	 target = $("#asset-block-content");
         params = thisUrl.substring(thisUrl.indexOf('?'));
         targetUrl = Drupal.settings.bookmark.basepath + "/asset/block" + params;
	 $.ajax({
	  url: targetUrl,
	  type: "GET",
	  beforeSend: function() {
                  $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').insertAfter(thisLink);
	  },
	  success: function(data) {
		  target.html(data);
		  Drupal.attachBehaviors("#asset-block-content");
	  }
	 });
	 return false;
}

$("#edit-field-openforreview-value-1").click(function(){
  $("#field-reviewers-items").fadeToggle('slow');
});
