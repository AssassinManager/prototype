<?php

/*
 * Adds the Kill buton bar for Players on their profiles
 */
function player_profile_am_custom_profile_alter(&$data) {

  global $user;
  $uid_viewed = $data['#account']->uid;
  if ($user->uid != $uid_viewed) return;

  if (!module_exists('target')) {
      drupal_set_message("Targeting module not found, could not display kill button.", "warning");
      return;
  }

  module_load_include('module', 'target', 'target');

  if (_check_player_status($user->uid) && !_check_player_unconfirmed_kill($user->uid)) {
    $data['_profile_kill_button'] = drupal_get_form('_profile_kill_button_enabled');
  } else {
    $data['_profile_kill_button'] = drupal_get_form('_profile_kill_button_disabled');
  }
}

function _profile_kill_button_enabled($form, &$form_state) {

  $form['kill_button'] = array(
                '#type' => 'button',
                '#name' => 'kill_button',
                '#value' => t('Target Eliminated'),
                '#ajax'  => array('callback' => 'target_kill'),
            );

  return $form;
}

function _profile_kill_button_disabled($form, &$form_state) {

  $form['kill_button'] = array(
                '#type' => 'button',
                '#name' => 'kill_button',
                '#disabled' => true,
                '#value' => t('Target Eliminated')
            );

  return $form;
}