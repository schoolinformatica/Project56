<?php

//Turn on more detailed errors
error_reporting(E_ALL);

//We check wether the GET var email was set, then we check wether it is not empty.
//The same applies to the GET var csv.
if(isset($_GET['email'])){
	if($_GET['email'] <> "") {
		if (isset($_GET['table'])){
			//We 'unpack' the GET vars our caller send us
			$email = $_GET['email'];
			$csv = $_GET['table'];

			//Then we try to call our c++ .out file with the get vars as parameters.
			try {
                                //We assign main.out's output to the variable $out.
				exec("./main.out $csv $email", $out);
				//we display the content of $out in the browser
				foreach($out as $line){
					echo $line . "\n" ;
				}
				redirect_now("/download?succes=1");
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


/**
 * Redirect the user no matter what. No need to use a return
 * statement. Also avoids the trap put in place by the Blade Compiler.
 *
 * @param string $url
 * @param int $code http code for the redirect (should be 302 or 301)
 */
function redirect_now($url, $code = 302)
{
	try {
		\App::abort($code, '', ['Location' => $url]);
	} catch (\Exception $exception) {
		// the blade compiler catches exceptions and rethrows them
		// as ErrorExceptions :(
		//
		// also the __toString() magic method cannot throw exceptions
		// in that case also we need to manually call the exception
		// handler
		$previousErrorHandler = set_exception_handler(function () {
		});
		restore_error_handler();
		call_user_func($previousErrorHandler, $exception);
		die;
	}
}