from pysnmp.hlapi import * 
#Funciones para el protocolo SNMP
import pymysql.cursors
import sys
import time
#Función get de SNMP
NomDispOID = '1.3.6.1.2.1.1.1.0'
MemoriaOID = "1.3.6.1.4.1.2021.4.5.0"
CPUOID = "1.3.6.1.4.1.2021.11.9.0"
DiscoOID = '1.3.6.1.4.1.2021.9.1.7.1'
OctRecib = "1.3.6.1.2.1.2.2.1.10"
OctTrans = "1.3.6.1.2.1.2.2.1.16"
AnchoTot = "1.3.6.1.2.1.2.2.1.5"
DiffInOct = []
DiffOutOct = []
ArrayVarBinds = []
def GetInOcts(OctetRecib,IPDir):
    #for i in range(1):
        iterator = nextCmd(SnmpEngine(),
                           CommunityData('ProyR', mpModel = 1),
                           UdpTransportTarget((IPDir,161)),
                           ContextData(),
                           ObjectType(ObjectIdentity(OctetRecib)),
        )
        errorIndication, errorStatus, errorIndex, varBinds = next(iterator)
        if errorIndication:
            print(errorIndication)
        elif errorStatus:
            print('%s at %s' % (errorStatus.prettyPrint(),
                            errorIndex and varBinds[int(errorIndex)-1][0] or '?'))
        else:
            for varBind in varBinds:
                print(' = '.join([x.prettyPrint() for x in varBind]))
                DiffInOct.append(str(varBind))

def GetOutOcts(OctetTrans,IPDir):
    #for i in range(1):
        iterator = nextCmd(SnmpEngine(),
                           CommunityData('ProyR', mpModel = 1),
                           UdpTransportTarget((IPDir,161)),
                           ContextData(),
                           ObjectType(ObjectIdentity(OctetTrans)),
        )
        errorIndication, errorStatus, errorIndex, varBinds = next(iterator)
        if errorIndication:
            print(errorIndication)
        elif errorStatus:
            print('%s at %s' % (errorStatus.prettyPrint(),
                            errorIndex and varBinds[int(errorIndex)-1][0] or '?'))
        else:
            for varBind in varBinds:
                print(' = '.join([x.prettyPrint() for x in varBind]))
                DiffOutOct.append(str(varBind))

def GetFunc(User, AuthKy,AgentTarget,PrivKy):
    
    getCommand = nextCmd(SnmpEngine(), #Instancia de la clase SNMPengine (obligatorio en la funcion)
                        CommunityData('ProyR', mpModel = 1),
                        #UsmUserData(User, authKey = AuthKy), #privkey es un valor opcional
                        UdpTransportTarget((AgentTarget,161)), #Establecer transport y target
                        ContextData(), #Contexto SNMP vacio valor default
                        ObjectType(ObjectIdentity(NomDispOID)), #ObjectIdentity aborda objetos MIB desde perspectiva humana #ObjectType objeto contenedor que referencia a instancias ObjectIdentity y SNMP
                        ObjectType(ObjectIdentity(MemoriaOID)),
                        ObjectType(ObjectIdentity(CPUOID)),
                        ObjectType(ObjectIdentity(DiscoOID)),
                        ObjectType(ObjectIdentity(AnchoTot))
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
            ArrayVarBinds.append(str(varBind))
    
    DispoName = ArrayVarBinds[0]
    Mem = ArrayVarBinds[1]
    Procesador = ArrayVarBinds[2]
    Disco = ArrayVarBinds[3]
    AnchoT = ArrayVarBinds[4]
    
    OctetoR1 = DiffInOct[0]
    OctetoT1 = DiffOutOct[0]
    OctetoR2 = DiffInOct[1]
    OctetoT2 = DiffOutOct[1]
    DatosSNMP(AgentTarget,User,AuthKy,PrivKy,NomDispOID)
    NombreDispositivo(DispoName, NomDispOID, Mem,Procesador,OctetoR1,OctetoT1,OctetoR2,OctetoT2,AnchoT,Disco,AgentTarget)
        
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

def NombreDispositivo(cadena,oid, memoria,procesador,octetoR1,octetoT1,octetoR2,octetoT2,anchoT,disco,dirip):
    #oidConsultados = [oid,cadmem,cadcpu,cadisk]
    #Establecer conexión con BD (cambiar los datos aqui por los requeridos para nuestra conexion)
    conexion = pymysql.connect(host = 'localhost',
                               user = 'root',
                               password = 'root123456',
                               database = 'SNMPDATA',
                               cursorclass = pymysql.cursors.DictCursor)

    #Evaluar el oid ingresado
    if(oid == '1.3.6.1.2.1.1.1.0'): #Oid SysDescr Obtener nombre del agente
        #Obtener el nombre del dispositivo al que se realizo la petición snmpget
        empiezasys = []
        empiezasys = cadena.split("=") #Separa la cadena en el MIB que se consulto
        quitarStringElemento = empiezasys[1].split("STRING:")
        snmpCadenaComp = quitarStringElemento[0].split("(") #Se separa la cadena para obtener unicamente el nombre del dispositivo
        limpiarGato = snmpCadenaComp[0].split("#")
        nombreDispositivo = limpiarGato[0] #Se asigna el nombre a la variable para hacer el insert en la base de datos
        print(nombreDispositivo) 
    
        #Obtener los datos de memoria
        memoria = memoria.split("=") #Separa la cadena para obtener el dato de relevancia
        RAMmem = memoria[1]
        #print(RAMmem)

        #Obtener los datos de cpu
        procesador = procesador.split("=") #Separa la cadena para obtener el dato de relevancia
        process = procesador[1]
        
        #Obtener los datos de disco
        #El dato de disco se obtiene directamente, no se necesita limpiar la cadena

        #Obtener datos para ancho de banda
        octetoR1 = octetoR1.split("=")
        octetoT1 =  octetoT1.split("=")
        octetoR2 = octetoR2.split("=")
        octetoT2 =  octetoT2.split("=")
        anchoT = anchoT.split("=")

        octR1 = octetoR1[1]
        octT1 = octetoT1[1]
        octR2 = octetoR2[1]
        octT2 = octetoT2[1]
        ancT = anchoT[1]

        AnchoB = CalcularAncho(int(octR1),int(octT1),int(octR2),int(octT2),int(ancT))
        status = 1
        #Update de la columna status.
        with conexion:
            with conexion.cursor() as mycursor:
                #Actualizar columna status para realizar un mejor trackeo
                trackstatus = "UPDATE `Datos_Dispo` SET `Status` = %s WHERE `Status` = %s"
                updatevalues = (0,1)
                mycursor.execute(trackstatus,updatevalues)
            
            conexion.commit()
        #Insert de nueva consulta de dispositivo
        
            with conexion.cursor() as cursor:
                #Crear nuevo registro de dispositivo
                register = "INSERT INTO `Datos_Dispo` (`NombreDispo`,`IPDispositivo`,`OIDConsultado`,`Memoria`,`Storage`,`CPU`,`AnchoB`,`Status`) VALUES (%s,%s,%s,%s,%s,%s,%s,%s)"
                cursor.execute(register,(nombreDispositivo,dirip,oid,RAMmem,disco,process,AnchoB,status))

                #Se usa el siguiente commit para guardar los cambios
            conexion.commit()  

def CalcularAncho(Recib1,Trans1,Recib2,Trans2,ifSpeed):
    RestaIn = Recib2 - Recib1
    RestaOut = Trans2 - Trans1

    NumSegs = (RestaIn + RestaOut)
    DivSup = NumSegs * 8 * 100
    DivInf = NumSegs * ifSpeed

    AnchoBanda = DivSup/DivInf
    print(DivSup)
    print(DivInf)
    print(AnchoBanda)
    return AnchoBanda

def DatosSNMP(IPDir,User,AuthKy,PrivKy,OIDN):
    #Establecer conexión con BD (cambiar los datos aqui por los requeridos para nuestra conexion)
    conexion = pymysql.connect(host = 'localhost',
                               user = 'root',
                               password = 'root123456',
                               database = 'SNMPDATA',
                               cursorclass = pymysql.cursors.DictCursor)

    with conexion:
            with conexion.cursor() as cursor:
                #Crear registro de la tabla de datos de snmp
                register = "INSERT INTO `Datos_SNMP` (`IPAgente`,`UserNameAgente`,`PassA`,`PassX`,`OIDaConsultar`) VALUES (%s,%s,%s,%s,%s)"
                cursor.execute(register,(IPDir,User,AuthKy,PrivKy,OIDN))

            #Se usa el siguiente commit para guardar los cambios
            conexion.commit()

user=sys.argv[1]
authk=sys.argv[2]
IPdelAgente=sys.argv[3]
for i in range(2):
    GetInOcts(OctRecib,IPdelAgente)
    GetOutOcts(OctTrans,IPdelAgente)
    time.sleep(15)#tiempo en segundos
    i = i + 1
GetFunc(user,authk,IPdelAgente,'')   
#Admin, Palabra123456,148.204.9.1 
