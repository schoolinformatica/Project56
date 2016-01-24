<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

require '../vendor/autoload.php';
//We assign our GET-variables to php vars
if(isset($_GET['dir'])
{
  $dir = $_GET['dir'];
}

if(isset($_GET['emailadress'])
{
  $emailadress = $_GET['emailadress'];
}


//We create a new object of class PHPMailer.
//PHPMailer is the library we use for emailing.
$mail = new PHPMailer();
$mail->SMTPDebug = 1;
$mail->IsSMTP();
//We create a variable to hold our email bodymessage.
$msg = "Uw rapport kunt u hier: <a href='" . $dir . "'>" . $dir . " </a> downloaden!";

$mail->isSendmail();
//We set the properties of our email.
$mail->setFrom('0890289@hr.nl', 'Cooperatio Mailer');
//We set our recipient to the $emailadress variable.
$mail->addAddress($emailadress);     
//We allow the usage of HTML elements in our email.
$mail->isHTML(true);                                  
//We set the subject and the bodu of our email.
$mail->Subject = 'Uw PDF-rapportage staat klaar op: ' . $dir;
$mail->Body    = $msg;
echo 'mail wordt verzonden';

//We check wether the email has actually been sent and catch excceptions if it hasnt.
if(!$mail->send()) {
    echo 'Message could not be sent.';
    echo 'Mailer Error: ' . $mail->ErrorInfo;
} else {
    echo 'Message has been sent';
}

?>
