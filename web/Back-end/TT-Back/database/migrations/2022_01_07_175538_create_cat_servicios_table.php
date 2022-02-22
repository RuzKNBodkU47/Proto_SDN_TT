<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateCatServiciosTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('cat_servicios', function (Blueprint $table) {
            $table->bigIncrements('id_cat_servicios');
            $table->string('nom_cat_servicios', 40)->comment('Nombre del catalogo de servicios');
            $table->dateTime('fecha_insercion')->nullable()->comment('Fecha en la que se insertó al catalogo');
            $table->dateTime('fecha_ult_mod')->nullable()->comment('Fecha en la que se modificó el catalogo por ultima vez');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('cat_servicios');
    }
}
