<?php

/*
 * Adds the button bar for Players on their profiles
 */
function player_profile_am_custom_profile_alter(&$data) {

  global $user;
  $uid_viewed = $data['#account']->uid;
  if ($user->uid != $uid_viewed) return;

  if (!module_exists('target')) {
      drupal_set_message("Targeting module not found, could not display kill button.", "warning");
      return;
  }
  module_load_include('module', 'am_tools', 'am_tools');
  if (!am_check_game_started()) return;

  module_load_include('module', 'target', 'target');

  if (!_check_player_valid($user->uid)) return;
  
  else if (_check_player_unconfirmed_kill($user->uid)) {    
    $data['_profile_kill_button'] = drupal_get_form('_profile_kill_button_disabled');
  } 

  else if (_target_pending_death_warrant($user->uid)) {
    $target_uid = $data['#account']->field_current_target['und'][0]['target_id'];
    if (_messaging_am_find_reply($user->uid, $target_uid)) {
      $data['_profile_deny_button'] = drupal_get_form('_profile_deny_button_disabled');
    }
    else {
      $data['_profile_deny_button'] = drupal_get_form('_profile_deny_button_enabled');
    }
    $data['_profile_accept_button'] = drupal_get_form('_profile_accept_button_enabled');
    $data['_profile_kill_notice'] = drupal_get_form('_profile_kill_notice');
  } 

  else {
    $data['_profile_kill_button'] = drupal_get_form('_profile_kill_button_enabled');
  }
}

function _profile_kill_notice($form, &$form_state) {

  $form['kill_notice'] = array(
					'#type' => 'item',
					'#title' => t('Your assassin claims to have eliminated you:'),
            );

  return $form;
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

function _profile_accept_button_enabled($form, &$form_state) {

  $form['accept_button'] = array(
                '#type' => 'button',
                '#name' => 'accept_button',
                '#value' => t('I Confirm I was eliminated'),
                '#ajax'  => array('callback' => 'target_accept'),
            );

  return $form;
}

function _profile_deny_button_enabled($form, &$form_state) {

  $form['deny_button'] = array(
                '#type' => 'button',
                '#name' => 'deny_button',
                '#value' => t('No, I was not eliminated!'),
                '#ajax'  => array('callback' => 'target_deny'),
            );

  return $form;
}

function _profile_deny_button_disabled($form, &$form_state) {

  $form['deny_button'] = array(
                '#type' => 'button',
                '#name' => 'deny_button',
                '#disabled' => true,
                '#value' => t('No, I was not eliminated!'),
            );

  return $form;
}