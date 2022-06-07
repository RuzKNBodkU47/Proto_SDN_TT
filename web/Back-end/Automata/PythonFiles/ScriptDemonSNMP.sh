#!/bin/bash
echo $(pip install pysnmp) > /dev/null
echo $(pip install pymysql) > /dev/null
ADMINROUTER=Admin
AUTHK=Palabra123456
DIRIP0=148.204.10.1
DIRIP1=147.100.64.50
DIRIP2=147.100.64.52
DIRIP3=147.100.64.53
DIRIP4=147.100.64.54
echo "Obteniendo informacion del dispositivo $DIRIP0"
echo $(python3 SNMP_Func.py $ADMINROUTER $AUTHK $DIRIP0)

#echo "Obteniendo informacion del dispositivo $DIRIP1"
#echo $(python3 SNMP_Func.py $ADMINROUTER $AUTHK $DIRIP1)

#echo "Obteniendo informacion del dispositivo $DIRIP2"
#echo $(python3 SNMP_Func.py $ADMINROUTER $AUTHK $DIRIP2)

#echo "Obteniendo informacion del dispositivo $DIRIP3"
#echo $(python3 SNMP_Func.py $ADMINROUTER $AUTHK $DIRIP3)

#echo "Obteniendo informacion del dispositivo $DIRIP4"
#echo $(python3 SNMP_Func.py $ADMINROUTER $AUTHK $DIRIP4)