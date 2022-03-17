<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class administradores_tareas_log extends Model
{
    use HasFactory;
    public $timestamps = false;
    protected $table = 'administradores_tareas_log';
}
