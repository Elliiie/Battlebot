#include <XBOXRECV.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);

int back_right_en = 2;
int front_right_en = 3;
int front_left_en = 4;
int back_left_en = 5;

int front_right1 = 28;
int front_right2 = 29;
int back_right1 = 30;
int back_right2 = 31;

int front_left1 = 43;
int front_left2 = 42;
int back_left1 = 41;
int back_left2 = 40;

int relay = 6;

int speed = 0;

void setup() {
  Serial.begin(9600);

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));

  pinMode(back_right_en, OUTPUT);
  pinMode(front_right_en, OUTPUT);
  pinMode(front_left_en, OUTPUT);
  pinMode(back_left_en, OUTPUT);

  pinMode(front_right1, OUTPUT);
  pinMode(front_right2, OUTPUT);
  pinMode(back_right1, OUTPUT);
  pinMode(back_right2, OUTPUT);

  pinMode(front_left1, OUTPUT);
  pinMode(front_left2, OUTPUT);
  pinMode(back_left1, OUTPUT);
  pinMode(back_left2, OUTPUT);

  pinMode(relay, OUTPUT); 
}

void loop() {
  /*
  digitalWrite(relay, HiGH);
  delay(5iii);
  digitalWrite(relay, LOW);
  delay(1iii);
  */

  Serial.println(digitalRead(relay));

  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    if (Xbox.Xbox360Connected[0]) {
      if (Xbox.getButtonPress(R2, 0)) {
        Serial.print("R2: ");
        Serial.println(Xbox.getButtonPress(R2, 0));
        // Xbox.setRumbleOn(Xbox.getButtonPress(R2, i), i);

       speed = Xbox.getButtonPress(R2, 0);

        if (speed <= 150) {
          speed = 0;
        }

        forward(speed);
      }

      if (Xbox.getButtonPress(L2, 0)) {
        Serial.print("L2: ");
        Serial.println(Xbox.getButtonPress(L2, 0));
        // Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), i);

        speed = Xbox.getButtonPress(L2, 0);

        if (speed <= 150) {
          speed = 0;
        }

        backward(speed);
      }

      if (Xbox.getAnalogHat(LeftHatX, 0) > 7500 || Xbox.getAnalogHat(LeftHatX, 0) < -7500 || Xbox.getAnalogHat(LeftHatY, 0) > 7500 || Xbox.getAnalogHat(LeftHatY, 0) < -7500 || Xbox.getAnalogHat(RightHatX, 0) > 7500 || Xbox.getAnalogHat(RightHatX, 0) < -7500 || Xbox.getAnalogHat(RightHatY, 0) > 7500 || Xbox.getAnalogHat(RightHatY, 0) < -7500) {
        if (Xbox.getAnalogHat(LeftHatX, 0) > 7500 || Xbox.getAnalogHat(LeftHatX, 0) < -7500) {
          Serial.print(F("LeftHatX: "));
          Serial.print(Xbox.getAnalogHat(LeftHatX, 0));
          Serial.print("\t");

          if (Xbox.getAnalogHat(LeftHatY, 0) < 28000 && Xbox.getAnalogHat(LeftHatY, 0) > -28000) {
            if (Xbox.getAnalogHat(LeftHatX, 0) < -22000 ) {
              Serial.println("Turning left");
              turn_left();
            }
            else if (Xbox.getAnalogHat(LeftHatX, 0) > 22000) {
              Serial.println("Turning right");
              turn_right();
            }
            else {
              stop_moving();
            }
          }
          else {
            stop_moving();
          }

        }
        if (Xbox.getAnalogHat(LeftHatY, 0) > 7500 || Xbox.getAnalogHat(LeftHatY, 0) < -7500) {
          Serial.print(F("LeftHatY: "));
          Serial.print(Xbox.getAnalogHat(LeftHatY, 0));
          Serial.print("\t");
        }

        Serial.println();
      }

      

      if (Xbox.getButtonClick(XBOX, 0)) {
        Xbox.setLedMode(ROTATING, 0);
        Serial.print(F("Xbox (Battery: "));
        Serial.print(Xbox.getBatteryLevel(0)); // The battery level in the range i-3
        Serial.println(F(")"));
      }

      if (Xbox.getButtonClick(A, 0)) {
        Serial.println(F("A"));
        weaponOn();
      }
     
      if (Xbox.getButtonClick(B, 0)) {
        Serial.println(F("B"));
        weaponOff();
      }

    }
  }
}

void forward(int en_value) {
  analogWrite(back_right_en, en_value);
  analogWrite(front_right_en, en_value);
  analogWrite(front_left_en, en_value);
  analogWrite(back_left_en, en_value);

  digitalWrite(front_right1, HIGH);
  digitalWrite(front_right2, LOW);
  digitalWrite(back_right1, HIGH);
  digitalWrite(back_right2, LOW);

  digitalWrite(front_left1, HIGH);
  digitalWrite(front_left2, LOW);
  digitalWrite(back_left1, HIGH);
  digitalWrite(back_left2, LOW);
}

void backward(int en_value) {
  analogWrite(back_right_en, en_value);
  analogWrite(front_right_en, en_value);
  analogWrite(front_left_en, en_value);
  analogWrite(back_left_en, en_value);

  digitalWrite(front_right1, LOW);
  digitalWrite(front_right2, HIGH);
  digitalWrite(back_right1, LOW);
  digitalWrite(back_right2, HIGH);

  digitalWrite(front_left1, LOW);
  digitalWrite(front_left2, HIGH);
  digitalWrite(back_left1, LOW);
  digitalWrite(back_left2, HIGH);
}

void turn_left() {
  analogWrite(back_right_en, 255);
  analogWrite(front_right_en, 255);
  analogWrite(front_left_en, 255);
  analogWrite(back_left_en, 255);

  digitalWrite(front_right1, HIGH);
  digitalWrite(front_right2, LOW);
  digitalWrite(back_right1, HIGH);
  digitalWrite(back_right2, LOW);

  digitalWrite(front_left1, LOW);
  digitalWrite(front_left2, HIGH);
  digitalWrite(back_left1, LOW);
  digitalWrite(back_left2, HIGH);
}

void turn_right() {
  analogWrite(back_right_en, 255);
  analogWrite(front_right_en, 255);
  analogWrite(front_left_en, 255);
  analogWrite(back_left_en, 255);

  digitalWrite(front_right1, LOW);
  digitalWrite(front_right2, HIGH);
  digitalWrite(back_right1, LOW);
  digitalWrite(back_right2, HIGH);

  digitalWrite(front_left1, HIGH);
  digitalWrite(front_left2, LOW);
  digitalWrite(back_left1, HIGH);
  digitalWrite(back_left2, LOW);
}

void stop_moving() {
  analogWrite(back_right_en, 0);
  analogWrite(front_right_en, 0);
  analogWrite(front_left_en, 0);
  analogWrite(back_left_en, 0);

  digitalWrite(front_right1, LOW);
  digitalWrite(front_right2, LOW);
  digitalWrite(back_right1, LOW);
  digitalWrite(back_right2, LOW);

  digitalWrite(front_left1, LOW);
  digitalWrite(front_left2, LOW);
  digitalWrite(back_left1, LOW);
  digitalWrite(back_left2, LOW);
}

void weaponOn() {
  digitalWrite(relay, HIGH);
}

void weaponOff(){
  digitalWrite(relay, LOW);
}
