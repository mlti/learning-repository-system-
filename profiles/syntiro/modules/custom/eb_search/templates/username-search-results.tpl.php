<?php
// $Id: username_search.tpl.php,v 1.1 2011/7/15 10:12:AM dries Exp $
/**
 * @file username_search.tpl.php
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   username-search.tpl.php
 * - $type: The type of search, e.g., "node" or "user".
 *
 *
 * @see template_preprocess_username_search()
 */
global $base_url;
?>
<div class="result recommend-wrapper">
  <div class="search-more-main search-username-result">
         <div class="popup-username-search-box">
          <?php if ($results['search_box']) { ?>
            <?php  print $results['search_box']; ?>
          <?php } ?>
          </div>
          <div class="select-all-main clearfix">
            <?php print $select_all_form; ?>
          </div>
          <div id="username-results">
              <?php if ($totalCount) { ?>
                <span id="total_count_top">
                  <?php  print $totalCount; ?>
                </span>
              <?php } ?>


              <?php if ($zeroResults) {
                  print $zeroResults;
                 } else {?>
            <div class="results recommend-group-listing">
              <?php    print $username_result;
                  } ?>
            </div>
              <div class="username-result-pager">
                <?php print $pager; ?>
              </div>
              <?php if ($submit_button) { ?>
                <?php  print $submit_button; ?>
            <?php } ?>
           </div>
   </div>
</div>
