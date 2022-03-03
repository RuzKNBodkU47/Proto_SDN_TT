/**
 * @file libred.c
 * @author Instituto Politecnico Nacional Escuela Superior de Computo
 * @brief programa que tendra las librerias para obtener IP y MAC
 * @version 0.1
 * @date 2022-03-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "libred.h"

#define MAXIP 10
#define MAXMAC 20
char* ObtIp()
{
    char* IP;
    IP= (char*) malloc(sizeof(char)*MAXIP);
    return IP;
}



char* ObtMAC()
{
    char* MAC;
    return MAC;
}