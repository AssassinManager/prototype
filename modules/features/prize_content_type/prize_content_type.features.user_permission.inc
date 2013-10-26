<?php
/**
 * @file
 * prize_content_type.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function prize_content_type_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create prize content'.
  $permissions['create prize content'] = array(
    'name' => 'create prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any prize content'.
  $permissions['delete any prize content'] = array(
    'name' => 'delete any prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own prize content'.
  $permissions['delete own prize content'] = array(
    'name' => 'delete own prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any prize content'.
  $permissions['edit any prize content'] = array(
    'name' => 'edit any prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own prize content'.
  $permissions['edit own prize content'] = array(
    'name' => 'edit own prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
