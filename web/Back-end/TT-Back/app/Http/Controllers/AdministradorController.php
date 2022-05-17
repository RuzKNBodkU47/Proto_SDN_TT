<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Http\Requests\GuardarAdministradorRequest;
use App\Models\administradores;
use App\Models\tipo_admin_cat_tareas;
use App\Models\status_admin;
use App\Models\tipo_admin;
use Illuminate\Support\Facades\DB;

class AdministradorController extends Controller
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
        $validated = $request->validate([
            'Id_Status_Admin'=>'required', 
            'Id_Tipo_Admin'=>'required', 
            'Nombre_Admin'=>'required',
            'Apellido_P_Admin'=>'required',
            'Apellido_M_Admin'=>'required',
            'Fecha_ingreso'=>'required',
            'Nombre_Usuario'=>'required', 
            'Password_Hash'=>'required', 
            'Fecha_Ultimo_Cambio_Pass'=>'required', 
            'Cant_dias_limit'=>'required'
        ]);
        $admin = new administradores();
        $admin->Id_Status_Admin = $request->Id_Status_Admin;
        $admin->Id_Tipo_Admin = $request->Id_Tipo_Admin;
        $admin->Nombre_Admin = $request->Nombre_Admin;
        $admin->Apellido_P_Admin = $request->Apellido_P_Admin;
        $admin->Apellido_M_Admin = $request->Apellido_M_Admin;
        $admin->Fecha_ingreso = date("Y-m-d H:i:s");
        $admin->Nombre_Usuario = $request->Nombre_Usuario;
        $admin->Password_Hash = bcrypt($request->Password_Hash);
        $admin->Fecha_Ultimo_Cambio_Pass = $request->Fecha_Ultimo_Cambio_Pass;
        $admin->Cant_dias_limit = $request->Cant_dias_limit;
        $admin->save();
        return response()->json(['data'=>[],"message"=>"Administrador regristrado con éxito","code"=>201]);
        
        //Funcion que permite hacer el registro de un paciente
        // administradores::create($request->all());
        // return response()->json([
        //     'res' => true,
        //     'msg' => 'Administrador guardado correctamente'
        // ]);
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
        try { 
            $admin = administradores::where('Id_Administradores', '=', $id)->get();
            if (count($admin) == 0) {
                return response()->json(["message"=>"Administrador no encontrado","code"=>404],404);
            }else {
                return response()->json(['data'=>$admin,"message"=>"Administrador encontrado con éxito","code"=>200]);
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
            $validated = $request->validate([
                'Id_Administradores'=>'required',
                'Id_Status_Admin'=>'required', 
                'Id_Tipo_Admin'=>'required', 
                'Nombre_Admin'=>'required',
                'Apellido_P_Admin'=>'required',
                'Apellido_M_Admin'=>'required',
                'Fecha_ingreso'=>'required',
                'Nombre_Usuario'=>'required', 
                'Password_Hash'=>'required', 
                'Fecha_Ultimo_Cambio_Pass'=>'required', 
                'Cant_dias_limit'=>'required'
            ]); 
            DB::table('administradores')
            ->where('Id_Administradores', $request->Id_Administradores)
            ->update([
                'Id_Status_Admin'=>$request->Id_Status_Admin, 
                'Id_Tipo_Admin'=>$request->Id_Tipo_Admin, 
                'Nombre_Admin'=>$request->Nombre_Admin,
                'Apellido_P_Admin'=>$request->Apellido_P_Admin,
                'Apellido_M_Admin'=>$request->Apellido_M_Admin,
                'Fecha_ingreso'=>$request->Fecha_ingreso,
                'Nombre_Usuario'=>$request->Nombre_Usuario, 
                'Password_Hash'=>$request->Password_Hash, 
                'Fecha_Ultimo_Cambio_Pass'=>$request->Fecha_Ultimo_Cambio_Pass, 
                'Cant_dias_limit'=>$request->Cant_dias_limit
            ]);
            return response()->json(['data'=>[],"message"=>"Administrador actualizado con éxito","code"=>201]);
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
            $admin=administradores::get();
            $adminconstatus['status']=[];
            $tipoadmin['tipo']=[];
            for ($i=0; $i < count($admin); $i++) { 
                $adminmas = status_admin::where('Id_Status_Admin', '=', $admin[$i]->Id_Status_Admin)->get();
                $tadmin = tipo_admin::where('Id_Tipo_Admin', '=', $admin[$i]->Id_Tipo_Admin)->get();
                // array_push($adminconstatus['status'], $adminmas);
                $admin[$i]->Id_Status_Admin=$adminmas;
                $admin[$i]->Id_Tipo_Admin=$tadmin;
            }
            // array_push($admin['status'], $adminconstatus);
            return $admin; 
            // return administradores::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
    public function adminwithtareas(Request $request){
        try {
            $admin = new administradores();
            $admin->Id_Status_Admin = $request->Id_Status_Admin;
            $admin->Id_Tipo_Admin = $request->Id_Tipo_Admin;
            $admin->Nombre_Admin = $request->Nombre_Admin;
            $admin->Apellido_P_Admin = $request->Apellido_P_Admin;
            $admin->Apellido_M_Admin = $request->Apellido_M_Admin;
            $admin->Fecha_ingreso = date("Y-m-d H:i:s");
            $admin->Nombre_Usuario = $request->Nombre_Usuario;
            // $admin->Password_Hash = bcrypt($request->Password_Hash);
            $admin->Password_Hash = $request->Password_Hash;
            $admin->Fecha_Ultimo_Cambio_Pass = $request->Fecha_Ultimo_Cambio_Pass;
            $admin->Cant_dias_limit = $request->Cant_dias_limit;
            $admin->save();
            $cadena = trim($request->Id_Cat_Tareas, '[]');
            // return str_replace(array("[", "]"), '', $request->Id_Cat_Tareas);
            $arreglo = explode(",", $cadena);
                for ($i=0; $i < count($arreglo); $i++) { 
                    $cattareasadmin = new tipo_admin_cat_tareas();
                    $cattareasadmin->Id_Administrador = $admin->id;
                    $cattareasadmin->Id_Cat_Tareas = $arreglo[$i];
                    $cattareasadmin->Fecha_Ult_Mod = $request->date("Y-m-d H:i:s");
                    // return $cattareasadmin;
                    $cattareasadmin->save();
                }
            return response()->json(['data'=>[],"message"=>"Administrador y tareas regristradas con éxito","code"=>201]);
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }
    }
    public function elimina(Request $request) {
        try {
            DB::table('administradores')
            ->where('Id_Administradores', $request->Id_Administradores)
            ->update([
                'Id_Status_Admin'=>$request->Id_Status_Admin, 
            ]);
            return response()->json(['data'=>[],"message"=>"Administrador eliminado con éxito","code"=>201]);
        } catch (\Throwable $th) {
            return response(["message"=>"error", 'error'=>$th],422);
        }
    }
}
