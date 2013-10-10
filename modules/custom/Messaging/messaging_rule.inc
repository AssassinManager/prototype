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

  $sms_rule = '{ "rules_messaging_sms" : {
    "LABEL" : "Messaging SMS",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "Assassin Manager" ],
    "REQUIRES" : [ "rules", "messaging" ],
    "ON" : { "node_insert--message" : { "bundle" : "message" } },
    "IF" : [ { "data_is" : { "data" : [ "node:field-send-sms" ], "value" : 1 } } ],
    "DO" : [
      { "am_sms" : {
          "subject" : [ "node:title" ],
          "message" : [ "node:field-body:value" ],
          "from" : [ "node:author" ],
          "to" : [ "node:field-recipients:0" ]
        }
      }
      ]
    }
  }';

  $email_reply_rule = '{ "messaging_messaging_email_reply" : {
    "LABEL" : "Messaging Email Reply",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "Assassin Manager" ],
    "REQUIRES" : [ "rules", "messaging", "comment" ],
    "ON" : { "comment_insert--comment_node_message" : { "bundle" : "comment_node_message" } },
    "IF" : [ { "data_is" : { "data" : [ "comment:field-send-email" ], "value" : 1 } } ],
    "DO" : [
      { "am_mail" : {
          "subject" : [ "comment:node:title" ],
          "message" : [ "comment:comment-body:value" ],
          "from" : [ "comment:author" ],
          "to" : [ "comment:field-recipients" ]
        }
      }
      ]
    }
  }';

  $configs['rules_messaging_email']           	= rules_import($email_rule);
  $configs['rules_messaging_sms'] 				= rules_import($sms_rule);
  $configs['messaging_messaging_email_reply'] 	= rules_import($email_reply_rule);

  return $configs;
}