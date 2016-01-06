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
		<form action="http://145.24.222.182/PDFMaker/processing/downloadFormHandler.php" method="get">
                <tr>
                    <td>1</td>
                    <td>Connections.csv</td>
                    <td align='left'>
                        <input type="Radio" name="csv" value="connections" style='width:30%">
                    </td>
                </tr>
                <tr>
                    <td>2</td>
                    <td>Positions.csv</td>
                    <td align='left'>
                        <input type="Radio" name="csv" value="positions" style='width:30%">
                    </td>
                </tr>
                <tr>
                    <td>3</td>
                    <td>Events.csv</td>
                    <td align='left'>
                        <input type="Radio" name="csv" value="events" style='width:30%">
                    </td>
                </tr>
                <tr>
                    <td>4</td>
                    <td>Monitoring.csv</td>
                    <td align='left'>
                        <input type="Radio" name="csv" value="monitoring" style='width:30%"> 
                    </td>
                </tr>
		<tr>
		    <td>Uw emailadres: </td>
		    <td align='left'>
			<input type="text" name="email" style='width:30%">
		    </td>
		</tr>
		<tr>
		    <td align='left'>
			<input type="Submit" name="submit" style='width:30%">
		    </td>
		</tr>
                </tbody>
		</form>
            </table>
        </div>
    </div>
@stop
