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
use Mail;

class MailController extends Controller {


    public function email()
    {
        return view('email.datareport');
    }


    /**
     * Send an e-mail with data report
     * to user.
     *
     * @return Response
     */
    public function sendEmail()
    {
        $file = 'http://145.24.222.240/downloads/'.Input::get('file');

        Mail::send('email.datareport', ['file' => $file], function ($message) {
            $message->from('us@example.com', 'Cooperatio - Citygis Data Reporters');
            $message->subject("Uw rapport staat klaar");
            $message->to(Input::get('email'));
        });

        return "done";
    }

}
