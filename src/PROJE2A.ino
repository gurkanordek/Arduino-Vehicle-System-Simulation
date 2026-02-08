#include <LiquidCrystal.h>
int rs = 13, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int lm35Pin = A0;
const int ldrPin = A1;
const int potPin = A2;
const int klimaMotorPin = 53;
const int arabaMotorPin = 44;
const int arabaMotorButonPin = 31;
const int emniyetKemerButonPin = 30;
const int kapiAnahtarPin = 29;
const int yakitLedPin = 26;
const int emniyetKemerLedPin = 27;
const int farLedPin = 28;
const int buzzerPin = 25;
const int rgbRPin = 10;
const int rgbGPin = 9;
const int rgbBPin = 8;

boolean arabaMotorDurumu = false;
boolean oncekiArabaButonDurumu = HIGH;
boolean emniyetKemerDurumu = false;
boolean oncekiEmniyetKemerButonDurumu = HIGH;
boolean farDurumu = false;
boolean klimaDurumu = false;
boolean yakitMesajiVerildiMi = false;
boolean kapiAcildiMi = false;

unsigned long yakitLedSonZaman = 0;
bool yakitLedDurumu = false;
const unsigned long yakitLedAralik = 100; 

//*********************************************************************************************************************************************************************************

void setup() {
 
  pinMode(lm35Pin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(klimaMotorPin, OUTPUT);
  pinMode(arabaMotorPin, OUTPUT);
  pinMode(arabaMotorButonPin, INPUT_PULLUP);
  pinMode(emniyetKemerButonPin, INPUT_PULLUP);
  pinMode(kapiAnahtarPin, INPUT_PULLUP);
  pinMode(yakitLedPin, OUTPUT);
  pinMode(emniyetKemerLedPin, OUTPUT);
  pinMode(farLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(rgbRPin, OUTPUT);
  pinMode(rgbGPin, OUTPUT);
  pinMode(rgbBPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  Serial1.begin(9600);
}

//*********************************************************************************************************************************************************************************

void loop() {

  int kapiAnahtarPinDegeri = digitalRead(kapiAnahtarPin);            

  if(kapiAnahtarPinDegeri == 1){

    analogWrite(rgbRPin, 0);
    analogWrite(rgbBPin, 55);
    analogWrite(rgbGPin, 255);
    kapiAcildiMi = true;

    if(arabaMotorDurumu == true){

      digitalWrite(arabaMotorPin, LOW);
      arabaMotorDurumu = false;

      lcd.setCursor(0, 0);
      lcd.print("kapi acildi!");
      lcd.setCursor(0, 1);
      lcd.print("motor durdu");
      delay(500);
      lcd.clear();
    }
  } 

  else{

    analogWrite(rgbRPin, 255);
    analogWrite(rgbBPin, 255);
    analogWrite(rgbGPin, 255);

    if(kapiAcildiMi){
      
      lcd.clear();
      kapiAcildiMi = false;
    }
  }                                                

//*********************************************************************************************************************************************************************************

  boolean suankiEmniyetKemerButonDurumu = digitalRead(emniyetKemerButonPin);

  if (suankiEmniyetKemerButonDurumu == LOW && oncekiEmniyetKemerButonDurumu == HIGH) {         
    
    delay(50);
    emniyetKemerDurumu = !emniyetKemerDurumu;

    if(emniyetKemerDurumu){

      digitalWrite(buzzerPin, LOW);
      digitalWrite(emniyetKemerLedPin, LOW);
      lcd.clear();
    }

    else if(arabaMotorDurumu){

      digitalWrite(arabaMotorPin, LOW);
      arabaMotorDurumu = false;
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(emniyetKemerLedPin, HIGH);

      lcd.setCursor(0, 0);
      lcd.print("kemer cikarildi!");
      lcd.setCursor(0, 1);
      lcd.print("motor durdu");
      delay(500);
      lcd.clear();
    }
  }

  oncekiEmniyetKemerButonDurumu = suankiEmniyetKemerButonDurumu;

//*********************************************************************************************************************************************************************************

  double potDegeri = analogRead(potPin);
  double yakitSeviyesi = (potDegeri / 1023.0) * 100.0;

  if(yakitSeviyesi < 10 && yakitSeviyesi > 5){

    digitalWrite(yakitLedPin, HIGH);
    yakitMesajiVerildiMi = true;
    
    lcd.setCursor(0, 0);
    lcd.print("yakit seviyesi ");
    lcd.setCursor(0, 1);
    lcd.print(" dusuk: %");
    lcd.print(yakitSeviyesi);
  }

  else if(yakitSeviyesi == 0){

    digitalWrite(yakitLedPin, LOW);
    digitalWrite(farLedPin, LOW);
    digitalWrite(emniyetKemerLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    analogWrite(rgbBPin, 255);
    analogWrite(rgbGPin, 255);
    analogWrite(rgbRPin, 255);
    digitalWrite(arabaMotorPin, LOW);
    arabaMotorDurumu = false;
    farDurumu = false;

    if (digitalRead(arabaMotorButonPin) == HIGH) 
      oncekiArabaButonDurumu = HIGH;

    lcd.setCursor(0, 0);
    lcd.print("yakit bitti  ");
    lcd.setCursor(0, 1);
    lcd.print("motor durdu  ");
    delay(500);
    lcd.clear();
  }
    
  else if(yakitSeviyesi < 5){
    
    unsigned long simdi = millis();
    
    if (simdi - yakitLedSonZaman >= yakitLedAralik) {
        yakitLedSonZaman = simdi;
        
        yakitLedDurumu = !yakitLedDurumu; 
        digitalWrite(yakitLedPin, yakitLedDurumu ? HIGH : LOW);
    }

    lcd.setCursor(0, 0);
    lcd.print("kritik: yakit ");
    lcd.setCursor(0, 1);
    lcd.print("cok az: %");
    lcd.print(yakitSeviyesi);
  }

  else{

    if(yakitMesajiVerildiMi){

      digitalWrite(yakitLedPin, LOW);
      lcd.clear();
      yakitMesajiVerildiMi = false;
    }
  }

//*********************************************************************************************************************************************************************************

  boolean suankiArabaButonDurumu = digitalRead(arabaMotorButonPin);

  if(suankiArabaButonDurumu == LOW && oncekiArabaButonDurumu == HIGH){    

    delay(50);

    if(kapiAnahtarPinDegeri == LOW){                                                            

      if(emniyetKemerDurumu){

        arabaMotorDurumu = !arabaMotorDurumu;

        if (arabaMotorDurumu)
          digitalWrite(arabaMotorPin, HIGH);
    
        else 
          digitalWrite(arabaMotorPin, LOW);
      }

      else{

        digitalWrite(emniyetKemerLedPin, HIGH);
        digitalWrite(buzzerPin, HIGH);

        lcd.setCursor(0, 0);
        lcd.print("emniyet kemeri");
        lcd.setCursor(0, 1);
        lcd.print("takili degil!");
      }
    }

    else{

      lcd.setCursor(0, 0);
      lcd.print("uyari: kapi acik!");
      lcd.setCursor(0, 1);
      lcd.print("motor calismaz");
    }
  }

  oncekiArabaButonDurumu = suankiArabaButonDurumu;

//*********************************************************************************************************************************************************************************

  double lm35Degeri = analogRead(lm35Pin);
  double sicaklik = lm35Degeri * 5.0 / 1023.0 * 100;          
                                                              
  if (sicaklik > 25) {                                       

    if (!klimaDurumu) 
        digitalWrite(klimaMotorPin, HIGH);

    klimaDurumu = true;

    lcd.setCursor(0, 0);
    lcd.print("sicaklik: ");
    lcd.print(sicaklik);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("klima acildi!");
  } 

  else {
  
    if (klimaDurumu) {

      digitalWrite(klimaMotorPin, LOW);
      lcd.clear(); 
      klimaDurumu = false;
    }
  }
  
//*********************************************************************************************************************************************************************************

  int ldrDegeri = analogRead(ldrPin);
  Serial1.println(ldrDegeri);

  if(ldrDegeri <= 250 && !farDurumu){

    digitalWrite(farLedPin, HIGH);
    farDurumu = true;
    lcd.print("farlar acildi!");
  }

  else if(ldrDegeri > 250 && farDurumu){

    digitalWrite(farLedPin, LOW);
    farDurumu = false;
    lcd.clear();
    lcd.print("farlar kapandi!");
    delay(500);
    lcd.clear();
  }
}

//*********************************************************************************************************************************************************************************









