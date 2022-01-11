//const { SlowBuffer } = require("buffer");
//const Automata = require("./juego_vida");

class ComponenteRed {
    constructor(idComponente,IPdir,num_puertos,tipo_conexion,velocidad_trans,color,procesxciento){
        this.idComponente = idComponente;
        this.IPdir = IPdir;
        this.num_puertos = num_puertos;
        this.tipo_conexion = tipo_conexion;
        this.velocidad_trans = velocidad_trans;
        this.color = color;
        this.procesxciento = procesxciento;
    }

    EstConnCliente = () => {
        var io = require('socket.io');
        var socket = new io.Socket();
        var host = process.env.HOST;
        var port = process.env.PORT;

        var client_conn = `http://${host}:${port}` 
        socket.connect(client_conn);

        //Establecer conexion al servidor
        socket.on('connect', function(){
            console.log('El cliente se ha conectado al servidor')
        });

        //Recepcion de informacion del servidor
        socket.on('connect',function(data){
            console.log("Mensaje recibido del servidor",data);
        });

        //Metodo de desconexion
        socket.on('disconnect', function(){
            console.log("Se ha desconectado del servidor")
        });
        
        this.sendData(client_conn,null); //Temporalmente el valor del mensaje se pone como null
    }

    /*sendData = (socket_conn, message) => {
        var io = require('socket.io');
        var socket = new io.Socket();

        socket.connect(socket_conn); 
        socket.send(message);
    }*/

    
    
}

class Switch{

    constructor(dirMAC, num_puertos, velocidad_trans, color, tipo_conexion,status){
        this.dirMAC = dirMAC;
        this.num_puertos = num_puertos;
        this.velocidad_trans = velocidad_trans;
        this.color = color;
        this.tipo_conexion = tipo_conexion;
        this.status = status;
    }

    //Métodos GET
    getMAC = () => {
        return this.dirMAC;
    }

    getPuertos = () => {
        return this.num_puertos;
    }

    getVelocidadTrans = () => {
        return this.velocidad_trans
    }

    getColor = () => {
        return this.Color
    }

    getTipoConexion = () => {
        return this.TipoConexion
    }

    getStatus = () => {
        return this.status
    }
    //Meter datos del switch al archivo json
    
    setSwitchData = () => {
        const fs = require(fs);
        fs.open("")
    }
    //Para Linux usando nodejs
    //Protocolo ARP

    //Funcion para enviar la solicitud ARP a un dispositivo
    /*getMAC = () => {
        var arp = require(arpjs);
        const fs = requiere(fs);
        //Leer el archivo json para obtener los datos para enviar la solicitud ARP
        fs.open("send_ARP_info.json","r", (err,file) => {
            var my_arp_data = JSON.parse(ARP_data)
            var OP = my_arp_data[0].op;
            var SRC_IP = my_arp_data[0].src_ip;
            var DST_IP = my_arp_data[0].dst_ip;
            var SRC_MAC = my_arp_data[0].src_mac;
            var DST_MAC = my_arp_data[0].dst_mac;
        })
        arp.send({
            'op': OP, //Tipo de solicitud que se envia
            'src_ip': SRC_IP, //Direccion IP fuente
            'dst_ip': DST_IP, //Direccion IP destino
            'src_mac': SRC_MAC,
            'dst_mac': DST_MAC
        })
    }

    getARPTable = () => {
        arp.table(function(err,table){
            console.log(table)
        })
    }*/
    
}

class SwitchMulticapa{
    constructor(dirMAC, num_puertos, velocidad_trans, color, tipo_conexion, status){
        this.dirMAC = dirMAC;
        this.num_puertos = num_puertos;
        this.velocidad_trans = velocidad_trans;
        this.color = color;
        this.tipo_conexion = tipo_conexion;
        this.status = status;
    }

    //Métodos GET
    getMAC = () => {
        return this.dirMAC;
    }

    getPuertos = () => {
        return this.num_puertos;
    }

    getVelocidadTrans = () => {
        return this.velocidad_trans
    }

    getColor = () => {
        return this.Color
    }

    getTipoConexion = () => {
        return this.TipoConexion
    }
    getStatus = () => {
        return this.status
    }
    //Protocolo ARP
    /*getMAC = () => {
        var arp = require(arpjs);
        const fs = requiere(fs);
        //Leer el archivo json para obtener los datos para enviar la solicitud ARP
        fs.open("send_ARP_info.json","r", (err,file) => {
            var my_arp_data = JSON.parse(ARP_data)
            var OP = my_arp_data[0].op;
            var SRC_IP = my_arp_data[0].src_ip;
            var DST_IP = my_arp_data[0].dst_ip;
            var SRC_MAC = my_arp_data[0].src_mac;
            var DST_MAC = my_arp_data[0].dst_mac;
        })
        arp.send({
            'op': OP, //Tipo de solicitud que se envia
            'src_ip': SRC_IP, //Direccion IP fuente
            'dst_ip': DST_IP, //Direccion IP destino
            'src_mac': SRC_MAC, //Dirección MAC Fuente
            'dst_mac': DST_MAC
        })
    }

    getARPTable = () => {
        arp.table(function(err,table){
            console.log(table)
        })
    }*/
}

class Router {
    constructor(dirIP, num_puertos,velocidad_trans,color,dirMAC,status, protocolo, tipo_conexion) {
        this.dirIP = dirIP;
        this.num_puertos = num_puertos;
        this.velocidad_trans = velocidad_trans;
        this.color = color;
        this.dirMAC = dirMAC;
        this.status = status;
        this.protocolo = protocolo;
        this.tipo_conexion = tipo_conexion;
    }

    //Metodos GET
    getIP = () => {
        return this.dirIP;
    }

    getNumPuertos = () => {
        return this.num_puertos;
    }

    getVelocidadTrans = () => {
        return this.velocidad_trans;
    }

    getColor = () => {
        return this.color;
    }

    getDirMAC = () =>{
        return this.dirMAC;
    }

    getStatus = () => {
        return this.status;
    }

    getProtocolo = () => {
        return this.protocolo;
    }

    getTipoConexion = () => {
        return this.tipo_conexion
    }
}

class Server {

    constructor(dirip, storage_capacity, sistemaOp, capacidadRAM, velocidad_trans, capacidadCPU,color,tipo_conexion, status){
        this.dirip = dirip;
        this.storage_capacity = storage_capacity;
        this.sistemaOp = sistemaOp;
        this.capacidadRAM = capacidadRAM;
        this.velocidad_trans = velocidad_trans;
        this.capacidadCPU = capacidadCPU;
        this.color = color;
        this.tipo_conexion = tipo_conexion;
        this.status = status;
    }

    //Métodos GET
    getIP = () => {
        return this.dirip;
    }

    getStorageCapacity = () => {
        return this.storage_capacity;
    }

    getSistemaOP = () => {
        return this.sistemaOp;
    }

    getCapacidadRAM = () => {
        return this.capacidadRAM;
    }

    getVelocidadTrans = () => {
        return this.velocidad_trans;
    }

    getCapacidadCPU = () => {
        return this.capacidadCPU;
    }


    getColor = () => {
        return this.color;
    }
    
    getTipoConexion = () => {
        return this.tipo_conexion
    }

    getStatus = () => {
        return this.status;
    }

    //Inicializar servidor
    /*static serverStart = async () => {
        var http = require('http');
        var port = process.env.PORT;
        try{
            var server = http.createServer(function(req,res){
                //Envio de cabecera
                res.writeHead(200,{'Content-Type': 'text/html'})
            })
            server.listen(port,function(){
                console.log("Servidor iniciado correctamente")
                console.log(`Servidor iniciado en ${process.env.HOST}:${process.env.PORT}`)
            })
            this.StablishConnection(server);
        }catch(error){
            console.error('No se pudo inicializar correctamente el servidor')
        }
    }*/
    //Establecer la conexión del servidor con un cliente
    /*static StablishConnection(server){
        var io = require('socket.io');
        var socket = io.listen(server);

        socket.on(connection, function(client){
            console.log("Conexion establecida correctamente con el cliente");

            client.on('message',function(event){
                console.log("Mensaje del cliente recibido",event);
            });

            client.on('disconnect',function(){
                clearInterval(interval);
                console.log('Se ha completado la desconexion')
            });
        });
    }
    
    static PetitionControl(req,resp){
        console.log("Petición recibida")
        var server = this.serverStart;
        server.on('request',control);
    }*/
}

class MetodoConexion{
    constructor(tipo_cable){
        this.tipo_cable = tipo_cable;
    }
}
