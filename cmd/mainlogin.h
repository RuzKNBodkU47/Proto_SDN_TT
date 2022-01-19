/**
 * @file mainlogin.h
 * @author Instituto Politecnico Nacional
 * @brief header que se guarda los prototipos de funciones y define macros para el main
 * @version 0.1
 * @date 2021-12-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MAINLOGIN_H
#define MAINLOGIN_H

#define QUIT_CMD "salir"
#define HELP_CMD "help"
#define EXIT_CMD "exit"
#define CONFIG_CMD "config"
#define CONFIG_CMD_1 "router"
#define CONFIG_CMD_2 "switch"
#define CONFIG_CMD_3 "server"

#define USERS_CMD "users"
#define USERS_CMD_1 "agregar"
#define USERS_CMD_2 "modificar"
#define USERS_CMD_3 "eliminar"
#define USERS_CMD_4 "listar"

#define LOGS_CMD "logs"
#define LOGS_CMD_1 "mostrar_todo"
#define LOGS_CMD_2 "buscar"


#define SYST_CMD "sistema"
#define SYST_CMD_1 "tipoadmin"
#define SYST_CMD_2 "statusadmin"
#define SYST_CMD_3 "statuslog"
#define SYST_CMD_4 "servicios"
#define SYST_CMD_5 "tareas"

#define USER_SYST_CMD "userconfig"
#define USER_SYST_CMD_1 "moddata"
#define USER_SYST_CMD_2 "modpass"



int login_cli(char *user, char *pass);
int login_cli_gui();

#endif