#include <time.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
int a,r,g,b,q,humid,hour,minute,second;
float temperature, resistance;
double temp;
String location, condition;

void setup() {
    Serial.begin(115200);
    q = 3975;
    location = "Vienna";
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("hi! i'm whether!");    
    r = 0;
    g = 0;
    b = 255;
    lcd.setRGB(r,g,b);
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Fetching data for "+location);
    for (int z = 0;z<3;z++){
      for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
        // scroll one position left:
        lcd.scrollDisplayLeft();
        // wait a bit:
        delay(150);
      }
    }
}

void loop() {
    a=analogRead(0);
    resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
    temperature=1/(log(resistance/10000)/q+1/298.15)-273.15;//convert to temperature via datasheet ;
    delay(1000);
    lcd.clear();
    temp = (9/5)*temperature+32.0;
    humid = 32;
    condition = "Clear";
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char buf[100];
    sprintf(buf, "%02d:%02d:%02d",tm.tm_hour-5,tm.tm_min,tm.tm_sec);
    Serial.println(buf);
    //Serial.print(tm.tm_hour+":"+tm.tm_min);
    //Print out data
    lcd.clear();
    lcd.print(temp);
    lcd.setCursor(4,0);
    lcd.print("F - ");
    lcd.print(humid);
    lcd.print("% RH");
    lcd.setCursor(0,1);
    lcd.print(condition+" - ");
    lcd.print(buf);
    delay(1000);
}

