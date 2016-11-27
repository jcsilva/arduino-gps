<?php
// When using Heroku
//$url = parse_url(getenv("DATABASE_URL"));
//$server = $url["host"];
//$username = $url["user"];
//$password = $url["pass"];
//$db = substr($url["path"], 1);

// When using Docker
$server = 'postgres-server'; //$url["host"];
$username = 'postgres'; //'gpsuser'; //$url["user"];
$password = '1234'; //$url["pass"];
$db = 'gpstrack'; //substr($url["path"], 1);

?>
