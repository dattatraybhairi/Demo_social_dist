void WriteReg(char addr, char value){
  digitalWrite(SS,LOW);
  
  currentMillis3 = millis();
  while ((digitalRead(MISO) == HIGH) && (millis() -currentMillis3 < 10)) {
    };
    
  SPI.transfer(addr);
  delay(10);
  SPI.transfer(value);
  digitalWrite(SS,HIGH);
}

char ReadReg(char addr){
  addr = addr + 0x80;
  digitalWrite(SS,LOW);
  currentMillis3 = millis();
  while ((digitalRead(MISO) == HIGH) && (millis() -currentMillis3 < 10)) {
    };
  char x = SPI.transfer(addr);
  delay(10);
  char y = SPI.transfer(0);
  digitalWrite(SS,HIGH);
  return y;  
}

char SendStrobe(char strobe){
  digitalWrite(SS,LOW);
  
  currentMillis3 = millis();
  while ((digitalRead(MISO) == HIGH) && (millis() - currentMillis3 < 10)) {
  };
    
  char result =  SPI.transfer(strobe);
  digitalWrite(SS,HIGH);
  //delayMicroseconds(10);
  //delay(1);
  return result;
}
