var express = require('express');
var app = express();
var server = app.listen(8080);
var io = require('socket.io').listen(server);

var sys = require('sys');
var repl = require('repl');
var SerialPort = require('serialport').SerialPort;
var serial = new SerialPort('COM3', { baudrate : 9600 });

app.get('/', function(req, res) {
  res.sendfile(__dirname + '/index.html');
});

io.sockets.on('connection', function(socket) {
    
    socket.on('update', function(data) {
        console.log('data', data);
        var message = data.rotationAngle + ',' + (data.isBlasting ? 1 : 0) + '\n';
        serial.write(message, function(err, results) {
            console.log('err ' + err);
            console.log('results ' + results);
        });
    });
    
});
