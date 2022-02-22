//Inicialización del server
//Modulos Express
const http = require("http");
const express = require("express");
const app = express();

//CORS
const cors = require("cors");
//Dotenv
require("dotenv").config();

//Middlewares globales
app.use(express.json());
app.use(express.urlencoded({extended: true}));

app.use(function (req, res, next) {
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    res.setHeader("Access-Control-Allow-Headers", "Content-Type");
    res.setHeader("Access-Control-Allow-Credentials", true);
    next();
});

async function serverStart(){
    try{
        app.listen(process.env.PORT, process.env.HOST, () => {
            console.log(`Servidor iniciado en http://${process.env.HOST}:${process.env.PORT}`)
        });
    }catch(error){
        console.error('Hubo un error con la conexion')
    }
}

serverStart();
