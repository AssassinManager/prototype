<?php

/*
 * Checking for the license upon Registration
 */
function license_to_kill_form_alter(&$form, &$form_state, $form_id) {
    if($form_id == "user_register_form") {
        $form['#validate'][] = 'reg_check_validation_callback';
    }
}

function check_license($license) {
    $query = db_select('node', 'n')
            ->fields('n', array('nid'));

    $query->join('field_data_field_code', 'fc', 'fc.entity_id = n.nid and field_code_value = :license', array(':license' => $license));
    $result = $query->countquery()->execute()->fetch();
    
    if($result->expression > 0) return true;

    return false;
}

function reg_check_validation_callback(&$form_state) {

    if (!isset($form_state['field_license_code']['und'][0]['value']['#value'])) return;
    $license_code = $form_state['field_license_code']['und'][0]['value']['#value'];

    if(!check_license($license_code))
        form_set_error('field-name-field-license-code', t('invalid license code'));
}

/*
 * Removing the license upon successfull registration
 */
function license_to_kill_user_insert(&$edit, $account, $category) {
    $license = $edit['field_license_code']['und'][0]['value'];

    $query = db_select('node', 'n')
            ->fields('n', array('nid'));

    $query->join('field_data_field_code', 'fc', 'fc.entity_id = n.nid and field_code_value = :license', array(':license' => $license));
    $result = $query->execute()->fetch();

    node_delete($result->nid);
}