<?php
/**
 * @file
 * kill_content_type.features.inc
 */

/**
 * Implements hook_node_info().
 */
function kill_content_type_node_info() {
  $items = array(
    'kill' => array(
      'name' => t('Kill'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
