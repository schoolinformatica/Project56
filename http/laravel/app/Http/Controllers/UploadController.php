<?php

namespace App\Http\Controllers;

use App\Http\Requests;
use App\Http\Controllers\Controller;
use Illuminate\Http\Request;
use Input;
use Validator;
use Session;
use Redirect;

class UploadController extends Controller {
    /**
     * Store an image.
     *
     * @return simple JSON response message
     */

     public function upload()
     {
         return view('pages.upload');
     }

    public function store(Request $r)
    {
        $image = Input::file('file');

        $destinationPath = storage_path() . '/uploads';
        if(!$image->move($destinationPath, $image->getClientOriginalName())) {
            return $this->errors(['message' => 'Error saving the file.', 'code' => 400]);
        }
        //return response()->json(['success' => true], 200);
        return view('pages.upload');
    }

    public function multiple_upload()
    {
        // getting all of the post data
        $files = Input::file('images');
        foreach($files as $file) {
          // validating each file.
          $rules = array('file' => 'required'); //'required|mimes:png,gif,jpeg,txt,pdf,doc'
          $validator = Validator::make(array('file'=> $file), $rules);
          if($validator->passes()){
            // path is root/uploads
            $destinationPath = storage_path() . '/uploads';
            $filename = $file->getClientOriginalName();
            $upload_success = $file->move($destinationPath, $filename);
            // flash message to show success.
            Session::flash('success', 'Upload successfully');
            return view('pages.upload');
          }
          else {
            // redirect back with errors.
            return view('pages.upload');
          }

    }

    }
}