<?php

/*
 * Messaging Recipients Utilities
 */
function _add_recipients($msg_nid, $recipients) {
    $msg = node_load($msg_nid);
    if ($msg == null) return;

    foreach ($recipients as $uid) {
        $msg->field_recipients['und'][]['target_id'] = $uid;
    }
    
    node_save($msg);
}
function _recipients_for_msg($uids) {
  $recipients = array();
  foreach ($uids as $uid) {
    array_push($recipients, array('target_id' => $uid));
  }
  return $recipients;
}
function _recipients_uids($message) {
  $recipients = array();
  foreach ($message->field_recipients['und'] as $user) {
    array_push($recipients, $user['target_id']);
  }
  return $recipients;
}