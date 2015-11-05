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


            body {
                padding-top: 0px; /* Required padding for .navbar-fixed-top. Change if height of navigation changes. */
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
                    <li><a  style="color:white" href="/">Home</a></li>
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
                        <img class="img-responsive img-rounded" src="main_pic.jpg" alt="">
                    </div>
                    <!-- /.col-md-8 -->
                    <div class="col-md-4">
                        <h1>Team Cooperatio</h1>
                            <p>This team is called Cooperatio. We are working on a project called 'Project56' which means that we have to process data as fast as possible. This website will serve as the webervice of our application.</p>
                            <a class="btn btn-primary btn-lg" href="/about/">Read more about us</a>
                    </div>
                    <!-- /.col-md-4 -->
                </div>
                <!-- /.row -->

                <hr>

                <!-- Call to Action Well -->
                <div class="row">
                    <div class="col-lg-12">
                        <div class="well text-center">
                            "We are not a team because we work together. We are a team because we respect, trust and care for each other." ~ Vala Afshar
                        </div>
                    </div>
                    <!-- /.col-lg-12 -->
                </div>
                <!-- /.row -->

                <!-- Content Row -->
                <div class="row">
                    <div class="col-md-4">
                        <h2>Upload data</h2>
                        <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Saepe rem nisi accusamus error velit animi non ipsa placeat. Recusandae, suscipit, soluta quibusdam accusamus a veniam quaerat eveniet eligendi dolor consectetur.</p>
                        <a class="btn btn-default" href="/uploadPage/">More Info</a>
                    </div>
                    <!-- /.col-md-4 -->
                    <div class="col-md-4">
                        <h2>Download data</h2>
                        <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Saepe rem nisi accusamus error velit animi non ipsa placeat. Recusandae, suscipit, soluta quibusdam accusamus a veniam quaerat eveniet eligendi dolor consectetur.</p>
                        <a class="btn btn-default" href="/loadPage/">More Info</a>
                    </div>
                    <!-- /.col-md-4 -->
                    <div class="col-md-4">
                        <h2>Contact us</h2>
                        <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Saepe rem nisi accusamus error velit animi non ipsa placeat. Recusandae, suscipit, soluta quibusdam accusamus a veniam quaerat eveniet eligendi dolor consectetur.</p>
                        <a class="btn btn-default" href="/contact/">More Info</a>
                    </div>
                    <!-- /.col-md-4 -->
                </div>
                <!-- /.row -->

                <!-- Footer -->
                <footer>
                    <div class="row">
                        <div class="col-lg-12">
                            <p>Copyright &copy;: Cooperatio 2015</p>
                        </div>
                    </div>
                </footer>

            </div>
            <!-- /.container -->





    </body>
</html>