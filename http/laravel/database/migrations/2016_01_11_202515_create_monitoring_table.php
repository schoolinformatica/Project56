<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateMonitoringTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('monitoring', function (Blueprint $table) {
            $table->bigInteger('UnitId');
            $table->timestamp('BeginTime');
            $table->timestamp('EndTime');
            $table->charset('Type');
            $table->double('Min');
            $table->double('Max');
            $table->double('Sum');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::drop('monitoring');
    }
}
