<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class datos_dispo extends Model
{
    protected $connection = 'comments';
    use HasFactory;

    protected $table = "datos_dispo";
}
