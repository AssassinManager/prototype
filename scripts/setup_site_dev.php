<?php

$mandrill_api_key = 'gaJNp0umNNprQZSVpiHAEQ';

$rankings_leaderboard_title = 'Rankings and Leaderboard';
$terms_title = 'Terms of use';
$terms_body = 'We no liable eyo!';

$disclaimer_title = 'Disclaimer';
$disclaimer_body = 'Be aware that we will capture you and sell your organs!';


//////
//////
//////
//////
//////
//////

print("Starting site setup\n");

////// * Enabling features & modules * //////

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
                    "am_tools",
                    "site_disclaimer",
                    "registration_role",
                    "front_page",
                    "login_redirect");

$dev_modules = array( "admin_menu",
                      "devel",
                      "module_filter");

module_enable(array('features'));

print("Enabling Features\n");
module_enable($am_features);

print("Enabling AM Modules\n");
module_enable($am_modules);

print("Enabling Dev Modules\n");
module_enable($dev_modules);

drupal_flush_all_caches();


////// * Pages configs * //////

print("Creating Basic Pages\n");

$roles = user_roles();

global $base_url;
$disclaimer_url = $base_url . '/content/' . str_replace(' ' , '-', strtolower($disclaimer_title));
$terms_url = $base_url . '/content/' . str_replace(' ' , '-', strtolower($terms_title));

$registration_title = 'Registration terms';
$registration_body = '<a href="' . $disclaimer_url . '" target="_blank">Disclaimer</a> -  <a href="' . $terms_url . '" target="_blank">Terms of use</a>';

_ss_basic_page($terms_title, $terms_body);
_ss_basic_page($disclaimer_title, $disclaimer_body);
_ss_basic_page($registration_title, $registration_body);
_ss_basic_page($rankings_leaderboard_title, '');
_ss_setup_blocks();


////// * Variables setting for modules * //////

print("Configuring Modules and Pages\n");

variable_set('theme_default','bootstrap_red');
variable_set('site_disclaimer_node_title', $registration_title);
variable_set('registration_role_roles', array_search('Player', $roles));
variable_set('mandrill_api_key', $mandrill_api_key);
variable_set('login_redirect_status', 1);
variable_set('login_redirect_parameter_name', "/");

_ss_front_page();

print("Setup Complete\n");

////// * Pages creation & config functions * //////

function _ss_basic_page($title, $body) {

  $node = new StdClass();
  $node->type = 'page';

  node_object_prepare($node);

  $node->language = 'und';

  $node->title = $title;
  $node->field_body['und'][0]['format'] = 'filtered_html';
  $node->field_body['und'][0]['value'] = $body;
  if (strlen($body) > 0)
    $node->field_body['und'][0]['safe_value'] = "<p>" . $body ."<p>";

  node_save($node);
}

function _ss_setup_blocks() {

  $result = db_update('block')
            ->fields(array(
                            'region' => 'content',
                            'pages' => str_replace(' ' , '-', strtolower($rankings_leaderboard_title)),
                            'visibility' => 1
                          )
                        )
            ->condition('delta', array('prizes-block', 'leaderboard-block'), 'IN')
            ->execute();
}

function _ss_front_page() {
  $roles = user_roles();
  variable_set('front_page_enable', 1);

  _ss_initialize_front_page();
  _ss_front_page_for_role('user', array_search('Player', $roles));
  _ss_front_page_for_role('content/game', array_search('Organizer', $roles));
}

function _ss_initialize_front_page() {
  $roles = user_roles();
  foreach ($roles as $rid => $role) {
    $result = db_insert('front_page')
              ->fields(array(
                            'rid' => $rid,
                            'mode' => "",
                            'data' => "",
                            'filter_format' => ""
                            )
                       )
              ->execute();
  }
}

function _ss_front_page_for_role($page, $rid) {
  $result = db_update('front_page')
            ->fields(array(
                          'mode' => 'alias',
                          'data' => $page
                          )
                     )
            ->condition('rid', $rid)
            ->execute();
  return $result;
}

?>