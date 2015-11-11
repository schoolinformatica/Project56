<?php
$dir = $_POST["dir"];

$msg = "Uw rapport kunt u hier {$dir} downloaden!";

mail("0890289@hr.nl", "Uw rapport-download", $msg);




?>
