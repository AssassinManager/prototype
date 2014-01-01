<?php

function _target_player_profile(&$build) {
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_library('system', 'jquery.form');

  foreach ($build as $key => $value) {
    if (strpos($key, 'field_') !== false) unset($build[$key]);
  }
  unset($build['summary']);

  //dsm($build['#account']);

  $build['test1'] = array(
                '#type' => 'button',
                '#name' => 'test1',
                '#value' => t('test2'),
                '#ajax'  => array(
                  'callback' => 'target_test',
                  'wrapper'  => 'the-wrapper-div-field',
                ),
              );

  $build['test2'] = array(
                '#type' => 'link',
                '#title' => t('test2'),
                '#href' => 'http://192.168.226.137/am/',
                '#ajax' => array(
                  'callback' => 'target_test',
                  'wrapper' => 'ajax-response-goes-here',
                  'method' => 'replace',
                  'effect' => 'fade',
                ),
              );
    
  $output = "<div id='ajax-response-goes-here'></div>Some HTML and stuff" . drupal_render($link);
}


function target_test() {
    watchdog("test", "Ajax test");
    //drupal_set_message("got into test");
}