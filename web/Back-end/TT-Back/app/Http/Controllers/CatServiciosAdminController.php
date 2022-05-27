<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\tipo_admin_cat_servicios;
use App\Models\administradores_tareas_log;
use Illuminate\Support\Facades\DB;

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
                'Id_Administrador'=> 'required',
                'Id_Cat_Servicios'=> 'required',
                'Fecha_Ult_Mod'=> 'required'
            ]); 
            // return $validated;
            $catservicioadmin = new tipo_admin_cat_servicios();
            if ($catservicioadmin) {
                $catservicioadmin->Id_Administrador = $request->Id_Administrador;
                $catservicioadmin->Id_Cat_Servicios = $request->Id_Cat_Servicios;
                $catservicioadmin->Fecha_Ult_Mod = $request->Fecha_Ult_Mod;
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
        // return tipo_admin_cat_servicios::get();
        try { 
            $cservicioadmin = tipo_admin_cat_servicios::where('Id_Tipo_Admin_Servicios', '=', $id)->get();
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
    public function update(Request $request)
    {
        //
        try {
            // $validated = $request->validate([
            //     'Id_Tipo_Admin_Servicios'=> 'required',
            //     'Id_Administrador'=> 'required',
            //     'Id_Cat_Servicios'=> 'required',
            //     'Fecha_Ult_Mod'=> 'required'
            // ]); 
            DB::table('tipo_admin_cat_servicios')
            ->where('Id_Tipo_Admin_Servicios', $request->Id_Tipo_Admin_Servicios)
            ->update([
                'Id_Tipo_Admin_Servicios'=>$request->Id_Tipo_Admin_Servicios,
                'Id_Administrador'=>$request->Id_Administrador,
                'Id_Cat_Servicios'=>$request->Id_Cat_Servicios,
                'Fecha_Ult_Mod'=>$request->Fecha_Ult_Mod
            ]);
            return response()->json(['data'=>[],"message"=>"Catalogo de servicios administrador actualizado con éxito","code"=>201]);
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
            return tipo_admin_cat_servicios::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
    public function buscaservicio($id)
    {
        //
        // return tipo_admin_cat_tareas::get();
        try {
            $ctareaadmin = tipo_admin_cat_servicios::where('Id_Administrador', '=', $id)->get();
            $global['admins']=[];
            for ($i=0; $i <count($ctareaadmin); $i++) {
                $datos['tareaenadmin']=$ctareaadmin[$i]->Id_Cat_Servicios;
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
    public function agregarservicio(Request $request) {
        try {
            $lista['servicioi']=[];
            // $lista['tareasd']=[];
            // $lista['tareasinsert']=[];
            $ctareaadmin = tipo_admin_cat_servicios::where('Id_Administrador', '=', $request->Id_Administrador)->get();
            $listainsert = str_split($request->lista_insert);
            for ($i=0; $i < count($listainsert); $i++) {
                if ($listainsert[$i]!="[" && $listainsert[$i]!="]" && $listainsert[$i]!=",") {
                    array_push($lista['servicioi'],$listainsert[$i]);
                }
            }
            for ($i=0; $i < count($ctareaadmin); $i++) {
                tipo_admin_cat_servicios::where('Id_Administrador', $ctareaadmin[$i]->Id_Administrador)->forceDelete();
            }
            for ($i=0; $i < count($lista['servicioi']); $i++) {
                $catservicioadmin = new tipo_admin_cat_servicios();
                $catservicioadmin->Id_Administrador = (int)$request->Id_Administrador;
                $catservicioadmin->Id_Cat_Servicios = (int)$lista['servicioi'][$i];
                $catservicioadmin->Fecha_Ult_Mod = date("Y-m-d H:i:s"); 
                $catservicioadmin->save();
            }
            $admintareaslog = new administradores_tareas_log();
            $admintareaslog->Id_Status_Log = 3;
            $admintareaslog->Id_Administradores = $request->id;
            $admintareaslog->Id_Cat_Tareas = 5;
            $admintareaslog->Ip_Dispositivo_Orig = \Request::ip();
            $admintareaslog->MAC_Dispositivo_Orig = 'Inalcanzable';
            $admintareaslog->Id_Admin_Obj = null;
            $admintareaslog->Fecha_Init_Serv = date("Y-m-d H:i:s");
            $admintareaslog->Fecha_Fin_Serv = date("Y-m-d H:i:s");
            $admintareaslog->save();
            return response()->json(['data'=>$lista['servicioi'],"message"=>"Lista de tareas actualizada con éxito","code"=>201]);
        } catch (\Throwable $th) {
            return \Response::json(['find' => false,"message"=>$th], 404);
        }
    }
}