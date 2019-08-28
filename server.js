//Módulos Necesitados
const express = require('express');
const cookieParser = require('cookie-parser');
const bodyParser = require('body-parser');
const cors = require('cors');

//Conexión con el Broker de MQTT
const mqtt = require('mqtt'); 
const mqttOptions = {host:'great-lawyer.cloudmqtt.com', port:'1883', username:'cboiwkvz', password:'NYfafrwlNXIt'};
let client = mqtt.connect(mqttOptions);

//Inicialización del server que escucha las solicitudes HTTP
let app = express();
app.use(express.logger('dev'));     /* 'default', 'short', 'tiny', 'dev' */
app.use(bodyParser.urlencoded({
  extended: true
}));
app.use(bodyParser.json());

//Ruteo de los archivos estáticos para correr diferentes aplicaciones
app.use(express.static(__dirname + '/dk'));
app.use('/hard', express.static(__dirname + '/hard'));

//CORS para permitir solicitudes de cualquier origen
app.all('*', (req, res, next) => {
  res.header('Access-Control-Allow-Origin', '*');
  res.header('Access-Control-Allow-Methods', 'PUT, GET, POST, DELETE, OPTIONS');
  res.header('Access-Control-Allow-Headers', 'Content-Type, Origin, X-Requested-With, Content-Type, Accept, Access-Control-Allow-Origin');
  next();
});

//Escucha cuando el cliente MQTT se conecte
client.on('connect', () => { // When connected
  console.log('Connected')
  client.subscribe('move/#', () => {

  });
  client.subscribe('banana/#', () => {
    
  });

  client.on('message', (topic, message, packet) => {

    console.log(topic);
    if(topic.split('/')[0] === 'banana'){
          
      let msgJson = JSON.parse(message);
      console.log(topic);
      console.log(msgJson);
    }
  });

  // publish a message to a topic
  client.publish('flag/rocks', {'mensaje':'Adrián Rockea'}, () => {
    console.log("Message is published");
    //client.end(); // Close the connection when published
  });
})

app.get('*', (req, res) => {
    res.redirect('../#home', 404);
});

//Obtención del puerto a escuchar
const port = Number(process.env.PORT || 3000);
app.listen(port);
console.log('Listening on port ' + port + '...');
