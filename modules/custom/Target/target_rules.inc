<?php

function target_default_rules_configuration() {
    $configs = array();

    $am_rankings = '{ "rules_update_rankings" : {
                      "LABEL" : "Update Rankings",
                      "PLUGIN" : "reaction rule",
                      "OWNER" : "rules",
                      "TAGS" : [ "Assassin Manager" ],
                      "REQUIRES" : [ "rules", "target" ],
                      "ON" : { "node_update--kill" : { "bundle" : "kill" } },
                      "IF" : [
                        { "data_is" : { "data" : [ "node:field-confirmed" ], "value" : 1 } },
                        { "AND" : [] },
                        { "data_is" : { "data" : [ "node:field-confirmed" ], "value" : 1 } }
                      ],
                      "DO" : [ { "am_ranking" : [] } ]
                    }
                  }';

    $am_targets = '{ "rules_assign_targets" : {
                     "LABEL" : "Assign Targets After Kill Confirmed",
                     "PLUGIN" : "reaction rule",
                     "OWNER" : "rules",
                     "TAGS" : [ "Assassin Manager" ],
                     "REQUIRES" : [ "rules", "target" ],
                     "ON" : { "node_update--kill" : { "bundle" : "kill" } },
                     "IF" : [
                       { "NOT data_is_empty" : { "data" : [ "node:field-target" ] } },
                       { "AND" : [] },
                       { "data_is" : { "data" : [ "node:field-confirmed" ], "value" : 1 } }
                     ],
                     "DO" : [ { "am_targeting" : [] } ]
                    }
                 }';

  $configs['rules_am_rankings'] = rules_import($am_rankings);
  $configs['rules_am_targets'] = rules_import($am_targets);

  return $configs;
}

/**
 * implements hook_user_insert().
 */
function target_user_insert(&$edit, $account, $category) {

  module_load_include('module', 'am_tools', 'am_tools');
  $player_uids = am_tools_players_uids();

  $edit->field_rank['und'][0]['value'] = count($player_uids);
  //user_save($account);
}

function _update_ranking_action() {

  return array(
          'label' => t('Update Rankings'),
          'group' => t('Assassin Manager'),
          'base' => '_am_update_rankings',
        );
}

function _am_update_rankings() {

  module_load_include('module', 'am_tools', 'am_tools');
  $player_uids = am_tools_players_uids();

  $query = db_select('node', 'n')
          ->fields('n', array('uid'))
          ->condition('type', 'kill')
          ->condition('uid', $player_uids, 'IN')
          ->groupBy('n.uid');
  $query->addExpression('COUNT(nid)', 'kill_count');
  $result = $query->execute();

  $usersKills = array();
  while($record = $result->fetchAssoc()) {
      $usersKills[$record['uid']] = $record["kill_count"];
  }
  if(count($usersKills) == 0) return;

  ksort($usersKills, SORT_NUMERIC);

  $counter = 0;
  foreach ($usersKills as $key => $value) {
      $counter++;

      $user = user_load($key);
      $user->field_rank['und'][0]['value'] = $counter;
      user_save($user);
      unset($user);
  }

  foreach ($player_uids as $value) {
      if (array_key_exists($value, $usersKills)) continue;

      $counter++;
      $user = user_load($value);
      $user->field_rank['und'][0]['value'] = $counter;
      user_save($user);
      unset($user);
  }
}


/**
 * implements hook_rules_action_info().
 */

function _update_targets_action() {
  return array(
          'label' => t('Update Targets'),
          'group' => t('Assassin Manager'),
          'base' => 'target_assign_targets',
        );
}