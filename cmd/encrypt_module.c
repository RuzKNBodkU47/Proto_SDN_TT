#include <stdio.h>
#include <stdlib.h>

#include "../cmathematics/cmathematics.h"
#include "../cmathematics/data/encryption/aes.h"

int main(char password, char key)
{
    char *txt = password; //texto a cifrar
    char *key = key; //llave de cifrado
    char *cipher = NULL; //

    //txt, numero de caracteres para el cifrado, llave, longitud de la llave, 
    char cipher_pass = aes_encrypt(txt, 128, key, 16, &cipher);

    FILE *CipherPass;
    CipherPass = fopen("PassHash.txt","w+");

    fputs(cipher_pass,CipherPass);
    fput("\n");

    fclose(CipherPass);
    return 0;
}