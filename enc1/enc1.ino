/*
  Код для обработки инкрементального энкодера.
*/

#include <LiquidCrystal.h>

// используемые пины
const int encPinA=6; // первый выход энкодера
const int encPinB=5; // второй выход энкодера 

// переменные для хранения состояний пинов 
// (чтобы не производить ненужных считываний)
boolean encA;
boolean encB;

byte prevState; // предыдущее состояние выходов

// изменяемое значение
int value=0; 

// символьный дисплей HD44780 16x2
// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void lcdUpdate(){
  lcd.clear();
  lcd.print(value);
}

// увеличение значения переменной
void valueInc(){  
  value++;
  lcdUpdate();
}

// уменьшение значения переменной
void valueDec(){
  value--;
  lcdUpdate();
}

void setup() {
  pinMode(encPinA, INPUT);
  digitalWrite(encPinA, HIGH); // включаем подтяжку к плюсу
  pinMode(encPinB, INPUT);
  digitalWrite(encPinB, HIGH);
  lcd.begin(16, 2);
  lcdUpdate();
}


void loop() {
  // считывание состояния выходов энкодера
  encA = digitalRead(encPinA);
  encB = digitalRead(encPinB);
  
  // детектирование переходов между состояниями
  // и последующее детектирование движения ручки энкодера
  // код комментирует сам себя :-)
  if ((encA)&&(encB)){
    if (prevState==B00000001){
      valueDec();
    }
    else if (prevState==B00000010){
      valueInc();
    }  
    prevState=B00000011;
  }
  
  else if ((!encA)&&(encB)){
    if (prevState==B00000000){
      valueDec();
    }
    else if (prevState==B00000011){
      valueInc();
    }  
    prevState=B00000001;
  } 

  else if ((!encA)&&(!encB)){
    if (prevState==B00000010){
      valueDec();
    }
    else if (prevState==B00000001){
      valueInc();
    }  
    prevState=B00000000;
  } 

  else if ((encA)&&(!encB)){
    if (prevState==B00000011){
      valueDec();
    }
    else if (prevState==B00000000){
      valueInc();
    }  
    prevState=B00000010;
  } 

}
