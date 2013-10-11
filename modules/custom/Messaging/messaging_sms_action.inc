<?php

/**
 * implements hook_rules_action_info().
 */
function _create_sms_action() {
    return array(
          'label' => t('Send AM sms'),
          'group' => t('Assassin Manager'),
          'parameter' => array(
              'subject' => array(
                'type' => 'text',
                'label' => t('Subject'),
                'description' => t("The message subject."),
                'translatable' => TRUE,
              ),
              'message' => array(
                'type' => 'text',
                'label' => t('Message'),
                'description' => t("The message."),
                'translatable' => TRUE,
              ),
              'from' => array(
                'type' => 'user',
                'label' => t('To'),
                'description' => t('Organizer user'),
              ),
              'to' => array(
                'type' => 'user',
                'label' => t('To'),
                'description' => t('User to send the sms to.'),
              ),
            ),
          'base' => '_messaging_am_sms',
        );
}

function _messaging_am_sms($subject, $message, $from, $to) {
    
    if ($to == null) return false;
    if (!isset($to)) return false;
    
    if ($from == null) return false;
    if (!isset($from)) return false;

    $sender_name = $from->field_first_name['und'][0]['value'] . " " . $from->field_last_name['und'][0]['value'];

    if (!isset($to->field_phone['und'])) return false;
    $recipient_phone = $to->field_phone['und'][0]['value'];

    $message = $sender_name . " sent you a msg on Assassin Manager: " . $message;

    $file = getcwd() . '/sites/all/libraries/twilio/Twilio.php';
    if (!is_file($file)) return false;

    require_once $file;

    $sid = variable_get('twilio_sid');
    $token = variable_get('twilio_auth_token');

    $client = new services_twilio($sid, $token);
    $sms = $client->account->sms_messages->create(
        variable_get('twilio_number'),
        $recipient_phone,
        $message
    );

    if($sms->sid > 0) return true;
    return false;
}
