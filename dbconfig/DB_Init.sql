-- version 1.0
IF NOT EXISTS(
	SELECT name
	FROM sys.databases
	WHERE name = 'SDNBD'
);

CREATE DATABASE SDNBD;
USE SDNBD;

-- tabla Status admin 
-- catalogo donde se almacenan los status que llevaran los adminsitradores
CREATE TABLE Status_admin(
	Id_Tipo_Admin int(2) NOT NULL AUTO_INCREMENT,
	Nom_Tipo_Admin varchar(60) NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin)
);

-- insert con los status basicos de los administradores
INSERT INTO Status_admin(Nom_Tipo_Admin) VALUES ('Activo'),('Inactivo'),('Fuera del sistema');

-- tabla Status log--
-- catalogo donde se almacenan los status de los logs
CREATE TABLE Status_log(
	Id_Status_Log int(2) NOT NULL AUTO_INCREMENT,
	Num_Status_Log varchar(60) NOT NULL,
	PRIMARY KEY(Id_Status_log)
);

-- insert con los status basicos de los logs
INSERT INTO Status_log(Nom_Status_Log) VALUES ('En Ejecucion'),('Error'),('Completado');

-- tabla Tipo_Admin
-- catalogo donde se almacenan los tipo de administradores
CREATE TABLE Tipo_Admin(
	Id_Tipo_Admin int(2) NOT NULL AUTO_INCREMENT,
	Nom_Tipo_Admin varchar(60) NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin)
);

-- insert con el catalogo de administradores 
INSERT INTO Tipo_Admin(Nom_Tipo_Admin) VALUES ("Administrador"),("SuperAdministrador");

-- tabla Cat_Servicios
-- Catalogo los servicios los cuales los administradores van a utilizar
CREATE TABLE Cat_Servicios(
	Id_Cat_Servicios int(10) NOT NULL AUTO_INCREMENT,
	Nom_Cat_Servicios VARCHAR(60) NOT NULL,
	PRIMARY KEY(Id_Cat_Servicios)
);

-- insert con los servicios basicos que podran asignarle a los administradores.

INSERT INTO Cat_Servicios(Nom_Cat_Servicios) VALUES ("Iniciar Sesion"),("Cerrar Sesion"),("Modificar Datos Propios Administrador"),("Alta Administrador"),("Modificacion de Datos Administrador"),
("Fuera del sistema Administrador"),("Monitorizacion"),("Configuracion de Router"),("Configuracion de Switch"),("Configuracion de Servidor");


-- tabla Addministradores
-- Tabla donde se almacenaran todos los administradores y super administradores
CREATE TABLE Administradores(
	Id_Administradores int(10) NOT NULL AUTO_INCREMENT,
	Id_Status_Admin int(2) NOT NULL,
	Id_Tipo_Admin int(2) NOT NULL,
	Nombre_Admin varchar(60) NOT NULL,
	Apellido_P_Admin varchar(60) NOT NULL,
	Apellido_M_Admin varchar(60) NOT NULL,
	Fecha_ingreso datetime NOT NULL,
	Nombre_Usuario varchar(60) NOT NULL,
	Password_Hash varchar(60) NOT NULL,
	Fecha_Ultimo_Cambio_Pass datetime NOT NULL,
	Cant_dias_limit int(2)NOT NULL,
	PRIMARY KEY(Id_Administradores),
	FOREIGN KEY (Id_Status_Admin) REFERENCES Status_admin(Id_Tipo_Admin),
	FOREIGN KEY (Id_Tipo_Admin) REFERENCES Tipo_Admin(Id_Tipo_Admin)
);


-- tabla Tipo_Admin_Cat_Servicios
-- tabla donde se relacionan los permisos a los cuales los administradores y super administradores tienen permitido
CREATE TABLE Tipo_Admin_Cat_Servicios(
	Id_Tipo_Admin_Servicios int(10) NOT NULL AUTO_INCREMENT,
	Id_Tipo_Admin int(2) NOT NULL,
	Id_Cat_Servicios int(2) NOT NULL,
	Fecha_Ult_Mod datetime NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin_Servicios),
	FOREIGN KEY (Id_Tipo_Admin) REFERENCES Tipo_Admin(Id_Tipo_Admin),
	FOREIGN KEY (Id_Cat_Servicios) REFERENCES Cat_Servicios(Id_Cat_Servicios)
);

-- Tabla Administradores_Servicios_Log
-- tabla donde se almacenan los logs de las actividades de los adminsitradores

CREATE TABLE Administradores_Servicios_Log(
	Id_Administradores_Servicios_Log int(100) NOT NULL AUTO_INCREMENT,
	Id_Status_Log int(2) NOT NULL,
	Id_Administradores int(10) NOT NULL,
	Id_Cat_Servicios int(10) NOT NULL,
	IP_Dispositivo_Orig varchar(20) NOT NULL,
	MAC_Dispositivo_Orig varchar(20) NOT NULL,
	IP_Dispositivos_Ant varchar(20),
	IP_Dispositivos_Desp varchar(20),
	Dir_MAC_Disp_Fin varchar(30),
	Fecha_Init_Serv date NOT NULL,
	Fecha_Fin_Serv date NOT NULL,
	PRIMARY KEY(Id_Administradores_Servicios_Log),
	FOREIGN KEY (Id_Status_Log) REFERENCES Status_Log(Id_Status_Log),
	FOREIGN KEY (Id_Administradores) REFERENCES Administradores(Id_Administradores),
	FOREIGN KEY (Id_Cat_Servicios) REFERENCES Cat_Servicios(Id_Cat_Servicios)
);