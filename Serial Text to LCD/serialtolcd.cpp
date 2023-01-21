/**
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <SPI.h>

#define MAX_BUFFER_SIZE 16
#define CS_PIN 10

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

File file;

void setup()
{
	lcd.begin();
	lcd.backlight();
  
	// Initialize the serial port at a speed of 9600
	Serial.begin(9600);

  //SD
  initializeSD();
  createFile("test.txt");
  writeToFile("Aries!!");
  closeFile();
}

void loop()
{
	// If characters arrived over the serial port...
	if (Serial.available()) {
		// Wait a bit for the entire message to arrive
		delay(100);
		// Clear the screen
		lcd.clear();
    lcd.setCursor(1, 0);

		// Write all characters received with the serial port to the LCD.
		while (Serial.available() > 0) {
      char buffer[MAX_BUFFER_SIZE];
      int pos = 0;
      char inByte = Serial.read();
 

      if(inByte != '\n'){
        buffer[pos++] = inByte;
        if(inByte != '\0')
          lcd.write(inByte);
      }
      else{
        buffer[pos] = '\0';
        pos = 0;
      }

      
		}
	}
}

void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}

bool createFile(char filename[]){
  file = SD.open(filename, FILE_WRITE);

  if (file){
    Serial.println("File created successfully.");
    return false;
  } 
  else{
    Serial.println("Error while creating file.");
    return true;
  }
}

bool writeToFile(char text[]){
  if (file){
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return true;
  } 
  else{
    Serial.println("Couldn't write to file");
    return false;
  }
}

void closeFile(){
  if (file){
    file.close();
    Serial.println("File closed");
  }
}

int openFile(char filename[]){
  file = SD.open(filename);
  if (file){
    Serial.println("File opened with success!");
    return 1;
  }
  else{
    Serial.println("Error opening file...");
    return 0;
  }
}

String readLine(){
  String received = "";
  char ch;
  while (file.available()){
    ch = file.read();
    if (ch == '\n'){
      return String(received);
    }
    else{
      received += ch;
    }
  }
  return "";
}