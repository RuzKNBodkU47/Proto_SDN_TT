<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\cat_servicios;
use Illuminate\Support\Facades\DB;

class CatServiciosController extends Controller
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
                'Nom_Cat_Servicios' => 'required'
                // 'fecha_insercion' => 'required',
                // 'fecha_ult_mod' => 'required'
            ]); 
            // return $validated;
            $catservicio = new cat_servicios();
            if ($catservicio) {
                $catservicio->Nom_Cat_Servicios = $request->Nom_Cat_Servicios;
                // $catservicio->fecha_insercion = date("Y-m-d H:i:s");
                // $catservicio->fecha_ult_mod = date("Y-m-d H:i:s");
                // return $catservicio;
                $catservicio->save();
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
        // return cat_servicios::get();
        try { 
            $cservicio = cat_servicios::where('Id_Cat_Servicios', '=', $id)->get();
            if (count($cservicio) == 0) {
                return response()->json(["message"=>"Servicio en catalogo no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$cservicio,"message"=>"Servicio en catalogo encontrado con éxito","code"=>200]);
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
    public function update(Request $request)
    {
        //
        try {
            // $validated = $request->validate([
            //     'Id_Cat_Servicios'=>'required',
            //     'Nom_Cat_Servicios' => 'required'
            // ]); 
            DB::table('cat_servicios')
            ->where('Id_Cat_Servicios', $request->Id_Cat_Servicios)
            ->update(['Nom_Cat_Servicios' => $request->Nom_Cat_Servicios]);
            return response()->json(['data'=>[],"message"=>"Catalogo de servicios actualizado con éxito","code"=>201]);
        } catch (\Throwable $th) {
            return response(["message"=>"error", 'error'=>$th],422);
        }
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
            return cat_servicios::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
}
