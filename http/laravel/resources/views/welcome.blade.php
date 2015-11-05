<!DOCTYPE html>
<html>
    <head>
        <title>Home</title>

        <link href="https://fonts.googleapis.com/css?family=Lato:100" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

        <style type="text/css">

        	.navbar{
        		margin-top: 0px;
        	}

            html, body {
                height: 100%;
            }

            body {
                margin: 0;
                padding: 0;
                width: 100%;
                display: table;
                font-weight: 100;
                font-family: "Times New Roman", Georgia, Serif;;
            }

            .container {
                text-align: center;
                vertical-align: middle;
            }

            .content {
                text-align: center;
                display: inline-block;
            }

            .title {
                font-size: 96px;
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
                    <li><a href="/about/">About Us</a></li>
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
                    <li><a href="/login/">Login</a></li>
                </ul>
            </div>

        </nav>
        <!-- Page Content -->
            <div class="container">

                <!-- Heading Row -->
                <div class="row">
                    <div class="col-md-8">
                        <img class="img-responsive img-rounded" src="handshake.jpg" alt="photo from two people shaking hands">
                    </div>
                    <!-- /.col-md-8 -->
                    <div class="col-md-4">
                        <h1>Cooperatio</h1>
                        <p>Deze website is gemaakt in opdracht van CityGis. Op deze website kunt u csv bestanden uploaden.
                        En data kopen waarna u het desbetreffende csv bestand kan downloaden.</p>
                    </div>
                    <!-- /.col-md-4 -->
                </div>
                <!-- /.row -->

                <hr>

                <!-- Call to Action Well -->
                <div class="row">
                    <div class="col-lg-12">
                        <div class="well text-center">
                            THIS IS COOPERATIO!!!
                        </div>
                    </div>
                    <!-- /.col-lg-12 -->
                </div>
                <!-- /.row -->

                <!-- Content Row -->
                <div class="row">
                    <div class="col-md-4">
                        <h2>About us</h2>
                        <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Saepe rem nisi accusamus error velit animi non ipsa placeat. Recusandae, suscipit, soluta quibusdam accusamus a veniam quaerat eveniet eligendi dolor consectetur.</p>
                        <a class="btn btn-default" href="/about/">More Info</a>
                    </div>
                    <!-- /.col-md-4 -->
                    <div class="col-md-4">
                        <h2>Download files</h2>
                        <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Saepe rem nisi accusamus error velit animi non ipsa placeat. Recusandae, suscipit, soluta quibusdam accusamus a veniam quaerat eveniet eligendi dolor consectetur.</p>
                        <a class="btn btn-default" href="#">More Info</a>
                    </div>
                    <!-- /.col-md-4 -->
                    <div class="col-md-4">
                        <h2>Upload files</h2>
                        <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Saepe rem nisi accusamus error velit animi non ipsa placeat. Recusandae, suscipit, soluta quibusdam accusamus a veniam quaerat eveniet eligendi dolor consectetur.</p>
                        <a class="btn btn-default" href="/upload/">More Info</a>
                    </div>
                    <!-- /.col-md-4 -->
                </div>
                <!-- /.row -->

                <!-- Footer -->
                <footer>
                    <div class="row">
                        <div class="col-lg-12">
                            <p>Copyright &copy; Cooperatio 2015</p>
                        </div>
                    </div>
                </footer>

            </div>
            <!-- /.container -->
    </body>
</html>