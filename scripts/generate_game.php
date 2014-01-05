<?php

_create_game();

function _create_game() {

	$node = new stdClass();
	$node->type = 'game';
	$node->title = 'The awesome game!';
	node_object_prepare($node);

	$node->field_time['und'][0]['value'] = date('Y-m-d H:i:s',time());
	$node->field_time['und'][0]['value2'] = date('Y-m-d H:i:s',time()+604800); // + 1 Week
	$node->field_time['und'][0]['timezone'] = 'America/Chicago';
	$node->field_time['und'][0]['timezone_db'] = 'UTC';
	$node->field_time['und'][0]['data_type'] = 'datetime';

	$node->field_information['und'][0]['value'] = "Test game - Yippi! \n\n This is an awesome game for blahblah school dudiyo year!";

	node_save($node);
}

?>