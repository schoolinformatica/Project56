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

class AdminController extends Controller {

    //Returns the uploadpage
    public function admin()
    {
        $users = User::all();

        return view('pages.admin')->with('users', $users);
    }

    public function update(Request $request) {
        $user =  User::find($request->input('id'));

        $user->role = $request->input('role');
        $user->save();

        return Redirect::back()->with('message','User is successfully updated !');
    }

}
