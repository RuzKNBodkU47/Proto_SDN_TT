<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\datos_dispo;

class DatosDispoController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        //
        try { 
            $admin = $dispositivo = datos_dispo::get();
            if (count($admin) == 0) {
                return response()->json(["message"=>"Dispositivos no encontrados","code"=>404]);
            }else {
                $global['dispositivos']=[];
                for ($i=0; $i <count($admin); $i++) {
                    $datos['idSolicitud']=$admin[$i]->idSolicitud;
                    $datos['NombreDispo']=$admin[$i]->NombreDispo;
                    $datos['IPDispositivo']=$admin[$i]->IPDispositivo;
                    $datos['OIDConsultado']=$admin[$i]->OIDConsultado;
                    $datos['Memoria']=$admin[$i]->Memoria;
                    $datos['CPU']=$admin[$i]->CPU;
                    $datos['AnchoB']=$admin[$i]->AnchoB;
                    $datos['Storage']=$admin[$i]->Storage;
                    array_push($global['dispositivos'],$datos);
                }
                return response()->json(['data'=>$global['dispositivos'],"message"=>"Dispositivos encontrados con éxito","code"=>200]);
            }
        } catch (\Throwable $th) {
            return \Response::json(['find' => false,"message"=>$th], 404);
        }
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
}
