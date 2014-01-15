<?php

require('messaging_email.inc');
require('messaging_sms.inc');

module_load_include('module', 'am_tools', 'am_tools');

/**
 * Action for Notifier
 * implements hook_rules_action_info().
 */
function _create_notifier_action() {
	return array(
          'label' => t('Send AM Notification'),
          'group' => t('Assassin Manager'),
          'parameter' => array(
              'message' => array(
                'type' => 'node',
                'label' => t('Message'),
                'description' => t("The message."),
                'translatable' => TRUE,
              ),
            ),
          'base' => '_messaging_am_notify',
        );
}
function _create_notifier_reply_action() {
  return array(
          'label' => t('Send AM Reply Notification'),
          'group' => t('Assassin Manager'),
          'parameter' => array(
              'message' => array(
                'type' => 'comment',
                'label' => t('Reply'),
                'description' => t("The message."),
                'translatable' => TRUE,
              ),
            ),
          'base' => '_messaging_am_notify',
        );
}

function _get_user_subscriptions($user) {
    $subscriptions = array();
    if (!isset($user->field_subscriptions['und'])) return $subscriptions;
    
	foreach ($user->field_subscriptions['und'] as $sub) {
		array_push($subscriptions, $sub['value']);
	}
	return $subscriptions;
}
function _get_user_info($user) {
	return array( 	"name" => am_tools_user_name($user),
					"phone" => $user->field_phone['und'][0]['value'],
					"email" => $user->mail,
					"subscriptions" =>_get_user_subscriptions($user)
				);

}

/*
 * Messaging Recipients Utilities
 */
function _recipients_uids_notifier($message) {
  $recipients = array($message->uid);
  if (!isset($message->field_recipients['und'])) return $recipients;

  foreach ($message->field_recipients['und'] as $user) {
    array_push($recipients, $user['target_id']);
  }
  return $recipients;
}

function _get_all_recipients($from, $original_msg) {
  $message_users = _recipients_uids_notifier($original_msg);

  $key = array_search($from, $message_users);
  if (false !== $key) unset($message_users[$key]);

  return $message_users;
}

function _messaging_am_notify($message) {

    $from = $message->uid;

    $original_msg = $message;
    if (isset($message->comment_body)) $original_msg = node_load($message->nid);
    $message_users = _get_all_recipients($from, $original_msg);
    if (count($message_users) < 1) return;

    $subscriptions = array();
    foreach ($message_users as $uid) {
    	$user = user_load($uid);
    	$user_info = _get_user_info($user);
    	$subscriptions[$uid] = $user_info;
    }

    /**
     * Test if there are no subscriptions from anyone just return
     */
    $counter = 0;
    foreach ($subscriptions as $subscription) {
    	if (count($subscription["subscriptions"]) < 1) $counter++;
    }
    if ($counter == count($subscriptions)) return;

    /**
     * More than 2 recipients, only send an email
     */
    if (count($message_users) > 2) {
    	$emails = array();

    	foreach ($subscriptions as $uid => $subscription) {
	    	if (!isset($subscription['email'])) continue;
	    	if (!in_array('Email', $subscription['subscriptions'])) continue;

	    	array_push($emails, $subscription['email']);
	    }

	    $emails = implode(", ", $emails);
	    $from_user = user_load($from);

      $msg_body = "";
      $msg_subject = "";

      if (isset($message->comment_body)) {
        $msg_subject = $message->subject;
        $msg_body = $message->comment_body['und'][0]['value'];
      }
      else {
        $msg_subject = $message->title;
        $msg_body = $message->field_body['und'][0]['value'];
      }

	    _messaging_am_organizer_mail($msg_subject, $msg_body, $from_user->mail, $emails);
    }

    /**
     * At most 2 recipients, send an sms or email
     */
    if (count($message_users) <= 2) {
      $emails = array();
      $phones = array();

      foreach ($subscriptions as $uid => $subscription) {
      	if (!isset($subscription['email'])) continue;
      	if (!in_array('Email', $subscription['subscriptions'])) continue;

      	array_push($emails, $subscription['email']);
      }
      foreach ($subscriptions as $uid => $subscription) {
      	if (!isset($subscription['phone'])) continue;
      	if (!in_array('SMS', $subscription['subscriptions'])) continue;

      	array_push($phones, $subscription['phone']);
      }
      $from_user = user_load($from);
      $from_name = am_tools_user_name($from_user);

      $msg_body = "";
      $msg_subject = "";

      if (isset($message->comment_body)) {
        $msg_subject = $message->subject;
        $msg_body = $message->comment_body['und'][0]['value'];
      }
      else {
        $msg_subject = $message->title;
        $msg_body = $message->field_body['und'][0]['value'];
      }

      if (count($emails) > 0) {
          $from_email = $from_user->mail;
          if (!$from_email || $from_email == null) continue;

          _messaging_am_mail($msg_subject, $msg_body, $from_email, $from_name, $emails);
      }
      if (count($phones) > 0) {
          $from_phone = $from_user->field_phone['und'][0]['value'];
          if (!isset($from_phone) || strlen($from_phone) < 1) $from_phone = variable_get('twilio_number');

          _messaging_am_sms($msg_subject, $msg_body, $from_phone, $from_name, $phones);
      }
    } 
}