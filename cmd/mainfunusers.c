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
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "mainfunusers.h"
#include "cmdmain.c"
#include "mainverif.h"

#define CANTTAREAS 10
#define CANTSERVICIOS 6


char FechaFunUser[70]="";

/**
 * @brief funcion para registrar usuarios
 * 
 */
int regis_user()
{
    int opc=0;
    int whilecontrol=1;
    int x=1,y=1,z=1;
    int cont=0;
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
        
        while(z)
        {
            printf("\nNombre de usuario:");
            scanf("%s",NomUsuario);
            if(validaruser(NomUsuario)!=1)
            {
                printf("\nEste Usuario ya existe.");
                cont++;
                if(cont>3)
                {
                    printf("\n3 Errores Regresando Al menu.");
                    return -4;
                }
            }
            else
            {
                z=0;
            }    
                
        }
        printf("\nNombre del administrador: ");
        scanf("%s",NombreAdmin);
        printf("\nApellido Paterno del administrador: ");
        scanf("%s",ApellidoPat);
        printf("\nApellido Materno del administrador: ");
        scanf("%s",ApellidoMat);
        strcpy(PassHash,Gen_Pass);
        printf("\nContrasena: %s \n==FAVOR DE GUARDAR ESTA CONTRASENA Y DESPUES CAMBIARLA==",PassHash);
        
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
    if(RegistrarFuncionesUser(ObtenerIdUser(NomUsuario)) == 1)
        printf("\nTodas los permisos fueron agregadas exitosamente.");
    else
        printf("\nNo todas los permisos se agregaron completamente");
    return 1;
}
/**
 * @brief Funcion que permite modificar la informacion de los usuarios 
 * 
 * @return int 
 */
int ModificarUser(int flag)
{
    int opc=1,sw=-1,extra=0;
    char NomUser[50];
    int x=1,scan=0;
    char respstring[60];
    char pass[60];
    printf("\n==Modificando Adminsitrador==\n");
    printf("\nIngrese el nombre de usuario a modificar: ");
    scanf("%s",NomUser);
    //obtener id del nombre del usuario
    //if(id_user=ObtenerIdUser(NomUser)== -1)
      //  return 0;
    //printf("\nflag %d ",flag);
    if(verifexistuser(NomUser)!=1)
    {
        printf("\nUser no existe.");
        return -3;
    }    

    if(flag==1)
    {
        printf("\nModificar informacion del usuario\nMostrando informacion del usuario %s ",NomUser);   
        if(imprimir_infouser(NomUser) != 1)
            printf("\nError en la busqueda del usuario");            
        printf("\n============================\n");
        while(opc)
        {
            menuflag1();
            scanf("%d",&sw);
            x=1;
            switch (sw)
            {
            case 1:printf("\nModificar Status del administrador.");
                while(x)
                {
                    printf("\nOpciones:\n1.Activo\n2.Fuera del Sistema\n3.Fuera del Sistema\nElija una opcion: ");
                    scanf("%d",&scan);
                    if(scan>0 && scan<4)
                    {
                        x=0;
                        if(Actualizar_StatusAdmin(NomUser,scan)!=1)
                        {
                            printf("\nError al actualizar el dato.");
                            x=0;
                        }
                    }
                    else
                        printf("\nError elija una opcion correcta.");                 
                }
                break;
            case 2:printf("\nModificar Tipo de administrador.");
                while(x)
                {
                    printf("\nOpciones:\n1.Administrador\n2.SuperAdministrador\nElija una opcion: ");
                    scanf("%d",&scan);
                    if(scan>0 && scan<3)
                    {
                        x=0;
                        if(Actualizar_TipoAdmin(NomUser,scan)!=1)
                        {
                            printf("\nError al actualizar el dato");
                            x=0;
                        }
                    }
                    else
                        printf("\nError elija una opcion correcta.");                 
                }
                break;
            case 3:printf("\nModificar Nombre del administrador.");
                while(x)
                {
                    printf("\nIngrese el nuevo nombre del usuario %s: ",NomUser);
                    scanf("%s",respstring);
                    if (strlen(respstring) > 0 )
                    {
                        printf("\nConfirma que el nuevo nombre del usuario %s sea %s \n(1.Si / 2.No) ",NomUser,respstring);
                        scanf("%d",&extra);
                        switch (extra)
                        {
                        case 1: x=0;
                            if(Actualizar_NombreAdmin(NomUser,respstring)!=1)
                            {
                                printf("\nError al actualizar el dato..");
                                x=0;
                            }
                            break;
                        case 2: printf("\nRegresando..");
                            break;
                        default:printf("\nError..");
                            break;
                        }
                    }
                    else
                    {
                        printf("\nIngrese una cadena.");
                    }
                }
                break;
            case 4:printf("\nModificar Apellido Paterno del administrador.");
                while(x)
                {
                    printf("\nIngrese el nuevo Apellido Paterno del usuario %s",NomUser);
                    scanf("%s",respstring);
                    if (strlen(respstring) > 0 )
                    {
                        printf("\nConfirma que el nuevo Apellido Paterno del usuario %s sea %s \n(1.Si / 2.No)",NomUser,respstring);
                        scanf("%d",&extra);
                        switch (extra)
                        {
                        case 1: x=0;
                            if(Actualizar_APAdmin(NomUser,respstring)!=1)
                            {
                                printf("\nError al actualizar el dato..");
                                x=0;
                            }
                            break;
                        case 2: printf("\nRegresando..");
                            break;
                        default:printf("\nError..");
                            break;
                        }
                    }
                    else
                    {
                        printf("\nIngrese una cadena.");
                    }
                }
                break;
            case 5:printf("\nModificar Apellido Materno del administrador.");
            while(x)
                {
                    printf("\nIngrese el nuevo Apellido Materno del usuario %s",NomUser);
                    scanf("%s",respstring);
                    if (strlen(respstring) > 0 )
                    {
                        printf("\nConfirma que el nuevo Apellido Materno del usuario %s sea %s \n(1.Si / 2.No)",NomUser,respstring);
                        scanf("%d",&extra);
                        switch (extra)
                        {
                        case 1: x=0;
                            if(Actualizar_AMAdmin(NomUser,respstring)!=1)
                            {
                                printf("\nError al actualizar el dato..");
                                x=0;
                            }
                            break;
                        case 2: printf("\nRegresando..");
                            break;
                        default:printf("\nError..");
                            break;
                        }
                    }
                    else
                    {
                        printf("\nIngrese una cadena.");
                    }
                }
                break;
            case 6:printf("\nModificar Nombre de usuario del administrador.");
            while(x)
                {
                    printf("\nIngrese el nuevo Nombre de usuario para el usuario %s: ",NomUser);
                    scanf("%s",respstring);
                    if (strlen(respstring) > 0 )
                    {
                        printf("\nConfirma que el nuevo Nombre de usuario del usuario %s sea %s \n(1.Si / 2.No)\t",NomUser,respstring);
                        scanf("%d",&extra);
                        switch (extra)
                        {
                        case 1: x=0;
                            if(Actualizar_NomUser(NomUser,respstring)!=1)
                            {
                                printf("\nError al actualizar el dato..");
                                x=0;
                            }
                            break;
                        case 2: printf("\nRegresando..");
                            break;
                        default:printf("\nError..");
                            break;
                        }
                    }
                    else
                    {
                        printf("\nIngrese una cadena.");
                    }
                }
                break;
            case 7:printf("\nModificar Contrasena del administrador.");
                strcpy(pass,Gen_Pass);
                printf("\n Nueva Contrasena: %s\nFAVOR DE GUARDAR ESTA CONTRASENA Y DESPUES CAMBIARLA",pass);
                break;
            case 8:printf("\nSaliendo del menu.");
                opc=0;
                break;    
            default:printf("\nElija una opcion correcta.");
                break;
            }
        }

    }
    if(flag==2)
    {
        printf("Modificar permisos del usuario\n Mostrando informacion del usuario %s",NomUser);
        if(imprimir_permisotareas(NomUser) != 1)
            printf("\nError en la busqueda del usuario");
        printf("\n============================\n");
        if(imprimir_permisoServicios(NomUser) != 1)
            printf("\nError en la busqueda del usuario");
        printf("\n============================\n");
        //mostrar permisos del usuario
        while(opc)
        {
            menuflag2();
            scanf("%d",&sw);
            x=1;
            extra=0;
            switch (sw)
            {
            case 1:printf("\nAgregar nuevos Administradores.");
                while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiTarea(4,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiTarea(4,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }        
                break;
            case 2:printf("\nModificar informacion de Administradores.");
                 while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiTarea(5,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiTarea(5,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }
                break;
            case 3:printf("\nEliminar Administradores del sistema.");
             while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiTarea(6,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiTarea(6,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }
                break;
            case 4:printf("\nAgregar Privilegios a Administradores.");
                 while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiTarea(8,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiTarea(8,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }
                break;
            case 5:printf("\nEliminar Privilegios a Administradores.");
             while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiTarea(7,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiTarea(7,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }
                break;
            case 6:printf("\nMonitorizacion.");
                while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiServicio(1,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiServicio(1,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }
                break;
            case 7:printf("\nConfiguracion de Router.");
                while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiServicio(2,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiServicio(2,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }
                break;
            case 8:printf("\nConfiguracion de Switch.");
            while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiServicio(3,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiServicio(3,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }
                break;
            case 9:printf("\nConfiguracion de Servidor.");
                while (x)
                {
                    printf("\nDesea Agregar o Eliminar este permiso del usuario %s (1.Agregar / 2.Eliminar /3.Salir): ",NomUser);
                    scanf("%d",&extra);
                    switch (extra)
                    {
                    case 1:printf("\nAgregando permiso");
                        obfecha();
                        if(verif_existpermiServicio(4,NomUser,FechaFunUser)!=1)
                        {
                            printf("\nEste usuario ya tiene este permiso.");
                            x=0;
                        }
                        else
                        {
                            printf("\nExito al agregar este permiso..");
                            x=0;
                        }
                        break;
                    
                    case 2:printf("\nEliminando permiso");
                        if(Elim_permiServicio(4,NomUser)==1)
                        {
                            printf("\nPermiso Eliminado con exito.");
                            x=0;
                        }
                        else
                        {
                            printf("\nPermiso Eliminado sin exito.");
                            x=0;
                        }
                        break;
                    
                    case 3:printf("\nSaliendo..");
                        x=1;
                        break;
                    default:printf("\nError en las opciones.");
                        break;
                    }
                }
                break;
            case 10:printf("\nSaliendo del menu.");
                opc=0;
                break;    
            default:printf("\nElija una opcion correcta.");
                break;
            }
        }
    }

    return 1;
}
/**
 * @brief Funcion que agrega permisos a las tareas y los servicios a un usuario
 * 
 * @param IdUser parametro que recibe el id del usuario
 * @return int 
 */
int RegistrarFuncionesUser(int IdUser)
{
    //int opc=0;
    printf("\nId del usuario. %d",IdUser);
    printf("\nAsignar Permisos al Nuevo Usuario");
    if(ModificarPermisosTareas(IdUser)!=0)
        printf("\nPermisos de Tareas Agregados Exitosamente.");
    else 
    {
        printf("\nPermisos de Tareas No se Agregaron Existosamente.");
        return 0;
    }
    if(ModificarPermisosServicios(IdUser)!=0)
        printf("\nPermisos de Servicios Agregados Exitosamente. ");
    else
    {
        printf("\nPermisos de Servicios No se Agregados Exitosamente. ");
        return 0;
    }
        
    return 1;
}
/**
 * @brief Funcion que permite modificar los permisos de los usuarios con las tareas
 * 
 * @param IdUser parametro que recibe el Id del usuario
 * @return int 
 */
int ModificarPermisosTareas(int IdUser)
{
    int* respuesta;
    int opcfinal=0;
    respuesta = (int *)malloc(sizeof(int)*CANTTAREAS);
    if(respuesta ==NULL)
        return -1;
    int indice=1;
    int global=1;
    while(global)
    {
        printf("\n<-- Tareas -->\n");
    while(indice)
    {
        printf("\n[ ]Agregar nuevos Administradores (1. si / 2. no ): ");
        scanf("%d",&respuesta[0]);
        if(respuesta[0] != 1 && respuesta[0] !=2)
            printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    indice = 1;
    while(indice)
    {
        printf("\n[ ]Modificar informacion de Administradores (1. si / 2. no ): ");
        scanf("%d",&respuesta[1]);
        if(respuesta[1] != 1 && respuesta[1] != 2)
         printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    indice=1;
    while(indice)
    {
        printf("\n[ ]Eliminar Administradores del sistema (1. si / 2. no ): ");
        scanf("%d",&respuesta[2]);
        if(respuesta[2] != 1 && respuesta[2] != 2)
         printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    indice=1;
    while(indice)
    {
        printf("\n[ ]Agregar Privilegios a Administradores (1. si / 2. no ): ");
        scanf("%d",&respuesta[3]);
        if(respuesta[3] != 1 && respuesta[3] != 2)
         printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    indice=1;
    while(indice)
    {
        printf("\n[ ]Eliminar Privilegios a Administradores (1. si / 2. no ): ");
        scanf("%d",&respuesta[4]);
        if(respuesta[4] != 1 && respuesta[4] != 2)
         printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    printf("\nConfirmando Opciones");
    if(respuesta[0]==1)
        printf("\n[X]Agregar nuevos Administradores");
    else if (respuesta[0]==2)
        printf("\n[ ]Agregar nuevos Administradores");
    
    if(respuesta[1]==1)
        printf("\n[X]Modificar informacion de Administradores");
    else if (respuesta[1]==2)
        printf("\n[ ]Modificar informacion de Administradores");
    
    if(respuesta[2]==1)
        printf("\n[X]Eliminar Administradores del sistema");
    else if (respuesta[2]==2)
        printf("\n[ ]Eliminar Administradores del sistema");
    if(respuesta[3]==1)
        printf("\n[X]Agregar Privilegios a Administradores");
    else if (respuesta[3]==2)
        printf("\n[ ]Agregar Privilegios a Administradores");
    if(respuesta[4]==1)
        printf("\n[X]Eliminar Privilegios a Administradores");
    else if (respuesta[4]==2)
        printf("\n[ ]Eliminar Privilegios a Administradores");

    printf("\nDesea Continuar ( 1 si / 2 no)");
    scanf("%d",&opcfinal);
    if(opcfinal==1)
        global=0;
    else if(opcfinal==0)
        global=1;
    else
        printf("\nEscoja entre 1 para continuar o 2 para comenzar de nuevo.");
    }
    obfecha();
    if(respuesta[0]==1)
        InsertarPermisosAgregarAdmin(IdUser,FechaFunUser);
    obfecha();
    if(respuesta[1]==1)
        InsertarPermisosModifAdmin(IdUser,FechaFunUser);
    obfecha();
    if(respuesta[2]==1)
        InsertarPermisosElimAdmin(IdUser,FechaFunUser);
    obfecha();
    if(respuesta[3]==1)
        InsertarPermisosAgrgAdmin(IdUser,FechaFunUser);
    obfecha();
    if(respuesta[4]==1)
        InsertarPermisosElimAgrgAdmin(IdUser,FechaFunUser);
    return 1;
}
/**
 * @brief Funcion que permite modificar los permisos de los usuarios con los servicios
 * 
 * @param IdUser parametro que recibe el Id del usuario
 * @return int 
 */
int ModificarPermisosServicios(int IdUser)
{
    int* respuesta;
    int opcfinal=0;
    respuesta = (int *)malloc(sizeof(int)*CANTSERVICIOS);
    if(respuesta ==NULL)
        return -1;
    int indice=1;
    int global=1;
    while(global)
    {
        printf("\n<-- Servicios -->\n");
    while(indice)
    {
        printf("\n[ ] Monitorizacion (1. si / 2. no ): ");
        scanf("%d",&respuesta[0]);
        if(respuesta[0] != 1 && respuesta[0] !=2)
            printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    indice = 1;
    while(indice)
    {
        printf("\n[ ] Configuracion de Router (1. si / 2. no ): ");
        scanf("%d",&respuesta[1]);
        if(respuesta[1] != 1 && respuesta[1] != 2)
         printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    indice=1;
    while(indice)
    {
        printf("\n[ ] Configuracion de Switch (1. si / 2. no ): ");
        scanf("%d",&respuesta[2]);
        if(respuesta[2] != 1 && respuesta[2] != 2)
         printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    indice=1;
    while(indice)
    {
        printf("\n[ ] Configuracion de Servidor (1. si / 2. no ): ");
        scanf("%d",&respuesta[3]);
        if(respuesta[3] != 1 && respuesta[3] != 2)
         printf("\nEscoja entre 1 para si o 2 para no");
        else
            indice=0;
    }
    printf("\nConfirmando Opciones");
    if(respuesta[0]==1)
        printf("\n[X]Monitorizacion");
    else if (respuesta[0]==2)
        printf("\n[ ]Monitorizacion");
    
    if(respuesta[1]==1)
        printf("\n[X]Configuracion de Router");
    else if (respuesta[1]==2)
        printf("\n[ ]Configuracion de Router");
    
    if(respuesta[2]==1)
        printf("\n[X]Configuracion de Switch");
    else if (respuesta[2]==2)
        printf("\n[ ]Configuracion de Switch");
    if(respuesta[3]==1)
        printf("\n[X]Configuracion de Servidor");
    else if (respuesta[3]==2)
        printf("\n[ ]Configuracion de Servidor");
    printf("\nDesea Continuar ( 1 si / 2 no)");
    scanf("%d",&opcfinal);
    if(opcfinal==1)
        global=0;
    else if(opcfinal==0)
        global=1;
    else
        printf("\nEscoja entre 1 para continuar o 2 para comenzar de nuevo.");
    }
    obfecha();
    if(respuesta[0]==1)
        InsertarPermisosServMonit(IdUser,FechaFunUser);
    obfecha();
    if(respuesta[1]==1)
        InsertarPermisosServRouter(IdUser,FechaFunUser);
    obfecha();
    if(respuesta[2]==1)
        InsertarPermisosServSwitch(IdUser,FechaFunUser);
    obfecha();
    if(respuesta[3]==1)
        InsertarPermisosServSevidor(IdUser,FechaFunUser);
    return 1;
}
/**
 * @brief funcion que obtiene la fecha del sistema
 * 
 * @return int regresa una flag del estado de la operacion
 */
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
/**
 * @brief Funcion que imprime el menu
 * 
 */
void menuflag1()
{
    printf("\nMenu de modificacion de informacion.");
    printf("\n1.Status del usuario.");
    printf("\n2.Tipo de Usuario.");
    printf("\n3.Nombre del administrador.");
    printf("\n4.Apellido Paterno del administrador.");
    printf("\n5.Apellido Materno del administrador.");
    printf("\n6.Nombre de usuario de acceso.");
    printf("\n7.Contrasena de acceso.");
    printf("\n8.Salir del Menu.");
    printf("\nElija una opcion: ");
}
/**
 * @brief Funcion que imprime el menu
 * 
 */
void menuflag2()
{
    printf("\nMenu de modificacion de Permisos.");
    printf("\n1.Agregar nuevos Administradores.");
    printf("\n2.Modificar informacion de Administradores.");
    printf("\n3.Eliminar Administradores del sistema.");
    printf("\n4.Agregar Privilegios a Administradores.");
    printf("\n5.Eliminar Privilegios a Administradores.");
    printf("\n6.Monitorizacion.");
    printf("\n7.Configuracion de Router.");
    printf("\n8.Configuracion de Switch.");
    printf("\n9.Configuracion de Servidor.");
    printf("\n10.Salir del Menu.");
    printf("\nElija el permiso que quiera agregar/eliminar: ");
}
/**
 * @brief Funcion que permite poner el status del usuario en fuera del sistema por lo que estaria dado de baja.
 * 
 * @return int 
 */
int EliminarUsers()
{
    char nomuser[50];
    printf("\nEliminar Administradores\nIngrese el Nombre del usuario a Eliminar del sistema: ");
    scanf("%s",nomuser);
    if(Elimuser(nomuser)!=1)
        return 0;
    return 1;
}
/**
 * @brief Funcion que muestra todos los administradores en la base de datos.
 * 
 * @return int 
 */
int ListarAdministradores()
{
    printf("\nListando los administradores\n\n");
    if(listar_usuarios()!=1)
        return 0;
    return 1;
}
/**
 * @brief Funcion que muestra el menu de la modificacion de informacion
 * 
 */
void menuuserdata()
{
    printf("\nMenu de modificacion de informacion.");
    printf("\n1.Nombre del administrador.");
    printf("\n2.Apellido Paterno del administrador.");
    printf("\n3.Apellido Materno del administrador.");
    printf("\n4.Salir del Menu.");
    printf("\nElija una opcion: ");
}
/**
 * @brief Funcion que modifica la informacion del usuario actual
 * 
 * @param user parametro que recibe el id del usuario
 * @return int 
 */
int usermoddata(int user)
{
    int indice=1;
    int opc=-1;
    char valor[50];
    while(indice)
    {
        menuuserdata();
        scanf("%d",&opc);
        switch (opc)
        {
        case 1:printf("\nCambiar Nombre del Administrador.\nIngrese el nuevo nombre: ");
            scanf("%s",valor);
            if(UpdateData(1,user,valor)!=1)
                return 0;
            break;
        case 2:printf("\nCambiar Apellido Paterno del Administrador.\nIngrese el nuevo Apellido Paterno: ");
            scanf("%s",valor);
            if(UpdateData(2,user,valor)!=1)
                return 0;
            break;
        case 3:printf("\nCambiar Apellido Materno del Administrador.\nIngrese el nuevo Apellido Materno: ");
            scanf("%s",valor);
            if(UpdateData(3,user,valor)!=1)
                return 0;
            break;
        case 4:printf("\nSaliendo..");
            indice=0;
            break;    
        default:printf("\nError en las opciones..");
            break;
        }
    }
    return 1;
}
/**
 * @brief Funcion que cambia la contrasena del usuario actual
 * 
 * @param user parametro que recibe el id del usuario
 * @return int 
 */
int usermodpass(int user)
{
    char pass[50];
    return 1;
}