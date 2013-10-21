<?php
 
 /**
 * implements hook_menu().
 */
 function messaging_menu() {
  $items = array();
  $items['admin/config/sms_action'] = array(
    'title' => 'Twilio & SMS',
    'description' => 'Set twilio api settings & msg templates',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('messaging_settings'),
    'access arguments' => array('administer site configuration'),
   );
  return $items;
}

function messaging_settings() {
    $form = array();

    $form['api_checkbox'] = array(
        '#type' => 'checkbox',
        '#title' => t('Twilio API configuration'),
    );
  
    $form['api'] = array(
        '#type' => 'container',
        '#states' => array(
            'visible' => array(
                ':input[name="api_checkbox"]' => array('checked' => true),
                ),
            ),
    );
  
    $form['api']['twilio_sid'] = array(
        '#type' => 'textfield',
        '#title' => t('account sid'),
        '#default_value' => variable_get('twilio_sid'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('twilio account sid - the 34 character string beginning with ac'),
    );
    $form['api']['twilio_auth_token'] = array(
        '#type' => 'textfield',
        '#title' => t('auth token'),
        '#default_value' => variable_get('twilio_auth_token'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('twilio auth token - <a href="https://www.twilio.com/user/account">available on your dashboard</a>'),
    );
    $form['api']['twilio_number'] = array(
        '#type' => 'textfield',
        '#title' => t('twilio number'),
        '#default_value' => variable_get('twilio_number'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('a <a href="https://www.twilio.com/user/account/phone-numbers" target="_new">phone number</a> from your twilio account'),
    );
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
