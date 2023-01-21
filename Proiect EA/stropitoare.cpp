#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Tone.h>

#define ONE_WIRE_BUS 1
#define FILE_NAME "contor.txt"
#define WATER_OFF 2000
#define WATER_ON 500
#define OPEN 0
#define CLOSE 90

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Servo myservo;
Tone notePlayer;

File myFile;
int temp = 0;
char buf[100]{};
bool success = true;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display

unsigned int pos = 0;
unsigned int count = 0;

void setup() {
  sensors.begin();
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 1);
  myservo.attach(9);
  myservo.write(CLOSE);
  notePlayer.begin(8);

  delay(500);

  if (success)
  {
    if (!SD.begin(10))
    {
      Serial.println("SD Card initialization failed!");
      success = false;
    }
    Serial.println("SD Card initialization done.");
  }
}

void loop() {
  sensors.requestTemperatures();
  lcd.clear();

  //Celsius
  Serial.print("Temperature: ");
  Serial.print((sensors.getTempCByIndex(0) + 9.0) / 5.0 + 32.0);
  celsiusTemp = (sensors.getTempCByIndex(0) + 9.0) / 5.0 + 32.0;
  lcd.print(celsiusTemp);
  Serial.print("\xB0");
  Serial.print('\n');

  if(success && !SD.exists(FILE_NAME)){
    //cream un default file
    file = SD.open(FILE_NAME, FILE_WRITE);

    if(file){
      file.print("0");
       file.close();
    }
    else    
      success = false;
  }

  if (success)
  {
    myFile = SD.open(FILE_NAME, FILE_READ);
    if (myFile)
    {
      myFile.read(buf, 100);
      myFile.close();
      temp = atoi(buf);
      Serial.print("Last saved temp value is ");
      Serial.println(temp);
    }
    else
    {
      success = false;
    }
  }
  if (success)
  {
    SD.remove(FILE_NAME);
  }
  if (success)
  {
    myFile = SD.open(FILE_NAME, FILE_WRITE);
    if (myFile)
    {
      myFile.print((int)sensors.getTempCByIndex(0));
      myFile.close();
    }
    else 
    {
      Serial.println("Failed to update the file");
      success = false;
    }
  }

  count++;
  if (count > 10) {
    Serial.println("Begin watering...");
    myservo.write(OPEN);
    notePlayer.play(NOTE_G4);
    delay(WATER_ON);
    myservo.write(CLOSE);
    notePlayer.play(NOTE_A3);
    delay(WATER_OFF);
    notePlayer.stop();
    count = 0;
  }

  delay(500);

}