<?php
/**
 * @file
 * am_players_and_organizers.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function am_players_and_organizers_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'players_alive';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Players Alive';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: User: First Name */
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
  /* Field: User: Alive */
  $handler->display->display_options['fields']['field_alive']['id'] = 'field_alive';
  $handler->display->display_options['fields']['field_alive']['table'] = 'field_data_field_alive';
  $handler->display->display_options['fields']['field_alive']['field'] = 'field_alive';
  $handler->display->display_options['fields']['field_alive']['label'] = '';
  $handler->display->display_options['fields']['field_alive']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_alive']['element_label_colon'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Alive (field_alive) */
  $handler->display->display_options['filters']['field_alive_value']['id'] = 'field_alive_value';
  $handler->display->display_options['filters']['field_alive_value']['table'] = 'field_data_field_alive';
  $handler->display->display_options['filters']['field_alive_value']['field'] = 'field_alive_value';
  $handler->display->display_options['filters']['field_alive_value']['operator'] = 'and';
  $handler->display->display_options['filters']['field_alive_value']['value'] = array(
    1 => '1',
  );

  /* Display: Players Alive */
  $handler = $view->new_display('entityreference', 'Players Alive', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Players Alive';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_alive' => 'field_alive',
    'field_first_name' => 0,
    'field_last_name' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['separator'] = '';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['players_alive'] = $view;

  return $export;
}
