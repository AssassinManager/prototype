<?php

/*
 * Checking for the license upon Registration
 */
function license_to_kill_form_alter(&$form, &$form_state, $form_id) {
    if($form_id == "user_register_form") {
        $form['#validate'][] = 'license_check_validation_callback';
    }
}

function check_license($license) {
    if (!$license || $license == null) return true;
    if (strlen($license) < 8 || strlen($license) > 8) return false;

    $query = db_select('field_data_field_license', 'fc')
            ->fields('fc', array('field_license_value'))
            ->condition('field_license_value', $license,'=');

    $result = $query->countquery()->execute()->fetch();
    
    if($result->expression > 0) return true;

    return false;
}

function license_check_validation_callback(&$form_state) {

    if (!isset($form_state['field_license_code']['und'][0]['value']['#value'])) return;

    $license_code = $form_state['field_license_code']['und'][0]['value']['#value'];

    if(!check_license($license_code)) {
        form_set_error('field-name-field-license-code', t('invalid license code'));
    }
}

/*
 * Removing the license upon successfull registration
 */
function license_to_kill_user_insert(&$edit, $account, $category) {

    $license = get_license_nid($edit['field_license_code']['und'][0]['value']);
    
    if (!$license || $license == null) return;

    node_delete($license);
}

/*
 * Getting a license Node
 */
function get_license_nid($code) {
    if (!$code || $code == null) return null;
    if (strlen($code) < 8 || strlen($code) > 8) return null;


    $query = db_select('field_data_field_license', 'fc')
            ->fields('fc', array('entity_id'))
            ->condition('field_license_value', $code,'=');
    $result = $query->execute()->fetch();

    if (!$result || !isset($result->entity_id)) return null;

    return $result->entity_id;
}