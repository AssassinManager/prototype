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
  if (!isset($message->field_recipients['und'])) return $recipients;

  foreach ($message->field_recipients['und'] as $user) {
    array_push($recipients, $user['target_id']);
  }
  return $recipients;
}
function _get_msg_between($author, $recipient) {

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'message')
            ->propertyCondition('status', 1)
            ->propertyCondition('uid', $author)
            ->fieldCondition('field_recipients', 'target_id', array($recipient));

    $msg_nid = $query->execute();

    if (count($msg_nid) < 1) return null;
    $msg_nid = array_keys($msg_nid['node']);
    return $msg_nid[0];
}