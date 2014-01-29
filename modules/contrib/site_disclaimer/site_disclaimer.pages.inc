<?php

/**
 * @file
 * Page callbacks for the Site Disclaimer module.
 */

/**
 * Display the Site Disclaimer, when a user needs to confirm them after registering.
 */
function site_disclaimer_confirm($form, $form_state, $langcode = NULL, $preview = FALSE) {
  global $user;

  $title = check_plain(variable_get('site_disclaimer_title', SITE_DISCLAIMER_DEFAULT_TITLE));
  if (!$preview) {
    drupal_set_title($title);
  }

  // Don't show the terms form if site_disclaimer is disabled or user already accepted the latest version.
  // We are doing a check here users may navigate to this page URL (from saved or cached link or ...).
  $site_disclaimer_enabled = _site_disclaimer_enabled($langcode);
  $site_disclaimer_version = variable_get('site_disclaimer_version', 1);
  if (!$site_disclaimer_enabled
    || !($preview || !isset($user->data['site_disclaimer']) || $user->data['site_disclaimer'] < $site_disclaimer_version)) {
    return array('#markup' => t('There were no changes.'));
  }

  $changes = filter_xss_admin(_site_disclaimer_variable_get_translated('site_disclaimer_version_details', '', $langcode));
  if (empty($changes)) {
    $changes = '.';
  }
  else {
    $changes = ':<br />' . $changes . '<br /><br />';
  }
  $form = array();
  $form['intro'] = array(
    '#type' => 'item',
    '#markup' => t('There were recent changes to the %terms!changes Please review the new %terms below. You must accept the following to continue.',
      array(
        '%terms' => $title,
        '!changes' => $changes,
      )),
  );
  site_disclaimer_form_user_register_form_alter($form, $form_state, 'site_disclaimer_confirm', $langcode, $preview);
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Continue'),
    '#weight' => 50,
  );

  return $form;
}

/**
 * Submit handler for site_disclaimer_confirm()
 */
function site_disclaimer_confirm_submit($form, &$form_state) {
  global $user;
  $edit = array(
    'data' => array('site_disclaimer' => $form_state['values']['I_agree']),
  );
  user_save($user, $edit);
}

