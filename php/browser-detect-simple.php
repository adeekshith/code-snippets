<?php
	$browser = $_SERVER['HTTP_USER_AGENT'];
	$chrome = '/Chrome/';
	$firefox = '/Firefox/';
	$ie = '/MSIE/';
	
	if (preg_match($chrome, $browser))
	    echo "chrome/opera";
	if (preg_match($firefox, $browser))
	    echo "firefox";
	if (preg_match($ie, $browser))
	    echo "internet_explorer";
?>