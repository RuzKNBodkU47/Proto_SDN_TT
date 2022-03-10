<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class administrador_tareas_log extends Model
{
    use HasFactory;
    public $timestamps = false;
    protected $table = 'administrador_tareas_logs';
}
