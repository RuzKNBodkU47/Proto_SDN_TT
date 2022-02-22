//Recepción de datos del formulario de componentes
//const entornoVar = require("./Entorno")
var componente;
var compcant;
var numcomps;
let form = document.getElementById('compform');

let Componente = form.elements[0];
let componentname = Componente.value;

form.onsubmit = function(e){
    var ready = false;

    if(form.component.value != "" && form.compcant.value != ""){
        ready = true;
    }else{
        ready = false;
        alert("Uno de los campos esta vacío porfavor llenelo");
        e.preventDefault();
    }

    if(ready){
        var cantidadComponentes = form.compcant.value;
        if(ValidarCantidadComps(cantidadComponentes)){
            var numeroComponentes = parseInt(compcant,10);
            if(numeroComponentes != "NaN"){
                ready = true;
            }else{
                ready = false;
                alert("No se ingreso un número en el campo especificado");
                e.preventDefault();
            }
        }
    }
}
//Función para comprobar que el input no se encuentre vacio
/*function CampoNoVacio(input){
    return !(input.value.trim() === '');
}

//Event Listener para validar cuando el usuario clicke el boton submit
form.addEventListener('submit', (event) => {
    requiredFields.forEach((input) => {
        valid = valid|CampoNoVacio(input.input);
    });
    if(!valid){
        event.preventDefault();
    }
})*/

function CheckComp() {

    componente = document.getElementById("component").value; //Obtiene el valor para determinar que componente se crea
    compcant = document.getElementById("compcant").value; //Obtiene el numero de componentes que se quiere crear
    numcomps = parseInt(compcant,10); //Transforma el valor anterior en un numero decimal

    //Crea un nodo router
    if(componente == "router"){
        document.getElementById("CompType").onClick="location.href='../../Front-end/Automata/HTML Files/RouterInfo'";
        //var newRouter = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        /*for(var i = 0;i <= numcomps; i++){
            routerArray = [newRouter.AlmacenarComp()+','];
        }*/
        
    }

    //Crea un nodo server
    if(componente == "server"){
        //var newServer = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        /*for(var i = 0; i <= numcomps; i++){
            serverArray = [newServer.AlmacenarComp()+','];
        }*/
        
    }

    //Crea un nodo switch
    if(componente == "switch"){
        //var newSwitch = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        /*for(var i = 0; i <= numcomps; i++){
            switchArray = [newSwitch.AlmacenarComp()+','];
        }*/
        
    }

    //Crea un nodo switch multicapa
    if(componente == "switch multicapa"){
        //var newSwitchM = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        /*for(var i = 0; i <= numcomps; i++){
            switchMArray = [newSwitchM.AlmacenarComp()+','];
        }*/
        
    }

    //Crea un nodo conexion
    if(componente == "conexion"){
        //var newConexion = new entornoVar.CrearNodo(componente);
        //Crea un objeto y lo almacena en el arreglo acorde a la cantidad de componentes se especifico para crear
        /*for(var i = 0; i <= numcomps; i++){
            conexionArray = [newConexion.AlmacenarComp()+','];
        }*/
        
    }
    var component = [componente,numcomps];
    return component;
}

/*var input = document.getElementsByTagName("input");
for(i=0; i<input.length; i++){
    input[i].addEventListener("change",function(){
        var revisarComp = CheckComp();
        console.log(revisarComp)
    })
}*/

//
/*let routerArray = [];
let serverArray = [];
let switchArray = [];
let switchMArray = [];
let conexionArray = [];*/

/*if(btnMapa){
    btnMapa.addEventListener("click", EscanearRed() ,false);
}*/


//Funcion que revisa el tipo de componente que se está creando


function ShowCompData() {
    console.log(entornoVar.EscanearRed());
}
