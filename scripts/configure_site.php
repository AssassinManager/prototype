<?php

function _get_r_l_title() {
  $rankings_leaderboard_title = 'Rankings and Leaderboard';
  return $rankings_leaderboard_title;
}

$terms_title = 'Terms of use';
$terms_body = 'We no liable eyo!';

$disclaimer_title = 'Disclaimer';
$disclaimer_body = 'Be aware that we will capture you and sell your organs!';

$roles = user_roles();


////// * Pages * //////

print("Creating Pages\n");

$terms_title = 'Terms of use';
$terms_body = 'We no liable eyo!';

$disclaimer_title = 'Disclaimer';
$disclaimer_body = 'Be aware that we will capture you and sell your organs!';

global $base_url;
$disclaimer_url = $base_url . '/content/' . str_replace(' ' , '-', strtolower($disclaimer_title));
$terms_url = $base_url . '/content/' . str_replace(' ' , '-', strtolower($terms_title));

$registration_title = 'Registration terms';
$registration_body = '<a href="' . $disclaimer_url . '" target="_blank">Disclaimer</a> -  <a href="' . $terms_url . '" target="_blank">Terms of use</a>';

_ss_basic_page($terms_title, $terms_body);
_ss_basic_page($disclaimer_title, $disclaimer_body);
$reg_nid = _ss_basic_page($registration_title, $registration_body);
_ss_basic_page(_get_r_l_title(), '');


////// * Blocks * //////

print("Configuring Blocks\n");
_ss_setup_blocks();
_ss_setup_count_block();


////// * Front pages * //////

print("Assigning Front Pages\n");

$player_rid = array_search('Player', $roles);
$organizer_rid = array_search('Organizer', $roles);
$administrator_rid = array_search('administrator', $roles);

variable_set('front_page_enable', 1);

$game_page = str_replace(' ' , '-', strtolower(variable_get('site_name', "404")));
_ss_front_page();
_ss_front_page_for_role('user', $player_rid);
_ss_front_page_for_role('content/' . $game_page, $organizer_rid);
_ss_front_page_for_role('content/' . $game_page, $administrator_rid);


////// * Login pages * //////

print("Assigning Login Pages\n");

$result = db_insert('login_destination')
          ->fields(array(
                        'id' => 1,
                        'triggers' => "a:1:{s:5:\"login\";s:5:\"login\";}",
                        'roles' => "a:1:{i:5;s:1:\"5\";}",
                        'pages' => "",
                        'destination' => "<front>",
                        )
                   )
          ->execute();


////// * Disclaimer * //////

print("Configuring Disclaimer\n");

variable_set('site_disclaimer_node_title', 'Registration terms');
variable_set('site_disclaimer_node_id', $reg_nid);
variable_set('site_disclaimer_fieldset', 1);
variable_set('site_disclaimer_title', 'User Agreement');


////// * Doing Functions * //////

function _ss_setup_blocks() {
  $page = 'content/' . str_replace(' ' , '-', strtolower(_get_r_l_title()));
  $result = db_update('block')
          ->fields(array(
                          'region' => 'content',
                          'status' => 1,
                          'pages' => $page,
                          'visibility' => 1
                        )
                      )
          ->condition('delta', array('prizes-block', 'leaderboard-block'), 'IN')
          ->execute();
}
function _ss_setup_count_block() {
  $result = db_update('block')
          ->fields(array(
                          'region' => 'header',
                          'status' => 1,
                        )
                      )
          ->condition('delta', 'jquery_countdown_timer')
          ->execute();
}
function _ss_basic_page($title, $body) {

  $node = new StdClass();
  $node->type = 'page';

  node_object_prepare($node);

  $node->language = 'und';

  $node->title = $title;
  $node->body['und'][0]['format'] = 'filtered_html';
  $node->body['und'][0]['value'] = $body;
  $node->body['und'][0]['safe_value'] = "<p>" . $body ."<p>";

  node_save($node);
  
  return $node->nid;
}

function _ss_front_page() {
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