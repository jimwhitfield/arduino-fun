#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>    // Core graphics library

// wiring with UNO or Mega2560:
//--------------POWER Pins--------------------------------
//   5V  connects to DC 5V
//   GND connects to Ground
//   3V3 do not need to connect(NC)
//--------------LCD Display Pins--------------------------
//   LCD_RD   connects to Analog pin A0
//   LCD_WR   connects to Analog pin A1
//   LCD_RS   connects to Analog pin A2
//   LCD_CS   connects to Analog pin A3
//   LCD_RST  connects to Analog pin A4
//   LCD_D0   connects to digital pin 8
//   LCD_D1   connects to digital pin 9
//   LCD_D2   connects to digital pin 2
//   LCD_D3   connects to digital pin 3
//   LCD_D4   connects to digital pin 4
//   LCD_D5   connects to digital pin 5
//   LCD_D6   connects to digital pin 6
//   LCD_D7   connects to digital pin 7
//--------------SD-card fuction Pins ----------------------
//This Connection Only for UNO, Do not support Mega2560
//because they use different Hardware-SPI Pins
//SD_SS    connects to digital pin 10
//SD_DI    connects to digital pin 11
//SD_DO    connects to digital pin 12
//SD_SCK   connects to digital pin 13

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3   // Chip Select goes to Analog 3
#define LCD_CD A2  // Command/Data goes to Analog 2
#define LCD_WR A1  // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

MCUFRIEND_kbv tft;

int units_x, units_y;
int units_w = 220, units_h = 50;
int logo_x, logo_y;
int logo_w = 360, logo_h = 50;

int rot = 1; // USB at top = 0.  rotate clockwise 90 degrees = 1

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  tft.reset();

  uint16_t identifier = tft.readID();
  if (identifier == 0x9481) {
    Serial.println(F("Found 9481 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    //identifier=0x9481;
  }
  tft.begin(identifier);

  srand(123);
  tft.fillScreen(BLACK);
  Serial1.begin(19200);
  Serial.begin(19200);
  //tft.fillRect(x, y, velo_w, velo_h, BLACK);
  //tft.setCursor(x, y);
  //tft.setTextColor(WHITE);
  //tft.setTextSize(6);
  //tft.println("Hello");

  if (rot == 0 || rot == 2) {
    units_x = 80;
    units_y = 120;
    logo_x = 30;
    logo_y = 160;
  } else {
    units_x = 180;
    units_y = 170;
    logo_x = 95;
    logo_y = 230;
  }

  tft.setRotation(rot);

  tft.fillRect(units_x, units_y, units_w, units_h, BLACK);
  tft.setCursor(units_x, units_y);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.println("km / h");

  tft.fillRect(logo_x, logo_y, logo_w, logo_h, BLACK);
  tft.setCursor(logo_x, logo_y);
  tft.setTextColor(CYAN);
  tft.setTextSize(4);
  tft.println("OmniPreSense");

}

char buf[100];
int buf_idx = 0;

int velo_x, velo_y;
int velo_w = 240, velo_h = 60;


void loop(void) {

  if (rot == 0 || rot == 2) {
    velo_x = 80;
    velo_y = 30;
  } else {
    velo_x = 150;
    velo_y = 80;
  }

  char incomingByte;

  // Gather the reading until end of line, then display it
  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    if (incomingByte == '\n' || incomingByte == '\r') {
      buf[buf_idx] = '\0';
      if (buf_idx > 0 && buf[0] != '{') {
        tft.fillRect(velo_x, velo_y, velo_w, velo_h, BLACK);
        tft.setCursor(velo_x, velo_y);
        if (buf[0] == '-')
            tft.setTextColor(BLUE);
        else
            tft.setTextColor(RED);
        tft.setTextSize(8);
        tft.println(buf);
      }
      buf_idx = 0;
      memset(buf, 0, 20);
    } else { // add 
      buf[buf_idx++] = incomingByte;
      buf[buf_idx] = '\0';
      Serial.println(buf);
    }
  }

}
