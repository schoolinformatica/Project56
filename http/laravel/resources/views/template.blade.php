<!DOCTYPE html>
<html>
<head>
    <title>@yield('title')</title>

    <link href="https://fonts.googleapis.com/css?family=Lato:100" rel="stylesheet" type="text/css">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

    <style type="text/css">

        .height-200 {
            height: 200px;
        }

        .box {
            -webkit-box-shadow: 0px 0px 32px 4px rgba(0, 0, 0, 0.75);
            -moz-box-shadow: 0px 0px 32px 4px rgba(0, 0, 0, 0.75);
            box-shadow: 0px 0px 32px 4px rgba(0, 0, 0, 0.75);
            padding: 30px;
        }

        .full-width {
            width: 100%;
        }

        /* Wrapper for page content to push down footer */
        .wrap {

            min-height: 100% !important;
            height: auto !important;

        }

        html {
            height: 100%;
        }

        body {
            padding-top: 0px; /* Required padding for .navbar-fixed-top. Change if height of navigation changes. */
            height: 100%;
            background-color: #E9E9E9;
        }

        .btn-primary {
            background-color: #3299BB !important;
        }

        .container {
            margin-top:60px;
        }

        .row {
            background-color: white;
        }


        .row div {
            margin:auto;
            //padding-top:20px;
            //float:initial;
            max-width:800px;
            height:100%;;
        }


        .navbar-custom {
            border-radius:0px;
            background-color: #3299BB !important;
            color: white;
            padding-right: 10px;

            -webkit-box-shadow: 0px 0px 32px 4px rgba(0, 0, 0, 0.75);
            -moz-box-shadow: 0px 0px 32px 4px rgba(0, 0, 0, 0.75);
            box-shadow: 0px 0px 32px 4px rgba(0, 0, 0, 0.75);
        }

        .navbar-custom .navbar-nav > li > a {
            color:#fff;
        }

        .navbar-custom li:hover > a {
            color: #424242 !important;
        }

        .navbar-custom .navbar-nav > .active > a, .navbar-nav > .active > a:hover, .navbar-nav > .active > a:focus {
            color: #424242 !important;
            background-color:transparent;
        }

        .navbar-custom label {
            color: #302d33;
        }


        .footer {
            height: 60px;
            background-color: #BCBCBC;
        }

        @media(min-width:768px) {
            body {
                padding-top: 0px; /* Required padding for .navbar-fixed-top. Change if height of navigation changes. */
            }

        }
    </style>
</head>
<body>

<nav role="navigation" class="navbar navbar-custom navbar-fixed-top">
    <!--toggle is grouped for better mobile display -->
    <div class="navbar-header">
        <button type="button" data-target="#navbarCollapse" data-toggle="collapse" class="navbar-toggle">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
        </button>
    </div>

    <!-- Collection of nav links, forms, and other content for toggling -->
    <div id="navbarCollapse" class="collapse navbar-collapse">
        <ul class="nav navbar-nav">
            <li><a href="/">Home</a></li>
            <li><a  style="color:white" href="/about/">About Us</a></li>
            <li><a href="/uploadPage/">Upload files</a></li>
            <li><a href="/download/">Download files</a></li>
            <li><a href="/vehicles/">Vehicles</a></li>
        </ul>

        <ul class="nav navbar-nav navbar-right">
            @if(Auth::check())
                <li class="dropdown">
                    <a class="dropdown-toggle" data-toggle="dropdown" href="#">Welcome,  {{ Auth::user()->name }}
                        <span class="caret"></span></a>
                    <ul class="dropdown-menu">
                        <li><a href="/auth/logout/">Logout</a></li>
                        <li><a href="/myfiles/">My reports</a></li>
                    </ul>
                </li>
            @else
                <li class="dropdown">
                    <a class="dropdown-toggle" href="#" data-toggle="dropdown">Sign In <strong class="caret"></strong></a>
                    <div class="dropdown-menu" style="padding: 15px; padding-bottom: 0px; margin-top: 10px;">
                                @if (count($errors) > 0)
                                    <div class="alert alert-danger">
                                        <strong>Whoops!</strong> There were some problems with your input.<br><br>
                                        <ul>
                                            @foreach ($errors->all() as $error)
                                                <li>{{ $error }}</li>
                                            @endforeach
                                        </ul>
                                    </div>
                                @endif

                                <form class="form-horizontal" role="form" method="POST" action="/auth/login">
                                    <input type="hidden" name="_token" value="{{ csrf_token() }}">

                                    <div class="form-group">
                                        <label class="col-md-4 control-label">E-Mail Address</label>

                                        <div class="col-md-6">
                                            <input type="email" class="form-control" name="email" value="{{ old('email') }}">
                                        </div>
                                    </div>

                                    <div class="form-group">
                                        <label class="col-md-4 control-label">Password</label>

                                        <div class="col-md-6">
                                            <input type="password" class="form-control" name="password">
                                        </div>
                                    </div>

                                    <div class="form-group">
                                        <div class="col-md-6 col-md-offset-4">
                                            <div class="checkbox">
                                                <label>
                                                    <input type="checkbox" name="remember"> Remember Me
                                                </label>
                                            </div>
                                        </div>
                                    </div>

                                    <div class="form-group">
                                        <div class="col-md-6 col-md-offset-4">
                                            <button type="submit" class="btn btn-primary">Login</button>


                                        </div>
                                    </div>
                                </form>
                                    <a class="btn btn-link" href="{{ url('/auth/register') }}">Don`t have an account yet?
                                        Register here!</a>

                </li>

            @endif
        </ul>
    </div>

</nav>



    @yield('content')



<!-- Footer -->
<footer class="footer">
    <div class="container">
        <br>
        <p align="center" class="text-muted">Copyright &copy;: Cooperatio 2015</p>
    </div>
</footer>


</body>
</html>