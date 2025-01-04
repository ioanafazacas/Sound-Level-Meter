// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        8 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

int microfonPin = A0;
int nivelZgomot=8;
long freq = 10;


void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(9600);
  pinMode(microfonPin, INPUT);

}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  int mn = 1024;
  int mx = 0;
  int val = 0;

  for (int i = 0; i < 10000; ++i) {

    val = analogRead(microfonPin);
    
    mn = min(mn, val);
    mx = max(mx, val);
  }

  int delta = mx - mn;
  /*
  int sum=0;
  for(int i=0; i<100; i++){
    long val = analogRead(microfonPin);
    freq = map(val, 0, 1024, 0, 255);
    sum = sum + freq;
  }
  sum=sum/100;
*/
  Serial.print(delta);
  Serial.print("   ");
  Serial.println(val);
  
  
  
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  if(delta<=3) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0));
    pixels.setPixelColor(7, pixels.Color(0, 0, 0));

    //pixels.show();   // Send the updated pixel colors to the hardware.

    //delay(DELAYVAL); // Pause before next pass through loop
  }
  else if(delta>3 && delta<=988){
    pixels.setPixelColor(1, pixels.Color(0, 120, 0));
    pixels.setPixelColor(2, pixels.Color(0, 120, 0));
    pixels.setPixelColor(3, pixels.Color(0, 120, 0));
    pixels.setPixelColor(4, pixels.Color(0, 120, 0));
    pixels.setPixelColor(5, pixels.Color(0, 120, 0));
    pixels.setPixelColor(6, pixels.Color(0, 120, 0));
    pixels.setPixelColor(7, pixels.Color(0, 120, 0));
  } else if(delta>988 && delta<=994){
    pixels.setPixelColor(1, pixels.Color(250, 120, 0));
    pixels.setPixelColor(2, pixels.Color(250, 120, 0));
    pixels.setPixelColor(3, pixels.Color(250, 120, 0));
    pixels.setPixelColor(4, pixels.Color(250, 120, 0));
    pixels.setPixelColor(5, pixels.Color(250, 120, 0));
    pixels.setPixelColor(6, pixels.Color(250, 120, 0));
    pixels.setPixelColor(7, pixels.Color(250, 120, 0));
  } else if(delta>994){
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.setPixelColor(2, pixels.Color(255, 0, 0));
    pixels.setPixelColor(3, pixels.Color(255, 0, 0));
    pixels.setPixelColor(4, pixels.Color(255, 0, 0));
    pixels.setPixelColor(5, pixels.Color(255, 0, 0));
    pixels.setPixelColor(6, pixels.Color(255, 0, 0));
    pixels.setPixelColor(7, pixels.Color(255, 0, 0));
  } 
  pixels.show();
  delay(100);
}


