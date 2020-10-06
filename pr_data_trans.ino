/*
 * Arduino with LM35 analog temperature sensor and SSD1306 OLED display.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */
 
#include <Wire.h>              // include Arduino wire library (required for I2C devices)
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_SSD1306.h>  // include Adafruit SSD1306 OLED display driver
#include <SimpleDHT.h>
 
#define OLED_RESET  4    // define display reset pin
Adafruit_SSD1306 display(OLED_RESET);

//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// define DHT11 pin connection
int pinDHT11 = 9;
SimpleDHT11 dht11;
 
void setup(void)
{
  delay(1000);  // wait a second

  //Serial.begin(9600); 
  // initialize the SSD1306 OLED display with I2C address = 0x3D
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
  // clear the display buffer.
  display.clearDisplay();
 
  display.setTextSize(1);   // text size = 1
  display.setTextColor(WHITE, BLACK);  // set text color to white and black background
  display.setCursor(15, 0);            // move cursor to position (15, 0) pixel
  display.print("Device Status");
  display.display();        // update the display
  display.setTextSize(2);   // text size = 2
}
 
void loop()
{
  to_oled_temphumidata();

  data_send();
}

void data_send()
{
  
}

char _buffer[8];

void to_oled_temphumidata()
{
  byte temperature = 0;
  byte humidity = 0;
  
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }

  display.setCursor(23, 10); 
  sprintf(_buffer, "%d C", (int)temperature);
  display.print(_buffer);
  
  display.setCursor(23, 30); 
  sprintf(_buffer, "%d /", (int)humidity);
  display.print(_buffer);
  
  //display.setCursor(23, 50);
  //printf(_buffer, "On/Off");
  //display.print("On/Off");
  
  display.drawCircle(88, 12, 2, WHITE); 
  //display.drawCircle(88, 32, 2, WHITE);
  
  // update the display 
  display.display();
    
  // DHT11 sampling rate is 1HZ.
  delay(2000);
}






void to_oled_temphumidata_test()
{
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" %");
  
  // DHT11 sampling rate is 1HZ.
  delay(2000);
  
}

 
// end of code.
