//masurarea voltmetrului si a tmp36-ului

void setup() {
  Serial.begin(9600);
}

void loop() {

  int reading = analogRead(A0);
  int reading2 = analogRead(A1);

  float voltage = reading * (5000 / 1024.0);

  float temperature = (voltage - 500) / 10;
  
  float v = reading2 / 1024.0;

  Serial.print(temperature);
  Serial.println(" C");
  Serial.print(v * 100);
  Serial.println(" ");

  delay(1000); 
}