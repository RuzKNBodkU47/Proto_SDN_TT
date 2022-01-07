/**
 * @file mainverif.h
 * @author Instituto Politecnico Nacional ESCOM
 * @brief header con los prototitpos de funciones y macros para mainverif.c
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MAINVERIF_H
#define MAINVERIF_H


int verif_tam(char * cadena );
int verif_carac_num(char *cadena);
int verif_carac_let(char *cadena);
int verif_carac_sim(char *cadena);

int verif_permi_users(char *user, char* hash_pass);

#endif