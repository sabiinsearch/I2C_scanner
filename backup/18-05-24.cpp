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
#define FULL_CHARGE_CAPACITY     0x10       // U2 word         return mAh if CAPM bit = 0, 10 mWh if CAPM bit = 1
#define BAT_ADDRESS              0x0B
#define MFG_NAME                 0x20      // String
#define DESIGN_CAPACITY          0x18     //  U2               return mAh if CAPM bit = 0, 10 mWh if CAPM bit = 1
#define OLED_ADDRESS             0x3C 

void tcaselect(uint8_t i) {
   //if(i<7) return;
   Wire.beginTransmission(MUX_ADDRESS);
   Wire.write(1<<i);
   Wire.endTransmission();
}
 
// Function to read Capacity of battery 
int get_design_capacity() {
         
    byte byte_buffer[2];
    uint32_t myInt;
    
         Wire.beginTransmission(BAT_ADDRESS);
         Wire.write(DESIGN_CAPACITY);
         Wire.endTransmission();
         Wire.requestFrom(BAT_ADDRESS,sizeof(byte_buffer));

        int k=0;
        while(0 < Wire.available())
        {
         byte_buffer[k] = Wire.read();
         k++;
        }
          myInt = byte_buffer[0] + (byte_buffer[1] << 8);
          return myInt;           

} 

    char * getManufacturerName() {

    byte string_buffer[21];

    static char char_array[20];
     
     Wire.begin();

     Wire.beginTransmission(BAT_ADDRESS);

     Wire.write(MFG_NAME);

     Wire.endTransmission();

     Wire.requestFrom(BAT_ADDRESS,sizeof(string_buffer));

     int k=0;
     while(0 < Wire.available())
     {
      string_buffer[k] = Wire.read();

        if ((char)string_buffer[k] =='\0' ||  (char)string_buffer[k] =='&') { 
            string_buffer[k] = ' ';           
            break;
        } 
      k++;
     }
     
     //char_value = (char * )malloc(20);

     for(int n=0; n < k; n++) {
        char_array[n] = (char)string_buffer[n+1]; 
     }
//         Serial.print(char_array);

         return char_array;
}
 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
                 
            for(byte addr=0; addr<=127; addr++) {  
                
                Wire.beginTransmission(addr);
                int response = Wire.endTransmission();

                if(response==0) {

                  if(addr==MUX_ADDRESS) {

                    for(uint8_t t=0; t<8; t++) { 
                      tcaselect(t);
                      Serial.print(F("TCA_Port#"));
                      Serial.println(t);                                
                      
                      for(int mux_addr=0; mux_addr<127;mux_addr++) {

                         if((mux_addr==MUX_ADDRESS) || (mux_addr==OLED_ADDRESS)) continue;

                      Wire.beginTransmission(mux_addr);
                      int response_local = Wire.endTransmission();
          
                       if(response_local==0) {

                        Serial.print(F("Found I2C at 0x"));
                        Serial.print(mux_addr,HEX);          
                        Serial.print("\t");
                        Serial.print("Manufacturer: ");
                        Serial.print(getManufacturerName());
                        Serial.print("\t");

                        Serial.print("Design Capacity: ");
                        Serial.println(get_design_capacity());                  

                       }
                      }
                  
                }
              }

            Serial.print(F("Found I2C at 0x"));
            Serial.print(addr,HEX);          
            Serial.print(" - \t");
                  
            }                
                  

          } 
                  
}         
 
void loop()
{

}