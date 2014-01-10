<?php
/**
 * @file
 * prize_content_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function prize_content_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function prize_content_type_node_info() {
  $items = array(
    'prize' => array(
      'name' => t('Prize'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Prize'),
      'help' => '',
    ),
  );
  return $items;
}
