@extends("template")
@section("title")
    download
@stop
@section("content")
    <div class="row">
        <div class="content">
            <h2>Download</h2>

            <p>Selecteer een van de hieronderstaande data en klik dan op download</p>
            <table class="table table-hover">
                <thead>
                <tr>
                    <th>ID</th>
                    <th>Name</th>
                    <th>Download</th>
                </tr>
                </thead>
                <tbody>
                <tr>
                    <td>1</td>
                    <td>Connections.csv</td>
                    <td align='left'>
                        <form><input type=submit value="Download" style="width:30%"></form>
                    </td>
                </tr>
                <tr>
                    <td>2</td>
                    <td>Positions.csv</td>
                    <td align='left'>
                        <form><input type=submit value="Download" style="width:30%"></form>
                    </td>
                </tr>
                <tr>
                    <td>3</td>
                    <td>Events.csv</td>
                    <td align='left'>
                        <form><input type=submit value="Download" style="width:30%"></form>
                    </td>
                </tr>
                <tr>
                    td>4</td>
                    <td>Monitoring.csv</td>
                    <td align='left'>
                        <form><input type=submit value="Download" style="width:30%"></form>
                    </td>
                </tr>
                </tbody>
            </table>
        </div>
    </div>
@stop