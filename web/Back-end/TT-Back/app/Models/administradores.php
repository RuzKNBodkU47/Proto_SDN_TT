<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class administradores extends Model
{
    use HasFactory;
    public $timestamps = false;
    protected $table="administradores";
    protected $primaryKey='Id_Administradores';

    // Todos los campos que se les permiten asignar masivamente
    protected $fillable = [
        // 'nombre_administrador',
        // 'apellido_p_administrador',
        // 'apellido_m_administrador',
        // 'nombre_usuario',
        // 'password_hash',
        
        // Campos que deben ir, por ejemplo 'nombre', 'apellidos'
    ];

    // // Todos los campos que no queremos que aparezcan en la data que se envía desde el controlador
    protected $hidden =[
        // Campos que deben ir, por ejemplo 'created_at', 'updated_at'
    ];
}
