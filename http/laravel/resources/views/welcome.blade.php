@extends('template')
@section('content')
    <style>
        /* Makes images fully responsive */

        .carousel-inner img {
            width: 100%;
        }

        .glyphicon {
            text-align: center;
            font-size: 132px;
        }

    </style>


    <div id="myCarousel" class="carousel slide" data-ride="carousel">
        <!-- Indicators -->
        <ol class="carousel-indicators">
            <li data-target="#myCarousel" data-slide-to="0" class="active"></li>
            <li data-target="#myCarousel" data-slide-to="1"></li>
            <li data-target="#myCarousel" data-slide-to="2"></li>
            <li data-target="#myCarousel" data-slide-to="3"></li>
        </ol>

        <!-- Wrapper for slides -->
        <div class="carousel-inner" role="listbox">
            <div class="item active">
                <img src="assets/images/banner-1.png" alt="">
            </div>

            <div class="item">
                <img src="assets/images/banner-2.png" alt="">
            </div>

        </div>

        <!-- Left and right controls -->
        <a class="left carousel-control" href="#myCarousel" role="button" data-slide="prev">

            <span class="sr-only">Previous</span>
        </a>
        <a class="right carousel-control" href="#myCarousel" role="button" data-slide="next">

            <span class="sr-only">Next</span>
        </a>
    </div>

    <div class="jumbotron box">
        <div class="container">
        <h1>~ Vala Afshar</h1>
        <p>"We are not a team because we work together. We are a team because we respect, trust and care for each other." </p>
            </div>
    </div>

    <div class="container wrap">

        <div class="container margin-top">


            <!-- Heading Row -->
            <div class="row box">

                <div class="col-md-4">
                    <span class="glyphicon glyphicon-user"></span>
                    <h2>Log in</h2>

                    <p>Log in or create an account to get access to our services. As a member you get access to upload
                        data
                        and
                        download created reports. These reports are based on the data which is uploaded in you uploaded
                        files.</p>
                    <a class="btn btn-default" href="/auth/login/">More Info</a>
                </div>
                <!-- /.col-md-4 -->

                <div class="col-md-4">
                    <span class="glyphicon glyphicon-upload"></span>
                    <h2>Upload data</h2>

                    <p>Uploading your data files in order to be processed to certain reports you prefer to have. You can
                        download
                        these reports in the download page of this site. This is one of our services we offer to you. It
                        is
                        mandatory to log in to make use of this service.</p>
                    <a class="btn btn-default" href="/uploadPage/">More Info</a>
                </div>
                <!-- /.col-md-4 -->
                <div class="col-md-4">
                    <span class="glyphicon glyphicon-download"></span>
                    <h2>Download data</h2>

                    <p>You can download data, or better said, reports as one of our services. These reports are created
                        on
                        your
                        demand when you upload your datafiles to our servers. For downloading this data it's required to
                        have an
                        account and you have to log in.</p>
                    <a class="btn btn-default" href="/download/">More Info</a>
                </div>
                <!-- /.col-md-4 -->
            </div>
            <!-- /.row -->
        </div>
    </div>

@stop



