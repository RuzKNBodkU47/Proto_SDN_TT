/*
* Instituto Politecnico Nacional
* Escuela Superior de Computo
* Prototipo de Arquitectura de Red Definida por Software para el 
* Centro de Datos de la Dirección de Cómputo y Comunicaciones del Instituto Politécnico Nacional
* main.cpp
*/
#include <iostream>
#include "liblogin/mainlogin.h"

using namespace std;

int main(int argc, char * argv[])
{
    int intentos=0,opc=argc,sesion=1;
    while(intentos<3)
    {
        if(opc==1)
        {
            if(login_cli_gui()!=1)
                intentos++;
        }    
        if(opc>1)
        {

            if(login_cli(argv[1],argv[2])!=1)
                intentos=3;
        }
    }
    while(sesion)
    {

    }
    return 1;    
}
