<?php

/**
 * @file
 * drush integration for islandora_reclinejs.
 */

/**
 * Define plugin URIs.
 */
define('RECLINE_URI', 'http://okfnlabs.org/recline/dist/recline.js');
define('RECLINE_CSV_URI', 'http://okfnlabs.org/csv.js/csv.js');
define('MUSTACHE_URI', 'https://github.com/janl/mustache.js/archive/v2.3.0.zip');
define('UNDERSCORE_URI', 'http://underscorejs.org/underscore-min.js');
define('BACKBONE_URI', 'http://backbonejs.org/backbone.js');


/**
 * Define directorys
 */
define('RECLINE_ORIGINAL_DIR', 'recline');
define('RECLINE_CSV_ORIGINAL_DIR', 'recline');
define('MUSTACHE_ORIGINAL_DIR', 'mustache.js');
define('UNDERSCORE_ORIGINAL_DIR', 'underscore');
define('BACKBONE_ORIGINAL_DIR', 'backbone');

/**
 * Define filename
 */
define('RECLINE_ORIGINAL_NAME', 'recline.js');
define('RECLINE_CSV_ORIGINAL_NAME', 'csv.js');
define('UNDERSCORE_ORIGINAL_NAME', 'underscore.js');
define('BACKBONE_ORIGINAL_NAME', 'backbone.js');

/**
 * Implements hook_drush_command().
 */
function islandora_reclinejs_drush_command() {
  $items = array();
  // The key in the $items array is the name of the command.
  $items['reclinejs-plugin'] = array(
    'callback' => 'drush_islandora_reclinejs_plugin',
    'description' => dt('Download and install the Recline.js plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Recline.js plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('reclinejsplugin'),
  );
  $items['reclinejs-csv-plugin'] = array(
    'callback' => 'drush_islandora_reclinejs_csv_plugin',
    'description' => dt('Download and install the Recline.js csv plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Recline.js csv plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('reclinejscsv-plugin','reclinejscsvplugin','reclinecsv-plugin','reclinecsvplugin'),
  );
  $items['mustachejs-plugin'] = array(
    'callback' => 'drush_islandora_reclinejs_mustache_plugin',
    'description' => dt('Download and install the Mustache.js plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Mustache.js plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('mustachejsplugin'),
  );
  $items['underscorejs-plugin'] = array(
    'callback' => 'drush_islandora_reclinejs_underscore_plugin',
    'description' => dt('Download and install the Underscore.js plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Underscore.js plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('underscorejsplugin'),
  );
  $items['backbonejs-plugin'] = array(
    'callback' => 'drush_islandora_reclinejs_backbone_plugin',
    'description' => dt('Download and install the Backbone.js plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Backbone.js plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('backbonejsplugin'),
  );
    $items['reclinejs-all-plugin'] = array(
    'callback' => 'drush_islandora_reclinejs_all_plugin',
    'description' => dt('Download and install all required plugins.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the plugins. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('reclinejsall-plugin','reclinejsallplugin'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function islandora_reclinejs_drush_help($section) {
  switch ($section) {
    case 'drush:reclinejs-plugin':
      return dt('Download and install the Recline.js plugin, default location is sites/all/libraries.');
  }
}


function drush_islandora_reclinejs_plugin() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = _drush_core_directory("@site:sites/all/libraries");
  }
  
  drush_islandora_reclinejs_install_plugin($path, RECLINE_URI, RECLINE_ORIGINAL_DIR, RECLINE_ORIGINAL_NAME);
}

function drush_islandora_reclinejs_csv_plugin() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = _drush_core_directory("@site:sites/all/libraries");
  }
  
  drush_islandora_reclinejs_install_plugin($path, RECLINE_CSV_URI, RECLINE_CSV_ORIGINAL_DIR, RECLINE_CSV_ORIGINAL_NAME);
}

function drush_islandora_reclinejs_mustache_plugin() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = _drush_core_directory("@site:sites/all/libraries");
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the zip archive.
  if ($filepath = drush_download_file(MUSTACHE_URI)) {
    $filename = basename($filepath);
    $dirname = MUSTACHE_ORIGINAL_DIR;

    // Remove any existing plugin directory.
    if (is_dir($dirname)) {
      drush_delete_dir($dirname, TRUE);
      drush_log(dt('A existing plugin was deleted from @path', array('@path' => $path)), 'notice');
    }


    $midname = $dirname . 'file';
    // Decompress the zip archive.
    drush_tarball_extract($filename, $midname);
    
    //Move up a directory
    drush_move_dir($midname . '/mustache.js-2.3.0', $dirname, FALSE);
    drush_delete_dir($midname, TRUE);
  }

  if (is_dir($dirname)) {
    drush_log(dt('Mustache.js plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the Mustache.js plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}

function drush_islandora_reclinejs_underscore_plugin() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = _drush_core_directory("@site:sites/all/libraries");
  }
  
  drush_islandora_reclinejs_install_plugin($path, UNDERSCORE_URI, UNDERSCORE_ORIGINAL_DIR, UNDERSCORE_ORIGINAL_NAME);
}

function drush_islandora_reclinejs_backbone_plugin() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = _drush_core_directory("@site:sites/all/libraries");
  }
  
  drush_islandora_reclinejs_install_plugin($path, BACKBONE_URI, BACKBONE_ORIGINAL_DIR, BACKBONE_ORIGINAL_NAME);
}

function drush_islandora_reclinejs_install_plugin($libraryPath, $source, $dirname, $filename) {  
  $path = $libraryPath . '/' . $dirname;
  
  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }
  
  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);
  
  $filepath = $path . '/' . $filename;
  
  //have to move the file to get the download to work
  if($temppath = drush_download_file($source, $path . '/foo')) {
    drush_move_dir($temppath, $filepath, true);
    chmod($filepath, 0664);
  }
  
  if (is_file($filepath)) {
    drush_log(dt('@name plugin has been installed in @path', array('@name' => $filename, '@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the @name plugin to @path', array('@name' => $filename, '@path' => $path)), 'error');
  }
}

function drush_islandora_reclinejs_all_plugin() {
  drush_islandora_reclinejs_plugin();
  drush_islandora_reclinejs_csv_plugin();
  drush_islandora_reclinejs_mustache_plugin();
  drush_islandora_reclinejs_underscore_plugin();
  drush_islandora_reclinejs_backbone_plugin();
}
