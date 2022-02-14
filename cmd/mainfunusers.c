/**
 * @file main_fun_users.c
 * @author Insituto Politecnico Nacional ESCOM
 * @brief programa que contiene las funciones para las opciones de usuarios
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include "mainfunusers.h"
#include "cmdmain.h"
/**
 * @brief funcion para registrar usuarios
 * 
 */
int regis_user()
{
    char opc=' ';
    int whilecontrol=1;
    int x=1,y=1;
    
    int StatusAdmin;
    int TipoAdmin;
    char NombreAdmin[60];
    char ApellidOPat[60];
    char ApellidoMat[60];
    char FechaIngreso[60]=" ";
    char NomUsuario[60];
    char PassHash[60];
    char FechaUltMod[60]=" ";
    int CantDiasLimit=0;

    printf("\n==Registrando Nuevo Administrador==\n");
    while(x)
    {
        printf("\nNombre de usuario:");
        scanf("%s",NomUsuario);
    //validar que no exista el usuario en base de datos
        printf("\nNombre del administrador: ");
        scanf("%s",NombreAdmin);
        printf("\nApellido Paterno del administrador: ");
        scanf("%s",ApellidOPat);
        printf("\nApellido Materno del administrador: ");
        scanf("%s",ApellidoMat);
        printf("\nContrasena:  ");
        scanf("%s",PassHash);
        while(whilecontrol)
        {
            printf("\nTipo de nuevo Admininistrador (1.-Administrador 2.-SuperAdministrador) ");
            scanf("%d",StatusAdmin);
                switch (StatusAdmin)
                {
                    case 1: printf("\n==Usuario %s Administrador==",NomUsuario);
                        whilecontrol=0;
                    break;
                    case 2:printf("\n==Usuario %s SuperAdministrador==",NomUsuario);
                        whilecontrol=0;
                    break;
                    default:printf("\nSeleccione un tipo de administrador correcto");
                    break;
                }
        }
        whilecontrol=1;
        while(whilecontrol)
        {
            printf("\nStatus del nuevo Admininistrador (1.-Activo 2.-Inactivo) ");
            scanf("%d",StatusAdmin);
                switch (StatusAdmin)
                {
                    case 1: printf("\n==Usuario %s Activo==",NomUsuario);
                        whilecontrol=0;
                        CantDiasLimit=0;
                    break;
                    case 2:printf("\n==Usuario %s Inactivo==",NomUsuario);
                        while(y)
                        {
                            printf("Cuantos dias Inactivo (mayor a 1 dia): ");
                            scanf("%d",CantDiasLimit);
                            if(CantDiasLimit>1)
                                y=0;
                            else
                                printf("\nElija mas de 1 dia ");    
                        }
                        whilecontrol=0;
                    break;
                    default:printf("\nSeleccione un status correcto");
                    break;
                }
        }
        printf("\nVerificando datos");
        printf("\nNombre del administrador: %s",NombreAdmin);
        printf("\nApellido paterno del Administrador: %s",ApellidOPat);
        printf("\nApellido Materno del Administrador: %s",ApellidoMat);
        printf("\nNombre de Usuario: %s",NomUsuario);
        if(TipoAdmin==1)
            printf("\nTipo de Administrador: Administrador");
        else    
            printf("\nTipo de Administrador: SuperAdministrador");
        if(StatusAdmin==1)
            printf("\nStatus del usuario: Activo");
        else
            printf("\nStatus del usuario: Inactivo");
        whilecontrol=1;
        while(whilecontrol)
        {
            printf("\nDesea continuar y/n");
            switch (opc)
            {
                case 'y': whilecontrol=0;
                        printf("\nAgregando nuevo administrador..");
                    break;
                case 'n': whilecontrol=0;
                        printf("\nRegresando al inicio del formulario..");
                    break;
                default:printf("\nElija entre y/n");
                break;
            }
        }
       // FechaIngreso=" ";
       // FechaUltMod=" ";
        if(InsertAdmin(StatusAdmin,TipoAdmin,NombreAdmin,ApellidOPat,ApellidoMat,FechaIngreso,NomUsuario,PassHash,FechaUltMod,CantDiasLimit)!=1);   
            return 0;
    }  
        

    return 1;
}