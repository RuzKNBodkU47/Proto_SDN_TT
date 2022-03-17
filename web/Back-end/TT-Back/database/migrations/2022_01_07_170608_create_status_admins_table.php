<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateStatusAdminsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        // Schema::create('status_admins', function (Blueprint $table) {
        //     $table->engine ='InnoDB';
        //     $table->bigIncrements('id_status_admin');
        //     $table->string('nombre_status_admin', 40)->comment('Nombre del status de admin');
        // });
        Schema::create('Status_admin', function (Blueprint $table) {
            $table->engine ='InnoDB';
            $table->bigIncrements('Id_Status_Admin');
            $table->string('Nom_Tipo_Admin', 60)->comment('Nombre del status de admin');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('status_admins');
    }
}
