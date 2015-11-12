<?php
$dir = $_POST["dir"];

require 'PHPMailerAutoload.php';

$mail = new PHPMailer;

$msg = "Uw rapport kunt u hier {$dir} downloaden!";

$mail->isSMTP();                                      // Set mailer to use SMTP
$mail->Host = 'smtp1.example.com;smtp2.example.com';  // Specify main and backup SMTP servers
$mail->SMTPAuth = true;                               // Enable SMTP authentication
$mail->Username = 'user@example.com';                 // SMTP username
$mail->Password = 'secret';                           // SMTP password
$mail->SMTPSecure = 'tls';                            // Enable TLS encryption
$mail->Port = 587;                                    // TCP port to connect to

$mail->setFrom('0890289@hr.nl', 'Cooperatio Mailer');
//TODO: Dit aanpassen naar een variabel emailadres
$mail->addAddress('0890289@hr.nl', 'Joe User');     // Add a recipient

$mail->isHTML(true);                                  // Set email format to HTML

$mail->Subject = 'Uw PDF-rapportage';
$mail->Body    = $msg;

if(!$mail->send()) {
    echo 'Message could not be sent.';
    echo 'Mailer Error: ' . $mail->ErrorInfo;
} else {
    echo 'Message has been sent';
}

?>
