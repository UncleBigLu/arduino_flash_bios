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



//Prints hex/dec formatted data from page reads - for debugging
void _printPageBytes(uint8_t *data_buffer, uint8_t outputType) {
  char buffer[10];
  for (int a = 0; a < 16; ++a) {
    for (int b = 0; b < 16; ++b) {
      if (outputType == 1) {
        sprintf(buffer, "%02x", data_buffer[a * 16 + b]);
        Serial.print(buffer);
      }
      else if (outputType == 2) {
        uint8_t x = data_buffer[a * 16 + b];
        if (x < 10) Serial.print("0");
        if (x < 100) Serial.print("0");
        Serial.print(x);
        Serial.print(',');
      }
    }
    Serial.println();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Waiting for commands");
  while(!Serial.available());
  Serial.println("Executing");
  
  resetQPI();

  static SPIFlash flash;
  flash.begin();

  // Read entire flash memory and print
  Serial.println("Reading all pages");
  uint8_t data_buffer[256];

  uint32_t maxAddr = flash.getCapacity();
  Serial.print("maxAddr: ");
  Serial.println(maxAddr);
  for(int a = 0; a < maxAddr; ++a) {
    flash.readByteArray(a, &data_buffer[0], 256);
    _printPageBytes(data_buffer, 1);
    delay(100);
  }
}

void loop() {
  
}
