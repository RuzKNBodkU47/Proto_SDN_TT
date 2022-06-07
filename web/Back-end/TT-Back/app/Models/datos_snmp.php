<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class datos_snmp extends Model
{
    protected $connection = 'comments';
    use HasFactory;

    protected $table = "datos_snmp";
}
