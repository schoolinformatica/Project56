@extends("template")
@section("title")
    upload
@stop
@section("content")
    <style type="text/css">


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

        .form-group {
            padding-bottom: 10px;
        }

        .progress {
            margin-top: 40px !important;
        }


    </style>

    @if(Session::has('submitted'))
        <script>$('#succes-modal').modal('toggle');</script>
    @endif

    <div class="container wrap full-width margin-top">

        <div class="row height-200">
            <div class="content">
                <div class="col-lg-12 text-center">
                    <br>

                    <h1 class="leadh1">Upload</h1>

                    <p class="lead">
                        Dear User, on this page you can upload files to our servers. Our servers will process the file
                        and
                        create reports of it.
                        For inserting only .CSV files are allowed.
                    </p>
                </div>
            </div>
        </div>
        <div class="container margin-top">
            <div class="row box">
                <div class="col-md-4">
                    <img class="img-responsive"
                         src="http://bethink.virtualcolors.net/wp-content/uploads/2014/03/csv-xxl.png">
                </div>
                <div class="col-md-8">
                    <h2>Upload</h2>

                    <form class="fileUploadForm" action="/uploadMultiple/" method="post" enctype="multipart/form-data"
                          files=true>
                        <input type="hidden" name="_token" value="<?php echo csrf_token(); ?>">

                        <div class="form-group">

                           <span class="btn btn-primary btn-file">
                               Browse&hellip; <input type="file" id="exampleInputFile" multiple="multiple"
                                                     name="images[]" multiple>
                           </span>
                        </div>
                        <div class="form-group">
                            <input type="text" class="form-control" readonly>
                            <!--<p class="help-block">Example block-level help text here.</p>-->
                        </div>
                        <button type="submit" class="btn btn-default">Upload</button>
                    </form>
                    <div class="progress">
                        <div class="progress-bar progress-bar-info progress-bar-striped active" role="progressbar"
                             aria-valuenow="40" aria-valuemin="0" aria-valuemax="100" style="width:0%">
                            <p class="percent">
                                0%
                            </p>
                        </div>
                    </div>
                </div>


            </div>

        </div>
    </div>

    <!-- Modal -->
    <div id="succes-modal" class="modal fade" role="dialog">
        <div class="modal-dialog">
            <!-- Modal content-->
            <div class="modal-content">
                <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal">&times;</button>
                    <h4 class="modal-title">Successfully uploaded</h4>
                </div>
                <div class="modal-body">
                    <p>All the files are successfully uploaded. Our system is processing them now.
                        This might take minutes, depending on the size of the files.
                    </p>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                </div>
            </div>
        </div>
    </div>

    <script src="http://malsup.github.com/jquery.form.js"></script>
    <script>
        (function () {

            var bar = $('.progress-bar');
            var percent = $('.percent');
            var status = $('#status');

            $('form').ajaxForm({
                beforeSend: function () {
                    status.empty();
                    var percentVal = '0%';
                    bar.width(percentVal)
                    percent.html(percentVal);
                },
                uploadProgress: function (event, position, total, percentComplete) {
                    var percentVal = percentComplete + '%';
                    bar.width(percentVal)
                    percent.html(percentVal);
                },
                success: function () {
                    var percentVal = '100%';
                    bar.width(percentVal)
                    percent.html(percentVal);
                },
                complete: function (xhr) {
                    $('#succes-modal').modal('toggle');
                }
            });

        })();
    </script>

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