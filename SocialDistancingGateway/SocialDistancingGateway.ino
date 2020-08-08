/**
   This code listens Sensortag data for 15 seconds and transmit data to thingsboard.

   Hardware SPI NODEMCU:
   MISO -> GPIO12.
   MOSI -> GPIO13.
   SCLK/SCK -> GPIO14.
   CSN/SS - > GPIO15.

*/

#include "cc2500_REG.h"
#include "cc2500_VAL.h"
#define GPO0 5
#include <SPI.h>

#define PACKET_LENGTH 64
#define data_channel 150     //change channel here

#define No_of_tags 100
#define data_per_tag 7

#define sw_a 0
#define sw_b 2
//#define sw_c A5

#define LED_2 10
#define LED_3 16

#define reception_time 5000

bool received = false;
uint8_t RSSI_offset;

#define tx true
#define rx false

unsigned long currentMillis1 = 0, currentMillis3 = 0, currentMillis4 = 0;
//long sendInterval = 100; // in milliseconds
byte val = 0;
unsigned long currentMillis;

int16_t rssi_val;
int recv;

#define radioPktBuffer_len 70
uint8_t radioPktBuffer[radioPktBuffer_len];
bool mode;
boolean to_be_send = false;
uint8_t seq_no;
uint8_t unique_count = 0;
uint8_t health_count = 0;
uint8_t unique_pair_data[No_of_tags * data_per_tag];
uint8_t health_data[No_of_tags * data_per_tag];
uint8_t data_to_send[No_of_tags * data_per_tag];


void setup() {

  pinMode(sw_a, OUTPUT);
  pinMode(sw_b, OUTPUT);
  //pinMode(sw_c,OUTPUT);

  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  Serial.begin(9600);
  pinMode(GPO0, INPUT);
  // Setup
  pinMode(SS, OUTPUT);
  SPI.begin();
  digitalWrite(SS, HIGH);
  //Serial.print("\n Starting Code");
  init_CC2500();
  //Read_Config_Regs();
  //Serial.println("read end\t");
  received = false;
  switch_antenna(1);
  init_channel(data_channel);
  send_rx_strobe();

}

void loop() {
  clearData();
  // Reception Time = 30 secs
  currentMillis4 = millis();
  while (millis() - currentMillis4 < reception_time)
  {
    CC2500_listenForPacket();
    if (received)
    {
      received = false;
      find_uinque_pairs();
      send_rx_strobe();
    }
    yield();
  }

  merge_arrays();
  digitalWrite(LED_2, HIGH);delay(10);digitalWrite(LED_2, LOW);

  digitalWrite(LED_3, HIGH);
  for (uint8_t i = 0; i < 100; i++)
  {
    for (uint8_t j = 0; j < 7; j++)
    {
      Serial.write(unique_pair_data[i * 7 + j]);
    }
  }
  Serial.write(127);
  digitalWrite(LED_3, LOW);
  //  // Send data to Raspberry Pi
//    Serial.println();
//    Serial.println("================ Unique Pair Data ================");
//    for (uint8_t i = 0; i < unique_count; i++)
//    {
//      for (uint8_t j = 0; j < 7; j++)
//      {
//        Serial.print(unique_pair_data[i*7+j]);Serial.print(" ");
//      }
//      Serial.println();
//    }
//    Serial.println();
//    Serial.println("================ Health Data ================");
//    for (uint8_t i = 0; i < health_count; i++)
//    {
//      for (uint8_t j = 0; j < 6; j++)
//      {
//        Serial.print(health_data[i*6+j]);Serial.print(" ");
//      }
//      Serial.println();
//    }
  send_rx_strobe();
  yield();
}
