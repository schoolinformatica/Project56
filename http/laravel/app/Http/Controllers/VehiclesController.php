<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

use App\Http\Requests;
use App\Http\Controllers\Controller;
use App\Events;
use App\Positions;
use DB;

class VehiclesController extends Controller
{
    public function vehicles()
    {
        $cars_on = Events::select(["UnitId", DB::raw('count("Value")')])
            ->where("Port", 'Ignition')
            ->where("Value", 1)
            ->groupBy("UnitId")
            ->get()
            ->toArray();


        $cars_off = Events::select(["UnitId", DB::raw('count("Value")')])
            ->where("Port", 'Ignition')
            ->where("Value", 0)
            ->groupBy("UnitId")
            ->get()
            ->toArray();


        $cars_speed = Positions::select(["UnitId", DB::raw('count("Speed") as total'), DB::raw('sum("Speed") as sum')])
            ->groupBy("UnitId")
            ->get()
            ->toArray();

        for ($i = 0; $i < count($cars_on); $i++) {
            $cars_on[$i]['averageSpeed'] = "Not available";
            $cars_on[$i]['count_two'] = 0;

            foreach ($cars_off as $car_off) {
                if ($cars_on[$i]['UnitId'] == $car_off['UnitId']) {
                    $cars_on[$i]['count_two'] = $car_off['count'];
                    break;
                }
            }
        }

        for ($i = 0; $i < count($cars_speed); $i++) {
            $cars_speed[$i]['averageSpeed'] = floor($cars_speed[$i]['sum'] / $cars_speed[$i]['total']);
            $cars_speed[$i]['count_two'] = 0;
            $cars_speed[$i]['count'] = 0;
        }


        foreach ($cars_speed as $car_speed) {
            $add_new = true;
            for ($i = 0; $i < count($cars_on); $i++) {
                if ($cars_on[$i]['UnitId'] == $car_speed['UnitId']) {
                    $cars_on[$i]['averageSpeed'] = $car_speed['averageSpeed'];
                    $add_new = false;
                    break;
                }
            }

            if ($add_new) {
                array_push($cars_on, $car_speed);
            }
        }

        for ($i = 0; $i < count($cars_on); $i++) {
            $cars_on[$i]['failedStarts'] = $cars_on[$i]['count']-$cars_on[$i]['count_two'];
        }


        return view('pages.vehicles')->with('cars', $cars_on);
    }

    function rd2wgs($x, $y)
    {
        // Calculate WGS84 coördinates
        $dX = ($x - 155000) * pow(10, -5);
        $dY = ($y - 463000) * pow(10, -5);

        $SomN = (3235.65389 * $dY) + (-32.58297 * pow($dX, 2))
            + (-0.2475 * pow($dY, 2)) + (-0.84978 * pow($dX, 2) * $dY)
            + (-0.0655 * pow($dY, 3)) + (-0.01709 * pow($dX, 2) * pow($dY, 2))
            + (-0.00738 * $dX) + (0.0053 * pow($dX, 4)) + (-0.00039 * pow($dX, 2) * pow($dY, 3))
            + (0.00033 * pow($dX, 4) * $dY) + (-0.00012 * $dX * $dY);

        $SomE = (5260.52916 * $dX) + (105.94684 * $dX * $dY) + (2.45656 * $dX * pow($dY, 2))
            + (-0.81885 * pow($dX, 3)) + (0.05594 * $dX * pow($dY, 3))
            + (-0.05607 * pow($dX, 3) * $dY) + (0.01199 * $dY)
            + (-0.00256 * pow($dX, 3) * pow($dY, 2)) + (0.00128 * $dX * pow($dY, 4))
            + (0.00022 * pow($dY, 2)) + (-0.00022 * pow($dX, 2)) + (0.00026 * pow($dX, 5));

        $Latitude = 52.15517 + ($SomN / 3600);
        $Longitude = 5.387206 + ($SomE / 3600);

        return array(
            'latitude' => $Latitude,
            'longitude' => $Longitude);
    }

}
