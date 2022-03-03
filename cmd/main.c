/**
 * @file main.c
 * @author Instituto Politecnico Nacional ESCOM
 * @brief programa principal de la SDNTT para la linea de comandos
 * @version 0.1
 * @date 2021-12-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mainlogin.h"
#include "mainverif.h"
#include "mainfunusers.h"
#include "mainconfig.h" 
/**
 * @brief  definiendo macros de la funcion main
 * 
 */
#define MAX_COMMAND_TAM 50
/**
 * @brief variables globales de la funcion main
 * 
 */
char Fecha[70]="";
int IDUSER=-2;
/**
 * @brief prototipo de funcion para obtener la fecha del sistema 
 */
void funcion_users();
void funcion_config();
int obtener_fecha_sys();
int imprimir_arch_help();
void funcion_log();
void funcion_system();
void funcion_user_syst();


/**
 * @brief funcion principal del programa SDNTT de la linea de comandos
 * 
 * @param argc cantidad de argumentos de entrada
 * @param argv los argumentos de entrada
 * @return int valor entero que regresa la funcion main
 */
int main(int argc, char * argv[])
{
    int intentos=0,opc=argc,sesion=1;
    char * comando;
    comando = (char *) malloc(sizeof(char)*MAX_COMMAND_TAM);
   // char fecha[40];
    while(intentos<3)
    {
        if(opc==1)
        {
            if((IDUSER=login_cli_gui())>0)
                break;
            else
                intentos++;    
        }    
        if(opc>1)
        {
            if((IDUSER=login_cli(argv[1],argv[2]))>0)
            {
                break;
            }      
            else
            {
                printf("\nError en el usuario o contrasena\n");
                return 0;
            }
        }
    }
    if(intentos!=3)
     {
        if(obtener_fecha_sys()==0)
            return 0;
        printf("\nInicio de sesion %s",Fecha);
        if(insert_login(Fecha,IDUSER)==0)
        {
            printf("\nError al registrar login");
            return 0;
        }
        while(sesion)
        {
            printf("\nSDNTT> ");
            scanf("%s",comando);
            if(strcmp(comando,QUIT_CMD)==0)//opcion de salir de la aplicacion
            {
                if(obtener_fecha_sys()==0)
                    return 0;
                printf("\nCierre de sesion %s\n",Fecha);
                if(insert_logout(Fecha,IDUSER)==0)
                {
                    printf("\nError al registrar login");
                    return 0;
                }
                return 1;
            }
            else if( strcmp(comando,HELP_CMD)==0)// opcion de imprimir el archivo de ayuda
            {
               if(imprimir_arch_help()==0)
                return 0; 
            }
           else if(strcmp(comando,CONFIG_CMD)==0)
            {
                funcion_config();
            }
            else if(strcmp(comando,USERS_CMD)==0)
            {
                /*validar si el usuario tiene funciones para entrar a estas opcionees**/
                funcion_users();
            }
            else if(strcmp(comando,SYST_CMD)==0)
            {
                /*validar si el usuario tiene permiso para entrar a estas funciones*/
                funcion_system();
            }
            else if(strcmp(comando,LOGS_CMD)==0)
            {
                /*validar si el usuario tiene permiso para entrar a estas funciones*/
                funcion_log();
            }
            else if(strcmp(comando,USER_SYST_CMD)==0)
            {
                /*validar si el usuario tiene permiso para entrar a estas funciones*/
                funcion_user_syst();
            }
            else
            {
                printf("\nEl comando %s no existe.",comando);   
            }
        }
     }   
    return 1;    
}
/**
 * @brief funcion que contiene las opciones de las configuracion de los usuarios.
 * 
 */
void funcion_user_syst()
{
    int indice=1;
    char * subcomando;
    subcomando =(char *) malloc(sizeof(char)*MAX_COMMAND_TAM);
    while(indice!=0)
    {
        printf("\nSDNTT>USERCONFIG>");
        scanf("%s",subcomando);
        if(strcmp(subcomando,USER_SYST_CMD)==0)
        {
            /*verificar permisos del usuario si tiene permitido usar esta funcion**/
            
        }
        else if(strcmp(subcomando,USER_SYST_CMD_1)==0)
        {
            /*verficar los permisos del usuario si tiene permitido usar esta funcion*/
        }
        else if(strcmp(subcomando,USER_SYST_CMD_2)==0)
        {
            /*verificar los permisos del usuario si tiene permitido usar esta funcion*/
        }
        else if(strcmp(subcomando,EXIT_CMD)==0)
            break;
        else
        {
            printf("\nEl comando %s no existe.",subcomando);            
        }
    }         
}
/**
 * @brief funcion que contiene las opciones para los logs
 * 
 */
void funcion_log()
{
    int indice=1;
    char * subcomando;
    subcomando =(char *) malloc(sizeof(char)*MAX_COMMAND_TAM);
    while(indice!=0)
    {
        printf("\nSDNTT>LOG>");
        scanf("%s",subcomando);
        if(strcmp(subcomando,LOGS_CMD_1)==0)
        {
            /*verificar permisos del usuario si tiene permitido usar esta funcion**/
            
        }
        else if(strcmp(subcomando,LOGS_CMD_2)==0)
        {
            /*verficar los permisos del usuario si tiene permitido usar esta funcion*/
        }
        else if(strcmp(subcomando,EXIT_CMD)==0)
            break;
        else
        {
            printf("\nEl comando %s no existe.",subcomando);            
        }
    }         
}
/**
 * @brief funcion que contiene las opciones para la configuracion del sistema
 * 
 */
void funcion_system()
{
    int indice=1;
    char * subcomando;
    subcomando =(char *) malloc(sizeof(char)*MAX_COMMAND_TAM);
    while(indice!=0)
    {
        printf("\nSDNTT>SYSTEM>");
        scanf("%s",subcomando);
        if(strcmp(subcomando,SYST_CMD_1)==0)
        {
            /*verificar permisos del usuario si tiene permitido usar esta funcion**/
            
        }
        else if(strcmp(subcomando,SYST_CMD_2)==0)
        {
            /*verficar los permisos del usuario si tiene permitido usar esta funcion*/
        }
        else if(strcmp(subcomando,SYST_CMD_3)==0)
        {
            /*verificar los permisos del usuario si tiene permitido usar esta funcion*/
        }
        else if(strcmp(subcomando,SYST_CMD_4)==0)
        {
            /*verificar los permisos del usuario si tiene permitido usar esta funcion*/    
        }
        else if(strcmp(subcomando,SYST_CMD_5)==0)
        {
            /*verificar los permisos del usuario si tiene permitido usar esta funcion*/    
        }
        else if(strcmp(subcomando,EXIT_CMD)==0)
            break;
        else
        {
            printf("\nEl comando %s no existe.",subcomando);            
        }
    }         
}
/**
 * @brief funcion para las opciones de usuarios
 * 
 */
void funcion_users()
{
    int indice=1,subindice=1;
    int flag=0;
    char * subcomando;
    subcomando =(char *) malloc(sizeof(char)*MAX_COMMAND_TAM);
    while(indice!=0)
    {
        printf("\nSDNTT>USERS>");
        scanf("%s",subcomando);
        if(strcmp(subcomando,USERS_CMD_1)==0)
        {
            /*verificar permisos del usuario si tiene permitido usar esta funcion**/
            if(regis_user()==1)
                printf("\n[+]Usuario agregado con exito. ");
            else
                printf("\n[X]Usuario no se agrego con exito.");
        }
        else if(strcmp(subcomando,USERS_CMD_2)==0)
        {
            /*verficar los permisos del usuario si tiene permitido usar esta funcion*/
            while(subindice)
            {
                printf("\nSDNTT>USERS>MODIFICAR>");
                scanf("%s",subcomando);
                if(strcmp(subcomando,USERS_SUBCMD_1)==0)
                {
                    flag=1;
                    if(ModificarUser(flag)==1)
                        printf("\n[+]Usuario Modificado con exito");
                    else
                        printf("\n[-]Usuario Modificado sin exito");
                }

                if(strcmp(subcomando,USERS_SUBCMD_2)==0)
                {
                    flag=2;
                    if(ModificarUser(flag)==1)
                        printf("\n[+]Usuario Modificado con exito");
                    else
                        printf("\n[-]Usuario Modificado sin exito");
                } 
                else if(strcmp(subcomando,EXIT_CMD)==0)
                    break;   
                
            }
            
        }
        else if(strcmp(subcomando,USERS_CMD_3)==0)
        {
            /*verificar los permisos del usuario si tiene permitido usar esta funcion*/
        }
        else if(strcmp(subcomando,USERS_CMD_4)==0)
        {
            /*verificar los permisos del usuario si tiene permitido usar esta funcion*/    
        }
        else if(strcmp(subcomando,EXIT_CMD)==0)
            break;
        else
        {
            printf("\nEl comando %s no existe.",subcomando);            
        }
    }              
}
/**
 * @brief Funcion para las opciones de configuracion
 * 
 */
void funcion_config()
{
    int indice=1;
    char * subcomando;
    subcomando = (char *) malloc(sizeof(char)*MAX_COMMAND_TAM);
    while(indice!=0)
    {
        printf("\nSDNTT>CONFIG>");
        scanf("%s",subcomando);
        if(strcmp(subcomando,CONFIG_CMD_1)==0)
        {
            /**verificar los permisos del usuario si tiene permitido usar esta funcion**/
        }
        else if(strcmp(subcomando,CONFIG_CMD_2)==0)
        {
            /**verificar los permisos del usuario si tiene permitido usar esta funcion**/
        }
        else if(strcmp(subcomando,CONFIG_CMD_3)==0)
        {
            /**verificar los permisos del usuario si tiene permitido usar esta funcion**/
        }
        else if(strcmp(subcomando,EXIT_CMD)==0)
            break;
        else
        {
             printf("\nEl comando %s no existe.",subcomando);   
        }
    }       
}
/**
 * @brief funcion que permite obtener la fecha del sistema
 * 
 * @return variable de tipo entero que regresa la comprobacion de la funcion
 */
int obtener_fecha_sys()
{
    // Tiempo actual
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    //char fechaHora[70];
    char *formato = "%Y-%m-%d %H:%M:%S";
    // Intentar formatear
    int bytesEscritos = strftime(Fecha, sizeof(Fecha), formato, &tiempoLocal);
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
 * @brief Funcion que permite imprimir el archivo de ayuda de los comandos de la terminal
 * 
 * @return int 
 */
int imprimir_arch_help()
{
    char cadenas[100];
    char Nom_arch[40]="Help.txt";
    FILE *archivo_ayuda;
    archivo_ayuda=fopen(Nom_arch,"r");
    if(archivo_ayuda==NULL)
    {
        printf("Error al abrir el archivo de ayuda.\n");
        return 0;
    }
    while(feof(archivo_ayuda)==0)
    {
        fgets(cadenas,100,archivo_ayuda);
        printf("%s",cadenas);
    }
    fclose(archivo_ayuda);
    return 1;
}