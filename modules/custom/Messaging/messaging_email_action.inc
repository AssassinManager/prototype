<?php

/**
 * implements hook_rules_action_info().
 */
function _create_email_action() {
    return array(
          'label' => t('Send AM email'),
          'group' => t('Assassin Manager'),
          'parameter' => array(
              'subject' => array(
                'type' => 'text',
                'label' => t('Subject'),
                'description' => t("The mail's subject."),
                'translatable' => TRUE,
              ),
              'message' => array(
                'type' => 'text',
                'label' => t('Message'),
                'description' => t("The mail's message body."),
                'translatable' => TRUE,
              ),
              'from' => array(
                'type' => 'user',
                'label' => t('From'),
                'description' => t("Author of the message."),
                'optional' => TRUE,
              ),
              'to' => array(
                'type' => 'unknown',
                'label' => t('To'),
                'description' => t('User(s) the email will be sent to.'),
              ),
            ),
          'base' => '_messaging_am_mail',
        );
}

function _is_valid($input) {
    if ($input == null) return false;
    if (!isset($input)) return false;

    return true;
}
function _messaging_am_mail($subject, $message, $from, $to) {
    
    if (!_is_valid($from))  return false;
    if (!_is_valid($to))    return false;

    $sender_name = $from->field_first_name['und'][0]['value'] . " " . $from->field_last_name['und'][0]['value'];
    $from = $from->mail;
    $to = implode(", ", _messaging_get_emails($to));

    if (!_is_valid($from))  return false;
    if (!_is_valid($to))    return false;
    $message = $sender_name . " sent you a message on Assassin Manager: \n\n" . $message;

    $my_module = 'messaging';
    $my_mail_token = microtime();
    $message = array(
        'id' => $my_module . '_' . $my_mail_token,
        'to' => $to,
        'subject' => $subject,
        'body' => $message,
        'headers' => array(
            'From' => $from,
            'Sender' => $from,
            'Return-Path' => $from,
        ),
    );
    $system = drupal_mail_system($my_module, $my_mail_token);
    $message = $system->format($message);

    if ($system->mail($message)) return TRUE;
    else return FALSE;
}