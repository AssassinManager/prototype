<?php

/**
 * implements hook_menu().
 */
 function target_menu() {
  $items = array();

  $items['admin/AM/Targeting/config'] = array(
    'title' => 'Targeting',
    'description' => 'Targeting defaults and msgs',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('target_defaults'),
    'access arguments' => array('administer site configuration'),
   );
  
  return $items;
}

function target_defaults() {
    $form = array();

    $form['no_valid_players'] = array(
        '#type' => 'textfield',
        '#title' => t('Generic "No Players" warning:'),
        '#default_value' => variable_get('no_valid_players', 'No available players.'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['one_assassin_left'] = array(
        '#type' => 'textfield',
        '#title' => t('When players are assigned targets but only one player is left alive:'),
        '#default_value' => variable_get('one_assassin_left', 'Only 1 player left, could he be THE winner?'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['targets_already_assigned'] = array(
        '#type' => 'textfield',
        '#title' => t('When an organizer wants to assign targets but all players already have some:'),
        '#default_value' => variable_get('targets_already_assigned', 'All targets already assigned'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['not_enough_targets'] = array(
        '#type' => 'textfield',
        '#title' => t('When targets are assigned but one assassin is left without target:'),
        '#default_value' => variable_get('not_enough_targets', 'No players left for an assassin without target.'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['all_targets_assigned'] = array(
        '#type' => 'textfield',
        '#title' => t('When all assassins have been successfully assigned targets:'),
        '#default_value' => variable_get('all_targets_assigned', 'All assassins have been assigned targets.'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['challenge_title'] = array(
        '#type' => 'textfield',
        '#title' => t('When a player denies having been killed, the message sent has the following subject:'),
        '#default_value' => variable_get('challenge_title', 'Elimination challenge'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['cannot_find_death_warrant'] = array(
        '#type' => 'textfield',
        '#title' => t('When a player\'s death warrant (a kill targeting him) is not found:'),
        '#default_value' => variable_get('cannot_find_death_warrant', 'Cannot find your death warrant... something must have went wrong. Please contact our staff for help'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['target_pending_elimination'] = array(
        '#type' => 'textfield',
        '#title' => t('When an assassin says he eliminated a target while still having to accpet his death:'),
        '#default_value' => variable_get('target_pending_elimination', 'Illegal action, please first accept or deny having been killed!'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['kill_deny_confirmation'] = array(
        '#type' => 'textfield',
        '#title' => t('When a player denies having been killed:'),
        '#default_value' => variable_get('kill_deny_confirmation', 'Got that. The assassin was notified, and the organizer was added to the loop to help settle this.'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    return system_settings_form($form);
}