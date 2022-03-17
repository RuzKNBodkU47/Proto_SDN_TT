<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class status_log extends Model
{
    use HasFactory;
    public $timestamps = false;
    protected $table = 'status_log';
}
