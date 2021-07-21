/*
    Author: Özgür Koca
    Update: 18.7.2021

  ss963   Uno         Logic Analyzer
  -----   ---         --------------
  Reset   8           4
  Latch   9           3
  Data    11  (MOSI)  1
  CLK     13  (SCL)   2
  Gnd     Gnd         Gnd
*/


/*
 * Hardware config.
 */
int DATA_PIN = 11; /* MOSI */
int LATCH_PIN = 9;
int RESET_PIN = 8;
int V5BMODE_PIN = 7;
int LATCH_DELAY_MS = 1;

/*
 * First, configure below.
 */
int PORT_COUNT = 192;
byte ports[192];
byte byte_array[24]; // PORT_COUNT/8


#include <SPI.h>
#include "lib.h"
int i;

void setup() {
  pinMode(RESET_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(V5BMODE_PIN, INPUT_PULLUP);
  digitalWrite(RESET_PIN, HIGH);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2); /* 16MHz/2 = 8MHz hiza ayarla */
  Serial.begin(115200);
}

void detect_v5b_mode()
{
  if (digitalRead(V5BMODE_PIN) == 0) {
    digitalWrite(RESET_PIN, LOW); /* OE^ */
  } else {
    digitalWrite(RESET_PIN, HIGH);
  }
}

void loop() {

  /* 
   *  V5BMODE_PIN butonuna basılmışsa 
   *  V5B'ye göre test et. 
   */  
  detect_v5b_mode();

  fill_ports(ports, 0);
  for (i = 0; i <= 191; i++)
  {
    ports[i] = HIGH;
    write_ports(ports);
    delay(20);    
  }

  for (i = 0; i < 3; i++)
  {
    fill_ports(ports, 0);
    write_ports(ports);
    delay(400);
    fill_ports(ports, 1);
    write_ports(ports);
    detect_v5b_mode();
    delay(400);
  }

  for (i = 191; i >= 0; i--)
  {
    ports[i] = LOW;
    write_ports(ports);
    detect_v5b_mode();
    delay(20);
  }

}
