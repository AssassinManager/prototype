<?php

/**
 * Implements hook_views_default_views().
 *
 * @return array
 */
function messaging_views_default_views() {

	$view = new view();
	$view->name = 'news';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'News';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'News';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '5';
	$handler->display->display_options['style_plugin'] = 'default';
	$handler->display->display_options['row_plugin'] = 'fields';
	$handler->display->display_options['row_options']['inline'] = array(
	  'title' => 'title',
	  'last_updated' => 'last_updated',
	);
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	/* Field: Content: Updated/commented date */
	$handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
	$handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
	$handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
	$handler->display->display_options['fields']['last_updated']['label'] = ' - ';
	$handler->display->display_options['fields']['last_updated']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
	/* Field: Content: Rules */
	$handler->display->display_options['fields']['field_body']['id'] = 'field_body';
	$handler->display->display_options['fields']['field_body']['table'] = 'field_data_field_body';
	$handler->display->display_options['fields']['field_body']['field'] = 'field_body';
	$handler->display->display_options['fields']['field_body']['label'] = '';
	$handler->display->display_options['fields']['field_body']['element_label_colon'] = FALSE;
	/* Sort criterion: Content: Post date */
	$handler->display->display_options['sorts']['created']['id'] = 'created';
	$handler->display->display_options['sorts']['created']['table'] = 'node';
	$handler->display->display_options['sorts']['created']['field'] = 'created';
	$handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
	  'message' => 'message',
	);
	/* Filter criterion: Content: Title */
	$handler->display->display_options['filters']['title']['id'] = 'title';
	$handler->display->display_options['filters']['title']['table'] = 'node';
	$handler->display->display_options['filters']['title']['field'] = 'title';
	$handler->display->display_options['filters']['title']['operator'] = '!=';
	$handler->display->display_options['filters']['title']['value'] = 'Assassin Manager job update';
	/* Filter criterion: Content: Title */
	$handler->display->display_options['filters']['title_1']['id'] = 'title_1';
	$handler->display->display_options['filters']['title_1']['table'] = 'node';
	$handler->display->display_options['filters']['title_1']['field'] = 'title';
	$handler->display->display_options['filters']['title_1']['operator'] = '!=';
	$handler->display->display_options['filters']['title_1']['value'] = 'Elimination challenge';
	/* Filter criterion: Content: Title */
	$handler->display->display_options['filters']['title_2']['id'] = 'title_2';
	$handler->display->display_options['filters']['title_2']['table'] = 'node';
	$handler->display->display_options['filters']['title_2']['field'] = 'title';
	$handler->display->display_options['filters']['title_2']['operator'] = '!=';
	$handler->display->display_options['filters']['title_2']['value'] = 'Assassin Manager elimination notice';
	/* Filter criterion: Content: Rules (field_body) */
	$handler->display->display_options['filters']['field_body_value']['id'] = 'field_body_value';
	$handler->display->display_options['filters']['field_body_value']['table'] = 'field_data_field_body';
	$handler->display->display_options['filters']['field_body_value']['field'] = 'field_body_value';
	$handler->display->display_options['filters']['field_body_value']['operator'] = 'shorterthan';
	$handler->display->display_options['filters']['field_body_value']['value'] = '140';

	/* Display: News Block */
	$handler = $view->new_display('block', 'News Block', 'news_block');
	$handler->display->display_options['block_description'] = 'News Block';

	$views[$view->name] = $view;
	return $views;
}