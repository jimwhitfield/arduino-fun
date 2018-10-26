#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment object

enum direction {Decreasing, Increasing}  direction_mode;


#define HIGH_VALUE 8.8
float display_value = 0; // or HIGH_VALUE;

void setup() {
  direction_mode=Decreasing;  
  if (direction_mode == Decreasing) {
    display_value = HIGH_VALUE;
  } else {
    display_value = 0;
  }
  byte numDigits = 2;
  byte digitPins[] = {2, 3};  // I have a 2-segment display
  byte segmentPins[] = {9, 8, 5, 6, 7, 11, 10, 4};  // these are the wirings I used.
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // I have a KEM-5621-BSR Common Anode 7 Segment led 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
}

unsigned long last_update = 0;
#define INTERVAL_MS 100
int freeze_blink_count=0;
void loop() {
  // update the display
  sevseg.setNumber(display_value,1);
  sevseg.refreshDisplay();

  // if INTERVAL_MS has elapsed, ready the next value
  int now = millis();
  if (last_update + INTERVAL_MS < now) {
    // time to update
    last_update = now;
    if (direction_mode == Increasing) {
      display_value += 0.1;
      if (display_value > HIGH_VALUE)
        display_value = 0;
    } else { //direction_mode must be Decreasing
      display_value -= 0.1;
      if (display_value < 0) {
        display_value = HIGH_VALUE;
      }
    }
  }

}
