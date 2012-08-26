// @todo: rewrite it in CoffeeScript

var express = require("express");
var app = express();
var server = app.listen(8080);
var io = require('socket.io').listen(server);

var sys = require('sys');
var repl = require('repl');
var SerialPort = require('serialport').SerialPort;

app.get('/', function(req, res) {
  res.sendfile(__dirname + '/radar.html');
});

io.sockets.on('connection', function(socket) {
	
	var buffer = '';
	var i;
	
	var serial = new SerialPort('COM3', { baudrate : 9600 });
	serial.on('data', function(chunk) {
		buffer += chunk;
		if (buffer.indexOf(';') > -1) {
			var messages = buffer.split(';');
			for (i = 0; i < messages.length - 1; i++) {
				sys.puts(messages[i]);
				socket.emit('radar_data', { data: messages[i] });
			}
			buffer = messages[messages.length-1];
		}
	});
});
