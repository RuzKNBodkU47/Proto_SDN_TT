IF NOT EXISTS(
	SELECT name
	FROM sys.databases
	WHERE name = N'SDNBD'
)

CREATE DATABASE SDNBD
USE SDNBD


CREATE TABLE Status_admin(
	Id_Tipo_Admin int NOT NULL,
	Nom_Tipo_Admin varchar(60) NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin)
)


CREATE TABLE Status_log(
	Id_Status_Log int NOT NULL,
	Num_Status_Log varchar(60) NOT NULL,
	PRIMARY KEY(Id_Status_log)
)


CREATE TABLE Tipo_Admin(
	Id_Tipo_Admin int NOT NULL,
	Nom_Tipo_Admin varchar(60) NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin)
)


CREATE TABLE Cat_Servicios(
	Id_Cat_Servicios int NOT NULL,
	Nom_Cat_Servicios VARCHAR(60) NOT NULL,
	PRIMARY KEY(Id_Cat_Servicios)
)


CREATE TABLE Administradores(
	Id_Administradores int NOT NULL,
	Id_Status_Admin int NOT NULL,
	Id_Tipo_Admin int NOT NULL,
	Apellido_P_Admin char(60) NOT NULL,
	Apellido_M_Admin char(60) NOT NULL,
	Fecha_ingreso datetime NOT NULL,
	Password_Hash varchar(60) NOT NULL,
	Nombre_Usuario varchar(60) NOT NULL,
	Fecha_Ultimo_Cambio_Pass datetime NOT NULL,
	PRIMARY KEY(Id_Administradores),
	FOREIGN KEY (Id_Status_Admin) REFERENCES Status_admin(Id_Tipo_Admin),
	FOREIGN KEY (Id_Tipo_Admin) REFERENCES Tipo_Admin(Id_Tipo_Admin)
)


CREATE TABLE Tipo_Admin_Cat_Servicios(
	Id_Tipo_Admin_Servicios int NOT NULL,
	Id_Tipo_Admin int NOT NULL,
	Id_Cat_Servicios int NOT NULL,
	Fecha_Ult_Mod datetime NOT NULL,
	PRIMARY KEY(Id_Tipo_Admin_Servicios),
	FOREIGN KEY (Id_Tipo_Admin) REFERENCES Tipo_Admin(Id_Tipo_Admin),
	FOREIGN KEY (Id_Cat_Servicios) REFERENCES Cat_Servicios(Id_Cat_Servicios)
)


CREATE TABLE Administradores_Servicios_Log(
	Id_Administradores_Servicios_Log int NOT NULL,
	Id_Status_Log int NOT NULL,
	Id_Administradores int NOT NULL,
	Id_Cat_Servicios int NOT NULL,
	Id_Dispositivos_Ant int NOT NULL,
	Id_Dispositivos_Desp int NOT NULL,
	Fecha_Eliminado datetime NOT NULL,
	PRIMARY KEY(Id_Administradores_Servicios_Log),
	FOREIGN KEY (Id_Status_Log) REFERENCES Status_Log(Id_Status_Log),
	FOREIGN KEY (Id_Administradores) REFERENCES Administradores(Id_Administradores),
	FOREIGN KEY (Id_Cat_Servicios) REFERENCES Cat_Servicios(Id_Cat_Servicios)
)
