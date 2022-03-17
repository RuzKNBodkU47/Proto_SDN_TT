<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateStatusLogsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        // Schema::create('status_logs', function (Blueprint $table) {
        //     $table->bigIncrements('id_status_log');
        //     $table->string('nom_status_log', 40)->comment('Nombre del log');
        // });
        Schema::create('Status_log', function (Blueprint $table) {
            $table->bigIncrements('Id_Status_Log');
            $table->string('Nom_Status_Log', 60)->comment('Nombre del log');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('status_logs');
    }
}
