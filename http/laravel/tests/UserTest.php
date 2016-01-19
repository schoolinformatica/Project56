<?php

use Illuminate\Foundation\Testing\WithoutMiddleware;
use Illuminate\Foundation\Testing\DatabaseMigrations;
use Illuminate\Foundation\Testing\DatabaseTransactions;

class UserTest extends TestCase
{
    /**
     * A basic test example.
     *
     * @return void
     */
    public function testHome()
    {
        $this->visit('/')
             ->see('Vala Afshar');
    }

    public function testAbout()
    {
        $this->visit('/about/')
             ->see('Cooperatio');
    }

    public function testLinks()
    {
        $this->visit('/')
             ->click('About Us')
             ->seePageIs('/about/');
    }
}
