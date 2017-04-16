#include <EEPROM.h>

#define RED 9
#define GREEN 10
#define BLUE 11
int R, G, B;
String val;

void setup() {
Serial.begin(9600);
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
}


void SaveSettings(){
  EEPROM.write(0,R);
  EEPROM.write(1,G);
  EEPROM.write(2,B);
}

String GeS = "GeS";

void SetCol(){
  analogWrite(RED, R);
  analogWrite(BLUE, B);
  analogWrite(GREEN, G);
  SaveSettings();
}

void LoadSettings(){
byte tmp;
R=EEPROM.read(0);
G=EEPROM.read(1);
B=EEPROM.read(2);
SetCol();
}

void GetSet(){
  String fs=String(R, DEC);
  String qqq1=":";
  fs=fs+qqq1+String(G, DEC)+qqq1+String(B, DEC);
  Serial.print(fs);
}



String RS;
String GS;
String BS;

void loop() {
LoadSettings();
if (Serial.available()){
  val = Serial.readString();
  if(val.equals(GeS)){
    GetSet();
    delay(2000);
  } else if(val.length()>4){
  int tmp;
  tmp=val.indexOf(":",0);
      RS=val.substring(0,tmp);
  val.remove(0,tmp+1);
  tmp=val.indexOf(":",0);
      GS=val.substring(0,tmp);
  val.remove(0,tmp+1);
  R=RS.toInt();
  G=GS.toInt();
  B=val.toInt();
    SetCol();
        SaveSettings();
  }
}
}
