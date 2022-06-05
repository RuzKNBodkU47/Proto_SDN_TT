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
    OIDConsultado VARCHAR(30),
    Memoria VARCHAR(20),
    CPU VARCHAR(20),
    AnchoB VARCHAR(20),
    Storage VARCHAR(20),
    PRIMARY KEY (idSolicitud),
    SegData int NOT NULL,
    FOREIGN KEY(SegData) REFERENCES Datos_SNMP(idSegmentoDatos)
);
