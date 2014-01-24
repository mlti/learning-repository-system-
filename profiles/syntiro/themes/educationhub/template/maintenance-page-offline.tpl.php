<?php
// $Id: maintenance-page.tpl.php,v 1.3.2.1 2009/04/30 00:13:31 goba Exp $

/**
 * @file maintenance-page.tpl.php
 *
 * This is an override of the default maintenance page. Used for Garland and
 * Minnelli, this file should not be moved or modified since the installation
 * and update pages depend on this file.
 *
 * This mirrors closely page.tpl.php for Garland in order to share the same
 * styles.
 */
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <?php print $head ?>
    <title>Site off-line | EducationHub</title>
    <?php print $styles ?>
    <?php print $scripts ?>
    <!--[if lt IE 7]>
      <?php print phptemplate_get_ie_styles(); ?>
    <![endif]-->
  </head>
  <body class="in-maintenance no-sidebars">

<!-- Layout -->
  <div id="header-region" class="clear-block"><?php print $header; ?></div>

    <div id="wrapper">
      <div id="header">
        <div class="header-inner clearfix">
          <div id="logo-floater">
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
              print '<h1><a href="'. check_url($base_path) .'" title=AcrossWorld>';
              if ($logo) {
                print '<img src="/sites/all/files/educationhub_logo.png" alt="" id="logo">';
              }
              print  '</a></h1>';
            }
          ?>
          
          </div>
        </div>
      </div> <!-- /header -->
       <div id="main">
            
      <div id="center"><div id="squeeze"><div class="right-corner"><div class="left-corner">
                                        <div class="clear-block">
            <div class="site-ofline-block"><img src="/sites/all/themes/educationhub/images/site-ofline-img.png" title="Site Under Maintenance" alt="Site Under Maintenance">
<h2>Site Under Maintenance</h2>
<p>We will return shortly!</p>
</div>          </div>
          
      </div></div></div></div></div>
          <div id="footer"><div class="footer-bottom"><div class="footer-links"><div class="copyright">&copy;AcrossWorld 2012</div></div></div></div>
      <?php if ($right): ?>
        <div id="sidebar-right" class="sidebar">
          <?php print $right ?>
        </div>
      <?php endif; ?>
  </div>
<!-- /layout -->

  </body>
</html>
