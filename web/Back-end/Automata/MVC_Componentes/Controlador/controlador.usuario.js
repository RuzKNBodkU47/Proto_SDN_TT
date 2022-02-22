//Importar modulos
const modeloUsuarios = require("../Modelo/modelo.usuarios");
const jwt = require('jsonwebtoken');

//Exportar modulos
module.exports.createUsers = async (user) => {
    let newUser = [
        user.idAdmin,
        user.idStatusAdmin,
        user.idTipoAdmin,
        user.nombresAdmin,
        user.apellidoPAdmin,
        user.apellidoMAdmin,
        user.fechaIngreso,
        user.nombreUsuario,
        user.passwordHash
    ]
    try{
        let resultadoCreacion = await modeloUsuarios.NuevoUsuario(newUser);
        if(resultadoCreacion){
            return 'Alta de usuario correcta'
        }else{
            throw new Error('Error en la creación de usuario o el usuario ya existe');
        }
    }catch(err){
        console.log(err);
        throw new Error('Error en la creación del usuario')
    }
}

module.exports.generateToken = async (data) => {
    const token = jwt.sign({
        data}, process.env.SECRET_KEY
        )//Tiempo maximo de validez de 15 minutos para el token
    return token;
}

//Verificacion de usuario
module.exports.VerifyUser = async (token) => {
    const resultVerificacion = jwt.verify(token, process.env.SECRET_KEY);

    if(resultado){
        return resultado;
    }else{
        throw new Error('Token no válido');
    }

}