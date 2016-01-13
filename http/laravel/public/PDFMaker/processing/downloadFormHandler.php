<?php

//Turn on more detailed errors
error_reporting(E_ALL);

//We check wether the GET var email was set, then we check wether it is not empty.
//The same applies to the GET var csv.
if(isset($_POST['email'])){
	if($_POST['email'] <> "") {
		if (isset($_POST['csv'])){
			//We 'unpack' the GET vars our caller send us
			$email = $_POST['email'];
			$csv = $_POST['csv'];

			//Then we try to call our c++ .out file with the get vars as parameters.
			try {
                                //We assign main.out's output to the variable $out.
				exec("./main.out $csv $email", $out);
				//we display the content of $out in the browser
				foreach($out as $line){
					echo $line . "\n" ;
				}
			}
			//catch the exceptions if there are some.. 
			catch(Exception $tx) {				
				print 'Exception: ' .$tx->getMessage()."\n";
			}
		}
		else {
			echo 'csv not given!';
		}
	}
	else {
		echo 'email is not given!';
	}
}
else {
	echo 'email is not given!';
}

?>
