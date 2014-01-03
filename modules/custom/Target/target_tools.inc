<?php

/**
 * Look for kills which target the given users
 * and return a list of those users
 */
function _target_users_death_warrants($uids) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'kill')
            ->propertyCondition('status', 1);

    $kills = $query->execute();

    if (count($kills) < 1) return array();
    $kills = node_load_multiple(array_keys($kills['node']));
    $targeted_players = array();
    foreach ($kills as $key => $value) {
      $uid = $value->field_target['und'][0]['target_id'];
      if (in_array($uid, $uids)) $targeted_players[] = $uid;
    }
    return $targeted_players;
}

/**
 * Look for a kill which targets the given user
 * and return the nid if it is found
 */
function _target_death_warrant($uid) {
  $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'kill')
            ->propertyCondition('status', 1)
            ->fieldCondition('field_target', 'target_id', array($uid));

    $warrant = $query->execute();

    if (count($warrant) < 1) return array();
    return array_keys($warrant['node']);
}

/**
 * Check if players is alive, not suspended & not targeted
 * and return true if valid, false if not
 */
function _check_player_status($uid) {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user')
        ->propertyCondition('uid', $uid, '=')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_suspended', 'value', array(0))
        ->fieldCondition('field_alive', 'value', array(1));
  $entities = $query->execute();

  if (count($entities) < 1) return false;
  if (count(_target_death_warrant($uid)) > 0) return false;

  return true;
}

/**
 * Check if players is alive and not suspended
 * and return true if valid, false if not
 */
function _check_player_valid($uid) {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user')
        ->propertyCondition('uid', $uid, '=')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_suspended', 'value', array(0))
        ->fieldCondition('field_alive', 'value', array(1));
  $entities = $query->execute();

  if (count($entities) < 1) return false;

  return true;
}

/**
 * Check if player has unconfirmed kill
 * and return true if at least 1 was found
 */
function _check_player_unconfirmed_kill($uid) {

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'kill')
            ->propertyCondition('status', 1)
            ->fieldCondition('field_confirmed', 'value', 0)
            ->fieldCondition('field_assassin', 'target_id', $uid);

    $unconfirmedKills = $query->execute();

    if (count($unconfirmedKills) > 0) return true;

    return false;
}

/**
 * Filter users to get those without targets
 */
function _users_without_target($users) {
  $result = array();

  foreach($users as $uid => $user) {
    if(!isset($user->field_current_target['und']) || count($user->field_current_target['und']) < 1) {
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
    if(!isset($user->field_current_target['und']) || count($user->field_current_target['und']) < 1) {
      continue;
    }
    $newUid = $user->field_current_target['und'][0]['target_id'];
    if (in_array($newUid, array_keys($users))) $result[$newUid] = $users[$newUid];
    else                                       $result[$newUid] = user_load($newUid);
  }
  return $result;
}

/**
 * Create kill node
 */
function _target_create_kill($assassin_uid, $target_uid) {
  $node = new stdclass();
    $node->type = 'kill';
    node_object_prepare($node);

    $node->language = 'und';
    $node->author = $assassin_uid;

    $node->title = 'Kill-' . $assassin_uid . "vs" . $target_uid;
    $node->field_confirmed['und'][0]['value'] = 0;

    $node->field_target['und'][0]['target_id'] = $target_uid;
    $node->field_assassin['und'][0]['target_id'] = $assassin_uid;

    node_save($node);
}