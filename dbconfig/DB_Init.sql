-- version 1.0
IF NOT EXISTS(
	SELECT name
	FROM sys.databases
	WHERE name = 'SDNTT'
);

CREATE DATABASE SDNTT2;
USE SDNTT2;

-- tabla Status admin 
-- catalogo donde se almacenan los status que llevaran los adminsitradores

CREATE TABLE status_admin(
	Id_Status_Admin INT(2) NOT NULL AUTO_INCREMENT,
	Nom_Tipo_Admin VARCHAR(60) NOT NULL,
	PRIMARY KEY(Id_Status_Admin)
);

-- insert con los status basicos de los administradores
INSERT INTO status_admin(Nom_Tipo_Admin) VALUES ('Activo'),('Inactivo'),('Fuera del sistema');

-- tabla Status log--
-- catalogo donde se almacenan los status de los logs
CREATE TABLE status_log(
	Id_Status_Log int(2) NOT NULL AUTO_INCREMENT,
	Nom_Status_Log varchar(60) NOT NULL,
	PRIMARY KEY(Id_Status_log)
);

-- insert con los status basicos de los logs
INSERT INTO status_log(Nom_Status_Log) VALUES ('En Ejecucion'),('Error'),('Completado');

-- tabla Tipo_Admin
-- catalogo donde se almacenan los tipo de administradores
CREATE TABLE tipo_admin(
	Id_Tipo_Admin int(2) NOT NULL AUTO_INCREMENT,
	Nom_Tipo_Admin varchar(60) NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin)
);

-- insert con el catalogo de administradores 
INSERT INTO tipo_admin(Nom_Tipo_Admin) VALUES ("Administrador"),("SuperAdministrador");

-- tabla Cat_Servicios
-- Catalogo los servicios los cuales los administradores van a utilizar
CREATE TABLE cat_servicios(
	Id_Cat_Servicios int(10) NOT NULL AUTO_INCREMENT,
	Nom_Cat_Servicios VARCHAR(60) NOT NULL,
	PRIMARY KEY(Id_Cat_Servicios)
);

-- insert con los servicios basicos que podran asignarle a los administradores.

 INSERT INTO cat_servicios(Nom_Cat_Servicios) VALUES ("Monitorizacion"),("Configuracion de Router"),("Configuracion de Switch"),("Configuracion de Servidor");
-- tabla Cat_Tables
-- catalogo de las tareas que pueden realizar los administradores
CREATE TABLE cat_tareas(
	Id_Cat_Tareas int(10) NOT NULL AUTO_INCREMENT,
	Nom_Cat_Tareas varchar(60) NOT NULL,
	PRIMARY KEY (Id_Cat_Tareas)
);

-- insert con los servicios basicos que podran asignarle a los administradores.

	INSERT INTO cat_tareas (Nom_Cat_Tareas) VALUES ("Iniciar Sesion"),('Cerrar Sesion'),("Modificar Datos Propios Administrador"),("Alta Administrador"),("Modificacion de Datos Administrador"),
	("Eliminar Administrador"),("Eliminar Privilegios"),("Agregar Privilegios");

-- tabla Addministradores
-- Tabla donde se almacenaran todos los administradores y super administradores
CREATE TABLE administradores(
	Id_Administradores int(10) NOT NULL AUTO_INCREMENT,
	Id_Status_Admin int(2) NOT NULL,
	Id_Tipo_Admin int(2) NOT NULL,
	Nombre_Admin varchar(60) NOT NULL,
	Apellido_P_Admin varchar(60) NOT NULL,
	Apellido_M_Admin varchar(60) NOT NULL,
	Fecha_ingreso varchar(60) NOT NULL,
	Nombre_Usuario varchar(60) NOT NULL,
	Password_Hash varchar(60) NOT NULL,
	Fecha_Ultimo_Cambio_Pass varchar(60) NOT NULL,
	Cant_dias_limit int(2)NOT NULL,
	PRIMARY KEY(Id_Administradores),
	FOREIGN KEY (Id_Status_Admin) REFERENCES status_admin(Id_Status_Admin),
	FOREIGN KEY (Id_Tipo_Admin) REFERENCES tipo_admin(Id_Tipo_Admin)
);

-- insert de usuario root inicial

INSERT INTO administradores(Id_Status_Admin,Id_Tipo_Admin,Nombre_Admin,Apellido_P_Admin,Apellido_M_Admin,Fecha_ingreso,Nombre_Usuario,Password_Hash,Fecha_Ultimo_Cambio_Pass,Cant_dias_limit)
VALUES (1,2,"ipn","sdn","sdn",now(),"SDNTTROOT","root",now(),0);

-- tabla Tipo_Admin_Cat_Servicios
-- tabla donde se relacionan los permisos a los cuales los administradores y super administradores tienen permitido
CREATE TABLE tipo_admin_cat_servicios(
	Id_Tipo_Admin_Servicios int(10) NOT NULL AUTO_INCREMENT,
	Id_Administrador int(2) NOT NULL,
	Id_Cat_Servicios int(2) NOT NULL,
	Fecha_Ult_Mod VARCHAR(60) NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin_Servicios),
	FOREIGN KEY (Id_Administrador) REFERENCES administradores(Id_Administradores),
	FOREIGN KEY (Id_Cat_Servicios) REFERENCES cat_servicios(Id_Cat_Servicios)
);


-- tabla Tipo_Admin_Cat_Servicios
-- tabla donde se relacionan los permisos a los cuales los administradores y super administradores tienen permitido
CREATE TABLE tipo_admin_cat_tareas(
	Id_Tipo_Admin_tareas int(10) NOT NULL AUTO_INCREMENT,
	Id_Administrador int(2) NOT NULL,
	Id_Cat_Tareas int(2) NOT NULL,
	Fecha_Ult_Mod varchar(60) NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin_Servicios),
	FOREIGN KEY (Id_Administrador) REFERENCES administradores(Id_Administradores),
	FOREIGN KEY (Id_Cat_Tareas) REFERENCES cat_tareas(Id_Cat_Tareas)
);
-- Tabla Administradores_Servicios_Log
-- tabla donde se almacenan los logs de las actividades de los adminsitradores

CREATE TABLE administradores_servicios_log(
	Id_Administradores_Servicios_Log int(100) NOT NULL AUTO_INCREMENT,
	Id_Status_Log int(2) NOT NULL,
	Id_Administradores int(10) NOT NULL,
	Id_Cat_Servicios int(10) NOT NULL,
	IP_Dispositivo_Orig varchar(20) NOT NULL,
	MAC_Dispositivo_Orig varchar(30) NOT NULL,
	IP_Dispositivos_Ant varchar(20),
	IP_Dispositivos_Desp varchar(20),
	Dir_MAC_Disp_Fin varchar(30),
	Fecha_Init_Serv varchar(60) NOT NULL,
	Fecha_Fin_Serv varchar(60) NOT NULL,
	PRIMARY KEY(Id_Administradores_Servicios_Log),
	FOREIGN KEY (Id_Status_Log) REFERENCES status_log(Id_Status_Log),
	FOREIGN KEY (Id_Administradores) REFERENCES administradores(Id_Administradores),
	FOREIGN KEY (Id_Cat_Servicios) REFERENCES cat_servicios(Id_Cat_Servicios)
);

-- Tabla Administradores_Tareas_Log
-- tabla donde se almacenan los logs de las actividades de los adminsitradores

CREATE TABLE administradores_tareas_log(
	Id_Administradores_Tareas_Log int(100) NOT NULL AUTO_INCREMENT,
	Id_Status_Log int(2) NOT NULL,
	Id_Administradores int(10) NOT NULL,
	Id_Cat_Tareas int(10) NOT NULL,
	IP_Dispositivo_Orig varchar(20) NOT NULL,
	MAC_Dispositivo_Orig varchar(30) NOT NULL,
	Id_Admin_Obj int(10),
	Fecha_Init_Serv varchar(60) NOT NULL,
	Fecha_Fin_Serv varchar(60) NOT NULL,
	PRIMARY KEY(Id_Administradores_Tareas_Log),
	FOREIGN KEY (Id_Status_Log) REFERENCES status_log(Id_Status_Log),
	FOREIGN KEY (Id_Administradores) REFERENCES administradores(Id_Administradores),
	FOREIGN KEY (Id_Cat_Tareas) REFERENCES cat_tareas(Id_Cat_Tareas),
	FOREIGN KEY (Id_Admin_Obj) REFERENCES administradores(Id_Administradores)
);