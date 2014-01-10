<?php
/**
 * @file
 * message_content_type.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function message_content_type_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create message content'.
  $permissions['create message content'] = array(
    'name' => 'create message content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'Player' => 'Player',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any message content'.
  $permissions['delete any message content'] = array(
    'name' => 'delete any message content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own message content'.
  $permissions['delete own message content'] = array(
    'name' => 'delete own message content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any message content'.
  $permissions['edit any message content'] = array(
    'name' => 'edit any message content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own message content'.
  $permissions['edit own message content'] = array(
    'name' => 'edit own message content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'Player' => 'Player',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
