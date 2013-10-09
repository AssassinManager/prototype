<?php
/**
 * @file
 * am_players_and_organizers.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function am_players_and_organizers_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function am_players_and_organizers_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function am_players_and_organizers_node_info() {
  $items = array(
    'profile' => array(
      'name' => t('Profile'),
      'base' => 'node_content',
      'description' => t('Automatically created and updated profile
node path = base_url/user-uid'),
      'has_title' => '1',
      'title_label' => t('User'),
      'help' => '',
    ),
  );
  return $items;
}
