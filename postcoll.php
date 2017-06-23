<?php
//Step1
 $dbhost = "localhost";
 $dbuser = "root";
 $dbpass = "";
 $dbb = "pandeyji";
 $db = new mysqli($dbhost, $dbuser, $dbpass,$dbb)
 or die('Error connecting to MySQL server.');
 $id=$_GET['id'];
 $sen1=$_GET['sen1'];
 $sen2=$_GET['sen2'];
$sen3=$_GET['sen3'];

?>

<html>
 <head>
 </head>
 <body>
 <h1>PHP connect to MySQL</h1>

<?php
//Step2
$sql = "INSERT INTO pressure VALUES ('$id','$sen1','$sen2','$sen3')";
	$result = mysqli_query($db,$sql);
	if (!$result) {
		die('Invalid query: ' . mysql_error());
	}
	echo "<h1>THE DATA HAS BEEN SENT!!</h1>";

//Step 3
mysqli_close($db);
?>

</body>
</html>