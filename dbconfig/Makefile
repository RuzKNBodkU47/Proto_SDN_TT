#MAKEFILE PARA COMPILAR CONTROLADORES DE BASE DE DATOS

OBJS = cmdmain.o 
BINARY = BDcontrolador

all: mainexe
#MAINEXE COMPILA EL ARCHIVO PRINCIPAL
mainexe: $(OBJS)
	gcc -o $(BINARY) $(OBJS) $(mysql_config --libs) -lmysqlclient
#MAIN.O GEMERA EL ARCHIVO OBJETO DEL MAIN
main.o: cmdmain.c cmdmain.h
	gcc -c $(mysql_config --cflags) cmdmain.c 

clean2:
	rm -f $(BINARY) *.o

clean:
	rm -f *.o
