/* https://e2e.ti.com/support/power-management-group/power-management/f/power-management-forum/742713/ev2300-evaluation-board-damaged-how-can-i-test*/

/*Zeno Modiff 
I2C Scanner 
https://www.youtube.com/channel/UC3x_svxO5Dxl0VesjEMpuGg 
sreeramzeno@gmail.com 
feel free to contact 
support me by subscribing to my channel */
#include <Arduino.h>
#include <Wire.h>

#define MUX_ADDRESS 0x70

void tcaselect(uint8_t i) {
   //if(i<7) return;
   Wire.beginTransmission(MUX_ADDRESS);
   Wire.write(1<<i);
   Wire.endTransmission();
}
 
 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
/*
  for (byte addr=0; addr<127; addr++) {
      Wire.beginTransmission(addr);
      int response = Wire.endTransmission();

      if(response==0) {
         Serial.print(F("Found I2C at 0x"));
         Serial.println(addr,HEX);
      }
      

        if(addr == MUX_ADDRESS) {
        //  Serial.print(F("Scanning port with address: 0x"));
        //  Serial.println(addr);
*/        
          for(uint8_t t=0; t<8; t++) { 
            tcaselect(t);
            Serial.print(F("TCA_Port#"));
            Serial.println(t);
            
            for(byte mux_addr=0; mux_addr<=127; mux_addr++) {  

              if(mux_addr==MUX_ADDRESS) continue;
               
                 Wire.beginTransmission(mux_addr);
                 int response = Wire.endTransmission();
    
                 if(response==0) {
                  Serial.print(F("Found I2C at 0x"));
                  Serial.println(mux_addr,HEX);
              
                 } 
            }
         }
//    Serial.println("\n");
//    delay(500);
      //}
       delay(100);
     //}
} 
 
void loop()
{
 /*
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    // Serial.print(F("checking address: "));
    // Serial.println(address);
 
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
 
  delay(5000);           // wait 5 seconds for next scan
  */
}