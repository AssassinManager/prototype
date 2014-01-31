#!/bin/bash
# Assassin Manager setup script

echo "BEGIN Assassin Manager Install"

drush site-install assassin_manager_dev --db-url=mysql://root:drupaladm1n@localhost/am1 --site-name="Assassin Manager 1" --account-name=admin --account-pass=99REDballoons
echo

drush scr setup_site.php
drush cc all
echo

drush scr configure_site.php
echo

drush scr generate_prizes.php
echo

drush scr generate_game.php
echo

drush scr generate_users.php

echo "Assassin Manager functional"