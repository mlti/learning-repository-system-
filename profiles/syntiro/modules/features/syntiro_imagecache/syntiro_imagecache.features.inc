<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function syntiro_imagecache_imagecache_default_presets() {
  $items = array(
    'assetimage' => array(
      'presetname' => 'assetimage',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '628',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'autocomplete_user_profile_image_32' => array(
      'presetname' => 'autocomplete_user_profile_image_32',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '32',
            'height' => '32',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'dis_rev_com_image' => array(
      'presetname' => 'dis_rev_com_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '63px',
            'height' => '63px',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'dis_rev_com_image2' => array(
      'presetname' => 'dis_rev_com_image2',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '48px',
            'height' => '48px',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'header_top_user_image_20' => array(
      'presetname' => 'header_top_user_image_20',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '20',
            'height' => '20',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'user_profile_image' => array(
      'presetname' => 'user_profile_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '85px',
            'height' => '85px',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'user_profile_image_123' => array(
      'presetname' => 'user_profile_image_123',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '123',
            'height' => '103',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'user_profile_image_146' => array(
      'presetname' => 'user_profile_image_146',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '146px',
            'height' => '146px',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'user_profile_image_188' => array(
      'presetname' => 'user_profile_image_188',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '188px',
            'height' => '188px',
            'upscale' => 1,
          ),
        ),
      ),
    ),
    'user_profile_image_37' => array(
      'presetname' => 'user_profile_image_37',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '37',
            'height' => '37',
            'upscale' => 0,
          ),
        ),
      ),
    ),
    'user_profile_image_53' => array(
      'presetname' => 'user_profile_image_53',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '53px',
            'height' => '53px',
          ),
        ),
      ),
    ),
  );
  return $items;
}
