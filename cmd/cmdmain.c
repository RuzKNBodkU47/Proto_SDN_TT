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
/**
 * @brief funcion que imprime la informacion guardada del usuario
 * 
 * @param id entra el id del usuario
 */
int imprimir_infouser(char * nomuser)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"SELECT %s FROM Administradores WHERE Nombre_Usuario='%s';",CamposAdministradores,nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    //int cant_campos = mysql_num_fields(res);
    while((row=mysql_fetch_row(res)) != NULL)
    {
        if(atoi(row[0]) == 1)
            printf("\nStatus del usuario: Activo");
        else if (atoi(row[0]) == 2)
            printf("\nStatus del usuario: Inactivo");
        else
            printf("\nStatus del usuario: Fuera del Sistema");
        
        if(atoi(row[1]) == 1)
            printf("\nTipo de administrador: Administrador");
        else
            printf("\nTipo de administrado: SuperAdministrador");
        
        printf("\nNombre del administrador: %s",row[2]);
        printf("\nApellido Paterno del administrador: %s",row[3]);
        printf("\nApellido Materno del administrador: %s",row[4]);
        printf("\nFecha de ingreso al sistema: %s",row[5]);
        printf("\nNombre de usuario de acceso: %s",row[6]);
        printf("\nFecha de ultimo cambio de contrasena: %s",row[8]);
    }
    free(consulta);
    return 1;
}
/**
 * @brief Funcion que permite imprimir los permisos que tiene permitido el usuario
 * 
 * @param nomuser parametro que recibe el nombre del usuario
 * @return int 
 */
int imprimir_permisotareas(char * nomuser)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    int id_user= ObtenerIdUser(nomuser);
    //printf("\nid del usuario: %d",id_user);
    sprintf(consulta,"SELECT %s FROM Tipo_Admin_Cat_Tareas WHERE Id_Administrador=%d;",CamposTipoAdminCatTareas,id_user);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    //int cant_campos = mysql_num_fields(res);
    printf("\nPermisos de Tareas Activos en el usuario %s",nomuser);
    while((row=mysql_fetch_row(res)) != NULL)
    {
        if(atoi(row[1]) == 4)
            printf("\n[X]Agregar nuevos Administradores.\t");
        if(atoi(row[1]) == 5)
            printf("\n[X]Modificar informacion de Administradores.\t");
        if(atoi(row[1]) == 6)
            printf("\n[X]Eliminar Administradores del sistema.\t");
        if(atoi(row[1]) == 7)
            printf("\n[X]Agregar Privilegios a Administradores.\t");
        if(atoi(row[1]) == 8)
            printf("\n[X]Eliminar Privilegios a Administradores.\t");
        
        printf("Fecha Ultima Modificacion: %s",row[2]);
    }
    free(consulta);
    return 1;
}
/**
 * @brief Funcion que permite imprimir los permisos de los Servicios
 * 
 * @param nomuser parametro que recibe el nombre del usuario
 * @return int 
 */
int imprimir_permisoServicios(char * nomuser)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    int id_user= ObtenerIdUser(nomuser);
    //printf("\nid del usuario: %d",id_user);
    sprintf(consulta,"SELECT %s FROM Tipo_Admin_Cat_Servicios WHERE Id_Administrador=%d;",CamposTipoAdminCatServicios,id_user);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    printf("\nPermisos de Servicios Activos en el usuario %s",nomuser);
    while((row=mysql_fetch_row(res)) != NULL)
    {
        if(atoi(row[1]) == 1)
            printf("\n[X]Monitorizacion.\t");
        if(atoi(row[1]) == 2)
            printf("\n[X]Configuracion de Router.\t");
        if(atoi(row[1]) == 3)
            printf("\n[X]Configuracion de Switch.\t");
        if(atoi(row[1]) == 4)
            printf("\n[X]Configuracion de Servidor.\t");
        
        printf("Fecha Ultima Modificacion: %s",row[2]);
    }
    free(consulta);
    return 1;
}
/**
 * @brief Funcion que permite agregar el permiso de agregar administradores
 * 
 * @param permisos recibe la cadena de los permisos puestos por el usuario
 * @param iduser recibe el id del usuario
 * @return int 
 */
int InsertarPermisosAgregarAdmin(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Tareas(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatTareas,iduser,4,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite agregar el permiso de modificar administradores
 * 
 * @param iduser parametro que recibe el id del usuario
 * @param Fecha parametro que recibe la fecha
 * @return int 
 */
int InsertarPermisosModifAdmin(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Tareas(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatTareas,iduser,5,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite agregar el permiso de eliminar administradores
 * 
 * @param iduser parametro que recibe el id del usuario
 * @param Fecha parametro que recibe la fecha de la operacion
 * @return int 
 */
int InsertarPermisosElimAdmin(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Tareas(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatTareas,iduser,6,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite agregar el permiso de agregar privilegios al adminsitrador.
 * 
 * @param iduser parametro que recibe el id del usuario
 * @param Fecha parametro que recibe la fecha
 * @return int 
 */
int InsertarPermisosAgrgAdmin(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Tareas(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatTareas,iduser,8,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite agregar el permiso de eliminar al administrador
 * 
 * @param iduser parametro que recibe el id delusuario
 * @param Fecha parametro que recibe la Fecha
 * @return int 
 */
int InsertarPermisosElimAgrgAdmin(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Tareas(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatTareas,iduser,7,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite agregar el permiso de Servicio de monitoreo
 * 
 * @param iduser parametro que recibe el id del usuario
 * @param Fecha parametro que recibe la fecha
 * @return int 
 */
int InsertarPermisosServMonit(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Servicios(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatServicios,iduser,1,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite agregar permisos de servicio de configuracion en router
 * 
 * @param iduser parametro que recibe el id del usuario
 * @param Fecha parametro que recibe la fecha
 * @return int 
 */
int InsertarPermisosServRouter(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Servicios(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatServicios,iduser,2,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite agregar el permiso de Servicio de configuracion en switches
 * 
 * @param iduser parametro que recibe el id del usuario
 * @param Fecha parametro que recibe la fecha
 * @return int 
 */
int InsertarPermisosServSwitch(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Servicios(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatServicios,iduser,3,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que permite agregar los permisos para el servicio de configuracion del servidor
 * 
 * @param iduser parametroque recibe el id del usuario
 * @param Fecha parametro que recibe la fecha
 * @return int 
 */
int InsertarPermisosServSevidor(int iduser,char* Fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Servicios(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatServicios,iduser,4,Fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1;   
}
/**
 * @brief Funcion que actualiza los datos del usuario
 * 
 * @param nomuser parametro que recibe el nombre del usuario
 * @param idstatus parametro que recibe el id del status que se va a cambiar
 * @return int 
 */
int Actualizar_StatusAdmin(char * nomuser,int idstatus)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"UPDATE Administradores SET Id_Status_Admin= %d WHERE Nombre_Usuario='%s';",idstatus,nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion que actualiza los datos del usuario
 * 
 * @param nomuser parametor que recibe el nombre del usuario 
 * @param idtipo parametro que recibe el id del tipo de administrador
 * @return int 
 */
int Actualizar_TipoAdmin(char * nomuser,int idtipo)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"UPDATE Administradores SET Id_Tipo_Admin= %d WHERE Nombre_Usuario='%s';",idtipo,nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion que permite actualizar el nombre del administrador
 * 
 * @param nomuser parametro que recibe el nombre del usuario
 * @param Nombre parametro que recibe el nombre del administrador
 * @return int 
 */
int Actualizar_NombreAdmin(char * nomuser,char* Nombre)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"UPDATE Administradores SET Nombre_Admin='%s' WHERE Nombre_Usuario='%s';",Nombre,nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion que permite actualizar el nombre del administrador
 * 
 * @param nomuser parametro que recibe el nombre del usuario
 * @param Nombre parametro que recibe el nombre nuevo
 * @return int 
 */
int Actualizar_APAdmin(char * nomuser,char* Nombre)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"UPDATE Administradores SET Apellido_P_Admin='%s' WHERE Nombre_Usuario='%s';",Nombre,nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Actualiza el nombre materno del adminsitrador
 * 
 * @param nomuser parametro que recibe el nombre del usuario.
 * @param Nombre parametro que recibe el nombre nuevo del usuario.
 * @return int 
 */
int Actualizar_AMAdmin(char * nomuser,char* Nombre)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"UPDATE Administradores SET Apellido_M_Admin='%s' WHERE Nombre_Usuario='%s';",Nombre,nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion que comprueba que no existan otros con el mismo nombre de usuario
 * 
 * @param nomuser parametro que recibe el nombre del usuario
 * @return int 
 */

int validaruser(char* nomuser)
{
   ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"SELECT COUNT(*) FROM Administradores WHERE Nombre_Usuario='%s';",nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    //int cant_campos = mysql_num_fields(res);
    //printf("\nuser 1 %s user 2 %s",nomuser,row[0]);
    while((row=mysql_fetch_row(res)) != NULL)
    {
        if( atoi(row[0]) > 0)
            return -2;
    }
    return 1;
}

/**
 * @brief Funcion que permite actualizar el nombre de usuario
 * 
 * @param nomuser recibe el nombre actual de usuario
 * @param Nombre recibe el nombre nuevo de usuario
 * @return int 
 */
int Actualizar_NomUser(char * nomuser,char* Nombre)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    if(validaruser(Nombre)!=1)
     {
         printf("\nError ya existe el nombre de usuario.");
         return -2;
     }   
    sprintf(consulta,"UPDATE Administradores SET Nombre_Usuario='%s' WHERE Nombre_Usuario='%s';",Nombre,nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion  que verifica si el usuario existe
 * 
 * @param nomuser parametro que recibe el nombre del usuario.
 * @return int 
 */
int verifexistuser(char* nomuser)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"SELECT COUNT(*) FROM Administradores WHERE Nombre_Usuario='%s';",nomuser);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    //int cant_campos = mysql_num_fields(res);
    //printf("\nuser 1 %s user 2 %s",nomuser,row[0]);
    while((row=mysql_fetch_row(res)) != NULL)
    {
        if( atoi(row[0]) == 0)
            return -2;
    }
    return 1;
}
/**
 * @brief Funcion que valida si ya el usuario tiene ese permiso asignado
 * 
 * @param idtarea parametro que recibe el id de la tarea
 * @param iduser parametro que recibe el id del user
 * @return int 
 */
int valid_permTarea(int idtarea,int iduser)
{
     ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"SELECT COUNT(*) FROM Tipo_Admin_Cat_Tareas WHERE Id_Administrador=%d AND Id_Cat_Tareas=%d;",iduser,idtarea);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    while((row=mysql_fetch_row(res)) != NULL)
    {
        if( atoi(row[0]) > 0)
            return -2;
    }
    return 1;
}
/**
 * @brief Funcion que verifica e inserta el permiso si el usuario no lo tiene.
 * 
 * @param idtarea parametro que recibe el id de la tarea
 * @param NomUser parametro que recibe el nombre del usuario
 * @param fecha parametro que recibe la fecha
 * @return int 
 */
int verif_existpermiTarea(int idtarea,char* NomUser,char *fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    int id_user= ObtenerIdUser(NomUser);
    if(valid_permTarea(idtarea,id_user)!=1)
        return -4;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Tareas(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatTareas,id_user,idtarea,fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion que elimina elpermiso asginado a un usuario
 * 
 * @param idtarea parametro que recibe el id de la tarea
 * @param NomUser parametro que recibe el nombre del usuario
 * @return int 
 */
int Elim_permiTarea(int idtarea,char*NomUser)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    int id_user= ObtenerIdUser(NomUser);
    sprintf(consulta,"DELETE FROM Tipo_Admin_Cat_Tareas WHERE Id_Administrador=%d AND Id_Cat_Tareas=%d;",id_user,idtarea);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}

/**
 * @brief Funcion que valida si ya el usuario tiene ese permiso asignado
 * 
 * @param idtarea parametro que recibe el id de la tarea
 * @param iduser parametro que recibe el id del user
 * @return int 
 */
int valid_permServicio(int idtarea,int iduser)
{
     ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    sprintf(consulta,"SELECT COUNT(*) FROM Tipo_Admin_Cat_Servicios WHERE Id_Administrador=%d AND Id_Cat_Servicios=%d;",iduser,idtarea);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    while((row=mysql_fetch_row(res)) != NULL)
    {
        if( atoi(row[0]) > 0)
            return -2;
    }
    return 1;
}
/**
 * @brief Funcion que verifica e inserta el permiso si el usuario no lo tiene.
 * 
 * @param idtarea parametro que recibe el id de la tarea
 * @param NomUser parametro que recibe el nombre del usuario
 * @param fecha parametro que recibe la fecha
 * @return int 
 */
int verif_existpermiServicio(int idtarea,char* NomUser,char *fecha)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    int id_user= ObtenerIdUser(NomUser);
    if(valid_permServicio(idtarea,id_user)!=1)
        return -4;
    sprintf(consulta,"INSERT INTO Tipo_Admin_Cat_Servicios(%s) VALUES(%d,%d,'%s');",CamposTipoAdminCatServicios,id_user,idtarea,fecha);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion que elimina elpermiso asginado a un usuario
 * 
 * @param idtarea parametro que recibe el id de la tarea
 * @param NomUser parametro que recibe el nombre del usuario
 * @return int 
 */
int Elim_permiServicio(int idtarea,char*NomUser)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    int id_user= ObtenerIdUser(NomUser);
    sprintf(consulta,"DELETE FROM Tipo_Admin_Cat_Servicios WHERE Id_Administrador=%d AND Id_Cat_Servicios=%d;",id_user,idtarea);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion que elimina del sistema a los administradores
 * 
 * @param Nombre parametro que recibe el nombre del usuario.
 * @return int 
 */
int Elimuser(char * Nombre)
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    if(verifexistuser(Nombre)!=1)
        return -2;
    sprintf(consulta,"UPDATE Administradores SET Id_Status_Admin=3 WHERE Nombre_Usuario='%s';",Nombre);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    free(consulta);
    return 1; 
}
/**
 * @brief Funcion que muestra los usuarios
 * 
 * @return int 
 */
int listar_usuarios()
{
    ControladorBD();
    char *consulta;
    consulta = (char *) malloc(sizeof(char)*MAXConsulta);
    if(consulta==NULL)
        return -1;
    //printf("\nid del usuario: %d",id_user);
    sprintf(consulta,"SELECT %s FROM Administradores;",CamposAdministradores);
    if(mysql_query(conexion,consulta))
    {
        fprintf(stderr,"%s\n",mysql_error(conexion));
        return 0;
    }
    res=mysql_use_result(conexion); 
    printf("\n||Status Admin||   Tipo Admin   ||     Nombre    ||    Apellido Paterno   ||     Apellido Materno   ||     Fecha Ingreso   ||  Nombre Usuario");
    while((row=mysql_fetch_row(res)) != NULL)
    {
        if(atoi(row[0]) == 1)
            printf("\n|| Activo");
        if(atoi(row[0]) == 2)
            printf("\nInactivo");
        if(atoi(row[0]) == 3)
            printf("\nFuera del sistema");

        if(atoi(row[1]) == 1)
            printf("  Administrador  ");
        if(atoi(row[1]) == 2)
            printf("  Superadministrador  ");
        printf("  %s    %s    %s    %s    %s  ||\n",row[2],row[3],row[4],row[5],row[6]);
    }
    free(consulta);
    return 1;
}