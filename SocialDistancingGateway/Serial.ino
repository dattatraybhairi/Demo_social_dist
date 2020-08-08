void select_freq()
{
  /*Serial.println("\n Enter the freq 1. 2480\n2. 2460\n3.2440\n4. 2420");
  while(1)
  {
    if(Serial.available())
    {
     recv =  Serial.parseInt();
     Serial.print("\n enter value is = ");
     Serial.println(recv);
    break;
    }
  }*/

  switch(recv)
  {
    case 1:
    //Serial.print("\n2480");
     VAL_FREQ2 = 0x5F;  // 2480Mhz
     VAL_FREQ1 = 0x62;
     VAL_FREQ0 = 0x76;
     break;

     case 2:
    // Serial.print("\n2460");
    
     VAL_FREQ2 = 0x5E;  //2460Mhz
     VAL_FREQ1 = 0x9D;
     VAL_FREQ0 = 0x89;
     break;

     case 3:
     //Serial.print("\n2440");
    
     VAL_FREQ2 = 0x5D;    // 2440Mhz
     VAL_FREQ1 = 0xD8;
     VAL_FREQ0 = 0x9D;
     break;

     case 4:
    // Serial.print("\n2420");
    
     VAL_FREQ2 = 0x5D;    // 2420Mhz
     VAL_FREQ1 = 0x13;    
     VAL_FREQ0 = 0xB1;
     break;

     case 5:
   //  Serial.print("\n2433");
    
     VAL_FREQ2 = 0x5D;    // 2433Mhz
     VAL_FREQ1 = 0x93;    
     VAL_FREQ0 = 0xB1;
     break;

     case 6:
   //  Serial.print("\n2400");
    
     VAL_FREQ2 = 0x5C;    // 2400.5Mhz
     VAL_FREQ1 = 0x4E;    
     VAL_FREQ0 = 0xC3;
     break;

     default:
     select_freq();
  }
}


void select_data()
{
  /*Serial.println("\n Enter the data rate 1. 500K\n2. 250K\n3.10K");
  while(1)
  {
    if(Serial.available())
    {
     recv =  Serial.parseInt();
    break;
    Serial.print("\nenter data is = ");
    Serial.print(recv);
    }
  }*/

  switch(recv)
  {
    case 1:       // for 500K baud
   // Serial.print("\n500K");
    
    VAL_FSCTRL1  = 0x10;   // Frequency synthesizer control.
    VAL_FSCTRL0  = 0x00;   // Frequency synthesizer control.
    VAL_MDMCFG4  = 0x0E;   // Modem configuration.
    VAL_MDMCFG3  = 0x3B;   // Modem configuration.
    VAL_MDMCFG2  = 0x73;   // Modem configuration.
    VAL_MDMCFG1  = 0x42;   // Modem configuration.
    VAL_MDMCFG0  = 0xF8;   // Modem configuration.
    VAL_DEVIATN  = 0x00;   // Modem deviation setting (when FSK modulation is enabled).
    VAL_FREND1   = 0xB6;   // Front end RX configuration.
    VAL_FREND0   = 0x10;   // Front end RX configuration.
    //VAL_MCSM0    = 0x14;   // Main Radio Control State Machine configuration.
    VAL_MCSM0    = 0x04;
    VAL_FOCCFG   = 0x1D;   // Frequency Offset Compensation Configuration.
    VAL_BSCFG    = 0x1C;   // Bit synchronization Configuration.
    VAL_AGCCTRL2 = 0xC7;   // AGC control.
    VAL_AGCCTRL1 = 0x40;   // AGC control.
    VAL_AGCCTRL0 = 0xB2;   // AGC control.
    VAL_FSCAL3   = 0xEA;   // Frequency synthesizer calibration.
    VAL_FSCAL2   = 0x0A;   // Frequency synthesizer calibration.
    VAL_FSCAL0   = 0x11;   // Frequency synthesizer calibration.
    VAL_TEST2    = 0x88;   // Various test settings.
    VAL_TEST1    = 0x31;   // Various test settings.
    VAL_TEST0    = 0x0B;   // Various test settings.
    RSSI_offset = 72;
    break;

    case 2:                 // for 250K baud
    //Serial.print("\n250K");
    
//    VAL_FSCTRL1  = 0x0A;   // Frequency synthesizer control.
//    VAL_FSCTRL0  = 0x00;   // Frequency synthesizer control.
//    VAL_MDMCFG4  = 0x2D;   // Modem configuration.
//    VAL_MDMCFG3  = 0x3B;   // Modem configuration.
//    VAL_MDMCFG2  = 0x73;   // Modem configuration.
//    VAL_MDMCFG1  = 0x22;   // Modem configuration.
//    VAL_MDMCFG0  = 0xF8;   // Modem configuration.
//    VAL_DEVIATN  = 0x00;   // Modem deviation setting (when FSK modulation is enabled).
//    VAL_FREND1   = 0xB6;   // Front end RX configuration.
//    VAL_FREND0   = 0x10;   // Front end RX configuration.
//    VAL_MCSM0    = 0x14;   // Main Radio Control State Machine configuration.
//    VAL_FOCCFG   = 0x1D;   // Frequency Offset Compensation Configuration.
//    VAL_BSCFG    = 0x1C;   // Bit synchronization Configuration.
//    VAL_AGCCTRL2 = 0xC7;   // AGC control.
//    VAL_AGCCTRL1 = 0x00;   // AGC control.
//    VAL_AGCCTRL0 = 0xB2;   // AGC control.
//    VAL_FSCAL3   = 0xEA;   // Frequency synthesizer calibration.
//    VAL_FSCAL2   = 0x0A;   // Frequency synthesizer calibration.
//    VAL_FSCAL0   = 0x11;   // Frequency synthesizer calibration.
//    VAL_TEST2    = 0x88;   // Various test settings.
//    VAL_TEST1    = 0x31;   // Various test settings.
//    VAL_TEST0    = 0x0B;   // Various test settings.
    VAL_FSCTRL1  = 0x0A;   // Frequency synthesizer control.
    VAL_FSCTRL0  = 0x00;   // Frequency synthesizer control.
    VAL_MDMCFG4  = 0x2D;   // Modem configuration.
    VAL_MDMCFG3  = 0x3B;   // Modem configuration.
    VAL_MDMCFG2  = 0x73;   // Modem configuration.
    VAL_MDMCFG1  = 0x22;   // Modem configuration.
    VAL_MDMCFG0  = 0xF8;   // Modem configuration.
    VAL_DEVIATN  = 0x00;   // Modem deviation setting (when FSK modulation is enabled).
    VAL_FREND1   = 0xB6;   // Front end RX configuration.
    VAL_FREND0   = 0x10;   // Front end RX configuration.
    VAL_MCSM0    = 0x14;   // Main Radio Control State Machine configuration.//18
    //VAL_MCSM0    = 0x04;
    VAL_FOCCFG   = 0x1D;   // Frequency Offset Compensation Configuration.
    VAL_BSCFG    = 0x1C;   // Bit synchronization Configuration.
    VAL_AGCCTRL2 = 0xC7;   // AGC control.
    VAL_AGCCTRL1 = 0x00;   // AGC control.
    VAL_AGCCTRL0 = 0xB2;   // AGC control. //B0
    VAL_FSCAL3   = 0xEA;   // Frequency synthesizer calibration.
    VAL_FSCAL2   = 0x0A;   // Frequency synthesizer calibration.
    VAL_FSCAL0   = 0x11;   // Frequency synthesizer calibration.
    VAL_TEST2    = 0x88;   // Various test settings.
    VAL_TEST1    = 0x31;   // Various test settings.
    VAL_TEST0    = 0x0B;   // Various test settings.
    RSSI_offset = 72;
    break;

    case 3:                 // for 10K baud
    //Serial.print("\n10K");
    
    VAL_FSCTRL1  = 0x08;   // Frequency synthesizer control.
    VAL_FSCTRL0  = 0x00;   // Frequency synthesizer control.
    VAL_MDMCFG4  = 0x78;   // Modem configuration.
    VAL_MDMCFG3  = 0x93;   // Modem configuration.
    VAL_MDMCFG2  = 0x03;   // Modem configuration. // 73 for MSK
    VAL_MDMCFG1  = 0x22;   // Modem configuration.
    VAL_MDMCFG0  = 0xF8;   // Modem configuration.
    VAL_DEVIATN  = 0x44;   // Modem deviation setting (when FSK modulation is enabled).
    VAL_FREND1   = 0x56;   // Front end RX configuration.
    VAL_FREND0   = 0x10;   // Front end RX configuration.
    VAL_MCSM0    = 0x14;   // Main Radio Control State Machine configuration.
    VAL_FOCCFG   = 0x16;   // Frequency Offset Compensation Configuration.
    VAL_BSCFG    = 0x6C;   // Bit synchronization Configuration.
    VAL_AGCCTRL2 = 0x43;   // AGC control.
    VAL_AGCCTRL1 = 0x40;   // AGC control.
    VAL_AGCCTRL0 = 0x91;   // AGC control.
    VAL_FSCAL3   = 0xA9;   // Frequency synthesizer calibration.
    VAL_FSCAL2   = 0x0A;   // Frequency synthesizer calibration.
    VAL_FSCAL0   = 0x11;   // Frequency synthesizer calibration.
    VAL_TEST2    = 0x88;   // Various test settings.
    VAL_TEST1    = 0x31;   // Various test settings.
    VAL_TEST0    = 0x0B;   // Various test settings.
    RSSI_offset = 69;
    break;

    default:
    select_data();
  }
}

/*
void watchdogSetup(void)
{
cli();  // disable all interrupts
wdt_reset(); // reset the WDT timer
/*
 WDTCSR configuration:
 WDIE = 1: Interrupt Enable
 WDE = 1 :Reset Enable
 WDP3 = 0 :For 2000ms Time-out
 WDP2 = 1 :For 2000ms Time-out
 WDP1 = 1 :For 2000ms Time-out
 WDP0 = 1 :For 2000ms Time-out
*/
// Enter Watchdog Configuration mode:
/*WDTCSR |= (1<<WDCE) | (1<<WDE);
// Set Watchdog settings:
 WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (0<<WDP0);  //4000 ms expected getting 4700 ms watchdog time
sei();
}*/
