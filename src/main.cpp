/* https://e2e.ti.com/support/power-management-group/power-management/f/power-management-forum/742713/ev2300-evaluation-board-damaged-how-can-i-test*/

/*Zeno Modiff 
I2C Scanner 
https://www.youtube.com/channel/UC3x_svxO5Dxl0VesjEMpuGg 
sreeramzeno@gmail.com 
feel free to contact 
support me by subscribing to my channel */
#include <Arduino.h>


#include "SoftwareI2C.h"

SoftwareI2C bus_1;
SoftwareI2C bus_2;

#define FULL_CHARGE_CAPACITY     0x10       // U2 word         return min
#define BAT_ADDRESS              0x0B
 


// Function to read Capacity of battery 
int get_full_charge_capacity(int bat_int) {
         
    byte byte_buffer[2];
    uint32_t myInt;
   
    switch(bat_int) {
      
      case 1:

         bus_1.beginTransmission(BAT_ADDRESS);
         bus_1.write(FULL_CHARGE_CAPACITY);
         bus_1.endTransmission();
         bus_1.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

        int k=0;
        while(0 < bus_1.available())
        {
         byte_buffer[k] = bus_1.read();
         k++;
        }
          myInt = byte_buffer[0] + (byte_buffer[1] << 8);

          break;
      
      case 2:
         bus_2.beginTransmission(BAT_ADDRESS);
         bus_2.write(FULL_CHARGE_CAPACITY);
         bus_2.endTransmission();
         bus_2.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

        int k=0;
        while(0 < bus_2.available())
        {
         byte_buffer[k] = bus_2.read();
         k++;
        }
          myInt = byte_buffer[0] + (byte_buffer[1] << 8);

          break;
        
      default:
          break;        
    }


//       myInt = byte_buffer[0] + byte_buffer[1];      
//     Serial.print((float)myInt/1000);   // convert Mili Volt to Volt
      
    // return ((float)myInt); 
       return myInt;

}

void setup()
{
  Serial.begin(9600);
  
  bus_1.begin(4,5);
  bus_2.begin(2,3);
 
  
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {

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
 
/************************  check input from batteries********/

    for (int i = 1; i < 3; i++) {
      
      Serial.print(F("Capacity of Bat "));
      Serial.print(i);
      Serial.print(F(" "));
      Serial.println(get_full_charge_capacity(i));
      Serial.println(F(""));
      delay(500);
    }

  delay(1000);           // wait 5 seconds for next scan
}