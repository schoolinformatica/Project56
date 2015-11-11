<!DOCTYPE html>
<html>
    <head>
        <title>Login</title>

<link href="https://fonts.googleapis.com/css?family=Lato:100" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

        <style type="text/css">


            body {
                padding-top: 0px; /* Required padding for .navbar-fixed-top. Change if height of navigation changes. */
            }

            nav {
                z-index:999;
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
                padding: 50px 0;
            }

            @media(min-width:768px) {
                body {
                    padding-top: 0px; /* Required padding for .navbar-fixed-top. Change if height of navigation changes. */
                }

                .navbar-fixed-top .navbar-brand {
                    padding: 15px 0;
                }
            }
            /*Css for navbar ends here and the css for the login screen starts here*/
            .form-signin {
                /*This make the login screen go to the middle of the container div*/
                top:30%;
                left:45%;
                margin-top:-50px; /* this is half the height of your div*/
                margin-left:-100px;
                max-width: 400px;
                display:block;
                background-color: #f7f7f7;
                -moz-box-shadow: 0 0 3px 3px #888;
                -webkit-box-shadow: 0 0 3px 3px #888;
                box-shadow: 0 0 3px 3px #888;
                border-radius:2px;
            }
            .main{
                padding: 38px;
            }
            .social-box{
                margin: 0 auto;
                padding: 38px;
                border-bottom:1px #ccc solid;
            }
            .social-box a{
                font-weight:bold;
                font-size:18px;
                padding:8px;
            }
            .social-box a i{
                font-weight:bold;
                font-size:20px;
            }
            .heading-desc{
                font-size:20px;
                font-weight:bold;
                padding:38px 38px 0px 38px;

            }
            .form-signin .form-signin-heading,
            .form-signin .checkbox {
                margin-bottom: 10px;
            }
            .form-signin .checkbox {
                font-weight: normal;
            }
            .form-signin .form-control {
                position: relative;
                font-size: 16px;
                height: 20px;
                padding: 20px;
                -webkit-box-sizing: border-box;
                -moz-box-sizing: border-box;
                box-sizing: border-box;
            }
            .form-signin .form-control:focus {
                z-index: 2;
            }
            .form-signin input[type="text"] {
                margin-bottom: 0px;
                border-radius: 5px;
            }
            .form-signin input[type="password"] {
                margin-bottom: 0px;
                border-radius: 5px;
            }
            .input-group {
                margin-bottom: 15px;
            }
            .login-footer{
                background:#f0f0f0;
                margin: 0 auto;
                border-top: 1px solid #dadada;
                padding:20px;
            }
            .login-footer .left-section a{
                font-weight:bold;
                line-height:19px;
            }
            .mg-btm{
                margin-bottom:20px;
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
                    <li><a  style="color:white" href="/login/">Login</a></li>
                </ul>
            </div>
        </nav>
        <!--This is where the login screen in created-->
        <div class="container">
            <div class="content">
                <div class="container">
                    <div class="row">
                        <form class="form-signin mg-btm">
                            <h3 class="heading-desc">
                                Login</h3>

                            <div class="main">
                                <label>Email</label>
                                <div class="input-group">
                                    <span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
                                    <input type="text" class="form-control" placeholder="" autofocus>
                                </div>
                                <label>Password   <!--<a href="">(forgot password)</a>--></label>
                                 <div class="input-group">
                                     <span class="input-group-addon"><i class="glyphicon glyphicon-lock"></i></span>
                                     <input type="password" class="form-control" placeholder="Password">
                                 </div>

                                 <div class="row">
                                     <div class="col-xs-6 col-md-6">

                                     </div>
                                     <div class="col-xs-6 col-md-6 pull-right">
                                         <button type="submit" class="btn btn-large btn-success pull-right">Login</button>
                                     </div>
                                 </div>
                             </div>

                             <span class="clearfix"></span>

                             <div class="login-footer">
                                 <div class="row">
                                     <div class="col-xs-6 col-md-6">
                                         <div class="left-section">
                                             <a href="/createaccount/">Create an account</a>
                                         </div>
                                     </div>
                                     <div class="col-xs-6 col-md-6 pull-right">
                                     </div>
                                 </div>
                             </div>
                         </form>
                     </div>
                 </div>
             </div>
         </div>

     </body>
 </html>
