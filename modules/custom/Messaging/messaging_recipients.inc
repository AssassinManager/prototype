<?php

/*
 * Adds in the recipients right before saving the comment
 */
function messaging_comment_presave($comment) {

  if ($comment->node_type != 'comment_node_message')  return;
  if (!isset($comment->field_recipients['und']))      return;

  $recipient = _get_other_recipient($comment->nid, $comment->uid);

  if (!$recipient || $recipient == null) return;

  $comment->field_recipients['und'][0] = $recipient;
}

/*
 * Returns the uid of the user to assign as recipient
 * This could be either the original author of the node
 * Or the first recipient of the origina message
 */
function _get_other_recipient($nid, $uid) {

  $query = db_select('node', 'n')
            ->fields('n', array('uid'))
            ->condition('nid', $nid,'=');
  $result = $query->execute()->fetch();

  if (!$result || !isset($result->uid)) return null;

  // If the author of the original message was not the current user,
  // then he must be the recipient therefore reply to the original user
  if ($result->uid != $uid) return array("target_id" => $result->uid);

  $query = db_select('field_data_field_recipients', 'fr')
            ->fields('fr', array('field_recipients_target_id'))
            ->condition('entity_id', $nid,'=')
            ->range(0,1);
  $result = $query->execute()->fetch();

  if (!$result || !isset($result->field_recipients_target_id)) return null;

  return array("target_id" => $result->field_recipients_target_id);
}

/*
 * Removes the recipients from the comment form
 */
function messaging_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'comment_node_message_form') {
    $form['field_recipients']['#access'] = FALSE;
  }
}