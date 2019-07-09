const int FLEX_PIN0 = A0; 
const int FLEX_PIN1 = A1;
const int FLEX_PIN2 = A2;
const int FLEX_PIN3 = A3;

const float VCC = 5; // Measured voltage of Ardunio 5V line
const float R_DIV = 33000.0; // Measured resistance of 3.3k resistor

const float STRAIGHT_RESISTANCE0 = 14000.0; // resistance when straight
const float STRAIGHT_RESISTANCE1 = 12000.0; // resistance when straight
const float STRAIGHT_RESISTANCE2 = 12000.0; // resistance when straight
const float STRAIGHT_RESISTANCE3 = 18000.0; // resistance when straight
const float BEND_RESISTANCE0 = 23000.0; // resistance at 90 deg
const float BEND_RESISTANCE1 = 25000.0; // resistance at 90 deg
const float BEND_RESISTANCE2 = 27000.0; // resistance at 90 deg
const float BEND_RESISTANCE3 = 35000.0; // resistance at 90 deg

void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN0, INPUT);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
}

void loop() 
{
  int flexADC0 = analogRead(FLEX_PIN0);
  int flexADC1 = analogRead(FLEX_PIN1);
  int flexADC2 = analogRead(FLEX_PIN2);
  int flexADC3 = analogRead(FLEX_PIN3);
  
  float flexV0 = flexADC0 * VCC / 1023.0;
  float flexV1 = flexADC1 * VCC / 1023.0;
  float flexV2 = flexADC2 * VCC / 1023.0;
  float flexV3 = flexADC3 * VCC / 1023.0;
  
  float flexR0 = R_DIV * (VCC / flexV0 - 1.0);
  float flexR1 = R_DIV * (VCC / flexV1 - 1.0);
  float flexR2 = R_DIV * (VCC / flexV2 - 1.0);
  float flexR3 = R_DIV * (VCC / flexV3 - 1.0);

  int angle0 = map(flexR0, STRAIGHT_RESISTANCE0, BEND_RESISTANCE0, 0, 90.0);
  int angle1 = map(flexR1, STRAIGHT_RESISTANCE1, BEND_RESISTANCE1, 0, 90.0);
  int angle2 = map(flexR2, STRAIGHT_RESISTANCE2, BEND_RESISTANCE2, 0, 90.0);
  int angle3 = map(flexR3, STRAIGHT_RESISTANCE3, BEND_RESISTANCE3, 0, 90.0);
  
  Serial.println(String(angle0) + " " + String(angle1) + " " + String(angle2) + " " + String(angle3));

  delay(250);
}
