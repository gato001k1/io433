#include <ELECHOUSE_CC1101_SRC_DRV.h>

//#define TICC1101
//#define E07M1101D

#ifdef E07M1101D
 #define CCGDO0 25
 #define CCGDO2 -1
 #define CCSCK 0
 #define CCMISO 33
 #define CCMOSI 32
 #define CCCSN 26
#endif

#ifdef TICC1101
 #define CCGDO0 27
 #define CCGDO2 32
 #define CCSCK 26
 #define CCMISO 2
 #define CCMOSI 25
 #define CCCSN 33
#endif

void CCSetTx() {
  pinMode(CCGDO0,OUTPUT);
  ELECHOUSE_cc1101.SetTx();
}

void CCSetMhz(float freq) {
#if defined(EMBED)
    #define BOARD_LORA_SW1  47
    #define BOARD_LORA_SW0  48
    // SW1:1  SW0:0 --- 315MHz
    // SW1:0  SW0:1 --- 868/915MHz
    // SW1:1  SW0:1 --- 434MHz
    if (freq - 315 < 0.1)
    {
        digitalWrite(BOARD_LORA_SW1, HIGH);
        digitalWrite(BOARD_LORA_SW0, LOW);
        //Serial.println("315Mhz");
    }
    else if (freq - 434 < 0.1)
    {
        digitalWrite(BOARD_LORA_SW1, HIGH);
        digitalWrite(BOARD_LORA_SW0, HIGH);
        //Serial.println("434Mhz");
    }
    else if (freq - 868 < 0.1)
    {
        digitalWrite(BOARD_LORA_SW1, LOW);
        digitalWrite(BOARD_LORA_SW0, HIGH);
        //Serial.println("868Mhz");
    }
    else if (freq - 915 < 0.1)
    {
        digitalWrite(BOARD_LORA_SW1, LOW);
        digitalWrite(BOARD_LORA_SW0, HIGH);
        //Serial.println("915Mhz");
    }

#endif


  ELECHOUSE_cc1101.setMHZ(freq);
}

void CCSetRxBW(int bandwidth) {
  ELECHOUSE_cc1101.setRxBW(bandwidth);
}

void CCInit() {

  ELECHOUSE_cc1101.Init();                // must be set to initialize the cc1101!
  ELECHOUSE_cc1101.setGDO(CCGDO0, CCGDO2);
  ELECHOUSE_cc1101.getCC1101();
 // ELECHOUSE_cc1101.setPA(8);
                                          //The lib calculates the frequency automatically (default = 433.92).
                                          //The cc1101 can do: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
  ELECHOUSE_cc1101.setClb(1,13,15);
  ELECHOUSE_cc1101.setClb(2,16,19);
  ELECHOUSE_cc1101.setModulation(2);      // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
  ELECHOUSE_cc1101.setDRate(512);         // Set the Data Rate in kBaud. Value from 0.02 to 1621.83. Default is 99.97 kBaud!
  ELECHOUSE_cc1101.setRxBW(256);          // Set the Receive Bandwidth in kHz. Value from 58.03 to 812.50. Default is 812.50 kHz.
  ELECHOUSE_cc1101.setPktFormat(3);       // Format of RX and TX data. 0 = Normal mode, use FIFOs for RX and TX. 
                                          // 1 = Synchronous serial mode, Data in on GDO0 and data out on either of the GDOx pins. 
                                          // 2 = Random TX mode; sends random data using PN9 generator. Used for test. Works as normal mode, setting 0 (00), in RX. 
                                          // 3 = Asynchronous serial mode, Data in on GDO0 and data out on either of the GDOx pins.
}

void CCSetRx() {
  pinMode(CCGDO0,INPUT);  
  ELECHOUSE_cc1101.SetRx();
}


#define BAVGSIZE 11
byte bavg[BAVGSIZE];
byte pb = 0;
byte cres = 0;

byte CCAvgRead() {
  cres -= bavg[pb];
  bavg[pb] = digitalRead(CCGDO0);
  cres += bavg[pb];
  pb++;
  if (pb >= BAVGSIZE) pb = 0;
  if (cres > BAVGSIZE/2) return 1;
  return 0;
}

void CCWrite(int b) {
  digitalWrite(CCGDO0,b);
}
