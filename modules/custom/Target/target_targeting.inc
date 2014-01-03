<?php

//////// ** Possible to remove ** //////////

/**
 * Look for kills of a specific assassin and return the targets
 */
/*
function _target_users_kill_warrants($uid) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'kill')
            ->propertyCondition('status', 1)
            ->fieldCondition('field_assassin', 'target_id', $uid);

    $kills = $query->execute();

    if (count($kills) < 1) return array();
    $kills = node_load_multiple(array_keys($kills['node']));
    $targeted_players = array();
    foreach ($kills as $key => $value) {
      $targeted_players[] = $value->field_target['und'][0]['target_id'];
    }
    return $targeted_players;
}
*/