<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\administrador_tareas_log;

class AdminTareasLogController extends Controller
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
                'fecha_inicio' => 'required',
                'fecha_fin' => 'required',
                'local_dir_mac' => 'required',
                'id_status_log' => 'required',
                'id_administradores' => 'required',
                'id_cat_tareas' => 'required'
            ]); 
            // return $validated;
            $admintareaslog = new administrador_tareas_log();
            if ($admintareaslog) {
                $admintareaslog->fecha_inicio = $request->fecha_inicio;
                $admintareaslog->fecha_fin = $request->fecha_fin;
                $admintareaslog->local_dir_mac = $request->local_dir_mac;
                $admintareaslog->id_status_log = $request->id_status_log;
                $admintareaslog->id_administradores = $request->id_administradores;
                $admintareaslog->id_cat_tareas = $request->id_cat_tareas;
                // return $admintareaslog;
                $admintareaslog->save();
                return response()->json(['data'=>[],"message"=>"Tarea log regristrada con éxito","code"=>201]);    
                # code...
            }else{
                return response()->json(['data'=>[],"message"=>"No se agregó","code"=>403]);
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
            return administrador_tareas_log::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
}
