//Recepción de datos del formulario de componentes


var componente = document.getElementById("component").value; //Obtiene el valor para determinar que componente se crea
var compcant = document.getElementById("compcant").value; //Obtiene el numero de componentes que se quiere crear
var numcomps = parseInt(compcant,10); //Transforma el valor anterior en un numero decimal

let routerArray = [];
let serverArray = [];
let switchArray = [];
let switchMArray = [];
let conexionArray = [];

var btnMapa = document.getElementById("UpdateMap");
if(btnMapa){
    btnMapa.addEventListener("click", EscanearRed() ,false);
}
console.log(componente);
//Funcion que revisa el tipo de componente que se está creando
function CheckComp () {
    console.log(componente);

    //Crea un nodo router
    if(componente == "router"){
        var newRouter = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        for(var i = 0;i <= numcomps; i++){
            routerArray = [newRouter.AlmacenarComp()+','];
        }
        
    }

    //Crea un nodo server
    if(componente == "server"){
        var newServer = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        for(var i = 0; i <= numcomps; i++){
            serverArray = [newServer.AlmacenarComp()+','];
        }
        
    }

    //Crea un nodo switch
    if(componente == "switch"){
        var newSwitch = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        for(var i = 0; i <= numcomps; i++){
            switchArray = [newSwitch.AlmacenarComp()+','];
        }
        
    }

    //Crea un nodo switch multicapa
    if(componente == "switch multicapa"){
        var newSwitchM = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        for(var i = 0; i <= numcomps; i++){
            switchMArray = [newSwitchM.AlmacenarComp()+','];
        }
        
    }

    //Crea un nodo conexion
    if(componente == "conexion"){
        var newConexion = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        for(var i = 0; i <= numcomps; i++){
            conexionArray = [newConexion.AlmacenarComp()+','];
        }
        
    }
}

function ShowCompData() {
    console.log(entornoVar.EscanearRed());
}
