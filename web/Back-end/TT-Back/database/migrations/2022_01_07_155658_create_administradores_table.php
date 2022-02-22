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
        Schema::create('administradores', function (Blueprint $table) {
            $table->engine ='InnoDB';
            $table->bigIncrements('id_administradores');
            $table->string('nombre_administrador', 40)->comment('Nombre de pila del administrador');
            $table->string('apellido_p_administrador', 40)->comment('Apellido paterno del administrador');
            $table->string('apellido_m_administrador', 40)->comment('Apellido materno del administrador');
            $table->string('nombre_usuario', 40)->comment('Nombre que el administrador una como Nickname');
            $table->string('password_hash',120)->comment('Contraseña');
            $table->dateTime('fecha_ingreso')->nullable()->comment('Fecha de la ultima vez que inicio sesión');
            $table->dateTime('fecha_ult_cambio_pass')->nullable()->comment('Fecha en la que se cambió la contraseña');
            // $table->integer('id_status_admin');
            $table->unsignedBigInteger('id_status_admin');
            $table->foreign('id_status_admin')->references('id_status_admin')->on('status_admins');
            // $table->integer('id_tipo_admin');
            $table->unsignedBigInteger('id_tipo_admin');
            $table->foreign('id_tipo_admin')->references('id_tipo_admin')->on('tipo_admins');
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
