<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\AdministradorController;
use App\Http\Controllers\StatusAdminController;
use App\Http\Controllers\TipoAdminController;
use App\Http\Controllers\CatTareasController;
use App\Http\Controllers\CatServiciosController;
use App\Http\Controllers\CatTareasAdminController;
use App\Http\Controllers\CatServiciosAdminController;
use App\Http\Controllers\AdminTareasLogController;
use App\Http\Controllers\AdminServiciosLogController;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

Route::middleware(['auth:sanctum', 'auth:api'])->get('/user', function (Request $request) {
    return $request->user();
});

// Route::middleware('auth:api')->get('/user', function (Request $request) {
//     return $request->user();
// });

// Route::group(['middleware'=>'api'], function ($router) {
//     Route::get('administrador','app\Http\Controllers\AdministradorController@prueba');
// });

// Route::ApiResource(name:'administrador', controller:'AdministradorController');

// Route::get('administrador', [AdministradorController::class,'prueba']);
Route::get('administrador','App\Http\Controllers\AdministradorController@prueba');

Route::post('create','App\Http\Controllers\AdministradorController@store');
Route::post('createstatusa','App\Http\Controllers\StatusAdminController@store');
Route::post('createtipoa','App\Http\Controllers\TipoAdminController@store');
Route::post('creacattarea','App\Http\Controllers\CatTareasController@store');
Route::post('creacatservicio','App\Http\Controllers\CatServiciosController@store');
Route::post('creastatuslog','App\Http\Controllers\StatusLogController@store');
Route::post('creacattareaadmin','App\Http\Controllers\CatTareasAdminController@store');
Route::post('creacatservicioadmin','App\Http\Controllers\CatServiciosAdminController@store');
Route::post('creaadmintarealog','App\Http\Controllers\AdminTareasLogController@store');
Route::post('creaadminserviciolog','App\Http\Controllers\AdminServiciosLogController@store');

Route::get('muestra','App\Http\Controllers\AdministradorController@showall');
Route::get('muestrastatusa','App\Http\Controllers\StatusAdminController@showall');
Route::get('muestratipoa','App\Http\Controllers\TipoAdminController@showall');
Route::get('muestracattarea','App\Http\Controllers\CatTareasController@showall');
Route::get('muestracatservicio','App\Http\Controllers\CatServiciosController@showall');
Route::get('muestrastatuslog','App\Http\Controllers\StatusLogController@showall');
Route::get('muestracattareaadmin','App\Http\Controllers\CatTareasAdminController@showall');
Route::get('muestracatservicioadmin','App\Http\Controllers\CatServiciosAdminController@showall');
Route::get('muestraadmintarealog','App\Http\Controllers\AdminTareasLogController@showall');
Route::get('muestraadminserviciolog','App\Http\Controllers\AdminServiciosLogController@showall');


