<?php

_create_players(1, array($rid));

function _create_license($number) {
    $node = new stdClass();
    $node->type = 'license_to_kill';
    node_object_prepare($node);

    $node->title = 'license-' . $number;
    $node->field_code['und'][0]['value'] = "0";

    node_save($node);
}

function _get_new_license() {
  $query = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('type', 'license_to_kill', '=')
    ->range(0,1)
    ->execute()
    ->fetch();

  if (!isset($query->nid)) return NULL;

  return node_load($query->nid);
}

function _generate_word($length){
  mt_srand((double)microtime()*1000000);

  $vowels = array("a", "e", "i", "o", "u");
  $cons = array("b", "c", "d", "g", "h", "j", "k", "l", "m", "n", "p", "r", "s", "t", "u", "v", "w", "tr",
  "cr", "br", "fr", "th", "dr", "ch", "ph", "wr", "st", "sp", "sw", "pr", "sl", "cl", "sh");

  $num_vowels = count($vowels);
  $num_cons = count($cons);
  $word = '';

  while(strlen($word) < $length){
    $word .= $cons[mt_rand(0, $num_cons - 1)] . $vowels[mt_rand(0, $num_vowels - 1)];
  }

  return substr($word, 0, $length);
}

function _create_players($num) {

  for ($i=0; $i < $num; $i++) { 
    _create_license($i);
  }

  $names = array();
  while (count($names) < $num) {
    $name = _generate_word(mt_rand(6, 12));
    $names[$name] = '';
  }

  foreach ($names as $name => $value) {

    $license_code = _get_new_license();
    $license = $license_code->field_license;

    $first_name = array('und' => array(array('value' => $name, 'safe_value' => $name)));
    $last_name = array('und' => array(array('value' => 'Devel', 'safe_value' => 'Devel')));

    $roles = array_search('Player', user_roles());
    $edit = array(
      'pass'    => '99REDballoons',
      'name'    => $name,
      'mail'    => $name . '@gmail.com',
      'status'  => 1,
      'roles' => drupal_map_assoc(array($roles)),
      'field_first_name' => $first_name,
      'field_last_name' => $last_name,
      'field_license_code' => $license,
    );

    $account = user_save(drupal_anonymous_user(), $edit);
    node_delete($license_code->nid);
  }

	module_load_include('module', 'target', 'target');
	target_assign_targets();
	target_update_rankings();
}

?>