@extends('template')
@section('content')


    @if(count($my_files) > 0)
        <div class="container">
            <h2>Download reports</h2>

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
                        <td>http://linknaardefile.com/downloads/{{ $file->filename }}</td>
                        <td><a href="http://linknaardefile.nl/downloads/{{ $file->filename }}" type="button"
                               class="btn btn-primary">Download</a></td>
                    </tr>

                @endforeach
                </tbody>
            </table>
        </div>
    @else
        <h2>Download reports</h2>
        <p>You have no reports to download.</p>
    @endif

@stop
