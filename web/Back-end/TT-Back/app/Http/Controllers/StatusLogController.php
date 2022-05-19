<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\status_log;
use Illuminate\Support\Facades\DB;

class StatusLogController extends Controller
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
            // return $request;
            $validated = $request->validate([
                'Nom_Status_Log' => 'required'
            ]); 
            // return $validated;
            $status_log = new status_log();
            if ($status_log) {
                $status_log->Nom_Status_Log = $request->Nom_Status_Log;
                // return $status_log;
                $status_log->save();
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
        // return status_log::get();
        try { 
            $slog = status_log::where('Id_Status_Log', '=', $id)->get();
            if (count($slog) == 0) {
                return response()->json(["message"=>"Status no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$slog,"message"=>"Status encontrado con éxito","code"=>200]);
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
            //     'Id_Status_Log'=>'required',
            //     'Nom_Status_Log' => 'required'
            // ]); 
            DB::table('status_log')
            ->where('Id_Status_Log', $request->Id_Status_Log)
            ->update(['Nom_Status_Log' => $request->Nom_Status_Log]);
            return response()->json(['data'=>[],"message"=>"Status Log actualizado con éxito","code"=>201]);
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
            return status_log::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        } 
    }
}
