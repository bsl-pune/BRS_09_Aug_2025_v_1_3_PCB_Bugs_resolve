#ifndef ext_var_h
#define ext_var_h
#include "Arduino.h"
#include <EEPROM.h>
#include <OneButton.h> 
#include <SoftwareSerial.h>
#include "Ticker.h" 
#include "Encoder.h"
#include"RTD_Sensor.h"
#include "TimerUpdate.h"
#include "Process.h"
#include"ProbeDetection.h"
#include"DwinDisplay.h"
#include "tickers.h"
#include"KType_sensor.h"
#include"HeaterPID.h"
#include"AlertMsg.h"
#include"Motor.h"
#include <Wire.h> 
#include <PID_v1.h>

//-------------------------version-----------------------------------//
extern bool stopVerDisplay;
//------------------------External probe detection--------------------------//
extern bool PT100_1_Detection_Occured;
//---------------------------Long press variables-------------------------------//
extern int inc_time;
extern int chk_time;
//---------------R-Encoder extern var--------------------//
extern int inc2,accel,inc1,accel_Encoder2,inc2_Encoder2;
extern volatile int encoder0Pos;
extern bool ONCE_Inc;
//----------------------probe
extern int Internal_probe_short_open_counter,PT1000_Not_Detected_counter;
extern bool Probe_Error_Flag,PT1000_Not_Detected_Flag,once_det_read;
//--------------------extern set parameter/Inprocess variables------------------------------//
extern int mode,Enter_Button,Set_temp,Set_Hour,Set_Min,Set_time,Set_speed,A_speed,Overhead_stirrer_motor_PWM_Map,Stop_pwm,OHS_Set_speed,Internal_safety_cutoff;
extern int EEPROM_Hour,EEPROM_Min,EEPROM_Set_Temp,Inprocess_Set_Temp_Change,initial_temp_inc_check_count;
extern bool Exit_Process,countDownStart,Process_Start_Flag,once_heater_PID,InF_mode,initial_temp_inc_check_ONCE,SSR_Failure_Flag,Inprocess_check_flag_for_autoresume,SetPoint_for_Cal2;
extern double  Setpoint,Input, Output; 
extern bool PT100_1_Detection_Occured,PT1000_Detection_Occured,Motor_Stop_Flagg,SSR_fail_In_Cal2_flag;
extern float Smoothed_Probe1_Temp,TEMP_DEG_RAW1,TEMP_DEG_RAW2,Smoothed_PT1000_Temperature,Final_Internal_Probe_Temp,smoothed_KType_Temp,Initial_temp,K_Type_emaFilter_Output,Internal_Temp_Post_Calb,PT1000_TEMP_RAW;
extern long setMin,incrementTime; 
extern bool sendDataFlag, toggle,Overhead_Motor_connected_Flag, stop_motor_slowly_ONCE,Inprocess_Flag_stop_motor,Motor_stop_After_process_exit,Motor_stop_In_Recipe;
extern int Current_Min,Current_HOUR;
extern bool Inprocess_Set_RPM_show_flag,Motor_Stop_During_OHS_Interuption_Flag;
extern int Inprocess_page_change;
extern bool door_open_flag,Inprocess_Lamp_glow_flag,RPM_read,Soak_time_start_flag,Soak_time_Once,Inprocess_Set_Temp_Save,Int_Motor_Spd_control_flag;
extern double Final_set_temperature;
extern int old_dimetime,dimtime,ramp_val,change_ramp;
extern double Setpoint1, Input1, Output1;
extern int counter2 ,set_input_cmp_factor,WindowSize,WindowSize_slow;
extern long pulses ,Current_RPM1;
extern float  Probe1_X, Probe1_P, Probe1_Q, Probe1_R, Probe1_K;
extern float  PT1000_X, PT1000_P, PT1000_Q, PT1000_R, PT1000_K;
extern bool Receipe_Mode,Knob_Single_Press_In_Receipe_start;
extern int Receipe_Step,Receipe_Parameter,Receipe,Process_start_stop_Rcp_step,Receipe_Count;
extern int Receipe_Set_Temp[4][6],Receipe_Set_Hour[4][6], Receipe_Set_Min[4][6],Receipe_Set_RPM[4][6],RCP_EEPROM_Address[4][6];
extern unsigned long windowStartTime;

extern bool SSR_cuttoff_reached_Flag;
extern uint8_t SSR_cutoff_Reach_Count,SSR_Fail_check_Count;
// extern unsigned char Receipe_Address[2][5];
//-------------------------Setting menu-----------------------------------------//
extern bool Slow_Fast_Mode_Flag,Autoresume_Enable_Disable_Flag;
extern uint8_t Time_mode_Flag;
extern bool Knob_Single_Press_In_Settings;
extern int Setting_Menu,Safe_Menu_Count,Safe_Temp[3];
extern unsigned int Master_Pressure,Master_RPM,Safe_Temperature;
//---------------Calibration--------------------//
extern bool Inside_Calibration_menu,Calibration_selection_flag,Knob_Single_Press_In_Calibration1,Calibration_1_plus_minus_EEPROM;
extern int Calibration1_Value,Final_Error_Difference;
extern float Temperature_After_Calibration;
extern int Cal2_Selection_Parameter,CAL2_Low_Set_temp,CAL2_High_Set_temp,CAL2_Low_Master,CAL2_High_Master;
extern bool CAL2_maintain_flag,Single_Click_In_Cal2_maintain;

//-----------------------Key1 & key2 variables-----------------------------//
extern int Process_stop_by_key1;

class Vclass
{
  public :
  Vclass();
};

extern Vclass var;

#endif