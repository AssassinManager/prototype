<?php

function _game_table_form($form, &$form_state) {
 
    $headers = array(
        'alive' => t('Alive'),
        'no_target' => t('No target'),
        'eliminated' => t('Eliminated'),
        'suspended' => t('Suspended'),
    );

    module_load_include('module', 'am_tools', 'am_tools');
    $players = am_tools_players_uids();
    $rows = create_table_content($players);

    $form['table'] = array(
        '#theme' => 'table',
        '#header' => $headers,
        '#rows' => $rows,
        '#empty' => t('No players yet'),
    );
    return $form;
}
function create_table_content($users) {
    $cols['alive'] = array();
    $cols['no_target'] = array();
    $cols['eliminated'] = array();
    $cols['suspended'] = array();

    global $user;
    global $base_url;
    $url = $base_url . '/';
    if(variable_get('clean_url', 0) != 1) $url = $url . '?q=';

    foreach($users as $uid){

        $player = user_load($uid);
        $name = am_tools_user_name($player);

        // get the user's profile url
        $url = $url . 'user/' . $uid;
        $name_url = $name;
        if (in_array('Organizer', $user->roles)) $name_url = '<a href="' . $url . '">' . $name . '</a>';
        
        // user is dead
        if ($player->field_alive['und'][0]['value'] == 0) {
            array_push($cols['eliminated'], $name_url);
            continue;
        }

        // user is suspended
        if ($player->field_suspended['und'][0]['value'] == 1) {
            array_push($cols['suspended'], $name_url);
            continue;
        }

        // user has no target
        if (!isset($player->field_current_target['und']) || count($player->field_current_target['und']) < 1) {
            array_push($cols['no_target'], $name_url);
            continue;
        }

        // user is all good!
        array_push($cols['alive'], $name_url);
    }

    $max_rows =count($cols['alive']);

    if ($max_rows < count($cols['eliminated'])) $max_rows = count($cols['eliminated']);
    if ($max_rows < count($cols['suspended']))  $max_rows = count($cols['suspended']);
    if ($max_rows < count($cols['no_target']))  $max_rows = count($cols['no_target']);

    $must_balance = true;
    while ($must_balance) {
        if (count($cols['eliminated']) < $max_rows) array_push($cols['eliminated'], '');
        if (count($cols['suspended']) < $max_rows)  array_push($cols['suspended'], '');
        if (count($cols['no_target']) < $max_rows)  array_push($cols['no_target'], '');
        if (count($cols['alive']) < $max_rows)      array_push($cols['alive'], '');

        if (count($cols['eliminated']) == $max_rows &&
            count($cols['suspended']) == $max_rows  &&
            count($cols['no_target']) == $max_rows &&
            count($cols['alive']) == $max_rows) {
            $must_balance = false;
        }
    }

    $rows = array();
    for($counter=0; $counter<$max_rows; $counter++) {
        $new_row = array (  
                            'alive' => $cols['alive'][$counter],
                            'no_target' => $cols['no_target'][$counter],
                            'eliminated' => $cols['eliminated'][$counter],
                            'suspended' => $cols['suspended'][$counter],
                        );
        array_push($rows, $new_row);
    }

    return $rows;
}