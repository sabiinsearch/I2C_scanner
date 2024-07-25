#include <Arduino.h>
#include <Wire.h>


int button_pin = 5;
int sda_pin = A4;
int scl_pin = A5;

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire

void setup() {
  WIRE.begin();

  Serial.begin(9600);

  pinMode(button_pin,INPUT);
  pinMode(scl_pin,OUTPUT);
  pinMode(sda_pin,OUTPUT);

  while (!Serial)
     delay(10);
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;
//  if(!(digitalRead(button_pin)==HIGH)) {

  Serial.println("Scanning...");

  nDevices = 0;
//  digitalWrite(scl_pin,HIGH);
  WIRE.begin();
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission(true);

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 // }  
  Wire.end();
  digitalWrite(scl_pin,LOW);
delay(5000);           // wait 5 seconds for next scan
}