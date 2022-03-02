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
#include <time.h>
#include <string.h>

#include "mainfunusers.h"
#include "cmdmain.c"

char FechaFunUser[70]="";

/**
 * @brief funcion para registrar usuarios
 * 
 */
int regis_user()
{
    int opc=0;
    int whilecontrol=1;
    int x=1,y=1;
    
    int StatusAdmin;
    int TipoAdmin=-1;
    char NombreAdmin[60];
    char ApellidoPat[60];
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
        scanf("%s",ApellidoPat);
        printf("\nApellido Materno del administrador: ");
        scanf("%s",ApellidoMat);
        printf("\nContrasena:  ");
        scanf("%s",PassHash);
        while(whilecontrol)
        {
            printf("\nTipo de nuevo Admininistrador (1.-Administrador 2.-SuperAdministrador): ");
            scanf("%d",&opc);
                switch (opc)
                {
                    case 1: printf("\n==Usuario %s Administrador==",NomUsuario);
                        TipoAdmin=1;
                        whilecontrol=0;
                    break;
                    case 2:printf("\n==Usuario %s SuperAdministrador==",NomUsuario);
                        TipoAdmin=2;
                        whilecontrol=0;
                    break;
                    default:printf("\nSeleccione un tipo de administrador correcto");
                    break;
                }
        }
        whilecontrol=1;
        opc=0;
        while(whilecontrol)
        {
            printf("\nStatus del nuevo Admininistrador (1.-Activo 2.-Inactivo): ");
            scanf("%d",&opc);
                switch (opc)
                {
                    case 1: printf("\n==Usuario %s Activo==",NomUsuario);
                        StatusAdmin=1;
                        whilecontrol=0;
                        CantDiasLimit=0;
                    break;
                    case 2:printf("\n==Usuario %s Inactivo==",NomUsuario);
                        StatusAdmin=2;
                        while(y)
                        {
                            printf("Cuantos dias Inactivo (mayor a 1 dia): ");
                            scanf("%d",&CantDiasLimit);
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
        opc=0;
        printf("\n\nVerificando datos");
        printf("\nNombre del administrador: %s",NombreAdmin);
        printf("\nApellido paterno del Administrador: %s",ApellidoPat);
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
            //probar si se puede tomar el valor ascii de y / n
            printf("\nDesea continuar 1-si , 2-no: ");
            scanf("%d",&opc);
            switch(opc)
            {
                case 1: printf("\nAgregando nuevo administrador..");
                        whilecontrol=0;
                        x=0;
                    break;
                case 2: whilecontrol=0;
                        x=1;
                        printf("\nRegresando al inicio del formulario..");
                    break;
                default:printf("\nElija entre valores entre si y no");
                break;
            }
        }
      
       
    } 
    if(obfecha()==0)
        printf("\nError con la fecha");
    strcpy(FechaIngreso,FechaFunUser);
    strcpy(FechaUltMod,FechaFunUser);
    if(InsertAdmin(StatusAdmin,TipoAdmin,NombreAdmin,ApellidoPat,ApellidoMat,FechaIngreso,NomUsuario,PassHash,FechaUltMod,CantDiasLimit)!=1)   
    {
        printf("\nError de MYSQL en insert de nuevo administrador");
        return 0;
    } 
    //registrar los permisos del usuario
    RegistrarFuncionesUser(ObtenerIdUser(NomUsuario));
    return 1;
}
/**
 * @brief Funcion que permite modificar la informacion de los usuarios 
 * 
 * @return int 
 */
int ModificarUser(int flag)
{
    //int id_user=-1;
    char NomUser[50];
    printf("\n==Modificando Adminsitrador==\n");
    printf("\nIngrese el nombre de usuario a modificar: ");
    scanf("%s",NomUser);
    //obtener id del nombre del usuario
    if(flag==1)
    {
        printf("Modificar informacion del usuario");   
        //mostrar informacion del usuario
        

    }
    if(flag==2)
    {
        printf("Modificar permisos del usuario");
        //mostrar permisos del usuario

    }

    return 1;
}

int RegistrarFuncionesUser(int IdUser)
{
    //int opc=0;
    printf("\nFunciones permitidas");
    return 1;
}

int obfecha()
{
    // Tiempo actual
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    //char fechaHora[70];
    char *formato = "%Y-%m-%d %H:%M:%S";
    // Intentar formatear
    int bytesEscritos = strftime(FechaFunUser, sizeof(FechaFunUser), formato, &tiempoLocal);
     if (bytesEscritos != 0) 
    {
        // Si no hay error, los bytesEscritos no son 0
        return 1;
    } 
    else 
    {
        printf("\nError formateando fecha\n");
        return 0;
    }
}