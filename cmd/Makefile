#MAKEFILE PARA COMPILAR TODO CMD
CC = gcc
MYSQLCONFIGLIBS = 'mysql_config --libs'
MYSQLCONFIGFLAGS = 'mysql_config --cflags'
MYSQLFLAGS = -lmysqlclient
OBJS = main.o mainlogin.o mainverif.o mainfunusers.o 
BINARY = exefin
MAINOBJS =  mainlogin.h
LOGINOBJS = mainlogin.h
VERIFOBJS =  mainverif.h
FUNUSERSOBJS = mainfunusers.h cmdmain.h
CONFIGOBJS =  mainconfig.h
CMDOBJS = cmdmain.h
REDOBJS = libred.h
INCLUDECMDMAIN = -I

#BINARY1 = BDcontrolador
#CFLAGS = -g -Wall


all: mainexe

#MAINEXE COMPILA EL ARCHIVO PRINCIPAL
mainexe: $(OBJS)
	$(CC) -g -Wall $(OBJS) -o  $(BINARY)  -I/usr/include/mysql -I/usr/include/mysql/mysql -lmysqlclient -lmariadb   
#MAIN.O OBTIENE EL ARCHIVO OBJETO DEL MAIN
main.o:$(MAINOBJS)
	$(CC) -g -c -Wall main.c 
#MAINLOGIN OBTIENE EL ARCHIVO OBJETO DE MAINLOGIN.C 
mainlogin.o: $(LOGINOBJS)
	$(CC) -g -c -Wall mainlogin.c 
#MAINVERIF OBTIENE EL ARCHIVO OBJETO DE MAINVERIF.C
mainverif.o: $(VERIFOBJS)
	$(CC) -g -c -Wall mainverif.c  
#MAINFUNUSERS OBTIENE EL ARCHIVO OBJETO DE MAINFUNUSERS,C
mainfunusers.o: $(FUNUSERSOBJS)
	$(CC) -g -c -Wall mainfunusers.c 
#MAINCONFIG OBTIENE EL ARCHIVO OBJETO DE MAINCONFIG.C
mainconfig.o: $(CONFIGOBJS)
	$(CC) -g -c -Wall mainconfig.c 

#MAIN.O GEMERA EL ARCHIVO OBJETO DEL MAIN
cmdmain.o: $(CMDOBJS)
	$(CC) -g -c -Wall  cmdmain.c 
libred.o: $(REDOBJS)
	$(CC) -g -c Wall libred.c

clean:
	rm -f exefin *.o


