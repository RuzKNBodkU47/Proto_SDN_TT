from unittest import loader
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.template import RequestContext
from django.urls import reverse
from .models import Arbol, Componente, Elemento
from .forms import RouterForm
# Create your views here.
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

#Funcion de ejemplo para visualizar la red
def _inicializarArbol():
    Arbol.objects.all().delete()
    elementoarray = Elemento.objects.raw('SELECT * FROM ArbolPy_elemento')

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
        elementoNodo = elementoarray[3],
        parent = nodo_raiz
    )

    subnodo.save()
#funcion para cargar los nodos y subirlos a la plantilla
def nodosAr(request):
    _inicializarArbol()
    nodos = Arbol.objects.filter(parent = None)
    context = {'nodos':nodos}

    return render(request,'ArbolPy/ArbolRed.html',context)

