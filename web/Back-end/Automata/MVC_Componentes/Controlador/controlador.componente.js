//Importamos modulos
const modeloComponentes = require('../Modelo/modelo.componentes');
const fs = require('fs')

//Exportar modulos
module.exports.ReadFile = async (filename) =>{
    let rawdata = fs.readFileSync(filename);
    let component = JSON.parse(rawdata);
}