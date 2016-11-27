<?php

include "config.php";

// Create connection
$conn = pg_connect("host=$server dbname=$db user=$username password=$password")  or die("Could not connect");

$stat = pg_connection_status($conn);
if (! $stat === PGSQL_CONNECTION_OK) {
    echo 'Connection status bad <br>';
    exit();
}


$last_id = $_GET["last_id"];

if ($last_id == "") {
    $last_id = 0;
}

$sql = "SELECT * FROM gpspos WHERE id > " . $last_id;
$result = pg_query($conn, $sql);

echo "<table><tr><th>ID</th><th>Lat</th><th>Lon</th></tr>";
if (pg_num_rows($result) > 0) {
    // output data of each row
    while($row = pg_fetch_assoc($result)) {
        echo "<tr><td>" . $row["id"] . "</td><td>" . $row["lat_coord"] . "</td><td>" . $row["lon_coord"] . "</td></tr>";
    }
} else {
    //echo "<tr><td>-</td><td>-</td><td>-</td></tr>";
}
echo "</table>";
//$conn->close();

?>

