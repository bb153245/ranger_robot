#include <PRIZM.h>;

PRIZM bob;
int sonic;
bool stopped = false;

void setup() {

  bob.PrizmBegin();

  bob.setMotorInvert(2, 1);

  bob.setMotorSpeeds(400, 400);
  bob.setGreenLED(HIGH);
  Serial.begin(9600);

}

void loop() {
  sonic = bob.readSonicSensorCM(4);

  Serial.print(sonic);

  Serial.print(" - ");

  if (sonic <= 20) {
    Stop();
    stopped = true;
  } else if (stopped == true && sonic > 20){
    Pull_over();
  } else{
    Forward();
  }

}




void Forward() {
  bob.setMotorPowers(50, 50);
  bob.setServoPosition(1,90);
}

void Stop() {
  bob.setMotorPowers(125, 125);
  bob.setServoPosition(1,0);
  bob.setGreenLED(LOW);
  bob.setRedLED(HIGH);
}

void Pull_over() {
  bob.setServoPosition(1,90);
  bob.setGreenLED(HIGH);
  bob.setRedLED(LOW);
  bob.setMotorPower(1, -25);
  bob.setMotorPower(2, 25);
  delay(500);
  Forward();
  delay(1350);
  Stop();
  delay(1000);
  bob.setMotorPower(1, 10);
  bob.setMotorPower(2, -10);
  delay(1100);
  bob.setGreenLED(LOW);
  bob.setRedLED(HIGH);
  bob.setServoPosition(1,0);
  delay(750);
  bob.PrizmEnd();
}
