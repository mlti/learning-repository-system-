<?php
// $Id: node.tpl.php,v 1.5 2007/10/11 09:51:29 goba Exp $
?>
<!--<div class="main-discussion clearfix">
   <div class="result-left">
      <div class="img">
         <?php //print $results['fields']['picture']; ?>
      </div>
   </div>
   <div class="result-right">-->
<div class="clearfix comm-list-title">
   <div class="asset-teaser clearfix">
      <?php if ($results['fields']['ext_title']) { print $results['fields']['ext_title']; } else {?>
      <?php  print $results['fields']['title']; } ?>
   </div>
</div>
<?php if ($results['fields']['author'] != "") { ?>
<div class="author-name">
   <span>
     <?php print $results['fields']['author']; ?>
   </span>

   <?php if ($results['fields']['category']) { ?>
      Type :  <span><?php print $results['fields']['category']; ?> </span>
    <?php  }?>
</div>
<?php } ?>
<p>
   <?php print $results['fields']['body_content']; ?>
</p>
<div class="more-icon"> <?php print $results['fields']['links'];?> </div>
<div class="links">
   <ul class="clearfix">
      <?php if ($results['fields']['bookmark']) { ?><li><?php print $results['fields']['bookmark']; ?></li><?php } ?>
      <?php if ($results['fields']['recommend']) { ?><li><?php print $results['fields']['recommend']; ?></li><?php } ?>
      <?php if ($results['fields']['delete']) { ?><li><?php print $results['fields']['delete']; ?></li> <?php } ?>
   </ul>
</div>
<!--   </div>
</div>-->
