from pysnmp.hlapi import * 
#Funciones para el protocolo SNMP
import MYSQLdb
#Función get de SNMP

def GetFunc(User, AuthKy,AgentTarget,OID):
    getCommand = getCmd(SnmpEngine(), #Instancia de la clase SNMPengine (obligatorio en la funcion)
                        UsmUserData(User, authKey = AuthKy), #privkey es un valor opcional
                        UdpTransportTarget((AgentTarget,161)), #Establecer transport y target
                        ContextData(), #Contexto SNMP vacio valor default
                        ObjectType(ObjectIdentity(OID)) #ObjectIdentity aborda objetos MIB desde perspectiva humana
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
            LimpiarCadena(str(varBind))
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
def TrapFunc():
    setTrap = sendNotification(SnmpEngine(),
                               CommunityData('public', mpModel = 1),
                               Udp6TransportTarget(('demo.snmplabs.com',162)),
                               ContextData(),
                               'trap',
                               NotificationType(ObjectIdentity('IF-MIB', 'linkup'),instanceIndex=(123,))
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

def LimpiarCadena(cadena):
    #Conexion con BD
    
    empiezasys = []
    empiezasys = cadena.split(":")

    snmpCadenaComp = empiezasys[2].split(",")
    print(empiezasys[2])
    print(snmpCadenaComp)

def conectarSQL():
    #Cambiar los valores por los de nuestra BD
    try:
        db_connection = MYSQLdb.connect("Hostname","dbusername","password","dbname")
    except:
        print("Error al conectar la DB")
    
    #Crear objeto para ejecucion de query
    cursor = db_connection.cursor()

    #Ejecución de una sentencia
    cursor.execute("Poner aqui la sentencia a ejecutar")

GetFunc('Admin','Palabra123456','148.204.9.1','1.3.6.1.2.1.1.1.0')   
