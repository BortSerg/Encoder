/*
  Код для обработки инкрементального энкодера, 
  ручка которого перемещается дискретно,
  и переход из одного положения в другое сопровождается сменой
  всех четырёх состояний выходов. 
*/


// используемые пины
const int encPinA=6; // первый выход энкодера
const int encPinB=5; // второй выход энкодера
const int PinSW=0; // кнопка

// переменные для хранения состояний пинов 
// (чтобы не производить ненужных считываний)
boolean encA;
boolean encB;
boolean sw;
boolean mem= false;

// переменные для информации о предыдущих состояниях
// и движениях энкодера
boolean prev11; // предыдущее состояние было 11
boolean clockwise1=true; // переход по часовой стрелке 1 (от 11)
boolean clockwise2=false; // переход по часовой стрелке 2 (от 00)

// изменяемое значение
int value=0;





void setup() {
  Serial.begin(115200);
  pinMode(encPinA, INPUT);
  digitalWrite(encPinA, HIGH); // включаем подтяжку к плюсу
  pinMode(encPinB, INPUT);
  digitalWrite(encPinB, HIGH);
  pinMode(PinSW, INPUT);
  digitalWrite(PinSW, HIGH); // включаем подтяжку к плюсу

}


void loop() {
  //считывание кнопки энкодера
  sw = digitalRead(PinSW);
  if (sw == LOW && mem == false )
    {
      Serial.println("sw down");
      mem = true;
    }
  if (sw == HIGH && mem == true)
    {
      Serial.println("sw UP");
      mem = false;
    }
  // считывание состояния выходов энкодера
  encA = digitalRead(encPinA);
  encB = digitalRead(encPinB);    
  // если в состояние 11 пришли не из 11
  // и 2 раза детектировалось движение 
  // в одну и ту же сторону, то соответствующим 
  // образом изменяем значение переменной
  if ((encA)&&(encB)&&(!prev11)){
    if ((clockwise1)&&(clockwise2)){
        value++;
    }
    if ((!clockwise1)&&(!clockwise2)){
        value--; 
    }        
    Serial.println(value);
    prev11 = true;
  }
  // детектирование направления первого перехода (от 11)
  else if ((!encA)&&(encB)&&(prev11)){
    clockwise1 = true;
    prev11 = false;
  }
  else if ((encA)&&(!encB)&&(prev11)){
    clockwise1 = false;
    prev11 = false;    
  }
  // детектирование направления второго перехода (от 00)
  else if ((!encA)&&(encB)&&(!prev11)){
    clockwise2 = false;
  }
  else if ((encA)&&(!encB)&&(!prev11)){
    clockwise2 = true;   
  }
}
