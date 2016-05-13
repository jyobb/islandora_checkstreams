<?php

/**
 * @file
 * Drush hooks.
 */

/**
 * Implements hook_drush_command().
 */
function islandora_checkstreams_drush_command() {
  $items = array();



  $items['islandora_checkstreams'] = array(
    'aliases' => array('icd'),
    'description' => 'Check datastream exists for all object in a collection.',
    'drupal dependencies' => array('islandora_checkstreams'),
    'examples' => array(
     'drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_checkstreams --parentpid="apid:111" --datastream="MODS" --outfile="outfilename.txt"',
    ),
    'options' => array(
      'parentpid' => array(
        'description' => 'collections object pid',
        'required' => TRUE,
      ),
      'datastream' => array(
        'description' => 'Target datastream to look for',
        'required' => TRUE,
      ),
      'outfile' => array(
        'description' => 'File name to save output',
        'required' => TRUE,
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

return $items;

}


/**
 * Implements drush_COMMAND_validate() for islandora_checkstreams
 */
function drush_islandora_checkstreams_validate() {
  
  //Test file exists
  /*
  $base = drupal_get_path('module', 'islandora_checkstreams');
  $filepath = drush_get_option('outfile');
  if (!file_exists($base . '/data/' .$filepath)) {
    drush_set_error('FILE EXISTS');
  }

  //Add test for datastreams

*/
}



function drush_islandora_checkstreams(){

  $parentPID = drush_get_option('parentpid');
  $dataStream = drush_get_option('datastream');
  $outFilename = drush_get_option('outfile');

  $base = drupal_get_path('module', 'islandora_checkstreams');

  $filepath = DRUPAL_ROOT . '/' . $base . '/data/' . $outFilename;
  //drush_set_error('Error with type match');

module_load_include('inc', 'islandora_checkstreams', 'includes/analyzer');

islandora_get_missing_datastreams($parentPID, $dataStream, $filepath );



}