/**
 * @file mainlogin.c
 * @author Instituto Politecnico Nacional ESCOM
 * @brief Funciones implementadas para operaciones extras para el main
 * @version 0.1
 * @date 2021-12-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "mainverif.h"
#include "mainlogin.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>

#define MAXPASS 10

struct admin
{
    int Tipo_admin;
    char* nombre_admin;
    char* Apellido_P_Admin;
    char* Apellido_M_Admin;
};


char * USUARIO = "sdn";
char * PASS = "A046-2021";

//char fecha_sesion[40];


int login_cli(char *user, char *pass)
{
    if((strcmp(user,USUARIO) && strcmp(pass,PASS)) != 1)
    {
        printf("Error en la contrasena y/o password\n");
        return 0;
    }
    return 1;
}

int login_cli_gui()
{
    struct termios oflags, nflags;
    char user[20],pwd[20];
    printf("Login CLI GUI\nUsuario: ");
    scanf("%s",user);
    printf("Contrasena: ");
    //noecho();
    scanf("%s",pwd);
    //scanf("%s",pwd);
    //getpass(pwd);
    /** Desabiliando los mensajes en terminal**/
   /* tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        return EXIT_FAILURE;
    }

    printf("Contrasena: ");
    fgets(pwd, sizeof(pwd), stdin);
    //pwd[strlen(pwd) - 1] = 0;
    pwd[ strcspn( pwd, "\n" ) ] = '\0';
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        return EXIT_FAILURE;
    }
    */


    printf("\n%s\n%s",user,pwd);
    if((strcmp(user,USUARIO) && strcmp(pwd,PASS)) != 0)
    {
        printf("Error en la contrasena y/o password\n");
        return 0;
    }
    return 1;
}


