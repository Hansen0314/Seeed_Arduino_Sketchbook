#include <SoftwareSerial.h>
#include <TFT_eSPI.h>

static const int RXPin = 0, TXPin = 1;
static const uint32_t GPSBaud = 9600;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
 
TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite 

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  tft.begin();
  tft.setRotation(3);
  spr.createSprite(tft.width(),tft.height()); 
}
void loop()
{
  
    spr.fillSprite(TFT_BLACK);
    spr.setCursor(0,5,2);
    spr.println("The GPS raw data"); 
    spr.setCursor(0,20,2);
    while(ss.available())                     // if date is coming from software serial port ==> data is coming from ss shield
    {              
        uint8_t reciver = ss.read();
        Serial.write(reciver);
        spr.write(reciver);
        int basetime = millis();
        while (!ss.available());
        int timecost = millis() - basetime;
        if(timecost > 709){
            break;
        } 
    }
    if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
        ss.write(Serial.read());        // write it to the ss shield
    spr.pushSprite(0, 0);
    Serial.print("----------------------------------------------------------\r\n");
}