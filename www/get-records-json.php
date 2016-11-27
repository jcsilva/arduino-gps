<?php

include "config.php";

header("Content-type:application/json");

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

$num_rows = $result->num_rows;

$json_result = array();
$json_records = array();

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
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
$conn->close();

?>

