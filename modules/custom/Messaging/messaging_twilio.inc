<?php

function messaging_twilio() {
    $form = array();

    $form['twilio_sid'] = array(
        '#type' => 'textfield',
        '#title' => t('Account sid'),
        '#default_value' => variable_get('twilio_sid', 'AC0dcbcc04c0625c2cbabff0fe47084fb4'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('twilio account sid - the 34 character string beginning with ac'),
    );
    $form['twilio_auth_token'] = array(
        '#type' => 'textfield',
        '#title' => t('Auth token'),
        '#default_value' => variable_get('twilio_auth_token', '53f8ccd5ac0279f4572960728ba8eeb4'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('twilio auth token - <a href="https://www.twilio.com/user/account">available on your dashboard</a>'),
    );
    $form['twilio_number'] = array(
        '#type' => 'textfield',
        '#title' => t('Twilio number'),
        '#default_value' => variable_get('twilio_number', '6304057181'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => true,
        '#description' => t('a <a href="https://www.twilio.com/user/account/phone-numbers" target="_new">phone number</a> from your twilio account'),
    );

    return system_settings_form($form);
}
