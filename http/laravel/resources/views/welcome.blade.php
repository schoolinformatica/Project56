@extends('template')
@section('content')
    <div class="container wrap">
        <!-- Heading Row -->
        <div class="row">
            <div class="col-md-8">
                <img class="img-responsive img-rounded" src="main_pic.jpg" alt="">
            </div>
            <!-- /.col-md-8 -->
            <div class="col-md-4">
                <h1>Team Cooperatio</h1>

                <p>This team is called Cooperatio. We are working on a project called 'Project56' which means that we
                    have to
                    process data as fast as possible. This website will serve as the webervice of our application.</p>
                <a id="button1" class="btn btn-primary btn-lg" href="/about/">Read more about us</a>
            </div>
            <!-- /.col-md-4 -->
        </div>
        <!-- /.row -->

        <hr>

        <!-- Call to Action Well -->
        <div class="row">
            <div class="col-lg-12">
                <div class="well text-center">
                    "We are not a team because we work together. We are a team because we respect, trust and care for
                    each
                    other." ~ Vala Afshar
                </div>
            </div>
            <!-- /.col-lg-12 -->
        </div>
        <!-- /.row -->

        <!-- Content Row -->
        <div class="row">
            <div class="col-md-4">
                <h2>Upload data</h2>

                <p>Uploading your data files in order to be processed to certain reports you prefer to have. You can
                    download
                    these reports in the download page of this site. This is one of our services we offer to you. It is
                    mandatory to log in to make use of this service.</p>
                <a class="btn btn-default" href="/uploadPage/">More Info</a>
            </div>
            <!-- /.col-md-4 -->
            <div class="col-md-4">
                <h2>Download data</h2>

                <p>You can download data, or better said, reports as one of our services. These reports are created on
                    your
                    demand when you upload your datafiles to our servers. For downloading this data it's required to
                    have an
                    account and you have to log in.</p>
                <a class="btn btn-default" href="/download/">More Info</a>
            </div>
            <!-- /.col-md-4 -->
            <div class="col-md-4">
                <h2>Log in</h2>

                <p>Log in or create an account to get access to our services. As a member you get access to upload data
                    and
                    download created reports. These reports are based on the data which is uploaded in you uploaded
                    files.</p>
                <a class="btn btn-default" href="/auth/login/">More Info</a>
            </div>
            <!-- /.col-md-4 -->
        </div>
        <!-- /.row -->
    </div>

@stop



