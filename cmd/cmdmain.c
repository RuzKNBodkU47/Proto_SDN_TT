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
#include "libred.c"
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
        printf("\n");
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

/**
 * @brief Funcion que permite hacer una consulta en la base de datos para verificar si ya existe el usuario
 * 
 * @param user parametro de tipo char* que recibe el nombre del usuario
 * @return int devuelve un valor bandera 1 si es correcto 0 si no es correcto
 */

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

/**
 * @brief Funcion que busca la contrasena en la base de datos del usuario
 * 
 * @param user parametro de tipo char* que almacena el nombre del usuario
 * @param pass parametro de tipo char* que almacena la contrasena
 * @return int devuelve una bandera para saber el status del proceso
 */


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

/**
 * @brief Funcion que nos permite obtener el id del usuario 
 * 
 * @param nomuser parametro de tipo char* que recibe el nombre del usuario
 * @return int regresa id
 */
int ObtenerIdUser(char *nomuser)
{
    int id=-1;
    char *consulta;
    ControladorBD();
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"SELECT Id_Administradores FROM Administradores WHERE Nombre_Usuario='%s';",nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    //printf("\nCOnsulta id %s",consulta);   
    while((row=mysql_fetch_row(res)) != NULL)
    {
        //printf("\nCOnsulta id %s",consulta); 
        //printf("resultado consulta: %d",atoi(row[0]));
        id=atoi(row[0]);
        /*if(strcmp(row[0],user)!=0)
            return 0;*/
    }
    //printf("\nCOnsulta id %s",consulta); 
    free(consulta);
    return id;
}
/**
 * @brief Funcion que permite buscar los permisos de los usuarios
 * 
 * @param id parametro que almacena el id del usuario
 * @return int regresa una bandera de tipo entero indicando el resultado de la operacion
 */

int BuscarPermUsers(int id)
{
    ControladorBD();
    int resultado;
    char * consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"SELECT Id_Tipo_Admin FROM Administradores WHERE Id_Administradores=%d;",id);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
     while((row=mysql_fetch_row(res)) != NULL)
    {
        resultado=atoi(row[0]);
    }
    free(consulta);
    //printf("\nresultado: %d",resultado);
    if(resultado==1)
        return 0;
    if(resultado==2 )
        return 1;
    return -2;
}
/**
 * @brief Funcion que realiza insert en los logs
 * 
 * @param Fecha parametro que recibe la fecha
 * @param id parametro que recibe el id del usuario
 * @return int 
 */
int insert_login(char* Fecha,int id)
{
    ControladorBD();
    char *consulta;
    char *IP=NULL;
    unsigned char *MAC=NULL;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    IP=ObtIp();
    MAC=ObtMAC();
    sprintf(consulta,"INSERT INTO Administradores_Tareas_Log(%s) VALUES(%d,%d,%d,'%s','%s',%d,'%s','%s');",CamposAdministradoresTareaslog,3,id,1,IP,MAC,id,Fecha,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite hacer el insert de log en la tabla de logs de las tareas
 * 
 * @param Fecha parametro que almacena la fecha
 * @param id parametro que almacena el id del usuario
 * @return int bandera del resultado de la operacion
 */
int insert_logout(char* Fecha,int id)
{
    ControladorBD();
    char *consulta;
    char *IP=NULL;
    unsigned char *MAC=NULL;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    IP=ObtIp();
    MAC=ObtMAC();
    sprintf(consulta,"INSERT INTO Administradores_Tareas_Log(%s) VALUES(%d,%d,%d,'%s','%s',%d,'%s','%s');",CamposAdministradoresTareaslog,3,id,2,IP,MAC,id,Fecha,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Insertar log de operacion correcta en creacion de nuevo administrador
 * 
 * @param id recibe el id del usuario
 * @param Fecha recibe la fecha en la que se genero el nuevo administrador
 * @return int regresa una flag de tipo entero
 */
int insert_log_user1(int id,char*Fecha)
{
    ControladorBD();
    char *consulta;
    char *IP=NULL;
    unsigned char *MAC=NULL;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    IP=ObtIp();
    MAC=ObtMAC();
    sprintf(consulta,"INSERT INTO Administradores_Tareas_Log(%s) VALUES(%d,%d,%d,'%s','%s',%d,'%s','%s');",CamposAdministradoresTareaslog,3,id,4,IP,MAC,id,Fecha,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Inserta el log de la operacion incorrecta en la creacion de nuevo administrador
 * 
 * @param id parametro que recibe el id del usuario
 * @param Fecha parametro que recibe la fecha en que se genero la falla
 * @return int flag de regreso de tipo entero.
 */
int insert_log_Euser1(int id,char*Fecha)
{
    ControladorBD();
    char *consulta;
    char *IP=NULL;
    unsigned char *MAC=NULL;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    IP=ObtIp();
    MAC=ObtMAC();
    sprintf(consulta,"INSERT INTO Administradores_Tareas_Log(%s) VALUES(%d,%d,%d,'%s','%s',%d,'%s','%s');",CamposAdministradoresTareaslog,2,id,4,IP,MAC,id,Fecha,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}