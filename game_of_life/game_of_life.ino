#define PIN_BL    8
#define PIN_RESET 7
#define PIN_SCE   6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3
#define PIN_BTN   2

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48

// surrounding buffer zone of 8 dots
#define BUFFER_DOTS 8
#define MATRIX_W  (LCD_X + 2*BUFFER_DOTS)
#define MATRIX_H  ((LCD_Y + 2*BUFFER_DOTS) >> 3)

static byte matrixes[2][MATRIX_H][MATRIX_W];
byte currentMatrix;

byte blState = HIGH;
byte btnState = LOW;

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
  pinMode(PIN_BTN, INPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  lcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  lcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  lcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  lcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
  lcdWrite(LCD_C, 0x20 );
  lcdWrite(LCD_C, 0x0C );
}

void lcdWrite(byte dc, byte data) {
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

void toggleBacklight() {
  if (btnState == LOW && digitalRead(PIN_BTN) == HIGH) {
    btnState = HIGH;
    blState = (blState + 1) & 1;
    digitalWrite(PIN_BL, blState);
  } else {
    // debounce
    btnState = LOW;
  }
}

void setup(void) {
  currentMatrix = 0;
  // initial state
  matrixes[currentMatrix][5][50] = 255;
  matrixes[currentMatrix][3][22] = 127;
  matrixes[currentMatrix][3][23] = 63;
  matrixes[currentMatrix][3][24] = 31;
  
  lcdInitialise();
  // turn on the back light
  digitalWrite(PIN_BL, blState);
}

void loop(void) {
  toggleBacklight();
  
  lcdDrawMatrix();
  
  // calculate the next generation and revive few cells to prevent "still life"
  nextGeneration();
  reviveRandomCells(5);
  
  currentMatrix = nextGenerationMatrix();
}
