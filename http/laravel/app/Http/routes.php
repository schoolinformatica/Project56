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


//Route::get('login', function() {
//    return view('login');
//});

Route::get('welcome', 'PagesController@home');
Route::get('about','PagesController@about');
Route::get('login', 'PagesController@login');
Route::get('createaccount', 'PagesController@createaccount');
Route::get('download', 'PagesController@download');

Route::get('uploadPage', 'UploadController@upload');
Route::post('uploadAdd', 'UploadController@multiple_upload');

// Authentication routes...
Route::get('auth/login', 'Auth\AuthController@getLogin');
Route::post('auth/login', 'Auth\AuthController@postLogin');
Route::get('auth/logout', 'Auth\AuthController@getLogout');

// Registration routes...
Route::get('auth/register', 'Auth\AuthController@getRegister');
Route::post('auth/register', 'Auth\AuthController@postRegister');


Route::controllers([
   'password' => 'Auth\PasswordController',
]);