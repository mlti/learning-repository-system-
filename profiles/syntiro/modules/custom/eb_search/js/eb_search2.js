

//Search results and ajax pagination
  //Ajax call on clicking find
function clickFind() {
    var rr = $('#search-box-block-search-results').html('');
    searchtext =  $('#edit-searchText-right').val();
    searchtype = 'filters=type:asset';
        $.ajax({
        type: 'POST',
        url: Drupal.settings.basePath+'mysearch/results/'+searchtext+'?'+searchtype+'&solrsort=ps_score_content desc',
        global: true,
        success: function (content) {
            $('#search-box-block-search-results').html(content);
            Drupal.attachBehaviors('#search-box-block-search-results');
          }
        });
    }

    // Filter Results Paginations
    function search_result_pager() {
        thisLink = $(this);
        thisUrl = this.href;
        target = $("#search-box-block-search-results");
         $.ajax({
          url: thisUrl,
          type: "GET",
          beforeSend: function() {
            $('<img src="'+ Drupal.settings.bookmark.loadingImg +'" id="img_check"/>').insertAfter(thisLink);
          },
          success: function(data) {
              $('#search-box-block-search-results').html(data);
            Drupal.attachBehaviors("#search-box-block-search-results");
                        $('#img_check').remove();
          }
        });
        return false;
    }
Drupal.behaviors.searchblock = function (context) {
  // Search Results In Right Block
  // Get Apache Solr Results in Block
  $('#getSolrSearchform-right .edit-searchText-right').click(function() {
    if($('#getSolrSearchform-right #edit-searchText-right').val() == 'Enter the topic and find' || jQuery.trim($('#getSolrSearchform-right #edit-searchText-right').val()) == '' ) {
      return false;
    }
    else {
      clickFind();
    }
    return true;
  });

  if($("#getSolrSearchform-right").length > 0) {
    var user_Role = Drupal.settings.bookmark.roles;
    if(user_Role != 'student'){
        $("#search-box-block-search-results .search-links").addClass("search-draggable").draggable({
         cursor: 'move',
         helper: 'clone',
         revert: true,
         iframeFix: true,
         tolerance: "pointer",
         cursorAt: { left: 5 }
        });
    }
  }

  $('#getSolrSearchform-right input').keypress(function(event) {
    if (event.which == '13') {
      event.preventDefault();
    }
  });

  $('.search-basket-block ul.pager li a').click(search_result_pager);

};

// Left Category Searchs
Drupal.behaviors.searchcategroy = function (context) {

  // Paging for Search Result
  $('.google-bottom-pager ul.pager li a').click(google_pager);
  $('.dropdown-cck-list ul li a').click(filter_cck_type);

  $('.filter-title').click(filter_toggle);
  $('#filterbydate-form a').click(filter_date);
  // to get filter format 
  $('#filterbyformat-form input[id^="edit-filterbyformat-"]').change(filterbyFormat);


  $('#creativecommon-form #edit-filterbycreativecommon-Attribution-NoDerivatives').change(filterbycreative);
  $('#creativecommon-form #edit-filterbycreativecommon-Attribution-NonCommercial').change(filterbycreative);
  $('#creativecommon-form #edit-filterbycreativecommon-Attribution-NonCommercial-ShareAlike').change(filterbycreative);
  $('#creativecommon-form #edit-filterbycreativecommon-Attribution-NonCommercial-NoDerivatives').change(filterbycreative);

  $('.pager-common a').click(pager_source);
  $('.filter-content .source .source-list-bead-filter a').click(filterbysource);

};
// source by filter
function filterbysource(e) {
  e.preventDefault();
  base_path = Drupal.settings.bookmark.basepath;
  searchtext = $('#edit-searchText').attr('value');
  type = $(this).attr('type');
  target = $('.result');
  var typelist = '';
  // To remove bold selected filter in  search result
  $('#filterbydate-form a').removeClass('font-bold');
  $('.filter-content .source .source-list-bead-filter a').removeClass('font-bold');
  $(this).addClass('font-bold');
  $(".class_active").each(function(index){
    // check if the matched value is equal to selected value
    typelist = typelist + '&filtertype_' + $(this).attr('type') + '=' + $(this).attr('type');
  });
  // if select filter list available
  if (typelist) {
    thisUrl = base_path + '/ebsearch/results/' + searchtext + '?' +  typelist +'&tm_source=' + type;
  }
  else {
    thisUrl = base_path + '/ebsearch/results/' + searchtext + '?tm_source=' + type;
  }
  $.ajax({
    url: thisUrl,
    type: "GET",
    success: function(data) {
      target.html($(data).find(".result").html());
      $('.result-count').html($(data).find(".result-count").html());
      Drupal.attachBehaviors(".result-count");
      Drupal.attachBehaviors(".result");

    }
  });
  return false;

}
// Filter source pagination
function pager_source(e) {
  e.preventDefault();
  thisLink = $(this);
  thisUrl = this.href;
  target =   $('.source');
  $.ajax({
    url: thisUrl,
    type: "GET",
    success: function(data) {
      target.html($(data).find(".source").html());
      Drupal.attachBehaviors(".source");
    }
  });
  return false;
}
// filter format
function filterbyFormat(creative_comm) {
    base_path = Drupal.settings.bookmark.basepath;
    searchtext = $('#edit-searchText').attr('value');
    target = $('.result');
    var typelist = '';
    var format_val = '';
    // To remove bold selected filter in  search result
    $('#filterbydate-form a').removeClass('font-bold');
    $('.filter-content .source .source-list-bead-filter a').removeClass('font-bold');
    $("#filterbyformat-form :checked").each(function(index){
      format_val = format_val + '&format_' + $(this).val() + '=' + $(this).val();
    });
    $(".class_active").each(function(index){
      // check if the matched value is equal to selected value
      typelist = typelist + '&filtertype_' + $(this).attr('type') + '=' + $(this).attr('type');
    });
    // if select filter list available
    if (typelist) {
      thisUrl = base_path + '/ebsearch/results/' + searchtext + '?' +  typelist + format_val;
    }
    else {
      thisUrl = base_path + '/ebsearch/results/' + searchtext + '?'+format_val;
    }
    $.ajax({
      url: thisUrl,
      type: "GET",
      success: function(data) {
        target.html($(data).find(".result").html());
        Drupal.attachBehaviors(".result");
        $('.result-count').html($(data).find(".result-count").html());
        Drupal.attachBehaviors(".result-count");
      }
    });
  return false;
}
// filter creative common options
function filterbycreative() {
    base_path = Drupal.settings.bookmark.basepath;
    searchtext = $('#edit-searchText').attr('value');
    target = $('.result');
    var typelist = '';
    var format_val = '';
    // To remove bold selected filter in  search result
    $('#filterbydate-form a').removeClass('font-bold');
    $('.filter-content .source .source-list-bead-filter a').removeClass('font-bold');
    $("#creativecommon-form :checked").each(function(index){
      format_val = format_val + '&creative_' + $(this).val() + '=' + $(this).val();
    });
    $(".class_active").each(function(index){
      // check if the matched value is equal to selected value
      typelist = typelist + '&filtertype_' + $(this).attr('type') + '=' + $(this).attr('type');
    });
    // if select filter list available
    if (typelist) {
      thisUrl = base_path + '/ebsearch/results/' + searchtext + '?' +  typelist + format_val;
    }
    else {
      thisUrl = base_path + '/ebsearch/results/' + searchtext + '?'+format_val;
    }
    $.ajax({
      url: thisUrl,
      type: "GET",
      success: function(data) {
        target.html($(data).find(".result").html());
        Drupal.attachBehaviors(".result");
        $('.result-count').html($(data).find(".result-count").html());
        Drupal.attachBehaviors(".result-count");
      }
    });
  return false;
}
// filter options with search textfield will call this functions
// This function will call from eb_search.js
function clicksearchfilter(value, thisvalue) {
  base_path = Drupal.settings.bookmark.basepath;
  searchtext = $('#edit-searchText').attr('value');
  type = thisvalue;
  thisLink = $(this);
  target = $('.result');
  var typelist = '';
  // To remove bold selected filter in  search result
  $('#filterbydate-form a').removeClass('font-bold');
  $('.filter-content .source .source-list-bead-filter a').removeClass('font-bold');
  $(".class_active").each(function(index){
    // check if the matched value is equal to selected value
    typelist = typelist + '&filtertype_' + $(this).attr('type') + '=' + $(this).attr('type');
  });
  // if select filter list available
  if (typelist) {
    thisUrl = base_path + '/ebsearch/results/' + searchtext + '?' +  typelist +'&' + value + '=' + type;
  }
  else {
    thisUrl = base_path + '/ebsearch/results/' + searchtext + '?'+ value + '=' + type;
  }
  $.ajax({
    url: thisUrl,
    type: "GET",
    success: function(data) {
      target.html($(data).find(".result").html());
      Drupal.attachBehaviors(".result");
      $('.result-count').html($(data).find(".result-count").html());
      Drupal.attachBehaviors(".result-count");
    }
  });
  return false;
}
// filter date
function filter_date(e) {
  e.preventDefault();
  base_path = Drupal.settings.bookmark.basepath;
  searchtext = $('#edit-searchText').attr('value');
  type = $(this).attr('type');
  This = $(this);
  // To remove bold selected filter in  search result
  $('#filterbydate-form a').removeClass('font-bold');
  $('.filter-content .source .source-list-bead-filter a').removeClass('font-bold');
  // To add bold selected filter in search result
  $(this).addClass('font-bold');

  target = $('.result');
  var typelist = '';
  $(".class_active").each(function(index){
    // check if the matched value is equal to selected value
    typelist = typelist + '&filtertype_' + $(this).attr('type') + '=' + $(this).attr('type');
  });
  // if select filter list available
  if (typelist) {
    thisUrl = base_path + '/ebsearch/results/' + searchtext + '?' +  typelist +'&solrsort=created ' + type;
  }
  else {
    thisUrl = base_path + '/ebsearch/results/' + searchtext + '?&solrsort=created ' + type;
  }
  $.ajax({
    url: thisUrl,
    type: "GET",
    success: function(data) {
      target.html($(data).find(".result").html());
      Drupal.attachBehaviors(".result");
      $('.result-count').html($(data).find(".result-count").html());

      //This.css("font-weight","bold");
      Drupal.attachBehaviors(".result-count");
    }
  });
  return false;

}
// filters list toggle
function filter_toggle(){
  //$('.filter-content').hide();
  $('.filter-content').addClass("element-invisible");
  //$(this).next().toggle();
  
  if($(this).next().hasClass("element-invisible")) {
     $(this).next().removeClass("element-invisible");
  }
  else{
     $(this).next().addClass("element-invisible");
  }
  
  $('.filter-title').removeClass('active');
  $(this).addClass('active');
  $("#filterbyformat-form :checked").each(function(index){
    $(this).attr('checked', false);
  });
  $("#creativecommon-form :checked").each(function(index){
    $(this).attr('checked', false);
  });
}

//function click_
/**
 * filter cck types
 *
 */
function filter_cck_type(e) {
    e.preventDefault();
    thisLink = $(this);
    thisUrl = this.href;
    target = $('.result');
    target_block = $(".filter-rightside");
    type = this.type;
    // get base path
    base_path=Drupal.settings.bookmark.basepath;
    // search text
    searchtext = $('#edit-searchText').attr('value');
    // check if the class is available
    if (thisLink.is('.class_active')) {
      Drupal.attachBehaviors(thisLink.removeClass("class_active"));
    }
    else {
      Drupal.attachBehaviors(thisLink.addClass("class_active"));
    }
    var typelist = '';
    flag = 0;
    $(".class_active").each(function(){
      // check if the matched value is equal to selected value
       typelist = typelist + '&filtertype_' + $(this).attr('type') + '=' + $(this).attr('type');
    });
    // if select filter list available
    if (typelist) {
      thisUrl = base_path + '/ebsearch/results/' + searchtext + '?' +  typelist +'&solrsort=ps_score_content desc';
    }
    else {
      thisUrl =  base_path + '/ebsearch/results/' + searchtext + '?solrsort=ps_score_content desc';
    }
    $.ajax({
      url: thisUrl,
      type: "GET",
      success: function(data) {
        target.html($(data).find(".result").html());
        target_block.html($(data).find(".filter-rightside").html());
        Drupal.attachBehaviors(".filter-rightside");
        Drupal.attachBehaviors(".result");
        $('.result-count').html($(data).find(".result-count").html());
        Drupal.attachBehaviors(".result-count");
      }
    });
    return false;
}

// Filter Results Paginations
function google_pager() {
   thisLink = $(this);
    thisUrl = this.href;
    target = $(".result");
    Drupal.attachBehaviors(".result");
    $.ajax({
      url: thisUrl,
      type: "GET",
      beforeSend: function() {
        $('<img src="'+ Drupal.settings.bookmark.loadingImg +'" id="img_check"/>').insertAfter(thisLink);
      },
      success: function(data) {
        // This function is in preview-baser.js
        preview_close_pager();
        target.html($(data).find(".result").html());
        Drupal.attachBehaviors(".result");
        $('#img_check').remove();
      }
    });
    return false;
}
