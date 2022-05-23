CREATE DATABASE SNMPDATA;

USE SNMPDATA;

CREATE TABLE Datos_SNMP(
    idAgente int NOT NULL,
    IPAgente VARCHAR(16),
    UserNameAgente VARCHAR(100),
    PassA VARCHAR(100),
    PassX VARCHAR(100),
     PRIMARY KEY (id)
);

CREATE TABLE Datos_Dispo(
    idDispo int NOT NULL
    NombreDispo VARCHAR (300),
    OIDConsultado VARCHAR(30),
    Memoria int,
    CPU int,
    AnchoB int,
    Storage int,
);