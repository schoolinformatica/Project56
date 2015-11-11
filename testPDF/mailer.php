<?php
$dir = $_POST["dir"];

$msg = "Uw rapport kunt u hier {$dir} downloaden!";

echo "test";

mail("0890289@hr.nl", "Uw rapport-download", $msg);




?>
