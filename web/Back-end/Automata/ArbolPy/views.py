from ast import iter_child_nodes
from turtle import width
from unittest import loader
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.template import RequestContext
from django.urls import reverse
from .models import Arbol, Componente, Elemento, RedScan, SubRedIMG
from .forms import *
import os, sys, platform
from datetime import datetime
import nmap
import networkx as nx
import matplotlib.pyplot as plt

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
            return HttpResponseRedirect(reverse('ArbolPy:autoRed'))#Cambiar ListaComponent por otra vista 
    context = {'form':form}
    return render(request, 'ArbolPy/TomaDatosScan.html',context)
       

#funcion para cargar los nodos y subirlos a la plantilla
def nodosView(request):
    context = {"segRed": SubRedIMG.objects.first()}
    return render(request,'ArbolPy/ArbolRed.html',context)

#Función para escanear la red por medio de la IP de la red
def EscanearRed(request):
    ip =  RedScan.objects.all() #Obtención de la tupla con los datos para el escaneo de la red  (para raw 'SELECT * FROM ArbolPy_redscan;')
    ipExiste = ip.exists()
    arrayHostdeRed = []
    print(ip)
    if(ip == None):
        arrayHostdeRed = []
        arrayHosts = []
        context = {'Hosts':arrayHostdeRed,
                   'HostName':arrayHosts}
        return render(request, 'ArbolPy/ArbolAuto.html',context)
    elif (ip != None):
        divIP = ip[0].segmento_red #Asignación del valor segmento_red a la variable divIP
    scanPort = nmap.PortScanner() #Creación de un objeto nmap para escanear puertos
    MascaraR = ip[0].MasRed
    componentesIP = divIP.split(".") #Division del segmento de red realizada en cada punto de la cadena
    
    #Evalua la mascara de subred para iniciar el escaneo
    if(MascaraR >= '8' and MascaraR <= '15'):
        #Concatenación de los valores del segmento de red
            red = componentesIP[0]+'.'
            comienzo = int(ip[0].subred_comienzo)
            fin = int(ip[0].subred_final)
            num_puertos = int(ip[0].puertos_escaneo)

            direccion_inicio = red+str(comienzo)+'.0.0'
            direccion_final = red+str(fin)
            scanPort.scan(direccion_inicio+'/'+str(MascaraR),str(num_puertos))

    elif(MascaraR >= '16' and MascaraR <= '23'):
        #Concatenación de los valores del segmento de red
            red = componentesIP[0]+'.'+componentesIP[1]+'.'
            comienzo = int(ip[0].subred_comienzo)
            fin = int(ip[0].subred_final)
            num_puertos = int(ip[0].puertos_escaneo)

            direccion_inicio = red+str(comienzo)+'.0'
            direccion_final = red+str(fin)
            contador = int(componentesIP[1])
            while contador <= 255:
                scanPort.scan(direccion_inicio+'/'+str(MascaraR),str(num_puertos))

                arrayHostdeRed.append(scanPort.all_hosts())#Se almacenan todas las direcciones encontradas en el rango especificado
                arrayHosts = [] #arreglo para almacenar unicamente los nombres de los host de cada dirección
                for arrayhost in arrayHostdeRed:
                    arrayHosts.append(scanPort[arrayhost].hostname())
                contador = contador + 1    

    elif(MascaraR >= '24' and MascaraR <= '31'): 
        try:
            #Concatenación de los 3 primeros valores del segmento de red
            red = componentesIP[0]+'.'+componentesIP[1]+'.'+componentesIP[2]+'.'
            comienzo = int(ip[0].subred_comienzo)
            fin = int(ip[0].subred_final)
            num_puertos = int(ip[0].puertos_escaneo)

            direccion_inicio = red+str(comienzo)
            direccion_final = red+str(fin)
            #Objeto scanPort escanea la red dirección de inicio con la mascara especificada
            #Se pasan los parametros y se empieza el escaneo
            contador = int(componentesIP[2])
            scanPort.scan(direccion_inicio+'/'+str(MascaraR),str(num_puertos))

            arrayHostdeRed = scanPort.all_hosts()   #Se almacenan todas las direcciones encontradas en el rango especificado
            arrayHosts = [] #arreglo para almacenar unicamente los nombres de los host de cada dirección
            for arrayhost in arrayHostdeRed:
                arrayHosts.append(scanPort[arrayhost].hostname())

        except:
            print("Error")
    
    context = {'Hosts':arrayHostdeRed,
               'HostName':arrayHosts}
    
    DibujarArbol(arrayHostdeRed,arrayHosts)

    RedScan.objects.all().delete()    #Borra el registro de la tabla para el escaneo de la red
    return render(request, 'ArbolPy/ArbolAuto.html',context)

#Funcion para dibujar el arbol de nuestra red de manera dinámica en el navegador
def DibujarArbol(CantidadHosts,HostName): #CantidadHosts = Direcciones IP detectadas en el escaneo
                                          #HostName = Nombre de host de cada dirección IP detectada
    subredcomponents = [] #Arreglo para almacenar los elementos de la red que no son gateways
    sublabel = [] #Arreglo para almacenar los labels que no pertenezcan a un gateway
    graph = nx.Graph()
    i=1 #Variable de control para labels de los nodos
    k=1 #Variable de control para los nodos no gateway

    #Se van recorriendo todos los elementos de HostName
    for hostN in HostName: 
        graph.add_node(i, name = hostN) #Añade todos los nombres de host como nodos
        i = i + 1 #Se incrementa el contador i para dar a cada nodo un label diferente
        

    #Revisar los nombres de los host para obtener los gateway
    for host in HostName:
        sublabel = list(graph.nodes) #Se almacenan los label de los nodos 

        #Revisa que el valor sea distinto de _gateway 
        if(host != '_gateway'):
            subredcomponents.append(host) #De cumplir la condicion mete el nombre en el arreglo    
        else:
            limiteForGate = len(sublabel)
            subcomp = 1
            while subcomp < limiteForGate:
                #Busca el nodo con el nombre gateway para quitarlo del arreglo sublabel
                if(graph.nodes[subcomp]['name'] == '_gateway'):
                    sublabel.remove(subcomp)
                    for subl in sublabel:
                        graph.add_edge(subcomp,subl)# Se añade el gateway como edge

                subcomp = subcomp + 1
    
    #Pruebas para correccion de errores y ver datos
    print(CantidadHosts) #hosts de la red
    print(len(CantidadHosts)) #cantidad de hosts en la red
    print(HostName) #nombres de los hosts
    print(subredcomponents) #nombres de los hosts excluyendo gateways
    print(list(graph.nodes)) #nodos en el grafico
    print(sublabel)
    print(graph.nodes[1]['name'])
    print(list(graph.edges)) #edges en el grafico

    #Hace un archivo gml de nuestro gráfico
    nx.write_gml(graph,"grafico_segmentoRed.gml")

    #Dibuja el grafico con los atributos especificados tamaño de nodo, ancho de lineas y mostrar o no labels de los nodos
    nx.draw(graph,with_labels = True) 
    plt.savefig("Grafico_Red.png", format = "PNG")
    