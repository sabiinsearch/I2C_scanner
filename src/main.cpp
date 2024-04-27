/* https://e2e.ti.com/support/power-management-group/power-management/f/power-management-forum/742713/ev2300-evaluation-board-damaged-how-can-i-test*/

/*Zeno Modiff 
I2C Scanner 
https://www.youtube.com/channel/UC3x_svxO5Dxl0VesjEMpuGg 
sreeramzeno@gmail.com 
feel free to contact 
support me by subscribing to my channel */
#include <Arduino.h>
#include <Wire.h>

#define MUX_ADDRESS 0x70 // TCA9548A Encoders address
#define FULL_CHARGE_CAPACITY     0x10       // U2 word         return min
#define BAT_ADDRESS              0x0B
 

// Initialize I2C buses using TCA9548A I2C Multiplexer
void tcaselect(uint8_t i2c_bus) {
    if (i2c_bus > 7) return;
    Wire.beginTransmission(MUX_ADDRESS);
    Wire.write(1 << i2c_bus);
    Wire.endTransmission(); 
}
 
// Function to read Capacity of battery 
int get_full_charge_capacity(int bat_int) {
         
    byte byte_buffer[2];
    uint32_t myInt;
    
    tcaselect(bat_int);

    switch(bat_int) {
      
      case 1:

      // Wire.beginTransmission(MUX_ADDRESS);
         Wire.write(FULL_CHARGE_CAPACITY);
         Wire.endTransmission();
         Wire.requestFrom(MUX_ADDRESS,sizeof(byte_buffer));

        int k=0;
        while(0 < Wire.available())
        {
         byte_buffer[k] = Wire.read();
         k++;
        }
          myInt = byte_buffer[0] + (byte_buffer[1] << 8);

          break;
      
      case 2:
      // Wire.beginTransmission(BAT_ADDRESS);
         Wire.write(FULL_CHARGE_CAPACITY);
         Wire.endTransmission();
         Wire.requestFrom(MUX_ADDRESS,sizeof(byte_buffer));

        int j=0;
        while(0 < Wire.available())
        {
         byte_buffer[j] = Wire.read();
         k++;
        }
         myInt = byte_buffer[0] + (byte_buffer[1] << 8);

          break;
        
      default:
          break;        
    }
}


void setup()
{
  Wire.begin(MUX_ADDRESS);
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
 
 
void loop() 

{
  Serial.println(F("Capacity of "));

    for (int i=1;i<3;i++) {
      
      Serial.print(F("Bat "));
      Serial.print(i);
      Serial.print(F(": "));
      Serial.print(get_full_charge_capacity(i));
      Serial.print(F(" \t"));
      delay(200); 
    }
    Serial.println(F("\n"));
    delay(1000); 
}