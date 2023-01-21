void setup(){
  
  //LED
  DDRD |= ( 1 << PD5);
  
  //BUTTON1
  DDRD &= ~(1 << PD3);
  PORTD |= (1 << PD3); //activam R de Pull Up
  //BUTTON2
  DDRD &= ~(1 << PD2);
  PORTD |= (1 << PD2); //activam R de Pull Up

  //BUTTON3
  DDRD &= ~(1 << PD1);
  PORTD |= (1 << PD1);
}

int delay_amount = 500;

volatile unsigned int pressed = 0, counter = 0;

void loop(){
  
  	if((PIND & (1 << PD1)) == 0){
    PORTD &= ~(1 << PD5);
    pressed = 1;
  }
  
	if((PIND & (1 << PD3)) == 0){
      if(delay_amount > 200){
        delay_amount -=100;
      }
  	}
  
	if((PIND & (1 << PD2)) == 0){
  	   if(delay_amount < 1000){
         delay_amount +=100;
      }
 	}

  
 
  if(pressed == 0){
    PORTD |= (1 << PD5);
    delay(delay_amount);
    PORTD &= ~(1 << PD5);
    delay(delay_amount);
  }
}