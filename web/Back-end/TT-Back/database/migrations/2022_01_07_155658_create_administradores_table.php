<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateAdministradoresTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        // Schema::create('administradores', function (Blueprint $table) {
        //     $table->engine ='InnoDB';
        //     $table->bigIncrements('id_administradores');
        //     $table->string('nombre_administrador', 40)->comment('Nombre de pila del administrador');
        //     $table->string('apellido_p_administrador', 40)->comment('Apellido paterno del administrador');
        //     $table->string('apellido_m_administrador', 40)->comment('Apellido materno del administrador');
        //     $table->string('nombre_usuario', 40)->comment('Nombre que el administrador una como Nickname');
        //     $table->string('password_hash',120)->comment('Contraseña');
        //     $table->dateTime('fecha_ingreso')->nullable()->comment('Fecha de la ultima vez que inicio sesión');
        //     $table->dateTime('fecha_ult_cambio_pass')->nullable()->comment('Fecha en la que se cambió la contraseña');
        //     // $table->integer('id_status_admin');
        //     $table->unsignedBigInteger('id_status_admin');
        //     $table->foreign('id_status_admin')->references('id_status_admin')->on('status_admins');
        //     // $table->integer('id_tipo_admin');
        //     $table->unsignedBigInteger('id_tipo_admin');
        //     $table->foreign('id_tipo_admin')->references('id_tipo_admin')->on('tipo_admins');
        // });
        Schema::create('Administradores', function (Blueprint $table) {
            $table->engine ='InnoDB';
            $table->bigIncrements('Id_Administradores');
            // $table->integer('id_status_admin');
            $table->unsignedBigInteger('Id_Status_Admin');
            $table->foreign('Id_Status_Admin')->references('id_Status_Admin')->on('Status_admin');
            // $table->integer('id_tipo_admin');
            $table->unsignedBigInteger('Id_Tipo_Admin');
            $table->foreign('Id_Tipo_Admin')->references('Id_Tipo_Admin')->on('Tipo_admin');
            $table->string('Nombre_Admin', 60)->comment('Nombre de pila del administrador');
            $table->string('Apellido_P_Admin', 60)->comment('Apellido paterno del administrador');
            $table->string('Apellido_M_Admin', 60)->comment('Apellido materno del administrador');
            $table->string('Fecha_ingreso',60)->nullable()->comment('Fecha de la ultima vez que inicio sesión');
            $table->string('Nombre_Usuario', 60)->comment('Nombre que el administrador una como Nickname');
            $table->string('Password_Hash',60)->comment('Contraseña');
            $table->string('Fecha_Ultimo_Cambio_Pass',60)->nullable()->comment('Fecha en la que se cambió la contraseña');
            $table->integer('Cant_dias_limit')->comment('Cantidad limite de días');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('administradores');
    }
}
