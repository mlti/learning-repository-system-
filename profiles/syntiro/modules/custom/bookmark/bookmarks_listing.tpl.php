<?php
// $Id$: bookmarks_page.tpl.php,v 1.1.2.1 2011/02/25 Beschi $
/**
 * @file
 * mybookmarks page display file
 */
?>
<div id="bm-result-area" class="common-list-wrapper" >
  <div class="common-list-drop-preview" style="display:none">
    <a title="results" class=""  href="#">Preview</a>
  </div>
  <div class="common-list-drop">   <!--<a title="results" href="#">Sort</a>--> </div>
  <div class="listing-content-area">
    <div class="view-content">
      <div class="item-list">
        <ul>
          <?php if (!$bookmark_result['bookmark_null']) {
            foreach ($bookmark_result as $value) { ?>
                <li class='bead-result'>
                   <?php print $value['body']; ?>
                </li>
            <?php }
          }
          else {
            print $bookmark_result['bookmark_null'];
          } ?>
        </ul>
      </div>
    </div>
    <div id="bm-pager">
      <?php print $pager; ?>
    </div>
  </div>
</div>
