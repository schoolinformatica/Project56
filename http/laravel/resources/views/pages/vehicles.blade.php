@extends("template")
@section("title")
    vehicles
@stop
@section("content")
    <div class="container wrap full-width margin-top">


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
            var cars = <?php echo json_encode($cars); ?>;

            function set_modal(id) {
                document.getElementById("unit-id").innerText = cars[id].UnitId;
                document.getElementById("speed").innerText = "Average speed: " + cars[id].averageSpeed + " km/h";
                document.getElementById("total-starts").innerText = "Total starts: " + cars[id].count;
                document.getElementById("failed-starts").innerText = "Total failed starts: " + cars[id].failedStarts;
                if (cars[id].failedStarts < 20) {
                    document.getElementById("image").src = "/assets/images/car-green.png";
                    document.getElementById("alert").innerHTML = "";
                }
                else {
                    document.getElementById("image").src = "/assets/images/car-red.png";
                    var alert = document.createElement("div");
                    alert.className = "alert alert-danger";
                    alert.innerHTML = "<strong>Engine failure!</strong> Engine ignition not working properly."
                    document.getElementById("alert").appendChild(alert);
                }


            }
        </script>

        <div class="container margin-top">
            <div class="row box">
                @for($i = 0; $i < count($cars); $i++)
                    <div class="col-md-4 col-marg-bottom">
                        <div id="{{ $i }}" class="panel panel-default car" onclick="set_modal(this.id)"
                             data-toggle="modal"
                             data-target="#myModal">
                            @if($cars[$i]['failedStarts'] < 20)
                                <div class="panel-heading"><img class="center" src="/assets/images/car-green.png"></div>
                            @else
                                <div class="panel-heading"><img class="center" src="/assets/images/car-red.png"></div>
                            @endif
                            <div class="panel-body">
                                <h3>Unit ID: {{ $cars[$i]['UnitId'] }}</h3>
                            </div>
                        </div>
                    </div>
                @endfor
            </div>
        </div>

        <!-- Modal -->
        <div id="myModal" class="modal fade" role="dialog">
            <div class="modal-dialog">

                <!-- Modal content-->
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal">&times;</button>
                        <h4 id="unit-id" class="modal-title"></h4>
                    </div>
                    <div class="modal-body">
                        <div class="row">
                            <div class="col-md-4">
                                <img id="image" style="max-width: 50%; max-height: 50%;"
                                     src="/assets/images/car-green.png">
                            </div>
                            <div class="col-md-8">
                                <p id="speed"></p>

                                <p id="total-starts"></p>

                                <p id="failed-starts"></p>
                            </div>
                        </div>
                        <div id="alert">
                        </div>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                    </div>
                </div>

            </div>
        </div>
    </div>
@stop
