<?php
/**
 * @file
 * File for views code.
 */

/**
 * Implementation of hook_views_plugins().
 */
function facetapi_exposed_filters_views_plugins() {
  return array(
    'exposed_form' => array(
      'facetapi_exposed_filters' => array(
        'title' => t('FacetAPI Exposed Filters'),
        'handler' => 'facetapi_exposed_filters_plugin_exposed_form',
        'uses options' => TRUE,
        'help topic' => 'exposed-form-basic',
      ),
    ),
  );
}
