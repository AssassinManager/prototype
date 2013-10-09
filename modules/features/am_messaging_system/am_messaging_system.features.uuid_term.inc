<?php
/**
 * @file
 * am_messaging_system.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function am_messaging_system_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Suspension',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '173840d0-e19c-4036-a6cd-0dfaa9616401',
    'vocabulary_machine_name' => 'message_types',
  );
  $terms[] = array(
    'name' => 'kill issue',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '23ebc2e8-84cd-4551-b3c0-391bf6125baf',
    'vocabulary_machine_name' => 'message_types',
  );
  $terms[] = array(
    'name' => 'Information',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '47d4ac7f-2587-4c88-9750-2bbe82b67df1',
    'vocabulary_machine_name' => 'message_types',
  );
  return $terms;
}
