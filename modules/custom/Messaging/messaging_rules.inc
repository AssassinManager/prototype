<?php

function messaging_default_rules_configuration() {
  $configs = array();

  $am_notify = '{ "rules_message_notify" : {
                  "LABEL" : "Message Notify",
                  "PLUGIN" : "reaction rule",
                  "TAGS" : [ "Assassin Manager" ],
                  "REQUIRES" : [ "messaging", "rules", "comment" ],
                  "ON" : {
                    "node_insert--message" : { "bundle" : "message" },
                    "comment_insert--comment_node_message" : { "bundle" : "comment_node_message" }
                  },
                  "DO" : [ { "am_notifier" : { "message" : [ "node" ] } } ]
                }
              }';

  $am_org_msg = '{ "rules_new_target_message" : {
                          "LABEL" : "New Target Message",
                          "PLUGIN" : "reaction rule",
                          "OWNER" : "rules",
                          "TAGS" : [ "Messaging" ],
                          "REQUIRES" : [ "rules", "messaging" ],
                          "ON" : { "user_update" : [] },
                          "IF" : [
                            { "user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "5" : "5" } } } },
                            { "AND" : [] },
                            { "NOT data_is_empty" : { "data" : [ "account:field-current-target" ] } },
                            { "AND" : [] },
                            { "NOT data_is" : {
                                "data" : [ "account-unchanged:field-current-target" ],
                                "value" : [ "account:field-current-target" ]
                              }
                            }
                          ],
                          "DO" : [ { "am_messages" : { "Player" : [ "account" ] } } ]
                        }
                      }';

  $configs['rules_message_notify'] = rules_import($am_notify);
  $configs['rules_message_org_msg'] = rules_import($am_org_msg);

  return $configs;
}

/**
 * Actions for Message creation
 * implements hook_rules_action_info().
 */
function _create_messages_action() {
  return array(
          'label' => t('New Target Message'),
          'group' => t('Assassin Manager'),
          'base' => '_messaging_am_create_org_msg',
          'parameter' => array(
              'Player' => array(
                'type' => 'user',
                'label' => t('Player'),
                'translatable' => TRUE,
              ),
            ),
        );
}

function _messaging_am_create_org_msg($player) {

  $target = user_load($player->field_current_target['und'][0]['target_id']);

  module_load_include('module', 'messaging', 'messaging');
  module_load_include('module', 'am_tools', 'am_tools');

  $subject = "Assassin Manager job update";
  $body = "You have a new target: " . am_tools_user_name($target);
  $to = array($player->uid);

  messaging_send_message($subject, $body, $to);
}