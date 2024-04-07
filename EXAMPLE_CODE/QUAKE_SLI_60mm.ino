/*
Created by chatGPT3.5----
Uploaded by Tevian Busselle
Designed for Voodoo2 SLI Bridge 60mm with neopixels x 8 on PB4.


LED MAP TOP VIEWED
....................................
....................................
...........##...........##..........
.........##.(0).......(4).##........
........##.................##.......
.......##...................##......
......##.....................##.....
......##.....................##.....
......##.(1).............(3).##.....
......###........(2).........##.....
.......##.......#####.......##......
.......####......###......####......
........#####....###....#####.......
......(7).#################.(5).....
............#############...........
.................###................
.................###................
.................###................
.................###................
..................#.(6).............
..................#.................
....................................
....................................
*/

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    4   // Pin connected to the NeoPixels
#define NUM_PIXELS   8   // Number of NeoPixels
#define BRIGHTNESS   100 // Brightness level (0-255)

// Initialize the NeoPixel library with the number of pixels and pin
Adafruit_NeoPixel pixels(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Define the colors
#define WHITE       pixels.Color(255, 255, 255)
#define YELLOW      pixels.Color(255, 255, 0, 0)
#define RED         pixels.Color(255, 0, 0, 0)
#define BLACK       pixels.Color(0, 0, 0, 0)

void setup() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
}

void loop() {
  // Define the pixel order
  int pixelOrder[NUM_PIXELS] = {6, 7, 5, 2, 1, 3, 0, 4};

  // Define the color sequence
  uint32_t colors[] = {WHITE, YELLOW, RED, BLACK};

  // Generate random flicker values for each color component
  uint8_t flickerR = random(180, 255); // Ensuring first pixel is brighter
  uint8_t flickerG = random(50, flickerR); // Ensure green is never greater than red
  uint8_t flickerB = 0; // No blue color data for colors other than white

  // Flickering flame effect with fade as heat travels
  for (int i = 0; i < NUM_PIXELS; i++) {
    // Set the color for the current pixel with flickering effect
    pixels.setPixelColor(pixelOrder[i], pixels.Color(flickerR, flickerG, flickerB));

    // Adjust the brightness for the next pixel
    flickerR = constrain(flickerR - 30, 0, 255); // Reduce red component for fade effect
    flickerG = flickerG > 20 ? flickerG - 20 : 0; // Reduce green component with constraint

    pixels.show();
    
    // Adjust the delay to control the flickering speed
    delay(random(20, 20));

    // Generate new random flicker values for each color component
    flickerR = random(0, 255);
    flickerG = random(0, flickerR); // Ensure green is never greater than red
    flickerB = 0; // No blue color data for colors other than white
  }
}
