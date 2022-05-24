
#include <DS3232RTC.h>     

DS3232RTC myRTC;


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

String ps11="",ps21="",ps31="",ps12="",ps22="",ps32="",ps13="",ps23="",ps33="";

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int s=10;
#define NUMFLAKES     10 

#define LOGO_HEIGHT  13
#define LOGO_WIDTH   32
int monitors=0;

////////pins
#define step1   A2
#define step2    15
#define step3   A0
#define step4    14
#define sound   2
#define enter    5
#define left   3
#define right    4
#define homeinput1    24

////////////////
int i=0;
int pr11=10,pr21=20,pr31=30,pr12=10,pr22=20,pr32=30,pr13=10,pr23=20,pr33=30;
int ht11=0,ht21=0,ht31=0,ht12=0,ht22=0,ht32=0,ht13=0,ht23=0,ht33=0;
int mt11=1,mt21=3,mt31=7,mt12=10,mt22=13,mt32=15,mt13=15,mt23=20,mt33=25;
int timeseth=0,timesetm=0;
int stepcount=0;
int systemcontrol=30;
static const unsigned char logo_bmp [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x06, 0x00, 0x01, 0xc1, 0x83, 0x80, 0x07, 0xc3, 0xc3, 0xe0,
    0x0f, 0xe3, 0xc7, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf8,
    0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x3b, 0xdc, 0xf0, 0x06, 0x01, 0x80, 0x60, 0x03, 0x01, 0x80, 0xc0,
    0x00, 0x00, 0x00, 0x00 };
void setup()
{
    Serial.begin(9600);
//    myRTC.begin();
//    setSyncProvider(myRTC.get);   
//    setTime(8,0,0,20,1,2022);
//    time_t t = now();
//    myRTC.set(now());    
       
  myRTC.begin();
    setSyncProvider(myRTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet)
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time"); 

 // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

 
  // Clear the buffer

 display.clearDisplay();

  display.setTextSize(1);            

    display.println(F("BME"));


     display.display();


  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  delay(2000);
pinMode(step1,OUTPUT);
pinMode(step2,OUTPUT);

pinMode(step3,OUTPUT);
pinMode(step4,OUTPUT);
pinMode(sound,OUTPUT);
pinMode(right,INPUT);
pinMode(enter,INPUT);
pinMode(left,INPUT);
pinMode(homeinput1,INPUT);


}

void loop()
{
    displayrun();
    delay(200);
    if(systemcontrol==1){
      makesound (10);
  while(systemcontrol==1){
      motordrive(20,2,ht11,mt11,pr11);
      motordrive(20,2,ht21,mt21,pr21);
      motordrive(20,2,ht31,mt31,pr31);
       display.clearDisplay();
          print_time();
if(ps11=="" && mt11-minute()>=0 ){
  if(mt11-minute()==1){
  makesound (10);}
notitime(ht11, mt11);
  }
  if(mt11-minute()<0 && mt21-minute()<0 && mt31-minute()<0){
    
    notitime(23, 60);
    }
  if(ps11=="d11" && ps21==""){
notitime(ht21, mt21);
 if(mt21-minute()==1 && ht21-hour()==0 ){
  makesound (10);}
  }
if(ps11=="d11" && ps21=="d21" && ps31==""){
notitime(ht31, mt31);
 if(mt31-minute()==1 && ht31-hour()==0  ){
  makesound (10);}
  }
           display.display();

if(stepcount==30){
  backstep(30);
  }}
}
    if(systemcontrol==2){  
            makesound (50);

  while(systemcontrol==2){
     motordrive(20,2,ht12,mt12,pr12);
      motordrive(20,2,ht22,mt22,pr22);
      motordrive(20,2,ht32,mt32,pr32);
       display.clearDisplay();
          print_time();
if(ps12==""){
  if(mt12-minute()==1){
  makesound (50);}
notitime(ht12, mt12);
  }
  if( ps12=="d12" ){
notitime(ht22, mt22);
if(mt22-minute()==1 && ht22-hour()==0 ){
  makesound (50);}
  }
if(ps12=="d12" && ps22=="d22" && ps32==""){
notitime(ht32, mt32);
if(mt32-minute()==1 && ht32-hour()==0){
  makesound (50);}
  }
           display.display();

if(stepcount==30){
  backstep(30);
  }}}
    if(systemcontrol==3){  
           makesound (70);


  while(systemcontrol==3){
    print_time();
      motordrive(20,40,0,4,10);
      motordrive(20,40,0,6,20);
      motordrive(20,40,0,8,30);
if(stepcount==30){
  backstep(30);
  }}}
  if(systemcontrol==4){
     int inj=0;  

          while(digitalRead(right)==0){  

              display.clearDisplay();

   print_time();

if(digitalRead(left)==1){
 inj++;
  if(inj>1) inj=0;
  }
  if(inj==1){
  display.println(F("set time"));
      display.println(F("->injection location"));
           display.display();

      delay(500);
         if(digitalRead(enter)==1){
stephome();  
display.println(F("->at home loction"));
     display.display();

      delay(2000);
 inj=0;
}}
  
  else{  
    display.clearDisplay();

    print_time();
  display.println(F("->set time"));
      display.println(F("injection location"));
            if(digitalRead(enter)==1){
                    delay(2000);
  timesetting();
     display.display();

 inj=0;
}                
        }
      display.display();
  } 
i=1;
systemcontrol=22;
}
}
void displayrun()
{
    
if(i<=0 || i==5){i=1;}
    if(digitalRead(left)==1){i++;delay(500);}
        if(digitalRead(right)==1){i--;delay(500);}
if(i==1){
        display.clearDisplay();
  print_time();

 
  display.println(F("->function1"));
      display.println(F("function2"));
display.println(F(""));display.println(F(""));
   display.println(F("function3"));
      display.println(F("settings"));

   if(digitalRead(enter)==1){
     systemcontrol=1;}
     display.display();
}
if(i==2){
        display.clearDisplay();

   print_time();

  display.println(F("function1"));
      display.println(F("->function2"));

   display.println(F("function3"));
         display.println(F("settings"));

   
     display.display();
     if(digitalRead(enter)==1){
     systemcontrol=2;}

}
if(i==3){
        display.clearDisplay();

  print_time();

  display.println(F("function1"));
      display.println(F("function2"));

   display.println(F("->function3"));
         display.println(F("settings"));

     display.display();
     if(digitalRead(enter)==1){
     systemcontrol=3;}
   }

if(i==4){
        display.clearDisplay();

  print_time();

  display.println(F("function1"));
      display.println(F("function2"));

   display.println(F("function3"));
         display.println(F("->settings"));

     display.display();
     if(digitalRead(enter)==1){
     systemcontrol=4;}
   }
   



  
}

void motordrive(int x,int s,int hours, int mints,int hand){
  if (hours==hour() && mints==minute()&& stepcount<= hand){
 for(int t=0;t<=x;t++){
stepleft( s);
 }
if(stepcount==pr11){
  ps11="d11";
}
if(stepcount==pr21){
  ps21="d21";
}
if(stepcount==pr31){
  ps31="d31";
}
if(stepcount==pr12){
  ps12="d12";
}
if(stepcount==pr22){
  ps22="d22";
}
if(stepcount==pr32){
  ps32="d32";
}
if(stepcount==pr13){
  ps13="d13";
}
if(stepcount==pr23){
  ps23="d23";
}
if(stepcount==pr31){
  ps33="d33";
}
stepcount++;


 display.clearDisplay();

  print_time();
  display.setTextSize(3);            
  display.setCursor(25,45); 

  display.println(map(stepcount,1,hand,1,100));
  display.setCursor(60,45); 
    display.println(F("%"));


     display.display();
     delay(1000);
     
}
  }
  // sound
  void makesound (int make){
    
      for(int w=0;w<=15;w++){
      digitalWrite(sound,HIGH);
delay(make);
digitalWrite(sound,LOW);
delay(make);}
    }
  void backstep(int hand){
    
      if (stepcount==hand ){
        i=5;
systemcontrol=33;
 stephome();
    }}
    //sound end
    //motor drive 
    void stepright(){
      digitalWrite(step1,LOW);
digitalWrite(step2,LOW);
digitalWrite(step3,LOW);
digitalWrite(step4,HIGH);

delay (2);
digitalWrite(step1,LOW);
digitalWrite(step2,LOW);
digitalWrite(step3,HIGH);
digitalWrite(step4,LOW);    
delay(2);
digitalWrite(step1,LOW);
digitalWrite(step2,HIGH);
digitalWrite(step3,LOW);
digitalWrite(step4,LOW);      
delay(2);
        digitalWrite(step1,HIGH);
digitalWrite(step2,LOW);
digitalWrite(step3,LOW);
digitalWrite(step4,LOW); 
         delay(2);
      }
    void stepleft(int s){
      digitalWrite(step1,HIGH);
digitalWrite(step2,HIGH);
digitalWrite(step3,LOW);
digitalWrite(step4,LOW);

delay (s);
digitalWrite(step1,LOW);
digitalWrite(step2,HIGH);
digitalWrite(step3,HIGH);
digitalWrite(step4,LOW);    
delay(s);
digitalWrite(step1,LOW);
digitalWrite(step2,LOW);
digitalWrite(step3,HIGH);
digitalWrite(step4,HIGH);      
delay(s);
        digitalWrite(step1,HIGH);
digitalWrite(step2,LOW);
digitalWrite(step3,LOW);
digitalWrite(step4,HIGH); 
         delay(s);
      }
      //motor drive end
// time 
      void print_time(){
        
         display.setTextSize(1);            
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(0,0); 
 display.println(hour());
   display.setCursor(10,0); 

  display.println(F(":"));
  display.setCursor(20,0); 

  display.println(minute());
    display.setCursor(30,0); 

    display.println(F(":"));
  display.setCursor(40,0); 

 display.println(second());
        }
       //time end
    void stephome(){
      while(digitalRead(homeinput1)==0){
           digitalWrite(step1,LOW);
digitalWrite(step2,LOW);
digitalWrite(step3,LOW);
digitalWrite(step4,HIGH);

delay (2);
digitalWrite(step1,LOW);
digitalWrite(step2,LOW);
digitalWrite(step3,HIGH);
digitalWrite(step4,LOW);    
delay(2);
digitalWrite(step1,LOW);
digitalWrite(step2,HIGH);
digitalWrite(step3,LOW);
digitalWrite(step4,LOW);      
delay(2);
        digitalWrite(step1,HIGH);
digitalWrite(step2,LOW);
digitalWrite(step3,LOW);
digitalWrite(step4,LOW); 
         delay(2);}
      return 1;
      }
    void notitime(int ho, int minu){
      
      display.setTextSize(3);            
  display.setCursor(30,45); 

  display.println(ho-hour());
  display.setCursor(60,45); 
    display.println(F(":"));
     display.setCursor(90,45);
  display.println(minu-minute());
  return 54;
      }
      void timesetting(){
        
        while(digitalRead(right)==0){
          
          if(digitalRead(left)==1){timesetm++;}
          if(digitalRead(enter)==1){timeseth++;}


          display.clearDisplay();

  
      display.setTextSize(1);            
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(0,0); 
 display.println(timeseth);
   display.setCursor(10,0); 

  display.println(F(":"));
  display.setCursor(20,0); 

  display.println(timesetm);
    display.setCursor(30,0); 



     display.display();
     delay(400);
          }
 myRTC.begin();
 setSyncProvider(myRTC.get);   
 setTime(timeseth,timesetm,0,20,1,2022);
 time_t t = now();
myRTC.set(now());    
        }
