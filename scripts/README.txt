Automatic Install

run sh ./full_install.sh 'site location' 'mysql user' 'mysql password'
During the process, accept the DB creation with 'y'


Manual Install

Download drupal to the directory you want to store you site at (drush dl is nice)
Then go to this directory
Then go to 'sites' directory
Then remove the 'all' (drupal_site/sites/all) directory --> rm -rf all
Clone the git repo into a new 'all' directory --> git clone git@github.com:username/prototype.git all

Go to 'all/scripts' directory
Move Install Profiles/assassin_manager_dev to the _drupal_site/profiles folder (../../../profiles)

Then do sh ./install_am.sh
During the process, accept the DB creation with 'y'