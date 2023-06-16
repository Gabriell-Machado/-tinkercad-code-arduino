#include <LiquidCrystal_I2C.h> 

int ledVermelhoDireito = 4;
int ledVermelhoEsquerdo = 5;
int sonarTriggerDireito = 3;
int sonarTriggerEsquerdo = 7;
int sonarEchoDireito = 2;
int sonarEchoEsquerdo = 6;

int distanciaDireito = 0;
int distanciaEsquerdo = 0;
int tempoDireito = 0;
int tempoEsquerdo = 0;

LiquidCrystal_I2C oLCD(0x20, 16, 2); 

void setup() {
  pinMode(ledVermelhoDireito, OUTPUT);
  pinMode(ledVermelhoEsquerdo, OUTPUT);
  pinMode(sonarTriggerDireito, OUTPUT);
  pinMode(sonarTriggerEsquerdo, OUTPUT);
  pinMode(sonarEchoDireito, INPUT);
  pinMode(sonarEchoEsquerdo, INPUT);
  
  oLCD.init();
  oLCD.backlight();
  oLCD.clear(); 
  oLCD.print("Inicializando...");
  delay(2000);
  
  //Serial.begin(9600);  
}

void calcularDistancia(String sensor) {
  if(sensor == "direito") {
  digitalWrite(sonarTriggerDireito, LOW);
  delayMicroseconds(2);

  digitalWrite(sonarTriggerDireito, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(sonarTriggerDireito, LOW);
  
  tempoDireito = pulseIn(sonarEchoDireito, HIGH);
  distanciaDireito = tempoDireito/58.2;
  }
  
  else if(sensor == "esquerdo") {

  digitalWrite(sonarTriggerEsquerdo, LOW);
  delayMicroseconds(2);

  digitalWrite(sonarTriggerEsquerdo, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(sonarTriggerEsquerdo, LOW);
  
  tempoEsquerdo = pulseIn(sonarEchoEsquerdo, HIGH);
  distanciaEsquerdo = tempoEsquerdo/58.2;
  }
}

void loop() {
  calcularDistancia("esquerdo");
  calcularDistancia("direito");
  //Serial.println(distanciaDireito);
  //Serial.println(distanciaEsquerdo);
  if(distanciaDireito > distanciaEsquerdo){
    oLCD.clear();
    oLCD.print("Esquerda menor");
    digitalWrite(ledVermelhoEsquerdo, HIGH);
    digitalWrite(ledVermelhoDireito, LOW);
  }
  else if (distanciaEsquerdo > distanciaDireito) {
  	oLCD.clear();
    oLCD.print("Direito menor");
    digitalWrite(ledVermelhoDireito, HIGH);
    digitalWrite(ledVermelhoEsquerdo, LOW); 
  }
  delay(1000);
}
