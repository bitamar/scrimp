<?php
/**
 * @file
 * scrimp.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function scrimp_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function scrimp_node_info() {
  $items = array(
    'expense' => array(
      'name' => t('Expense'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
