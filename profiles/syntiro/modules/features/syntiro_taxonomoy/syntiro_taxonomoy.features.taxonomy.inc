<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function syntiro_taxonomoy_taxonomy_default_vocabularies() {
  return array(
    'subject' => array(
      'name' => 'Subject',
      'description' => 'Subject ',
      'help' => 'Enter a comma separated list of words',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '0',
      'required' => '0',
      'tags' => '1',
      'module' => 'taxonomy',
      'weight' => '-7',
      'nodes' => array (
        'asset' => 'asset',
        'bead' => 'bead',
        'curriculum' => 'curriculum',
        'profile' => 'profile',
      ),
    ),
    'discipline' => array(
      'name' => 'Discipline',
      'description' => 'Based on Discipline we have to generate mars page',
      'help' => 'Enter a comma separated list of words',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '0',
      'required' => '0',
      'tags' => '1',
      'module' => 'taxonomy',
      'weight' => '-5',
      'nodes' => array (
        'profile' => 'profile',
      ),
    ),
    'class_gragde' => array(
     'name' => 'Class/Grade',
     'description' => 'Class or Grade',
     'help' => 'Enter a comma separated list of words',
     'relations' => '1',
     'hierarchy' => '0',
     'multiple' => '0',
     'required' => '1',
     'tags' => '1',
     'module' => 'taxonomy',
     'weight' => '-6',
     'nodes' => array (
        'profile' => 'profile',
      ),
    ),
    'academic_level' => array(
      'name' => 'Academic Level',
      'description' => 'audience',
      'help' => 'eg. K12, Higher Ed...',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '0',
      'required' => '0',
      'tags' => '1',
      'module' => 'taxonomy',
      'weight' => '-9',
      'nodes' => array (
        'asset' => 'asset',
        'bead' => 'bead',
        'curriculum' => 'curriculum',
      ),
    ),
    'asset_category' => array(
      'name' => 'Asset Category',
      'description' => 'Category',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '0',
      'required' => '0',
      'tags' => '1',
      'module' => 'taxonomy',
      'weight' => '-8',
      'nodes' => array (
        'asset' => 'asset',
        'bead' => 'bead',
      ),
    ),
    'tags' => array(
      'name' => 'Tags',
      'description' => '',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '0',
      'required' => '0',
      'tags' => '1',
      'module' => 'taxonomy',
      'weight' => '-10',
      'nodes' => array (
        'asset' => 'asset',
        'bead' => 'bead',
        'curriculum' => 'curriculum',
      ),
    ),
    'mlr' => array(
      'name' => 'Mlr',
      'description' => 'Mlr standard',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '1',
      'multiple' => '1',
      'required' => '0',
      'tags' => '0',
      'module' => 'features_mlr',
      'weight' => '0',
      'nodes' => array(
        'asset' => 'asset',
      ),
    ), 
  );
}

