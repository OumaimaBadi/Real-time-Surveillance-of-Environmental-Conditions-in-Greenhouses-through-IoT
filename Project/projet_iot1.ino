#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(10, OUTPUT);//Ventilateur
  pinMode(7, OUTPUT);//Chauffage
  pinMode(6, OUTPUT);//Pompe
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);//Capteur de l'humidité dans le sol
  pinMode(A1, INPUT);//Capteur de luminosité
  pinMode(A3, INPUT);//Capteur de la température
  
}

void loop(){
  tempSensor();
  photoresistor();
  humiditySensor();
}

void photoresistor(){
int ld = analogRead(A1);
  //Serial.println(ld);
  int ldr = map(ld, 0, 1023, 0, 100);
  //Serial.println("Niveau de luminosité : " + String(ldr));
  lcd.setCursor(1,0);
  lcd.print("Intensity");
  lcd.setCursor(12,0);
  lcd.print(ldr);
  if (ldr<40)
  {  
     lcd.setCursor(4,1);
     lcd.print("TOO DARK");
     digitalWrite (9,HIGH);//Lampe s'allume
  }
  if (ldr>50)
  {
     lcd.setCursor(4,1);
     lcd.print("TOO BRIGHT");
	 digitalWrite (9,LOW);//Lampe s'éteint 
  }
  if(ldr<50 && ldr>40){
    
    lcd.setCursor(4,1);
  	lcd.print("NORMAL");
  digitalWrite (9,LOW);
  }
  
  delay(1000);
  lcd.clear();
}
 

void tempSensor() {
  
  // Calculant la température en Celcius
  float voltage=analogRead(A3)*0.004882814;
  float temp = ( voltage - 0.5 ) * 100;
 
  lcd.setCursor(3,0);
  lcd.print("Temp :");   
  lcd.setCursor(8,0); 
  lcd.print(temp);

  if (temp<20)
  {
    lcd.setCursor(4,1);
    lcd.print("Low Temp");    
    digitalWrite (7,HIGH);//Chauffage s'allume
    digitalWrite (10,LOW);//Le ventilateur s'éteint 
  }
  
   if (temp>20 &&  temp<40)
  {
    lcd.setCursor(4,1);
    lcd.print("Normal Temp");
     digitalWrite (7,LOW);
     digitalWrite (10,LOW);
   }
  
  if (temp>40){
    lcd.setCursor(4,1);
    lcd.print("High Temp");
    digitalWrite (7,LOW);//Chauffage s'éteint
    digitalWrite (10,HIGH);//Ventilateur s'allume
   }
  
  delay(1000);
  lcd.clear();
}

void humiditySensor(){
  int humidVoltage = analogRead(A0);
  //Serial.println(humidVoltage);
  int humidLevel = map(humidVoltage, 0, 1023, 0, 100);
  //Serial.println("Niveau d'humidité : " + String(humidLevel)); 
  if (humidLevel<50)
  {
    lcd.setCursor(1,0);
    lcd.print("Humidity :");
    lcd.print(humidLevel);
    lcd.setCursor(4,1);
    lcd.print("Pompe ON");
    digitalWrite (6,HIGH);
  
  }
  if (humidLevel<70 && humidLevel>50)
  {
    lcd.setCursor(1,0);
    lcd.print("Humidity Normal");
    lcd.print(humidLevel);
    lcd.setCursor(4,1);
    lcd.print("Pompe OFF"); 
    digitalWrite (6,LOW);
  }
  
  if (humidLevel>70)
  {
    lcd.setCursor(1,0);
    lcd.print("Humidity: ");
    lcd.print(humidLevel);
    lcd.setCursor(4,1);
    lcd.print("Pompe OFF");
    digitalWrite (6,LOW);
 
  }
  delay(1000);
  lcd.clear();
}