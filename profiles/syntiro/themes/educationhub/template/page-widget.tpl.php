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
        </div>
      </div> <!-- /header -->
      <div id="main" class="clearfix">

              <!--main-content-wrapper float-left starts -->
            <div class="main-content-wrapper float-left">
              <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
              <div class="clearfix <?php if ($title): print "title-wrapper";  endif; ?> ">
              <?php if ($title): print '<h2 class="title">'. ucwords($title) .'</h2>'; endif; ?>              </div>
              <!-- End of Assignment form in Assign more page -->
              <?php if ($tabs):
              // Open Tab Div
              print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
             
              <!-- End of Assignment form in Assigned more page -->
              <?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul></div>'; endif; // Close Tab Div?>
              <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
               <?php if ($messages): print '<div class="display-messages">' . $messages . '</div>'; endif; ?>
              <?php print $help; ?>
              <div id="content-section" class="clear-block">
                <div class="preview-content"></div>
                <?php print $content ?>
              </div>
              <?php print $feed_icons ?>
       </div>  <!--main-content-wrapper float-left ends -->




      </div> <!-- /main -->

<!-- /layout -->
  <?php print $closure ?>
  </div> <!-- /container -->
  </body>
</html>
