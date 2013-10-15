<?php

/**
 * implements hook_rules_action_info().
 */
function _create_kill_action() {
    return array(
          'label' => t('Killed Target'),
          'group' => t('Assassin Manager'),
          'parameter' => array(
              'assassin' => array(
                'type' => 'user',
                'label' => t('Assassin'),
                'description' => t("The assain."),
                'translatable' => TRUE,
              ),
              'target' => array(
                'type' => 'user',
                'label' => t('Target'),
                'description' => t("The target."),
                'translatable' => TRUE,
              ),
            ),
          'base' => '_assassinations_am_kill',
        );
}

function _assassinations_am_kill($assassin, $target) {
    
    if ($assassin == null) return false;
    if (!isset($assassin)) return false;
    
    if ($target == null) return false;
    if (!isset($target)) return false;

    if (!module_exists('messaging')) return false;

    messaging_send_message_to_organizers("test", "test");

    /*
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
    */
    return true;
}
