<?php

/**
 * Check all kill nodes for users found
 */
function _assassinations_death_warrants($uids) {
  $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'kill')
            ->propertyCondition('status', 1)
            ->fieldCondition('field_target', 'target_id', $uids);

    $warrants = $query->execute();

    if (count($warrants) < 1) return array();
    $warrant_nodes = node_load_multiple(array_keys($warrants['node']));
    unset($warrants);
    foreach ($warrant_nodes as $key => $value) {
      $warrants[] = $value->field_target['und'][0]['target_id'];
    }
    return $warrants;
}

/**
 * Get all users who are Players and alive (& not suspended)
 */
function _get_users_alive_and_well() {
  $uids = array();
  $users = array();
  $role = user_role_load_by_name('Player');

  $result = db_select('users_roles', 'ur')
          ->fields('ur', array('uid'))
          ->condition('rid', $role->rid, '=')
          ->execute();

  foreach ($result as $record) {
    $uids[] = $record->uid;
  };

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user')
        ->propertyCondition('uid', $uids, 'IN')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_suspended', 'value', array(0))
        ->fieldCondition('field_alive', 'value', array(1));
  $entities = $query->execute();
  if (count($entities) < 1) return array();

  foreach ($entities['user'] as $key => $value) {
    $users[] = $key;
  }

  $deathWarrants = _assassinations_death_warrants($users);
  if (count($deathWarrants) < 1) return $users;

  foreach ($users as $key => $uid) {
    if (in_array($uid, $deathWarrants)) unset($users[$key]);
  }
  return $users;
}

/**
 * Filter users to get those without targets
 */
function _users_without_target($users) {
  $result = array();

  foreach($users as $uid => $user) {
    if(!isset($user->field_current_target['und']) || 
      count($user->field_current_target['und']) < 1) {
      $result[$uid] = $user;
    }
  }
  return $result;
}
/**
 * Filter users to get those targeted
 */
function _users_targeted($users) {
  $result = array();
  foreach($users as $uid => $user) {
    if(!isset($user->field_current_target['und']) || 
      count($user->field_current_target['und']) < 1) {
      continue;
    }
    $newUid = $user->field_current_target['und'][0]['target_id'];
    $result[$newUid] = user_load($newUid);
  }
  return $result;
}

/**
 * Main target expert
 */
function assassinations_assign_targets() {

  // Get all the players
  $users = _get_users_alive_and_well();
  if (count($users) < 1) {
    drupal_set_message('No users alive or at all!', 'warning');
    return;
  } 
  else if (count($users) == 1) {
    $theUser = user_load(array_shift(array_values($users)));
    $name = $theUser->field_first_name['und'][0]['value'] . ' ' . $theUser->field_last_name['und'][0]['value'];
    drupal_set_message(t('Only 1 player (' . $name . ') left alive!'), 'warning');
    return;
  }

  $users = user_load_multiple($users);

  // Find those without targets
  $users_without_target = _users_without_target($users);
  if (count($users_without_target) < 1) {
    drupal_set_message('All targets already assigned');
    return;
  }

  // Find those untargeted
  $users_targeted = _users_targeted($users);
  $users_not_targeted = array();
  foreach ($users as $uid => $user) {
    if (in_array($uid, array_keys($users_targeted))) continue;
    $users_not_targeted[$uid] = $user;
  }
  if (count($users_not_targeted) < 1) {
    drupal_set_message('No possible targets');
    return;
  }

  // Assign targets
  foreach ($users_without_target as $uid => $user) {

    if (count($users_not_targeted) < 1) {
      drupal_set_message('No possible targets');
      return;
    }

    $target = array_pop($users_not_targeted);
    $user->field_current_target['und'][0]['target_id'] = $target->uid;
    user_save($user);
  }
  drupal_set_message(t('All targets assigned'));
}