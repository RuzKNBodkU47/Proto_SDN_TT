/**
 * @file mainconfig.c
 * @author Insitituto Politecnico Nacional ESCOM
 * @brief archivo con las funciones para la configuracion de los equipos de red.
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "mainconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int config_router()
{

    int session=1,opc=-1;
    printf("\n<-- Entrando a Menu de configuracion de servidores -->\n");
    while(session)
    {
        menu_router();
        scanf("%d",&opc);
        switch (opc)
        {
        case 0:opc=0;
            printf("\nSaliendo de las opciones de configuracion de servidor");
            break;    
        case 1:printf("\n<<-- Protocolo de Enrutamiento OSPF -->>");
            break;
        case 2:printf("\n<<-- Protocolo de Enrutamiento EIGRP -->>");
            break;
        case 3:printf("\n<<-- Protocolo de Enrutamiento RIP -->>");
            break;
        case 4:printf("\n<<-- Protocolo de Enrutamiento SNMP -->>");
            break;
        case 5:printf("\n<<-- Protocolo de Enrutamiento VLAN -->>");
            break;
        default: printf("\nError en la opcion elegida. \nEscoja una correcta opcion.");
            break;
        }
    }
    return 1;
}

int config_switch()
{
    return 1;
}

int config_server()
{
    int session=1,opc=-1;
    printf("\n<-- Entrando a Menu de configuracion de servidores -->\n");
    while(session)
    {
        menu_server();
        scanf("%d",&opc);
        switch (opc)
        {
        case 0:opc=0;
            printf("\nSaliendo de las opciones de configuracion de servidor");
            break;    
        case 1:printf("\n<<-- Servicio de Almacenamiento -->>");
            break;
        case 2:printf("\n<<-- Balanceo de Cargas -->>");
            break;
        case 3:printf("\n<<-- Servicio Web php -->>");
            break;
        case 4:printf("\n<<-- Servicio Web Django -->>");
            break;
        case 5:printf("\n<<-- Servicio Web Apache -->>");
            break; 
        case 6:printf("\n<<-- Base de Datos -->>");
            break; 
        case 7:printf("\n<<-- Servicio DNS -->>");
            break;
        case 8:printf("\n<<-- Servicio VPN -->>");
            break;  
        default: printf("\nError en la opcion elegida. \nEscoja una correcta opcion.");
            break;
        }
    }
    return 1;
}

void menu_server()
{
    printf("\n1.Servicio de Almacenaiento.");
    printf("\n2.Balanceo de Cargas.");
    printf("\n3.Servicio Web php.");
    printf("\n4.Servicio Web Django.");
    printf("\n5.Servicio Web Apache.");
    printf("\n6.Servicio Base de Datos.");
    printf("\n7.Servicio de DNS.");
    printf("\n8.Servicio de VPN.");
    printf("\n0.Salir");
}

void menu_router()
{
    printf("\n1.Protocolo de Enrutamiento OSPF.");
    printf("\n2.Protocolo de Enrutamiento EIGRP.");
    printf("\n3.Protocolo de Enrutamiento RIP.");
    printf("\n4.Protocolo de Enrutamiento SNMP.");
    printf("\n5.Protocolo de Enrutamiento VLAN.");
    printf("\n0.Salir.");
}

void menu_switch()
{
    printf("\n1.Protocolo de Enrutamiento OSPF.");
    printf("\n2.Protocolo de Enrutamiento EIGRP.");
    printf("\n3.Protocolo de Enrutamiento RIP.");
    printf("\n4.Protocolo de Enrutamiento SNMP.");
    printf("\n5.Protocolo de Enrutamiento VLAN.");
    printf("\n0.Salir.");
}