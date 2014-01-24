<?php
// $Id: search-results.tpl.php,v 1.1 2007/10/31 18:06:38 dries Exp $
/**
 * @file search-results.tpl.php
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
 * @see template_preprocess_search_results()
 */
global $base_url;
?>
<?php if ($totalCount) { ?> <div class="result-count" > <?php print $totalCount;?> </div> <?php } ?>
<div class="clearfix search-block-innner common-list-wrapper <?php print $mars_nocontent; ?>">
   <div class="common-list-drop-preview" style="display:none">
      <a title="results" class=""  href="#">Preview</a>
   </div>
   <div class="common-list-drop ">   <!--<a title="results" href="#">Sort</a>--> </div>
      <div class="search-block-r">
      <div class="result">
      <div class="search-more-main">
        <div class="search-list-left">
            <div class="search-list-left-top item-list">
              <p style="display:none" id="total_count">
                <?php print $totalCount?$totalCount:''; ?>
              </p>
              <ul class="results">
                <?php if ($new_keyword) { ?>
                 <div class="margin-bottom">
                   Did you mean :
                    <span class="did-mean"><?php print $new_keyword; ?></span>
                    </div>
                <?php } ?>

                <?php if(!$search_assets) {
                  print $zeroResults;
                       } else { ?>
                  <?php print $search_assets;
                }
                ?>
              </ul>
            </div>
        </div>
      </div>
    <div class="google-search">
      <div class="paging clearfix">
          <div class="paging-inner">
              <div class="google-bottom-pager"><?php print $pager; ?>
              </div>
         </div>
        </div>
    </div>
    </div>
  </div>
</div>
