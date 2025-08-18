//*******************************************Tickers****************************************************//
#include "ext_var.h"

tickers_class::tickers_class() // tickers_class tickers
{}

//-------------------------------------------Buzzer----------------------------------------------------------//
void STOP_BUZZER();
Ticker BUZZ(STOP_BUZZER, 100, 1);

void tickers_class :: BUZZ_INTERVAL(int i)
{
  BUZZ.interval(i);
  digitalWrite(BUZZER, HIGH);
  BUZZ.start();
}

void STOP_BUZZER()
{
  BUZZ.stop();
  digitalWrite(BUZZER, LOW);  
}

//---------------------------------Software Version display ticker-------------------------------------------------//
void VerDisp();
Ticker VersionDisplay(VerDisp, 4000, 1);
void VerDisp()
{ 
  stopVerDisplay=0;//------------------------------Version Display Stop Flag off
  sendDataFlag=0;
  if(Probe_Error_Flag==0 && PT1000_Not_Detected_Flag==0)
       mode=1;
  
  
}
//------------------------------7 second long press ticker------------------------------------------------//
void LongPress7sec_fun();
Ticker LongPress7sec_ticker(LongPress7sec_fun, 900, 0);
void LongPress7sec_fun()
{
  if(chk_time == 1)
  {
    inc_time ++;
 
  }
} 
//-----------------------------Fast Increment/Decrement Temp,Time while set------------------------------------//
void Fast_Inc_Dec();
Ticker Fast_Inc_Dec_ticker(Fast_Inc_Dec, 25, 0);
void Fast_Inc_Dec()
{
  if(accel || accel_Encoder2) 
  {
    inc1++;  
    if(inc1 > 8) 
    {
      inc1 = inc2 = accel =inc2_Encoder2=accel_Encoder2 = 0;
    }
  }
}
//---------------------------------Display toggle ticker-----------------------------------------------//
void toggle_fun();
Ticker toggle_ticker(toggle_fun, 500, 0, MILLIS);  //Time_speed_show_toggle
void toggle_fun()
{  

  toggle == 0 ? toggle = 1 : toggle = 0;

}

//--------------------------------Process stop by clicking key1 ticker-------------------------------------------------//
void Process_stop_by_key1_func();
Ticker Process_stop_by_key1_ticker(Process_stop_by_key1_func, 5000, 1);
void Process_stop_by_key1_func()
{  
   sendDataFlag=0;
   Inprocess_page_change==1;
   Inprocess_Lamp_glow_flag=1;
   Process_stop_by_key1=0;
}

//--------------------------------In process Set RPM Inc/Dec show ticker--------------------------------------------------//
void In_process_Set_RPM_show();
Ticker In_process_Set_RPM_show_ticker(In_process_Set_RPM_show, 4000, 1);
void In_process_Set_RPM_show()
{ 
  sendDataFlag=0; 
  Inprocess_Set_RPM_show_flag=0;
  // tickers.Time_Speed_toggle_ticker_start();         
} 
//------------------------------7 second long press ticker------------------------------------------------//
void Inprocess_Lamp_glow();
Ticker Inprocess_Lamp_glow_ticker(Inprocess_Lamp_glow, 2500, 1);
void Inprocess_Lamp_glow()
{ 
  sendDataFlag=0; 
  Inprocess_Lamp_glow_flag=1;
} 

//-------------------Internal probe short/open check filter---------------------------------//
void Internal_probe_short_open();
Ticker Internal_probe_short_open_ticker(Internal_probe_short_open, 5000, 0);
void Internal_probe_short_open()
{ 
    //------------short condition----------------------------------open condition--------//  
    if((Final_Internal_Probe_Temp==-1) ) 
    { 
       Internal_probe_short_open_counter++;
       if(Internal_probe_short_open_counter>=2) //--------if count greater than 2(this is to check atleast 20 sec)
       {  
            //   Serial.print("Internal_probe_short_open_counter :");
            //  Serial.println("short....");
            // Serial2.println("K-type Probe error");
            if(Process_Start_Flag==1)//------------In process
            {
              Exit_Process=0;  //-----------Exit process
            }
            Probe_Error_Flag=1;
            mode=0;
            Internal_probe_short_open_counter=0;
            Internal_probe_short_open_ticker.stop();
       }
      
    }
   
}

//----------------------PT1000 status(Probe Removed condition)------------------------------//
void PT1000_Not_Detected();
Ticker PT1000_Not_Detected_ticker(PT1000_Not_Detected, 3000, 0);
void PT1000_Not_Detected()
{ 
    //------------Removed codtion----------------//  
    // if(PT1000_Detection_Occured==0) 
    // { 
    //    PT1000_Not_Detected_counter++;
    //    if(PT1000_Not_Detected_counter>=2) //--------if count greater than 2(this is to check atleast 10 sec)
    //    {  
    //         //   Serial.print("Internal_probe_short_open_counter :");
    //         //  Serial.println("short....");
    //         Serial2.println("External Probe error");
    //         if(Process_Start_Flag==1)//------------In process
    //         {
    //           Exit_Process=0;  //-----------Exit process
    //         }
    //         PT1000_Not_Detected_Flag=1;
    //         mode=0;
    //         PT1000_Not_Detected_counter=0;
    //         PT1000_Not_Detected_ticker.stop();
    //    }
      
    // }
   
}
//-----------------------------Home page temperture increment ticker------------------------------------//
void initial_temp_inc_check();
Ticker initial_temp_inc_check_ticker(initial_temp_inc_check, 10000, 0);
void initial_temp_inc_check()
{   
    if((Final_Internal_Probe_Temp>Initial_temp) && Process_Start_Flag==0)
    { 
     
      if(Final_Internal_Probe_Temp-Initial_temp>=3)//------------Differance greater than 5 degree C
      {
        initial_temp_inc_check_count++; //-----------------to count
       
      }
      Initial_temp=Final_Internal_Probe_Temp; 
    }
   
}
//-------------------BLDC motor Ramp Ticker--------------------------//
void Ramp_ticker_func();
Ticker Ramp_ticker(Ramp_ticker_func, 10, 0);
void Ramp_ticker_func()
{
   BLDC.Ramp_up(change_ramp);
}
void tickers_class::Ramp_ticker_update()
{
    Ramp_ticker.update();
}
//----------------------BLDC motor slow stop-------------------------//
void Motor_slow_stop();
Ticker Motor_slow_stop_tick(Motor_slow_stop, 2000, 0, MILLIS);
void Motor_slow_stop() 
{
  //  Serial.print("Stop_pwm : ");
  //  Serial.println(Stop_pwm);
  Stop_pwm = Stop_pwm + 5;
}

//----------------------BLDC motor slow stop-------------------------//
void Int_Motor_Spd_control();
Ticker Int_Motor_Spd_control_tick(Int_Motor_Spd_control, 4000, 1, MILLIS);
void Int_Motor_Spd_control() 
{
  //  Serial.print("Stop_pwm : ");
  Int_Motor_Spd_control_flag=0;
  //  Serial2.println("Int_Motor_Spd_control");
   
}

//-------------------Internal probe short/open check filter---------------------------------//
void SSR_cutoff_Reach();
Ticker SSR_cutoff_Reach_ticker(SSR_cutoff_Reach, 2000, 0);
void SSR_cutoff_Reach()
{   
    SSR_Fail_check_Count++;
    // Serial2.print("SSR_Fail_check_Count :");
    //    Serial2.println(SSR_Fail_check_Count);
    if(Final_Internal_Probe_Temp>=650)
    {
       SSR_cutoff_Reach_Count++;
      //  Serial2.print("SSR_cutoff_Reach_Count :");
      //  Serial2.println(SSR_cutoff_Reach_Count);
      //  Serial2.print("Final_Internal_Probe_Temp :");
      //  Serial2.println(Final_Internal_Probe_Temp);
    }
    if(SSR_Fail_check_Count>=6 && SSR_cutoff_Reach_Count<4)
    {  
        // Serial2.println("no ssr ");
        SSR_cutoff_Reach_Count=0;
        SSR_Fail_check_Count=0;
        SSR_cuttoff_reached_Flag=0;
        SSR_cutoff_Reach_ticker.stop();
    }
}

//--------------------------------Cal1 & Cal2 save msg show ticker-----------------------------------------------//
void Calibration_save();
Ticker Calibration_save_ticker(Calibration_save, 4000, 1, MILLIS);  //Time_speed_show_toggle
void Calibration_save()
{  
              Inside_Calibration_menu=0;
              Cal2_Selection_Parameter=0;
              Knob_Single_Press_In_Calibration1=0;
              Knob_Single_Press_In_Settings=0;
              Setting_Menu=0;
              encoder0Pos=0;
  
}
// //---------------------------------Set Up function-----------------------------------------------------------//
void tickers_class::tickers_SETUP()
{ 
  VersionDisplay.start();
  LongPress7sec_ticker.start();
  Fast_Inc_Dec_ticker.start();
  toggle_ticker.start();
  Ramp_ticker.start();
  // PT1000_Not_Detected_ticker.start();
}

void tickers_class::Process_stop_by_key1_ticker_start()
{
    Process_stop_by_key1_ticker.start();
}
// //------------------In_process_Set_RPM_show ticker  update--------------------------------------//
void tickers_class::In_process_Set_RPM_show_start()
{
    In_process_Set_RPM_show_ticker.start();
}

//-----------------------------Version show ticker update---------------------------------------------------//
void tickers_class::VersionDisplay_update()
{ 
   VersionDisplay.update();
}
//---------------------------LongPress7sec update----------------------------------------//
void tickers_class::LongPress7sec_update()
{ 
    LongPress7sec_ticker.update();
    BUZZ.update();
     
}
//------------------Encoder Fast_Inc_Dec_ticker update--------------------------------------//
void tickers_class::Encoder_Fast_Inc_Dec_update()
{ 
     Fast_Inc_Dec_ticker.update();
}

//---------------------------toggle_display update----------------------------------------//
void tickers_class::toggle_display_update()
{ 
   toggle_ticker.update();
}

void tickers_class:: In_Process_Ticker_Update() 
{
   Process_stop_by_key1_ticker.update();
   In_process_Set_RPM_show_ticker.update();
   BUZZ.update();
   Inprocess_Lamp_glow_ticker_update();
   Ramp_ticker.update();
}
void tickers_class::Inprocess_Lamp_glow_ticker_start()
{
  Inprocess_Lamp_glow_ticker.start();
}
void tickers_class::Inprocess_Lamp_glow_ticker_update()
{
  Inprocess_Lamp_glow_ticker.update();
}

//----------------------Probe error condition----------------------------//
void tickers_class::Internal_probe_short_open_ticker_start()
{
  Internal_probe_short_open_ticker.start();
}
void tickers_class::Internal_probe_short_open_ticker_update()
{
  Internal_probe_short_open_ticker.update();
}

void tickers_class::PT1000_Not_Detected_ticker_start()
{
PT1000_Not_Detected_ticker.start();
}

void tickers_class::PT1000_Not_Detected_ticker_update()
{
  PT1000_Not_Detected_ticker.update();
}


void tickers_class::Motor_slow_stop_tick_start()
{
  Motor_slow_stop_tick.start();
}
void tickers_class::Motor_slow_stop_tick_stop()
{
  Motor_slow_stop_tick.stop();
}
void tickers_class::Motor_slow_stop_tick_update()
{
  Motor_slow_stop_tick.update();
}

//----------------------Temp Inc check in home page----------------------------//
void tickers_class::initial_temp_inc_check_ticker_start()
{
    initial_temp_inc_check_ticker.start();
}
void tickers_class::initial_temp_inc_check_ticker_stop()
{
    initial_temp_inc_check_ticker.stop();
}
void tickers_class::initial_temp_inc_check_ticker_update()
{
    initial_temp_inc_check_ticker.update();
}

void tickers_class::Int_Motor_Spd_control_tick_start()
{
    Int_Motor_Spd_control_tick.start();
}
void tickers_class::Int_Motor_Spd_control_tick_update()
{
    Int_Motor_Spd_control_tick.update();
}
//-----------------
void tickers_class::SSR_cutoff_Reach_ticker_start()
{
    SSR_cutoff_Reach_ticker.start();
}
void tickers_class::SSR_cutoff_Reach_ticker_update()
{
    SSR_cutoff_Reach_ticker.update();
}
//----------------------
void tickers_class::Calibration_save_ticker_start()
{
    Calibration_save_ticker.start();
}
void tickers_class::Calibration_save_ticker_update()
{
    Calibration_save_ticker.update();
}
tickers_class tickers = tickers_class();  