<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateCatTareasAdministradoresTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        // Schema::create('cat_tareas_administradores', function (Blueprint $table) {
        //     $table->bigIncrements('id_cat_tareas_administradores');
        //     $table->dateTime('fecha_ult_mod')->nullable()->comment('Fecha en la que se modificó el catalogo por ultima vez');            
        //     $table->integer('status_servicios_admin');
        //     $table->unsignedBigInteger('id_administradores');
        //     $table->foreign('id_administradores')->references('id_administradores')->on('administradores');
        //     $table->unsignedBigInteger('id_cat_tareas'); 
        //     $table->foreign('id_cat_tareas')->references('id_cat_tareas')->on('cat_tareas');       
        // });
        Schema::create('Tipo_Admin_Cat_Tareas', function (Blueprint $table) {
            $table->bigIncrements('Id_Tipo_Admin_Tareas');           
            // $table->integer('status_servicios_admin');
            $table->unsignedBigInteger('Id_Administrador');
            $table->foreign('Id_Administrador')->references('Id_Administradores')->on('Administradores');
            $table->unsignedBigInteger('Id_Cat_Tareas'); 
            $table->foreign('Id_Cat_Tareas')->references('Id_Cat_Tareas')->on('Cat_tareas');
            $table->string('Fecha_Ult_Mod')->nullable()->comment('Fecha en la que se modificó el catalogo por ultima vez');        
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('cat_tareas_administradores');
    }
}
