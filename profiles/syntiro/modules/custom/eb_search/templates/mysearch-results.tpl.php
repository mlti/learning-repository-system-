<?php
// $Id: custom-search.tpl.php,v 1.1 2010/10/13 18:06:38 karthikeyan Exp $

/**
 * @file custom-search.tpl.php
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
 * - $federated_search:  results as it is rendered for federated search
 * - $google_search:  results as it is rendered for google search
 * - $custom_search:  results as it is rendered for custom search
 *
 * @see template_preprocess_search_results()
 */
?>
                <?php print $custom_search; ?>
            
