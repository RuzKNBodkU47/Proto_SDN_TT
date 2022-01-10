#MAKEFILE PARA COMPILAR TODO CMD
OBJS = main.o mainlogin.o mainverif.o mainfunusers.o
BINARY = exefin
#CFLAGS = -g -Wall


all: mainexe

#MAINEXE COMPILA EL ARCHIVO PRINCIPAL
mainexe: $(OBJS)
	gcc -o exefin $(OBJS)

main.o:main.c mainlogin.h
	gcc -c main.c
#MAINLOGIN OBTIENE EL ARCHIVO OBJETO DE MAINLOGIN.C 
mainlogin.o: mainlogin.c mainlogin.h
	gcc -c mainlogin.c
#MAINVERIF OBTIENE EL ARCHIVO OBJETO DE MAINVERIF.C
mainverif.o: mainverif.c mainverif.h
	gcc  -c mainverif.c
#MAINFUNUSERS OBTIENE EL ARCHIVO OBJETO DE MAINFUNUSERS,C
mainfunusers.o: mainfunusers.c mainfunusers.h
	gcc -c mainfunusers.c

#MAINCONFIG OBTIENE EL ARCHIVO OBJETO DE MAINCONFIG.C
mainconfig.o: mainconfig.c mainconfig.h
	gcc -c mainconfig.c
clean:
	rm -f exefin *.o