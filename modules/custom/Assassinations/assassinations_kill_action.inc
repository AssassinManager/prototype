<?php

/**
 * implements hook_rules_action_info().
 */
function _create_kill_action() {
    return array(
          'label' => t('Killed Target'),
          'group' => t('Assassin Manager'),
          'parameter' => array(
              'assassin' => array(
                'type' => 'user',
                'label' => t('Assassin'),
                'description' => t("The assain."),
                'translatable' => TRUE,
              ),
              'target' => array(
                'type' => 'user',
                'label' => t('Target'),
                'description' => t("The target."),
                'translatable' => TRUE,
              ),
            ),
          'base' => '_assassinations_am_kill',
        );
}

function _assassinations_am_kill($assassin, $target) {
    
    if ($assassin == null) return false;
    if (!isset($assassin)) return false;
    
    if ($target == null) return false;
    if (!isset($target)) return false;

    $assassin->field_pending_target['und'][0]['target_id'] = $target->uid;

    //if (!module_exists('messaging')) return false;

    //messaging_send_message_to_organizers("test", "test");
    
    return true;
}
