void setup()
{
  DDRB |= (1 << PB5);
  DDRD &= ~(1 << PD2);
  PORTD |= (1 << PD2);
  Serial.begin(9600);
  delay(100);
  Serial.println("Initialized Serial");
}

char rxbuf[20];
int index = 0;
long ts = 0;
short blink_on = 0;

void loop()
{
  if (Serial.available()) {
    char a = Serial.read();
    //sprintf(txbuf, "%s: %c", "primit caracter", a);
    //Serial.println(txbuf);
    if (a == '!') {
      rxbuf[index] = '\0';
      Serial.println(rxbuf);
      if (strcmp(rxbuf, "on") == 0) {
        blink_on = 0;
        digitalWrite(13, HIGH);
      }
      if (strcmp(rxbuf, "off") == 0) {
        blink_on = 0;
        digitalWrite(13, LOW);
      }
      if (strcmp(rxbuf, "blink") == 0) {
        blink_on = !blink_on;
        PORTB &= ~(1 << PB5);
      }
      if (strcmp(rxbuf, "get") == 0) {
        Serial.print("button state: ");
        if ( (PIND & (1 << PD2)) ) {
            Serial.println( "unpressed" );
        } else {
            Serial.println( "pressed" );
        }

      }

      if ( strncmp(rxbuf, "analog", 6) == 0 ){
        int value;
        if (sscanf(rxbuf, "analog %d", &value) == 1){

            analogWrite(5, value);
        }
      }

      index = 0;
      rxbuf[index] = '\0';
    } else {
      rxbuf[index] = a;
      index++;
      rxbuf[index] = '\0';
    }
  }

  if (blink_on) {
    if ((millis() - ts) >= 500) {
      ts = millis();
      PORTB ^= (1 << PB5);
    }
  }
}