<?php

function messaging_default_rules_configuration() {
  $configs = array();

  $email_rule = '{ "rules_messaging_email" : {
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
  
  $configs['messaging_messaging_email_reply'] 	= rules_import($email_reply_rule);

  return $configs;
}