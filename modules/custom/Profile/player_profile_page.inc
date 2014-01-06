<?php

function player_profile_pp_status($build) {

  $alive = $build['#account']->field_alive['und'][0]['value'];
  $suspended = $build['#account']->field_suspended['und'][0]['value'];

  $status = "In good shape.";
  if ($suspended)   $status = 'Suspended!';
  else if (!$alive) $status = 'Eliminated!';

  return $form['player_status'] = array(
                '#type' => 'item',
                '#title' => t('Your Status:'),
                '#markup' => $status,
            );
}

function player_profile_pp_game($build) {

  module_load_include('module', 'am_tools', 'am_tools');

  $game_nid = am_get_game_nid();
  $status = "No valid game found.";

  if ($game_nid > 0) {
    $game = node_load($game_nid);
    $start_time = $game->field_time['und'][0]['value'];
    $end_time = $game->field_time['und'][0]['value2'];

    $start_time = strtotime($start_time);
    $end_time = strtotime($end_time);

    if ($start_time > time()) {
      $interval = $start_time - time();
      if ($interval > 86400) { // 1 Day
        $time = $interval - 86400;
        $status = 'Game starts in ' . $time . ' days.';
      }
      else if ($interval > 3600) { // 1 Hour
        $status = 'Game starts in ' . date("H", $interval) . ' hours';
        if (date("i", $interval) > 0) $status = $status . ' and .' . date("i", $interval) . ' minutes';
        $status = $status . '.';
      }
      else if ($interval > 60) { // 1 Minute
        $status = 'Game starts in ' . date("i", $interval) . ' minutes.';
      }
      else {
        $status = 'Game starts in ' . date("s", $interval) . ' seconds.';
      }
    }
    else {
      $interval = $end_time - time();
      if ($interval > 86400) { // 1 Day
        $time = $interval / 86400;
        $status = floor($time) . ' days left in game.';
      }
      else if ($interval > 3600) { // 1 Hour
        $status = date("H", $interval) . ' hours';
        if (date("i", $interval) > 0) $status = $status . ' and .' . date("i", $interval) . ' minutes';
        $status = $status . ' left in game.';
      }
      else if ($interval > 60) { // 1 Minute
        $status = date("i", $interval) . ' minutes left in game.';
      }
      else {
        $status = date("s", $interval) . ' seconds left in game!';
      }
    }
  }

  return $form['game_status'] = array(
                '#type' => 'item',
                '#title' => t('Game Status:'),
                '#markup' => $status,
            );
}