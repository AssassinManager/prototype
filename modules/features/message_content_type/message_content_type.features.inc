<?php
/**
 * @file
 * message_content_type.features.inc
 */

/**
 * Implements hook_node_info().
 */
function message_content_type_node_info() {
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
