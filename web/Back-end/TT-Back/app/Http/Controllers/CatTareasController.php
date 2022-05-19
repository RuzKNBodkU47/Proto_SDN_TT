<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\cat_tareas;
use Illuminate\Support\Facades\DB;

class CatTareasController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        //
        return cat_tareas::get();
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
                'Nom_Cat_Tareas' => 'required'
                // 'fecha_insercion' => 'required',
                // 'fecha_ult_mod' => 'required'
            ]); 
            // return $validated;
            $cattarea = new cat_tareas();
            if ($cattarea) {
                $cattarea->Nom_Cat_Tareas = $request->Nom_Cat_Tareas;
                // $cattarea->fecha_insercion = date("Y-m-d H:i:s");
                // $cattarea->fecha_ult_mod = date("Y-m-d H:i:s");
                // return $cattarea;
                $cattarea->save();
                return response()->json(['data'=>[],"message"=>"Tarea en catálogo regristrada con éxito","code"=>201]);    
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
        // return cat_tareas::get();
        try { 
            $ctarea = cat_tareas::where('Id_Cat_Tareas', '=', $id)->get();
            if (count($ctarea) == 0) {
                return response()->json(["message"=>"Tarea en catalogo no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$ctarea,"message"=>"Tarea en catalogo encontrado con éxito","code"=>200]);
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
            //     'Id_Cat_Tareas'=> 'required',
            //     'Nom_Cat_Tareas'=> 'required',
            // ]); 
            DB::table('cat_tareas')
            ->where('Id_Cat_Tareas', $request->Id_Cat_Tareas)
            ->update([
                'Nom_Cat_Tareas'=>$request->Nom_Cat_Tareas,
            ]);
            return response()->json(['data'=>[],"message"=>"Catalogo de tareas actualizado con éxito","code"=>201]);
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
            return cat_tareas::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
}
