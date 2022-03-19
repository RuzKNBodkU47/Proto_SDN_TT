
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
#define TAMPASSGEN 10
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
/**
 * @brief Funcion que genera los passwords
 * 
 * @return char* 
 */
char* Gen_Pass()
{
    int x;
    int random=0;
    char num[] = "0123456789";
    char l[] = "abcdefghijklmnoqprstuvwyzx";
    char L[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
    char sim[] = "!@#$^&*?";
    char *password;
    srand((unsigned int )( time(NULL) ));
    random = rand() % 4;
    password=(char*)malloc(sizeof(char)*TAMPASSGEN);
    if(password==NULL)
        return NULL;
    for(x=0;x<TAMPASSGEN;x++)
    {
        if(random == 1)
        {
            password[x]=num[rand()%10];
            random =rand() % 4;
        }
        else if(random ==2)
        {
            password[x]=sim[rand()%8];
            random =rand() % 4;
        }
        else if (random ==3)
        {
            password[x]=L[rand()%26];
            random =rand() % 4;
        }
        else
        {
            password[x]=l[rand()%26];
            random =rand() % 4;
        }
        
    }
    return password;
}