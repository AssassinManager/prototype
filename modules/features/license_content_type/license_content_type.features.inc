<?php
/**
 * @file
 * license_content_type.features.inc
 */

/**
 * Implements hook_node_info().
 */
function license_content_type_node_info() {
  $items = array(
    'license_to_kill' => array(
      'name' => t('License to kill'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('License'),
      'help' => '',
    ),
  );
  return $items;
}
