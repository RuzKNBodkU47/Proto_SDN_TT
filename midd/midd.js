//Importar modulos necesarios
const rateLimit =  require('express-rate-limit');
const ControladorUsuario = require('../web/Back-end/Automata/MVC_Componentes/Controlador/controlador.usuario')
const ControladorComponente = require('../web/Back-end/Automata/MVC_Componentes/Controlador/controlador.componente')
//Middleware

//Limitar el uso de la API
module.exports.theLimit = rateLimit({
    windowsMS: 30 * 60 * 1000, //30 minutos de uso
    max: 1000, //10 peticiones por ventana
    message: "Usted ha excedido los límites de la API"
});

module.exports.ComponenteValido = async(req,res,next) => {
    try{
        if(req == 'router'){
            let validComponent = await ControladorComponente.readFile('Router.json');
        }else if(req == 'switch'){
            let validComponent = await ControladorComponente.readFile('Switch.json');
        }else if(req == 'switch multicapa'){
            let validComponent = await ControladorComponente.readFile('SwitchMulticapa.json');
        }else if(req == 'server'){
            let validComponent = await ControladorComponente.readFile('Server.json');
        }else if(req == 'conexion'){
            let validComponent = await ControladorComponente.readFile('Conexion.json');
        }else{
            throw new Error ('El componente ingresado no es uno valido dentro del sistema')
        }
    }catch(err){
        console.log(err.message);
        res.status(500).json({error: err.message})
    }
}

module.exports.UsuarioValido = async (req, res, next) => {
    try{
        if(req.headers.authorizartion != undefined){
            const token = req.headers.authorizartion.split(' ')[1]
            let verificado = await ControladorUsuario.VerifyUser(token);
            console.log(verificado);
            req.params.usuario = verificado.data
            return next()
        }else{
            throw new Error ('El sistema requiere autorización forzosamente para su acceso');
        }
    }catch(err){
        console.log(err.message);
        res.status(500).json({error: err.message})
    }
}