@extends("template")
@section("content")
    <style type="text/css">
        .col-md-4 {
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

    <div class="row">
        @for($i = 0; $i < count($cars_on); $i++)
            <div class="col-md-4">
                <div class="panel panel-default car">
                    @if(($cars_on[$i]->count - $cars_off[$i]->count) < 20)
                        <div class="panel-heading"><img class="center" src="/assets/images/car-green.png"></div>
                    @else
                        <div class="panel-heading"><img class="center" src="/assets/images/car-red.png"></div>
                    @endif
                    <div class="panel-body">
                        <h3>Unit ID: {{ $cars_on[$i]->UnitId }}</h3>
                    </div>
                </div>
            </div>
        @endfor
    </div>

@stop
