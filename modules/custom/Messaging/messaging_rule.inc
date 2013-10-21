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
  $configs['rules_message_notify'] = rules_import($am_notify);

  return $configs;
}