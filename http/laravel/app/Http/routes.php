<?php

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the controller to call when that URI is requested.
|
*/

Route::get('/', function () {
    return view('welcome');
});
<<<<<<< HEAD
Route::get('login', function() {
    return view('login');
});
=======

Route::get('about','PagesController@about');
>>>>>>> 713ce7e3ef751f3e4336fb4377350b8adff9f3eb
