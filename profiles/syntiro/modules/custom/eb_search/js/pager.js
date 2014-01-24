Drupal.behaviors.abdu = function(context){
  $('.item-list').find('li').each(function(){
    pager = $(this).find('a').attr('href');
    if(pager != undefined) {
      pagerv = pager.split('=');
      pager = pagerv[1];
      $(this).attr('class', 'mypager');
      $(this).attr('id', 'page-'+pager);
    } else {
      pager = 0;
    } 
  }); 

  $('li.mypager:not(.abdu-processed)', context).addClass('abdu-processed').click(function () {
    $(this).addClass('ajax-progress');
    ajaxLoad(this.id);
    return false;
  });
  function ajaxLoad(clickId){
    splitId = clickId.split("-");
    pager = splitId[1];
    var currentPathArr = jQuery.trim(Drupal.settings.currentPath).split('/');
    var init=0;
    var k=0;
    var newPathArr = new Array();
    for(; init<currentPathArr.length; init++) {
      if(jQuery.trim(currentPathArr[init])) {
        newPathArr[k] = jQuery.trim(currentPathArr[init]);
        k++;
      }
    }
    Drupal.settings.currentPath = newPathArr.join('/');
    $.ajax({
      type: "GET",
      url: Drupal.settings.basePath+"abdu/ajax",
      data: 'page='+pager+'&path='+Drupal.settings.currentPath,      
      success: function(msg){          
      msg = msg.replace(/abdu\/ajax/g, Drupal.settings.currentPath);
      $('#ajaxpager').html(msg);
      Drupal.attachBehaviors('#ajaxpager');
      $('form').attr('action', Drupal.settings.basePath+Drupal.settings.currentPath);
      },
      beforeSend: function(){
      },
      error: function(XMLHttpRequest, textStatus, errorThrown){
        alert(XMLHttpRequest.statusText);          
      }
    });   
    return true;
  }
}