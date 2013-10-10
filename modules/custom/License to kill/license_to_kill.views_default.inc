<?php

$licenses_views_file = 'license_export_view.inc';

/**
 * Implements hook_views_default_views().
 *
 * @return array
 */
function license_to_kill_views_default_views() {

	$view = new view();
	$view->name = 'licenses_export';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'Licenses export';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE;

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Licenses export';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'role';
	$handler->display->display_options['access']['role'] = array(
	  3 => '3',
	  4 => '4',
	);
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'none';
	$handler->display->display_options['style_plugin'] = 'default';
	$handler->display->display_options['row_plugin'] = 'fields';
	/* Field: Content: License */
	$handler->display->display_options['fields']['field_license']['id'] = 'field_license';
	$handler->display->display_options['fields']['field_license']['table'] = 'field_data_field_license';
	$handler->display->display_options['fields']['field_license']['field'] = 'field_license';
	$handler->display->display_options['fields']['field_license']['element_label_colon'] = FALSE;
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
	  'license_to_kill' => 'license_to_kill',
	);

	/* Display: Data export */
	$handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['style_plugin'] = 'views_data_export_csv';
	$handler->display->display_options['style_options']['provide_file'] = 1;
	$handler->display->display_options['style_options']['filename'] = 'licenses.csv';
	$handler->display->display_options['style_options']['parent_sort'] = 0;
	$handler->display->display_options['style_options']['quote'] = 1;
	$handler->display->display_options['style_options']['trim'] = 0;
	$handler->display->display_options['style_options']['replace_newlines'] = 0;
	$handler->display->display_options['style_options']['header'] = 1;
	$handler->display->display_options['style_options']['keep_html'] = 0;
	$handler->display->display_options['path'] = 'licenses-export';

	$views[$view->name] = $view;
	return $views;
}