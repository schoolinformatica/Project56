<?php

namespace App\Http\Controllers;

use App\Http\Requests;
use App\Http\Controllers\Controller;
use Illuminate\Http\Request;
use App\User;
use Input;
use Validator;
use Session;
use Redirect;
use Auth;

class DownloadController extends Controller {

    //Returns the uploadpage
    public function download()
    {
        return view('pages.download');
    }

    public function generate_report(Request $request) {

        $csv = $request->table;
        $email = $request->email;
	    $startDate = $request->dateStart;
	    $endDate = $request->dateEnd;

        //Then we try to call our c++ .out file with the get vars as parameters.
        try {
            //We assign main.out's output to the variable $out.
            exec("./main.out $csv $email $startDate $endDate", $out);
            //we display the content of $out in the browser
        }
            //catch the exceptions if there are some..
        catch(Exception $tx) {
            $exceptio =  'Exception: ' .$tx->getMessage()."\n";
        }

        return Redirect::back()->with('message', 'succes');
    }

}
