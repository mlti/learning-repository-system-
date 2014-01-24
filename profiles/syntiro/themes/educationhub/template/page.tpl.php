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
    <div id="skip-link">
      <a class="visually-hidden focusable" href="#main-content">
        Skip to main content
      </a>
    </div>
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

              if ($logo || $hub_sitename) {
                print '<h1 id="logo-text"><a href="'. check_url($front_page) .'" title="'. $hub_sitename .'">';
                if ($logo) {
                  print '<img src="'. check_url($logo) .'" alt="'. $hub_sitename .'" id="logo" />';
                }
                
                print $site_html .'<span class="element-invisible">Homepage</span></a></h1>';
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
                  <ul class="header-drop-down element-invisible">
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
            <div class="main-content-wrapper float-left" id="main-content">


              <?php if ($right){ ?>

               <!-- for  <div class="clearfix main-content-top"> <div class="main-content"> Right side region is enabled then we add this div opening -->
                <div class="clearfix main-content-top">
                <div class="main-content">

              <?php } ?>

              <?php // print $breadcrumb; ?>
              <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
              <div class="clearfix <?php if ($title): print "title-wrapper";  endif; ?> ">
              <?php //if ($title): print '<h2'. ($tabs ? ' class="with-tabs"' : ' class="title"') .'>'. $title .'</h2>'; endif; ?>
              <?php if ($title): print '<h2 class="title">'. ucwords($title) .'</h2>'; endif; ?>              <?php if ($flag_view): print $flag_view; endif; ?>
              <?php if ($create_link): print $create_link;  endif; ?>
              <?php if ($drop_link): print $drop_link;  endif; ?>
              <?php if ($join_link): print $join_link;  endif; ?>
              <?php if (isset($edit)) { print $edit; } ?>
              <?php if (isset($ratings)) { print $ratings; } ?>
              </div>
              <?php if($edit_header_name): ?>
          <!--      <h3 class="assigned-to">
                  <?php print $edit_header_name; ?>
                </h3>-->
              <?php endif; ?>
              <?php if ($og_title): print '<h3 class="assigned-to">'. $og_title .'</h3>'; endif; ?>
              <!-- End of Assignment form in Assign more page -->
              <?php if ($tabs):
              // Open Tab Div
              print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
              <?php if($edit_header_name): print '<h2 class="with-tabs">'. $edit_header_name .'</h2>'; endif; ?>
              <!-- Assignment form in Assigned more page -->
              <?php if($assignment_form): ?>
                <div class="assign-more-form" style="display: none">
                  <?php print $assignment_form; ?>
                </div>
              <?php endif; ?>
              <!-- End of Assignment form in Assigned more page -->
              <?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul></div>'; endif; // Close Tab Div?>
              <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
              <?php if ($compose_message): print '<div class="compose-mess">'. $compose_message . '</div>'; endif; ?>
              <?php if ($manage_membership): print '<div class="compose-mess">'. $manage_membership . '</div>'; endif; ?>
              <?php if ($assign_more_button): print '<div class="compose-assign">'. $assign_more_button . '</div>'; endif; ?>
              <?php if ($messages): print '<div class="display-messages">' . $messages . '</div>'; endif; ?>
              <?php print $help; ?>

              <div id="content-section" class="clear-block">
                <div class="preview-content"></div>
                <?php print $content ?>
              </div>
              <?php print $feed_icons ?>


           <?php if ($right): ?>

               <!-- for <div class="main-content"> Right side region is enabled then we add this div ending -->
                </div>
              <div id="sidebar-right" class="sidebar">
                                <?php if (!$left && $search_box): ?><div class="block block-theme"><?php print $search_box ?></div><?php endif; ?>
                <?php print $right ?>
              </div>
            <?php endif; ?>

            <?php if ($right){ ?>
            <!-- for <div class="clearfix main-content-top"> Right side region is enabled then we add this div ending-->
          </div> <?php } ?>
          <?php if ($content_bottom) { ?>
            <div class="main-content-bottom">
              <?php print $content_bottom; ?>
           </div>
          <?php } ?>
       </div>  <!--main-content-wrapper float-left ends -->




      </div> <!-- /main -->
 <div id="footer">
        <?php if ($footer) { ?>
          <div class="footer-top">
          <div class="footer-menu-wrapper">
            <span class="footerbox clearfix">
              <?php //if ($footer_title) {?>
                <?php //print $footer_title; ?>
              <?php //} ?>
            </span>
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
  <!--<noscript>
	<div id="mask"></div>
    <div id="container">
    <div class="container-content">
    	<p>Please Enable JavaScript</p>
   </div></div>
  </noscript> --><!--end container-->
  </body>
</html>
