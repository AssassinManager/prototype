<?php

print("Creating Game\n");
_create_game();
_create_game_rules();

function _create_game() {

	$node = new stdClass();
	$node->type = 'game';
	$node->title = 'Assassin Manager';
	node_object_prepare($node);

	$node->field_time['und'][0]['value'] = date('Y-m-d H:i:s',time());
	$node->field_time['und'][0]['value2'] = date('Y-m-d H:i:s',time()+604800); // + 1 Week
	$node->field_time['und'][0]['timezone'] = 'America/Chicago';
	$node->field_time['und'][0]['timezone_db'] = 'UTC';
	$node->field_time['und'][0]['data_type'] = 'datetime';

	node_save($node);
}
function _create_game_rules() {

	$node = new stdClass();
	$node->type = 'game-rules';
	$node->title = 'Assassin Manager Rules';
	node_object_prepare($node);

	$body = "So this is what's gona happens yoyos!";
	$node->body['und'][0]['format'] = 'filtered_html';
	$node->body['und'][0]['value'] = $body;
	$node->body['und'][0]['safe_value'] = "<p>" . $body ."<p>";

	node_save($node);
}

?>