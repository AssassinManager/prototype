<?php
/**
 * @file
 * am_messaging_system.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function am_messaging_system_taxonomy_default_vocabularies() {
  return array(
    'message_types' => array(
      'name' => 'Message types',
      'machine_name' => 'message_types',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
