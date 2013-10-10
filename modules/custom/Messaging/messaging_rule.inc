<?php

function messaging_default_rules_configuration() {
  $configs = array();

   $rule = '{ "rules_messaging_email" : {
    "LABEL" : "Messaging Email",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "Assassin Manager" ],
    "REQUIRES" : [ "rules", "messaging" ],
    "ON" : { "node_insert--message" : { "bundle" : "message" } },
    "IF" : [ { "data_is" : { "data" : [ "node:field-send-email" ], "value" : 1 } } ],
    "DO" : [
      { "am_mail" : {
          "subject" : [ "node:title" ],
          "message" : [ "node:field-body:value" ],
          "from" : [ "node:author" ],
          "to" : [ "node:field-recipients" ]
        }
      }
      ]
    }
  }';
  $configs['rules_messaging_email'] = rules_import($rule);

  return $configs;
}