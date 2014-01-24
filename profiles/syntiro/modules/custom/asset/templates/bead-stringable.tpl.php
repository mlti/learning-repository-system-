<?php
// $Id: asset-view.tpl.php,v 1.1.2.1 2011/03/05 Beschi Exp $
global $base_url;
?>
<div id="bead-result-sequence" class="result no-content">
   <div class="view-content">
      <?php if (!$results['no_record']): ?>
         <div class="item-list">
            <ul id="limit-scroll">
               <?php foreach ($results['fields'] as $value) {?>
                  <!-- // If he is an author <li class="selected-author">-->
                  <li>
                     <div class="main-discussion clearfix <?php if ($value['nid'] == arg(2)) { print  "selected-author";  } ?>" id="<?php print $value['title_id']; ?>" >
                        <div id="title-<?php print $value['nid'] ?>">
                           <div class="result-right-inner clearfix " >
                              <div class="bead-title">
                                 <?php print $value['title']; ?>
                                 <?php if ($value['nid']) { ?> <a name="<?php print $value['nid'] ?>"></a> <?php } ?>
                              </div>
                           </div>
                           <div class="stringable-body">
                              <?php print $value['body_content']; ?>
                           </div>
                        </div>
                     </div>
                  </li>
               <?php  } ?>
            </ul>
        </div>
      <?php else :?>
         <span><?php print $results['no_record']; ?></span>
      <?php endif; ?>
   </div>
</div>
