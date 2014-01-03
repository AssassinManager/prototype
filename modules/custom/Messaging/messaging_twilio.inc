<?php

function messaging_twilio() {
    $form = array();

    $form['twilio_sid'] = array(
        '#type' => 'textfield',
        '#title' => t('account sid'),
        '#default_value' => variable_get('twilio_sid'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('twilio account sid - the 34 character string beginning with ac'),
    );
    $form['twilio_auth_token'] = array(
        '#type' => 'textfield',
        '#title' => t('auth token'),
        '#default_value' => variable_get('twilio_auth_token'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('twilio auth token - <a href="https://www.twilio.com/user/account">available on your dashboard</a>'),
    );
    $form['twilio_number'] = array(
        '#type' => 'textfield',
        '#title' => t('twilio number'),
        '#default_value' => variable_get('twilio_number'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('a <a href="https://www.twilio.com/user/account/phone-numbers" target="_new">phone number</a> from your twilio account'),
    );

    return system_settings_form($form);
}
