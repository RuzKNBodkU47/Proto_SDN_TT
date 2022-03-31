<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateAdministradorTareasLogsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        // Schema::create('administrador_tareas_logs', function (Blueprint $table) {
        //     $table->bigIncrements('id_administrador_tareas_logs');
        //     $table->dateTime('fecha_inicio')->nullable()->comment('Fecha de inicio de la tarea');
        //     $table->dateTime('fecha_fin')->nullable()->comment('Fecha de fin de la tarea');
        //     $table->string('local_dir_mac', 40)->comment('dirección mac de donde se aplica la tarea');
        //     $table->unsignedBigInteger('id_status_log');
        //     $table->foreign('id_status_log')->references('id_status_log')->on('status_logs');
        //     $table->unsignedBigInteger('id_administradores');
        //     $table->foreign('id_administradores')->references('id_administradores')->on('administradores');
        //     $table->unsignedBigInteger('id_cat_tareas');
        //     $table->foreign('id_cat_tareas')->references('id_cat_tareas')->on('cat_tareas');
        // });
        Schema::create('Administradores_Tareas_Log', function (Blueprint $table) {
            $table->bigIncrements('Id_Administradores_Tareas_Log');
            $table->unsignedBigInteger('Id_Status_Log');
            $table->foreign('Id_Status_Log')->references('Id_Status_Log')->on('Status_log');
            $table->unsignedBigInteger('Id_Administradores');
            $table->foreign('Id_Administradores')->references('Id_Administradores')->on('Administradores');
            $table->unsignedBigInteger('Id_Cat_Tareas');
            $table->foreign('Id_Cat_Tareas')->references('Id_Cat_Tareas')->on('Cat_tareas');
            $table->string('Ip_Dispositivo_Orig', 20)->comment('dirección ip de origen');
            $table->string('MAC_Dispositivo_Orig', 30)->comment('dirección mac anterior');
            $table->unsignedBigInteger('Id_Admin_Obj');
            $table->foreign('Id_Admin_Obj')->references('Id_Cat_Tareas')->on('Cat_tareas');
            $table->string('Fecha_Init_Serv',60)->nullable()->comment('Fecha de inicio de la tarea');
            $table->string('Fecha_Fin_Serv',60)->nullable()->comment('Fecha de fin de la tarea');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('administrador_tareas_logs');
    }
}
