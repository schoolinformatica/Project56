@extends('template')
@section('content')
    <div class="container full-width wrap margin-top">
        <div class="row height-200">
            <div class="content">
                <div class="col-lg-12 text-center">
                    <br>

                    <h1 class="leadh1">My files</h1>

                    <p class="lead">
                        On this page all your custom generated reports are represented.
                        To download an report click the corresponding download button.
                    </p>
                </div>
            </div>
        </div>

        @if(count($my_files) > 0)
            <div class="container margin-top">
                <div class="row box">
                    <h2>My reports</h2>

                    <p>Click to download a report.</p>
                    <table class="table table-hover">
                        <thead>
                        <tr>
                            <th>File</th>
                            <th>Downloadlink</th>
                        </tr>
                        </thead>
                        <tbody>
                        @foreach($my_files as $file)
                            <tr>
                                <td>{{ $file->filename }}</td>
                                <td>http://145.24.222.240/downloads/{{ $file->filename }}</td>
                                <td><a href="/downloads/{{ $file->filename }}" type="button"
                                       class="btn btn-primary">Download</a></td>
                            </tr>

                        @endforeach
                        </tbody>
                    </table>
                </div>
            </div>
        @else
            <h2>Download reports</h2>
            <p>You have no reports to download.</p>
        @endif
    </div>
@stop
