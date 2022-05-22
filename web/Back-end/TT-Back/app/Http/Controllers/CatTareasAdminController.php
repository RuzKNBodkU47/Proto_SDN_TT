<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\tipo_admin_cat_tareas;
use Illuminate\Support\Facades\DB;

class CatTareasAdminController extends Controller
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
                'Id_Administrador'=> 'required',
                'Id_Cat_Tareas'=> 'required',
                'Fecha_Ult_Mod'=> 'required'
            ]); 
            // return $validated;
            $cattareasadmin = new tipo_admin_cat_tareas();
            if ($cattareasadmin) {
                $cattareasadmin->Id_Administrador = $request->Id_Administrador;
                $cattareasadmin->Id_Cat_Tareas = $request->Id_Cat_Tareas;
                $cattareasadmin->Fecha_Ult_Mod = $request->Fecha_Ult_Mod;
                // return $cattareasadmin;
                $cattareasadmin->save();
                return response()->json(['data'=>[],"message"=>"Tarea en catálogo regristrada con éxito","code"=>201]);    
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
        // return tipo_admin_cat_tareas::get();
        try { 
            $ctareaadmin = tipo_admin_cat_tareas::where('Id_Tipo_Admin_Tareas', '=', $id)->get();
            if (count($ctareaadmin) == 0) {
                return response()->json(["message"=>"Tarea en catalogo de administrador no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$ctareaadmin,"message"=>"Tarea en catalogo de administrador encontrado con éxito","code"=>200]);
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
            //     'Id_Tipo_Admin_Tareas'=> 'required',
            //     'Id_Administrador'=> 'required',
            //     'Id_Cat_Tareas'=> 'required',
            //     'Fecha_Ult_Mod'=> 'required'
            // ]); 
            DB::table('tipo_admin_cat_tareas')
            ->where('Id_Tipo_Admin_Tareas', $request->Id_Tipo_Admin_Tareas)
            ->update([
                'Id_Administrador'=>$request->Id_Administrador,
                'Id_Cat_Tareas'=>$request->Id_Cat_Tareas,
                'Fecha_Ult_Mod'=>$request->Fecha_Ult_Mod
            ]);
            return response()->json(['data'=>[],"message"=>"Catalogo de tareas del aministrador actualizado con éxito","code"=>201]);
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
            return tipo_admin_cat_tareas::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
    public function buscatarea($id)
    {
        //
        // return tipo_admin_cat_tareas::get();
        try {
            $ctareaadmin = tipo_admin_cat_tareas::where('Id_Administrador', '=', $id)->get();
            $global['admins']=[];
            for ($i=0; $i <count($ctareaadmin); $i++) {
                $datos['tareaenadmin']=$ctareaadmin[$i]->Id_Cat_Tareas;
                array_push($global['admins'],$datos);
            }
            return $global;
            // if (count($ctareaadmin) == 0) {
            //     return response()->json(["message"=>"Tarea en catalogo de administrador no encontrado","code"=>404],404);
            // }else {
            //     return response()->json(['data'=>$ctareaadmin,"message"=>"Tarea en catalogo de administrador encontrado con éxito","code"=>200]);
            // }
        } catch (\Throwable $th) {
            return \Response::json(['find' => false,"message"=>$th], 404);
        }
    }
    public function agregartarea(Request $request) {
        try {
            $lista['tareasi']=[];
            $lista['tareasd']=[];
            $lista['tareasinsert']=[];
            $ctareaadmin = tipo_admin_cat_tareas::where('Id_Administrador', '=', $request->Id_Administrador)->get();
            $listainsert = str_split($request->lista_insert);
            for ($i=0; $i < count($listainsert); $i++) {
                if ($listainsert[$i]!="[" && $listainsert[$i]!="]" && $listainsert[$i]!=",") {
                    array_push($lista['tareasi'],$listainsert[$i]);
                }
            }
            for ($i=0; $i < count($ctareaadmin); $i++) {
                tipo_admin_cat_tareas::where('Id_Administrador', $ctareaadmin[$i]->Id_Administrador)->forceDelete();
            }
            for ($i=0; $i < count($lista['tareasi']); $i++) {
                $cattareasadmin = new tipo_admin_cat_tareas();
                $cattareasadmin->Id_Administrador = (int)$request->Id_Administrador;
                $cattareasadmin->Id_Cat_Tareas = (int)$lista['tareasi'][$i];
                $cattareasadmin->save();
            }
            return response()->json(['data'=>$lista['tareasi'],"message"=>"Lista de tareas actualizada con éxito","code"=>201]);
        } catch (\Throwable $th) {
            return \Response::json(['find' => false,"message"=>$th], 404);
        }
    }
}
