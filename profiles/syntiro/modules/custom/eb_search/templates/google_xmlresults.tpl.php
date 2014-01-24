<?php
//echopre ($results);
//exit;

 if(count($results['items']) <= 0): ?>
  <div style="" class="affiliate-partner">
    <div class="search-empty-result">
&nbsp;&nbsp;     <?php print check_plain($results['keywords']);?></b> - does not have any Results.
Please  make sure all words are spelled correctly or try different Topic.<!--</b> - does not have any results. <br/>

&nbsp;&nbsp; Please  make sure all words are spelled correctly or try different topic.-->
     <br/>
     <br/>
    </div>
  </div>
<?php endif;    ?>

  <?php if(count($results['items']) > 0): ?>
    <?php  print $results['result_txt'];?>
      <input type="hidden" id="totalpages" value="<?php print $results['total'];?>">
      <input type="hidden" id="startid" value="<?php print $results['startid'];?>">
      <input type="hidden" id="keywords" value="<?php print check_plain($results['keywords']);?>">
      <input type="hidden" id="limit" value="<?php print $results['limit'];?>">
      <input type="hidden" id="fromid" value="<?php print $results["from"];?>">
      <input type="hidden" id="toid" value="<?php print $results["to"];?>">
      <input type="hidden" id="total" value="<?php print $results["total"];?>">
    <div  class="google-bottom-pager">
      <?php if($results['startid'] > 1): ?>
       <a title="<<" class="my-pager" href=""><< Prev</a>&nbsp;
      <?php endif; ?>
      <?php
       print 'Page '.floor($results["to"]/$results['limit']).' of '.ceil($results["total"]/$results['limit']).'&nbsp;';
      ?>
      <?php if($results['startid']<=$results["total"]): ?>
       <a title=">>" class="my-pager" href="">Next >></a>&nbsp;
      <?php endif; ?>
    </div>
  <?php endif; ?>
