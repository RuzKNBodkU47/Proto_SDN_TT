//Definicion de tamaños, en que se van a mapear los objetos
const fs = require(fs)

class Arbol{
    constructor(){
        this.root = null;
    }
}


class CrearNodo{
    constructor(tipo_comp){
        //Tipo de componente = router, servidor, switch, switch multicapa, conexión
        this.tipo_comp = tipo_comp;
    }
    
    AlmacenarComp = () => {
        console.log(this.tipo_comp);
        
        //Evalua el tipo de componente que se esta creando para almacenar su respectiva información
    
        if(this.tipo_comp == "router"){
            var nombreR = document.getElementById("componentname");
            var dirIP = document.getElementById("ipComp");
            var numPorts = document.getElementById("numPorts");
            var velocidad_transR = document.getElementById("velTrans");
            var dirMAC = document.getElementById("dirMAC");
            var statusR = document.getElementById("status");
            var protocoloR = document.getElementById("protocolo");
            var conexion = document.getElementById("tipoconn");
           
            let router = {
                nombre: nombreR,
                dir_ip: dirIP,
                num_puertos: numPorts,
                velocidad_trans: velocidad_transR,
                color: "azul", //buscar y cambiar por codigo hexadecimal mas especifico
                dirMAC: dirMAC,
                status: statusR,
                protocolo: protocoloR,
                tipo_conexion: conexion
            }
    
            let dataR = JSON.stringify(router,null,2)
            
            fs.writeFile("./Componentes/Router.json", dataR,(err) => {
                if(err) throw err;
                console.log("Se escribio la informacion del router en el archivo")
            });
        }
    
        if(this.tipo_comp == "servidor"){
            var nombreSer = document.getElementById("servername");
            var dirIP = document.getElementById("ipServer");
            var storage_capacitySer = document.getElementById("storageCap");
            var sistemaOpSer = document.getElementById("opsys");
            var capacidadRAMSer = document.getElementById("capRam");
            var velocidad_transSer = document.getElementById("servervel");
            var capacidadCPUSer = document.getElementById("capCpu");
            var conexionSer = document.getElementById("serverconn");
            var statusSer = document.getElementById("statusServ");
            
            let server = {
                nombre: nombreSer,
                dirip: dirIP,
                storage_capacity: storage_capacitySer,
                sistemaOp: sistemaOpSer,
                capacidadRAM: capacidadRAMSer,
                velocidad_trans: velocidad_transSer,
                capacidadCPU: capacidadCPUSer,
                color: "verde", //buscar y cambiar por codigo hexadecimal mas especifico
                tipo_conexion: conexionSer,
                status: statusSer
            }
            
            let dataSer = JSON.stringify(server,null,2)
    
            fs.writeFile("./Componentes/Server.json", dataSer,(err) => {
                if(err) throw err;
                console.log("Se escribio la informacion del router en el archivo")
            });
        }
    
        if(this.tipo_comp == "switch"){
            var nombreSw = document.getElementById("switchname");
            var dirMACSw = document.getElementById("dirMACSw");
            var numPortsSw = document.getElementById("numPortsSw");
            var velocidad_transSw = document.getElementById("velTransSw");
            var statusSw = document.getElementById("statusSw");
            var conexionSw = document.getElementById("tipoconnSw");
           
            let switchcomp = {
                nombre: nombreSw,
                dirMAC: dirMACSw,
                num_puertos: numPortsSw,
                velocidad_trans: velocidad_transSw,
                color: "amarillo", //buscar y cambiar por codigo hexadecimal mas especifico
                tipo_conexion: conexionSw,
                status: statusSw
            }
    
            let dataSw = JSON.stringify(switchcomp,null,2);
    
            fs.writeFile("./Componentes/Switch.json", dataSw,(err) => {
                if(err) throw err;
                console.log("Se escribio la informacion del router en el archivo")
            });
        }
    
        if(this.tipo_comp == "switch multicapa"){
            var nombreSW = document.getElementById("switchname");
            var dirMACSW = document.getElementById("dirMACSw");
            var numPortsSW = document.getElementById("numPortsSw");
            var velocidad_transSW = document.getElementById("velTransSw");
            var statusSW = document.getElementById("statusSw");
            var conexionSW = document.getElementById("tipoconnSw");
    
            let switchcomp = {
                nombre: nombreSW,
                dirMAC: dirMACSW,
                num_puertos: numPortsSW,
                velocidad_trans: velocidad_transSW,
                color: "amarillo", //buscar y cambiar por codigo hexadecimal mas especifico y diferente de switch
                tipo_conexion: conexionSW,
                status: statusSW
            }
    
            let dataSW = JSON.stringify(switchcomp,null,2);
            fs.writeFile("./Componentes/SwitchMulticapa.json",dataSW, (err) => {
                if(err) throw err;
                console.log("Se escribio la informacion del router en el archivo")
            });
        }
    
        if(this.tipo_comp == "conexion"){
    
            fs.open("./Componentes/Conexion.json","w"),(err,data) => {
                var server_data = JSON.parse(data);
                //Por el momento esto se encuentra en consola, trabajarlo sobre un form
            }
        }
    }

    ImprimirArbol = () =>{
        let dataR = fs.readFileSync("Router.json");
        let routerInfo = JSON.parse(dataR);

        let dataSw = fs.readFileSync("Switch.json");
        let switchInfo = JSON.parse(dataSw);

        let dataSW = fs.readFileSync("SwitchMulticapa.json");
        let switchMInfo = JSON.parse(dataSW);

        let dataSer = fs.readFileSync("Server.json");
        let serverInfo = JSON.parse(dataSer);

        let dataConn = fs.readFileSync("Conexion.json");
        let connInfo = JSON.parse(dataConn);

        document.getElementById("InfoComp").innerHTML = routerInfo.nombre;
        document.getElementById("InfoComp").innerHTML = switchInfo.nombre;
        document.getElementById("InfoComp").innerHTML = switchMInfo.nombre;
        document.getElementById("InfoComp").innerHTML = serverInfo.nombre;
        

    }
    
    EscanearRed = () =>{
        let dataR = fs.readFileSync("Router.json");
        let routerInfo = JSON.parse(dataR);

        let dataSw = fs.readFileSync("Switch.json");
        let switchInfo = JSON.parse(dataSw);

        let dataSW = fs.readFileSync("SwitchMulticapa.json");
        let switchMInfo = JSON.parse(dataSW);

        let dataSer = fs.readFileSync("Server.json");
        let serverInfo = JSON.parse(dataSer);

        let dataConn = fs.readFileSync("Conexion.json");
        let connInfo = JSON.parse(dataConn);

        document.getElementById("RoutersData").innerHTML = routerInfo;
        document.getElementById("SwitchData").innerHTML = switchInfo;
        document.getElementById("SwitchMData").innerHTML = switchMInfo;
        document.getElementById("ServerData").innerHTML = serverInfo;
        document.getElementById("ConnData").innerHTML = connInfo;
    }
}