#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

int dataPositions[42];

void setup() {
  display.begin();
  display.setContrast(60);
    display.clearDisplay();

  Serial.begin(9600);
}

void loop() {
  int data = (analogRead(A0) / 23);
  Serial.println(data);
  memcpy(dataPositions, &dataPositions[1], sizeof(dataPositions) - sizeof(int));
  dataPositions[41] = data;
  for (int i=0; i<42; i++) {
    display.fillRect(84-i*2, dataPositions[i], 2, 5, 1);
    Serial.print(i);
    Serial.print("  ");
    Serial.println(dataPositions[i]);
  }
  
  display.display();
  delay(10);
  display.clearDisplay();
}
