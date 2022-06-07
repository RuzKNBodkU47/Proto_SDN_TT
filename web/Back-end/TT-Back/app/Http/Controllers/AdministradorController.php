<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Http\Requests\GuardarAdministradorRequest;
use App\Models\administradores;
use App\Models\tipo_admin_cat_tareas;
use App\Models\tipo_admin_cat_servicios;
use App\Models\status_admin;
use App\Models\tipo_admin;
use App\Models\administradores_tareas_log;
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
            // $validated = $request->validate([
            //     'Id_Administradores'=>'required',
            //     'Id_Status_Admin'=>'required', 
            //     'Id_Tipo_Admin'=>'required', 
            //     'Nombre_Admin'=>'required',
            //     'Apellido_P_Admin'=>'required',
            //     'Apellido_M_Admin'=>'required',
            //     'Fecha_ingreso'=>'required',
            //     'Nombre_Usuario'=>'required', 
            //     'Password_Hash'=>'required', 
            //     'Fecha_Ultimo_Cambio_Pass'=>'required', 
            //     'Cant_dias_limit'=>'required'
            // ]); 
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
            if ($request->Id_Status_Admin==3) {
                $admintareaslog = new administradores_tareas_log();
                $admintareaslog->Id_Status_Log = 3;
                $admintareaslog->Id_Administradores = $request->id;
                $admintareaslog->Id_Cat_Tareas = 6;
                $admintareaslog->Ip_Dispositivo_Orig = \Request::ip();
                $admintareaslog->MAC_Dispositivo_Orig = 'Inalcanzable';
                $admintareaslog->Id_Admin_Obj = null;
                $admintareaslog->Fecha_Init_Serv = date("Y-m-d H:i:s");
                $admintareaslog->Fecha_Fin_Serv = date("Y-m-d H:i:s");
                $admintareaslog->save();
                return response()->json(['data'=>[],"message"=>"Administrador eliminado con éxito","code"=>201]);
            }else{
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
                return response()->json(['data'=>[],"message"=>"Administrador eliminado con éxito","code"=>201]);
            }
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
            if ($request->Servicios) {
                $cadena = trim($request->Servicios, '[]');
                // return str_replace(array("[", "]"), '', $request->Id_Cat_Tareas);
                $arreglo = explode(",", $cadena);
                    for ($i=0; $i < count($arreglo); $i++) { 
                        $cattareasadmin = new tipo_admin_cat_servicios();
                        $cattareasadmin->Id_Administrador = $admin->Id_Administradores;
                        $cattareasadmin->Id_Cat_Servicios = $arreglo[$i];
                        $cattareasadmin->Fecha_Ult_Mod = date("Y-m-d H:i:s");
                        // return $cattareasadmin;
                        $cattareasadmin->save();
                    }
            }
            if ($request->Tareas) {
                $cadena2 = trim($request->Tareas, '[]');
                // return str_replace(array("[", "]"), '', $request->Id_Cat_Tareas);
                $arreglo = explode(",", $cadena2);
                    for ($i=0; $i < count($arreglo); $i++) { 
                        $cattareasadmin = new tipo_admin_cat_tareas();
                        $cattareasadmin->Id_Administrador = $admin->Id_Administradores;
                        $cattareasadmin->Id_Cat_Tareas = $arreglo[$i];
                        $cattareasadmin->Fecha_Ult_Mod = date("Y-m-d H:i:s");
                        // return $cattareasadmin;
                        $cattareasadmin->save();
                    }
            }
            $admintareaslog = new administradores_tareas_log();
            $admintareaslog->Id_Status_Log = 3;
            $admintareaslog->Id_Administradores = $request->id;
            $admintareaslog->Id_Cat_Tareas = 4;
            $admintareaslog->Ip_Dispositivo_Orig = \Request::ip();
            $admintareaslog->MAC_Dispositivo_Orig = 'Inalcanzable';
            $admintareaslog->Id_Admin_Obj = null;
            $admintareaslog->Fecha_Init_Serv = date("Y-m-d H:i:s");
            $admintareaslog->Fecha_Fin_Serv = date("Y-m-d H:i:s");
            $admintareaslog->save();
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
            if ($request->Id_Status_Admin==3) {
                $admintareaslog = new administradores_tareas_log();
                $admintareaslog->Id_Status_Log = 3;
                $admintareaslog->Id_Administradores = $request->id;
                $admintareaslog->Id_Cat_Tareas = 6;
                $admintareaslog->Ip_Dispositivo_Orig = \Request::ip();
                $admintareaslog->MAC_Dispositivo_Orig = 'Inalcanzable';
                $admintareaslog->Id_Admin_Obj = null;
                $admintareaslog->Fecha_Init_Serv = date("Y-m-d H:i:s");
                $admintareaslog->Fecha_Fin_Serv = date("Y-m-d H:i:s");
                $admintareaslog->save();
                return response()->json(['data'=>[],"message"=>"Administrador eliminado con éxito","code"=>201]);
            }else{
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
                return response()->json(['data'=>[],"message"=>"Administrador eliminado con éxito","code"=>201]);
            }
        } catch (\Throwable $th) {
            return response(["message"=>"error", 'error'=>$th],422);
        }
    }
    public function login(Request $request) {
        $user = administradores::where('Nombre_Usuario',$request->Nombre_Usuario)->first();
        if (isset($user->Id_Administradores)) {
            // if(Hash::check($request->Password,$user->Password_Hash)){
            if (strcmp($request->Password,$user->Password_Hash)==0) {
                if ($user->Id_Status_Admin==1||$user->Id_Status_Admin==2) {
                    $admintareaslog = new administradores_tareas_log();
                    $admintareaslog->Id_Status_Log = 3;
                    $admintareaslog->Id_Administradores = $user->Id_Administradores;
                    $admintareaslog->Id_Cat_Tareas = 1;
                    $admintareaslog->Ip_Dispositivo_Orig = \Request::ip();
                    $admintareaslog->MAC_Dispositivo_Orig = 'Inalcanzable';
                    $admintareaslog->Id_Admin_Obj = null;
                    $admintareaslog->Fecha_Init_Serv = date("Y-m-d H:i:s");
                    $admintareaslog->Fecha_Fin_Serv = date("Y-m-d H:i:s");
                    $admintareaslog->save();
                    DB::table('administradores')
                    ->where('Id_Administradores', $user->Id_Administradores)
                    ->update([
                        'Id_Status_Admin'=>1, 
                    ]);
                    return response(["message"=>"Usuario ingresado con éxito",'code'=>201, 'data'=>$user]);
                }else {
                    return response(["message"=>"Usuario no cuenta con permisos para poder ingresar", 'code'=>403]);
                }
            }else {
                return response(["message"=>"Contraseña incorrecta", 'code'=>403]);
            }
        }else {
            return response(["message"=>"Usuario no registrado", 'code'=>404]);
        }
    }
    public function logout(Request $request) {
        $user = administradores::where('Id_Administradores',$request->id)->first();
        if (isset($user->Id_Administradores)) {
            $admintareaslog = new administradores_tareas_log();
            $admintareaslog->Id_Status_Log = 3;
            $admintareaslog->Id_Administradores = $user->Id_Administradores;
            $admintareaslog->Id_Cat_Tareas = 2;
            $admintareaslog->Ip_Dispositivo_Orig = \Request::ip();
            $admintareaslog->MAC_Dispositivo_Orig = 'Inalcanzable';
            $admintareaslog->Id_Admin_Obj = null;
            $admintareaslog->Fecha_Init_Serv = date("Y-m-d H:i:s");
            $admintareaslog->Fecha_Fin_Serv = date("Y-m-d H:i:s");
            $admintareaslog->save();
            DB::table('administradores')
            ->where('Id_Administradores', $user->Id_Administradores)
            ->update([
                'Id_Status_Admin'=>2, 
            ]);
            return response(["message"=>"Logout",'code'=>201, 'data'=>[]]);
        }else {
            return response(["message"=>"Usuario no registrado", 'code'=>404]);
        }
    }
    public function obtenermac(){
        $macAddr = exec('getmac');
        if(isset($macAddr)){
            return $macAddr;
        }else {
            return 'unattainable';
        }
    }
    public function cambiapass(Request $request){
        
        //
        try {
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
            $admintareaslog = new administradores_tareas_log();
            $admintareaslog->Id_Status_Log = 3;
            $admintareaslog->Id_Administradores = $request->id;
            $admintareaslog->Id_Cat_Tareas = 3;
            $admintareaslog->Ip_Dispositivo_Orig = \Request::ip();
            $admintareaslog->MAC_Dispositivo_Orig = 'Inalcanzable';
            $admintareaslog->Id_Admin_Obj = null;
            $admintareaslog->Fecha_Init_Serv = date("Y-m-d H:i:s");
            $admintareaslog->Fecha_Fin_Serv = date("Y-m-d H:i:s");
            $admintareaslog->save();
            return response()->json(['data'=>[],"message"=>"Administrador actualizado con éxito","code"=>201]);
        } catch (\Throwable $th) {
            return response(["message"=>"error", 'error'=>$th],422);
        }
    }
}