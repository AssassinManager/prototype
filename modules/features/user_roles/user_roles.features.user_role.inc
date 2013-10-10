<?php
/**
 * @file
 * user_roles.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function user_roles_user_default_roles() {
  $roles = array();

  // Exported role: Organizer.
  $roles['Organizer'] = array(
    'name' => 'Organizer',
    'weight' => 4,
  );

  // Exported role: Player.
  $roles['Player'] = array(
    'name' => 'Player',
    'weight' => 3,
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  return $roles;
}
