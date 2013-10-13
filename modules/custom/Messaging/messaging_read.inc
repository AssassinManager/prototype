<?php

/*
 * Implements hook_entity_view
 * Responds when the user views a message or a reply (comment)
 */
function messaging_entity_view($entity, $type, $view_mode, $langcode) {

  // Check if this is a message
  if ($type == "node" && $entity->type == "message") {
    global $user;

    if (!isset($entity->field_recipients['und'])) return;

    $recipients = _messaging_get_recipients($entity);
    if (!in_array($user->uid, $recipients)) return;

    if (isset($entity->field_read_by['und'])) {
      $readBy = _messaging_get_reads($entity);
      if (in_array($user->uid, $readBy)) return;
    }
    _messaging_read_node_by(node_load($entity->nid), $user);

  }
  // Otherwise do this for a reply/comment
  else if ($type == "comment" && $entity->node_type == "comment_node_message") {
    watchdog("Got comment", "<pre>" . print_r($entity, 1) . "<\pre>"); 
    global $user;

    if (!isset($entity->field_recipients['und'])) return;

    $recipients = _messaging_get_recipients($entity);
    if (!in_array($user->uid, $recipients)) return;

    if (isset($entity->field_read_by['und'])) {
      $readBy = _messaging_get_reads($entity);
      if (in_array($user->uid, $readBy)) return;
    }
    _messaging_read_comment_by(comment_load($entity->cid), $user);
  }
}

/*
 * Utilities
 */
function _messaging_get_recipients($entity) {
  $recipients = array();
  foreach ($entity->field_recipients['und'] as $user) {
    array_push($recipients, $user['target_id']);
  }
  return $recipients;
}

function _messaging_get_reads($entity) {
  $reads = array();
  foreach ($entity->field_read_by['und'] as $user) {
    array_push($reads, $user['target_id']);
  }
  return $reads;
}

/*
 * Sets the message to read if needed
 */
function _messaging_read_node_by($node, $user) {
  $node->field_read_by['und'][] = array('target_id' => $user->uid);
  node_save($node);
}
function _messaging_read_comment_by($comment, $user) {
  $comment->field_read_by['und'][] = array('target_id' => $user->uid);
  comment_save($comment);
}