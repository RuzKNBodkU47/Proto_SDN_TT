#!/bin/bash

echo "[+]Comenzando la configuracion de MariaDB"

VAR=1
while [[ RET -ne 0 ]]; do
    echo "=> Esperando la confirmacion del inicio del servicio de MariaDB"
    sleep 5
    mysql -uroot -p${MYSQL_ROOT_PASSWORD} -e "status" > /dev/null 2>&1
    VAR=$?
done

echo "Validando la base de datos a importar desde las variables de entorno";

if [ -n "$INSTALL_SDNTT" ]; then
    echo "=> Importando la base de datos DB_Init.sql"
    mysql -uroot -p${MYSQL_ROOT_PASSWORD} -e "CREATE DATABASE SDNTT"
    mysql -uroot -p${MYSQL_ROOT_PASSWORD} SDNTT < DB_Init.sql
fi

echo "[+] Otorgando acceso a la base de datos '${MYSQL_USER}'"
mysql -uroot -p${MYSQL_ROOT_PASSWORD} -e "GRANT ALL PRIVILEGES ON *.* TO '${MYSQL_USER}'@'%' WITH GRANT OPTION"


echo "[+]Finalizacion de containerstart.sh"