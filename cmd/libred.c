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

/**
 * @brief Funcion que obtiene la IP del equipo
 * 
 * @return char* regresa la IP
 */

char* ObtIp()
{
    char* IP;
    IP= (char*) malloc(sizeof(char)*MAXIP);
    int inet_sock;
    struct ifreq ifr;
    inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, "eno1");//cambiar la interfaz de red a la correspondiente en el equipo
    if (ioctl(inet_sock, SIOCGIFADDR, &ifr) <  0)
        perror("ioctl");
    sprintf(IP,"%s", inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
    close(inet_sock);
    return IP;
}



unsigned char* ObtMAC()
{
    unsigned char* MAC=NULL;
    unsigned char submac[10]=" ";
    MAC= (char*) malloc(sizeof(char)*MAXMAC);
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    strcpy(s.ifr_name, "eno1");
    memset(MAC,0,MAXMAC);
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) 
    {
        int i;
        for (i = 0; i < 6; ++i)
        {
            sprintf(submac,"%02X", (unsigned char) s.ifr_addr.sa_data[i]);
            strcat(MAC,submac);
            if(i<5)
                strcat(MAC,":");
        }        
    }
    close(fd);
    return MAC;
}