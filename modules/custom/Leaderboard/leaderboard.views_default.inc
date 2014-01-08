<?php

/**
 * Implements hook_views_default_views().
 *
 * @return array
 */
function leaderboard_views_default_views() {

	/*
	 * Prize view
	 */
	$prize_view = new view();
	$prize_view->name = 'prizes';
	$prize_view->description = '';
	$prize_view->tag = 'default';
	$prize_view->base_table = 'node';
	$prize_view->human_name = 'Prizes';
	$prize_view->core = 7;
	$prize_view->api_version = '3.0';
	$prize_view->disabled = FALSE; 

	/* Display: Master */
	$handler = $prize_view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Prizes';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'none';
	$handler->display->display_options['style_plugin'] = 'table';
	/* Field: Content: Required Rank */
	$handler->display->display_options['fields']['field_required_rank']['id'] = 'field_required_rank';
	$handler->display->display_options['fields']['field_required_rank']['table'] = 'field_data_field_required_rank';
	$handler->display->display_options['fields']['field_required_rank']['field'] = 'field_required_rank';
	$handler->display->display_options['fields']['field_required_rank']['label'] = '';
	$handler->display->display_options['fields']['field_required_rank']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_required_rank']['settings'] = array(
	  'thousand_separator' => ' ',
	  'prefix_suffix' => 1,
	);
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	/* Field: Content: Desciption */
	$handler->display->display_options['fields']['field_prize_description']['id'] = 'field_prize_description';
	$handler->display->display_options['fields']['field_prize_description']['table'] = 'field_data_field_prize_description';
	$handler->display->display_options['fields']['field_prize_description']['field'] = 'field_prize_description';
	$handler->display->display_options['fields']['field_prize_description']['label'] = '';
	$handler->display->display_options['fields']['field_prize_description']['element_label_colon'] = FALSE;
	/* Sort criterion: Content: Required Rank (field_required_rank) */
	$handler->display->display_options['sorts']['field_required_rank_value']['id'] = 'field_required_rank_value';
	$handler->display->display_options['sorts']['field_required_rank_value']['table'] = 'field_data_field_required_rank';
	$handler->display->display_options['sorts']['field_required_rank_value']['field'] = 'field_required_rank_value';
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'prize' => 'prize',
	);

	/* Display: Block */
	$handler = $prize_view->new_display('block', 'Block', 'block');
	$handler->display->display_options['block_description'] = 'Prizes';

	/*
	 * Leaderboard view
	 */
	$leaderboard_view = new view();
	$leaderboard_view->name = 'leaderboard';
	$leaderboard_view->description = '';
	$leaderboard_view->tag = 'default';
	$leaderboard_view->base_table = 'users';
	$leaderboard_view->human_name = 'Leaderboard';
	$leaderboard_view->core = 7;
	$leaderboard_view->api_version = '3.0';
	$leaderboard_view->disabled = FALSE;

	/* Display: Master */
	$handler = $leaderboard_view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Leaderboard';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['access']['perm'] = 'access user profiles';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '10';
	$handler->display->display_options['style_plugin'] = 'table';
	/* Field: User: Rank */
	$handler->display->display_options['fields']['field_rank']['id'] = 'field_rank';
	$handler->display->display_options['fields']['field_rank']['table'] = 'field_data_field_rank';
	$handler->display->display_options['fields']['field_rank']['field'] = 'field_rank';
	$handler->display->display_options['fields']['field_rank']['label'] = '';
	$handler->display->display_options['fields']['field_rank']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_rank']['settings'] = array(
	  'thousand_separator' => ' ',
	  'prefix_suffix' => 1,
	);
	/* Field: User: First name */
	$handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
	$handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
	$handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
	$handler->display->display_options['fields']['field_first_name']['label'] = '';
	$handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
	/* Field: User: Last Name */
	$handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
	$handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
	$handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
	$handler->display->display_options['fields']['field_last_name']['label'] = '';
	$handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
	/* Sort criterion: User: Rank (field_rank) */
	$handler->display->display_options['sorts']['field_rank_value']['id'] = 'field_rank_value';
	$handler->display->display_options['sorts']['field_rank_value']['table'] = 'field_data_field_rank';
	$handler->display->display_options['sorts']['field_rank_value']['field'] = 'field_rank_value';
	/* Filter criterion: User: Active */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'users';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = '1';
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: User: Rank (field_rank) */
	$handler->display->display_options['filters']['field_rank_value']['id'] = 'field_rank_value';
	$handler->display->display_options['filters']['field_rank_value']['table'] = 'field_data_field_rank';
	$handler->display->display_options['filters']['field_rank_value']['field'] = 'field_rank_value';
	$handler->display->display_options['filters']['field_rank_value']['operator'] = '<=';
	$handler->display->display_options['filters']['field_rank_value']['value']['value'] = '10';

	/* Display: Block */
	$handler = $leaderboard_view->new_display('block', 'Block', 'block');
	$handler->display->display_options['block_description'] = 'Top 10';
	
	/*
	 * Array saving
	 */
	$views[$leaderboard_view->name] = $leaderboard_view;
	$views[$prize_view->name] = $prize_view;

	return $views;
}