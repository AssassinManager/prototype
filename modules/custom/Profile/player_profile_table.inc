<?php

function pp_table_form($form, &$form_state) {

  $path = explode ('/', current_path());
  if (count($path) < 2) {
    drupal_set_message("There was a problem building your profile. Please contact our staff for help.", "error");
    return;
  }
  $player = user_load($path[1]);

  $current_target = array();
  $pending_target = array();
  $killed_targets = _get_targets_killed($player);

  // test if the user is suspended
  if ($player->field_suspended['und'][0]['value'] != 1) {
      $pending_target = _get_target_pending($player);
      if (count($pending_target) < 1) $current_target = _get_target_current($player);
  }

  module_load_include('module', 'am_tools', 'am_tools');
  foreach ($killed_targets as $idx => $uid) {
    $killed_targets[$idx] = am_tools_user_name(user_load($uid));
  }
  if (count($current_target) > 0) 
    $current_target[0] = am_tools_user_name(user_load($current_target[0]));
  if (count($pending_target) > 0) 
    $pending_target[0] = am_tools_user_name(user_load($pending_target[0]));

  // create table
  $headers = array(
      'current' => t('Current target'),
      'pending' => t('Pending kill'),
      'killed' => t('killed targets'),
  );

  if (!is_array($current_target)) $current_target = array();
  if (!is_array($pending_target)) $pending_target = array();
  if (!is_array($killed_targets)) $killed_targets = array();

  $rows = populate_pp_table($current_target,
                            $pending_target,
                            $killed_targets);

  $form_targets['table'] = array(
      '#theme' => 'table',
      '#header' => $headers,
      '#rows' => $rows,
      '#empty' => t('-'),
  );
  return $form_targets;
}

function populate_pp_table($current_target, $pending_target, $killed_targets) {
  $cols['current'] = $current_target;
  $cols['pending'] = $pending_target;
  $cols['killed'] = $killed_targets;

  $max_rows = count($cols['current']);

  if ($max_rows < count($cols['pending'])) $max_rows = count($cols['pending']);
  if ($max_rows < count($cols['killed']))  $max_rows = count($cols['killed']);

  $must_balance = true;
  while ($must_balance) {
      if (count($cols['current']) < $max_rows) array_push($cols['current'], '');
      if (count($cols['pending']) < $max_rows) array_push($cols['pending'], '');
      if (count($cols['killed']) < $max_rows)  array_push($cols['killed'], '');

      if (count($cols['current']) == $max_rows &&
          count($cols['pending']) == $max_rows &&
          count($cols['killed']) == $max_rows) {
          $must_balance = false;
      }
  }

  $rows = array();
  for($counter=0; $counter<$max_rows; $counter++) {
      $new_row = array (  
                          'current' => $cols['current'][$counter],
                          'pending' => $cols['pending'][$counter],
                          'killed' => $cols['killed'][$counter],
                      );
      array_push($rows, $new_row);
  }

  return $rows;
}

function _get_targets_killed($player) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'kill')
          ->propertyCondition('status', 1)
          ->fieldCondition('field_confirmed', 'value', 1)
          ->fieldCondition('field_assassin', 'target_id', $player->uid);

  $kills = $query->execute();
  
  if (count($kills) < 1) return array();
  
  $targets = array();
  foreach($kills['node'] as $nid => $kill) {
    $kill = node_load($nid);
    array_push($targets, $kill->field_target['und'][0]['target_id']);
  }
  return $targets;
}

function _get_target_current($player) {
  if (!isset($player->field_current_target['und']))     return array();
  if (count($player->field_current_target['und']) < 1)  return array();
  
  return array($player->field_current_target['und'][0]['target_id']);
}

function _get_target_pending($player) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'kill')
          ->propertyCondition('status', 1)
          ->fieldCondition('field_confirmed', 'value', 0)
          ->fieldCondition('field_assassin', 'target_id', $player->uid);

  $unconfirmed = $query->execute();
  
  if (count($unconfirmed) < 1) return array();

  $pending = node_load(key($unconfirmed['node']));
  return array($pending->field_target['und'][0]['target_id']);
}