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
                    @if(Auth::check())
                        <li><a href="/auth/logout/">Logout</a></li>
                    @else
                        <li><a href="/auth/login/">Login</a></li>
                    @endif
                </ul>
            </div>

        </nav>


        <div class="container">

            <div class="row">
                <div class="content">
                    <div class="col-lg-12 text-center">
                        <h1 class="leadh1">Upload</h1>
                        <p class="lead">
                            Dear <User>, on this page you can upload files to our servers. Our servers will process the file and create reports of it.
                            For inserting only .CSV files are allowed.
                        </p>
                    </div>
                </div>
            </div>

            <div class="row">
                <div class="content">
                    <form class="fileUploadForm" action="/uploadMultiple/" method="post" enctype="multipart/form-data" files=true>
                        <input type="hidden" name="_token" value="<?php echo csrf_token(); ?>">
                        <label for="exampleInputFile">File input</label>
                        <div class="form-group">

                            <span class="btn btn-primary btn-file">
                                Browse&hellip; <input type="file" id="exampleInputFile" multiple="multiple" name="images[]" multiple>
                            </span>
                        </div>
                        <div class="form-group">
                            <input type="text" class="form-control" readonly>
                            <!--<p class="help-block">Example block-level help text here.</p>-->
                        </div>
                        <button type="submit" class="btn btn-default">Submit</button>
                    </form>
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




        <script> //Script to let the file feedback work (the readonly textblock which shows the chosen file)
        $(document).on('change', '.btn-file :file', function() {
          var input = $(this),
              numFiles = input.get(0).files ? input.get(0).files.length : 1,
              label = input.val().replace(/\\/g, '/').replace(/.*\//, '');
          input.trigger('fileselect', [numFiles, label]);
        });

        $(document).ready( function() {
            $('.btn-file :file').on('fileselect', function(event, numFiles, label) {

                var input = $(this).parents('.fileUploadForm').find(':text'),
                    log = numFiles > 1 ? numFiles + ' files selected' : label;

                if( input.length ) {
                    input.val(log);
                } else {
                    if( log ) alert(log);
                }

            });
        });
        </script>

    </body>
</html>