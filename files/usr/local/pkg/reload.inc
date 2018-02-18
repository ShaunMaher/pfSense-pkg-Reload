<?php
/*
 * reload.inc
 *
 * MIT License
 *
 *  Copyright (c) 2018 Shaun Maher
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

function reload_install_command() {
  /* Create a cron task that runs every minute to check to see is a reload
     should be triggered */
 	$crontask = "/usr/bin/nice -n20 /usr/local/bin/php /usr/local/pkg/reload.inc do_reload";

  //install_cron_job($command, $active = false, $minute = "0", $hour = "*", $monthday = "*", $month = "*", $weekday = "*", $who = "root", $write_config = true)
 	install_cron_job("${crontask}", true, "*", "*", "*", "*", "*", "root", true);
}

function reload_deinstall_command() {
  /* Remove the cron task we created during installation */
	$crontask = "/usr/bin/nice -n20 /usr/local/bin/php /usr/local/pkg/reload.inc do_reload";
	install_cron_job("${crontask}", false);
}

/*
 Generates a list of available confif file versions available in TODO
 @returns [name => value] Returns an associative array for creation of <options/> elements
*/
function reload_get_configversions() {
  global $config;

  //TODO: Use "config_backup()" from config.lib.inc instead?
  write_config("Reload: Save config to create a reload point", true, true);
  $entries = [];
  $files = [];
  $tmp["name"] = ">> " . date("r", $config["revision"]["time"]);
  $tmp["value"] = $config["revision"]["time"];
  $entries[] = $tmp;
  if ($dirhandle = opendir('/conf/backup')) {
    while (false !== ($entry = readdir($dirhandle))) {
      if ((preg_match("/^config/", $entry)) && (preg_match("/xml\$/", $entry))) {
        $files[] = $entry;
      }
    }
    closedir($handle);
  }

  sort($files);
  foreach (array_reverse($files) as $entry) {
    $entry = explode("-", $entry, 2)[1];
    $entry = explode(".", $entry, 2)[0];
    $tmp["name"] = date("r", $entry);
    $tmp["value"] = $entry;
    $entries[] = $tmp;
  }
  return $entries;
}

// If we are being executed from cron, there will be an argument set to
//  "do_reload"
foreach ($argv as $arg) {
  if ($arg == "do_reload") {
    echo "Trigger Reload?\n";
    require_once("config.inc");

    # See config_restore in config.lib.inc
  }
}

?>
