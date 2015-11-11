<?php
$dir = $_POST["dir"];

$msg = "Uw rapport kunt u hier {$dir} downloaden!";

if(sendmail())
{
	echo "mail sent!";
}
else
{
	echo "mail not sent";
}

function sendmail()
{
	mail("0890289@hr.nl", "Uw rapport-download", $msg);
	return true;
}


?>
