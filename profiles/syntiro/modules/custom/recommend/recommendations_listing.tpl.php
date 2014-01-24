<?php
// $Id: recommendations_new_page.tpl.php,v 1.1.2.1 2011/03/05 Beschi Exp $
/**
 * @file
 * Myrecommendations page - displaying recommendations received page
 */
?>
<div id="rec-result-area" class="common-list-wrapper">
  <div class="common-list-drop-preview" style="display:none">
    <a title="results" class=""  href="#">Preview</a>
  </div>
  <div class="common-list-drop">   <!--<a title="results" href="#">Sort</a>--> </div>
  <div class="listing-content-area">
    <div class="view-content ">
      <div class="item-list">
        <ul>
          <?php if (!$recommend_result['recommend_null']) {
            foreach ($recommend_result as $key => $value) { ?>
              <li class=bead-result>
                <?php print $value['body']; ?>
              </li>
            <?php  }
          }
          else {
            print $recommend_result['recommend_null'];
          } ?>
        </ul>
      </div>
    </div>
    <div id="rec-pager">
      <?php print $pager; ?>
    </div>
  </div>
</div>
