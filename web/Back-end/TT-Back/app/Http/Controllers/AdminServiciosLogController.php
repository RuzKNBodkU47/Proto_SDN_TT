<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\administradores_servicios_log;
use App\Models\cat_servicios;
use App\Models\status_log;
use Illuminate\Support\Facades\DB;

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
                'Id_Status_Log' => 'required',
                'Id_Administradores' => 'required',
                'Id_Cat_Servicios' => 'required',
                'Ip_Dispositivo_Orig'=>'required',
                'MAC_Dispositivo_Orig'=>'required',
                'Ip_Dispositivo_Ant' => 'required',
                'Ip_Dispositivo_Desp' => 'required',
                'Dir_MAC_Disp_Fin' => 'required',
                'Fecha_Init_Serv' => 'required',
                'Fecha_Fin_Serv' => 'required',
            ]); 
            // return $validated;
            $adminserviciolog = new administradores_servicios_log();
            if ($adminserviciolog) {
                $adminserviciolog->Id_Status_Log = $request->Id_Status_Log;
                $adminserviciolog->Id_Administradores = $request->Id_Administradores;
                $adminserviciolog->Id_Cat_Servicios = $request->Id_Cat_Servicios;
                $adminserviciolog->Ip_Dispositivo_Orig = $request->Ip_Dispositivo_Orig;
                $adminserviciolog->MAC_Dispositivo_Orig = $request->MAC_Dispositivo_Orig;
                $adminserviciolog->Ip_Dispositivo_Ant = $request->Ip_Dispositivo_Ant;
                $adminserviciolog->Ip_Dispositivo_Desp = $request->Ip_Dispositivo_Desp;
                $adminserviciolog->Dir_MAC_Disp_Fin = $request->Dir_MAC_Disp_Fin;
                $adminserviciolog->Fecha_Init_Serv = $request->Fecha_Init_Serv;
                $adminserviciolog->Fecha_Fin_Serv = $request->Fecha_Fin_Serv;
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
        // return administradores_servicios_log::get();
        try { 
            $adminservlog = administradores_servicios_log::where('Id_Administradores_Servicios_Log', '=', $id)->get();
            if (count($adminservlog) == 0) {
                return response()->json(["message"=>"Log del servicio del administrador no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$adminservlog,"message"=>"Log del servicio del administrador encontrado con éxito","code"=>200]);
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
            //     'Id_Administradores_Servicios_Log'=> 'required',
            //     'Id_Status_Log' => 'required',
            //     'Id_Administradores' => 'required',
            //     'Id_Cat_Servicios' => 'required',
            //     'Ip_Dispositivo_Orig'=>'required',
            //     'MAC_Dispositivo_Orig'=>'required',
            //     'Ip_Dispositivo_Ant' => 'required',
            //     'Ip_Dispositivo_Desp' => 'required',
            //     'Dir_MAC_Disp_Fin' => 'required',
            //     'Fecha_Init_Serv' => 'required',
            //     'Fecha_Fin_Serv' => 'required',
            // ]); 
            DB::table('administradores_servicios_log')
            ->where('Id_Administradores_Servicios_Log', $request->Id_Administradores_Servicios_Log)
            ->update([
                'Id_Status_Log'=>$request->Id_Status_Log,
                'Id_Administradores'=>$request->Id_Administradores,
                'Id_Cat_Servicios'=>$request->Id_Cat_Servicios,
                'Ip_Dispositivo_Orig'=>$request->Ip_Dispositivo_Orig,
                'MAC_Dispositivo_Orig'=>$request->MAC_Dispositivo_Orig,
                'Ip_Dispositivo_Ant'=>$request->Ip_Dispositivo_Ant,
                'Ip_Dispositivo_Desp'=>$request->Ip_Dispositivo_Desp,
                'Dir_MAC_Disp_Fin'=>$request->Dir_MAC_Disp_Fin,
                'Fecha_Init_Serv'=>$request->Fecha_Init_Serv,
                'Fecha_Fin_Serv'=>$request->Fecha_Fin_Serv
            ]);
            return response()->json(['data'=>[],"message"=>"Log del administrador de servicio actualizado con éxito","code"=>201]);
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
            $admin=administradores_servicios_log::get();
            for ($i=0; $i < count($admin); $i++) { 
                $serv = cat_servicios::where('Id_Cat_Servicios', '=', $admin[$i]->Id_Cat_Servicios)->get();
                $status = status_log::where('Id_Status_Log', '=', $admin[$i]->Id_Status_Log)->get();
                $admin[$i]->Id_Cat_Servicios=$serv;
                $admin[$i]->Id_Status_Log=$status;
            }
            return $admin;
            // return administradores_servicios_log::get(); //Así lo tenía originalmente
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
}
