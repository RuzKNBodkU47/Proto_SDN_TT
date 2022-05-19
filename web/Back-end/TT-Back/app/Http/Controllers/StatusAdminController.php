<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\status_admin;
use Illuminate\Support\Facades\DB;

class StatusAdminController extends Controller
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
            $validated = $request->validate([
                'Nom_Tipo_Admin' => 'required'
            ]); 
            $admins = new status_admin();
            if ($admins) {
                $admins->Nom_Tipo_Admin = $request->Nom_Tipo_Admin;
                // return $admins;
                $admins->save();
                return response()->json(['data'=>[],"message"=>"Nombre del administrador regristrado con éxito","code"=>201]);    
                # code...
            }else{
                return response()->json(['data'=>[],"message"=>"No se agregó nombre","code"=>403]);
            }
            //code...
        } catch (\Throwable $th) {
            //throw $th;
            return \Response::json(['created' => false,"message"=>$th->status], 422);
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
        // return status_admin::get();
        try { 
            $sadmin = status_admin::where('Id_Status_Admin', '=', $id)->get();
            if (count($sadmin) == 0) {
                return response()->json(["message"=>"Status del administrador no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$sadmin,"message"=>"Status del administrador encontrado con éxito","code"=>200]);
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
            //     'Id_Status_Admin'=>'required',
            //     'Nom_Tipo_Admin' => 'required'
            // ]); 
            DB::table('status_admin')
            ->where('Id_Status_Admin', $request->Id_Status_Admin)
            ->update(['Nom_Tipo_Admin' => $request->Nom_Tipo_Admin]);
            return response()->json(['data'=>[],"message"=>"Status del administrador actualizado con éxito","code"=>201]);
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
            return status_admin::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        } 
    }
}
