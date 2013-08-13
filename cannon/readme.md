To run the project you need node.js and to install the following modules:

`npm install socket.io express serialport`

Then run the server with `node ./server.js` and open the cannon control page (localhost:8080 or your-ip:8080).

To control the cannon use the arrows or touch (if you have touch screen device).

Here is a [Vine with the concept](https://vine.co/v/hhPXA0EWuMh). I am still missing few parts to make a decent prototype.

Constructing the water tank:

If your water pump has short wires like mine or you can not put it in deep water, then you could use the [hydrostatic pressure](http://www.youtube.com/watch?v=Ffe7JfYyBFE) on your side (just a hole in a bottle :D).

Short overview of the architecture:
```
-----------                 -------------                 -----------
| Web     |  socket.io      | server.js |  serial port    | Arduino |
| Browser | --------------> |           | --------------> | Board   |
-----------                 -------------                 -----------
```
- socket.io let's you use WebSockets and it will gracefully fall back to other communication methods if WebSockets are no supported.
- server.js is a node application that will proxy instructions from the web browser to the serial port of the Arduino board.

Useful article about [sleep modes](http://donalmorrissey.blogspot.se/2010/04/sleeping-arduino-part-5-wake-up-via.html) and [power saving](http://www.gammon.com.au/forum/?id=11497).

