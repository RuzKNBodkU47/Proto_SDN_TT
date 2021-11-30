#Dockerfile donde se encontrara nuestro prototipo
FROM fedora:34

LABEL MAINTAINER JorgeAgula <jorge_ag2468@outlook.com>

# Actualizamos el sistema
RUN dnf upgrade -y \ 
    && dnf clean all 

RUN mkdir cmd


# Instalamos MariaDB
RUN dnf install -y mariadb-server
EXPOSE 3306
LABEL version="1.0"
LABEL description="MariaDB Servidor ProtoSDNTT"
HEALTHCHECK --start-period=5m \
  CMD mariadb -e 'SELECT @@datadir;' || exit 1
CMD ["mysqld"]

RUN mkdir dbconfig

ADD  dbconfig/  /dbconfig/

WORKDIR /dbconfig

RUN chmod 700 /containerstart.sh

# Instalamos nginx
RUN dnf install -y nginx \
  	&& dnf clean all \
  	&& rm -rf /var/cache/yum
RUN mkdir web 