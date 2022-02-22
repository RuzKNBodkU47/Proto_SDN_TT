<?php

namespace App\Http\Requests;

use Illuminate\Foundation\Http\FormRequest;

class GuardarAdministradorRequest extends FormRequest
{
    /**
     * Determine if the user is authorized to make this request.
     *
     * @return bool
     */
    public function authorize()
    {
        return true;
    }

    /**
     * Get the validation rules that apply to the request.
     *
     * @return array
     */
    public function rules()
    {
        // return [
        //     //Aqui se guardan todas aquellas reglas que queremos hacer validas para guardar un administrador
        //     "nombre_administrador" => "require",
        //     "apellido_p_administrador" => "require", 
        //     "apellido_m_administrador" => "require",
        //     "nombre_usuario" => "require", 
        //     "password_hash" => "require"
        // ];
    }
}
