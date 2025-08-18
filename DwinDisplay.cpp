#include "ext_var.h"

#define set_temp_address 0x41
#define probe_temp_address 0x42
#define Set_RPM_address 0x43
#define Set_Hour_address 0x44
#define Set_Minute_address 0x45
#define UV_Lamp_address 0x46
#define BLDC_Current_RPM_address 0x47
#define Inprocess_temp_address 0x48
#define Save_Temp_address 0x50
#define Save_HH_address 0x51
#define Save_Min_address 0x52
#define Inprocess_UV_Lamp_address 0x49
#define Time_Graph_address 0x96
//------------------------------Setting menu-------------------------------//
#define Internal_Safe_Temp_Address 0x53
#define External_Safe_Temp_Address  0x91
#define Vapour_Safe_Temp_Address  0x92

#define Pressure_Calb_Address 0x54
#define RPM_Calb_Address 0x55
#define RPM_Calb_Current_Address 0x94

#define Cal1_Master_Temp_Address 0x80
#define Cal1_Current_Temp_Address 0x81
#define Cal2_Low_Set_Temp_Address 0x84
#define Cal2_High_Set_Temp_Address 0x85
#define Cal2_Current_Temp_Address 0x86
#define Cal2_RPM_Address 0x87
#define Cal2_Hour_Address 0x88
#define Cal2_Min_Address 0x89
#define Cal2_Master_Temp_Address 0x90
#define Cal2_LoW_High_Set_Temp_Address 0x98

#define Receipe_Address 0x95

#define Receipe_Set_Temp_Step0_Address 0x56
#define Receipe_Set_RPM_Step0_Address 0x57
#define Receipe_Set_Hour_Step0_Address 0x58
#define Receipe_Set_Min_Step0_Address 0x59

#define Receipe_Set_Temp_Step1_Address 0x60
#define Receipe_Set_RPM_Step1_Address 0x61
#define Receipe_Set_Hour_Step1_Address 0x62
#define Receipe_Set_Min_Step1_Address 0x63

//----------step2
#define Receipe_Set_Temp_Step2_Address 0x64
#define Receipe_Set_RPM_Step2_Address 0x65
#define Receipe_Set_Hour_Step2_Address 0x66
#define Receipe_Set_Min_Step2_Address 0x67

//----------step3
#define Receipe_Set_Temp_Step3_Address 0x68
#define Receipe_Set_RPM_Step3_Address 0x69
#define Receipe_Set_Hour_Step3_Address 0x70
#define Receipe_Set_Min_Step3_Address 0x71
//----------step4
#define Receipe_Set_Temp_Step4_Address 0x72
#define Receipe_Set_RPM_Step4_Address 0x73
#define Receipe_Set_Hour_Step4_Address 0x74
#define Receipe_Set_Min_Step4_Address 0x75
//----------step5
#define Receipe_Set_Temp_Step5_Address 0x76
#define Receipe_Set_RPM_Step5_Address 0x77
#define Receipe_Set_Hour_Step5_Address 0x78
#define Receipe_Set_Min_Step5_Address 0x79

// unsigned char Receipe_Address[2][5]={ 
//                                       {0x00,0x56,0x57,0x58,0x59},{0x00,0x60,0x61,0x62,0x63}
//                                     };

unsigned char   Set_Temperature[8] = {0x5A, 0xA5, 0x05, 0x82, set_temp_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};   
unsigned char   Probe_current_temp1[8] = {0x5A, 0xA5, 0x05, 0x82, probe_temp_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};   
unsigned char   Set_RPM[8] = {0x5A, 0xA5, 0x05, 0x82, Set_RPM_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   BLDC_Current_RPM[8] = {0x5A, 0xA5, 0x05, 0x82,BLDC_Current_RPM_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};    
unsigned char   Set_Hour_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Set_Hour_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};   
unsigned char   Set_Minute_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Set_Minute_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};   
unsigned char   UV_Lamp_Intensity[8] = {0x5A, 0xA5, 0x05, 0x82, UV_Lamp_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Inprocess_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Inprocess_temp_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Save_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Save_Temp_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Save_HH_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Save_HH_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Save_Min_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Save_Min_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Inprocess_UV_Lamp_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Inprocess_UV_Lamp_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 
unsigned char   Temp_Graph[18] = {0x5A , 0xA5 , 0x13 , 0x82 , 0x03 , 0x10 , 0x5A , 0xA5 , 0x02 , 0x00 , 0x00 , 0x01 , 0x00, 0x00 , 0x01 , 0x01 , 0x00 , 0x00};
unsigned char   Time_Graph_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Time_Graph_address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 

//-------------------------Setting menu--------------------------------------//
unsigned char   Internal_SAFE_TEMP_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Internal_Safe_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 
unsigned char   External_SAFE_TEMP_arr[8] = {0x5A, 0xA5, 0x05, 0x82, External_Safe_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 
unsigned char   Vapour_SAFE_TEMP_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Vapour_Safe_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 

unsigned char   Pressure_Calb_arr[8] = {0x5A, 0xA5, 0x05, 0x82, Pressure_Calb_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 
unsigned char   RPM_Calb_arr[8] = {0x5A, 0xA5, 0x05, 0x82, RPM_Calb_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 
unsigned char   RPM_Calb_current_arr[8] = {0x5A, 0xA5, 0x05, 0x82, RPM_Calb_Current_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 

unsigned char   Cal1_Master_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal1_Master_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 
unsigned char   Cal1_Current_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal1_Current_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; 

unsigned char   Cal2_Low_Set_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal2_Low_Set_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Cal2_High_Set_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal2_High_Set_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};

unsigned char   Cal2_Current_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal2_Current_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Cal2_RPM_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal2_RPM_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Cal2_Hour_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal2_Hour_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Cal2_Min_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal2_Min_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Cal2_Master_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82,  Cal2_Master_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
unsigned char   Cal2_LoW_High_Set_Temp_arr[8] = {0x5A, 0xA5, 0x05, 0x82,   Cal2_LoW_High_Set_Temp_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
//-------------------------Receipe-------------------------------------------//
unsigned char   Receipe_Set_Temp_Step0[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Temp_Step0_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_RPM_Step0[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_RPM_Step0_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Hour_Step0[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Hour_Step0_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Min_Step0[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Min_Step0_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  

unsigned char   Receipe_Set_Temp_Step1[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Temp_Step1_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_RPM_Step1[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_RPM_Step1_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Hour_Step1[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Hour_Step1_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Min_Step1[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Min_Step1_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};

unsigned char   Receipe_Set_Temp_Step2[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Temp_Step2_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_RPM_Step2[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_RPM_Step2_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Hour_Step2[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Hour_Step2_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Min_Step2[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Min_Step2_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
//--step3
unsigned char   Receipe_Set_Temp_Step3[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Temp_Step3_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_RPM_Step3[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_RPM_Step3_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Hour_Step3[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Hour_Step3_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Min_Step3[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Min_Step3_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
//--step4
unsigned char   Receipe_Set_Temp_Step4[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Temp_Step4_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_RPM_Step4[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_RPM_Step4_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Hour_Step4[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Hour_Step4_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Min_Step4[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Min_Step4_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};
//--step5
unsigned char   Receipe_Set_Temp_Step5[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Temp_Step5_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_RPM_Step5[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_RPM_Step5_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Hour_Step5[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Hour_Step5_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};  
unsigned char   Receipe_Set_Min_Step5[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Set_Min_Step5_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};

unsigned char   Receipe_Cunt[8] = {0x5A, 0xA5, 0x05, 0x82, Receipe_Address , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/};

// unsigned char   Receipe_Set_Temp_Step1[8] = {0x5A, 0xA5, 0x05, 0x82, 0x56 , 0x00, 0x00/*High Byte*/, 0x00/*Low Byte*/}; //Receipe_Address[Receipe_Step][Enter_Button]


DwinDisplay_class::DwinDisplay_class()
{}

void DwinDisplay_class :: Data_Arduino_to_Display_Current_Temp(float current_temp) 
{  
  int Probe_current_temp = current_temp * 10;
  Probe_current_temp1[6] = highByte(Probe_current_temp);
  Probe_current_temp1[7] = lowByte(Probe_current_temp);
  Serial.write(Probe_current_temp1, 8);

}

void DwinDisplay_class :: Data_Arduino_to_Display_for_set(int temp_set) 
{  
   int t1 = temp_set;
   Set_Temperature[6] = highByte(t1);
   Set_Temperature[7] = lowByte(t1);
   Serial.write(Set_Temperature, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_for_set_RPM(int RPM_set) 
{  
   int R1 = RPM_set;
  Set_RPM[6] = highByte(R1);
  Set_RPM[7] = lowByte(R1);
  Serial.write(Set_RPM, 8);
}

void DwinDisplay_class :: Data_Arduino_to_Display_Inprocess_Current_RPM(int Current_RPM ) 
{  
   int CR1=Current_RPM;
  BLDC_Current_RPM[6] = highByte(CR1);
  BLDC_Current_RPM[7] = lowByte(CR1);
  Serial.write(BLDC_Current_RPM, 8);
}

void DwinDisplay_class :: Data_Arduino_to_Display_set_Hour(int Hour_set)
{
  int H1 = Hour_set;
  Set_Hour_arr[7] = lowByte(H1);
  Serial.write(Set_Hour_arr, 8);
}

void DwinDisplay_class :: Inprocess_hour() 
{
  int IH = Current_HOUR;
  Set_Hour_arr[7] = lowByte(IH);
  Serial.write(Set_Hour_arr, 8);
}

void DwinDisplay_class :: Data_Arduino_to_Display_set_Min(int Min_set) 
{
  int M1 = Min_set;
  Set_Minute_arr[7] = lowByte(M1);
  Serial.write(Set_Minute_arr, 8);
}

void DwinDisplay_class :: Inprocess_Min() 
{
  int IM = Current_Min;
  Set_Minute_arr[7] = lowByte(IM);
  Serial.write(Set_Minute_arr, 8);
}

void DwinDisplay_class :: Inprocess_Temperature(float Inprocess_Temp) 
{
  int I_Temp = Inprocess_Temp* 10;
  Inprocess_Temp_arr[6] = highByte(I_Temp);
  Inprocess_Temp_arr[7] = lowByte(I_Temp);
  Serial.write(Inprocess_Temp_arr, 8);
  
}
void DwinDisplay_class :: Save_Temperature(float Save_Temp) 
{
  int S_Temp = Save_Temp;
  Save_Temp_arr[6] = highByte(S_Temp);
  Save_Temp_arr[7] = lowByte(S_Temp);
  Serial.write(Save_Temp_arr, 8);
  
}
void DwinDisplay_class :: Save_hour(int Save_Hour) 
{
  int SH = Save_Hour;
  Save_HH_arr[7] = lowByte(SH);
  Serial.write(Save_HH_arr, 8);
 
}
void DwinDisplay_class :: Save_Min(int Save_Min) 
{
  int SM = Save_Min;
  Save_Min_arr[7] = lowByte(SM);
  Serial.write(Save_Min_arr, 8);
}

void DwinDisplay_class :: Data_controller_to_Display_Vapour_Temp(float Vapour_Temp ) 
{
  int SUV =Vapour_Temp*10;
  UV_Lamp_Intensity[6] = highByte(SUV);
  UV_Lamp_Intensity[7] = lowByte(SUV);
  Serial.write(UV_Lamp_Intensity, 8);
  
}
void DwinDisplay_class :: Data_controller_to_Display_Inprocess_Vapour_Temp(float Process_Vapour_Temp) 
{
  int IUV = Process_Vapour_Temp*10;
  Inprocess_UV_Lamp_arr[6] = highByte(IUV);
  Inprocess_UV_Lamp_arr[7] = lowByte(IUV);
  Serial.write(Inprocess_UV_Lamp_arr, 8);
  
}

void DwinDisplay_class:: Data_to_Display_graph(float temp_curve) 
{

  int Current_temp_curve = static_cast<int>(temp_curve);
  Temp_Graph[12] = highByte(Current_temp_curve);
  Temp_Graph[13] = lowByte(Current_temp_curve);

  int Set_temp_curve = Final_set_temperature;
  //   Serial2.print(" SET_TEMP_DEG : "); Serial2.println(SET_TEMP_DEG);
  Temp_Graph[16] = highByte(Set_temp_curve);
  Temp_Graph[17] = lowByte(Set_temp_curve);

  Serial.write(Temp_Graph, 18);
}
void DwinDisplay_class :: Data_to_Display_Time_graph(int Time_Graph)
{
 
  int Inprocess_Grph_time = Time_Graph;
  Time_Graph_arr[6] = highByte(Inprocess_Grph_time);
  Time_Graph_arr[7] = lowByte(Inprocess_Grph_time);
  Serial.write(Time_Graph_arr, 8);

}

//------------------------------Setting menu display--------------------------------------------------//
void DwinDisplay_class :: Data_Arduino_to_Display_Internal_SAFE_TEMP(int Internal_Safe_Temperature) //---------------Safe temperature(Set)
{  
  //  int Safe1 = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  Internal_SAFE_TEMP_arr[6] = highByte(Internal_Safe_Temperature);
  Internal_SAFE_TEMP_arr[7] = lowByte(Internal_Safe_Temperature);
  Serial.write(Internal_SAFE_TEMP_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_External_SAFE_TEMP(int External_Safe_Temperature) //---------------Safe temperature(Set)
{  

  External_SAFE_TEMP_arr[6] = highByte(External_Safe_Temperature);
  External_SAFE_TEMP_arr[7] = lowByte(External_Safe_Temperature);
  Serial.write(External_SAFE_TEMP_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Vapour_SAFE_TEMP(int Vapour_Safe_Temperature) //---------------Safe temperature(Set)
{  

  Vapour_SAFE_TEMP_arr[6] = highByte(Vapour_Safe_Temperature);
  Vapour_SAFE_TEMP_arr[7] = lowByte(Vapour_Safe_Temperature);
  Serial.write(Vapour_SAFE_TEMP_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Pressure_Calb(int Pressure_Calb_for_display) //-----------Pressure calibration
{  
  //  int Pres = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  Pressure_Calb_arr[6] = highByte(Pressure_Calb_for_display);
  Pressure_Calb_arr[7] = lowByte(Pressure_Calb_for_display);
  Serial.write(Pressure_Calb_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_RPM_Calb(int RPM_Calb_for_display) //-----------RPM calibration
{  
  //  int Pres = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  RPM_Calb_arr[6] = highByte(RPM_Calb_for_display);
  RPM_Calb_arr[7] = lowByte(RPM_Calb_for_display);
  Serial.write(RPM_Calb_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_RPM_Calb_current(int RPM_Calb_current_for_display) //-----------RPM calibration
{  
  //  int Pres = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  RPM_Calb_current_arr[6] = highByte(RPM_Calb_current_for_display);
  RPM_Calb_current_arr[7] = lowByte(RPM_Calb_current_for_display);
  Serial.write(RPM_Calb_current_arr, 8);
}
//-------------------------------Calibration (single/double point)---------------------------------------------------//
void DwinDisplay_class :: Data_Arduino_to_Display_Cal1_Master_Temp(int Cal1_Master_Temp) //----------
{  
  Cal1_Master_Temp_arr[6] = highByte(Cal1_Master_Temp);
  Cal1_Master_Temp_arr[7] = lowByte(Cal1_Master_Temp);
  Serial.write(Cal1_Master_Temp_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Cal1_Current_Temp(float Cal1_Current_Temp) //-----------
{  
  int  Cal1_Current= Cal1_Current_Temp*10;
  Cal1_Current_Temp_arr[6] = highByte(Cal1_Current);
  Cal1_Current_Temp_arr[7] = lowByte(Cal1_Current);
  Serial.write(Cal1_Current_Temp_arr, 8);
}

void DwinDisplay_class :: Data_Arduino_to_Display_Cal2_Low_Set_Temp(int Cal2_Low_Set_Temp) //----------
{  
  int Cal2_Low_Temp=Cal2_Low_Set_Temp*10;
  Cal2_Low_Set_Temp_arr[6] = highByte(Cal2_Low_Temp);
  Cal2_Low_Set_Temp_arr[7] = lowByte(Cal2_Low_Temp);
  Serial.write(Cal2_Low_Set_Temp_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Cal2_High_Set_Temp(int Cal2_High_Set_Temp) //----------
{  
  int Cal2_High_Temp=Cal2_High_Set_Temp*10;
  Cal2_High_Set_Temp_arr[6] = highByte(Cal2_High_Temp);
  Cal2_High_Set_Temp_arr[7] = lowByte(Cal2_High_Temp);
  Serial.write(Cal2_High_Set_Temp_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Cal2_Current_Temp(float Cal2_Current_Temp) //----------
{  
  int Current_Temp_Cal2=Cal2_Current_Temp*10;
  Cal2_Current_Temp_arr[6] = highByte(Current_Temp_Cal2);
  Cal2_Current_Temp_arr[7] = lowByte(Current_Temp_Cal2);
  Serial.write(Cal2_Current_Temp_arr, 8);
}

void DwinDisplay_class :: Data_Arduino_to_Display_Cal2_Set_Temp_Heating(int Cal2_Heating) //----------
{  
  int Cal2_Set_Temp_Heating=Cal2_Heating;
  Cal2_LoW_High_Set_Temp_arr[6] = highByte(Cal2_Set_Temp_Heating);
  Cal2_LoW_High_Set_Temp_arr[7] = lowByte(Cal2_Set_Temp_Heating);
  Serial.write(Cal2_LoW_High_Set_Temp_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Cal2_RPM(int Cal2_RPM) //----------
{  
  Cal2_RPM_arr[6] = highByte(Cal2_RPM);
  Cal2_RPM_arr[7] = lowByte(Cal2_RPM);
  Serial.write(Cal2_RPM_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Cal2_Hour(int Cal2_Hour) //----------
{  
  Cal2_Hour_arr[6] = highByte(Cal2_Hour);
  Cal2_Hour_arr[7] = lowByte(Cal2_Hour);
  Serial.write(Cal2_Hour_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Cal2_Min(int Cal2_Min) //----------
{  
  Cal2_Min_arr[6] = highByte(Cal2_Min);
  Cal2_Min_arr[7] = lowByte(Cal2_Min);
  Serial.write(Cal2_Min_arr, 8);
}
void DwinDisplay_class :: Data_Arduino_to_Display_Cal2_Master_Temp(int Cal2_master_Temp) //----------
{  
  Cal2_Master_Temp_arr[6] = highByte(Cal2_master_Temp);
  Cal2_Master_Temp_arr[7] = lowByte(Cal2_master_Temp);
  Serial.write(Cal2_Master_Temp_arr, 8);
}


//-------------------------------Receipe ---------------------------------------------------//
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Temp_Step0(int Step0_Set_Temp) 
{  
  /*------Send Data to Display------*/
  Receipe_Set_Temp_Step0[6] = highByte(Step0_Set_Temp);
  Receipe_Set_Temp_Step0[7] = lowByte(Step0_Set_Temp);
  Serial.write(Receipe_Set_Temp_Step0, 8);
}

void DwinDisplay_class :: Data_to_Display_Receipe_Set_RPM_Step0(int Step0_Set_RPM) //---
{  
 
  Receipe_Set_RPM_Step0[6] = highByte(Step0_Set_RPM);
  Receipe_Set_RPM_Step0[7] = lowByte(Step0_Set_RPM);
  Serial.write(Receipe_Set_RPM_Step0, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Hour_Step0(int Step0_Set_Hour)
{
  Receipe_Set_Hour_Step0[7] = lowByte(Step0_Set_Hour);
  Serial.write(Receipe_Set_Hour_Step0, 8);
 
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Min_Step0(int Step0_Set_Min) 
{
  Receipe_Set_Min_Step0[7] = lowByte(Step0_Set_Min);
  Serial.write(Receipe_Set_Min_Step0, 8);
 
}
//---------Recipe step1
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Temp_Step1(int Step1_Set_Temp) //----------
{  
  //  int Pres = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  Receipe_Set_Temp_Step1[6] = highByte(Step1_Set_Temp);
  Receipe_Set_Temp_Step1[7] = lowByte(Step1_Set_Temp);
  Serial.write(Receipe_Set_Temp_Step1, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_RPM_Step1(int Step1_Set_RPM) //------
{   
  Receipe_Set_RPM_Step1[6] = highByte(Step1_Set_RPM);
  Receipe_Set_RPM_Step1[7] = lowByte(Step1_Set_RPM);
  Serial.write(Receipe_Set_RPM_Step1, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Hour_Step1(int Step1_Set_Hour)
{
  Receipe_Set_Hour_Step1[7] = lowByte(Step1_Set_Hour);
  Serial.write(Receipe_Set_Hour_Step1, 8);
 
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Min_Step1(int Step1_Set_Min) 
{
  Receipe_Set_Min_Step1[7] = lowByte(Step1_Set_Min);
  Serial.write(Receipe_Set_Min_Step1, 8);
 
}

//----------------------Recipe step2
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Temp_Step2(int Step2_Set_Temp) //----------
{  
  //  int Pres = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  Receipe_Set_Temp_Step2[6] = highByte(Step2_Set_Temp);
  Receipe_Set_Temp_Step2[7] = lowByte(Step2_Set_Temp);
  Serial.write(Receipe_Set_Temp_Step2, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_RPM_Step2(int Step2_Set_RPM) //------
{   
  Receipe_Set_RPM_Step2[6] = highByte(Step2_Set_RPM);
  Receipe_Set_RPM_Step2[7] = lowByte(Step2_Set_RPM);
  Serial.write(Receipe_Set_RPM_Step2, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Hour_Step2(int Step2_Set_Hour)
{
  Receipe_Set_Hour_Step2[7] = lowByte(Step2_Set_Hour);
  Serial.write(Receipe_Set_Hour_Step2, 8);
 
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Min_Step2(int Step2_Set_Min) 
{
  Receipe_Set_Min_Step2[7] = lowByte(Step2_Set_Min);
  Serial.write(Receipe_Set_Min_Step2, 8);
 
}
//----------------------Recipe step3
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Temp_Step3(int Step3_Set_Temp) //----------
{  
  //  int Pres = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  Receipe_Set_Temp_Step3[6] = highByte(Step3_Set_Temp);
  Receipe_Set_Temp_Step3[7] = lowByte(Step3_Set_Temp);
  Serial.write(Receipe_Set_Temp_Step3, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_RPM_Step3(int Step3_Set_RPM) //------
{   
  Receipe_Set_RPM_Step3[6] = highByte(Step3_Set_RPM);
  Receipe_Set_RPM_Step3[7] = lowByte(Step3_Set_RPM);
  Serial.write(Receipe_Set_RPM_Step3, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Hour_Step3(int Step3_Set_Hour)
{
  Receipe_Set_Hour_Step3[7] = lowByte(Step3_Set_Hour);
  Serial.write(Receipe_Set_Hour_Step3, 8);
 
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Min_Step3(int Step3_Set_Min) 
{
  Receipe_Set_Min_Step3[7] = lowByte(Step3_Set_Min);
  Serial.write(Receipe_Set_Min_Step3, 8);
 
}

//----------------------Recipe step4
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Temp_Step4(int Step4_Set_Temp) //----------
{  
  //  int Pres = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  Receipe_Set_Temp_Step4[6] = highByte(Step4_Set_Temp);
  Receipe_Set_Temp_Step4[7] = lowByte(Step4_Set_Temp);
  Serial.write(Receipe_Set_Temp_Step4, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_RPM_Step4(int Step4_Set_RPM) //------
{   
  Receipe_Set_RPM_Step4[6] = highByte(Step4_Set_RPM);
  Receipe_Set_RPM_Step4[7] = lowByte(Step4_Set_RPM);
  Serial.write(Receipe_Set_RPM_Step4, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Hour_Step4(int Step4_Set_Hour)
{
  Receipe_Set_Hour_Step4[7] = lowByte(Step4_Set_Hour);
  Serial.write(Receipe_Set_Hour_Step4, 8);
 
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Min_Step4(int Step4_Set_Min) 
{
  Receipe_Set_Min_Step4[7] = lowByte(Step4_Set_Min);
  Serial.write(Receipe_Set_Min_Step4, 8);
 
}
//----------------------Recipe step5
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Temp_Step5(int Step5_Set_Temp) //----------
{  
  //  int Pres = Safe_Temperature_for_display;
  /*------Send Data to Display------*/
  Receipe_Set_Temp_Step5[6] = highByte(Step5_Set_Temp);
  Receipe_Set_Temp_Step5[7] = lowByte(Step5_Set_Temp);
  Serial.write(Receipe_Set_Temp_Step5, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_RPM_Step5(int Step5_Set_RPM) //------
{   
  Receipe_Set_RPM_Step5[6] = highByte(Step5_Set_RPM);
  Receipe_Set_RPM_Step5[7] = lowByte(Step5_Set_RPM);
  Serial.write(Receipe_Set_RPM_Step5, 8);
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Hour_Step5(int Step5_Set_Hour)
{
  Receipe_Set_Hour_Step5[7] = lowByte(Step5_Set_Hour);
  Serial.write(Receipe_Set_Hour_Step5, 8);
 
}
void DwinDisplay_class :: Data_to_Display_Receipe_Set_Min_Step5(int Step5_Set_Min) 
{
  Receipe_Set_Min_Step5[7] = lowByte(Step5_Set_Min);
  Serial.write(Receipe_Set_Min_Step5, 8);
 
}

void DwinDisplay_class :: Data_to_Display_Receipe(int Rcp_count) 
{
  Receipe_Cunt[7] = lowByte(Rcp_count);
  Serial.write(Receipe_Cunt, 8);
 
}


void DwinDisplay_class::setPage(int page)
{
  if (!sendDataFlag) 
  {
    byte sendBuffer[] = {0x5A, 0xA5, 0x07, 0x82, 0x00, 0x84, 0x5A, 0x01, 0x00, static_cast<byte>(page)};
    Serial.write(sendBuffer, sizeof(sendBuffer));
      //  Serial.println("DWIN Data Sent! \n\n");
      //   Serial.print("page :");
      //   Serial.println(page);
      //   Serial.println("******************************");
    sendDataFlag = 1; // Set the flag to true after executing sendData
  }
}


DwinDisplay_class DwinDisplay = DwinDisplay_class();