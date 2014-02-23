#include <SPI.h>

#define PIN_BL    3
#define PIN_DC    5
#define PIN_SCE   6
#define PIN_RESET 7
#define PIN_SDIN  11
#define PIN_SCLK  13
#define APIN_POT  1

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48

#define POT_MAX   690

// surrounding buffer zone of 8 dots
#define BUFFER_DOTS 8
#define MATRIX_W  (LCD_X + 2*BUFFER_DOTS)
#define MATRIX_H  ((LCD_Y + 2*BUFFER_DOTS) >> 3)

short potLevel;
short noRandomRevivalCounter = 200;

static byte matrixes[2][MATRIX_H][MATRIX_W];
byte currentMatrix;

inline byte nextGenerationMatrix() {
  return (currentMatrix + 1) & 1;
}

inline byte isAlive(byte x, byte y) {
  return (matrixes[currentMatrix][y >> 3][x] >> (y & 7)) & 1;
}

inline void setNextGenerationCellState(byte x, byte y, byte state) {
  if (state == 0) {
    matrixes[nextGenerationMatrix()][y >> 3][x] &= ~(1 << (y & 7));
  } else {
    matrixes[nextGenerationMatrix()][y >> 3][x] |= (1 << (y & 7));
  }
}

byte countNeighbours(byte x, byte y) {
  byte up = y + 1;
  byte down = y - 1;
  byte left = x - 1;
  byte right = x + 1;
  
  return isAlive(left, y) + isAlive(left, up) + isAlive(x, up) + isAlive(right, up) 
         + isAlive(right, y) + isAlive(right, down) + isAlive(x, down) + isAlive(left, down);
} 

void nextGeneration() {
  for (byte i = 1; i < (MATRIX_H << 3) - 1; i++) {
    for (byte j = 1; j < MATRIX_W - 1; j++) {
      byte neighbours = countNeighbours(j, i);
      byte newCellState = isAlive(j, i) && neighbours == 2 || neighbours == 3;
      setNextGenerationCellState(j, i, newCellState);
    }
  } 
}

void reviveRandomCells(byte n) {
  for (byte i = 0; i < n; i++) {
    byte x = random(0, MATRIX_W);
    byte y = random(0, MATRIX_H << 3);
    setNextGenerationCellState(x, y, 1);
  }
}

void createGosperGlider() {
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 0] = 0x60;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 1] = 0x60;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 10] = 0x70;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 11] = 0x88;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 12] = 0x04;
  matrixes[currentMatrix][(BUFFER_DOTS >> 3) + 1][BUFFER_DOTS + 12] = 0x01;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 13] = 0x04;
  matrixes[currentMatrix][(BUFFER_DOTS >> 3) + 1][BUFFER_DOTS + 13] = 0x01;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 14] = 0x20;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 15] = 0x88;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 16] = 0x70;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 17] = 0x20;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 20] = 0x1C;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 21] = 0x1C;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 22] = 0x22;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 24] = 0x63;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 34] = 0x0C;
  matrixes[currentMatrix][BUFFER_DOTS >> 3][BUFFER_DOTS + 35] = 0x0C;
}

void lcdDrawMatrix() {
  for (byte i = BUFFER_DOTS >> 3; i < MATRIX_H - (BUFFER_DOTS >> 3); i++) {
    for (byte j = BUFFER_DOTS; j < MATRIX_W - BUFFER_DOTS; j++) {
      lcdWrite(LCD_D, matrixes[currentMatrix][i][j]);
    }
  }
}

void lcdInitialise(void) {
  pinMode(PIN_BL, OUTPUT);
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV64);

  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  lcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  lcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast).
  lcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  lcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  lcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
  lcdWrite(LCD_C, 0x20 );
  lcdWrite(LCD_C, 0x0C );
  lcdWrite(LCD_C, 0x80);   // Set position X = 0
  lcdWrite(LCD_C, 0x40);   // Set position Y = 0
}

void lcdWrite(byte dc, byte data) {
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  SPI.transfer(data);
  digitalWrite(PIN_SCE, HIGH);
}

void backlightLevel() {
  potLevel = analogRead(APIN_POT);
  byte brightness = map(potLevel, 0, POT_MAX, 0, 0xFF);
  analogWrite(PIN_BL, brightness);
}

void setup(void) {
  currentMatrix = 0;
  createGosperGlider();
  
  lcdInitialise();
  randomSeed(analogRead(0));
}

void loop(void) {
  backlightLevel();
  
  lcdDrawMatrix();
  
  // calculate the next generation and revive few cells to prevent "still life"
  nextGeneration();

  // bring some random cells to life, but not in the very beginning of the game
  if (noRandomRevivalCounter > 0) {
    noRandomRevivalCounter--;
  } else {
    reviveRandomCells(5);
  }

  currentMatrix = nextGenerationMatrix();

  // Regulate the speed of the game using the potentiometer.
  // Also add some tolerance to be able to run at full speed - no delays.
  if (POT_MAX - potLevel - 20 > 0) {
    delay((POT_MAX - potLevel) >> 1);
  }
}
