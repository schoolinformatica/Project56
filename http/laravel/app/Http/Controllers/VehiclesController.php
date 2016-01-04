<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

use App\Http\Requests;
use App\Http\Controllers\Controller;
use App\Events;
use DB;

class VehiclesController extends Controller
{
    public function vehicles()
    {
        $cars_on = Events::select(["UnitId", DB::raw('count("Value")')])
            ->where("Port", 'Ignition')
            ->where("Value", 1)
            ->groupBy("UnitId")
            ->get();

        $cars_off = Events::select(["UnitId", DB::raw('count("Value")')])
            ->where("Port", 'Ignition')
            ->where("Value", 0)
            ->groupBy("UnitId")
            ->get();


        return view('pages.vehicles')->with('cars_on', $cars_on)->with('cars_off', $cars_off);
    }

}
