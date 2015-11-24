<?php
include('session.php');
?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>

    <!--[if lt IE 9] -->
    <script type="text/javascript">
        document.createElement('header');
        document.createElement('nav');
        document.createElement('section');
        document.createElement('article');
        document.createElement('aside');
        document.createElement('footer');

    </script>
    <!--[endif]-->
    <link href="style.css" rel="stylesheet" type="text/css"/>

</head>
<body>

<section>

    <div class="container">

        <div class="tekst">
            <div id="profile">
                <b id="welcome">Welkom: <i><?php echo $login_session; ?></i></b>
                <b id="logout"><a href="logout.php">Uitloggen</a></b><br>
            </div>


        </div>
    </div>

</section>


<script type="text/javascript" src="../scripts/jquery-1.7.2.min.js"></script>
<script type="text/javascript" src="../scripts/main.js"></script>

</body>
</html>
