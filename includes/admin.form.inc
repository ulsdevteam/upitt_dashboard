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
      '#title' => t('Lorem ipsum '),
      'sitejump_domain' => array(
        '#type' => 'textfield',
        '#title' => t('Bibendum phasellus venenatis'),
        '#description' => t('Sollicitudin ut. Ligula pulvinar turpis vehicula.'),
        '#default_value' => variable_get('islandora_upitt_sitejump_domain', 'gamera.library.pitt.edu'),
      ),
      'show_sitejump' => array(
        '#type' => 'checkbox',
        '#title' => t('Dolor sit amet, pharetra facilisi faucibus ligula lobortis in.'),
        '#description' => t('Pede risus vel, mauris congue id mi ultrices lobortis ligula, vel rutrum. Quam auctor sit ultricies sit ut, proin et, mi nibh mauris suscipit.'),
        '#default_value' => variable_get('islandora_upitt_show_sitejump', 1),
      ),
      'sitejump_tab_text' => array(
        '#type' => 'textfield',
        '#title' => t('Fermentum sit'),
        '#description' => t('Cras euismod ultrices metus pellentesque duis amet, nonummy suspendisse.'),
        '#default_value' => variable_get('islandora_upitt_sitejump_tab_text', 'Site Jump'),
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
function upitt_dashboard_admin_submit(array $form, array &$form_state) {
  drupal_set_message(t('The settings have been updated!'));
  $id = $form_state['triggering_element']['#id'];
  switch ($id) {
    case 'edit-submit':
      variable_set('upitt_dashboard_namespace', $form_state['values']['namespace']);
      variable_set('upitt_dashboard_sites', $form_state['values']['sites']);
      break;

    case 'edit-reset':
      variable_del('upitt_dashboard_namespace');
      variable_del('upitt_dashboard_sites');
      break;
  }
}
