<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreatePositionsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('positions', function (Blueprint $table) {
            $table->timestamp('DateTime');
            $table->bigInteger('UnitId');
            $table->double('Rdx');
            $table->double('Rdy');
            $table->bigInteger('Speed');
            $table->double('Course');
            $table->integer('NumSatellites');
            $table->integer('HDOP');
            $table->char('Quality');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::drop('positions');
    }
}
