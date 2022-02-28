<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Http\Requests\GuardarAdministradorRequest;
use App\Models\administradores;

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
        // $validated = $request->validate([
        //     'nombre_administrador' => 'required',
        //     'apellido_p_administrador' => 'required',
        //     'apellido_m_administrador' => 'required',
        //     'nombre_usuario' => 'required',
        //     'password_hash' => 'required',
        //     // 'id_status_admin' => 'required',
        //     // 'id_tipo_admin' => 'required'
        // ]);
        $admin = new administradores();
        $admin->nombre_administrador = $request->nombre_administrador;
        $admin->apellido_p_administrador = $request->apellido_p_administrador;
        $admin->apellido_m_administrador = $request->apellido_m_administrador;
        $admin->nombre_usuario = $request->nombre_usuario;
        $admin->password_hash = bcrypt($request->password_hash);
        $admin->fecha_ingreso = date("Y-m-d H:i:s");
        $admin->fecha_ult_cambio_pass = $request->fecha_ult_cambio_pass;
        $admin->id_status_admin = $request->id_status_admin;
        $admin->id_tipo_admin = $request->id_tipo_admin;
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
    public function update(Request $request, $id)
    {
        //
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

    public function prueba(){
        return administradores::all();
    }
}
