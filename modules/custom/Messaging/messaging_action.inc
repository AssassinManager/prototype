<?php

/**
 * implements hook_rules_action_info().
 */
function messaging_rules_action_info() {
    return array(
        'am_mail' => array(
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
            ),
        );
}

function _is_valid($input) {
    if ($input == null) return false;
    if (!isset($input)) return false;

    return true;
}
function _get_email_addresses($email_users) {

    $emails = array();

    foreach ($email_users as $user) {
        if (!isset($user->mail)) continue;
        array_push($emails, str_replace(array("\r", "\n"), '', $user->mail));
    }
    
    return implode(", ", $emails);
}
function _messaging_am_mail($subject, $message, $from, $to) {
    
    if (!_is_valid($from))  return false;
    if (!_is_valid($to))    return false;

    $from = $from->mail;
    $to = _get_email_addresses($to);

    if (!_is_valid($from))  return false;
    if (!_is_valid($to))    return false;

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