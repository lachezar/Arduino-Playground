To run the project you need node.js and to install the following modules:

`npm install socket.io express serialport`

Then run the server with `node ./server.js` and open the cannon control page (localhost:8080 or your-ip:8080).

To control the cannon use the arrows or touch (if you have touch screen device).

Here is a [Vine with the concept](https://vine.co/v/hhPXA0EWuMh). <del>I am still missing few parts to make a decent prototype.</del> Here is a [video with the fully operational cannon](www.youtube.com/watch?v=kpN9SZHvAV).

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


Info about the used components:
- [Water pump](http://dx.com/p/szf280-pvc-mini-water-pump-motor-beige-205304)
- 4 x AA to power the pump
- Battery holder
- 2N3904 transistor to turn on/off the water pump
- 1N4001 diode to stop the back-emf
- LED
- 2 x 220ohm resistors
- 3.3Kohm resistor
- Servo ... 3v, tiny servo will be good enough (it is just directing the water cannon)
- Arduino Uno (or any other DIY board)
- Bottle(s) - use this [nifty trick](http://www.youtube.com/watch?v=Ffe7JfYyBFE) to keep the water level low
- Shallow tank/pot/bowl
- Hose - I bought 3mm wide hose, but I needed 5mm, so I heated one of the ends of the hose with a lighter and expanded its size to fit the water pump tap. I also heated the hose in the other end to make it [more flexible and easier for the servo to bend](http://i.imgur.com/MZq9dSp.jpg?3) it. 
 
![water cannon photo](http://i.imgur.com/fMhkEA6.jpg?1)
