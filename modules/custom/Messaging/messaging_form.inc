<?php

/*
* Adds the "Assign All Targets" button to the game page
*/
function messaging_am_custom_game_alter(&$data) {

  global $user;
  if (!in_array('Organizer',$user->roles)) return;

  $data['message_all_form'] = drupal_get_form('message_all_form');
}

/**
* Form creation & management
*/
function message_all_form() {
  $form['message_checkbox'] = array(
      '#type' => 'checkbox',
      '#title' => t('Message all players'),
  );

  $form['message'] = array(
      '#type' => 'container',
      '#states' => array(
          'visible' => array(
              ':input[name="message_checkbox"]' => array('checked' => true),
              ),
          ),
  );

  $form['message']['subject_field'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject:'),
      '#default_value' => '',
      '#size' => 30,
      '#maxlength' => 60,
  );

  $form['message']['message_field'] = array(
      '#type' => 'textarea',
      '#title' => t('Message'),
      '#wysiwyg' => false,
      '#rows' => 3,
  );

  $form['message']['message_send'] = array(
      '#type' => 'button', 
      '#name' => 'message_send',
      '#value' => t('Send Message'),
      '#button_type' => 'submit',
      '#executes_submit_callback' => true,
      '#submit' => array('send_message'),
  );

  return $form;
}

function message_to_all_form_validate(&$form, &$form_state) {
  if($form_state['values']['subject_field'] == "" || strlen($form_state['values']['subject_field']) == 0) {
      form_set_error('subject_field', t('must enter subject'));
  }
  if($form_state['values']['message_field'] == "" || strlen($form_state['values']['message_field']) == 0) {
      form_set_error('message_field', t('must enter message'));
  }
}

function send_message(&$form, &$form_state) {
  global $user;
  module_load_include('module', 'am_tools', 'am_tools');
  messaging_send_message( $form_state['values']['subject_field'],
                          $form_state['values']['message_field'],
                          am_tools_players_uids(),
                          $user->uid);
}