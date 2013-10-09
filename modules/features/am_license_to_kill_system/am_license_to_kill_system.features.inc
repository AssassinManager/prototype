<?php
/**
 * @file
 * am_license_to_kill_system.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function am_license_to_kill_system_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function am_license_to_kill_system_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function am_license_to_kill_system_node_info() {
  $items = array(
    'license_to_kill' => array(
      'name' => t('License to kill'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
