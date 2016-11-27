<?php

include "config.php";

header("Content-type:application/json");

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

$num_rows = pg_num_rows($result);

$json_result = array();
$json_records = array();

if ($num_rows > 0) {
    // output data of each row
    while($row = pg_fetch_assoc($result)) {
        $json_record = array();
        $json_record["id"] = $row["id"];
        $json_record["lat"] = $row["lat_coord"];
        $json_record["lon"] = $row["lon_coord"];
        $json_records[] = $json_record;
        $num_rows = $num_rows - 1;
        $last_id = $row["id"];
    }
} else {
    //echo "<tr><td>-</td><td>-</td><td>-</td></tr>";
}
$json_result["records"] = $json_records;
$json_result["last_id"] = $last_id;
echo json_encode($json_result);
//$conn->close();

?>

