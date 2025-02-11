//This code belongs to the ADS1256 library developed by Curious Scientist
//A very detailed documentation can be found at: https://curiousscientist.tech/ads1256-custom-library 

#include <ADS1256.h>

//Below a few examples of pin descriptions for different microcontrollers I used:
ADS1256 A(2.5, 25, 26, 23, 33, 32); //VREF, DRDY, CS, SCK, MISO, MOSI.

long rawConversion = 0; //24-bit raw value
float voltageValue = 0; //human-readable floating point value

int singleEndedChannels[8] = {SING_0, SING_1, SING_2, SING_3, SING_4, SING_5, SING_6, SING_7}; //Array to store the single-ended channels
int differentialChannels[4] = {DIFF_0_1, DIFF_2_3, DIFF_4_5, DIFF_6_7}; //Array to store the differential channels
int inputChannel = 0; //Number used to pick the channel from the above two arrays
char inputMode = ' '; //can be 's' and 'd': single-ended and differential

int pgaValues[7] = {PGA_1, PGA_2, PGA_4, PGA_8, PGA_16, PGA_32, PGA_64}; //Array to store the PGA settings
int pgaSelection = 0; //Number used to pick the PGA value from the above array

int drateValues[16] =
{
  DRATE_30000SPS,
  DRATE_15000SPS,
  DRATE_7500SPS,
  DRATE_3750SPS,
  DRATE_2000SPS,
  DRATE_1000SPS,
  DRATE_500SPS,
  DRATE_100SPS,
  DRATE_60SPS,
  DRATE_50SPS,
  DRATE_30SPS,
  DRATE_25SPS,
  DRATE_15SPS,
  DRATE_10SPS,
  DRATE_5SPS,
  DRATE_2SPS
}; //Array to store the sampling rates

int drateSelection = 0; //Number used to pick the sampling rate from the above array

String registers[11] =
{
  "STATUS",
  "MUX",
  "ADCON",
  "DRATE",
  "IO",
  "OFC0",
  "OFC1",
  "OFC2",
  "FSC0",
  "FSC1",
  "FSC2"
};//Array to store the registers

int registerToRead = 0; //Register number to be read
int registerToWrite = 0; //Register number to be written
int registerValueToWrite = 0; //Value to be written in the selected register

void setup()
{
  Serial.begin(115200); //The value does not matter if you use an MCU with native USB

  while (!Serial)
  {
    ; //Wait until the serial becomes available
  }

  Serial.println("ADS1256 - Custom Library Demo File by Curious Scientist - 2023-11-10");

  A.InitSPI(7.68);
  A.InitializeADC(DRATE_2000SPS, 0x06, false);
}

void loop()
{
  float data[4];
  float result[4] = {0,0,0,0};

  for(int i = 0 ; i < 1000 ; i++) {
    data[0] = A.readCurrentChannel(DIFF_0_1);
    result[0] += data[0];
  }
  result[0] = result[0] / 1000;
  Serial.print("Differential 1 : ");
  Serial.print(result[0] * 200000.0,8);

  for(int i = 0 ; i < 1000 ; i++) {
    data[1] = A.readCurrentChannel(DIFF_2_3);
    result[1] += data[1];
  }
  result[1] = result[1] / 1000;
  Serial.print("  |   Differential 2 : ");
  Serial.print(result[1]*20000.0 - 10.0,8);

  for(int i = 0 ; i < 1000 ; i++) {
    data[2] = A.readCurrentChannel(DIFF_4_5);
    result[2] += data[2];
  }
  result[2] = result[2] / 1000;
  Serial.print("  |  Differential 3 : ");
  Serial.print(result[2]*20000.0 - 10,8);

  for(int i = 0 ; i < 1000 ; i++) {
    data[3] = A.readCurrentChannel(DIFF_6_7);
    result[3] += data[3];
  }
  result[3] = result[3] / 1000;
  Serial.print("  |  Differential 4 : ");
  Serial.println(result[3] * 20000.0 - 10,8);
  delay(500);
}
