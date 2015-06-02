<?php
/**
 * @file
 * File for description
 */

class facetapi_exposed_filters_plugin_exposed_form extends views_plugin_exposed_form_basic {

  function summary_title() {
    return t('Settings');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['facetapi_exposed_filters_facets'] = array('default' => array());
    $options['facetapi_exposed_filters_render'] = array('default' => FALSE, 'bool' => FALSE);
    return $options;
  }

  /**
   * Set the options on the form, and include the facets.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $facets = facetapi_get_block_info(array('block'));
    $available_facets = array();
    foreach ($facets as $facet_key => $facet ) {
      $available_facets[$facet_key] = $facet['info'];
    }
    $form['facetapi_exposed_filters_facets'] = array(
      '#type' => 'checkboxes',
      '#options' => $available_facets,
      '#title' => t('Facet blocks to include in the exposed form.'),
      '#default_value' => $this->options['facetapi_exposed_filters_facets'],
    );

    $form['facetapi_exposed_filters_render'] = array(
      '#type' => 'checkbox',
      '#title' => t('Send the form as a render array.'),
      '#description' => t('If rendering as an array, you will need an additional module, or template.php to render out the exposed form. This is ideal if you need to move the form objects.'),
      '#default_value' => $this->options['facetapi_exposed_filters_render'],
    );
  }

  function exposed_form_alter(&$form, &$form_state) {
    parent::exposed_form_alter($form, $form_state);
    if (!empty($this->options['facetapi_exposed_filters_facets'])) {
      // Grab the list of exposed filters and add them as filters.
      $form['#facet_filters'] = array(
        '#type' => 'hidden',
        '#ids' => array(),
      );
      foreach ($this->options['facetapi_exposed_filters_facets'] as $facet) {
        if (!empty($facet)) {
          $id = 'facet_filter_' . $facet;
          $form[$id] = array();
          $form[$id]['#facet_id'] = $facet;
          $form[$id]['#id'] = 'edit-' . $id;
          // // Pass information to the #info for use in template_views_
          $form['#info'][$id] = array();
          $form['#info'][$id]['value'] = $id;
          $form['#facet_filters']['#ids'][] = $facet;
        }
      }
    }
    // Set whether or not to send the form as a render array or html.
    $form['#facetapi_exposed_filters_render'] = FALSE;
    if (!empty($this->options['facetapi_exposed_filters_render'])) {
      $form['#facetapi_exposed_filters_render'] = TRUE;
    }
  }

  /**
   * Outputs the render array of the exposed form.
   */
  function render_exposed_form($block = FALSE) {
    // Nearly Identical to parent::render_exposed_block, but the form isn't rendered.
    // We need this to allow for the form to be hooked after the build, so the facets will load.
    // Deal with any exposed filters we may have, before building.
    $form_state = array(
      'view' => &$this->view,
      'display' => &$this->display,
      'method' => 'get',
      'rerender' => TRUE,
      'no_redirect' => TRUE,
      'always_process' => TRUE,
    );

    // Some types of displays (eg. attachments) may wish to use the exposed
    // filters of their parent displays instead of showing an additional
    // exposed filter form for the attachment as well as that for the parent.
    if (!$this->view->display_handler->displays_exposed() || (!$block && $this->view->display_handler->get_option('exposed_block'))) {
      unset($form_state['rerender']);
    }

    if (!empty($this->ajax)) {
      $form_state['ajax'] = TRUE;
    }

    $form_state['exposed_form_plugin'] = $this;
    $form = drupal_build_form('views_exposed_form', $form_state);
    // Note: We don't render the form.
    if (!$this->view->display_handler->displays_exposed() || (!$block && $this->view->display_handler->get_option('exposed_block'))) {
      return "";
    }
    else {
      return $form;
    }
  }
}
