<?php

include "config.php";

// Create connection
$conn = pg_connect("host=$server dbname=$db user=$username password=$password")  or die("Could not connect");

$stat = pg_connection_status($conn);
if (!$stat === PGSQL_CONNECTION_OK) {
    echo 'Connection status bad <br>';
    exit();
}

$sql = "INSERT INTO gpspos (lat_coord, lon_coord) VALUES ('" . $_GET["lat"] . "', '" . $_GET["lon"] . "')";

if (pg_query($conn, $sql)) {
    echo "OK";
} else {
    echo "ERROR: " . $sql . "<br>";
}

//$conn->close();

?>

