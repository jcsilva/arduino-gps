<?php
// When using Heroku
if(getenv("DATABASE_URL")){
  $url = parse_url(getenv("DATABASE_URL"));
  $server = $url["host"];
  $username = $url["user"];
  $password = $url["pass"];
  $db = substr($url["path"], 1);
} else{
// When using Docker
$server = 'postgres-server';
$username = 'postgres';
$password = '1234'; 
$db = 'gpstrack'; 
}
?>
