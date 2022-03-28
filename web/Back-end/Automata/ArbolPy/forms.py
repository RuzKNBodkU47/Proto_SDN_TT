#Archivo de pruebas para los formularios con django
from dataclasses import fields
from django import forms
from .models import Componente,Elemento,RedScan

class RouterForm(forms.ModelForm):
    class Meta:
        model =  Elemento.Router
        fields = ['idRouter','dirIP','num_puertos','velocidad_trans','unidad_trans','color','dirMAC','status','protocolo','tipo_conexion']
        labels = {'idRouter': 'Identificador del Router','dirIP':'Direccion IP','num_puertos':'Numero de puertos','velocidad_trans':'Velocidad de transmision maxima (numero unicamente)','unidad_trans':'Unidad de transmision de datos','color':'Color representativo','dirMAC':'Direccion MAC','status':'Estado del dispositivo','protocolo':'Protocolos implementados','tipo_conexion': 'Identificador de la conexion'}

class ServerForm(forms.ModelForm):
    class Meta:
        model = Elemento.Server
        fields = ['idServer','dirip', 'storage_capacity', 'unidad_storage', 'sistemaOP', 'capacidadRAM', 'velocidad_trans', 'unidad_trans', 'capacidadCPU', 'color', 'tipo_conexion', 'status']
        labels = {'idServer':'Identificador del Servidor','dirip':'Direccion IP', 'storage_capacity': 'Capacidad de almacenamiento (numero unicamente)', 'unidad_storage': 'Unidad del almacenamiento (GB/TB)','sistemaOP':'Sistema operativo del servidor','capacidadRAM':'Total de memoria RAM del servidor','velocidad_trans':'Velocidad de transmision maxima (numero unicamente)','unidad_trans':'Unidad de transmision de datos','capacidadCPU':'Capacidad de CPU del servidor (nucleos)','color':'Color representativo en este tipo de elemento','tipo_conexion':'Identificador de la Conexion','status':'Estado del elemento'}

class SwitchForm(forms.ModelForm):
    class Meta:
        model = Elemento.Switch
        fields = ['idSW','dirMac', 'num_Puertos','velocidad_trans','color','tipo_conexion','status']
        labels = {'idSW':'Identificador del switch','dirMac':'Direccion MAC', 'num_Puertos':'Numero de puertos del elemento','velocidad_trans':'Velocidad de transmision maxima (numero unicamente)','color':'Color representativo para este tipo de elemento','tipo_conexion':'Identificador de la Conexion','status':'Estado del elemento'} 

class SwitchMulForm(forms.ModelForm):
    class Meta:
        model = Elemento.SwitchMulticapa
        fields = ['idSWM','dirMac', 'num_Puertos','velocidad_trans','color','tipo_conexion','status']
        labels = {'idSWM':'Identificador del switch','dirMac':'Direccion MAC', 'num_Puertos':'Numero de puertos del elemento','velocidad_trans':'Velocidad de transmision maxima (numero unicamente)','color':'Color representativo para este tipo de elemento','tipo_conexion':'Identificador de la Conexion','status':'Estado del elemento'} 

class ConnForm(forms.ModelForm):
    class Meta:
        model = Elemento.Conexion
        fields = ['idConn','tipo_cable','extremoIni','extremoFin','status']
        labels = {'idConn':'Identificador de Conexion','tipo_cable':'Tipo de cable','extremoIni':'Elemento conextado en uno de sus extremos','extremoFin':'Elemento conectado en su extremo opuesto','status':'Estado del elemento'}

class RedInfo(forms.ModelForm):
    class Meta:
        model = RedScan
        fields = ['segmento_red','subred_comienzo','subred_final','puertos_escaneo']
        labels = {'segmento_red':'Ingresa la dirección del segmento de red a escanear',
                  'subred_comienzo': 'Ingresa el número de subred donde se iniciará el escaneo',
                  'subred_final': 'Ingresa el número de subred donde terminara el escaneo',
                  'puertos_escaneo': 'Ingresa los puertos, separados por comas, en los que deseas realizar el escaneo'}
