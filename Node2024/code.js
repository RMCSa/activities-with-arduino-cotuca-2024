const express = require("express");
const { SerialPort, ReadlineParser } = require("serialport");

const app = express();

var arduinoPort = "/dev/cu.usbserial-2210";

const sp = new SerialPort({ path: arduinoPort, baudRate: 9600 }, function (
  err
) {
  if (err) {
    return console.log(`Erro: ${err.message}`);
  }
});

const parser = new ReadlineParser({ delimiter: "\r\n" });

sp.pipe(parser);
sp.on("open", function () {
  console.log(`Serial port on ${arduinoPort}`);
});

parser.on("data", (data) => {
  console.log(data.toString());
});

// definição das rotas
app.get("/", function (req, res) {
  return res.send("funcionando...");
});

app.get("/:codigo", function (req, res) {
  var codigo = req.params.codigo.toString() || req.param("codigo").toString(); 
    
  if (codigo == "1" || codigo == "2") {
    console.log(codigo);
    sp.write(codigo);
    return res.send(`<h1>Efeito ${codigo}</h1>`);
  }

  return res.send("Efeito inexistente : " + codigo);
});

var port = 3000;
app.listen(port, function () {
  console.log(`Escutando na porta : ${port}`);
});
