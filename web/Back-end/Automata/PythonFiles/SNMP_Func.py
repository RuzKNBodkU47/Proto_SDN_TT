from pysnmp.hlapi import * 
#Funciones para el protocolo SNMP

#Función get de SNMP

def GetFunc():
    getCommand = getCmd(SnmpEngine(), #Instancia de la clase SNMPengine (obligatorio en la funcion)
                        CommunityData('public', mpModel = 1), #Eleccion de version mpModel = 0 es para SNMP version 1, mpModel = 1 es para version 2c
                        UdpTransportTarget(('demo.snmplabs.com',200)), #Establecer transport y target
                        ContextData(), #Contexto SNMP vacio valor default
                        ObjectType(ObjectIdentity('SNMPv2-MIB','sysDescr',0)) #ObjectIdentity aborda objetos MIB desde perspectiva humana
                                                                              #ObjectType objeto contenedor que referencia a instancias ObjectIdentity y SNMP
                        ) 


    errorIndication, errorStatus, errorIndex, varBinds = next(getCommand)

    if errorIndication:
        print(errorIndication)

    elif errorStatus:
        print('%s at %s' % (errorStatus.prettyPrint(),
                        errorIndex and varBinds[int(errorIndex) - 1][0] or '?'))

    else:
        for varBind in varBinds:
            print(' = '.join([x.prettyPrint() for x in varBind]))
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
    
GetFunc()
