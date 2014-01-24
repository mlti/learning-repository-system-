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
   <?php if (isset($results['fields']['title'])) { ?>
   <div class="asset-teaser">
      <?php print $results['fields']['title']; ?>
       <?php if ($results['fields']['flag_content']) { ?>
         <?php print $results['fields']['flag_content']; ?>
      <?php } ?>
   </div>
   <?php } ?>
   <?php if (isset($results['fields']['fivestar_widget'])) { ?> <div class="fivestar-widget">  <?php print $results['fields']['fivestar_widget']; ?></div><?php } ?>
   </div>
<?php if ($results['fields']['source'] != "") { ?>
<div class="author-name">
 <span>
          <?php print 'Source'; ?>
         </span>
<?php print $results['fields']['source'] ; ?>

</div>
<?php } ?>
<p>
   <?php print $results['fields']['body_content']; ?>
</p>
<?php if (isset($results['fields']['links'])) {?>
      <div class="more-icon"> <?php print $results['fields']['links'];?> </div>
   <?php } ?>
   <div class="links">
      <ul class="clearfix">
         <?php if (isset($results['fields']['bookmark'])) { ?><li><?php print $results['fields']['bookmark']; ?></li><?php } ?>
         <?php if (isset($results['fields']['delete'])) { ?><li><?php print $results['fields']['delete']; ?></li> <?php } ?>
         <?php if (isset($results['fields']['stringable_beads_link'])) { ?><li><?php print $results['fields']['stringable_beads_link']; ?></li> <?php } ?>
      </ul>
   </div>
<?php if (isset($results['fields']['recommendedby']) || isset($results['fields']['comments']) || isset($results['fields']['recommendedby'])) { ?>
   <div class="discussion-comments">
      <ul class="clearfix">
         <?php if (isset($results['fields']['recommendedby'])) { $class = ''; } else { $class = 'last';} ?>
         <?php if($results['fields']['comments'] != '') { ?>
          <!--<li class=<?php //print $class;?> ><?php  //print $results['fields']['comments']; ?></li>-->
         <?php } ?>
         <?php if (isset($results['fields']['recommendedby'])) { ?>
            <li class="last">
               <span>Recommended By</span>
               <?php print $results['fields']['recommendedby']; ?>
            </li>
         <?php } ?>
      </ul>
   </div>
<?php } ?>
<!--   </div>
</div>-->
