<?php
/**
 * @file
 * am_messaging_system.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function am_messaging_system_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function am_messaging_system_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function am_messaging_system_node_info() {
  $items = array(
    'message' => array(
      'name' => t('Message'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Subject'),
      'help' => '',
    ),
  );
  return $items;
}
