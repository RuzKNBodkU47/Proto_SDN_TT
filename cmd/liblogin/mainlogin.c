#include "../libverif/mainverif.h"
#include "mainverif.h"
#include <stdio.h>
#include <string.h>

char * USUARIO = "sdn";
char * PASS = "A046-2021";

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
    char * user,*pwd;
    printf("Login CLI GUI\nUsuario: ");
    scanf("%s",user);
    printf("Contrasena: ");
    scanf("%s",pwd);
    if((strcmp(user,USUARIO) && strcmp(pwd,PASS)) != 1)
    {
        printf("Error en la contrasena y/o password\n");
        return 0;
    }
    return 1;
}
