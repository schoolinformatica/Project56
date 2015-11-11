$dir = $_POST["dir"];

$msg = "Uw rapport kunt u hier {$dir} downloaden!";

mail("0890289@hr.nl", "Uw rapport-download", $msg);
//TO do: Bijhouden wat het emailadres vd user die het report
//vroeg is
