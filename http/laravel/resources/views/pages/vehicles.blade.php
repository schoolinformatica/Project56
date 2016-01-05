@extends("template")
@section("content")

    <?php
    function toGps($rdx, $rdy)
    {
        $dX = ($rdx - 155000) * 10 ^ -5;
        $dY = ($rdy - 463000) * 10 ^ -5;

        $SomN = (3235.65389 * $dY) + (-32.58297 * $dX ^ 2) + (-0.2475 * $dY ^ 2) + (-0.84978 * $dX ^ 2 * $dY) + (-0.0655 * $dY ^ 3) + (-0.01709 * $dX ^ 2 * $dY ^ 2) + (-0.00738 * $dX) + (0.0053 * $dX ^ 4) + (-0.00039 * $dX ^ 2 * $dY ^ 3) + (0.00033 * $dX ^ 4 * $dY) + (-0.00012 * $dX * $dY);
        $SomE = (5260.52916 * $dX) + (105.94684 * $dX * $dY) + (2.45656 * $dX * $dY ^ 2) + (-0.81885 * $dX ^ 3) + (0.05594 * $dX * $dY ^ 3) + (-0.05607 * $dX ^ 3 * $dY) + (0.01199 * $dY) + (-0.00256 * $dX ^ 3 * $dY ^ 2) + (0.00128 * $dX * $dY ^ 4) + (0.00022 * $dY ^ 2) + (-0.00022 * $dX ^ 2) + (0.00026 * $dX ^ 5);

        $Latitude = 52.15517 + ($SomN / 3600);
        $Longitude = 5.387206 + ($SomE / 3600);

        $LatitudeGraden = floor($Latitude);
        $LongitudeGraden = floor($Longitude);

        $LatitudeMinuten = ($Latitude - $LatitudeGraden) * 60.0;
		$LongitudeMinuten = ($Longitude - $LongitudeGraden) * 60.0;

        return $LatitudeGraden . $LatitudeMinuten . $LongitudeGraden . $LongitudeMinuten;

    }

    $vector = toGps(158126.102542985, 380446.027478599);
    echo $vector;
    ?>

    <style type="text/css">
        .col-marg-bottom {
            margin-bottom: 30px !important;
        }

        img.center {
            display: block;
            margin: 0 auto;
        }

        .car:hover {
            -webkit-box-shadow: 1px 1px 21px 0px rgba(50, 50, 50, 0.75);
            -moz-box-shadow: 1px 1px 21px 0px rgba(50, 50, 50, 0.75);
            box-shadow: 1px 1px 21px 0px rgba(50, 50, 50, 0.75);

            cursor: pointer;
        }
    </style>

    <script>
        var id_clicked;
        var cars = <?php echo json_encode($cars); ?>;

        function set_id_clicked(id) {
            id_clicked = id;
        }
        function get_id_clicked() {
            return id_clicked;
        }

    </script>

    <div class="row">
        @for($i = 0; $i < count($cars); $i++)
            <div class="col-md-4 col-marg-bottom">
                <div id="{{ $i }}" class="panel panel-default car" onclick="set_id_clicked(this.id)" data-toggle="modal"
                     data-target="#myModal">
                    @if(($cars[$i]->count - $cars[$i]->count_two) < 20)
                        <div class="panel-heading"><img class="center" src="/assets/images/car-green.png"></div>
                    @else
                        <div class="panel-heading"><img class="center" src="/assets/images/car-red.png"></div>
                    @endif
                    <div class="panel-body">
                        <h3>Unit ID: {{ $cars[$i]->UnitId }}</h3>
                    </div>
                </div>
            </div>
        @endfor
    </div>

    <!-- Modal -->
    <div id="myModal" class="modal fade" role="dialog">
        <div class="modal-dialog">

            <!-- Modal content-->
            <div class="modal-content">
                <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal">&times;</button>
                    <h4 class="modal-title">12003952</h4>
                </div>
                <div class="modal-body">
                    <div class="row">
                        <div class="col-md-4">
                            <img style="max-width: 50%; max-height: 50%;" src="/assets/images/car-green.png">
                        </div>
                        <div class="col-md-8">
                            Vehicle info
                        </div>
                    </div>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                </div>
            </div>

        </div>
    </div>

@stop
