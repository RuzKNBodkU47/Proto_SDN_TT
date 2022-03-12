<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\cat_tareas_administradores;

class CatTareasAdminController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        //
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        //
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        //
        // return $request;
        try {
            $validated = $request->validate([
                'fecha_ult_mod' => 'required',
                'status_servicios_admin' => 'required',
                'id_administradores' => 'required',
                'id_cat_tareas' => 'required'
            ]); 
            // return $validated;
            $cattareasadmin = new cat_tareas_administradores();
            if ($cattareasadmin) {
                $cattareasadmin->fecha_ult_mod = $request->fecha_ult_mod;
                $cattareasadmin->status_servicios_admin = $request->status_servicios_admin;
                $cattareasadmin->id_administradores = $request->id_administradores;
                $cattareasadmin->id_cat_tareas = $request->id_cat_tareas;
                // return $cattareasadmin;
                $cattareasadmin->save();
                return response()->json(['data'=>[],"message"=>"Tarea en catálogo regristrada con éxito","code"=>201]);    
                # code...
            }else{
                return response()->json(['data'=>[],"message"=>"No se agregó nombre","code"=>403]);
            }
            //code...
        } catch (\Throwable $th) {
            //throw $th;
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        //
        // return cat_tareas_administradores::get();
        try { 
            $ctareaadmin = cat_tareas_administradores::where('id_cat_tareas_administradores', '=', $id)->get();
            if (count($ctareaadmin) == 0) {
                return response()->json(["message"=>"Tarea en catalogo de administrador no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$ctareaadmin,"message"=>"Tarea en catalogo de administrador encontrado con éxito","code"=>200]);
            }
        } catch (\Throwable $th) {
            return \Response::json(['find' => false,"message"=>$th], 404);
        }
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        //
    }
    public function showall(){
        try { 
            return cat_tareas_administradores::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
}
