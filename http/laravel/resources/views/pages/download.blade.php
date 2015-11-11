<!DOCTYPE html>
<html>
<head>
    <title>Download</title>

        <link href="https://fonts.googleapis.com/css?family=Lato:100" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

        <style type="text/css">


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
                    <li><a  style="color:white" href="/download/">Download files</a></li>
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

<div class="container">
    <div class="row">
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
              <td>Voertuigen Analyse</td>
              <td align='left'><form><input type=submit value="Download" style="width:25%"></form></td>
          </tr>
          <tr>
              <td>2</td>
              <td>Kapotte Voertuigen</td>
              <td align='left'><form><input type=submit value="Download" style="width:25%"></form></td>
          </tr>
          <tr>
              <td>3</td>
              <td>Deathstar Schematics</td>
              <td align='left'><form><input type=submit value="Download" style="width:25%"></form></td>
          </tr>
            </tbody>
        </table>
    </div>

    </div>
</div>
</body>
</html>