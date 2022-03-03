
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
#include "mainverif.h"
#include "mainlogin.h"

int verif_tam(char * cadena )
{
    if(strlen(cadena)<8)
        return 0;
    else 
        return 1;
}

int verif_carac_num(char *cadena)
{
    
    return 1;
}

int verif_carac_let(char *cadena)
{

    return 1;
}

int verif_carac_sim(char *cadena)
{
    return 1;
}

int verif_permi_users(int id)
{
    if(BuscarPermUsers(id)>0)
        return 1;
    else
        return 0;
}
