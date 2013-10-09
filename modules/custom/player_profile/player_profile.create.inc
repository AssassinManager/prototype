<?php

// implements hook_user_insert()
function player_profile_user_insert(&$edit, $account, $category) {
    $node = new stdclass();
    $node->type = 'profile';
    node_object_prepare($node);

    $node->uid = $account->uid;
    $node->language = 'und';

    $node->title = $account->field_first_name['und'][0]['value'] . ' ' . $account->field_last_name['und'][0]['value'];

    $node->field_status['und'][0]['value'] = 'in good shape';
    $node->field_status['und'][0]['format'] = 'filtered_html';

    $game = node_load(get_game());
	if (isset($game->field_time)) {
		$node->field_time['und'][0] = $game->field_time['und'][0];
	}

    node_save($node);
}
