
//Exportamos módulos para el servidor
module.exports = (app) =>{
    //Levantamos el servidor
    app.listen(process.env.PORT,() =>{
        console.log(`Servidor levantado en: http://${process.env.HOST}:$${process.env.PORT}`);
    });

    //Métodos POST
    app.post('/tipocomponente',midd.ComponenteValido(componente), async(req, res) => {
        try{

        }catch(error){
            console.log(error)
            res.status(400).send('Ocurrio un error durante la operacion');
        }
    })
}