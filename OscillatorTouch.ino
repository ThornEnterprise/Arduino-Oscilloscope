//Download and include Library for Elegoo_TFTLCD & Elegoo_GFX

#include <registers.h>
#include <Elegoo_TFTLCD.h>
#include <pin_magic.h>
#include <Elegoo_GFX.h>


//For Aduino MEGA w/ Shield & Elegoo 2.8" TFT
//Individual board parameters may differ. 
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

//Define common colors
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//Create new TFT
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


// These constants won't change:
const int sensorPin = A15;    // pin that the sensor is attached to
// variables:
int xPOS = 0;                // Counter for graph


void setup() {
  // put your setup code here, to run once:
tft.reset();
tft.begin(0x9341);

tft.fillScreen(BLACK);
tft.setRotation(3);
tft.setCursor(5, 5);

tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.println("Voltage value :");

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);


   // draw outline
   tft.drawLine(100, 210, (100 + 200), 210, WHITE);
   tft.drawLine(100, 210, 100, (210 - 200), WHITE);

}

void loop() 
{
  
  int sensor = analogRead(sensorPin);
  tft.fillRect(5,20,75,75,BLACK); //Clear old data
 
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensor * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);
    
tft.setCursor(15, 45);
tft.setTextColor(RED);
tft.setTextSize(2);
tft.println(voltage); //Display Voltage
 sensor = map(sensor,0,1023,0,190);
tft.drawFastVLine(101+xPOS,10,sensor,BLUE); //Draw Voltage


  
  
  //High/Low Display Conditions
  if (voltage >= 2.5) 
  {
    digitalWrite(LED_BUILTIN, HIGH);
    tft.setCursor(15, 60);
    tft.setTextColor(GREEN);
    tft.setTextSize(2);
    tft.println("HIGH");
    }
  
  
  if (voltage < 2.5) 
  {
    digitalWrite(LED_BUILTIN, LOW);
    tft.setCursor(15, 60);
    tft.setTextColor(BLUE);
    tft.setTextSize(2);
    tft.println("LOW");
    }

// Counter for graph
if (xPOS >= 200) {

    xPOS = 0;

    tft.fillRect(101,0,300,200,BLACK);

  }

  else {

    xPOS=xPOS+1;

  }

  //Continuity Checker
  pinMode(22,INPUT_PULLUP);
  if(digitalRead(22)!=HIGH){
    tft.setCursor(15, 75);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("Cont.");
  }

  delay(10);
}



 
