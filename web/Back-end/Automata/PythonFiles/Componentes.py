#Clases de los elementos de la red

class Switch():
    """Metodos de la clase Switch"""

    def __init__(self, dirMac, num_Puertos, velocidad_trans, color, tipo_conexion, status):
        """Inicializa los atributos del componente Switch"""
        self.dirMac = dirMac
        self.num_Puertos = num_Puertos
        self.velocidad_trans = velocidad_trans
        self.color = color
        self.tipo_conexion = tipo_conexion
        self.status = status

class SwitchMulticapa():
    """Métodos de la clase Switch Multicapa"""
    def __init__(self, dirMac, num_Puertos, velocidad_trans, color, tipo_conexion, status):
        """Inicializa los atributos del componente Switch Multicapa"""
        self.dirMac = dirMac
        self.num_Puertos = num_Puertos
        self.velocidad_trans = velocidad_trans
        self.color = color
        self.tipo_conexion = tipo_conexion
        self.status = status

class Router():
    """Metodos de la clase Router"""

    def __init__(self, dirIP, num_puertos, velocidad_trans, color, dirMAC, status, protocolo, tipo_conexion):
        """Inicializa los atributos del componente Router"""
        self.dirIP = dirIP
        self.num_puertos = num_puertos
        self.velocidad_trans = velocidad_trans
        self.color = color
        self.dirMAC = dirMAC
        self.status = status
        self.protocolo = protocolo
        self.tipo_conexion = tipo_conexion

class Server():
    """Metodos de la clase Server"""

    def __init__(self, dirip, storage_capacity, sistemaOp, capacidadRAM, velocidad_trans, capacidadCPU, color, tipo_conexion, status):
        """Inicializa los atributos del componente Server"""
        self.dirip = dirip
        self.storage_capacity = storage_capacity
        self.sistemaOp = sistemaOp
        self.capacidadRAM = capacidadRAM
        self.velocidad_trans = velocidad_trans
        self.capacidadCPU = capacidadCPU
        self.color = color
        self.tipo_conexion = tipo_conexion
        self.status = status

class Conexion():
    """Metodos de la clase Conexion"""
    
    def __init__(self, tipo_cable, extremoIni, extremoFin):
        """Inicializa los atributos del componente Conexion"""
        self.tipo_cable = tipo_cable
        self.extremoIni = extremoIni
        self.extremoFin = extremoFin
