/*
Slacker
Version 1.1.0
https://github.com/uCBill/Slacker
Linux like watchface by Bill Eichner

Based on Bahn-for-Watchy
https://github.com/BraininaBowl/Bahn-for-Watchy

Based on SmatWatch
https://github.com/theRealc2c2/SmartWatch

Face for Watchy watch
https://watchy.sqfmi.com
*/

#include <Watchy.h> //include the Watchy library
#include "LiberationSansNarrow_Bold8pt7b.h"
#include "prompt.h"
#include "settings.h"

class WatchFace : public Watchy { //inherit and extend Watchy class
  using Watchy::Watchy;
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1;
      uint16_t w, h;
      String textstring;
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
        textstring += " PM EST";
      } else {
        textstring += " AM EST";
	  }

      display.setCursor(0, 102);
      display.print(textstring);
      
      // draw battery
      display.setFont(&LiberationSansNarrow_Bold8pt7b);
     float VBAT = getBatteryVoltage();
     if(VBAT > 4.1){
        textstring ="100%";
     }
     else if(VBAT > 4.08 && VBAT <= 4.1){
        textstring = "95%";
     }
     else if(VBAT > 4.06 && VBAT <= 4.08){
        textstring = "90%";
     }
     else if(VBAT > 4.04 && VBAT <= 4.06){
        textstring = "85%";
     }    
     else if(VBAT > 4.02 && VBAT <= 4.04){
        textstring = "80%";
     }    
     else if(VBAT > 4.00 && VBAT <= 4.02){
        textstring = "75%";
     }    
     else if(VBAT > 3.98 && VBAT <= 4.00){
        textstring = "70%";
     }    
     else if(VBAT > 3.96 && VBAT <= 3.98){
        textstring = "65%";
     }
     else if(VBAT > 3.94 && VBAT <= 3.96){
        textstring = "60%";
     }    
     else if(VBAT > 3.92 && VBAT <= 3.94){
        textstring = "55%";
     }    
     else if(VBAT > 3.90 && VBAT <= 3.92){
        textstring = "45%";
     }    
     else if(VBAT > 3.88 && VBAT <= 3.90){
        textstring = "40%";
     }    
     else if(VBAT > 3.86 && VBAT <= 3.88){
        textstring = "35%";
     }
     else if(VBAT > 3.84 && VBAT <= 3.86){
        textstring = "30%";
     }    
     else if(VBAT > 3.82 && VBAT <= 3.84){
        textstring = "25%";
     }    
     else if(VBAT > 3.80 && VBAT <= 3.82){
        textstring = "20%";
     }    
     else if(VBAT > 3.78 && VBAT <= 3.80){
        textstring = "15%";
     }    
     else if(VBAT > 3.76 && VBAT <= 3.78){
        textstring = "10%";
     }
     else if(VBAT > 3.74 && VBAT <= 3.76){
        textstring = "5%";
     }    
     else if(VBAT <= 3.73){
        textstring = "1%";
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
      display.print(textstring);
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
      textstring += "";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(75, 36);
      display.setTextColor(light ? GxEPD_BLACK: GxEPD_WHITE);
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
