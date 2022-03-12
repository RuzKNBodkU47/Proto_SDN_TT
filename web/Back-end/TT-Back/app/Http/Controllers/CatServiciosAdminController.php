<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\cat_servicios_administradores;

class CatServiciosAdminController extends Controller
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
                'id_cat_servicios' => 'required'
            ]); 
            // return $validated;
            $catservicioadmin = new cat_servicios_administradores();
            if ($catservicioadmin) {
                $catservicioadmin->fecha_ult_mod = $request->fecha_ult_mod;
                $catservicioadmin->status_servicios_admin = $request->status_servicios_admin;
                $catservicioadmin->id_administradores = $request->id_administradores;
                $catservicioadmin->id_cat_servicios = $request->id_cat_servicios;
                // return $catservicioadmin;
                $catservicioadmin->save();
                return response()->json(['data'=>[],"message"=>"Servicio en catálogo regristrada con éxito","code"=>201]);    
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
        // return cat_servicios_administradores::get();
        try { 
            $cservicioadmin = cat_servicios_administradores::where('id_cat_servicios_administradores', '=', $id)->get();
            if (count($cservicioadmin) == 0) {
                return response()->json(["message"=>"Servicio en catalogo del administrador no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$cservicioadmin,"message"=>"Servicio en catalogo del administrador encontrado con éxito","code"=>200]);
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
            return cat_servicios_administradores::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
}
