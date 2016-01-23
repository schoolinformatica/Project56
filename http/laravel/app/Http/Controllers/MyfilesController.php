<?php

namespace App\Http\Controllers;

use App\Userhaspdfs;
use Illuminate\Http\Request;

use App\Http\Requests;
use App\Events;
use DB;
use Illuminate\Support\Facades\Auth;

class MyfilesController extends Controller
{

    public function myfiles()
    {
        $my_files = Userhaspdfs::all()
            ->where("email", Auth::user()->email);
        dd($my_files);


        return view('pages.myfiles')->with('my_files', $my_files);
    }

}
