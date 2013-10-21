<?php

module_load_include('module', 'messaging');

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

function _assassinations_am_deny($target_uid, $assassin_uid) {
    
    if ($assassin_uid == null) return;
    if ($target_uid == null) return;

    messaging_reply_to_kill($assassin_uid, $target_uid);
}

function _assassinations_am_kill($assassin_uid, $target_uid) {
    
    if ($assassin_uid == null) return;
    if ($target_uid == null) return;

    /*
    $assassin = user_load($assassin_uid);
	$edit = array(
	  'field_pending_target_target_id' => array(
	    'und' => array(
	      0 => array(
	        'value' => $target_uid,
	      ),
	    ),
	  ),
	);

    watchdog("edit", "<pre>" . print_r($edit, 1) . "</pre>");
    watchdog("assassin", "<pre>" . print_r($assassin, 1) . "</pre>");

	user_save($assassin, $edit);
	*/

    $assassin_name = _get_user_name(user_load($assassin_uid));
    $message = $assassin_name . " said he eliminated you. Do you confirm?";

    $recipients[] = array('target_id' => $target_uid);
    messaging_send_message("Target termination", $message, $recipients);
}
