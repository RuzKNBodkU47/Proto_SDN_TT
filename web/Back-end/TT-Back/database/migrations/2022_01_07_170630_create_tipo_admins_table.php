<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateTipoAdminsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        // Schema::create('tipo_admins', function (Blueprint $table) {
        //     $table->bigIncrements('id_tipo_admin');
        //     $table->string('nom_tipo_admin', 40)->comment('Nombre del tipo de admin');
        // });
        Schema::create('Tipo_admin', function (Blueprint $table) {
            $table->bigIncrements('Id_Tipo_Admin');
            $table->string('Nom_Tipo_Admin', 60)->comment('Nombre del tipo de admin');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('tipo_admins');
    }
}
