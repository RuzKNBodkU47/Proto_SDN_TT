from ast import iter_child_nodes
from unittest import loader
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.template import RequestContext
from django.urls import reverse
from .models import Arbol, Componente, Elemento, RedScan
from .forms import *
import os, sys, platform
from datetime import datetime
import nmap
import networkx as nx

#Url para la pagina de inicio
def index(request):
    """Página de inicio"""
    return render(request,'ArbolPy/index.html')

#Url para la pagina de seleccion de componente
def ListaComponent(request):
    """Pagina para pruebas de creación de componentes Lista de componentes"""
    components = Componente.objects.order_by('componente')
    context = {'Componentes': components}
    return render(request, 'ArbolPy/ListaComponent.html', context)

def componente(request,componente_id):
    """Mostrara lo relacionado a un tipo de componente unicamente"""
    id_componente = Componente.objects.get(id = componente_id)
    objetos_componente = id_componente.elemento_set.order_by('date_added')
    context = {'ComponenteInd':id_componente,'Elementos':objetos_componente}
    return render(request, 'ArbolPy/ComponenteInd.html', context)

#Funciones para obtener la informacion de los elementos por medio del formulario
def datosConn(request):
    """Pagina para prueba para ingresar los datos de una conexion"""
    if(request.method != 'POST'):
        #No se ingreso informacion al formulario y crea uno en blanco en consecuencia
        form = ConnForm()
    else:
        #Se procesa la información recibida
        form = ConnForm(data = request.POST)
        if(form.is_valid()):
            new_conn = form.save(commit = False)
            new_conn.save()
            return HttpResponseRedirect(reverse('ArbolPy:ListaComponent'))
    context = {'form':form}
    return render(request, 'ArbolPy/datosConn.html',context)

def datosRouter(request):
    """Pagina para prueba para ingresar los datos de un router"""
    if(request.method != 'POST'):
        #No se ingreso informacion al formulario y crea uno en blanco en consecuencia
        form = RouterForm()
    else:
        #Se procesa la información recibida
        form = RouterForm(data = request.POST)
        if(form.is_valid()):
            new_router = form.save(commit = False)
            new_router.save()
            return HttpResponseRedirect(reverse('ArbolPy:ListaComponent'))
    context = {'form':form}
    return render(request, 'ArbolPy/datosRouter.html',context)

def datosServer(request):
    """Pagina para prueba para ingresar los datos de un server"""
    if(request.method != 'POST'):
        #No se ingreso informacion al formulario y crea uno en blanco en consecuencia
        form = ServerForm()
    else:
        #Se procesa la información recibida
        form = ServerForm(data = request.POST)
        if(form.is_valid()):
            new_server = form.save(commit = False)
            new_server.save()
            return HttpResponseRedirect(reverse('ArbolPy:ListaComponent'))
    context = {'form':form}
    return render(request, 'ArbolPy/datosServer.html',context)

def datosSwitch(request):
    """Pagina para prueba para ingresar los datos de un switch"""
    if(request.method != 'POST'):
        #No se ingreso informacion al formulario y crea uno en blanco en consecuencia
        form = SwitchForm()
    else:
        #Se procesa la información recibida
        form = SwitchForm(data = request.POST)
        if(form.is_valid()):
            new_switch = form.save(commit = False)
            new_switch.save()
            return HttpResponseRedirect(reverse('ArbolPy:ListaComponent'))
    context = {'form':form}
    return render(request, 'ArbolPy/datosSwitch.html',context)

def datosSwitchM(request):
    """Pagina para prueba para ingresar los datos de un switch multicapa"""
    if(request.method != 'POST'):
        #No se ingreso informacion al formulario y crea uno en blanco en consecuencia
        form = SwitchMulForm()
    else:
        #Se procesa la información recibida
        form = SwitchMulForm(data = request.POST)
        if(form.is_valid()):
            new_switchM = form.save(commit = False)
            new_switchM.save()
            return HttpResponseRedirect(reverse('ArbolPy:ListaComponent'))
    context = {'form':form}
    return render(request, 'ArbolPy/datosSwitchM.html',context)

def datosRed(request):
    """Pagina para recopilar los datos para el escaneo de la red"""
    if(request.method != 'POST'):
        #No se ingreso información alguna
        form = RedInfo()
    else:
        form = RedInfo(data = request.POST)
        if(form.is_valid()):
            new_scan = form.save(commit = False)
            new_scan.save()
            return HttpResponseRedirect(reverse('ArbolPy:ListaComponent'))#Cambiar ListaComponent por otra vista 
    context = {'form':form}
    return render(request, 'ArbolPy/TomaDatosScan.html',context)
       

#Funcion de ejemplo para visualizar la red
def _inicializarArbol():
    Arbol.objects.all().delete()
    routerArray = Elemento.Router.objects.raw('SELECT idRouter,tipo_conexion FROM ArbolPy_router')
    connArray = Elemento.Conexion.objects.raw('SELECT extremoIni,extremoFin,idConn FROM ArbolPy_conexion')
    serverArray = Elemento.Server.objects.raw('SELECT idServer,tipo_conexion FROM ArbolPy_server')
    switchArray = Elemento.Server.objects.raw('SELECT idSW,tipo_conexion FROM ArbolPy_switch')
    switchMArray = Elemento.Server.objects.raw('SELECT idSWM,tipo_conexion FROM ArbolPy_switchmulticapa')
    elementoarray = Elemento.objects.raw('SELECT * FROM ArbolPy_elemento')
    ip =  RedScan.objects.raw('SELECT * FROM ArbolPy_redscan')
    #i = 0
    #lenRoutArr = len(routerArray)
    
    nodo_raiz = Arbol(
        elementoNodo = elementoarray[2]
    )
    nodo_raiz.save()

    subnodo = Arbol(
        elementoNodo = elementoarray[1],
        parent = nodo_raiz
    )

    subnodo.save()

    subnodo = Arbol(
        elementoNodo = elementoarray[0].date_added,
        parent = nodo_raiz
    )   

    subnodo.save()

    subnodo = Arbol(
        elementoNodo = ip[0].segmento_red.split("."),
        parent = nodo_raiz
    )

    subnodo.save()

#funcion para cargar los nodos y subirlos a la plantilla
def nodosAr(request):
    _inicializarArbol()
    nodos = Arbol.objects.filter(parent = None)
    context = {'nodos':nodos}

    return render(request,'ArbolPy/ArbolRed.html',context)

#Función para escanear la red por medio de la IP de la red
def EscanearRed(request):
    ip =  RedScan.objects.raw('SELECT * FROM ArbolPy_redscan') #Obtención de la tupla con los datos para el escaneo de la red
    divIP = ip[0].segmento_red #Asignación del valor segmnto_red a la variable divIP
    scanPort = nmap.PortScanner() #Creación de un objeto nmap para escanear puertos
    try:
        componentesIP = divIP.split(".") #Division del segmento de red realizada en cada punto de la cadena
        #Concatenación de los 3 primeros valores del segmento de red
        red = componentesIP[0]+'.'+componentesIP[1]+'.'+componentesIP[2]+'.'
        comienzo = int(ip[0].subred_comienzo)
        fin = int(ip[0].subred_final)
        num_puertos = int(ip[0].puertos_escaneo)

        direccion_inicio = red+str(comienzo)
        direccion_final = red+str(fin)
    except:
        print("Error")
        #sys.exit(1)
    
    #Se pasan los parametros y se empieza el escaneo
    scanPort.scan(direccion_inicio+'-'+str(fin),str(num_puertos))
    arrayHostdeRed = scanPort.all_hosts() #Se almacenan todas las direcciones encontradas en el rango especificado
    arrayHosts = []
    for arrayhost in arrayHostdeRed:
        arrayHosts.append(scanPort[arrayhost].hostname())
        
    context = {'Hosts':arrayHostdeRed,
                'HostName':arrayHosts}
    
    return render(request, 'ArbolPy/ArbolAuto.html',context)
    
#Función para devolver los datos escaneados de la red
def devolverRed(request):
    EscanearRed()

    context = {}
    return render(request, 'ArbolPy/ArbolAuto.html',context)

#Funcion para dibujar el arbol de nuestra red de manera dinámica en el navegador
def DibujarArbol():
    graph = nx.Graph()