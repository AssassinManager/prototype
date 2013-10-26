<?php
/**
 * @file
 * kill_content_type.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function kill_content_type_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create kill content'.
  $permissions['create kill content'] = array(
    'name' => 'create kill content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any kill content'.
  $permissions['delete any kill content'] = array(
    'name' => 'delete any kill content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own kill content'.
  $permissions['delete own kill content'] = array(
    'name' => 'delete own kill content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any kill content'.
  $permissions['edit any kill content'] = array(
    'name' => 'edit any kill content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own kill content'.
  $permissions['edit own kill content'] = array(
    'name' => 'edit own kill content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
