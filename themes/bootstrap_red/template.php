<?php

function mytheme_preprocess_html(&$variables) {
  drupal_add_css('http://fonts.googleapis.com/css?family=PT+Sans+Narrow', array('type' => 'external'));
  drupal_add_css('http://fonts.googleapis.com/css?family=PT+Sans', array('type' => 'external'));
}
