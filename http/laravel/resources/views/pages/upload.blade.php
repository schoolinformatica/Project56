@extends("template")
@section("title")
    upload
@stop
@section("content")
    <style type="text/css">

        .row {
            margin-bottom:50px;
            padding:20px;
            background-color:#eeeeee ;
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

    <div class="row">
        <div class="content">
            <div class="col-lg-12 text-center">
                <h1 class="leadh1">Upload</h1>

                <p class="lead">
                    Dear User, on this page you can upload files to our servers. Our servers will process the file and
                        create reports of it.
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


        <script> //Script to let the file feedback work (the readonly textblock which shows the chosen file)
            $(document).on('change', '.btn-file :file', function () {
                var input = $(this),
                        numFiles = input.get(0).files ? input.get(0).files.length : 1,
                        label = input.val().replace(/\\/g, '/').replace(/.*\//, '');
                input.trigger('fileselect', [numFiles, label]);
            });

            $(document).ready(function () {
                $('.btn-file :file').on('fileselect', function (event, numFiles, label) {

                    var input = $(this).parents('.fileUploadForm').find(':text'),
                            log = numFiles > 1 ? numFiles + ' files selected' : label;

                    if (input.length) {
                        input.val(log);
                    } else {
                        if (log) alert(log);
                    }

                });
            });
        </script>
@stop