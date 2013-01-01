<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Weekly preview'),
  'description' => t('Weekly expenses preview.'),
  'single' => TRUE,
  'category' => 'Scrimp',
);

function scrimp_weekly_preview_content_type_render($subtype, $conf, $args, $context) {
  global $user;
  if (empty($user->uid)) {
  	return;
  }	
  
  $block = new stdClass();
  $block->title = t('Weekly preview');
  $block->module = 'scrimp';

  $now = time();
  $start = $now - 86400 * 6;
  
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'expense')
    ->fieldCondition('field_date', 'value', array($start, $now), 'BETWEEN')
    ->execute();
  if (empty($result['node'])) {
  	return;
  }
  
  $dates_data = array();
  $category_data = array();
  foreach (node_load_multiple(array_keys($result['node'])) as $node) {
  	$wrapper = entity_metadata_wrapper('node', $node);
	$day = date('Y-m-d', $wrapper->field_date->value()); 
	if (!array_key_exists($day, $dates_data)) {
	  $dates_data[$day] = array('total' => 0);
	}
	
	$tid = $wrapper->field_category->getIdentifier();
	$name = $wrapper->field_category->label();
	if (empty($dates_data[$day][$name])) {
      $dates_data[$day][$name] = 0;
	}
	if (empty($category_data[$name])) {
      $category_data[$name] = 0;
	}
	
	$amount = $wrapper->field_price->amount->value();

	$dates_data[$day]['total'] += $amount;
	$dates_data[$day][$name] += $amount / 100;
	// $weekly_data['total'] += $amount;
	$category_data[$name] += $amount / 100;
  }

  $header = array();
  $row = array();
  for ($day = $start; $day <= $now; $day += 86400) {
  	$date = date('Y-m-d', $day);
	$header[] = $date;
  	$cell = array_key_exists($date, $dates_data) ? $dates_data[$date]['total'] : '';
    $row[] = commerce_currency_format($cell, commerce_default_currency());
  }  
  $block->content = theme('table', array('header' => $header, 'rows' => array($row)));
  
  $chart = array(
  	'#title' => '',
    '#chart_id' => 'weekly_categories',
    '#type' => CHART_TYPE_PIE_CONCENTRIC,
    '#data' => $category_data,
    '#legends' => array_keys($category_data),
  );

  $block->content .= theme('chart', array('chart' => $chart));
  return $block;

}

function scrimp_weekly_preview_content_type_edit_form($form, &$form_state) {
  return $form;
}
