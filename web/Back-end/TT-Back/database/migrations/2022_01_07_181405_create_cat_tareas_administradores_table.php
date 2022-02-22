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
        Schema::create('cat_tareas_administradores', function (Blueprint $table) {
            $table->bigIncrements('id_cat_tareas_administradores');
            $table->dateTime('fecha_ult_mod')->nullable()->comment('Fecha en la que se modificó el catalogo por ultima vez');            
            $table->integer('status_servicios_admin');
            $table->unsignedBigInteger('id_administradores');
            $table->foreign('id_administradores')->references('id_administradores')->on('administradores');
            $table->unsignedBigInteger('id_cat_tareas'); 
            $table->foreign('id_cat_tareas')->references('id_cat_tareas')->on('cat_tareas');       
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
