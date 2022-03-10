<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\tipo_admin;

class TipoAdminController extends Controller
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
            //code...
            $tipoadmins = new tipo_admin();
            $tipoadmins->nom_tipo_admin = $request->nom_tipo_admin;
            // return $tipoadmins;
            $tipoadmins->save();
            return response()->json(['data'=>[],"message"=>"Nombre del tipo de administrador regristrado con éxito","code"=>201]);
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
    public function showall(){
        try {
            return tipo_admin::get();
        } catch (\Throwable $th) {
            return \Response::json(['created' => false,"message"=>$th], 422);
        }   
    }
}
