#include <string.h>
#include <iostream>

using namespace std;

#define USUARIO "sdn"
#define PASS "A046-2021"

int main(int args, char * argv[])
{
    char Usu[25];
    char Pass[25];
    int intentos=0;
    bool verificado=false;
    std::cout << "Usuario:" << std::endl;
    cin.getline(Usu,25);
    std::cout << "Contraseña:" << std::endl;
    cin.getline(Pass,25);
    intentos++;
    if(strlen(Pass)>=8){
        if((strcmp(Pass,PASS)==0)&&(strcmp(Usu,USUARIO)==0)){
            verificado=true;
        }
    }
    else{
       std::cout << "La contraseña debe tener al menos 8 caracteres" << std::endl; 
    }
    if(verificado==true){
        std::cout << "Bienvenido "<< Usu << std::endl;
        std::cout << "Se ingresó correctamente" << std::endl;
    }
}
