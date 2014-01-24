<?php
// $Id: page.tpl.php,v 1.18.2.1 2009/04/30 00:13:31 goba Exp $
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <?php print $head ?>
    <title><?php print $head_title ?></title>
    <?php print $styles ?>
    <?php print $scripts ?>
    <!--[if lt IE 7 ]>
      <?php print phptemplate_get_ie_styles(); ?>
    <![endif]-->
     <!--[if lt IE 8 ]>
      <?php print phptemplate_get_ie_styles(); ?>
    <![endif]-->
  </head>
  <body  class="<?php print $body_classes; ?>">
    <!--<div id="header-region" class="clear-block"><?php //print $header; ?></div>-->
    <div class="wrapper">
      <!-- Layout -->
      <div id="header">
        <div class="header-inner clearfix">
          <div class="logo float-left">
            <?php
              // Prepare header
              $site_fields = array();
              if ($site_name) {
                $site_fields[] = check_plain($site_name);
              }
              if ($site_slogan) {
                $site_fields[] = check_plain($site_slogan);
              }
              $site_title = implode(' ', $site_fields);
              if ($site_fields) {
                $site_fields[0] = '<span>'. $site_fields[0] .'</span>';
              }
              $site_html = implode(' ', $site_fields);

              if ($logo || $site_title) {
                print '<h1><a href="'. check_url($front_page) .'" title="'. $site_title .'">';
                if ($logo) {
                  print '<img src="'. check_url($logo) .'" alt="'. $site_title .'" id="logo" />';
                }
                print $site_html .'</a></h1>';
              }
            ?>
          </div>
          <div class="header-right float-right">
            <div class="clearfix">
              <?php if ($search_box): ?><div class="block block-theme"><?php print $search_box ?></div><?php endif; ?>
              <?php if ($header_middle) { ?>
                <div class="search-type float-left">
                  <?php print $header_middle; ?>
                </div>
              <?php } ?>

              <div class="header-top-right float-right">
              <?php if($top_user_image) : ?>
              <div class="header-top-user-block clearfix">
                <?php print $top_user_image;  ?>
                <?php if($top_user_link): print $top_user_link; endif; ?>
                <?php if($manage_account): ?>
                  <ul class="header-drop-down" style="display: none;">
                    <li><?php print $manage_account; ?></li>
                    <li><?php print $logout_link; ?></li>
                  </ul>
                <?php endif; ?>
              </div>
            <?php endif; ?>
            <?php if($header_login): ?>
              <div class="header-right-top"> <?php print $header_login; ?></div>
            <?php endif; ?>
            <?php if (isset($primary_links) || isset($unread)) : ?>
              <div class="message-count-top clearfix">
              <?php if (isset($primary_links)) : ?>
                <?php print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
              <?php endif; ?>
              <?php if (isset($unread)) : ?>
              <span class="message-count"><span><?php print $unread; ?></span></span>
              <?php endif; ?>
              </div>
              <?php endif; ?>
            </div>
            </div>
          </div>
        </div>
      </div> <!-- /header -->
      <div id="main" class="clearfix">
        <?php if ($left): ?>
          <div id="sidebar-left" class="sidebar">
            <?php if ($search_box): ?><div class="block block-theme"><?php print $search_box ?></div><?php endif; ?>
            <?php print $left ?>
          </div>
        <?php endif; ?>

          <?php if ($content_top) {
            //<!-- Content top region -->
            print $content_top; } ?>
 <?php if ($message_listing): print '<div class="display-messages top-message">' . $message_listing . '</div>'; endif; ?>
              <!--main-content-wrapper float-left starts -->
            <div class="main-content-wrapper float-left">
              <div class="page-not-found clearfix">
                <div class="page-not-found-inner">
                  <div class="pnf-left float-left">
                    <img src="<?php print base_path() . path_to_theme();?>/images/page-not-img.png" alt="Page Not Found" />
                  </div>
                  <div class="pnf-right float-left">
                    <h3>Sorry</h3>
                    <p>This content is not available. The content may have been removed. Use the search bar at the top to continue searching.</p>
                  </div>
                </div>
              </div>
            </div>  <!--main-content-wrapper float-left ends -->




      </div> <!-- /main -->
 <div id="footer">
        <?php if ($footer) { ?>
          <div class="footer-top">
          <div class="footer-menu-wrapper">
            <?php if ($footer_title) {?>
              <h2>
                <?php //print $footer_title; ?>
              </h2>
            <?php } ?>
            <div class="content">
              <div class="clearfix footer-menu-inner">
                <div class="footer-menu-links">
                  <?php print $footer ?>
                </div>
              </div>
              <?php if ($footer_upper_right) { ?>
                <div class="footer-follow-us">
                  <?php print $footer_upper_right ?>
                </div>
              <?php } ?>
            </div>
          </div>
        </div>
      <?php }?>
      <div class="footer-bottom">
        <div class="footer-links">
          <?php if (isset($secondary_links)) : ?>
                <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?>
              <?php endif; ?>
          <?php if ($footer_bottom) { print $footer_bottom; }?>
          <?php print $footer_message  ?>
        </div>
        <?php if ($footer_right) { ?> <div class="chat-block"> <?php print $footer_right; ?></div> <?php } ?>
      </div>
      </div>
<!-- /layout -->
  <?php print $closure ?>
  </div> <!-- /container -->
  <noscript>
	<div id="mask"></div>
    <div id="container">
    <div class="container-content">
    	<p>Please Enable JavaScript</p>
    <!--end container--></div></div>
  </noscript>
  </body>
</html>
