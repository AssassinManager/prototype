<?php
/**
 * @file
 * prize_content_type.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function prize_content_type_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-prize-field_prize_description'
  $field_instances['node-prize-field_prize_description'] = array(
    'bundle' => 'prize',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_prize_description',
    'label' => 'Desciption',
    'required' => 1,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Desciption');

  return $field_instances;
}
