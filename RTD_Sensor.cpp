#include "ext_var.h"
#define PT1000_Pin 24
#define PT100_probe_1 23
#define Address 0x36 //----I2C  address
#define Selection_pin  1//x60

RTD_Sensor_class::RTD_Sensor_class() {}

void PT100_Probe1_Temperature();
Ticker PT100_Probe1_Temperature_Reading(PT100_Probe1_Temperature, 100, 0);

//------------------PT1000 sensor ticker------------------------------//
void PT1000_External_Temperature();
Ticker PT1000_External_Temperature_Reading(PT1000_External_Temperature, 100, 0);

float  Probe1_X=25.00, Probe1_P=0.01, Probe1_Q=10, Probe1_R=200000, Probe1_K=0.001;
float Smoothed_Probe1_Temp=0;
float  PT1000_X=25.00, PT1000_P=0.01, PT1000_Q=10, PT1000_R=200000, PT1000_K=0.001;
float Smoothed_PT1000_Temperature=0;
//*********************************************temp**********************************************//
float Probe1_TEMP_DEG_RAW = 0.0, Probe2_TEMP_DEG_RAW = 0.0;
//------------------------------------------------------------------------------------------------
float R0 = 100.0;
float R1 = 4700.0;
float R2 = 100.0;
float R3 = 4700.0, Probe1_Vin = 0, Probe1_Rt = 0, Probe2_Vin = 0, Probe2_Rt = 0;
// float PT1000_R0 = 1000.0;
// float PT1000_R1 = 4700.0;
// float PT1000_R2 = 1000.0;
// float PT1000_R3 = 4700.0;
float PT1000_R0 = 1000.0;
float PT1000_R1 = 4700.0;
float PT1000_R2 = 1000.0;
float PT1000_R3 = 4700.0;
const int Vs = 5;
const float Alpha = 0.00385;
float Probe1_TotalVout = 0, Probe1_AvgVout = 0;
float Probe2_TotalVout = 0, Probe2_AvgVout = 0;
int Probe1_avrage_val = 150, Probe2_avrage_val = 150;
static int Probe1_sample = 0;
static int Probe2_sample = 0;

float PT1000_Vin = 0, PT1000_Rt = 0,PT1000_TEMP_RAW=0;
int Read_Array[2];

void RTD_Sensor_class::RTDSetup() 
{
  Wire.begin();    
  Wire.beginTransmission(Address);
  Wire.write(0x80);
  Wire.endTransmission();

  pinMode(PT100_probe_1, INPUT);
  pinMode(PT1000_Pin, INPUT);
  PT100_Probe1_Temperature_Reading.start();
  PT1000_External_Temperature_Reading.start();
  
}

float Probe1_kalmanFilter(float Probe1_measurement)
{
  float Probe1_X_pred = Probe1_X;             // Predicted state estimate
  float Probe1_P_pred = Probe1_P + Probe1_Q;         // Predicted estimate error covariance

  // Update phase
  Probe1_K = Probe1_P_pred / (Probe1_P_pred + Probe1_R);    // Kalman gain
  Probe1_X = Probe1_X_pred + Probe1_K * (Probe1_measurement - Probe1_X_pred); // Updated state estimate
  Probe1_P = (1 - Probe1_K) * Probe1_P_pred;         // Updated estimate error covariance

  return Probe1_X;                     // Return the smoothed value
}

void PT100_Probe1_Temperature()
{
      float Probe1_instant_val = analogRead(PT100_probe_1);
      float Probe1_Vout = ((Probe1_instant_val * Vs) / 1023.0);
      Probe1_Vin = Probe1_Vout / 10.47;
      Probe1_Rt = (R2 * R3 + R3 * (R1 + R2) * Probe1_Vin / Vs) / (R1 - (R1 + R2) * Probe1_Vin / Vs);
      Probe1_TEMP_DEG_RAW = ((Probe1_Rt / R0) - 1) / (Alpha);
      Smoothed_Probe1_Temp = Probe1_kalmanFilter(Probe1_TEMP_DEG_RAW);
      //  Serial2.print("Smoothed_Probe1_Temp :");
      // Serial2.println(Smoothed_Probe1_Temp); 
 
}

//---------------------PT1000(12 bit ADC)-----------------------------------//
float Read_12Bit_ADC(bool ADC_Channel_Selection)
{ 
  Wire.beginTransmission(Address);
  if(ADC_Channel_Selection)     Wire.write(0x61);  //Select_Probe  1 x61
  else                          Wire.write(0x63); 
  Wire.endTransmission();
  Wire.requestFrom(Address, 2); 
  while (Wire.available()==2)
  if(Wire.available()<=2)
  { 
    for(int j=0; j<2; j++){
      Read_Array[j] = Wire.read();           // receive a byte as character
    }
  }
  return  (( (Read_Array[0] & 15) <<8)| Read_Array[1]);
}
float PT1000_kalmanFilter(float PT1000_measurement)//-----------Filter for PT1000
{
  float PT1000_X_pred = PT1000_X;             // Predicted state estimate
  float PT1000_P_pred = PT1000_P + PT1000_Q;         // Predicted estimate error covariance
  // Update phase
  PT1000_K = PT1000_P_pred / (PT1000_P_pred + PT1000_R);    // Kalman gain
  PT1000_X = PT1000_X_pred + PT1000_K * (PT1000_measurement - PT1000_X_pred); // Updated state estimate
  PT1000_P = (1 - PT1000_K) * PT1000_P_pred;         // Updated estimate error covariance
  return PT1000_X;      // Return the PT1000 smoothed value
}
void PT1000_External_Temperature()
{
      float PT1000_instant_val = Read_12Bit_ADC(Selection_pin);
      float PT1000_Vout = ((PT1000_instant_val * Vs) / 4096.0);
      // PT1000_Vin = PT1000_Vout / 10.47;
      PT1000_Vin = PT1000_Vout / 5.1;
      PT1000_Rt = (PT1000_R2 * PT1000_R3 + PT1000_R3 * (PT1000_R1 + PT1000_R2) * PT1000_Vin / Vs) / (PT1000_R1 - (PT1000_R1 + PT1000_R2) * PT1000_Vin / Vs);
      PT1000_TEMP_RAW = ((PT1000_Rt / PT1000_R0) - 1) / (Alpha);
      Smoothed_PT1000_Temperature = PT1000_kalmanFilter(PT1000_TEMP_RAW); 
      //  Serial2.print("PT1000_TEMP_RAW :");
      // Serial2.println(PT1000_TEMP_RAW);
 
}
void RTD_Sensor_class :: PT1000_Temperature_Reading_update() //-------------PT1000 ticker update function
{
  PT1000_External_Temperature_Reading.update();
}


void RTD_Sensor_class :: PT100_Probe1_Temperature_Reading_update()//----------PT100 ticker update
{
  PT100_Probe1_Temperature_Reading.update();
}


RTD_Sensor_class RTD_Sensor = RTD_Sensor_class();