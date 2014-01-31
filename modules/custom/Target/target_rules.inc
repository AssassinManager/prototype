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

    $am_targets = '{"rules_am_targets" : {
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
                    "DO" : [ { "am_targeting" : { "Kill" : [ "node" ] } } ]
                  }
                }';

    $am_targets_s = '{"rules_am_targets_suspension" : {
                      "LABEL" : "Assign Targets after Suspension",
                      "PLUGIN" : "reaction rule",
                      "OWNER" : "rules",
                      "TAGS" : [ "Assassin Manager" ],
                      "REQUIRES" : [ "rules", "target" ],
                      "ON" : { "user_update" : [] },
                      "IF" : [
                        { "user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "5" : "5" } } } },
                        { "AND" : [] },
                        { "data_is" : { "data" : [ "account:field-suspended" ], "value" : 1 } }
                      ],
                      "DO" : [ { "am_targeting_s" : { "Player" : [ "account" ] } } ]
                    }
                  }';

  $configs['rules_am_targets_s'] = rules_import($am_targets_s);
  $configs['rules_am_rankings'] = rules_import($am_rankings);
  $configs['rules_am_targets'] = rules_import($am_targets);

  return $configs;
}

/**
 * implements hook_rules_action().
 */
function _update_ranking_action() {

  return array(
          'label' => t('Update Rankings'),
          'group' => t('Assassin Manager'),
          'base' => 'target_update_rankings',
        );
}

/**
 * implements hook_rules_action().
 */
function _update_target_action() {
  return array(
          'label' => t('Update Target'),
          'group' => t('Assassin Manager'),
          'base' => '_target_update_target',
          'parameter' => array(
            'Kill' => array(
                'type' => 'node',
                'label' => t('The Kill'),
                'translatable' => FALSE,
              ),
            ),
        );
}

/**
 * implements hook_rules_action().
 */
function _update_target_s_action() {
  return array(
          'label' => t('Update Target Suspension'),
          'group' => t('Assassin Manager'),
          'base' => '_target_update_target_s',
          'parameter' => array(
            'Player' => array(
                'type' => 'user',
                'label' => t('The Player'),
                'translatable' => FALSE,
              ),
            ),
        );
}