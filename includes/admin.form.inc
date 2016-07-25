<?php

/**
 * @file
 * Administration forms and submit handling for upitt_dashboard module.
 */

/**
 * Administration and configuration form
 *
 * @ingroup forms
 *
 * @todo break out non-settings elements into their own form.
 *
 * @return array
 *   The Drupal form definition.
 */
function upitt_dashboard_admin_form(array $form, array &$form_state) {
  $form = array(
    'options' => array(
      '#type' => 'fieldset',
      '#title' => t('University of Pittsburgh Dashboard Settings'),
      'permission_text' => array(
        '#type' => 'textfield',
        '#title' => t('Access Permission'),
        '#description' => t('Permission which controls whether or not a dashboard is available.'),
        '#default_value' => variable_get('upitt_dashboard_permission', 'administer site configuration'),
      ),
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    ),
    'reset' => array(
      '#type' => 'submit',
      '#value' => t('Reset to defaults'),
    ),
  );
  return $form;
}

/**
 * Function that sets the Drupal variables with user's input.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function upitt_dashboard_admin_form_submit(array $form, array &$form_state) {
  drupal_set_message(t('The settings have been updated!'));
  $id = $form_state['triggering_element']['#id'];
  switch ($id) {
    case 'edit-submit':
      variable_set('upitt_dashboard_permission', $form_state['values']['permission_text']);
      break;

    case 'edit-reset':
      variable_del('upitt_dashboard_permission');
      break;
  }
}

