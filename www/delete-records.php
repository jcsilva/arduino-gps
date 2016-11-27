<?php

include "config.php";

// Create connection
$conn = pg_connect("host=$server dbname=$db user=$username password=$password")  or die("Could not connect");

$stat = pg_connection_status($conn);
if (!$stat === PGSQL_CONNECTION_OK) {
    echo 'Connection status bad <br>';
    exit();
}

$last_id = $_GET['last_id'];
if($last_id != undefined){
  $sql = "DELETE FROM gpspos WHERE id <= $last_id";

  if (pg_query($conn, $sql)) {
    echo "OK";
  } else {
    echo "ERROR: " . $sql . "<br>";
  }
}else{
  echo "No records were deleted";
}

//$conn->close();

?>

