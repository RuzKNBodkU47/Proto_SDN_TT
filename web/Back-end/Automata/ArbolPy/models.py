from tabnanny import verbose
from unicodedata import decimal
from django.db import models
from django.forms import CharField

# Create your models here.
class Componente(models.Model):
    """Clase que agrupa todos los componentes"""
    componente = models.CharField(max_length=12)

    def __str__(self):
        return self.componente

class Elemento(models.Model):
    """Clase que representa un elemento para cualquier tipo de componente"""
    tipo_comp = models.ForeignKey(Componente, on_delete=models.CASCADE)
    id_comp = models.SlugField(max_length=15)
    date_added = models.DateTimeField(auto_now_add=True)

    class Conexion(models.Model):
        idConn = models.SlugField(max_length=15)
        tipo_cable = models.CharField(max_length=30)
        extremoIni = models.CharField(max_length=15)
        extremoFin = models.CharField(max_length=15)
        status = models.CharField(max_length=20)

    class Router(models.Model):
        idRouter = models.SlugField(max_length=15)
        dirIP = models.GenericIPAddressField(protocol='both', unpack_ipv4=False)
        num_puertos = models.DecimalField(max_digits=3, decimal_places=0)
        velocidad_trans = models.DecimalField(max_digits=3, decimal_places=0)#Cantidad numerica de la velocidad de transferencia
        unidad_trans = models.SlugField(max_length=5)#Unidad de transferencia de datos (KB/s, MB/s, etc.)
        color = models.SlugField(max_length=10)
        dirMAC = models.CharField(max_length=17)
        status = models.CharField(max_length=20)
        protocolo = models.CharField(max_length=8)
        tipo_conexion = models.CharField(max_length=30)
        rolPoH = models.SlugField(max_length=5)
        
    
    class Server(models.Model):
        idServer = models.SlugField(max_length=15)
        dirip = models.GenericIPAddressField(protocol='both',unpack_ipv4=False)
        storage_capacity = models.DecimalField(max_digits=3, decimal_places=0)#Cantidad numerica de la capacidad de almacenaje
        unidad_storage = models.SlugField(max_length=3)#Unidad de almacenamiento (GB, TB)
        sistemaOP = models.CharField(max_length=30)
        capacidadRAM = models.DecimalField(max_digits=2, decimal_places=0)
        velocidad_trans = models.DecimalField(max_digits=3, decimal_places=0)#Cantidad numerica de la velocidad de transmision
        unidad_trans = models.SlugField(max_length=5)#Unidad de transferencia de datos (KB/s, MB/s, etc.)
        capacidadCPU = models.DecimalField(max_digits=1, decimal_places=0)
        color = models.SlugField(max_length=10)
        tipo_conexion =  models.CharField(max_length=30)
        status = models.CharField(max_length=20)

    class Switch(models.Model):
        idSW = models.SlugField(max_length=15)
        dirMac = models.CharField(max_length=17)
        num_Puertos = models.DecimalField(max_digits=3, decimal_places=0)
        velocidad_trans = models.DecimalField(max_digits=3, decimal_places=0)
        color = models.SlugField(max_length=10)
        tipo_conexion = models.CharField(max_length=30)
        status = models.CharField(max_length=20)

    class SwitchMulticapa(models.Model):
        idSWM = models.SlugField(max_length=15)
        dirMac = models.CharField(max_length=17)
        num_Puertos = models.DecimalField(max_digits=3, decimal_places=0)
        velocidad_trans = models.DecimalField(max_digits=3, decimal_places=0)
        color = models.SlugField(max_length=10)
        tipo_conexion = models.CharField(max_length=30)
        status = models.CharField(max_length=20)

    def __str__(self):
        return self.id_comp + ' ' + self.id_comp

class Arbol(models.Model):
    elementoNodo = models.SlugField(max_length = 15)
    parent = models.ForeignKey("self", null = True, related_name = 'children', on_delete=models.DO_NOTHING)

    class Meta:
        verbose_name = "Nodo"
        verbose_name_plural = "Nodos"

class RedScan(models.Model):
    MasRed = models.SlugField(max_length=4)
    segmento_red = models.GenericIPAddressField(protocol = 'both', unpack_ipv4 = False)
    subred_comienzo = models.SlugField(max_length = 3)
    subred_final = models.SlugField(max_length = 3)
    puertos_escaneo = models.CharField(max_length = 50)

class SubRedIMG(models.Model):
    graficaSegmento = models.ImageField()   