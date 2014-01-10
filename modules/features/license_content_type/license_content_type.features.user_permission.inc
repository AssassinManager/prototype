<?php
/**
 * @file
 * license_content_type.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function license_content_type_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create license_to_kill content'.
  $permissions['create license_to_kill content'] = array(
    'name' => 'create license_to_kill content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'Player' => 'Player',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any license_to_kill content'.
  $permissions['delete any license_to_kill content'] = array(
    'name' => 'delete any license_to_kill content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'Player' => 'Player',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own license_to_kill content'.
  $permissions['delete own license_to_kill content'] = array(
    'name' => 'delete own license_to_kill content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any license_to_kill content'.
  $permissions['edit any license_to_kill content'] = array(
    'name' => 'edit any license_to_kill content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own license_to_kill content'.
  $permissions['edit own license_to_kill content'] = array(
    'name' => 'edit own license_to_kill content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'Player' => 'Player',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
