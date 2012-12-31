<?php
/**
 * @file
 * scrimp.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function scrimp_taxonomy_default_vocabularies() {
  return array(
    'categories' => array(
      'name' => 'Categories',
      'machine_name' => 'categories',
      'description' => 'Expense categories',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'payment_types' => array(
      'name' => 'Payment types',
      'machine_name' => 'payment_types',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'things' => array(
      'name' => 'Things',
      'machine_name' => 'things',
      'description' => 'The thing that caused the expense',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
