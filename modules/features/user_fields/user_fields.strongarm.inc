<?php
/**
 * @file
 * user_fields.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function user_fields_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'genpass_algorithm';
  $strongarm->value = 'genpass';
  $export['genpass_algorithm'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'genpass_display';
  $strongarm->value = '3';
  $export['genpass_display'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'genpass_entropy';
  $strongarm->value = 'abcdefghjkmnpqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ23456789!#$%&()*+,-./:;<=>?@[]^_{|}~';
  $export['genpass_entropy'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'genpass_length';
  $strongarm->value = '8';
  $export['genpass_length'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'genpass_mode';
  $strongarm->value = '0';
  $export['genpass_mode'] = $strongarm;

  return $export;
}
