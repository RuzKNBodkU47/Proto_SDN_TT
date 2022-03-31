
/**
 * @file mainverif.c
 * @author Instituto Politecnico Nacional ESCOM
 * @brief programa que contiene las validaciones necesarias para el programa principal
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "mainverif.h"
#include "mainlogin.h"

#define TAMPASS 8

/**
 * @brief funcion que verifica que el tamano de la contrasena sea mayor a 8 caracteres
 * 
 * @param cadena 
 * @return int 
 */
int verif_tam(char * cadena )
{
    if(strlen(cadena)<TAMPASS)
        return 0;
    else 
        return 1;
}
/**
 * @brief funcion que verifica que en la contrasena exista numeros
 * 
 * @param cadena 
 * @return int 
 */
int verif_carac_num(char *cadena)
{
    int x,cont=0;
    for(x=0;x<strlen(cadena);x++)
        if(cadena[x]>47 && cadena[x]<58)
            cont++;
    if(cont==0)
        return 0;
    return 1;
}
/**
 * @brief funcion que verifica que tenga letras minusculas
 * 
 * @param cadena 
 * @return int 
 */
int verif_carac_let(char *cadena)
{
    int x,cont=0;
    for(x=0;x<strlen(cadena);x++)
        if(cadena[x]>96 && cadena[x]<123)
            cont++;
    if(cont==0)
        return 0;
    return 1;
}
/**
 * @brief funcion que verifica que tenga letras en mayusculas
 * 
 * @param cadena 
 * @return int 
 */
int verif_carac_letM(char* cadena)
{
    int x,cont=0;
    for(x=0;x<strlen(cadena);x++)
        if(cadena[x]>64 && cadena[x]<91)
            cont++;
    if(cont==0)
        return 0;
    return 1;
}
/**
 * @brief funcion que verifica que existan simbolos en la contrasena
 * 
 * @param cadena 
 * @return int 
 */
int verif_carac_sim(char *cadena)
{
    int x,cont=0;
    for(x=0;x<strlen(cadena);x++)
        if(cadena[x]>32 && cadena[x]<48 || cadena[x]>57 && cadena[x]<65 || cadena[x]>122 && cadena[x]<128) 
            cont++;
    if(cont==0)
        return 0;
    return 1;
}
/**
 * @brief funcion que verifica los permisos de los usuarios
 * 
 * @param id 
 * @return int 
 */
int verif_permi_users(int id)
{
    if(BuscarPermUsers(id)>0)
        return 1;
    else
        return 0;
}