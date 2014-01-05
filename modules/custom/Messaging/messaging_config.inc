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
        '#title' => t('The message a player receives notifying him of his suspension:'),
        '#default_value' => variable_get('suspension_msg', 'Your license to kill has been revoked. If you have any questions, please contact your organizer.'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['sms_long_notification'] = array(
        '#type' => 'textfield',
        '#title' => t('The SMS a player will receive when the message to be sent is over the SMS size limit:'),
        '#default_value' => variable_get('sms_long_notification', '_name_ sent you a message on Assassin Manager. Please log in to view this message.'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    $form['sms_notification'] = array(
        '#type' => 'textfield',
        '#title' => t('The prefix for all sms:'),
        '#default_value' => variable_get('sms_notification', '_name_ sent you a msg on Assassin Manager: _msg_'),
        '#size' => 100,
        '#maxlength' => 100,
        '#required' => true,
    );

    return system_settings_form($form);
}