<?php

/*
 * Messaging Recipients Utilities
 */
function _recipients_uids_read($message) {
  $recipients = array();
  if (!isset($message->field_recipients['und'])) return $recipients;

  foreach ($message->field_recipients['und'] as $user) {
    array_push($recipients, $user['target_id']);
  }
  return $recipients;
}

/*
 * Implements hook_entity_view
 * Responds when the user views a message or a reply (comment)
 */
function messaging_entity_view($entity, $type, $view_mode, $langcode) {

  // Check if this is a message or a reply
  if (!($type == "node" && $entity->type == "message") &&
      !($type == "comment" && $entity->node_type == "comment_node_message")) 
    return;

  global $user;

  $recipients = array();
  if (isset($entity->comment_body)) 
       $recipients = _get_all_recipients($entity->uid, node_load($entity->nid));
  else $recipients = _get_all_recipients($entity->uid, $entity);
  if (count($recipients) < 1) return;

  if (isset($entity->field_read_by['und']) && 
    in_array(array('target_id' => $user->uid), $entity->field_read_by['und'])) return; 

  $entity->field_read_by['und'][] = array('target_id' => $user->uid);

  if (isset($entity->comment_body))  comment_save($entity);
  else                      node_save($entity);
}


/*
 * Reads Utilities
 */
function _messaging_get_reads($message) {
  $reads = array();
  foreach ($message->field_read_by['und'] as $user) {
    array_push($reads, $user['target_id']);
  }
  return $reads;
}