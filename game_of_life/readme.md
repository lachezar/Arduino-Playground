# Game of Life using Arduino Uno and Nokia display

![blueprint](https://raw2.github.com/lucho-yankov/Arduino-Playground/master/game_of_life/game_of_life.png)

Check out this Vine for demo: [https://vine.co/v/MmhM5ihpmPp](https://vine.co/v/MmhM5ihpmPp)

Wiki entry for Game of Life: [http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

## Recent changes

The Nokia 5110 LCD requires pin voltage in the range of 2.7V to 3.3V and the Arduino Uno board runs on 5V, so I had to add [voltage divider](http://en.wikipedia.org/wiki/Voltage_divider) resistors - pairs of 2.4kOhm and 3.6kOhm. 

The formula is: Vout = (Vin * R2) / (R1 + R2) = (5 * 3.6) / (2.4 + 3.6) = 3V

The code grows a little bit too much for a single file and the reason for this is the surrounding functionality like "Create Gosper Glider pattern" or "Adjust game speed with a potentiometer". May be I will refactor it one day.
