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


        foreach ($cars_on as $car_on) {
            foreach ($cars_off as $car_off) {
                if($car_on->UnitId == $car_off->UnitId) {
                    $car_on->count_two = $car_off->count;
                    continue;
                }
            }
        }

        return view('pages.vehicles')->with('cars', $cars_on);
    }

}
