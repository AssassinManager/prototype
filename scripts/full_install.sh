#!/bin/bash
# Assassin Manager setup script

if [ -z "$3" ]
  then
  	echo " Missing arguments"
    echo " Use:"
    echo "     full_install.sh 'site location' 'mysql user' 'mysql password'"
    echo ""
    echo " Will install Assassin Manager at the given site location"
    echo ""
    exit
fi


echo "BEGIN Components Download"

# download drupal
drush dl -r $1

# move drupal to the given directory and remove the old one
mkdir $1
mv drupal-*/* $1
rm -rf drupal-*

# move the content of the git repo into he sites/all directory
rm -rf $1/sites/all
cp -rf .. $1/sites/all

# move to that directory
cd $1/sites/all/scripts

# copy the installation profile
cp -rf Install\ profiles/assassin_manager_dev ../../../profiles


echo "BEGIN Assassin Manager Install"

echo
drush site-install assassin_manager_dev --db-url=mysql://$2:$3@localhost/am1 --site-name="Assassin Manager 1" --account-name=admin --account-pass=99REDballoons
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