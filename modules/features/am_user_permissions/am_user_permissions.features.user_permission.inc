<?php
/**
 * @file
 * user_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function am_user_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: access comments.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access user profiles.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: create game content.
  $permissions['create game content'] = array(
    'name' => 'create game content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create license_to_kill content.
  $permissions['create license_to_kill content'] = array(
    'name' => 'create license_to_kill content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create message content.
  $permissions['create message content'] = array(
    'name' => 'create message content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: create page content.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create prize content.
  $permissions['create prize content'] = array(
    'name' => 'create prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create profile content.
  $permissions['create profile content'] = array(
    'name' => 'create profile content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any game content.
  $permissions['delete any game content'] = array(
    'name' => 'delete any game content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any license_to_kill content.
  $permissions['delete any license_to_kill content'] = array(
    'name' => 'delete any license_to_kill content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any message content.
  $permissions['delete any message content'] = array(
    'name' => 'delete any message content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any page content.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any prize content.
  $permissions['delete any prize content'] = array(
    'name' => 'delete any prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any profile content.
  $permissions['delete any profile content'] = array(
    'name' => 'delete any profile content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own game content.
  $permissions['delete own game content'] = array(
    'name' => 'delete own game content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own license_to_kill content.
  $permissions['delete own license_to_kill content'] = array(
    'name' => 'delete own license_to_kill content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own message content.
  $permissions['delete own message content'] = array(
    'name' => 'delete own message content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own page content.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own prize content.
  $permissions['delete own prize content'] = array(
    'name' => 'delete own prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own profile content.
  $permissions['delete own profile content'] = array(
    'name' => 'delete own profile content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete revisions.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any game content.
  $permissions['edit any game content'] = array(
    'name' => 'edit any game content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any license_to_kill content.
  $permissions['edit any license_to_kill content'] = array(
    'name' => 'edit any license_to_kill content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any message content.
  $permissions['edit any message content'] = array(
    'name' => 'edit any message content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any page content.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any prize content.
  $permissions['edit any prize content'] = array(
    'name' => 'edit any prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any profile content.
  $permissions['edit any profile content'] = array(
    'name' => 'edit any profile content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own comments.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'Organizer' => 'Organizer',
      'Player' => 'Player',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: edit own game content.
  $permissions['edit own game content'] = array(
    'name' => 'edit own game content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own license_to_kill content.
  $permissions['edit own license_to_kill content'] = array(
    'name' => 'edit own license_to_kill content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own message content.
  $permissions['edit own message content'] = array(
    'name' => 'edit own message content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own page content.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own prize content.
  $permissions['edit own prize content'] = array(
    'name' => 'edit own prize content',
    'roles' => array(
      'Organizer' => 'Organizer',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own profile content.
  $permissions['edit own profile content'] = array(
    'name' => 'edit own profile content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: post comments.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: revert revisions.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: skip comment approval.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: view revisions.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
