/*
  This program is for read and write mx25l12873f flash chip.
  Tested using arduino mega2560.
*/

#include<SPIMemory.h>

#define MISO 50
#define MOSI 51
#define SS 53
#define SCK 52
#define SIO2 48
#define SIO3 49

/*
  Since mx25l12873f is on QPI mode by default according to its data sheet, and arduino 
  series only support 1 I/0 SPI mode, we need to first turn the chip into 1 I/0 mode.
*/


void resetQPI()
{
  // Init pins
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(SS, OUTPUT);
  pinMode(SCK, OUTPUT);
  pinMode(SIO2, OUTPUT);
  pinMode(SIO3, OUTPUT);

  // Reset QPI mode by input F5h
  digitalWrite(SS, HIGH);
  digitalWrite(SCK, LOW);
  
  digitalWrite(MISO, HIGH);
  digitalWrite(MOSI, HIGH);
  digitalWrite(SIO2, HIGH);
  digitalWrite(SIO3, HIGH);

  digitalWrite(SS, LOW);
  digitalWrite(SCK, HIGH);
  digitalWrite(SCK, LOW);

  digitalWrite(SIO3, LOW);
  digitalWrite(MISO, LOW);

  digitalWrite(SCK, HIGH);
  digitalWrite(SCK, LOW);

  digitalWrite(SS,HIGH);
  delay(1);
}



void arduino_println(char* c)
{
  Serial.print("Arduino:");
  Serial.println(c);
}

void read_flash(SPIFlash&);

void setup() {
  
  Serial.begin(115200);
  arduino_println("Press any key to reset QPI");
  // Waiting for user input
  int8_t c = Serial.read();
  while(c == -1) {
    c = Serial.read();
  }
  
  resetQPI();
  
  static SPIFlash flash;
  flash.begin();

  // Clear Serial buffer
  c = Serial.read();
  while(c != -1){
    c = Serial.read();
  }

  arduino_println("Please enter command:");
  arduino_println("1: Read flash out");
  arduino_println("2: Write flash from file");

  c = Serial.read();
  while(c == -1){
    c = Serial.read();
  }
  if(c == '1'){
    arduino_println("Read flash");
    read_flash(flash);
  }
  else{
    arduino_println("Write flash");
  }
//  // Read entire flash memory and print
//  Serial.println("Reading all pages");
//  uint8_t data_buffer[256];
//
//  uint32_t maxAddr = flash.getCapacity();
//  Serial.print("maxAddr: ");
//  Serial.println(maxAddr);
//  for(int a = 0; a < maxAddr; ++a) {
//    flash.readByteArray(a, &data_buffer[0], 256);
//    _printPageBytes(data_buffer, 1);
//    delay(100);
//  }
}

void loop() {
  
}

void read_flash(SPIFlash& flash) {
// Read entire chip and send binary data to serial
  
  uint8_t data_buffer[256];
  uint32_t maxAddr = flash.getCapacity();
  Serial.println(maxAddr);
  for(int a = 0; a < maxAddr; a+=256) {
    flash.readByteArray(a, &data_buffer[0],256);
    Serial.write(&data_buffer[0], 256);
  }
}
