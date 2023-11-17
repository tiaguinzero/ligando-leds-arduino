const express = require('express')
const { path } = require('express/lib/application')
const { SerialPort, ReadlineParser } = require('serialport')

const app = express()

var arduinoPort = 'COM10'

const sp = new SerialPort(
    {path:arduinoPort, baudRate: 9600}, function (err){
        if (err){
            return console.log("erro" + err.message)
        }
    }
)

const parser = new ReadlineParser(
    {delimeter: '\r\n',}
)

sp.pipe(parser)

sp.on('open', function(){
    console.log("Serial port on" + arduinoPort)
})

parser.on('data', data =>{
    console.log(data.toString())
})
//rota 
app.get('/', function(req,res){
    return res.send("Funcionando...")
})

app.get('/:action',function(req,res){
    var action = req.params.action || req.param('action')

    if (action == 'on'){
        sp.write("o")
        return res.send('<h1>Led ligado</h1>')
    }
    if (action == 'off'){
        sp.write("f")
        return res.send('<h1>Led desligado</h1>')
    }
    return res.send('Action' + action)
})


//iniciando porta para escutar

var port = 3000

app.listen(port,function(){
    console.log("Escutando na porta : " + port)
})