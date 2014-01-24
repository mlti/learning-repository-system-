Drupal.behaviors.assignment_report = function (context) {

    // to work with group list on report level 1 & 2 - Group List
    $(".assignment-group-list .group-list-one").click(clickSelect);
    $(".assignment-group-list .custom-selectboxes-replaced-list li").click(clickSelectedItem);

    // to work with status list on report level 2 - Status List
    $(".assignment-group-list .status-list-one .seleted-option").click(clickStatusSelect);
    $(".assignment-group-list .custom-status-replaced-list li").click(clickSelectedItem);

    /// to work with status list on report level 2 - Topic List
    $(".assignment-group-list .topic-list-one .seleted-option").click(clickTopicSelect);
    $(".assignment-group-list .custom-topic-replaced-list li").click(clickSelectedItem);

    $('.assignment-topic-list ul.pager li a').click(topiclistPager);
    $('.assignment-topic-list .tableHeader-processed th a').click(topiclistPager);

   // $('#username-form #edit-report-users').keyup(usernameAuto);
   $("#edit-report-users").keyup(function () {
     clickSelectedItem();
   })
   $('#assignment-block-form ul.pager li a').click(assignmentPager);
   $('#assign-result-area ul.pager li a').click(assignmentPager);
    // to hide the dropdown
    $('body').click(clickSelectAll);
  // for assignment report listing page pager   
  $('.assignment-report-listing .subtopic-total-count ul.pager li a').click(assingment_report_list_Pager);
}

function assignmentPager(e) {
  e.preventDefault();
  thisLink = $(this);
  thisUrl = this.href;
  params = thisUrl.substring(thisUrl.indexOf('?'));
  if ($(this).parent().parent().parent().parent().is('#assignment-block-content')) {
  //  target = $("#assignment-block-form");
    target = $("#assignment-block-content");
    target_attach = "#assignment-block-form";
    targetUrl = Drupal.settings.bookmark.basepath + "/assignment/block" + params;
    flag = 0;
  }
  else {
    target = $("#assign-result-area");
    target_attach = "#assign-result-area";
    flag = 1;
    // for assignment completed tab pager should change the callback
    if (Drupal.settings.assignment_completed_pager == true) {
      targetUrl = Drupal.settings.bookmark.basepath + "/assignment/listing/completed" + params;
    }
    else {
   
      targetUrl = Drupal.settings.bookmark.basepath + "/assignment/listing" + params;
    }
  }

  $.ajax({
    url: targetUrl,
    type: "GET",
    beforeSend: function() {
      //target.html("Loading...");
      $('<img src="'+ Drupal.settings.curriculum.loadingImg +'"/>').insertAfter(thisLink);
    },
    success: function(data) {
      // for replace or html purpose we created flag variable
      if (flag == 1) {
        target.replaceWith(data);
      }
      else {
        target.html(data);
      }
      Drupal.attachBehaviors(target_attach);
      $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
    }
  });
  return false;
}
//function usernameAuto() {
//  var path = window.location.href;
//
//  var explode1 = path.split("/");
//  // getting the nodes ID
//  var explode2 = explode1[5].split("?");
//  // getting the sub topic's ID
//  if(explode1[6]) {
//    var explode3 = explode1[6].split("?");
//  }
// thisUrl =  Drupal.settings.bookmark.basepath+"/assignment/report-users-autocomplete/"+ explode2[0]+"/"+ explode3+"/" + $("#edit-report-users").val() + "?st_id=" + $(".topic-list").attr('id') + "&status_id=" + $(".status-list").attr('id')+ "&gid=" + $(".selectbox-list").attr('id')+ "&uname=" + $("#edit-report-users").val();
//    target = $(".username-list");
//    $.ajax({
//      url: thisUrl,
//      type: "GET",
//      success: function(data) {
//        //target.html($(data).find(".assign-report-left").html());
//        console.log(data);
//        target.html($(data).find(".assignment-topic-list .assignment-topic .sticky-enabled tbody").html());
//        //Drupal.attachBehaviors(".assignment-topic-list .report-level-two");
//      }
//    });
//}

/**
 * Cookie Handling Functions
 */
//function eduCreateCookie(name,value,days) {
//  if (days) {
//    var date = new Date();
//    date.setTime(date.getTime()+(days*24*60*60*1000));
//    var expires = "; expires="+date.toGMTString();
//  }
//  else {
//    var expires = "";
//  }
//  document.cookie = name+"="+value+expires+"; path=/";
//}
//
//function eduReadCookie(name) {
//  var nameEQ = name + "=";
//  var ca = document.cookie.split(';');
//  for(var i=0;i < ca.length;i++) {
//    var c = ca[i];
//    while (c.charAt(0)==' ') c = c.substring(1,c.length);
//    if (c.indexOf(nameEQ) == 0) {
//      return c.substring(nameEQ.length,c.length);
//    }
//  }
//  return null;
//}
//
//function eduEraseCookie(name) {
//  createCookie(name,"",-1);
//}

// This function is used to hide the drop down.
function clickSelectAll() {

  // If visible it will hide the selectbox-(group) drop down.
  if($(".custom-selectboxes-replaced-list").is(':visible')) {
     $(".custom-selectboxes-replaced-list").hide();
  }
  // If visible it will hide the status drop down.
  if($(".custom-status-replaced-list").is(':visible')) {
     $(".custom-status-replaced-list").hide();
  }
  // If visible it will hide the topic drop down.
  if($(".custom-topic-replaced-list").is(':visible')) {
     $(".custom-topic-replaced-list").hide();
  }
}
// When we click this function it will hide all the other dropdowns and show only the GROUP.
function clickSelect() {
   // When the group box is selected the others (topic & status - drop down) will hide
  $(".custom-selectboxes-replaced-list").toggle();
  $(".custom-status-replaced-list").hide();
  $(".custom-topic-replaced-list").hide();
  return false;
}
// When we click this function it will hide all the other dropdowns and show only the STATUS.
function clickStatusSelect() {
  // When the status box is selected the others (groups & topic - drop down) will hide
 // alert($(".custom-status-replaced-list").live.css("display"));
  if ($(".custom-status-replaced-list").css("display") == 'none') {
    $(".custom-status-replaced-list").show();
  }
  else {
    $(".custom-status-replaced-list").hide();
  }
  //alert($(".custom-status-replaced-list").css("display"));
  //$(".custom-status-replaced-list").toggle();
  
  $(".custom-selectboxes-replaced-list").hide();
  $(".custom-topic-replaced-list").hide();

  return false;
}
// When we click this function it will hide all the other dropdowns and show only the TOPIC.
function clickTopicSelect() {
  // When the topic box is selected the others (status & topic - drop down) will hide
  $(".custom-topic-replaced-list").toggle();
  $(".custom-status-replaced-list").hide();
  $(".custom-selectboxes-replaced-list").hide();

  return false;
}

// When we click this function it will hide all the other dropdowns and show only the TOPIC.
function clickSelectedItem() {

  var $ul = $(this).closest('ul'); // finding the closest ul.
  var curr_ul_class = ($ul.attr('class')); // ul class
  var curr_div_class = ($ul.prev().attr('class')); // div class
  // it will get the value when clicking on the auto complete textbox.
  if($("#edit-report-users").val() == "Enter assignee's name to find") {
   // making the value empty if it is default value.
   var uname = '';
  } else if($("#edit-report-users").val() != "Enter assignee's name to find") {
   // replacing the value it is not the default value.
   var uname = $("#edit-report-users").val();
  }

  if(curr_ul_class == 'custom-selectboxes-replaced-list' || curr_div_class == 'selectbox-list') {
   // Replacing the curr_div_class value in to selectbox-list
    $(".selectbox-list").html($(this).html());
    // Appending an id the selectbox-list for ajax purpose. (Doing this we can easily get the ID and pass it)
    $(".selectbox-list").attr('id', $(this).attr('value'));
    //Hiding the div after the user selects the value.
    $(".custom-selectboxes-replaced-list").toggle();
  } else if (curr_ul_class == 'custom-status-replaced-list' || curr_div_class == 'status-list') {
    // Replacing the curr_div_class value in to status-list
    $(".status-list").html($(this).html());
    // Appending an id the status-list for ajax purpose. (Doing this we can easily get the ID and pass it)
    $(".status-list").attr('id', $(this).attr('value'));
    //Hiding the div after the user selects the value.
    $(".custom-status-replaced-list").toggle();
  } else if (curr_ul_class == 'custom-topic-replaced-list' || curr_div_class == 'topic-list-selected') {
    // Replacing the curr_div_class value in to topic-list
    $(".topic-list-selected").html($(this).html());
    // Appending an id the topic-list for ajax purpose. (Doing this we can easily get the ID and pass it)
    $(".topic-list-selected").attr('id', $(this).attr('value'));
    //Hiding the div after the user selects the value.
    $(".custom-topic-replaced-list").toggle();
  }

  var path = window.location.href;

  var explode1 = path.split("/");
  // getting the nodes ID
  var explode2 = explode1[5].split("?");
  // getting the sub topic's ID
  if(explode1[6]) {
    var explode3 = explode1[6].split("?");
  }

  if(!explode3) {
      thisUrl =  Drupal.settings.bookmark.basepath+"/assignment/reports/"+ explode2[0] +"?group_id=" + $(this).attr("value");
    target = $(".assignment-reports-level1");
    $.ajax({
      url: thisUrl,
      type: "GET",
      success: function(data) {
        target.html($(data).find(".assignment-reports-level1").html());
        Drupal.attachBehaviors(".assignment-reports-level1");
      }
    });
  } else {

    // Appending the values in the url and making changes in the query. - assignment_reports.inc : function assignment_report_level2($cid, $topic_id, $uid, $status = 0, $gid = 0, $uname = NULL);
    // @param : explode2[0] -> node_id
    // @param : explode3 -> sub topic id (Which is from URL)
    // @param : st_id -> sub topic id (Which is from clicking the dropdown)
    // @param : status_id -> Assignment Status -> Pending or Completed
    // @param : gid -> Group ID
    // @param : uname -> Search by using users First Name and Last Name

    thisUrl =  Drupal.settings.bookmark.basepath+"/assignment/reports/"+ explode2[0]+"/"+ explode3+"?st_id=" + $(".topic-list-selected").attr('id') + "&status_id=" + $(".status-list").attr('id')+ "&gid=" + $(".selectbox-list").attr('id')+ "&uname=" + uname;

    target = $(".assignment-topic-list");
    $.ajax({
      url: thisUrl,
      type: "GET",
      success: function(data) {
        //target.html($(data).find(".assign-report-left").html());
        //target.html($(data).find(".assignment-topic-list .assignment-topic .sticky-enabled tbody").html());
        //Drupal.attachBehaviors(".assign-report-left");

        target.html($(data).find(".assignment-topic-list").html());
        // added below line to add class for the table.
        $('.sticky-enabled').eq(0).children('thead').addClass('tableHeader-processed');
        //Drupal.attachBehaviors(".assignment-topic-list");
      }
    });
  }
  return false;
}

 // Filter Results Paginations
function topiclistPager() {
  thisLink = $(this);
  thisUrl = this.href;
  target = $(".assignment-topic-list");
   $.ajax({
    url: thisUrl,
    type: "GET",
    success: function(data) {
      target.html($(data).find(".assignment-topic-list").html());
      Drupal.attachBehaviors(".assignment-topic-list");
    }
  });
  return false;
}
/**
 * for assignment report listing page pagers
 *
 */
function assingment_report_list_Pager() {
  thisLink = $(this);
  thisUrl = this.href;
  target = $(".assignment-report-listing");
  params = thisUrl.substring(thisUrl.indexOf('?'));
  targetUrl = Drupal.settings.bookmark.basepath + "/assignment/reports/ajax/list" + params;
  $.ajax({
    url: targetUrl,
    type: "GET",
    beforeSend: function() {
      //target.html("Loading...");
      $('<img src="'+ Drupal.settings.bookmark.loadingImg +'"/>').insertAfter(thisLink);
    },
    success: function(data) {
      target.html($(data).find(".assignment-report-listing-table").html());
      Drupal.attachBehaviors(".assignment-report-listing-table");
      $('html, body').animate({scrollTop:$('.main-content').offset().top}, 1000);
    }
  });
  return false;
}
