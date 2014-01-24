Drupal.behaviors.comment_location = function() {
 //When we click the review tab we need to Hide the Comment form and show the review form.
  $('.comment-review-tabs li.comment-tab').click(function(e){
    e.preventDefault();
    $(this).addClass('active');
    $('.box').show();
    $('#comments').show();
    $('.review-box').hide();
    $('#reviews').hide();
    $('.review-tab').removeClass('active');
		//Remove Error class and Error message in Review form
    $('.review-box #edit-body').removeClass('error');
		$('.review-box label.error').remove();

    if($('.review-box #node-form #edit-body').val() != 'Write a review..'){
      $('.review-box #node-form #edit-body').val('Write a review..');
    }
  });
  $('.comment-review-tabs li.review-tab').click(function(e){
    e.preventDefault();
    $(this).addClass('active');
    $('.review-box').show();
    $('#reviews').show();
    $('.box').hide();
    $('#comments').hide();
		$('.comment-tab').removeClass('active');
		//Remove Error class and Error message in Comment form
    $('#comment-form #edit-comment').removeClass('error');
		$('#comment-form label.error').remove();

		if($('#comment-form #edit-comment').val() != 'Write a comment..'){
      $('#comment-form #edit-comment').val('Write a comment..');
    }
  });

  //When click the Comment or Review body field we need to remove the default text.
  $('#comment-form #edit-comment').click(function(){
    if($(this).val() == 'Write a comment..'){
      $(this).val('');
    }
  });
  $('.review-box #node-form #edit-body').click(function(){
    if($(this).val() == 'Write a review..'){
      $(this).val('');
    }
  });
  //When click the outside of Comment or Review body field we need to set the default text.
  $('#comment-form #edit-comment').blur(function(){
    if($(this).val() == ''){
      $(this).val('Write a comment..');
    }
  });
  $('.review-box #node-form #edit-body').blur(function(){
    if($(this).val() == ''){
      $(this).val('Write a review..');
    }
  });

  //Set Cookie for Comment, Review tab's
  $('.review-box .form-submit').click(function(){
    //Set Reviews body field as empty
		if($('.review-box #edit-body').val() == 'Write a review..'){
      $('.review-box #edit-body').val('');
		}
    createCookie('review', 1, 5);
  });

  $('#comment-form .form-submit').click(function(){
    //Set comment body field as empty
		if($('#comment-form #edit-comment').val() == 'Write a comment..'){
      $('#comment-form #edit-comment').val('');
		}
		createCookie('review', 0);
  });

	//$('.review-edit-link').click(inlineReviewEdit);
}


//function inlineReviewEdit(e){
//	e.preventDefault();
//  reviewContent = $(this).parents('div.links').siblings('div.content').text();
//  editReviewForm = '<div class="edit-review-form" id="edit-review-form" ><input type="text" value="'+ reviewContent +'" name="inline_review_content" id="inline_review_content" style="width: 100%; border: none; background: none;"/></div>';
//	submittedBy = $(this).parents('div.links').siblings('.submitted');
//	$(editReviewForm).insertAfter(submittedBy);
//	$(this).parents('div.links').siblings('div.content').hide();
//	$(this).remove();
//}

$(document).ready(function() {
	//Hide reviews label.
	$('.review-box #edit-body-wrapper label').hide();
  if(readCookie('review') == 1){
    $('ul.comment-review-tabs li.review-tab, ul.comment-review-tabs li.review-tab a').addClass('active');
    $('ul.comment-review-tabs li.comment-tab, ul.comment-review-tabs li.comment-tab a').removeClass('active');
    //By default we need to hide the Reviews form.
    $('.box').hide();
    $('#comments').hide();
    $('.review-box').show();
    $('#reviews').show();
  }
  else{
    $('ul.comment-review-tabs li.review-tab, ul.comment-review-tabs li.review-tab a').removeClass('active');
    $('ul.comment-review-tabs li.comment-tab, ul.comment-review-tabs li.comment-tab a').addClass('active');
    //By default we need to hide the Reviews form.
    $('.box').show();
    $('#comments').show();
    $('.review-box').hide();
    $('#reviews').hide();
  }
});


/**
 * Javascript function to create a cookie.
 */
function createCookie(name, value, sec) {
	if (sec) {
		var date = new Date();
		date.setTime(date.getTime()+(sec*1000));
		var expires = "; expires="+date.toGMTString();
	}
	else {
		var expires = "";
	}
	document.cookie = name+"="+value+expires+";path=/";
}


/**
 * Javascript function to read a cookie value.
 */
function readCookie(name) {
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++) {
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
	}
	return null;
}

/**
 * Javascript function to delete a cookie value.
 */
function eraseCookie(name) {
	createCookie(name,"",-1);
}
