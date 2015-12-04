<!DOCTYPE html>
<html>
    <head>
        <title>About us</title>

        <link href="https://fonts.googleapis.com/css?family=Lato:100" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

        <style type="text/css">


            body {
                padding-top: 0px; /* Required padding for .navbar-fixed-top. Change if height of navigation changes. */
            }

            .container {
                width:100%;
                margin-top:60px;
            }

            .row {
                margin-bottom:50px;
                background-color:#eeeeee;
            }

            .row div {
                margin:auto;
                padding-top:20px;
                float:initial;
                max-width:800px;
                height:100%;;
            }

            .leadh1 {
                margin-top:0px;
            }

            .navbar-inverse {
                border-radius:0px;
            }

            .navbar-fixed-top .nav {
                padding: 15px 0;
            }

            .navbar-fixed-top .navbar-brand {
                padding: 0 15px;
            }

            footer {
                padding-top: 50px;
                margin:0px,0px,0px,10px;
            }
            #footer {
                padding-top:0px;
                margin-left:10px;
                width:100%;
            }

            @media(min-width:768px) {
                body {
                    padding-top: 0px; /* Required padding for .navbar-fixed-top. Change if height of navigation changes. */
                }

                .navbar-fixed-top .navbar-brand {
                    padding: 15px 0;
                }
            }
        </style>
    </head>
    <body>

        <nav role="navigation" class="navbar navbar-inverse">
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
                    <!--<li class="dropdown">
                        <a data-toggle="dropdown" class="dropdown-toggle" href="#">Messages <b class="caret"></b></a>
                            <ul role="menu" class="dropdown-menu">
                                <li><a href="#">Inbox</a></li>
                                <li><a href="#">Drafts</a></li>
                                <li><a href="#">Sent Items</a></li>
                                <li class="divider"></li>
                                <li><a href="#">Trash</a></li>
                            </ul>
                    </li>-->
                </ul>
                <ul class="nav navbar-nav navbar-right">
                    @if(Auth::check())
                        <li><a href="/auth/login/">Logout</a></li>
                    @else
                        <li><a href="/auth/login/">Login</a></li>
                    @endif
                </ul>
            </div>

        </nav>

        <!-- Page Content -->
            <div class="container">

                <div class="row">
                    <div class="col-lg-12 text-center">
                        <h1 class="leadh1">Cooperatio</h1>
                        <p class="lead">
                                        Cooperatio, founded in September 2015. We are a team of 5 enthusiastic and studious students.
                                        We have met each other at the Hogeschool Rotterdam (High School of Rotterdam). Cooperatio is founded for the 'Project56.'
                                        The teammembers are: "Cees-Jan Nolen, Robert Kraaijeveld, Robin Bakker, Steven Schenk
                                        en William de Visser".
                        </p>
                    </div>
                </div>
                <!-- /.row -->

                <div class="row">
                    <div class="col-lg-12 text-center">
                        <h1 class="leadh1">Project56</h1>
                        <p class="lead">
                                        Bij dit project moeten we voor CityGis een systeem maken dat csv-bestanden kan uploaden en toevoegen aan de database.
                                        Ook moeten er files 'verkocht' kunnen worden. Waarna de gebruiker de csv bestand(en) kan downloaden.
                        </p>
                    </div>
                </div>
                <!-- /.row -->

            </div>
            <!-- /.container -->

            <!-- Footer -->
            <footer>
                <div class="row" id="footer" style="background-color:white; ">
                    <div class="col-lg-120">
                        <p>Copyright &copy;: Cooperatio 2015</p>
                    </div>
                </div>
            </footer>

        </div>
        <!-- /.container -->


    </body>
</html>