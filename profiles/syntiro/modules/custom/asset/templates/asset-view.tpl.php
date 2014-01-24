<?php
// $Id: asset-view.tpl.php,v 1.1.2.1 2011/03/05 Beschi Exp $

?>
<div id="asset-result-area" class="common-list-wrapper">
  <div class="common-list-drop-preview" style="display:none">
    <a title="results" class=""  href="#">Preview</a>
  </div>
  <div class="common-list-drop">  <!-- <a title="results" href="#">Sort</a>--> </div>
  <div class="listing-content-area">
    <div class="view-content">
      <?php if (!isset($results['no_record']) && isset($results['fields'])): ?>
        <div class="item-list">
          <ul>
            <?php foreach ($results['fields'] as $value) {?>
              <!-- // If he is an author <li class="selected-author">-->
              <li>
                <?php  print $value['teaser_asset_view']; ?>
              </li>
            <?php  } ?>
          </ul>
        </div>
      <?php elseif (isset($results['no_record'])) :?>
         <span><?php print $results['no_record']; ?></span>
      <?php endif; ?>
    </div>
    <?php if (isset($results['create_link'])) {  print $results['create_link'];}?>
    <div id="asset-pager">
      <?php print $results['pager']; ?>
    </div>
  </div>
</div>
