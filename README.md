INTRODUCTION
------------
FacetAPI Exposed filters is a module meant to help bridge the gap between views
exposed filters and


REQUIREMENTS
------------
This module requires facetapi to function.


INSTALLATION
------------
 * Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.


CONFIGURATION
-------------
 * Configuration is on a per view basis. To configure, change the "Exposed form style"
   under advanced to "FacetAPI Exposed Filters". In this modal, you should be able
   to see your active facet blocks to select from them as checkboxes. Select the
   ones you would like to show and then hit save.
 * If you need to do editting to the exposed form and the weights of the elements
   shown, that can be accomplished by selecting "Send the form as a render array".
   This will send the form as a render array that can be altered/preprocessed in
   a module or template.php using the proper hook_alter or template_preprocess.


MAINTAINERS
-----------
Current maintainers:
 * Tim Whitney (timodwhit) - https://www.drupal.org/user/1629156


This project has been sponsored by:
 * Miles
 Visit https://milespartnership.com
