/**
 * @file cmd_main.c
 * @author Insitituto Politecnico Nacional Escuela Superior de Computo
 * @brief programa main que se comunicara con la base de datos
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//gcc -o BDControlador 'mysql_config --cflags' cmdmain.c 'mysql_config --libs'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmdmain.h"
#include <mysql/mysql.h>

MYSQL *conexion;
MYSQL_RES *res;
MYSQL_ROW row;

#define MAXConsulta 10000

/**
 * @brief Funcion que realiza la conexion con la base de datos
 * 
 */
void ControladorBD()
{
    conexion = mysql_init(NULL);
    if(!conexion)
    {
        fprintf(stderr,"mysql_init Error\n");
        exit(1);
    }
    conexion = mysql_real_connect (conexion,servidor,user,password,database,0,NULL,0);
    if(conexion)
        printf("\nConexion Exitosa con BD");
    else 
        printf("\nError en la Conexion con BD");
}
/**
 * @brief Funcion que permite insertar administradores en la base de datos
 * 
 * @param StatusAdmin recibe el id status del adminsitrador al ser ingresado
 * @param TipAdmin recibe el id del tipo de administrador
 * @param NomAdmin recibe el nombre del administrador
 * @param ApPat recibe el apellido paterno del administrador
 * @param ApMat recibe el apellido materno del administrador
 * @param FechaIng recibe la fecha de ingreso del administrador
 * @param NomUser recibe el nombre de usuario del administrador
 * @param Pass recibe la contrasena hasheada del adminsitrador
 * @param FechaUlt la ultima fecha de modificacion de los datos del administrador
 * @param cantdias cantidad de dias limite de inactividad
 * @return int regresa un valor de tipo entero segun el resultado de la operacion
 */

int InsertAdmin(int StatusAdmin, int TipAdmin , char* NomAdmin, char* ApPat, char* ApMat, char* FechaIng, char* NomUser, char* Pass, char* FechaUlt, int cantdias)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Administradores(%s) VALUES(%d,%d,'%s','%s','%s','%s','%s','%s','%s',%d);",CamposAdministradores,StatusAdmin,TipAdmin,NomAdmin,ApPat,ApMat,FechaIng,NomUser,Pass,FechaUlt,cantdias);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    else
		printf("\nSe ingresaron los datos correctamente\n");
    free(consulta);
    return 1;   
}

int ObtenerIdUser(char *nomuser)
{
    int id=-1;
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"SELECT Id_Administradores FROM Administradores WHERE Nombre_Usuario='%s';",user);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    //printf("\nCOnsulta id %s",consulta);   
    while((row=mysql_fetch_row(res)) != NULL)
    {
        //printf("resultado consulta: %s",row[0]);
        if(strcmp(row[0],user)!=0)
            return 0;
    }
    free(consulta);
    return id;
}

int BuscarUsuario(char *user)
{
    ControladorBD();
    char* consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;  
    sprintf(consulta,"SELECT Nombre_Usuario FROM Administradores WHERE Nombre_Usuario='%s';",user);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion);   
    while((row=mysql_fetch_row(res)) != NULL)
    {
        //printf("\nresultado consulta user: %s",row[0]);
        if(strcmp(row[0],user)==0)
        {
            free(consulta);
            //printf("\nUsuario Correcto cmdmain");
            return 1;
        }   
        else
        {
            free(consulta);
            return 0;
        }
    }    
    return -1;
}




int BuscarPass(char *user,char* pass)
{
    ControladorBD();
    char* consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    
    sprintf(consulta,"SELECT Password_Hash FROM Administradores WHERE Nombre_Usuario='%s';",user);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion);  
    while((row=mysql_fetch_row(res)) != NULL)
    {  
        //printf("\nresultado consulta pass : %s",row[0]);
        if(strcmp(row[0],pass)==0)
        {
            free(consulta);
            //printf("\nContrasena correcta");
            return 1;
        }    
        else
        {
            free(consulta);
            return 0;
        }       
    }
    return -1;
}