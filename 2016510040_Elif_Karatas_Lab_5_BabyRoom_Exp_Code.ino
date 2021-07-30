#include <LiquidCrystal.h> // for lcd screen
LiquidCrystal lcd(12,11,5,4,3,2); 
#include "DHT.h"
#define DHTPIN 8     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

String TIME_STRING = "2021.05.30 - 02:10:56"; // DATE AND TIME

// Date and time substring operations for lcd screen and time clock
int year = TIME_STRING.substring(0,4).toInt(); 
int month = TIME_STRING.substring(5,7).toInt();
int day = TIME_STRING.substring(8,10).toInt();
int hour = TIME_STRING.substring(13,15).toInt();
int minute = TIME_STRING.substring(16,18).toInt();
int second = TIME_STRING.substring(19,21).toInt();

int light;
int temperature;
int humidity;

int WAIT = 3000; // delay 3 seconds

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  dht.begin();
}

void loop() {
  light=analogRead(A0); // Light sensor
  temperature = dht.readTemperature(); // Temperature and humidity sensor
  humidity = dht.readHumidity();

   // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    lcd.println("DHT read error!");
    return;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hour: ");
  second++; // second increase
  if(hour<10){ // if hour is less than 10, than add 0 to start cursor
    lcd.print("0");
  }
  lcd.print(hour);
  lcd.print(":");
  if(minute<10){ // if minute is less than 10, than add 0 to start cursor
    lcd.print("0");
  }
  lcd.print(minute);
  lcd.print(":");
  if(second<10){ // if hour is less than 10, than add 0 to start cursor
    lcd.print("0");
  }
  lcd.print(second);      
  if(second==59){
    second = 0;
    lcd.setCursor(6,0);
    minute++; // increase minute for every 60 seconds
  }
  if(minute == 60){
    minute = 0;
    lcd.setCursor(3,0);
    hour++; // increase hour for every 60 minutes
  }
  lcd.setCursor(0,1);

  // date and time display
  lcd.print("Date: ");
  lcd.print(day);
  lcd.print(".");
  lcd.print(month);
  lcd.print(".");
  lcd.print(year);
  delay(WAIT);

  // light, temperature and humidity values display
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("L:");
  lcd.print(light);
  lcd.print(" T:");
  lcd.print(temperature);
  lcd.print("C ");
  lcd.print("H:");
  lcd.print(humidity);
  lcd.print("%");
  delay(WAIT);

  // room mood display
  lcd.clear();
  lcd.setCursor(0,0);
  if(light>=400){
    lcd.print("Day-");
  }
  else lcd.print("Night-");
  
  if((light>= 400 && (temperature <=24 && temperature >= 20)) || (light<400 && (temperature <=21 && temperature >= 18))){
    lcd.print("Opt T");
  }
  else if(light>= 400 && temperature<20){
    lcd.print("Cold ");
  }
  else if(light>= 400 && temperature>24){
    lcd.print("Hot");
  }
  else if(light< 400 && temperature<18){
    lcd.print("Cold ");
  }
  else if(light< 400 && temperature>21){
    lcd.print("Hot");
  }
  lcd.setCursor(0,1);
  if(humidity >= 30 && humidity <= 50){
    lcd.print("Opt Humidity");
  }
  else if(humidity < 30){
    lcd.print("Low Humidity");
  }
  else if(humidity > 50){
    lcd.print("High Humidity");
  }
  delay(WAIT);
}

/* references:
[1] https://create.arduino.cc/projecthub/pibots555/how-to-connect-dht11-sensor-with-arduino-uno-f4d239
[2] https://www.arduino.cc/reference/en/libraries/dht-sensor-library/ 
 */ 
