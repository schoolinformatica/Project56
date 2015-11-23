<?php
include('login.php'); // Includes Login Script

if (isset($_SESSION['login_user'])) {
    header("location: profile.php");
}
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
    <link rel="stylesheet" type="text/css" href="style.css"


</head>
<body>

<section>
    <div class=container>
        <div class="begin">
            <h1 class="titel">Administratie paneel</h1>
        </div>
        <div class="clearfix"></div>

        <div id="tekst">


            <div id="login">

                <form class="contactform" action="" method="post">
                    <label>Gebruikersnaam :</label>
                    <input id="name" name="username" placeholder="gebruikersnaam" type="text">
                    <label>Wachtwoord:</label>
                    <input id="password" name="password" placeholder="*******" type="password">
                    <input name="submit" type="submit" value=" Login ">
                    <span><?php echo $error; ?></span>
                </form>
            </div>
        </div>




    </div>
</section>


<script type="text/javascript" src="../scripts/jquery-1.7.2min.js"></script>
<script type="text/javascript" src="../scripts/main.js"></script>
<script type="text/javascript" src="../scripts/scroll.js"></script>.

</body>
</html>


