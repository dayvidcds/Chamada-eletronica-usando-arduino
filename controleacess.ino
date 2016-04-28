#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <MFRC522.h>

#define buzzer 2
#define SS_PIN A4
#define RST_PIN 9
#define ledPin 7

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup(){
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(1,0);
  lcd.print("- ANAUELABS -");
  lcd.setCursor(1, 1);
  lcd.print("ControlAcess");
  delay(2000);
  pinMode(buzzer, OUTPUT);
  tone(buzzer, 450);
  delay(200);
  noTone(buzzer);
  delay(200);
  tone(buzzer, 450);
  delay(200);
  noTone(buzzer);
  lcd.clear();
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Aguardando...");
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  Serial.println("Aproxime o seu cartao do leitor...");
}

void loop() {
  lerCartao();
  delay(100);
}

void lerCartao(){
  if (!mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()){
    return;
  }
  
  Serial.print("ID da tag :");
  String conteudo= "";
  byte letra;
  
  for (byte i = 0; i < mfrc522.uid.size; i++){
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();  
  conteudo.toUpperCase();
  
  if(conteudo.substring(1) == "2D F2 33 CB"){
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Dayvid");
    delay(2000);
    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Aguardando...");

  }
  else if(conteudo.substring(1) == "CA 1C 4C 10"){
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Wedson");
    delay(2000);
    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Aguardando...");
  }
  else if(conteudo.substring(1) == "4E C0 33 CB"){
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Fernando");
    delay(2000);
    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Aguardando...");
  }
  else if(conteudo.substring(1) == "33 7E ED 00"){
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Distomia");
    delay(2000);
    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Aguardando...");
  }
  else{
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("ERROR");
    tone(buzzer, 450);
    delay(1000);
    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    lcd.clear();
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Aguardando...");
  }
  noTone(buzzer);
}
