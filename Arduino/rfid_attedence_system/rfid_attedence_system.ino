#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
bool stopReading = false;  // Flag to stop reading new cards

void setup() {
  Serial.begin(9600);  // Initiate a serial communication
  SPI.begin();         // Initiate  SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  lcd.begin();
  lcd.backlight();
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to NI");
   lcd.setCursor(0, 1);
  lcd.print("GROUP - E");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || stopReading) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial() || stopReading) {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  lcd.setCursor(3, 1);
  lcd.print("Thank You");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Swap Your Card");
}

void stopReadingProcess() {
  stopReading = true;
}
