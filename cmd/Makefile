#MAKEFILE PARA COMPILAR TODO CMD
CC = gcc
MYSQLCONFIGLIBS = mysql_config --libs
MYSQLCONFIGFLAGS = mysql_config --cflags
MYSQLFLAGS = -lmysqlclient
OBJS = main.o mainlogin.o mainverif.o mainfunusers.o 
BINARY = exefin
MAINOBJS = main.c mainlogin.h
LOGINOBJS = mainlogin.c mainlogin.h
VERIFOBJS = mainverif.c mainverif.h
FUNUSERSOBJS = mainfunusers.c mainfunusers.h 
CONFIGOBJS = mainconfig.c mainconfig.h
CMDOBJS = cmdmain.c cmdmain.h

INCLUDECMDMAIN = -I../cmd
#BINARY1 = BDcontrolador
#CFLAGS = -g -Wall


all: mainexe

#MAINEXE COMPILA EL ARCHIVO PRINCIPAL
mainexe: $(OBJS)
	$(CC) -o $(BINARY) $(OBJS)  $(shell MYSQLCONFIGFLAGS)  -Wall
#MAIN.O OBTIENE EL ARCHIVO OBJETO DEL MAIN
main.o:$(MAINOBJS)
	$(CC) -c main.c
#MAINLOGIN OBTIENE EL ARCHIVO OBJETO DE MAINLOGIN.C 
mainlogin.o: $(LOGINOBJS)
	$(CC) -c mainlogin.c
#MAINVERIF OBTIENE EL ARCHIVO OBJETO DE MAINVERIF.C
mainverif.o: $(VERIFOBJS)
	$(CC) -c mainverif.c  
#MAINFUNUSERS OBTIENE EL ARCHIVO OBJETO DE MAINFUNUSERS,C
mainfunusers.o: $(FUNUSERSOBJS)
	$(CC) -c mainfunusers.c $(INCLUDECMDMAIN) -lcmdmain
#MAINCONFIG OBTIENE EL ARCHIVO OBJETO DE MAINCONFIG.C
mainconfig.o: $(CONFIGOBJS)
	$(CC) -c mainconfig.c 

#cmdmainexe: $(OBJS1)
#	gcc -o $(BINARY1) $(OBJS1) $(mysql_config --libs) -lmysqlclient

#MAIN.O GEMERA EL ARCHIVO OBJETO DEL MAIN
cmdmain.o: $(CMDOBJS)
	gcc -c $(shell MYSQLCONFIGLIBS) cmdmain.c 

#MAINCONFIG OBTIENE EL ARCHIVO OBJETO DE MAINCONFIG.C

clean:
	rm -f exefin *.o


