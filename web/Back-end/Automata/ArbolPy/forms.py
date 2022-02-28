#Archivo de pruebas para los formularios con django
from dataclasses import fields
from django import forms
from .models import Componente,Elemento

class RouterForm(forms.ModelForm):
    class Meta:
        model =  Elemento.Router
        fields = ['idRouter','dirIP','num_puertos','velocidad_trans','unidad_trans','color','dirMAC','status','protocolo','tipo_conexion']
        labels = {'idRouter': 'Identificador del Router','dirIP':'Direccion IP','num_puertos':'Numero de puertos','velocidad_trans':'Velocidad de transmision maxima (numero unicamente)','unidad_trans':'Unidad de transmision de datos','color':'Color representativo','dirMAC':'Direccion MAC','status':'Estado del dispositivo','protocolo':'Protocolos implementados','tipo_conexion': 'Tipos de cable de su conexion'}