<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\tipo_admin;
use Illuminate\Support\Facades\DB;

class TipoAdminController extends Controller
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
        try {
            //code...
            $validated = $request->validate([
                'Nom_Tipo_Admin' => 'required'
            ]);
            $tipoadmins = new tipo_admin();
            $tipoadmins->Nom_Tipo_Admin = $request->Nom_Tipo_Admin;
            // return $tipoadmins;
            $tipoadmins->save();
            return response()->json(['data'=>[],"message"=>"Nombre del tipo de administrador regristrado con éxito","code"=>201]);
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
        // return tipo_admin::get();
        try { 
            $tadmin = tipo_admin::where('Id_Tipo_Admin', '=', $id)->get();
            if (count($tadmin) == 0) {
                return response()->json(["message"=>"Tipo de administrador no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$tadmin,"message"=>"Tipo de administrador encontrado con éxito","code"=>200]);
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
            //     'Id_Tipo_Admin'=> 'required',
            //     'Nom_Tipo_Admin' => 'required'
            // ]); 
            DB::table('tipo_admin')
            ->where('Id_Tipo_Admin', $request->Id_Tipo_Admin)
            ->update(['Nom_Tipo_Admin' => $request->Nom_Tipo_Admin]);
            return response()->json(['data'=>[],"message"=>"Tipo de administrador actualizado con éxito","code"=>201]);
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
            return tipo_admin::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }   
    }
}
