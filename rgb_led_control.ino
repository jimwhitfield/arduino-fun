
// Gray text with two slashes are just helpful comments, you don’t need to type them. :)

/******* -----=====!! EASY STUFF TO MESS WITH !!=====------ ******/

  // What analog pin should we use to read the value from the potentiometer?
  int analogPin = 2; // Yep, you heard right: The coolest of the Analog pins...

  // What pins are the LEDs connected to?
  int redPin = 9;
  int greenPin = 10;
  int bluePin = 11;
  int whitePin = 6;

/******* -----=====^^ EASY STUFF TO MESS WITH ^^=====------ ******/

void setup() {
  pinMode(redPin, OUTPUT); // Setup ledPin as an output.
  pinMode(greenPin, OUTPUT); // Setup ledPin as an output.
  pinMode(bluePin, OUTPUT); // Setup ledPin as an output.
  pinMode(whitePin, OUTPUT);
}

void loop() {
  // if you have a pot attached to the analog pin, use this to read the "color value" to use
  int colorValue = map(analogRead(analogPin), 0, 1023, 0, 255);
  
  
  
  int r, g, b;
  int w;
  analogWrite(whitePin, colorValue);
  
  if (colorValue < 85) {
    r = 255 - colorValue * 3;
    g = 0;
    b = colorValue * 3;
  } else if (colorValue < 170) {
    colorValue -= 85;
    r = 0;
    g = colorValue * 3;
    b = 255 - colorValue * 3;
  } else {
    colorValue -= 170;
    r = colorValue * 3;
    g = 255 - colorValue * 3;
    b = 0;
  }
  
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  delay(50);
}
