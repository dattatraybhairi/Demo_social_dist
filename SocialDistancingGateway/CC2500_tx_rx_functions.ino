void CC2500_sendPacket(uint8_t pkt_len) {
  radioPktBuffer[0] = pkt_len;                  // Length byte

   SendStrobe(CC2500_SIDLE);
   SendStrobe(CC2500_SFTX);  // flush tx FIFO
   
   digitalWrite(SS,LOW);
   currentMillis3 = millis();
   while((digitalRead(MISO) == HIGH) && (millis() - currentMillis3 < 10));

   SPI.transfer(0x7F);  // 3f for single at a time 7f for burst
   for(uint8_t i=0;i<=pkt_len;i++)
   SPI.transfer(radioPktBuffer[i]);
   
   digitalWrite(SS,HIGH);

   SendStrobe(CC2500_STX); //Send data in tx fifo wirelessly
  // Serial.print("\n wait till GPO0 is LOW"); 
   currentMillis3 = millis();
   while((!digitalRead(GPO0)) && (millis()- currentMillis3 < 10));       // wait till data get transmitted
   //Serial.print("\n wait for GPIO gets HIGH");
   currentMillis3 = millis();
   while((digitalRead(GPO0))&& (millis() - currentMillis3 < 10));
  // Serial.print("\n done sending data");
   //SendStrobe(CC2500_SIDLE);
   //SendStrobe(CC2500_SFRX);
   //SendStrobe(CC2500_SRX);
  //Serial.print("\n S\n");
 /* for(uint8_t i=0;i<=pkt_len;i++)
  {
    Serial.print(radioPktBuffer[i]);
    Serial.print(" ");
  }*/
}

void CC2500_listenForPacket() {
  
  if(digitalRead(GPO0) == HIGH)
  {
     currentMillis3 = millis();
    while((digitalRead(GPO0) == HIGH) && (millis() - currentMillis3 < 10));       //wait till receiption gets end
    
   //Command to receive data wirelessly
 
  digitalWrite(SS,LOW);
   currentMillis3 = millis();
  while ((digitalRead(MISO) == HIGH)&& (millis() -currentMillis3 < 10));
     
  SPI.transfer(0xFF);  // bF for single byte by byte read // ff for burst read
  radioPktBuffer[0] = SPI.transfer(0x3D);

  if(radioPktBuffer[0] <= PACKET_LENGTH)
  {
    
      for(uint8_t i = 1; i <= (radioPktBuffer[0]+2) ;i++)
     radioPktBuffer[i] = SPI.transfer(0x3D);
    
      //rssi = SPI.transfer(0x3D);
      //lqi = SPI.transfer(0x3D);
      
      digitalWrite(SS,HIGH);
    
      //rssi_val = (rssi/2) - RSSI_offset;
      
    if((radioPktBuffer[radioPktBuffer[0] + 2] & 0x80) == 0x80)
      {
        radioPktBuffer[radioPktBuffer[0] + 1] = (-1)*convertRssiByte( radioPktBuffer[radioPktBuffer[0] + 1]);
      
        received = true;
//      Serial.print("\n"); 
//      for(uint8_t i = 1; i <= (radioPktBuffer[0]+2) ;i++)
//      {
//        Serial.print(radioPktBuffer[i], DEC);
//        Serial.print(" ");
//      }
       
    }

    else 
      {
        //Serial.print("\nCR ");
          //for(uint8_t i = 1; i <= (radioPktBuffer[0]+2) ;i++)
      {
        //Serial.print(radioPktBuffer[i], DEC);
        //Serial.print(" ");
      }
       //Serial.print("\r");
        SendStrobe(CC2500_SIDLE);
        SendStrobe(CC2500_SFRX);
        SendStrobe(CC2500_SRX);
      }
   }
  else
  {
    digitalWrite(SS,HIGH);
    //Serial.print("\n s \t\t");
   // Serial.print(ReadReg(0x7B),DEC);
    //Serial.print("\t");
    /*Serial.print(ReadReg(0x73),DEC);
    Serial.print("\t");*/
    //rssi_val = ReadReg(0x74);
    //rssi_val = ((rssi_val/ 2) - RSSI_offset);
    //Serial.print(rssi_val,DEC);
    SendStrobe(CC2500_SIDLE);
    SendStrobe(CC2500_SFRX);
    SendStrobe(CC2500_SRX);
  }
  }
  
  //else
  //Serial.print("\ne");
}

void send_rx_strobe()
{
  for(uint8_t m = 0; m < radioPktBuffer_len ; m++)
  radioPktBuffer[m] = 0 ;
  
  SendStrobe(CC2500_SIDLE);
  SendStrobe(CC2500_SFRX);
  SendStrobe(CC2500_SRX);
}

void switch_antenna(uint8_t ant_sel)
{
 if((ant_sel & 0x01) == 0x01)
 digitalWrite(sw_a,HIGH);
 else
 digitalWrite(sw_a,LOW);

if((ant_sel & 0x02) == 0x02)
 digitalWrite(sw_b,HIGH);
 else
 digitalWrite(sw_b,LOW);

 /*if((ant_sel & 0x04) == 0x04)
 digitalWrite(sw_c,HIGH);
 else
 digitalWrite(sw_c,LOW);*/
}

int8_t convertRssiByte(byte rssiComp)
{
    // Convert RSSI value from 2's complement to decimal value.
    int8_t rssiDec = (int8_t) rssiComp;

    // Convert to absolute value (RSSI value from radio has resolution of
    // 0.5 dBm) and subtract the radio's appropriate RSSI offset.
    if(rssiDec < 128){
        return (rssiDec/2) - RSSI_offset;
    }
    else{
        return ((rssiDec - 256)/2) - RSSI_offset;
    }
}
