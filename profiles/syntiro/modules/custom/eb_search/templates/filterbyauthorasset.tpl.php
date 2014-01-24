<?php
// $Id: search-results.tpl.php,v 1.1 2007/10/31 18:06:38 dries Exp $

/**
 * @file filterbyauthorasset.tpl.php
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_filterbyauthorasset(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $filterbyauthor: All results as it is rendered through
 *
 *
 * @see template_preprocess_filterbyauthorasset()
 */
?>
<div class="filter-rightside">
<?php if ($filterdate || $author || $filterformat || $subject || $source || $insititution || $co_author || $reviewer || $academic_level || $mlr_standard) {?>
    <div class="filter-results">
      <ul>
      <?php if ($filterdate) {?>
        <li tabindex="0"> <div class="filter-title"><a href="javascript:;">Date </a></div>
          <div class="filter-content element-invisible">
          <?php print $filterdate; ?>
        </div>
        </li>
      <?php }?>
      <?php if ($author) {?>
      <li> <div class="filter-title"><a href="javascript:;">Authors </a></div>
          <div class="filter-content filter-authors element-invisible">
          <?php print $author; ?>
        </div>
      </li>
      <?php }?>
      <?php if ($filterformat) {?>
      <li> <div class="filter-title"><a href="javascript:;">Format </a></div>
          <div class="filter-content filter-format element-invisible">
          <?php print $filterformat; ?>
        </div>
      </li>
      <?php }?>
      <?php if ($subject) {?>
      <li> <div class="filter-title"><a href="javascript:;">Subject </a></div>
          <div class="filter-content filter-subject element-invisible">
          <?php print $subject; ?>
        </div>
        </li>
      <?php }?>
      <?php if ($source) {?>
        <li> <div class="filter-title"><a href="javascript:;">Source </a></div>
          <div class="filter-content filter-source element-invisible">
          <?php print $source; ?>
             </div>
        </li>
      <?php }?>
        <?php if ($insititution) {?>
        <li> <div class="filter-title"><a href="javascript:;">Institution </a></div>
          <div class="filter-content filter-institution element-invisible">
          <?php print $insititution; ?>
        </div>
          </li>
       <?php }?>
           
       
        <?php if ($co_author) {?>
        <li> <div class="filter-title"><a href="javascript:;">Co-Authors </a></div>
          <div class="filter-content filter-coauthor element-invisible">
          <?php print $co_author; ?>
        </div>
        </li>
        <?php }?>
        <?php if ($reviewer) {?>
        <li> <div class="filter-title"><a href="javascript:;">Reviewers </a></div>
          <div class="filter-content filter-reviewers element-invisible">
          <?php print $reviewer; ?>
        </div>
        </li>
        <?php }?>
        <?php if ($academic_level) {?>
        <li> <div class="filter-title"><a href="javascript:;">Academic Level </a></div>
          <div class="filter-content filter-academic-level element-invisible">
          <?php print $academic_level; ?>
        </div>
        </li>
        <?php }?>
        <?php if ($creative_common) {?>
        <li> <div class="filter-title"><a href="javascript:;">Creative Common Option </a></div>
          <div class="filter-content filter-creative-common element-invisible">
          <?php print $creative_common; ?>
        </div>
        </li>
        <?php }?>
        <?php if ($mlr_standard) {?>
        <li> <div class="filter-title"><a href="javascript:;">MLR Standard </a></div>
          <div class="filter-content filter-mlstandard element-invisible">
          <?php print $mlr_standard; ?>
        </div>
        </li>
        <?php }?>
      </ul>
    </div>
<?php }?>
</div>