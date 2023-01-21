void setup() {
  // put your setup code here, to run once:
  setColorRGB(0, 0, 0);
}

void loop() {
  unsigned int rgb[3];
  rgb[0] = 255;
  rgb[1] = 0;
  rgb[2] = 0;
  double hsv[3];
  hsv[0] = 0;
  hsv[1] = 1;
  hsv[2] = 0.1f;
  
  for (int i = 0; i < 360; i++) {
    hsv[0] = i;
    setLedColorHSV(hsv[0], hsv[1], hsv[2]);
    delay(5);    
  }
}

void setColorRGB(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(9, red);
  analogWrite(10, green);
  analogWrite(11, blue);
}

void setLedColorHSV(int h, double s, double v) {
  double r = 0;
  double g = 0;
  double b = 0;

  double hf = h / 60.0;

  int i = (int)floor(h / 60.0);
  double f = h / 60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s * f);
  double tv = v * (1 - s * (1 - f));

  switch (i)
  {
    case 0:
      r = v;
      g = tv;
      b = pv;
      break;
    case 1:
      r = qv;
      g = v;
      b = pv;
      break;
    case 2:
      r = pv;
      g = v;
      b = tv;
      break;
    case 3:
      r = pv;
      g = qv;
      b = v;
      break;
    case 4:
      r = tv;
      g = pv;
      b = v;
      break;
    case 5:
      r = v;
      g = pv;
      b = qv;
      break;
  }

  int red = constrain((int)255 * r, 0, 255);
  int green = constrain((int)255 * g, 0, 255);
  int blue = constrain((int)255 * b, 0, 255);
  setColorRGB(red, green, blue);
}