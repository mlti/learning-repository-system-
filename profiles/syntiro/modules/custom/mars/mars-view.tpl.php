<?php
// $Id: recommendations_new_page.tpl.php,v 1.1.2.1 2011/03/22 Antonyj Exp $
global $base_url;
?>
<div id="mars-result-area" class="common-list-wrapper">
  <div class="common-list-drop-preview" style="display:none">
    <a title="results" class=""  href="#">Preview</a>
  </div>
  <div class="common-list-drop">   <!--<a title="results" href="#">Sort</a> --></div>
  <?php if ($mars_title) { ?> <h2><?php print $mars_title ?></h2> <?php } ?>
  <div class="listing-content-area">
    <?php if (!$results['no_record']): ?>
      <div class="view-content">
        <div class="item-list">
          <ul>
            <?php foreach ($results['fields'] as $value) {?>
              <li class="bead-result <?php print $value['nd_visited']; ?>">
                <?php print $value['body']; ?>
              </li>
            <?php  } ?>
          </ul>
        </div>
      </div>
    <?php else :?>
      <div class="view-content no-content">
        <span><p><?php print $results['no_record']; ?></p></span>
      </div>
    <?php endif; ?>
    <?php if ($pager) { ?>
    <div id="mars-pager">
      <?php print $pager; ?>
    </div>
    <?php } ?>
  </div>
</div>
