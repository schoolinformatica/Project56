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
                font-family: 'Lato';
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
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" data-target="#navbarCollapse" data-toggle="collapse" class="navbar-toggle">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a href="#" class="navbar-brand">Brand</a>
            </div>
            <!-- Collection of nav links, forms, and other content for toggling -->
            <div id="navbarCollapse" class="collapse navbar-collapse">
                <ul class="nav navbar-nav">
                    <li class="active"><a href="/">Home</a></li>
                    <li><a href="/about/">About Us</a></li>
                    <li><a href="/upload/">Upload files</a></li>
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
                        <img class="img-responsive img-rounded" src="http://placehold.it/900x350" alt="">
                    </div>
                    <!-- /.col-md-8 -->
                    <div class="col-md-4">
                        <h1>Cooperatio</h1>
                        <p>This is a template that is great for small businesses. It doesn't have too much fancy flare to it, but it makes a great use of the standard Bootstrap core components. Feel free to use this template for any project you want!</p>
                        <a class="btn btn-primary btn-lg" href="#">Call to Action!</a>
                    </div>
                    <!-- /.col-md-4 -->
                </div>
                <!-- /.row -->

                <hr>

                <!-- Call to Action Well -->
                <div class="row">
                    <div class="col-lg-12">
                        <div class="well text-center">
                            This is a well that is a great spot for a business tagline or phone number for easy access!
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