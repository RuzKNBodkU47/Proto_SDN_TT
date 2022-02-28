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
    #Requerimientos de datos para un router
    path('nuevoRouter/',views.datosRouter, name = "datosRouter"),
    #Viste de la red
    path('VistaRed/', views.nodosAr, name = "verRed"),
]
