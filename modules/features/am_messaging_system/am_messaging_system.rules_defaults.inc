<?php
/**
 * @file
 * am_messaging_system.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function am_messaging_system_default_rules_configuration() {
  $items = array();
  $items['rules_message_read_system_comment'] = entity_import('rules_config', '{ "rules_message_read_system_comment" : {
      "LABEL" : "Message Read System - Comment",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "messages_read", "comment" ],
      "ON" : [ "comment_view" ],
      "IF" : [
        { "AND" : [
            { "node_is_of_type" : {
                "node" : [ "comment:node" ],
                "type" : { "value" : { "message" : "message" } }
              }
            },
            { "messages_read_rules_condition_reply_viewed" : { "comment" : [ "comment" ] } }
          ]
        }
      ],
      "DO" : [ { "messages_read_action_viewed" : { "comment" : [ "comment" ] } } ]
    }
  }');
  $items['rules_message_read_system_node'] = entity_import('rules_config', '{ "rules_message_read_system_node" : {
      "LABEL" : "Message Read System - Node",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_view" ],
      "IF" : [
        { "AND" : [
            { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "message" : "message" } } } },
            { "data_is" : {
                "data" : [ "site:current-user" ],
                "op" : "IN",
                "value" : [ "node:field-recipient-s-" ]
              }
            }
          ]
        }
      ],
      "DO" : [
        { "list_add" : {
            "list" : [ "node:field-read-by" ],
            "item" : [ "site:current-user" ],
            "unique" : 1
          }
        }
      ]
    }
  }');
  $items['rules_user_message_send_sms'] = entity_import('rules_config', '{ "rules_user_message_send_sms" : {
      "LABEL" : "User message send SMS",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "user message" ],
      "REQUIRES" : [ "rules", "twilio_sms" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "AND" : [
            { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "message" : "message" } } } },
            { "data_is" : { "data" : [ "node:field-send-sms" ], "value" : 1 } }
          ]
        }
      ],
      "DO" : [
        { "twilio_sms_action_send_sms" : {
            "user" : [ "node:field-recipient-s-:0" ],
            "message" : "[node:field-message:value]"
          }
        }
      ]
    }
  }');
  return $items;
}
