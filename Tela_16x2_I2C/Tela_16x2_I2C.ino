// Programa : Display LCD 16x2 e modulo I2C

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27 ou 0x3f
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup()
{
 lcd.begin (16,2);
}
 
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Foodtece!!!");
  lcd.setCursor(0,1);
  lcd.print("Sejam Bem-vindo");
  delay(4000);
  lcd.setBacklight(LOW);
  delay(1000);
}
