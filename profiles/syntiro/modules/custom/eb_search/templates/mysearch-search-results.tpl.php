<?php
// $Id: search-results.tpl.php,v 1.1 2007/10/31 18:06:38 dries Exp $

/**
 * @file mysearch-search-results.tpl.php
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
 *   search-result.tpl.php
 * - $type: The type of search, e.g., "node" or "user".
 *
 *
 * @see template_preprocess_mysearch_search_results()
 */

?>
<?php if ($search_results) {?>
  <div class="item-list">
    <ul class="search-results <?php print $type; ?>-results">
      <?php print $search_results; ?>
    </ul>
  </div>
  
  <?php// print $pager; ?>
  <?php  if($_GET['searchs']) { ?>
   <div class='mars-basket-block'>
    <?php print $pager_mars_block; ?>
  </div>
  <?php } else  { ?>
   <div class='search-basket-block'>
    <?php print $pager_search_block; ?>
  </div>
    
  <?php }?>
 
<?php }?>
