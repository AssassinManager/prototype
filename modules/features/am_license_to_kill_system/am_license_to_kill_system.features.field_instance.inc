<?php
/**
 * @file
 * am_license_to_kill_system.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function am_license_to_kill_system_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-license_to_kill-field_code'
  $field_instances['node-license_to_kill-field_code'] = array(
    'bundle' => 'license_to_kill',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_code',
    'label' => 'Code',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 10,
      ),
      'type' => 'text_textfield',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Code');

  return $field_instances;
}
