<?php
// $Id: search-result.tpl.php,v 1.1.2.1 2008/08/28 08:21:44 dries Exp $

/**
 * @file search-result.tpl.php
 * Default theme implementation for displaying a single search result.
 *
 * This template renders a single search result and is collected into
 * search-results.tpl.php. This and the parent template are
 * dependent to one another sharing the markup for definition lists.
 *
 * Available variables:
 * - $url: URL of the result.
 * - $title: Title of the result.
 * - $snippet: A small preview of the result. Does not apply to user searches.
 * - $info: String of all the meta information ready for print. Does not apply
 *   to user searches.
 * - $info_split: Contains same data as $info, split into a keyed array.
 * - $type: The type of search, e.g., "node" or "user".
 *
 * Default keys within $info_split:
 * - $info_split['type']: Node type.
 * - $info_split['user']: Author of the node linked to users profile. Depends
 *   on permission.
 * - $info_split['date']: Last update of the node. Short formatted.
 * - $info_split['comment']: Number of comments output as "% comments", %
 *   being the count. Depends on comment.module.
 * - $info_split['upload']: Number of attachments output as "% attachments", %
 *   being the count. Depends on upload.module.
 *
 * Since $info_split is keyed, a direct print of the item is possible.
 * This array does not apply to user searches so it is recommended to check
 * for their existance before printing. The default keys of 'type', 'user' and
 * 'date' always exist for node searches. Modules may provide other data.
 *
 *   <?php if (isset($info_split['comment'])) : ?>
 *     <span class="info-comment">
 *       <?php print $info_split['comment']; ?>
 *     </span>
 *   <?php endif; ?>
 *
 * To check for all available data within $info_split, use the code below.
 *
 *   <?php print '<pre>'. check_plain(print_r($info_split, 1)) .'</pre>'; ?>
 *
 * @see template_preprocess_search_result()
 */
global $base_url;
?>
<?php if ($result_type == 'asset') { ?>
  <li class="clearfix">
    <?php if (isset($image_url)) { ?>
    <div class="result-left">
      <div class="img">
        <?php print $image_url; ?>
      </div>
    </div>
    <?php } ?>
    <div class="result-right ">
      <div class=" result-right-inner clearfix  comm-list-title">
        <div class="asset-teaser clearfix">
          <div class="float-left">
            <a title="Click to view content" href="<?php print $base_url.'/'.$url; ?>"  ><?php print $title; ?></a>
          </div>
           <?php if ($flag_content) { ?>
              <?php print $flag_content; ?>
           <?php } ?>
        </div>
        <?php if (isset($fivestar_widget)) { ?>
          <div class="fivestar-widget">
            <?php print $fivestar_widget; ?>
          </div>
        <?php } ?>
      </div>
      <!-- print the author name -->
      <?php if ($author_username) : ?>
        <div class="author-name">
          By <span><?php  print $author_username; ?></span>
        </div>
      <?php endif; ?>
      <?php if ($body) : ?>
        <p><?php print $body;?></p>
      <?php endif; ?>
      <?php if (isset($more_preview)) { ?>
        <div class="more-icon" title="Click to Preview">
          <?php print $more_preview; ?>
        </div>
      <?php } ?>
      <?php if (isset($bookmark_links)) : ?>
        <div class="links">
          <ul class="clearfix">
            <li><?php print  $bookmark_links; ?></li>
          </ul>
        </div>
      <?php endif; ?>  
    </div>
  </li>
<?php } else if ($result_type == 'profile') { ?>
  <li class="clearfix">
    <?php if (isset($image_url)) { ?>
    <div class="result-left">
      <div class="img">
        <?php print $image_url; ?>
      </div>
    </div>
    <?php } ?>
    <div class="result-right">
      <div class="result-right-inner clearfix">
        <?php if ($firstlastname) : ?>
          <div class="asset-teaser"><?php print $firstlastname_link; ?></div>
        <?php endif; ?>
      </div>
      <?php if ($email) : ?>
        <p><?php print $email; ?></p>
      <?php endif; ?>
      <?php if ($institution) : ?>
        <p><?php print $institution; ?></p>
      <?php endif; ?>
      <?php if ($firstlastname) : ?>
        <div class="contact-icon">
          <a title="Contact" href="<?php print $base_url ?>/messages/new?cid=<?php print $contactId;?>"></a>
        </div>
      <?php endif; ?>
    </div>
   </li>
<?php } else if ($result_type == 'community_interest_group') { ?>
  <li class="clearfix">
    <?php if (isset($image_url)) { ?>
      <div class="result-left">
        <div class="img">
         <?php print $image_url; ?>
        </div>
      </div>
    <?php } ?>
    <div class="result-right">
      <div class="result-right-inner clearfix">
        <div class="asset-teaser clearfix">
        <div class="float-left">
          <a title="Click to view content" href="<?php print $base_url.'/'.$url; ?>" ><?php print $title; ?></a>
        </div>
          <?php if ($flag_content) { ?>
            <?php print $flag_content; ?>
          <?php } ?>
        </div>
      </div>
      <!-- print the author name -->
      <?php if ($author_username) : ?>
        <div class="author-name">
          By <span><?php  print $author_username; ?></span>
        </div>
      <?php endif; ?>
      <?php if ($body) : ?>
        <p><?php print $body;?></p>
      <?php endif; ?>
      <?php if (isset($bookmark_links) || isset($recommend_links)) { ?>
        <div class="links">
          <ul class="clearfix">
            <?php if ($bookmark_links) : ?>
              <li><?php print  $bookmark_links; ?></li>
            <?php endif; ?>
            <?php if ($recommend_links) : ?>
              <li><?php print $recommend_links; ?></li>
            <?php endif; ?>
          </ul>
        </div>
      <?php } ?>  
    </div>
  </li>
<?php } elseif ($result_type == 'discussion') {?>
  <li class="clearfix">
  <?php if (isset($image_url)) { ?>
    <div class="result-left">
      <div class="img">
        <?php print $image_url; ?>
      </div>
    </div>
    <?php } ?>
    <div class="result-right ">
      <div class="result-right-inner clearfix">
        <div class="asset-teaser clearfix">
          <div class="float-left">
            <a title="Click to view content" href="<?php print $base_url.'/'.$url; ?>" ><?php print $title; ?></a>
          </div>
          <?php if ($flag_content) { ?>
            <?php print $flag_content; ?>
          <?php } ?> 
        </div>
      </div>
      <!-- print the author name -->
      <?php if ($author_username) : ?>
        <div class="author-name">
          By <span><?php  print $author_username; ?></span>
        </div>
      <?php endif; ?>
      <?php if ($body) : ?>
        <p><?php print $body;?></p>
      <?php endif; ?>
      <?php if (isset($bookmark_links) || isset($recommend_links)) { ?>
        <div class="links">
          <ul class="clearfix">
            <?php if ($bookmark_links) : ?>
              <li><?php print  $bookmark_links; ?></li>
            <?php endif; ?>
            <?php if ($recommend_links) : ?>
              <li><?php print $recommend_links; ?></li>
            <?php endif; ?>
          </ul>
        </div>
      <?php } ?>
    </div>
  </li>
<?php }elseif ($result_type == 'curriculum') {?>
  <li class="clearfix">
    <?php if (isset($image_url)) { ?>
      <div class="result-left">
        <div class="img">
          <?php print $image_url; ?>
        </div>
      </div>
    <?php } ?>
    <div class="result-right ">
      <div class="result-right-inner clearfix">
        <div class="asset-teaser clearfix">
          <div class="float-left">
            <a title="Click to view content" href="<?php print $base_url.'/'.$url; ?>" ><?php print $title; ?></a>
          </div>
          <?php if ($flag_content) { ?>
            <?php print $flag_content; ?>
          <?php } ?>
        </div>
      </div>
      <!-- print the author name -->
      <?php if ($author_username) : ?>
        <div class="author-name">
          By <span><?php  print $author_username; ?></span>
        </div>
      <?php endif; ?>
      <?php if ($body) : ?>
        <p><?php print $body;?></p>
      <?php endif; ?>
      <?php if (isset($more_preview)) { ?>
        <div class="more-icon" title="More"><?php print $more_preview; ?></div>
      <?php } ?>
      <?php if (isset($bookmark_links) || isset($recommend_links)) { ?>
      <div class="links">
        <ul class="clearfix">
          <?php if ($bookmark_links) : ?>
            <li><?php print  $bookmark_links; ?></li>
          <?php endif; ?>
          <?php if ($recommend_links) : ?>
            <li><?php print $recommend_links; ?></li>
          <?php endif; ?>
        </ul>
      </div>
      <?php } ?>  
    </div>
  </li>
<?php } elseif ($result_type == 'bead') {?>
  <li class="bead-result clearfix">
  <?php if (isset($image_url)) { ?>
    <div class="result-left">
      <div class="img">
        <?php print $image_url; ?>
        <?php print $bead_icons; ?>
      </div>
    </div>
    <?php } ?>
    <div class="result-right">
      <div class="result-right-inner clearfix">
        <div class="similar-assets-title">
            <a title="Click to view content" href="<?php print $base_url.'/'.$url; ?>" ><?php print $title; ?></a>
        </div>
      </div>
      <!-- print the author name -->
      <!-- print the Source-->
      <?php if ($source) : ?>
        <div class="author-name">
          Source <span><?php  print $source; ?></span>
        </div>
      <?php endif; ?>
      <?php if ($body) : ?>
        <p><?php print $body;?></p>
      <?php endif; ?>
      <?php if (isset($more_preview)) { ?>
        <div class="more-icon" title="Click to Preview"><?php print $more_preview; ?></div>
      <?php } ?>
      <?php if (isset($bookmark_links) || isset($recommend_links) || isset($beads_stringable_link)) { ?>
      <div class="links">
        <ul class="clearfix">
          <?php if ($bookmark_links) : ?>
            <li><?php print  $bookmark_links; ?></li>
          <?php endif; ?>
          <?php if ($recommend_links) : ?>
            <li><?php print $recommend_links; ?></li>
          <?php endif; ?>
          <?php if ($beads_stringable_link) : ?>
            <li><?php print $beads_stringable_link; ?></li>
          <?php endif; ?>
        </ul>
      </div>
      <?php } ?>
    </div>
  </li>
<?php } elseif ($result_type == 'quiz') {?>
  <li class="bead-result clearfix">
    <?php if (isset($image_url)) { ?>
    <div class="result-left">
      <div class="img">
        <?php print $image_url; ?>
      </div>
    </div>
    <?php } ?>
    <div class="result-right ">
      <div class="result-right-inner clearfix">
        <div class="asset-teaser clearfix">
          <div class="float-left">
            <a title="Click to view content" href="<?php print $base_url.'/'.$url; ?>" ><?php print $title; ?></a>
          </div>
          <?php if ($flag_content) { ?>
            <?php print $flag_content; ?>
         <?php } ?>
        </div>
      </div>
      <!-- print the author name -->
      <!-- print the Source-->
      <?php if ($author_username) : ?>
        <div class="author-name">
          By <span><?php  print $author_username; ?></span>
        </div>
      <?php endif; ?>
      <?php if ($body) : ?>
        <p><?php print $body;?></p>
      <?php endif; ?>
      <?php if (isset($more_preview)) { ?>
        <div class="more-icon" title="Click to Preview"><?php print $more_preview; ?></div>
      <?php } ?>
       <?php if (isset($bookmark_links) || isset($recommend_links) || isset($beads_stringable_link)) { ?>
          <div class="links">
            <ul class="clearfix">
              <?php if ($bookmark_links) : ?>
                <li><?php print  $bookmark_links; ?></li>
              <?php endif; ?>
              <?php if ($recommend_links) : ?>
                <li><?php print $recommend_links; ?></li>
              <?php endif; ?>
              <?php if ($beads_stringable_link) : ?>
                <li><?php print $beads_stringable_link; ?></li>
              <?php endif; ?>
            </ul>
          </div>
        <?php } ?>
    </div>
  </li>
<?php } ?>