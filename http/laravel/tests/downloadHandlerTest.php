<?php

class downloadHandlerTest extends PHPUnit_Framework_TestCase
{
    public function testEmailNullParam()
    {
        $expectedOutput = "email not given!";
	$_GET['email'] = "";
	$_GET['csv'] = "connections"; 
	$actualOutput = include "/home/ubuntu-0902130/project56/Project56/http/laravel/public/PDFMaker/processing/downloadFormHandler.php";
        $this->assertEquals($expectedOutput, $actualOutput);
    }

    public function testCsvNullParam()
    {
        $expectedOutput = "csv not given!";
        $_GET['email'] = "foo@foo.foo";
        $_GET['csv'] = "";
	$actualOutput = include "/home/ubuntu-0902130/project56/Project56/http/laravel/public/PDFMaker/processing/downloadFormHandler.php";
        $this->assertEquals($expectedOutput, $actualOutput);
    }
}
