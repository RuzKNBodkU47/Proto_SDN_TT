from pysnmp.hlapi import * 
#Funciones para el protocolo SNMP
import pymysql.cursors
#Función get de SNMP

def GetFunc(User, AuthKy,AgentTarget,OIDN, OIDMem, OIDcpu, OIDDisk):
    getCommand = getCmd(SnmpEngine(), #Instancia de la clase SNMPengine (obligatorio en la funcion)
                        UsmUserData(User, authKey = AuthKy), #privkey es un valor opcional
                        UdpTransportTarget((AgentTarget,161)), #Establecer transport y target
                        ContextData(), #Contexto SNMP vacio valor default
                        ObjectType(ObjectIdentity(OIDN)) #ObjectIdentity aborda objetos MIB desde perspectiva humana
                                                                              #ObjectType objeto contenedor que referencia a instancias ObjectIdentity y SNMP
                        ) 


    errorIndication, errorStatus, errorIndex, varBinds = next(getCommand)

    if errorIndication:
        print(errorIndication)
    elif errorStatus:
        print('%s at %s' % (errorStatus.prettyPrint(),
                        errorIndex and varBinds[int(errorIndex)-1][0] or '?'))
    else:
        for varBind in varBinds:
            print(' = '.join([x.prettyPrint() for x in varBind]))
       
            print(str(varBind).split(","))
            NombreDispositivo(str(varBind), OIDN, OIDMem,OIDcpu,OIDDisk)
    #Eleccion de version mpModel = 0 es para SNMP version 1, mpModel = 1 es para version 2c
    #CommunityData('public', mpModel = 1),
    
    #Para elegir SNMP version 3
    #UsmUserData('testuser', authKey = 'myauthkey', privKey = 'myenckey') #privkey es un valor opcional

#Solicitar MIB siguiente al actual
def nextFunc():
    nextCommand = nextCmd(SnmpEngine(),
                          CommunityData('public', mpModel = 1),
                          Udp6TransportTarget(('demo.snmplabs.com',161)),
                          ContextData(),
                          ObjectType(ObjectIdentity('SNMPv2-MIB','sysDescr'))
                        )
    next(nextCommand)

#Funcion Set de SNMP
def SetFunc():
    setCommand = setCmd(SnmpEngine(),
                        CommunityData('public', mpModel = 1),
                        Udp6TransportTarget(('demo.snmplabs.com',161)),
                        ContextData(),
                        ObjectType(ObjectIdentity('SNMPv2-MIB','sysDescr', 0), 'Linux i386')
                        )
    next(setCommand)

#Envio de una trampa SNMP (establecimiento de comunicación agent-to-manager de una sola via)
def TrapFunc(User, AuthKy,AgentTarget):
    setTrap = sendNotification(SnmpEngine(),
                               UsmUserData(User, authKey = AuthKy),
                               Udp6TransportTarget((AgentTarget,162)),
                               ContextData(),
                               'trap',
                               NotificationType(ObjectIdentity('1.3.6.1.4.1.2021.4.5.0'))
                               )
    next(setTrap)

#Comando inform para comunicación manager-to-manager y agent-to-manager
def InformFunc():
    setInform = sendNotification(SnmpEngine(),
                                 CommunityData('public'),
                                 UdpTransportTarget(('demo.snmplabs.com', 162)),
                                 ContextData(),
                                 'inform',
                                 NotificationType(ObjectIdentity('IF-MIB', 'linkUp'), instanceIndex=(123,))
                                )
    next(setInform)

def NombreDispositivo(cadena,oid, oidmem, oidcpu, oidisk):
    #Establecer conexión con BD (cambiar los datos aqui por los requeridos para nuestra conexion)
    conexion = pymysql.connect(host = 'localhost',
                               user = 'user',
                               password = 'passwd',
                               database = 'db',
                               charset = 'utf8mb4',
                               cursorclass = pymysql.cursors.DictCursor)

    #Evaluar el oid ingresado
    if(oid == '1.3.6.1.2.1.1.1.0'): #Oid SysDescr Obtener nombre del agente
        #Obtener el nombre del dispositivo al que se realizo la petición snmpget
        empiezasys = []
        empiezasys = cadena.split("=") #Separa la cadena en el MIB que se consulto
        quitarStringElemento = empiezasys[1].split("STRING:")
        snmpCadenaComp = quitarStringElemento[1].split("(") #Se separa la cadena para obtener unicamente el nombre del dispositivo
        limpiarGato = snmpCadenaComp[0].split("#")
        nombreDispositivo = limpiarGato[0] #Se asigna el nombre a la variable para hacer el insert en la base de datos
        print(nombreDispositivo)

        with conexion:
            with conexion.cursor() as cursor:
                #Crear nuevo registro
                register = "INSERT INTO `Datos_Dispo` (`NombreDispo`) VALUES (%s)"
                cursor.execute(register,(nombreDispositivo))

            #Se usa el siguiente commit para guardar los cambios
            conexion.commit()   
    
    if(oidmem == '1.3.6.1.4.1.2021.4.5.0'):
        #Obtener los datos de memoria
        cadenaOid = []
        cadenaOid = cadena.split("=") #Separa la cadena para obtener el dato de relevancia
        quitarStringElemento = cadenaOid[1].split("STRING:")
        snmpMemComp = quitarStringElemento[1].split("(")
        RAMmem = snmpMemComp[0]
        print(RAMmem)

        with conexion:
            with conexion.cursor() as cursor:
                #Crear nuevo registro
                register = "INSERT INTO `Datos_Dispo` (`Memoria`) VALUES (%s)"    
                cursor.execute(register(RAMmem))
    
    if(oidisk == '1.3.6.1.4.1.2021.9.1.6.1'):
        #Obtener los datos de disco
        cadenaOid = []
        cadenaOid = cadena.split("=") #Separa la cadena para obtener el dato de relevancia
        quitarStringElemento = cadenaOid[1].split("STRING:")
        snmpDiskComp = quitarStringElemento[1].split("(")

        Disksize = snmpDiskComp[0]
        with conexion:
            with conexion.cursor() as cursor:
                #Crear nuevo registro
                register = "INSERT INTO `Datos_Dispo` (`Storage`) VALUES (%s)"    
                cursor.execute(register(Disksize))
    
    if(oidcpu == '1.3.6.1.4.1.2021.11.9.0'):
        #Obtener los datos de cpu
        cadenaOid = []
        cadenaOid = cadena.split("=") #Separa la cadena para obtener el dato de relevancia
        quitarStringElemento = cadenaOid[1].split("STRING:")
        snmpCPUComp = quitarStringElemento[1].split("(")

        CPUporcentaje = snmpCPUComp[0]
        with conexion:
            with conexion.cursor() as cursor:
                #Crear nuevo registro
                register = "INSERT INTO `Datos_Dispo` (`CPU`) VALUES (%s)"    
                cursor.execute(register(CPUporcentaje))



GetFunc('Admin','Palabra123456','148.204.9.1','1.3.6.1.2.1.1.1.0','1.3.6.1.4.1.2021.4.5.0', '1.3.6.1.4.1.2021.9.1.6.1', '1.3.6.1.4.1.2021.11.9.0')  
