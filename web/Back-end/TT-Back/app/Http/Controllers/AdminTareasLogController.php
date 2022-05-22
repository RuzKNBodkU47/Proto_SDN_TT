<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\administradores_tareas_log;
use App\Models\cat_tareas;
use App\Models\status_log;
use Illuminate\Support\Facades\DB;

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
                'Id_Status_Log'=> 'required', 
                'Id_Administradores'=> 'required', 
                'Id_Cat_Tareas'=> 'required', 
                'Ip_Dispositivo_Orig'=> 'required', 
                'MAC_Dispositivo_Orig'=> 'required', 
                'Id_Admin_Obj'=> 'required', 
                'Fecha_Init_Serv'=> 'required',
                'Fecha_Fin_Serv'=> 'required'
            ]); 
            // return $validated;
            $admintareaslog = new administradores_tareas_log();
            if ($admintareaslog) {
                $admintareaslog->Id_Status_Log = $request->Id_Status_Log;
                $admintareaslog->Id_Administradores = $request->Id_Administradores;
                $admintareaslog->Id_Cat_Tareas = $request->Id_Cat_Tareas;
                $admintareaslog->Ip_Dispositivo_Orig = $request->Ip_Dispositivo_Orig;
                $admintareaslog->MAC_Dispositivo_Orig = $request->MAC_Dispositivo_Orig;
                $admintareaslog->Id_Admin_Obj = $request->Id_Admin_Obj;
                $admintareaslog->Fecha_Init_Serv = $request->Fecha_Init_Serv;
                $admintareaslog->Fecha_Fin_Serv = $request->Fecha_Fin_Serv;
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
        // return administradores_tareas_log::get();
        try { 
            $admintareaslog = administradores_tareas_log::where('Id_Administradores_Tareas_Log', '=', $id)->get();
            if (count($admintareaslog) == 0) {
                return response()->json(["message"=>"Log de la tarea del administrador no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$admintareaslog,"message"=>"Log de la tarea del administrador encontrado con éxito","code"=>200]);
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
            //     'Id_Administradores_Tareas_Log'=> 'required',
            //     'Id_Status_Log'=> 'required', 
            //     'Id_Administradores'=> 'required', 
            //     'Id_Cat_Tareas'=> 'required', 
            //     'Ip_Dispositivo_Orig'=> 'required', 
            //     'MAC_Dispositivo_Orig'=> 'required', 
            //     'Id_Admin_Obj'=> 'required', 
            //     'Fecha_Init_Serv'=> 'required',
            //     'Fecha_Fin_Serv'=> 'required'
            // ]); 
            DB::table('administradores_tareas_log')
            ->where('Id_Administradores_Tareas_Log', $request->Id_Administradores_Tareas_Log)
            ->update([
                'Id_Status_Log'=>$request->Id_Status_Log,
                'Id_Administradores'=>$request->Id_Administradores,
                'Id_Cat_Tareas'=>$request->Id_Cat_Tareas,
                'Ip_Dispositivo_Orig'=>$request->Ip_Dispositivo_Orig,
                'MAC_Dispositivo_Orig'=>$request->MAC_Dispositivo_Orig,
                'Id_Admin_Obj'=>$request->Id_Admin_Obj,
                'Fecha_Init_Serv'=>$request->Fecha_Init_Serv,
                'Fecha_Fin_Serv'=>$request->Fecha_Fin_Serv
            ]);
            return response()->json(['data'=>[],"message"=>"Log del administrador de tareas actualizado con éxito","code"=>201]);
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
            $admin=administradores_tareas_log::get();
            // return administradores_tareas_log::get();
            for ($i=0; $i < count($admin); $i++) { 
                $tarea = cat_tareas::where('Id_Cat_Tareas', '=', $admin[$i]->Id_Cat_Tareas)->get();
                $status = status_log::where('Id_Status_Log', '=', $admin[$i]->Id_Status_Log)->get();
                $admin[$i]->Id_Cat_Tareas=$tarea;
                $admin[$i]->Id_Status_Log=$status;
            }
            return $admin;
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
}
