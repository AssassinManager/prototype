<?php

function _is_valid($input) {
    if ($input == null) return false;
    if (!isset($input)) return false;

    return true;
}

function _messaging_am_mail($subject, $message, $from, $from_name, $to) {

    if (!_is_valid($from))  return;
    if (!_is_valid($to))    return;

    $to = implode(", ", $to);

    $message = "Hi,\n\n" . $from_name . " sent you a message on Assassin Manager: \n\n" . $message;

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

    if (!$system->mail($message))
        watchdog("Email failure", "Could not send email to " . "<pre>" . print_r($to, 1) . "</pre>");
}

function _messaging_am_organizer_mail($subject, $message, $from, $to) {

    if (!_is_valid($from))  return;
    if (!_is_valid($to))    return;
    
    $message = "Hi,\n\n Your organizer sent you a message on Assassin Manager: \n\n" . $message;

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

    if (!$system->mail($message))
        watchdog("Email failure", "Could not send email to " . "<pre>" . print_r($to, 1) . "</pre>"); 
}