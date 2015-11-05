<?php

namespace App\Http\Controllers;

use App\Http\Requests;
use App\Http\Controllers\Controller;
use Illuminate\Http\Request;
use Input;
use Validator;

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
}