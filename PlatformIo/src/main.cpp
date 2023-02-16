/* SpaceRat Arduino code by Kiki Hobby Repair - Still under development!!!
 MPU6050_light library license: MIT
 - L.G. Changed to achieve simultaneous movement on different axis
 */

#include <Wire.h>
#include <MPU6050_light.h>
#include <Mouse.h>
#include <Keyboard.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;
int Xang, Yang, Zang;


int Xmov = 0;
int Ymov = 0;
int Zoom = 0;


int done = 0;
int buttonState = 0;
int button = 7;
int hall = 9;
int rot;
int rotMap;

void pressed()
{

  buttonState = !buttonState;
  digitalWrite(LED_BUILTIN, buttonState);
//  Serial.println(buttonState);
}
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button, INPUT);
  pinMode(hall, INPUT);
  attachInterrupt(4, pressed, RISING);

  //Serial.begin(9600);
  //while (!Serial)
    ;

  Wire.begin();
  byte status = mpu.begin();
  while (status != 0)
  {
  }
  delay(1000);
  mpu.calcOffsets();
  Mouse.begin();
  Keyboard.begin();
}

void loop()
{

  mpu.update();

  if ((millis() - timer) > 50)
  {

    // Reading the MPU data
    Xang = mpu.getAngleX();
    Yang = mpu.getAngleY();
    Zang = mpu.getAngleZ();

    // Reading the Hall sensor data
    rot = analogRead(hall);

    // Logic for the Mouse and Keyboard movements
    if (buttonState == 0)
    {
      if (Yang > 6)
      {
        Mouse.press(MOUSE_RIGHT);
        Xmov = map(Yang, 6, 10, 1, 10);
        done = 1;
      }

      else if (Yang < -6)
      {
        Mouse.press(MOUSE_RIGHT);
        Xmov = map(Yang, -10, -6, -10, -1);
        done = 1;
      }
      else
      {
        Xmov = 0;
      }

      if (Xang > 6)
      {
        Mouse.press(MOUSE_RIGHT);
        Ymov = map(Xang, 6, 10, 1, 10);
        done = 1;
      }

      else if (Xang < -6)
      {
        Mouse.press(MOUSE_RIGHT);
        Ymov = map(Xang, -10, -6, -10, -1);
        done = 1;
      }
      else
      {
        Ymov = 0;
      }

      if (rot < 500)
      {
        rotMap = map(rot, 500, 320, 0, 10);
        Zoom = -rotMap / 10;
//Serial.println(Zoom);
        done = 1;
      }
      else if (rot > 600)
      {
        rotMap = map(rot, 600, 730, 0, 10);
        Zoom = rotMap / 10;
//Serial.println(Zoom);
        done = 1;
      }
      else
      {
        Zoom = 0;
      }

      if ((Xmov == 0) && (Ymov == 0) && (Zoom == 0))
      {

        if (done == 1)
        {
          Mouse.release(MOUSE_RIGHT);
          Keyboard.write(KEY_ESC);
          done = 0;
        }
      }
      else {

      Mouse.move(Xmov / 5, Ymov / 5, Zoom);
      Xmov = 0;
      Ymov = 0;
      Zoom = 0;
      }
    }

    else if (buttonState == 1)
    {
      if (Yang > 6)
      {
        Mouse.press(MOUSE_MIDDLE);
        Xmov = map(Yang, 6, 10, 1, 10);
        done = 1;
      }

      else
        if (Yang < -6)
        {
          Mouse.press(MOUSE_MIDDLE);
          Xmov = map(Yang, -10, -6, -10, -1);
          done = 1;
        }
      else
      {
        Xmov = 0;
      }

      if (Xang > 6)
      {
        Mouse.press(MOUSE_MIDDLE);
        Ymov = map(Xang, 6, 10, 1, 10);
        done = 1;
      }

      else if (Xang < -6)
      {
        Mouse.press(MOUSE_MIDDLE);
        Ymov = map(Xang, -10, -6, -10, -1);
        done = 1;
      }
      else
      {
        Ymov = 0;
      }
      if (rot < 500)
      {
        rotMap = map(rot, 500, 320, 0, 10);
        Zoom = -rotMap / 10;
        done = 1;
      }
      else if (rot > 600)
      {
        rotMap = map(rot, 600, 730, 0, 10);
        Zoom = rotMap / 10;
        done = 1;
      }
      else
      {
        Zoom = 0;
      }

      if ((Xmov == 0) && (Ymov == 0) && (Zoom == 0))
      {

        if (done == 1)
        {
          Mouse.release(MOUSE_MIDDLE);
         // Mouse.release(MOUSE_RIGHT);
          Keyboard.write(KEY_ESC);
          done = 0;
        }
      }
        else {

      Mouse.move(Xmov / 5, Ymov / 5, Zoom);
      Xmov = 0;
      Ymov = 0;
      Zoom = 0;
      }
    }
    
    timer = millis();
  }
}
