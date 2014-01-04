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

    $form['no_valid_users'] = array(
        '#type' => 'textfield',
        '#title' => t('No valid assassins (message)'),
        '#default_value' => variable_get('no_valid_users'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['no_valid_players'] = array(
        '#type' => 'textfield',
        '#title' => t('No assassins in condition to get to work (message)'),
        '#default_value' => variable_get('no_valid_players'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['one_assassin_left'] = array(
        '#type' => 'textfield',
        '#title' => t('Only one assassin left in the game (message)'),
        '#default_value' => variable_get('one_assassin_left'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['targets_already_assigned'] = array(
        '#type' => 'textfield',
        '#title' => t('Targets already assigned (message)'),
        '#default_value' => variable_get('targets_already_assigned'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['assassin_singled_out'] = array(
        '#type' => 'textfield',
        '#title' => t('One assassin has been singled out without targets (message)'),
        '#default_value' => variable_get('assassin_singled_out'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['not_enough_targets'] = array(
        '#type' => 'textfield',
        '#title' => t('Not enough assassins to target (balance issue) (message)'),
        '#default_value' => variable_get('not_enough_targets'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['all_targets_assigned'] = array(
        '#type' => 'textfield',
        '#title' => t('All targets assigned, success (message)'),
        '#default_value' => variable_get('all_targets_assigned'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    return system_settings_form($form);
}