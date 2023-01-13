#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <RFID.h>

LiquidCrystal lcd(0x27, 20, 4);

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

int buzzPin = 3;
int led = 2;

// Setup variables:
int serNum0, 
    serNum1, 
    serNum2, 
    serNum3, 
    serNum4;

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(5, 0); // Move to letter 0 on column 1
  lcd.print("Welcome To");
   
  lcd.setCursor(6, 1); // Move to letter 6 on column 2
  lcd.print("Electric Bike");
  
  lcd.setCursor(1, 2); // Move to letter 0 on column 1
  lcd.print("Please put your card on.");
}

void loop()
{
  if (rfid.isCard())
  {
    if (rfid.readCardSerial())
    {
      if (rfid.serNum[0] != serNum0 && rfid.serNum[1] != serNum1 && rfid.serNum[2] != serNum2 && rfid.serNum[3] != serNum3 && rfid.serNum[4] != serNum4)
      {

        /* With a new cardnumber, show it. */
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];

        // Serial.println(" ");
        Serial.println("Cardnumber:");
        Serial.print("Dec: ");
        Serial.print(rfid.serNum[0], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], DEC);
        Serial.println(" ");

        Serial.print("Hex: ");
        Serial.print(rfid.serNum[0], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], HEX);
        Serial.println(" ");
        // buzzer
        analogWrite(3, 20);
        delay(500);
        analogWrite(3, 0);
      }
      else
      {
        /* If we have the same ID, just write a dot. */
        Serial.print(".");
      }
      
      if (rfid.serNum[0] == serNum0 && rfid.serNum[1] == serNum1 && rfid.serNum[2] == serNum2 && rfid.serNum[3] == serNum3 && rfid.serNum[4] == serNum4)
      {
        digitalWrite(led, HIGH);
        Serial.println("LED ON");
      }
      else
      {
        digitalWrite(led, LOW);
        Serial.println("LED OFF");
      }
    }
  }
  rfid.halt();
}

// If the system meet unauthorized use, trigger the alarm
void isAlarm()
{
  
}
