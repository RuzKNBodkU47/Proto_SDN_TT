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
#define USERS_CMD "users"



int login_cli(char *user, char *pass);
int login_cli_gui();

#endif