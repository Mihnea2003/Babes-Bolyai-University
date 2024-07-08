<?php
$dbServerName = "localhost";
$dbUsername = "root";
$dbPassword = "Mihnea2003";
$dbName = "Web_lab7";
$connection = mysqli_connect($dbServerName, $dbUsername, $dbPassword, $dbName);
// Check connection
if (!$connection) {
    die("Connection failed: " . mysqli_connect_error());
} else {
    echo "Connected successfully";
}


