<?php

/*
* Adds the "Assign All Targets" button to the game page
*/
function license_to_kill_am_custom_game_alter(&$data) {
  global $user;
  if (!in_array('Organizer',$user->roles)) return;

  $data['manage_licenses_button'] = drupal_get_form('manage_licenses_button');
}

/**
* Validation for form
*/
function code_gen_form_validate(&$form, &$form_state) {
  if(!is_numeric($form_state['values']['generate_licenses'])) {
      form_set_error('generate_licenses', t('must enter number'));
  }

  if(intval($form_state['values']['generate_licenses']) > 999) {
      form_set_error('generate_licenses', t('cannot generate more than 999 licenses at a time...'));
  }
}

/**
* Form creation & management
*/
function manage_licenses_button() {
  /* -- message form -- */
  $form['licenses_checkbox'] = array(
      '#type' => 'checkbox',
      '#title' => t('Manage Licenses'),
  );

  $form['licenses'] = array(
      '#type' => 'container',
      '#states' => array(
          'visible' => array(
              ':input[name="licenses_checkbox"]' => array('checked' => true),
              ),
          ),
  );

  $num_licenses = count_licenses();
  $form['licenses']['licenses_title'] = array(
      '#type' => 'item', 
      '#title' => t('%licenses_num  license(s) still unused', array( '%licenses_num' => $num_licenses )),
  );

  if ($num_licenses > 0) {
    $form['licenses']['licenses_download'] = array(
        '#type' => 'button', 
        '#name' => 'download',
        '#value' => t('Download'),
        '#button_type' => 'submit',
        '#executes_submit_callback' => TRUE,
        '#submit' => array('export_licenses_as_csv'),
    );
    $form['licenses']['licenses_clean'] = array(
        '#type' => 'button',
        '#name' => 'clean',
        '#value' => t('Clean up'),
        '#ajax'  => array('callback' => 'clean_licenses'),
    );
  } else {
    $form['licenses']['licenses_download'] = array(
        '#type' => 'button', 
        '#name' => 'download',
        '#value' => t('Download'),
        '#disabled' => true,
    );
    $form['licenses']['licenses_clean'] = array(
        '#type' => 'button',
        '#name' => 'clean',
        '#value' => t('Clean up'),
        '#disabled' => true,
    );
  }

  // code generation
  $form['licenses']['generate_licenses'] = array(
      '#type' => 'textfield', 
      '#title' => t('generate licenses:'),
      '#default_value' => 1,
      '#size' => 3, 
      '#maxlength' => 3, 
  );

  $form['licenses']['generate_download'] = array(
      '#type' => 'submit', 
      '#name' => 'generate',
      '#value' => t('Generate and download'),
      '#submit' => array('generate_licenses'),
  );

  return $form;
}

/**
 * Utilities & Doers
 */
function count_licenses() {
  $query = db_select('node', 'n')
      ->condition('type', 'license_to_kill')
      ->countQuery()
      ->execute();
  $data = $query->fetchObject();

  return strval($data->expression);
}
function clean_licenses() {
  $query = db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('type', 'license_to_kill')
      ->execute();

  $nids = array();
  while($record = $query->fetch()) {
      array_push($nids, $record->nid);
  }

  node_delete_multiple($nids);
}
function generate_licenses(&$form, &$form_state) {
  $license_num = intval($form_state['values']['generate_licenses']);

  for ($counter=0; $counter<$license_num; $counter++) {
      create_license($counter+1);
  }

  export_licenses_as_csv();
}