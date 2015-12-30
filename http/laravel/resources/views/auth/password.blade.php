<!DOCTYPE html>
<html>
    <head>
        <title>Upload</title>

        <link href="https://fonts.googleapis.com/css?family=Lato:100" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

        <style type="text/css">

            .row {
                margin-bottom:50px;
                padding:20px;
                background-color:#eeeeee;
            }
            .content {
                margin:auto;
                padding-top:20px;
                float:initial;
                max-width:800px;
                height:100%;
            }
            .container {
                width:100%;
                margin-top:60px;
            }

            .btn-file {
              position: relative;
              overflow: hidden;
            }
            .btn-file input[type=file] {
              position: absolute;
              top: 0;
              right: 0;
              min-width: 100%;
              min-height: 100%;
              font-size: 100px;
              text-align: right;
              filter: alpha(opacity=0);
              opacity: 0;
              background: red;
              cursor: inherit;
              display: block;
            }
            input[readonly] {
              background-color: white !important;
              cursor: text !important;
            }


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
                    <li><a href="/about/">About Us</a></li>
                    <li><a  style="color:white" href="/uploadPage/">Upload files</a></li>
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


        <div class="container-fluid">
        	<div class="row">
        		<div class="col-md-8 col-md-offset-2">
        			<div class="panel panel-default">
        				<div class="panel-heading">Reset Password</div>
        				<div class="panel-body">
        					@if (session('status'))
        						<div class="alert alert-success">
        							{{ session('status') }}
        						</div>
        					@endif

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

        					<form class="form-horizontal" role="form" method="POST" action="{{ url('/password/email') }}">
        						<input type="hidden" name="_token" value="{{ csrf_token() }}">

        						<div class="form-group">
        							<label class="col-md-4 control-label">E-Mail Address</label>
        							<div class="col-md-6">
        								<input type="email" class="form-control" name="email" value="{{ old('email') }}">
        							</div>
        						</div>

        						<div class="form-group">
        							<div class="col-md-6 col-md-offset-4">
        								<button type="submit" class="btn btn-primary">
        									Send Password Reset Link
        								</button>
        							</div>
        						</div>
        					</form>
        				</div>
        			</div>
        		</div>
        	</div>
        </div>

        <!-- Footer -->
        <footer>
            <div class="row" id="footer" style="background-color:white; margin-bottom:0px;">
                <div class="col-lg-120">
                    <p>Copyright &copy;: Cooperatio 2015</p>
                </div>
            </div>
        </footer>


    </body>
</html>