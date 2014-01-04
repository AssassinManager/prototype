<?php

/**
 * implements hook_menu().
 */
 function suspend_menu() {
  $items = array();

  $items['admin/AM/Suspensions/config'] = array(
    'title' => 'Suspensions',
    'description' => 'Suspensions defaults and msgs',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('suspend_defaults'),
    'access arguments' => array('administer site configuration'),
   );
  
  return $items;
}

function suspend_defaults() {
    $form = array();

    $form['player_pending_elimination'] = array(
        '#type' => 'textfield',
        '#title' => t('Player is still pending elimination, suspending him will break the system (message)'),
        '#default_value' => variable_get('player_pending_elimination'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['unsuspension_3_rule'] = array(
        '#type' => 'textfield',
        '#title' => t('Cannot unsuspend player when there are 3 players or less left in the game (message)'),
        '#default_value' => variable_get('unsuspension_3_rule'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    return system_settings_form($form);
}