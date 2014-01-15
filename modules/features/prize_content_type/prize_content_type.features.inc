<?php
/**
 * @file
 * prize_content_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function prize_content_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function prize_content_type_image_default_styles() {
  $styles = array();

  // Exported image style: icon.
  $styles['icon'] = array(
    'name' => 'icon',
    'label' => 'Icon',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 60,
          'height' => 60,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function prize_content_type_node_info() {
  $items = array(
    'prize' => array(
      'name' => t('Prize'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Prize'),
      'help' => '',
    ),
  );
  return $items;
}
