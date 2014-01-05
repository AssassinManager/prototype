<?php

/*
 * Adds the "Assign All Targets" button to the game page
 */
function target_am_custom_game_alter(&$data) {

  global $user;
  if (!in_array('Organizer',$user->roles)) return;

  $data['_assign_targets_button'] = drupal_get_form('assign_targets_button');
}


function assign_targets_button($form, &$form_state) {

  $form['assign_targets_button'] = array(
                '#type' => 'button',
                '#name' => 'assign_targets_button',
                '#value' => t('Assign all targets'),
                '#ajax'  => array('callback' => 'target_assign_targets'),
            );

  return $form;
}