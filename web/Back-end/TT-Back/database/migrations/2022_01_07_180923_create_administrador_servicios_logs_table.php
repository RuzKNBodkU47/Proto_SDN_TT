<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateAdministradorServiciosLogsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        // Schema::create('administrador_servicios_logs', function (Blueprint $table) {
        //     $table->bigIncrements('id_administrador_servicios_logs');
        //     $table->string('ip_dispositivo_ant', 40)->comment('dirección ip anterior');            
        //     $table->string('ip_dispositivo_desp', 40)->comment('dirección ip posterior');
        //     $table->dateTime('fecha_inicio')->nullable()->comment('Fecha de inicio del servicio');
        //     $table->dateTime('fecha_fin')->nullable()->comment('Fecha de fin del servicio');
        //     $table->string('local_dir_mac', 40)->comment('dirección mac de donde se aplica al servicio');
        //     $table->unsignedBigInteger('id_status_log');
        //     $table->foreign('id_status_log')->references('id_status_log')->on('status_logs');
        //     $table->unsignedBigInteger('id_administradores');
        //     $table->foreign('id_administradores')->references('id_administradores')->on('administradores');
        //     $table->unsignedBigInteger('id_cat_servicios');
        //     $table->foreign('id_cat_servicios')->references('id_cat_servicios')->on('cat_servicios');
        // });
        Schema::create('Administradores_Servicios_Log', function (Blueprint $table) {
            $table->bigIncrements('Id_Administradores_Servicios_Log');
            $table->unsignedBigInteger('Id_Status_Log');
            $table->foreign('Id_Status_Log')->references('Id_Status_Log')->on('Status_log');
            $table->unsignedBigInteger('Id_Administradores');
            $table->foreign('Id_Administradores')->references('Id_Administradores')->on('Administradores');
            $table->unsignedBigInteger('Id_Cat_Servicios');
            $table->foreign('Id_Cat_Servicios')->references('Id_Cat_Servicios')->on('Cat_servicios');
            $table->string('Ip_Dispositivo_Orig', 20)->comment('dirección ip de origen');
            $table->string('MAC_Dispositivo_Orig', 30)->comment('dirección mac anterior');
            $table->string('Ip_Dispositivo_Ant', 20)->comment('dirección ip anterior');            
            $table->string('Ip_Dispositivo_Desp', 20)->comment('dirección ip posterior');
            $table->string('Dir_MAC_Disp_Fin', 30)->comment('dirección mac del dispositivo final');
            $table->string('Fecha_Init_Serv',60)->nullable()->comment('Fecha de inicio del servicio');
            $table->string('Fecha_Fin_Serv',60)->nullable()->comment('Fecha de fin del servicio');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('administrador_servicios_logs');
    }
}
