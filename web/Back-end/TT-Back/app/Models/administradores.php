<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class administradores extends Model
{
    use HasFactory;
    protected $table="administradores";

    // Todos los campos que se les permiten asignar masivamente
    // protected $fillable = [
    //     // Campos que deben ir, por ejemplo 'nombre', 'apellidos'
    // ];

    // // Todos los campos que no queremos que aparezcan en la data que se envía desde el controlador
    // protected $hidden =[
    //     // Campos que deben ir, por ejemplo 'created_at', 'updated_at'
    // ];
}
