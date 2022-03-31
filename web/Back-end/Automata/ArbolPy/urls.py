"""Define las urls de la app ArbolPy."""

from django.urls import path
from . import views

app_name = 'ArbolPy'
urlpatterns = [
    #Pagina de inicio
    path('', views.index, name = 'index'),
    #Pagina para request Crear Componente (pruebas)
    path('listaComps/', views.ListaComponent, name = 'ListaComponent'),
    #Detalles para cada tipo de componente
    path('listaComps/<int:componente_id>/', views.componente, name = 'ComponenteIndividual'),
    #Requerimientos de datos para una conexion
    path('nuevaConn/',views.datosConn, name = 'datosConn'),
    #Requerimientos de datos para un router
    path('nuevoRouter/',views.datosRouter, name = "datosRouter"),
    #Requerimientos de datos para un server
    path('nuevoServer/',views.datosServer, name = 'datosServer'),
    #Requerimientos de datos para un switch
    path('nuevoSwitch/',views.datosSwitch, name = 'datosSwitch'),
    #Requerimientos de datos para un switch multicapa
    path('nuevoSwitchM/',views.datosSwitchM, name = 'datosSwitchM'),
    #Vista de la red estática
    path('VistaRed/', views.nodosAr, name = "verRed"),
    #Recopilar datos para escanear la red
    path('getRedData/',views.datosRed, name = 'getRedinfo'),
    #Vista de la red automática
    path('showRed/',views.EscanearRed, name = 'autoRed'),
]
