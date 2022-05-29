/**
 * @file main_fun_users.h
 * @author Instituto Politecnico Nacional ESCOM
 * @brief header para las funciones de los usuarios
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MAINFUNUSERS_H
#define MAINFUNUSERS_H
int regis_user();
int ModificarUser(int flag);
int RegistrarFuncionesUser(int IdUser);
int obfecha();
int ModificarPermisosTareas(int IdUser);
int ModificarPermisosServicios(int IdUser);
void menuflag1();
void menuflag2();
int EliminarUsers();
int ListarAdministradores();
int usermoddata(int user);
void Gen_Pass();
int ImLogTareas();
int ImLogServicios();
int ImLogTareasTxt();
int ImLogServiciosTxt();
void menusublogs();
int busc_userlog();
int fun_fech(int flag,int flag2);
int busc_fechainitlog(int flag2);
int buscarlogstarserv(int flag);
int idbuslog();
#endif