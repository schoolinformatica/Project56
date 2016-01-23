@extends("template")
@section("title")
    download
@stop
@section("content")

    @if(Session::has('message'))
        <script>$('#succes-modal').modal('toggle');</script>
    @endif


    <div class="container wrap full-width margin-top">
        <div class="row height-200">
            <div class="content">
                <div class="col-lg-12 text-center">
                    <br>

                    <h1 class="leadh1">Download</h1>

                    <p class="lead">
                        On this page it is possible to generate reports of the City-gis
                        data.
                    </p>
                </div>
            </div>
        </div>
        <div class="container margin-top">
            <div class="row box">
                <div class="col-md-4">
                    <img class="img-responsive" src="http://www.experian.com/assets/marketing-services/images/benchmark-report-graph-q3.png">
                </div>
                <div class="col-md-8">
                    <h3>How it works</h3>
                    <p>
                        After you pressed the "Generate" button the system starts generating
                        your custom report file. This mights take minutes, depending on your
                        preferences and the amount of data. When the report is done, you
                        will be notified by email and the download to the file will be
                        added to your files in the "My reports" section.
                    </p>
                    <h2>Download</h2>
                    <form action="/generateReport" method="post" role="form">
                        <input type="hidden" name="_token" value="<?php echo csrf_token(); ?>">
                        <input type="hidden" name="email" value="{{ $user->email }}" >
                        <div class="form-group">
                            <label for="table">Table:</label>
                            <select class="form-control" name="table" id="table-select">
                                <option value="connections">connections</option>
                                <option value="events">events</option>
                                <option value="monitoring">monitoring</option>
                                <option value="positions">positions</option>
                            </select>
                        </div>
                        <div class="form-group">
                            <table class="form-table">
                                <tr>
                                    <td>
                                        <label for="date-1">From:</label>
                                        <input id="date-1" type="date" class="form-control" name="date-start" required>
                                    </td>
                                    <td>
                                        <label for="date-2">Untill:</label>
                                        <input id="date-2" type="date" class="form-control" name="date-end" required>
                                    </td>
                                </tr>
                            </table>
                            <button type="submit" class="btn btn-default">Generate</button>

                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>


    <div id="succes-modal" class="modal fade" role="dialog">
        <div class="modal-dialog">
            <div class="modal-content">
                <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal">&times;</button>
                    <h4 class="modal-title">Successfully generating</h4>
                </div>
                <div class="modal-body">
                    <p>
                        We are processing your report now. You will be notified by email.
                    </p>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                </div>
            </div>
        </div>
    </div>
@stop