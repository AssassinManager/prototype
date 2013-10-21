<?php

function _assassinations_player_profile(&$build) {

  foreach ($build as $key => $value) {
    if (strpos($key, 'field_') !== false) unset($build[$key]);
  }
  unset($build['summary']);

  dsm($build['#account']);

  $build['replace_textfield'] = array(
    '#type' => 'textfield',
    '#title' => t("The default value will be changed"),
    '#description' => t("Say something about why you chose") . "'" .
      (!empty($build['values']['changethis'])
      ? $build['values']['changethis'] : t("Not changed yet")) . "'",
    '#prefix' => '<div id="replace_textfield_div">',
    '#suffix' => '</div>',
  );
  $build['button'] = create_button();
}

function create_button() {
    $button = array();
    if (true) {
        $button['test'] = array(
          '#type'  => 'button',
          '#name'  => 'test',
          '#value' => t('Do Something Awesome!'),
          '#ajax'  => array(
            'callback' => 'assassinations_test',
            'wrapper' => 'replace_textfield_div',
          ),
        );
    } else {
        $button['test'] = array(
                '#type' => 'button',
                '#disabled' => false,
                '#name' => 'Test',
                '#value' => t('Test'),
                '#button_type' => 'submit',
                '#executes_submit_callback' => true,
                '#submit' => array('assassinations_test'),
            );
    }

    return $button;
}


function assassinations_test() {
    watchdog("test", "Ajax test");
    //drupal_set_message("got into test");
}