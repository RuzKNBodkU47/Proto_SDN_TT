<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\administrador_servicios_log;

class AdminServiciosLogController extends Controller
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
                'ip_dispositivo_ant' => 'required',
                'ip_dispositivo_desp' => 'required',
                'fecha_inicio' => 'required',
                'fecha_fin' => 'required',
                'local_dir_mac' => 'required',
                'id_status_log' => 'required',
                'id_administradores' => 'required',
                'id_cat_servicios' => 'required'
            ]); 
            // return $validated;
            $adminserviciolog = new administrador_servicios_log();
            if ($adminserviciolog) {
                $adminserviciolog->ip_dispositivo_ant = $request->ip_dispositivo_ant;
                $adminserviciolog->ip_dispositivo_desp = $request->ip_dispositivo_desp;
                $adminserviciolog->fecha_inicio = $request->fecha_inicio;
                $adminserviciolog->fecha_fin = $request->fecha_fin;
                $adminserviciolog->local_dir_mac = $request->local_dir_mac;
                $adminserviciolog->id_status_log = $request->id_status_log;
                $adminserviciolog->id_administradores = $request->id_administradores;
                $adminserviciolog->id_cat_servicios = $request->id_cat_servicios;
                // return $adminserviciolog;
                $adminserviciolog->save();
                return response()->json(['data'=>[],"message"=>"Servicio log regristrada con éxito","code"=>201]);    
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
}
