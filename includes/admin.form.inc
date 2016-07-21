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
  $reports = _get_reports_variable_get();
  $form = array(
    'options' => array(
      '#type' => 'fieldset',
      '#title' => t('University of Pittsburgh Dashboard Settings'),
      'display_generation_fieldset' => array(
        '#type' => 'fieldset',
        '#title' => t('Available report blocks'),
        '#description' => t('Controls the blocks that become available for each user to add to their dashboard.'),
        'test1' => array(
          '#type' => 'checkbox',
          '#title' => t('Dashboard report TEST Block.'),
          '#default_value' => $reports['test1'],
        ),
        'test2' => array(
          '#type' => 'checkbox',
          '#title' => t('Dashboard report 2 TEST Block.'),
          '#default_value' => $reports['test2'],
        ),
      ),
      'permission_text' => array(
        '#type' => 'textfield',
        '#title' => t('Access Permission'),
        '#description' => t('Permission which controls whether or not a dashboard is available.'),
        '#default_value' => variable_get('upitt_dashboard_permission', 'access dashboard'),
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

function _get_reports_form_values($form_state) {
  if ($form_state['values']['test1'] > 0) {
    $vals['test1'] = $form_state['values']['test1'];
  }
  if ($form_state['values']['test2'] > 0) {
    $vals['test2'] = $form_state['values']['test2'];
  }
  return serialize($vals);
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
      variable_set('upitt_dashboard_block_bids', _get_reports_form_values($form_state));
      variable_set('upitt_dashboard_permission', $form_state['values']['permission_text']);
      break;

    case 'edit-reset':
      variable_del('upitt_dashboard_block_bids');
      variable_del('upitt_dashboard_permission');
      break;
  }
}

