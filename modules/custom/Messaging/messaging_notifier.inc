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
					"phone" => am_tools_field_val($user->field_phone),
					"email" => $user->mail,
					"subscriptions" =>_get_user_subscriptions($user)
				);

}

function _messaging_am_notify($message) {
    
    $from = $message->uid;
    if (!am_tools_valid($from))  return false;

    require('messaging_tools.inc');
    $to = _recipients_uids($message);
    if (!am_tools_valid($to))    return false;

    $subscriptions = array();
    foreach ($to as $uid) {
    	$user = user_load($uid);
    	$user_info = _get_user_info($user);
    	$subscriptions[$uid] = $user_info;
    }

    /**
     * Test if there are no subscriptions from anyone just return
     */
    foreach ($subscriptions as $subscription) {
    	if (!empty($subscription["subscriptions"]) || 
    		count($subscription["subscriptions"]) < 1) 
    		return true;
    }

    /**
     * More than 2 recipients, only send an email
     */
    if (count($to) > 2) {
    	$emails = array();

    	foreach ($subscriptions as $uid => $subscription) {
	    	if (!isset($subscription['email'])) continue;
	    	if (!in_array('Email', $subscription['subscriptions'])) continue;

	    	array_push($emails, $subscription['email']);
	    }

	    $emails = implode(", ", $emails);
	    $from_user = user_load($message->uid);
	    $from_email = $from_user->mail;
	    $msg_body = am_tools_field_val($message->field_body);

	    _messaging_am_organizer_mail($message->title, $msg_body, $from_email, $emails);
    }

    /**
     * At most 2 recipients, send an sms or email
     */
    if (count($to) <= 2) {
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
	    $from_user = user_load($message->uid);
        $from_name = am_tools_user_name($from_user);
        $msg_body = am_tools_field_val($message->field_body);

        if (count($emails > 0)) {
            $from_email = $from_user->mail;
            if (!$from_email || $from_email == null) continue;

            _messaging_am_mail($message->title, $msg_body, $from_email, $from_name, $emails);
        }
        if (count($phones > 0)) {
            $from_phone = am_tools_field_val($from_user->field_phone);
            if (!$from_phone || $from_phone == null) $from_phone = variable_get('twilio_number');

            _messaging_am_sms($message->title, $msg_body, $from_phone, $from_name, $phones);
        }
    }
}