<?php

include "config.php";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("ERROR: Connection failed: " . $conn->connect_error);
} 

$sql = "INSERT INTO gpspos (lat_coord, lon_coord) VALUES ('" . $_GET["lat"] . "', '" . $_GET["lon"] . "')";

if ($conn->query($sql) === TRUE) {
    echo "OK";
} else {
    echo "ERROR: " . $sql . "<br>" . $conn->error;
}

$conn->close();

?>

