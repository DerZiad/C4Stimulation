#include <IRremote.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

void success();

class Timer{
  int D1 = 8;
  int A = 9;
  int F = 10;
  int D2 = 11;
  int D3 = 12;
  int B = 13;
  int E = 2;
  int D = 3;
  int decimal = 4;
  int C = 5;
  int G =6;
  int D4 = 7;
  public:
    Timer(){
      
    }

    void startTiming(){
      pinMode(D1,OUTPUT);
      pinMode(D2,OUTPUT);
      pinMode(D3,OUTPUT);
      pinMode(D4,OUTPUT);
      pinMode(decimal,OUTPUT);
      pinMode(A,OUTPUT);
      pinMode(B,OUTPUT);
      pinMode(C,OUTPUT);
      pinMode(D,OUTPUT);
      //pinMode(E,OUTPUT);
      pinMode(F,OUTPUT);
    }

    void writeAll(){
      digitalWrite(D1,HIGH);
      digitalWrite(D2,HIGH);
      digitalWrite(D3,HIGH);
      digitalWrite(D4,HIGH);
      digitalWrite(decimal,HIGH);
      digitalWrite(A,HIGH);
      digitalWrite(B,HIGH);
      digitalWrite(C,HIGH);
      digitalWrite(D,HIGH);
      digitalWrite(E,HIGH);
      digitalWrite(F,HIGH);
    }
};

LiquidCrystal_I2C lcd(0x3F,16, 2);
int codelength = 6;
int numbers[6];
int compteur = 0;
int code[6] = {0,0,0,0,0,0};
int ledvert = 0;
const char DIN_RECEPTEUR_INFRAROUGE = 2;
IRrecv monRecepteurInfraRouge (DIN_RECEPTEUR_INFRAROUGE);
Timer timer;
decode_results messageRecu;
void setup()
{
 timer.startTiming();
 pinMode(ledvert,OUTPUT);
 digitalWrite(ledvert,LOW);
 lcd.begin();
 lcd.backlight();
 lcd.print("Enter code:");
 Serial.begin(9600);
 monRecepteurInfraRouge.enableIRIn();
 monRecepteurInfraRouge.blink13(true);
}

void loop()
{ 
  timer.writeAll();
  Serial.println("Ziad");
  Serial.println(monRecepteurInfraRouge.decode(&messageRecu));
  if (monRecepteurInfraRouge.decode(&messageRecu))
  {
    Serial.println(messageRecu.value);
    if(messageRecu.value == 0xFF30CF){
      ecrireLCD(1);
    }else if(messageRecu.value == 0xFF18E7){
      ecrireLCD(2);
    }else if(messageRecu.value == 0xFF7A85){
      ecrireLCD(3);
    }else if(messageRecu.value == 0xFF10EF){
      ecrireLCD(4);
    }else if(messageRecu.value == 0xFF38C7){
      ecrireLCD(5);
    }else if(messageRecu.value == 0xFF5AA5){
      ecrireLCD(6);
    }else if(messageRecu.value == 0xFF42BD){
      ecrireLCD(7);
    }else if(messageRecu.value == 0xFF4AB5){
      ecrireLCD(8);
    }else if(messageRecu.value == 0xFF52AD){
      ecrireLCD(9);
    }else if(messageRecu.value == 0xFF6897){
      ecrireLCD(0);
    }else if(messageRecu.value == 0xFFA25D){
      if(compteur != 0){
            numbers[compteur] = 0;
            compteur--;
            lcd.clear();
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("Enter code:");
            lcd.setCursor(0,1);
            char c[compteur];
            for(int i = 0;i<compteur;i++){
              c[i] = '*';
            }
            lcd.print(c); 
      }
    }
    Serial.println(messageRecu.value,HEX);
    delay(500);
    monRecepteurInfraRouge.resume();
  }
  delay(1);
}
void success(){
  int boo = 1;
  for(int i = 0;i<6;i++){
    if(numbers[i] != code[i]){
      boo = 0;
    }
  }
  if(boo == 1){
      digitalWrite(ledvert,LOW);
  }
}


void ecrireLCD(int number){
   if(compteur != 6){
    numbers[compteur] = number;
    compteur++;
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Enter code:");
    lcd.setCursor(0,1);
    char c[compteur];
    for(int i = 0;i<compteur;i++){
      c[i] = '*';
    }
    lcd.print(c);
   }else{
      success();
   }
}
