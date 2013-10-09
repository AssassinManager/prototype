<?php

// implements hook_form_user_profile_form_alter
function player_profile_form_user_profile_form_alter(&$form, &$form_state, $form_id) {
    global $user;

    if(in_array("administrator", $user->roles)) return;

    if(!in_array("Organizer", $user->roles)){
        unset($form['field_suspended']);
        unset($form['field_alive']);
    }

    unset($form['account']['name']);
    unset($form['account']['roles']);
    unset($form['account']['status']);
    unset($form['account']['notify']);

    if($form['#user']->uid != $user->uid) unset($form['account']);

    unset($form['field_license_code']);
    unset($form['field_player_rank']);

    unset($form['field_current_target']);
    unset($form['field_pending_target']);
    unset($form['field_killed_targets']);

    unset($form['contact']);
    unset($form['ckeditor']);
}

// Implements hook_user_update()
function player_profile_user_update(&$edit, $account, $category) {
    if(!in_array("Player", $account->roles)) return;

    if (!($nid = get_player_profile($account->uid))) return;

    $user_profile = node_load($nid);
    $user_profile->title = $account->field_first_name['und'][0]['value'] . ' ' . $account->field_last_name['und'][0]['value'];

    if ($account->field_suspended['und'][0]['value'] != 0)
        $user_profile->field_status['und'][0]['value'] = 'Suspended';

    else if ($account->field_alive['und'][0]['value'] != 1)
        $user_profile->field_status['und'][0]['value'] = 'Dead';

    node_save($user_profile);
}

// Implements hook_node_update()
function player_profile_node_update($node) {
    if($node->type != 'game') return;

    if (!($profiles = get_player_profiles())) return;

    foreach($profiles as $profile) {
        $profile->field_time = $node->field_time;
        $profile->field_info = $node->field_info;
        node_save($profile);
    }
}