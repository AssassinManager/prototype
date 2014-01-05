<?php

$am_features = array( "game_content_type",
                      "kill_content_type",
                      "license_content_type",
                      "message_content_type",
                      "prize_content_type",
                      "user_fields");

$am_modules = array("game",
                    "leaderboard",
                    "license_to_kill",
                    "messaging",
                    "player_profile",
                    "suspend",
                    "target",
                    "tools");

module_enable($am_features);
module_enable($am_modules);

?>