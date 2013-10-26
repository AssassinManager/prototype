<?php
/**
 * @file
 * user_fields.features.inc
 */

//Add

/**
 * Implements hook_node_info().
 */
function user_fields_node_info() {
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
