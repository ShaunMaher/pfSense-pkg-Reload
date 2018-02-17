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
 	$crontask = "/usr/bin/nice -n20 " . SYSLOGNG_BASEDIR . "sbin/logrotate /usr/local/etc/logrotate.conf";
 	install_cron_job("${crontask}", true, "0");
}

function reload_deinstall_command() {
  /* Remove the cron task we created during installation */
	$crontask = "/usr/bin/nice -n20 " . SYSLOGNG_BASEDIR . "sbin/logrotate /usr/local/etc/logrotate.conf";
	install_cron_job("${crontask}", false);
}

/*
 Generates a list of available confif file versions available in TODO
 @returns [name => value] Returns an associative array for creation of <options/> elements
*/

function reload_get_configversions() {
  $entries = [];
  if ($dirhandle = opendir('/conf/backup')) {
    while (false !== ($entry = readdir($dirhandle))) {
      $tmp["name"] = $entry;
      $tmp["value"] = $entry;
      $entries[] = $tmp;
    }

    closedir($handle);
  }

	#$tmp["name"] = "{$gateway['name']} (Monitor: {$gateway['monitor']})";
	#$tmp["value"] = $gateway['name'];
	#$gws[] = $tmp;
	return $entries;
}

?>
