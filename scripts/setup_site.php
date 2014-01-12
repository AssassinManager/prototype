<?php

$am_features = array( "game_content_type",
                      "kill_content_type",
                      "license_content_type",
                      "message_content_type",
                      "prize_content_type",
                      "user_fields",
                    );

$am_modules = array("am_tools",
                    "game",
                    "leaderboard",
                    "license_to_kill",
                    "messaging",
                    "player_profile",
                    "suspend",
                    "target",
                   );

print("Disabling updates\n");
module_disable(array("update"));

print("Enabling Features\n");
module_enable(array('features'));
module_enable($am_features);

print("Enabling AM Modules\n");
module_enable($am_modules);

?>