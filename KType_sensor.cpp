#include "ext_var.h"

#define MISO 5
#define SCLK 6
#define CS1 4
#define CS2 7

float TEMP_DEG_RAW1=0,TEMP_DEG_RAW2=0,Final_Internal_Probe_Temp=0;
//----------------------------Kalman filter var--------------------------//
float  X_KType=25.00, P_KType=0.01, Q_KType=10, R_KType=200000, K_KType=0.001;
// float  X_KType=25.00, P_KType=0.01, Q_KType=80, R_KType=5000, K_KType=0.001;
float smoothed_KType_Temp=0;

byte spiread(void); 
float Selection_Of_Thermocouple(uint8_t ChipSelectionPin);

void READ_THERMOCOUPLE();
Ticker TEMP_READING(READ_THERMOCOUPLE, 1200, 0);

float K_Type_emaFilter_Output=0,Internal_Temp_Post_Calb=0;
float emaFilter(float input);
static float prev_output = 25.0f;
    // static unsigned long heaterOffTime = 0;
    // static int count = 0;
    // float alpha;
const float alpha = 0.001f; 
// Ticker TEMP_READING(READ_THERMOCOUPLE, 50, 0,MICROS_MICROS);

//************************************************Thermocouple***********************************************
//MAX6675 thermocouple(SCK_PIN, CS_PIN, SO_PIN);
//-----------------------------------------------------------------------------------------------------------
//*********************************************temp**********************************************
// float TEMP_DEG_RAW = 25.5, TEMP_DEG_RAW2, TEMP_DEG_RAW1;
// float TEMP_DEG = 25.5;
// bool SIGN=0;
//------------------------------------------------------------------------------------------------
KType_sensor_class::KType_sensor_class() // tickers_class tickers
{}

void KType_sensor_class::KType_setup()
{      

  // Serial.begin(9600);

  pinMode(MISO, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(CS1, OUTPUT);
  pinMode(CS2, OUTPUT);

  
  TEMP_READING.start();
 
}
void  KType_sensor_class::KType_Reading_Update()
{
  TEMP_READING.update();

}

float Selection_Of_Thermocouple(uint8_t ChipSelectionPin) //(uint8_t )
{
  uint16_t v;

  digitalWrite(ChipSelectionPin, LOW);
  delayMicroseconds(10);

  v = spiread();
  v <<= 8;
  v |= spiread();

  digitalWrite(ChipSelectionPin, HIGH);

  if (v & 0x4) 
  {
    // uh oh, no thermocouple attached!
//    return NAN;
     return -1;
  }

  v >>= 3;

  return v * 0.25;
   

}
 
void READ_THERMOCOUPLE()
{
    TEMP_DEG_RAW1  = Selection_Of_Thermocouple(CS1);   
    TEMP_DEG_RAW2  = Selection_Of_Thermocouple(CS2);

    //  Serial2.print("TEMP_DEG_RAW1 :");
    //  Serial2.println(TEMP_DEG_RAW1);

    //  Serial2.print("TEMP_DEG_RAW2 :");
    //  Serial2.println(TEMP_DEG_RAW2);

}

byte spiread(void) 
{
  int i;
  byte d = 0;

  for (i = 7; i >= 0; i--) 
  {
    digitalWrite(SCLK, LOW);
    delayMicroseconds(10);
    if (digitalRead(MISO))
    {
      // set the bit to 0 no matter what
      d |= (1 << i);
    }
    digitalWrite(SCLK, HIGH);
    delayMicroseconds(10);
  }
  return d;
}

// void KType_sensor_class::Internal_Probe_Temperature() //K-Type Reading
// {
  // if (TEMP_DEG_RAW1 != -1) 
  // {   
  //    Final_Internal_Probe_Temp=TEMP_DEG_RAW1;
  // } 
  // if (TEMP_DEG_RAW2 != -1) {
  //    Final_Internal_Probe_Temp=TEMP_DEG_RAW2;
  // } 
  // if((TEMP_DEG_RAW1 != -1) && (TEMP_DEG_RAW2 != -1)) //----------------If both K-Type are Connected
  // {
  //     Final_Internal_Probe_Temp=TEMP_DEG_RAW1;
  // }
  // if((TEMP_DEG_RAW1 == -1) && (TEMP_DEG_RAW2 == -1)) //----------Both k_type are not connected-Probe Error
  // {
  //     Final_Internal_Probe_Temp=-1;
  // }
 
// }
float kalmanFilter_KType(float measurement_KType) //------------Filter for K-Type Raw temp
{
  float X_pred_KType = X_KType;             // Predicted state estimate
  float P_pred_KType = P_KType + Q_KType;         // Predicted estimate error covariance

  // Update phase
  K_KType = P_pred_KType / (P_pred_KType + R_KType);    // Kalman gain
  X_KType = X_pred_KType + K_KType * (measurement_KType - X_pred_KType); // Updated state estimate
  P_KType = (1 - K_KType) * P_pred_KType;         // Updated estimate error covariance

  return X_KType;                     // Return the smoothed value
}

// void KType_Reading_after_KalmanFilter()
void KType_sensor_class::Internal_Probe_Temperature()
{    
        if (TEMP_DEG_RAW1 != -1) 
        {   
          Final_Internal_Probe_Temp=TEMP_DEG_RAW1;
        } 
        if (TEMP_DEG_RAW2 != -1) {
          Final_Internal_Probe_Temp=TEMP_DEG_RAW2;
        } 
        if((TEMP_DEG_RAW1 != -1) && (TEMP_DEG_RAW2 != -1)) //----------------If both K-Type are Connected
        {
            Final_Internal_Probe_Temp=TEMP_DEG_RAW1;
        }
        if((TEMP_DEG_RAW1 == -1) && (TEMP_DEG_RAW2 == -1)) //----------Both k_type are not connected-Probe Error
        {
            Final_Internal_Probe_Temp=-1;
        }
        K_Type_emaFilter_Output=emaFilter(Final_Internal_Probe_Temp); 
        smoothed_KType_Temp=kalmanFilter_KType(K_Type_emaFilter_Output);
}

// float emaFilter(float input, bool heaterOn) 
float emaFilter(float input) 
{
    
    // const unsigned long HOLD_DURATION_MS = 5000;  // Hold temp for 3 seconds after heater OFF

    // First-time dummy value
    // if (count < 200) {
    //     count++;
    //     prev_output = input;
    //     return 25.0f;  // Default startup display
    // }

    float filtered = (alpha * input) + ((1.0f - alpha) * prev_output);
    prev_output = filtered;
    return filtered;
}

KType_sensor_class KType_sensor = KType_sensor_class();  
