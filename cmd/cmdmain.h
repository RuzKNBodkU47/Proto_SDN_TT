/**
 * @file cmd_main.h
 * @author Instituto Politecnico Nacional Escuela Superior de Computo
 * @brief header del archivo cmd_main.c
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//#include <mysql.h>
#include<mysql/mysql.h>
//#include "cmdmain.c"

#ifndef CMDMAIN_H
#define CMDMAIN_H

MYSQL *conexion;
MYSQL_RES *res;
MYSQL_ROW row;

#define MAXConsulta 1000

char *servidor = "localhost";
char *user = "ruzkn47";
char *password ="inquisidor1922";
char *database = "SDNTT";

char CamposStatusAdmin[50]="Nom_Tipo_Admin";
char CamposStatuslog[50]="Nom_Status_Log";
char CamposTipoAdmin[50]="Nom_Tipo_Admin";
char CamposCatServicios[50]="Nom_Cat_Servicios";
char CamposCatTareas[50]="Nom_Cat_Tareas";
char CamposAdministradores[500]="Id_Status_Admin,Id_Tipo_Admin,Nombre_Admin,Apellido_P_Admin,Apellido_M_Admin,Fecha_ingreso,Nombre_Usuario,Password_Hash,Fecha_Ultimo_Cambio_Pass,Cant_dias_limit";
char CamposTipoAdminCatServicios[120]="Id_Administrador,Id_Cat_Servicios,Fecha_Ult_Mod";
char CamposTipoAdminCatTareas[120]="Id_Administrador,Id_Cat_Tareas,Fecha_Ult_Mod";
char CamposAdministradoresServicioslog[500]="Id_Status_Log,Id_Administradores,Id_Cat_Servicios,IP_Dispositivo_Orig,MAC_Dispositivo_Orig,IP_Dispositivos_Ant,IP_Dispositivos_Desp,Dir_MAC_Disp_Fin,Fecha_Init_Serv,Fecha_Fin_Serv";
char CamposAdministradoresTareaslog[500]="Id_Status_Log,Id_Administradores,Id_Cat_Tareas,IP_Dispositivo_Orig,MAC_Dispositivo_Orig,Id_Admin_Obj,Fecha_Init_Serv,Fecha_Fin_Serv";

void ControladorBD();

int InsertAdmin(int StatusAdmin, int TipAdmin , char* NomAdmin, char * ApPat, char *ApMat, char *FechaIng, char* NomUser, char * Pass, char* FechaUlt, int cantdias);

#endif