/*
Slacker
Version 1.2.1
https://github.com/uCBill/Slacker
Linux like watchface by Bill Eichner
Daylight Savings Time is configured in the settings.h section

Based on Bahn-for-Watchy
https://github.com/BraininaBowl/Bahn-for-Watchy

Based on SmatWatch
https://github.com/theRealc2c2/SmartWatch

Face for Watchy watch
https://watchy.sqfmi.com
*/

#include <Watchy.h> //include the Watchy library
#include "LiberationSansNarrow_Bold8pt7b.h"
#include "Teko_Regular20pt7b.h"
#include "prompt.h"
#include "settings.h"

class WatchFace : public Watchy { //inherit and extend Watchy class
  using Watchy::Watchy;
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1;
      uint16_t w, h;
      String textstring;
      int temp;
      bool light = true; // left this here if someone wanted to tweak for dark

      //resets step counter at midnight everyday
      if(currentTime.Hour == 00 && currentTime.Minute == 00) {
        sensor.resetStepCounter();
      }
      
      // ** DRAW **

      //drawbg
      display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);  
      display.setFont(&LiberationSansNarrow_Bold8pt7b);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setTextWrap(false);
      
      //draw slacker text
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(0, 10);
      display.print("sk@darkstar:/~");
      display.setCursor(0, 23);
      display.print("$ ls -l");
      display.setCursor(0, 36);
      display.print("total (steps)");//use step # for total
      display.setCursor(0, 49);
      display.print("4 drwxr-xr-x 5 sk sk 4K Jn 1 Dcs");
      display.setCursor(0, 62);
      display.print("4 drwxr-xr-x 2 sk sk 4K Ag 9 Dnl");
      display.setCursor(0, 75);
      display.print("sk@darkstar:/~");
      display.setCursor(0, 88);
      display.print("$ date");
      
      // draw day of week
      textstring = dayShortStr(currentTime.Wday);
      textstring += " ";

      //draw day, month, year
      textstring += currentTime.Day;
      textstring += " ";
      textstring += monthShortStr(currentTime.Month);
      textstring += " ";
      textstring += currentTime.Year + 1970;
      textstring += " ";
      
      
      //draw time
      display.setFont(&LiberationSansNarrow_Bold8pt7b);
     if (currentTime.Hour > 0 && currentTime.Hour < 10) {
        textstring += "0";
      } else if(currentTime.Hour > 12 && currentTime.Hour <= 21){
        textstring += "0";
      } else {
        textstring += "";
      }
      if (currentTime.Hour > 0 && currentTime.Hour <= 12) {
        textstring += currentTime.Hour;
      } else if (currentTime.Hour < 1) {
        textstring += 12;
      } else {
        textstring += ((currentTime.Hour+11)%12)+1;
      }

      textstring += ":";
      if (currentTime.Minute < 10) {
        textstring += "0";
      } else {
        textstring += "";
      }
      textstring += currentTime.Minute;

      //this section adds AM or PM to the display
      if (currentTime.Hour >= 12) {
        textstring += " PM EDT";//List of US Time Zones: EST, CST, MST, PST, AKST
      } else {
        textstring += " AM EDT";//List of US Daylight Savings Time Zones: EDT, CDT, MDT, PDT, AKDT
	  }
   //To change Time Zones, including Daylight Savings Time, see the settings.h section

      display.setCursor(0, 102);
      display.print(textstring);

      //drawTimeBold
      display.setFont(&Teko_Regular20pt7b);
      if (currentTime.Hour > 0 && currentTime.Hour <= 12) {
        textstring = currentTime.Hour;
      } else if (currentTime.Hour < 1) {
        textstring = 12;
      } else {
        textstring = ((currentTime.Hour+11)%12)+1;
      }

      textstring += ":";
      if (currentTime.Minute < 10) {
        textstring += "0";
      } else {
        textstring += "";
      }
      textstring += currentTime.Minute;

      //this section adds AM or PM to the display
      if (currentTime.Hour >= 12) {
        textstring += "PM";
      } else {
        textstring += "AM";
    }

      display.setCursor(107, 23);
      display.print(textstring);
      

      
      // draw battery
      display.setFont(&LiberationSansNarrow_Bold8pt7b);
     int8_t batteryLevel = 0;
     float VBAT = getBatteryVoltage();

     if(VBAT >= 4.2){
        batteryLevel = 100.0;
     }
     else if (VBAT >= 3.3) {
        batteryLevel = 100.0*(VBAT-3.3)/0.9;
    }
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(0, 116);
      display.print("sk@darkstar:/~");
      display.setCursor(0, 129);
      display.print("$ upower -i/UPwr/dvcs/btry_BT0");
      display.setCursor(0, 143);
      display.print("voltage:");
      display.setCursor(120, 143);
      display.print(VBAT);
      display.setCursor(0, 157);
      display.print("percentage:");
      display.setCursor(120, 157);
      display.print(batteryLevel); 
      display.setCursor(143, 157);
      display.print("%"); 
      display.setCursor(0, 171);
      display.print("technology:");
      display.setCursor(120, 171);
      display.print("lithium-pol");
      display.setCursor(0, 185);
      display.print("sk@darkstar:/~");
      display.setCursor(0, 199);
      display.print("$ ");
      //draw image
      display.drawBitmap(12,187, epd_bitmap_prompt, 7, 14, GxEPD_BLACK);


      //draw steps
      display.setFont(&LiberationSansNarrow_Bold8pt7b);
      textstring = sensor.getCounter();
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(75, 36);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.print(textstring);


    }

};


WatchFace m(settings); //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
