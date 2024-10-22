/**
 * @file cmd_main.h
 * @author Instituto Politecnico Nacional Escuela Superior de Computo
 * @brief header del archivo cmdmain.c
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//#include <mysql.h>


#ifndef CMDMAIN_H
#define CMDMAIN_H
char *servidor = "localhost";
char *user = "ruzkn47";
//char *user = "root";
char *password ="inquisidor1922";
char *database = "SDNTT2";

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
void ControladorBD2();
int InsertAdmin(int StatusAdmin, int TipAdmin , char* NomAdmin, char* ApPat, char* ApMat, char* FechaIng, char* NomUser, char* Pass, char* FechaUlt, int cantdias);
int ObtenerIdUser(char *nomuser);
int BuscarUsuario(char *user);
int BuscarPass(char *user,char* pass);
int BuscarPermUsers(int id);
int insert_login(char* Fecha,int id);
int insert_logout(char* Fecha,int id);
int InsertarPermisosAgregarAdmin(int iduser,char* Fecha);
int InsertarPermisosModifAdmin(int iduser,char* Fecha);
int InsertarPermisosElimAdmin(int iduser,char* Fecha);
int InsertarPermisosAgrgAdmin(int iduser,char* Fecha);
int InsertarPermisosElimAgrgAdmin(int iduser,char* Fecha);
int InsertarPermisosServMonit(int iduser,char* Fecha);
int InsertarPermisosServRouter(int iduser,char* Fecha);
int InsertarPermisosServSwitch(int iduser,char* Fecha);
int InsertarPermisosServSevidor(int iduser,char* Fecha);
int insert_log_user1(int id,char*Fecha);
int insert_log_Euser1(int id,char*Fecha);
int imprimir_infouser(char * nomuser);
int imprimir_permisotareas(char * nomuser);
int imprimir_permisoServicios(char * nomuser);
int Actualizar_TipoAdmin(char * nomuser,int idtipo);
int Actualizar_StatusAdmin(char * nomuser,int idstatus);
int Actualizar_NombreAdmin(char * nomuser,char* Nombre);
int Actualizar_APAdmin(char * nomuser,char* Nombre);
int Actualizar_AMAdmin(char * nomuser,char* Nombre);
int Actualizar_NomUser(char * nomuser,char* Nombre);
int validaruser(char* nomuser);
int verifexistuser(char* nomuser);
int valid_permTarea(int idtarea,int iduser);
int verif_existpermiTarea(int idtarea,char* NomUser,char *fecha);
int Elim_permiTarea(int idtarea,char*NomUser);
int valid_permServicio(int idtarea,int iduser);
int verif_existpermiServicio(int idtarea,char* NomUser,char *fecha);
int Elim_permiServicio(int idtarea,char*NomUser);
int Elimuser(char * Nombre);
int listar_usuarios();
int Verif_status(char *user);
int UpdateData(int flag, int user, char *data);
int UpdatePass(int user,char *pass);
int MostrarLogsTareas();
void ObtenerNomUser(int id);
int MostrarLogsServicios();
int GenLogTareasTxt(char *nomarch);
int GenLogServiciosTxt(char *nomarch);
int busquedaloguser(char * nomuser, int flag);
int busquedalogfecha(char * fecha, int flag, int flag2, int flag3);
int buslogid(int flag,int id);

#endif