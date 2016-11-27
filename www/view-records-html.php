<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Consulta de Registros</title>
<script src="jquery-3.1.1.min.js"></script>
<script>
var lastId = "<?php echo $_GET['last_id']; ?>";
$( document ).ready(function() {
    
    function loadData() {
        $("#records").load("get-records-html.php?last_id=" + lastId, function(responseTxt, statusTxt, xhr) {
            if(statusTxt == "success")
                //alert("External content loaded successfully!");
            if(statusTxt == "error")
                alert("Error: " + xhr.status + ": " + xhr.statusText);
        });
    }
    
    var intervalId = setInterval(loadData, 1000);

    $("#start").click(function() {
        clearInterval(intervalId);        
        intervalId = setInterval(loadData, 1000);
        $("#status").text("Running");
    });

    $("#stop").click(function() {
        clearInterval(intervalId);
        $("#status").text("Stopped");
    });
 
});
</script>
<style>
table {
    border-collapse: collapse;
    width: 90%;
}

th, td {
    text-align: left;
    padding: 8px;
    width: 30%;
}

tr:nth-child(even){background-color: #f2f2f2}

th {
    background-color: #4CAF50;
    color: white;
}

</style>
</head>
<body>
<h1>Consulta de Registros</h1>
<div>
<button id="start">Start</button>
<button id="stop">Stop</button>
<span id="status">Running</span>
</div>
<p/>
<div id="records"></div>
</body>
</html>

