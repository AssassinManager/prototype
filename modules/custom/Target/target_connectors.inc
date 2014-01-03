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
    drupal_set_message("Target still pending elimination confirmation!", 'warning');
    return;
  }

  $target_uid = $user->field_current_target['und'][0]['target_id'];
    _target_create_kill($user->uid, $target_uid);
}

function target_deny() {
  global $user;

  if (count(_target_death_warrant($user->uid)) < 1) {
    drupal_set_message("Cannot find your death warrant... something must have went wrong. Please contact our staff for help.", 'warning');
    return;
  }

  $user = user_load($user->uid);
  $target_uid = $user->field_current_target['und'][0]['target_id'];

  module_load_include('module', 'messaging', 'messaging');
  messaging_deny_kill($target_uid, $user->uid);

  drupal_set_message("Got that, the organizer was added to the loop to help set this straight.");
}

function target_accept() {
  global $user;

  $deathWarrants = _target_death_warrant($user->uid);
  if (count($deathWarrants) < 1) {
    drupal_set_message("Cannot find your death warrant... something must have went wrong. Please contact our staff for help.", 'warning');
    return;
  }

  $kill = node_load($deathWarrants[0]);
  $kill->field_confirmed['und'][0]['value'] = 1;
  node_save($kill);

  // Assigning new target
  $user = user_load($user->uid);
  unset($user->field_current_target['und']);
}