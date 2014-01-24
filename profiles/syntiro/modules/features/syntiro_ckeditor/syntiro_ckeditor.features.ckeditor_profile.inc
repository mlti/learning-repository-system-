<?php

/**
 * Implementation of hook_ckeditor_profile_defaults().
 */
function syntiro_ckeditor_ckeditor_profile_defaults() {
  $data = array(
    'Advanced' => array(
      'name' => 'Advanced',
      'settings' => array(
        'allow_user_conf' => 'f',
        'filters' => array(
          'filter/3' => 0,
          'filter/0' => 0,
        ),
        'ss' => '1',
        'min_rows' => '1',
        'excl_mode' => '1',
        'excl' => 'asset@node/*/content.edit-body
bead@node/*/content.edit-body
bead@node/add/bead.edit-body',
        'simple_incl' => '',
        'default' => 't',
        'show_toggle' => 'f',
        'popup' => 'f',
        'skin' => 'office2003',
        'uicolor' => 'color_bottom',
        'uicolor_textarea' => '<p>
	Click the <strong>UI Color Picker</strong> button to set your color preferences.</p>
',
        'uicolor_user' => 'default',
        'toolbar' => '[
    [\'Source\'],
    [\'Cut\',\'Copy\',\'Paste\',\'PasteText\',\'PasteFromWord\',\'-\',\'SpellChecker\',\'Scayt\'],
    [\'Undo\',\'Redo\',\'Find\',\'Replace\',\'-\',\'SelectAll\',\'RemoveFormat\'],
    [\'Image\',\'Flash\',\'Table\',\'HorizontalRule\',\'Smiley\',\'SpecialChar\',\'Iframe\'],
    \'/\',
    [\'Bold\',\'Italic\',\'Underline\',\'Strike\',\'-\',\'Subscript\',\'Superscript\',\'fmath_formula\'],
    [\'NumberedList\',\'BulletedList\',\'-\',\'Outdent\',\'Indent\',\'Blockquote\',\'CreateDiv\'],
    [\'JustifyLeft\',\'JustifyCenter\',\'JustifyRight\',\'JustifyBlock\',\'-\',\'BidiRtl\',\'BidiLtr\'],
    [\'Link\',\'Unlink\',\'Anchor\',\'Linkit\',\'LinkToNode\',\'LinkToMenu\'],
    \'/\',
    [\'Format\',\'Font\',\'FontSize\'],
    [\'TextColor\',\'BGColor\'],
    [\'Maximize\',\'ShowBlocks\'],
    [\'DrupalBreak\',\'DrupalPageBreak\']
]',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
        'custom_formatting' => 'f',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterOpen' => 'breakAfterOpen',
            'breakAfterClose' => 'breakAfterClose',
            'breakBeforeClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'theme',
        'css_path' => '',
        'css_style' => 'default',
        'styles_path' => '',
        'filebrowser' => 'ckfinder',
        'filebrowser_image' => '',
        'filebrowser_flash' => '',
        'UserFilesPath' => '%b%f/%u/',
        'UserFilesAbsolutePath' => '%d%b%f/%u/',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => '0',
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 't',
        'scayt_autoStartup' => 'f',
        'theme_config_js' => 't',
        'js_conf' => '',
        'loadPlugins' => array(
          'drupalbreaks' => array(
            'name' => 'drupalbreaks',
            'desc' => 'Plugin for inserting Drupal teaser and page breaks.',
            'path' => '%base_path%%plugin_dir%drupalbreaks/',
            'buttons' => array(
              'DrupalBreak' => array(
                'label' => 'DrupalBreak',
                'icon' => 'images/drupalbreak.png',
              ),
            ),
            'default' => 't',
          ),
          'fmath_formula' => array(
            'name' => 'fmath_formula',
            'desc' => 'Plugin file: fmath_formula',
            'path' => '%base_path%%plugin_dir%fmath_formula/',
            'buttons' => array(
              'fmath_formula' => array(
                'label' => 'fmath_formula',
                'icon' => 'fmath_formula.jpg',
              ),
            ),
            'default' => 'f',
          ),
          'tableresize' => array(
            'name' => 'tableresize',
            'desc' => 'Table Resize plugin',
            'path' => '%base_path%%editor_path%plugins/tableresize/',
            'buttons' => FALSE,
            'default' => 't',
          ),
        ),
        'excl_regex' => '#(?:^.*:asset@node/.*/content\\.edit-body$)|(?:^.*:bead@node/.*/content\\.edit-body$)|(?:^.*:bead@node/add/bead\\.edit-body$)#',
        'simple_incl_regex' => '',
      ),
      'roles' => array(
        'Site Admin' => 'Site Admin',
      ),
    ),
    'Asset_Editor' => array(
      'name' => 'Asset_Editor',
      'settings' => array(
        'allow_user_conf' => 'f',
        'filters' => array(
          'filter/3' => 0,
          'filter/0' => 0,
        ),
        'ss' => '2',
        'min_rows' => '1',
        'excl_mode' => '1',
        'excl' => 'bead@node/*/content.edit-body
bead@node/add/bead.edit-body
asset@node/*/content.edit-body',
        'simple_incl' => '',
        'default' => 't',
        'show_toggle' => 't',
        'popup' => 'f',
        'skin' => 'office2003',
        'uicolor' => 'default',
        'uicolor_textarea' => '<p>
	Click the <strong>UI Color Picker</strong> button to set your color preferences.</p>
',
        'uicolor_user' => 'default',
        'toolbar' => '[
    [\'Source\'],
    [\'Cut\',\'Copy\',\'Paste\',\'PasteText\',\'PasteFromWord\',\'-\',\'SpellChecker\',\'Scayt\'],
    [\'Undo\',\'Redo\',\'Find\',\'Replace\',\'-\',\'SelectAll\',\'RemoveFormat\'],
    [\'Image\',\'Flash\',\'Table\',\'HorizontalRule\',\'Smiley\',\'SpecialChar\'],
    \'/\',
    [\'Bold\',\'Italic\',\'Underline\',\'Strike\',\'-\',\'Subscript\',\'Superscript\',\'fmath_formula\'],
    [\'NumberedList\',\'BulletedList\',\'-\',\'Outdent\',\'Indent\'],
    [\'JustifyLeft\',\'JustifyCenter\',\'JustifyRight\',\'JustifyBlock\',\'-\',\'BidiRtl\',\'BidiLtr\'],
    [\'Link\',\'Unlink\',\'Anchor\'],
    \'/\',
    [\'Format\',\'Font\',\'FontSize\'],
    [\'TextColor\',\'BGColor\'],
    [\'Maximize\'],
]',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h2',
        'custom_formatting' => 'f',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterOpen' => 'breakAfterOpen',
            'breakAfterClose' => 'breakAfterClose',
            'breakBeforeClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'theme',
        'css_path' => '',
        'css_style' => 'default',
        'styles_path' => '',
        'filebrowser' => 'ckfinder',
        'filebrowser_image' => 'ckfinder',
        'filebrowser_flash' => 'ckfinder',
        'UserFilesPath' => '%b%f/%u/',
        'UserFilesAbsolutePath' => '%d%b%f/%u/',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => '0',
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 't',
        'scayt_autoStartup' => 'f',
        'theme_config_js' => 't',
        'js_conf' => '',
        'loadPlugins' => array(
          'drupalbreaks' => array(
            'name' => 'drupalbreaks',
            'desc' => 'Plugin for inserting Drupal teaser and page breaks.',
            'path' => '%base_path%%plugin_dir%drupalbreaks/',
            'buttons' => array(
              'DrupalBreak' => array(
                'label' => 'DrupalBreak',
                'icon' => 'images/drupalbreak.png',
              ),
            ),
            'default' => 't',
          ),
          'fmath_formula' => array(
            'name' => 'fmath_formula',
            'desc' => 'Plugin file: fmath_formula',
            'path' => '%base_path%%plugin_dir%fmath_formula/',
            'buttons' => array(
              'fmath_formula' => array(
                'label' => 'fmath_formula',
                'icon' => 'fmath_formula.jpg',
              ),
            ),
            'default' => 'f',
          ),
          'tableresize' => array(
            'name' => 'tableresize',
            'desc' => 'Table Resize plugin',
            'path' => '%base_path%%editor_path%plugins/tableresize/',
            'buttons' => FALSE,
            'default' => 't',
          ),
        ),
        'excl_regex' => '#(?:^.*:bead@node/.*/content\\.edit-body$)|(?:^.*:bead@node/add/bead\\.edit-body$)|(?:^.*:asset@node/.*/content\\.edit-body$)#',
        'simple_incl_regex' => '',
      ),
      'roles' => array(
        'Teacher' => 'Teacher',
      ),
    ),
    'CKEditor Global Profile' => array(
      'name' => 'CKEditor Global Profile',
      'settings' => array(
        'rank' => array(
          '0' => '3',
          '1' => '5',
          '2' => '4',
          '3' => '2',
        ),
        'excl_mode' => '1',
        'excl' => 'asset@node/*/content.edit-body
bead@node/*/content.edit-body
bead@node/add/bead.edit-body
multichoice@node/add/multichoice
multichoice@node/*/edit
',
        'simple_incl' => '*.edit-signature
admin/settings/site-information.*
admin/settings/site-maintenance.*
*.edit-page-help
*.edit-user-registration-help
*.edit-user-picture-guidelines
',
        'ckeditor_path' => '%m/ckeditor',
        'ckeditor_local_path' => '',
        'ckeditor_plugins_path' => '%m/plugins',
        'ckeditor_plugins_local_path' => '',
        'ckfinder_path' => '%m/ckfinder',
        'show_fieldnamehint' => 'f',
        'toolbar_wizard' => 't',
        'loadPlugins' => array(),
        'excl_regex' => '#(?:^.*:asset@node/.*/content\\.edit-body$)|(?:^.*:bead@node/.*/content\\.edit-body$)|(?:^.*:bead@node/add/bead\\.edit-body$)|(?:^.*:multichoice@node/add/multichoice\\..*$)|(?:^.*:multichoice@node/.*/edit\\..*$)#',
        'simple_incl_regex' => '#(?:^.*:.*@.*\\.edit-signature$)|(?:^.*:.*@admin/settings/site-information\\..*$)|(?:^.*:.*@admin/settings/site-maintenance\\..*$)|(?:^.*:.*@.*\\.edit-page-help$)|(?:^.*:.*@.*\\.edit-user-registration-help$)|(?:^.*:.*@.*\\.edit-user-picture-guidelines$)#',
      ),
      'roles' => array(),
    ),
    'Default' => array(
      'name' => 'Default',
      'settings' => array(
        'allow_user_conf' => 'f',
        'filters' => array(
          'filter/3' => 0,
          'filter/0' => 0,
        ),
        'ss' => '2',
        'min_rows' => '1',
        'excl_mode' => '1',
        'excl' => '
',
        'simple_incl' => '',
        'default' => 't',
        'show_toggle' => 't',
        'popup' => 'f',
        'skin' => 'office2003',
        'uicolor' => 'default',
        'uicolor_textarea' => '<p>
	Click the <strong>UI Color Picker</strong> button to set your color preferences.</p>
',
        'uicolor_user' => 'default',
        'toolbar' => '[
    [\'Source\'],
    [\'Cut\',\'Copy\',\'Paste\',\'PasteText\',\'PasteFromWord\',\'-\',\'SpellChecker\',\'Scayt\'],
    [\'Undo\',\'Redo\',\'Find\',\'Replace\',\'-\',\'SelectAll\',\'RemoveFormat\'],
    [\'Image\',\'Flash\',\'Table\',\'HorizontalRule\',\'Smiley\',\'SpecialChar\',\'Iframe\'],
    \'/\',
    [\'Bold\',\'Italic\',\'Underline\',\'Strike\',\'-\',\'Subscript\',\'Superscript\',\'fmath_formula\'],
    [\'NumberedList\',\'BulletedList\',\'-\',\'Outdent\',\'Indent\',\'Blockquote\',\'CreateDiv\'],
    [\'JustifyLeft\',\'JustifyCenter\',\'JustifyRight\',\'JustifyBlock\',\'-\',\'BidiRtl\',\'BidiLtr\'],
    [\'Link\',\'Unlink\',\'Anchor\',\'Linkit\',\'LinkToNode\',\'LinkToMenu\'],
    \'/\',
    [\'Format\',\'Font\',\'FontSize\'],
    [\'TextColor\',\'BGColor\'],
    [\'Maximize\',\'ShowBlocks\'],
    [\'DrupalBreak\',\'DrupalPageBreak\']
]',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
        'custom_formatting' => 'f',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterOpen' => 'breakAfterOpen',
            'breakAfterClose' => 'breakAfterClose',
            'breakBeforeClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'theme',
        'css_path' => '',
        'css_style' => 'default',
        'styles_path' => '',
        'filebrowser' => 'ckfinder',
        'filebrowser_image' => 'ckfinder',
        'filebrowser_flash' => 'ckfinder',
        'UserFilesPath' => '%b%f/%u/',
        'UserFilesAbsolutePath' => '%d%b%f/%u/',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => '0',
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 't',
        'scayt_autoStartup' => 'f',
        'theme_config_js' => 't',
        'js_conf' => '',
        'loadPlugins' => array(
          'drupalbreaks' => array(
            'name' => 'drupalbreaks',
            'desc' => 'Plugin for inserting Drupal teaser and page breaks.',
            'path' => '%base_path%%plugin_dir%drupalbreaks/',
            'buttons' => array(
              'DrupalBreak' => array(
                'label' => 'DrupalBreak',
                'icon' => 'images/drupalbreak.png',
              ),
            ),
            'default' => 't',
          ),
          'fmath_formula' => array(
            'name' => 'fmath_formula',
            'desc' => 'Plugin file: fmath_formula',
            'path' => '%base_path%%plugin_dir%fmath_formula/',
            'buttons' => array(
              'fmath_formula' => array(
                'label' => 'fmath_formula',
                'icon' => 'fmath_formula.jpg',
              ),
            ),
            'default' => 'f',
          ),
          'tableresize' => array(
            'name' => 'tableresize',
            'desc' => 'Table Resize plugin',
            'path' => '%base_path%%editor_path%plugins/tableresize/',
            'buttons' => FALSE,
            'default' => 't',
          ),
        ),
        'excl_regex' => '',
        'simple_incl_regex' => '',
      ),
      'roles' => array(
        'Site Admin' => 'Site Admin',
      ),
    ),
    'Quiz_Editor_3' => array(
      'name' => 'Quiz_Editor_3',
      'settings' => array(
        'allow_user_conf' => 'f',
        'filters' => array(
          'filter/3' => 0,
          'filter/0' => 0,
        ),
        'ss' => '2',
        'min_rows' => '1',
        'excl_mode' => '1',
        'excl' => 'multichoice@node/add/multichoice
multichoice@node/*/edit
',
        'simple_incl' => '',
        'default' => 't',
        'show_toggle' => 't',
        'popup' => 'f',
        'skin' => 'office2003',
        'uicolor' => 'default',
        'uicolor_textarea' => '<p>
	Click the <strong>UI Color Picker</strong> button to set your color preferences.</p>
',
        'uicolor_user' => 'default',
        'toolbar' => '[
    [\'Source\'],[\'Image\',\'SpecialChar\',\'Bold\',\'Italic\',\'Underline\',\'Subscript\',\'Superscript\',\'fmath_formula\'],
]',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h2',
        'custom_formatting' => 'f',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterOpen' => 'breakAfterOpen',
            'breakAfterClose' => 'breakAfterClose',
            'breakBeforeClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'theme',
        'css_path' => '',
        'css_style' => 'default',
        'styles_path' => '',
        'filebrowser' => 'ckfinder',
        'filebrowser_image' => 'ckfinder',
        'filebrowser_flash' => 'ckfinder',
        'UserFilesPath' => '%b%f/%u/',
        'UserFilesAbsolutePath' => '%d%b%f/%u/',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => '0',
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 't',
        'scayt_autoStartup' => 'f',
        'theme_config_js' => 't',
        'js_conf' => '',
        'loadPlugins' => array(
          'drupalbreaks' => array(
            'name' => 'drupalbreaks',
            'desc' => 'Plugin for inserting Drupal teaser and page breaks.',
            'path' => '%base_path%%plugin_dir%drupalbreaks/',
            'buttons' => array(
              'DrupalBreak' => array(
                'label' => 'DrupalBreak',
                'icon' => 'images/drupalbreak.png',
              ),
            ),
            'default' => 't',
          ),
          'fmath_formula' => array(
            'name' => 'fmath_formula',
            'desc' => 'Plugin file: fmath_formula',
            'path' => '%base_path%%plugin_dir%fmath_formula/',
            'buttons' => array(
              'fmath_formula' => array(
                'label' => 'fmath_formula',
                'icon' => 'fmath_formula.jpg',
              ),
            ),
            'default' => 'f',
          ),
          'tableresize' => array(
            'name' => 'tableresize',
            'desc' => 'Table Resize plugin',
            'path' => '%base_path%%editor_path%plugins/tableresize/',
            'buttons' => FALSE,
            'default' => 't',
          ),
        ),
        'excl_regex' => '#(?:^.*:multichoice@node/add/multichoice\\..*$)|(?:^.*:multichoice@node/.*/edit\\..*$)#',
        'simple_incl_regex' => '',
      ),
      'roles' => array(
        'Teacher' => 'Teacher',
      ),
    ),
  );
  return $data;
}
