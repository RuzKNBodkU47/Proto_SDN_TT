#MAKEFILE PARA COMPILAR TODO CMD
OBJS = main.o mainlogin.o mainverif.o mainfunusers.o 
BINARY = exefin

OBJS1 = cmdmain.o 
BINARY1 = BDcontrolador
#CFLAGS = -g -Wall


all: mainexe

#MAINEXE COMPILA EL ARCHIVO PRINCIPAL
mainexe: $(OBJS)
	gcc -o exefin $(OBJS)
#MAIN.O OBTIENE EL ARCHIVO OBJETO DEL MAIN
main.o:main.c mainlogin.h
	gcc -c main.c
#MAINLOGIN OBTIENE EL ARCHIVO OBJETO DE MAINLOGIN.C 
mainlogin.o: mainlogin.c mainlogin.h
	gcc -c mainlogin.c
#MAINVERIF OBTIENE EL ARCHIVO OBJETO DE MAINVERIF.C
mainverif.o: mainverif.c mainverif.h
	gcc  -c mainverif.c
#MAINFUNUSERS OBTIENE EL ARCHIVO OBJETO DE MAINFUNUSERS,C
mainfunusers.o: mainfunusers.c mainfunusers.h cmdmain.o
	gcc -c mainfunusers.c

#cmdmainexe: $(OBJS1)
#	gcc -o $(BINARY1) $(OBJS1) $(mysql_config --libs) -lmysqlclient
#MAIN.O GEMERA EL ARCHIVO OBJETO DEL MAIN
cmdmain.o: cmdmain.c cmdmain.h
	gcc -c $(mysql_config --cflags) cmdmain.c 

#MAINCONFIG OBTIENE EL ARCHIVO OBJETO DE MAINCONFIG.C
mainconfig.o: mainconfig.c mainconfig.h
	gcc -c mainconfig.c
clean:
	rm -f exefin *.o