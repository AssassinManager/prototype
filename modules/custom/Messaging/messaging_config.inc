<?php
 
require('messaging_twilio.inc');

/**
 * implements hook_menu().
 */
 function messaging_menu() {
  $items = array();

  $items['admin/AM'] = array(
    'title' => 'AM',
    'description' => 'Messaging defaults and msgs',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('messaging_defaults'),
    'access arguments' => array('administer site configuration'),
   );
  $items['admin/AM/Messaging/config'] = array(
    'title' => 'Messaging',
    'description' => 'Messaging defaults and msgs',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('messaging_defaults'),
    'access arguments' => array('administer site configuration'),
   );
  $items['admin/AM/SMS/twilio'] = array(
    'title' => 'Twilio',
    'description' => 'Twilio api settings',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('messaging_twilio'),
    'access arguments' => array('administer site configuration'),
   );
  
  return $items;
}

function messaging_defaults() {
    $form = array();

    $form['suspension_msg'] = array(
        '#type' => 'textfield',
        '#title' => t('Suspension message'),
        '#default_value' => variable_get('suspension_msg'),
        '#size' => 160,
        '#maxlength' => 160,
        '#required' => true,
    );

    return system_settings_form($form);
}