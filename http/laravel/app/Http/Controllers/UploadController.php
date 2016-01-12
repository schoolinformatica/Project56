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

    //Returns the uploadpage
     public function upload()
     {
         return view('pages.upload');
     }

    public function multiple_upload() {
        if($connected = @fsockopen("www.google.com", 80)) //If internetconnection is established (and fast)
        {
            // getting all of the post data
            $files = Input::file('images');
            // Making counting of uploaded images
            $file_count = count($files);
            if($file_count <= 10)
            {
                // start count how many uploaded
                $uploadcount = 0;
                foreach($files as $file) {
                    $rules = array('file' => 'required'); //'required|mimes:png,gif,jpeg,txt,pdf,doc'
                    $validator = Validator::make(array('file'=> $file), $rules);
                    if($validator->passes()){
                        $destinationPath = storage_path() . '/uploads';
                        $filename = $file->getClientOriginalName();
                        $upload_success = $file->move($destinationPath, $filename);
                        $uploadcount ++;
                    }
                }
                if($uploadcount == $file_count){
                    return Redirect::back()->with('submitted','true');
                }
                else //If the upload failed (partially or completely)
                {
                    //returns back to the page and shows an error message to the user
                    $message = "Somehow the upload process has been interrupted. ";
                    echo "<script type='text/javascript'>alert('$message');</script>";
                    return redirect('uploadPage');
                }
            }
            else
            {
                $message = "ERROR! Uploading more than 10 files is not allowed. Try again!";
                echo "<script type='text/javascript'>alert('$message');</script>";
                return redirect('uploadPage');
            }
        }
        else //If internetconnection is slow or not established
        {
            //Shows an warning to the user
            $message = "WARNING!our internet might be slow or not even connected. This could abort the upload process!";
            echo "<script type='text/javascript'>alert('$message');</script>";
        }
    }
}
