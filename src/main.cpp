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
 

void tcaselect(uint8_t i) {
   //if(i<7) return;
   Wire.beginTransmission(MUX_ADDRESS);
   Wire.write(1<<i);
   Wire.endTransmission();
}
 
// Function to read Capacity of battery 
int get_full_charge_capacity() {
         
    byte byte_buffer[2];
    uint32_t myInt;
    
         Wire.beginTransmission(MUX_ADDRESS);
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
        //  myInt = byte_buffer[0] + byte_buffer[1];
          byte_buffer[0] = byte_buffer[1]= NULL;
          return myInt; 
          //return 1;

} 
 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
      

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
                  Serial.print(mux_addr,HEX);          
                  Serial.print("\t");
                  Serial.print("Charge Capacity: ");
                  Serial.println(get_full_charge_capacity());
                 } 
                  
            }
         }
//    Serial.println("\n");
//    delay(500);
      //}
       delay(100);
     //}

         Serial.println("Scanning..");     
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