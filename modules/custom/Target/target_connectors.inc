<?php

function target_kill() {
  global $user;
  $user = user_load($user->uid);

  if (!isset($user->field_current_target['und']) || 
    count($user->field_current_target['und']) < 1) {
    drupal_set_message("No assigned target!", 'warning');
    return;
  }

  if (_check_player_unconfirmed_kill($user->uid)) {
    drupal_set_message(variable_get('target_pending_elimination'), 'warning');
    return;
  }

  $target_uid = $user->field_current_target['und'][0]['target_id'];
    _target_create_kill($user->uid, $target_uid);
}

function target_deny() {
  global $user;

  $deathWarrants = _target_death_warrant($user->uid);
  if (count($deathWarrants) < 1) {
    drupal_set_message(variable_get('cannot_find_death_warrant'), 'error');
    return;
  }

  if (!module_exists('messaging')) {
    drupal_set_message("Cannot find messaging module, you cannot challenge a kill without communication!", 'error');
    return;
  }

  $user = user_load($user->uid);
  $target_uid = $user->field_current_target['und'][0]['target_id'];

  module_load_include('module', 'messaging', 'messaging');
  _messaging_am_deny_kill($user->uid, $target_uid);

  drupal_set_message(variable_get('kill_deny_confirmation'), 'status');
}

function target_accept() {
  global $user;

  $deathWarrants = _target_death_warrant($user->uid);
  if (count($deathWarrants) < 1) {
    drupal_set_message(variable_get('cannot_find_death_warrant'), 'error');
    return;
  }

  // Update the kill node
  $kill = node_load($deathWarrants[0]);
  $kill->field_confirmed['und'][0]['value'] = 1;
  node_save($kill);
}