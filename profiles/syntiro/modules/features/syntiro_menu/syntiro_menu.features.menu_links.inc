<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function syntiro_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-bridge:bridge/myassets
  $menu_links['menu-bridge:bridge/myassets'] = array(
    'menu_name' => 'menu-bridge',
    'link_path' => 'bridge/myassets',
    'router_path' => 'bridge/myassets',
    'link_title' => 'Assets',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: menu-bridge:bridge/myassignments
  $menu_links['menu-bridge:bridge/myassignments'] = array(
    'menu_name' => 'menu-bridge',
    'link_path' => 'bridge/myassignments',
    'router_path' => 'bridge/myassignments',
    'link_title' => 'Assignments',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Exported menu link: menu-bridge:bridge/mybookmarks
  $menu_links['menu-bridge:bridge/mybookmarks'] = array(
    'menu_name' => 'menu-bridge',
    'link_path' => 'bridge/mybookmarks',
    'router_path' => 'bridge/mybookmarks',
    'link_title' => 'Bookmarks',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: menu-bridge:bridge/mycurriculum
  $menu_links['menu-bridge:bridge/mycurriculum'] = array(
    'menu_name' => 'menu-bridge',
    'link_path' => 'bridge/mycurriculum',
    'router_path' => 'bridge/mycurriculum',
    'link_title' => 'Playlists',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: menu-bridge:bridge/mymars
  $menu_links['menu-bridge:bridge/mymars'] = array(
    'menu_name' => 'menu-bridge',
    'link_path' => 'bridge/mymars',
    'router_path' => 'bridge/mymars',
    'link_title' => 'MARS',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: menu-bridge:bridge/myrecommendations
  $menu_links['menu-bridge:bridge/myrecommendations'] = array(
    'menu_name' => 'menu-bridge',
    'link_path' => 'bridge/myrecommendations',
    'router_path' => 'bridge/myrecommendations',
    'link_title' => 'Recommendations',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: menu-footer-menu:<front>
  $menu_links['menu-footer-menu:<front>'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Setting',
    'options' => array(
      'attributes' => array(
        'title' => 'Setting',
      ),
    ),
    'module' => 'menu',
    'hidden' => '1',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: menu-footer-menu:communities/list
  $menu_links['menu-footer-menu:communities/list'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'communities/list',
    'router_path' => 'communities/list',
    'link_title' => 'Communities',
    'options' => array(
      'attributes' => array(
        'title' => 'Registration',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: menu-footer-menu:messages/inbox
  $menu_links['menu-footer-menu:messages/inbox'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'messages/inbox',
    'router_path' => 'messages',
    'link_title' => 'Messages',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: menu-footer:node/84
  $menu_links['menu-footer:node/84'] = array(
    'menu_name' => 'menu-footer',
    'link_path' => 'node/84',
    'router_path' => 'node/%',
    'link_title' => 'Conditions of Use',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: primary-links:assignment/reports/list
  $menu_links['primary-links:assignment/reports/list'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'assignment/reports/list',
    'router_path' => 'assignment/reports/list',
    'link_title' => 'Reports',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: primary-links:bridge/myassets
  $menu_links['primary-links:bridge/myassets'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'bridge/myassets',
    'router_path' => 'bridge/myassets',
    'link_title' => 'Assets',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: primary-links:bridge/mycurriculum
  $menu_links['primary-links:bridge/mycurriculum'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'bridge/mycurriculum',
    'router_path' => 'bridge/mycurriculum',
    'link_title' => 'Playlists',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: primary-links:communities/list
  $menu_links['primary-links:communities/list'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'communities/list',
    'router_path' => 'communities/list',
    'link_title' => 'Communities',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: primary-links:messages/inbox
  $menu_links['primary-links:messages/inbox'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'messages/inbox',
    'router_path' => 'messages',
    'link_title' => 'Message',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: secondary-links:node/84
  $menu_links['secondary-links:node/84'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/84',
    'router_path' => 'node/%',
    'link_title' => 'Privacy Notice',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Assets');
  t('Assignments');
  t('Bookmarks');
  t('Communities');
  t('Conditions of Use');
  t('MARS');
  t('Message');
  t('Messages');
  t('Playlists');
  t('Privacy Notice');
  t('Recommendations');
  t('Reports');
  t('Setting');


  return $menu_links;
}
