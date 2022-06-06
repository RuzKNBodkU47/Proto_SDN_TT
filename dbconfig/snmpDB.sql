CREATE DATABASE SNMPDATA;

USE SNMPDATA;

CREATE TABLE Datos_SNMP(
    idSegmentoDatos int NOT NULL AUTO_INCREMENT,
    IPAgente VARCHAR(16),
    UserNameAgente VARCHAR(100),
    PassA VARCHAR(100),
    PassX VARCHAR(100),
    OIDaConsultar VARCHAR(30),
    PRIMARY KEY (idSegmentoDatos)
);

CREATE TABLE Datos_Dispo(
    idSolicitud int NOT NULL AUTO_INCREMENT,
    NombreDispo VARCHAR (300),
    IPDispositivo VARCHAR (16),
    OIDConsultado VARCHAR(300),
    Memoria VARCHAR(50),
    CPU VARCHAR(50),
    AnchoB VARCHAR(50),
    Storage VARCHAR(50),
    PRIMARY KEY (idSolicitud)
);
