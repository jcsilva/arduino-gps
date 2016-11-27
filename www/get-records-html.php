<?php

include "config.php";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$last_id = $_GET["last_id"];

if ($last_id == "") {
    $last_id = 0;
}

$sql = "SELECT * FROM gpspos WHERE id > " . $last_id;
$result = $conn->query($sql);

echo "<table><tr><th>ID</th><th>Lat</th><th>Lon</th></tr>";
if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>" . $row["id"] . "</td><td>" . $row["lat_coord"] . "</td><td>" . $row["lon_coord"] . "</td></tr>";
    }
} else {
    //echo "<tr><td>-</td><td>-</td><td>-</td></tr>";
}
echo "</table>";
$conn->close();

?>

