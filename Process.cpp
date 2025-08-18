//************************************Set parameter,Process,Setting menu************************************************//
#include "ext_var.h"

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
void Cal1_Master_temperature_conversion();
//--------------------set parameter variables------------------------------//
int mode=0;
int Enter_Button=0;
int Set_temp=0, Set_time=0, Set_speed=0,Set_Hour=0,Set_Min=0,OHS_Set_speed=0,Internal_safety_cutoff=380;
int EEPROM_Hour=0,EEPROM_Min=0,EEPROM_Set_Temp=0;
bool Exit_Process=0,Process_Start_Flag=0,SetPoint_for_Cal2=0,SSR_fail_In_Cal2_flag=0;
bool PT100_1_Detection_Occured=0,PT1000_Detection_Occured=0;
bool ONCE_EEPROM_write_flag=0;
int set_temperature_num=0,set_temperature_decimal=0;
double Final_set_temperature=0;
bool Overhead_Motor_connected_Flag=0,Motor_Stop_Flagg=0;
int Stop_pwm = 233;
bool stop_motor_slowly_ONCE = 0,Inprocess_Flag_stop_motor=0,Int_Motor_Spd_control_flag=0,Motor_stop_After_process_exit=0,Motor_stop_In_Recipe=0;
bool  Soak_time_start_flag=0,Soak_time_Once=0;
bool Receipe_Mode=0,Knob_Single_Press_In_Receipe_start=0;
int Receipe_Step=0,Receipe_Parameter=0,Receipe=0,Process_start_stop_Rcp_step=0,Receipe_Count=0;
int Receipe_Set_Temp[4][6]={},Receipe_Set_Hour[4][6]={}, Receipe_Set_Min[4][6]={},Receipe_Set_RPM[4][6]={},Receipe_cnt[4]={93,94,95,96};  //Receipe_cnt[4]={19,20,21,22};
int Receipe_Page[6]={44,45,46,47,48,49};
int Graph_Temp_update_Flag=0,Graph_Time_update_Flag=0,TC=0,Inprocess_Set_Temp_Change=0;
bool Inprocess_Set_Temp_Save=1,initial_temp_inc_check_ONCE=0,SSR_Failure_Flag=0;
float Initial_temp=0;
int initial_temp_inc_check_count=0;
int Home_Page[2]={57,1},Set_page1[2]={59,2},Set_page2[2]={61,3},Set_page3[2]={66,55},Process_page[2]={63,5};
int Home_Vapor_alert[2]={58,7},Home_Vapor_alert_blank[2]={65,56};
int Set_page1_Vapor_alert[2]={73,71},Set_page1_Vapor_alert_blank[2]={74,72};
int Set_page2_Vapor_alert[2]={77,75},Set_page2_Vapor_alert_blank[2]={78,76};
int Set_page3_Vapor_alert[2]={81,79},Set_page3_Vapor_alert_blank[2]={82,80};
int Process_Vapor_alert[2]={85,83},Process_Vapor_alert_blank[2]={86,84};
int RCP_EEPROM_Address[4][6]={{40,46,52,58,64,70},
                              {76,82,88,94,100,106},
                              {112,118,124,130,136,142},
                              {148,154,160,166,172,178}
                              };
int RCP_Page_with_Arrow[6][4]={{43,97,98,98},{43,99,100,100},{43,101,102,102},{43,103,104,104},{43,105,106,106},{43,107,108,108}
                              };
//-------------------------probe----------------------------------------//
int Internal_probe_short_open_counter=0,PT1000_Not_Detected_counter=0;
bool Probe_Error_Flag=0,PT1000_Not_Detected_Flag=0;
//-------------------------------------Setting menu-------------------------------------------------------//
bool Knob_Single_Press_In_Settings=0;
int Setting_Menu=0;
bool Slow_Fast_Mode_Flag=0,Autoresume_Enable_Disable_Flag=0;
uint8_t Time_mode_Flag=0;
unsigned int Master_Pressure=0,Master_RPM=0,Safe_Temperature=0;
int RPM_diff_Factor=0,Master_unit_RPM_diff=0;
                                            
int EEPROM_Error_value_Cal1[2]={ };
int EEPROM_Plus_Minus_flag_Cal1[2]={ };
int Safe_Menu_Count=0,Safe_Temp[3]={};
//--------------------Calibration----------------//
float Temperature_After_Calibration = 0,Probe_Temp[2]={ };
bool Inside_Calibration_menu=0,Calibration_selection_flag=0,Knob_Single_Press_In_Calibration1=0;
int Calibration1_Value=0,cal1_error_num=0,cal1_error_decimal=0,Final_Error_Difference=0,master_temp_num,master_temp_decimal;
bool Calibration_1_plus_minus_EEPROM=0;
double Final_calibration1_error_final[2]={},probe_selection[2]={},Final_calibration2_Low_Master[2]={},Final_calibration2_High_Master[2]={},Final_temp_after_cal2[2]={};
float Error_Difference=0,Final_master_temp=0;
int Cal2_Selection_Parameter=0,CAL2_Low_Set_temp=0,CAL2_High_Set_temp=0,CAL2_Low_Master=0,CAL2_High_Master=0;
bool CAL2_maintain_flag=0,Single_Click_In_Cal2_maintain=0,Oncee_Cal2=0;
int EEPROM_cal2_Low_Master=0,EEPROM_cal2_High_Master=0,EEPROM_calibration2_LOW_value=0,EEPROM_calibration2_High_value=0;
int cal2_Low_temperature_num=0,cal2_Low_temperature_decimal=0,cal2_High_temperature_num=0,cal2_High_temperature_decimal=0;
//-------------------In process-------------------------------------------//
bool toggle=0;
int Current_Min=0,Current_HOUR=0;
bool Inprocess_Set_RPM_show_flag=0;
int Inprocess_page_change=1;
bool door_open_flag=0,Inprocess_Lamp_glow_flag=0,Heater_PID_start_Flag=0,Inprocess_check_flag_for_autoresume=0;
//************************************PINs declaration************************************************//
bool SSR_cuttoff_reached_Flag=0;
uint8_t SSR_cutoff_Reach_Count=0,SSR_Fail_check_Count=0;

void Temp_readings();
Ticker Temp_readings_ticker(Temp_readings, 60000, 0);
void Temp_readings()
{ 
   Serial2.print(Temperature_After_Calibration);
   Serial2.print("     \t");
   Serial2.print(Smoothed_PT1000_Temperature);
   Serial2.print("     \t");
   Serial2.print(Internal_Temp_Post_Calb);
   Serial2.print("     \t");
   Serial2.println(Final_Internal_Probe_Temp);



  //  Serial2.print("Probe Temp: ");
  // if(PT1000_Detection_Occured==1)
  // {
  //  Serial2.print(Temperature_After_Calibration);
  //  Serial2.print("     \t");
  //  Serial2.print(PT1000_TEMP_RAW);
  //  Serial2.print("     \t");
  // //  Serial2.print("Internal : ");
  //  Serial2.print(Internal_Temp_Post_Calb);
  //  Serial2.print("     \t");
  // //  Serial2.print("Int Raw : ");
  //  Serial2.println(Final_Internal_Probe_Temp);
  // }

  // else
  // {
  //   Serial2.print(Internal_Temp_Post_Calb);
  //   Serial2.print("     \t");
  // //  Serial2.print("Int Raw : ");
  //  Serial2.println(Final_Internal_Probe_Temp);

  // }

      // Serial2.print("Output1 : ");
      //  Serial2.println(Output1);
      //  Serial2.print("A_speed : ");
      //  Serial2.println(A_speed);
      //  Serial2.print("Setpoint1 : ");
      //  Serial2.println(Setpoint1);
      //  Serial2.print("Input1 : ");
      //  Serial2.println(Input1); 
      //  Serial2.print("set_speed : ");
      //  Serial2.println(Set_speed); 
      //  Serial2.println("********************************");
  

  //  Serial2.print("Ext Probe Temp: ");
  //  Serial2.println(Smoothed_PT1000_Temperature);
  //  Serial2.print("Internal : ");
  //  Serial2.println(smoothed_KType_Temp);
  //  Serial2.print("Int Raw : ");
  //  Serial2.println(Final_Internal_Probe_Temp);
  //  Serial2.print("     \t");
  //  Serial2.print(" TEMP_DEG_RAW1: ");
  //  Serial2.print(TEMP_DEG_RAW1);
  //  Serial2.print("     \t");
  //  Serial2.print(" TEMP_DEG_RAW2: ");
  //  Serial2.println(TEMP_DEG_RAW2);
 
  //  Serial2.print(" Temperature_After_Calibration: ");
  //  Serial2.println(Temperature_After_Calibration);
  //  Serial2.print(" Internal_Temp_Post_Calb: ");
  //  Serial2.println(Internal_Temp_Post_Calb);
  //  Serial2.print(" Setpoint: ");
  //  Serial2.println(Setpoint);
  //  Serial2.print(" Input: ");
  //  Serial2.println(Input);
  //  Serial2.println("***********************************************");
      
  //  Serial2.print(Final_Internal_Probe_Temp);
  //                 Serial2.print("\t");
  //                 Serial2.println(K_Type_emaFilter_Output);
                  // Serial2.print("\t");

}

void Temp_Value_for_Graph();
Ticker Temp_Value_for_Graph_ticker(Temp_Value_for_Graph, 1000, 0);

void Heater_PID_start();
Ticker Heater_PID_start_ticker(Heater_PID_start, 5000, 1);
void Heater_PID_start()
{
  Heater_PID_start_Flag=1;
   
}

ProcessClass::ProcessClass()
{}

//----------------------------------Process Set Up function--------------------------------------------//
void ProcessClass::PROCESS_SETUP() 
{ 
  Set_temp= (EEPROM.read(1) << 8) + EEPROM.read(2);
  Set_Hour=EEPROM.read(3);
  Set_Min=EEPROM.read(4);
  EEPROM_Set_Temp=Set_temp;
  EEPROM_Hour=Set_Hour;
  EEPROM_Min=Set_Min;
  Time_mode_Flag=EEPROM.read(5);
  Slow_Fast_Mode_Flag=EEPROM.read(6);
  Autoresume_Enable_Disable_Flag=EEPROM.read(7);
  Inprocess_check_flag_for_autoresume=EEPROM.read(35);
  Calibration_selection_flag=EEPROM.read(10);
  Safe_Temp[0]=(EEPROM.read(8) << 8) + EEPROM.read(9);
  Safe_Temp[1]=(EEPROM.read(31) << 8) + EEPROM.read(32);
  Safe_Temp[2]=(EEPROM.read(33) << 8) + EEPROM.read(34);

  pinMode(Set_LED,OUTPUT);
  pinMode(Process_LED,OUTPUT);
  digitalWrite(Set_LED,LOW);
  digitalWrite(Process_LED,LOW);
  pinMode(relay,OUTPUT);
  // digitalWrite(relay,LOW);
  digitalWrite(relay,HIGH);

  // for(int rcp_i=0;rcp_i<6;rcp_i++)
  // {
  //   Receipe_Set_Temp[Receipe][rcp_i]=250;
  // }
  for(Receipe=0;Receipe<4;Receipe++)
  { 
    for(Receipe_Step=0;Receipe_Step<6;Receipe_Step++)
    {
        Receipe_Set_Temp[Receipe][Receipe_Step]=(EEPROM.read(RCP_EEPROM_Address[Receipe][Receipe_Step]) << 8) + EEPROM.read(RCP_EEPROM_Address[Receipe][Receipe_Step]+1);
        Receipe_Set_Hour[Receipe][Receipe_Step]=EEPROM.read(RCP_EEPROM_Address[Receipe][Receipe_Step]+2);
        Receipe_Set_Min[Receipe][Receipe_Step]=EEPROM.read(RCP_EEPROM_Address[Receipe][Receipe_Step]+3);
        Receipe_Set_RPM[Receipe][Receipe_Step]=(EEPROM.read((RCP_EEPROM_Address[Receipe][Receipe_Step])+4) << 8) + EEPROM.read(RCP_EEPROM_Address[Receipe][Receipe_Step]+5);

                        // Serial2.print("RCP_EEPROM_Address[Receipe][Receipe_Step] :");
                        // Serial2.println(RCP_EEPROM_Address[Receipe][Receipe_Step]);
                        // Serial2.print("Receipe :");
                        // Serial2.println(Receipe);
                        // Serial2.print("Receipe_Step :");
                        // Serial2.println(Receipe_Step);
                        // Serial2.print(" Receipe_Set_Temp[Receipe][Receipe_Step]  :");
                        // Serial2.println( Receipe_Set_Temp[Receipe][Receipe_Step] );
                        // Serial2.print(" Receipe_Set_Hour[Receipe][Receipe_Step]  :");
                        // Serial2.println( Receipe_Set_Hour[Receipe][Receipe_Step] );
                        // Serial2.print(" Receipe_Set_Min[Receipe][Receipe_Step]  :");
                        // Serial2.println( Receipe_Set_Min[Receipe][Receipe_Step] );
                        // Serial2.print(" Receipe_Set_RPM[Receipe][Receipe_Step]  :");
                        // Serial2.println( Receipe_Set_RPM[Receipe][Receipe_Step] );
                        // Serial2.println("**********************************************");
        delay(1);
    }
  }
  //  Serial2.println("ENDDDD......" );
  Receipe_Step=0;
  Receipe=EEPROM.read(200);
 
  Temp_readings_ticker.start();
}

//*****************************************************SET Parameters ****************************************************//
void ProcessClass::set_display()
{ 
  switch (Enter_Button)
  {
        case 0 :  //--------------Home page
                      digitalWrite(Set_LED,LOW);
                      digitalWrite(Process_LED,LOW);
                      if(Motor_stop_After_process_exit==1)
                      { 
                            if(Set_speed==0)
                            {
                                  // Serial2.println("AAAAAAAAA...");
                                  Motor_stop_After_process_exit=0; 
                            }
                           if(Set_speed!=0)
                           {   
                              // Serial2.println("Output1 : ");
                              
                              Set_speed=0;
                              if(Overhead_Motor_connected_Flag==0)
                              {
                                    // Serial2.println("motor stop process exit");
                                    Stop_pwm=233;
                                    Motor_Stop_Flagg=1;
                                    tickers.Motor_slow_stop_tick_start();
                              }
                              Motor_stop_After_process_exit=0; 

                           }
                            

                      }
                        // Serial2.print("Set_speed : ");
                        //     Serial2.println(Set_speed);
                        //  digitalWrite(HEATER,HIGH);
                      //  analogWrite(pwm, 237);
                      //-------------------Read values from EEPROM----------------------------------------//
                      once_det_read=0;
                      Process_stop_by_key1=0;
                      Process_Start_Flag=0;
                      ONCE_EEPROM_write_flag=0;
                      Inprocess_Lamp_glow_flag=0;
                      Inprocess_page_change=1;
                      once_heater_PID=0;
                      Setting_Menu=0;
                      incrementTime=0;
                      setMin=0;
                      InF_mode=0;
                      Current_HOUR = 0;
                      Current_Min =0 ;
                      Soak_time_start_flag=0;
                      Soak_time_Once=0;
                      Inside_Calibration_menu=0;
                      Knob_Single_Press_In_Receipe_start=0;
                      Knob_Single_Press_In_Calibration1=0;
                      Graph_Temp_update_Flag=0;
                      Graph_Time_update_Flag=0;
                      TC=0;
                      Inprocess_Set_Temp_Change=0;
                      Inprocess_Set_Temp_Save=1;
                      Safe_Menu_Count=0;
                      Heater_PID_start_Flag=0;
                      SetPoint_for_Cal2=0;
                      SSR_cuttoff_reached_Flag=0;
                      SSR_cutoff_Reach_Count=0;
                      SSR_Fail_check_Count=0;
                      SSR_fail_In_Cal2_flag=0;
                      Input=0;

                        Receipe_Step=0;
                        // EEPROM_Set_Temp=(EEPROM.read(1) << 8) + EEPROM.read(2);
                        Set_temp=(EEPROM.read(1) << 8) + EEPROM.read(2);
                        EEPROM_Hour=EEPROM.read(3);
                        Set_Hour=EEPROM_Hour;
                        EEPROM_Min=EEPROM.read(4);
                        Set_Min=EEPROM_Min;
                        Time_mode_Flag=EEPROM.read(5);
                        Slow_Fast_Mode_Flag=EEPROM.read(6);
                        Autoresume_Enable_Disable_Flag=EEPROM.read(7);
                        Inprocess_check_flag_for_autoresume=EEPROM.read(35);
                        Safe_Temp[0]=(EEPROM.read(8) << 8) + EEPROM.read(9);
                        Safe_Temp[1]=(EEPROM.read(31) << 8) + EEPROM.read(32);
                        Safe_Temp[2]=(EEPROM.read(33) << 8) + EEPROM.read(34);
                        Receipe=EEPROM.read(200);
                       if(Autoresume_Enable_Disable_Flag==0 && Inprocess_check_flag_for_autoresume==1) //---------------Autoresume enable and inprocess- process stop
                       {  
                          Receipe_Mode=EEPROM.read(201);
                          if(Receipe_Mode==0)
                          {
                             Set_speed=(EEPROM.read(202) << 8) + EEPROM.read(203);
                          }
                          Enter_Button=4;
                       }                  
                      // EEPROM_Error_value_Cal1[0]=EEPROM.read(14); //----------------Internal
                      // EEPROM_Plus_Minus_flag_Cal1[0]=EEPROM.read(13);
                      // EEPROM_Error_value_Cal1[1]=EEPROM.read(12);//----------------External
                      // EEPROM_Plus_Minus_flag_Cal1[1]=EEPROM.read(11);
                      //  Serial2.print(" EEPROM_Error_value_Cal1[1] : ");
                      //              Serial2.println( EEPROM_Error_value_Cal1[1]);
                      //              Serial2.print(" EEPROM_Plus_Minus_flag_Cal1[1][1] : ");
                      //              Serial2.println(EEPROM_Plus_Minus_flag_Cal1[1]);
                      //              Serial2.println("*******************************************************");
                      // Final_Error_Difference= (EEPROM.read(12) << 8) + EEPROM.read(13);
                                //   Serial2.print("Time_mode_Flag :");
                                //   Serial2.println(Time_mode_Flag);
                                //  Serial2.print("Slow_Fast_Mode_Flag :");
                                //  Serial2.println(Slow_Fast_Mode_Flag);
                                //  Serial2.print("Safe_Temperature :");
                                //   Serial2.println(Safe_Temperature);
                                //    Serial2.print("Autoresume :");
                                //    Serial2.println(Autoresume_Enable_Disable_Flag);
                                //      Serial2.println("*********************************************************");
                        if(Receipe_Mode==0)
                        {
                              sendDataFlag=0;
                              if(PT100_1_Detection_Occured==1)
                                       DwinDisplay.setPage(Home_Page[PT1000_Detection_Occured]);
                              if(PT100_1_Detection_Occured==0)
                              {
                                     if(toggle==0)
                                      {
                                       DwinDisplay.setPage(Home_Vapor_alert[PT1000_Detection_Occured]);
                                      }
                                      if(toggle==1)
                                      {
                                       DwinDisplay.setPage(Home_Vapor_alert_blank[PT1000_Detection_Occured]);
                                      }
                              }
                              DwinDisplay.Data_Arduino_to_Display_Current_Temp(Temperature_After_Calibration);
                              DwinDisplay.Save_hour(EEPROM_Hour);
                              DwinDisplay.Save_Min(EEPROM_Min);
                              if(Overhead_Motor_connected_Flag==0)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(Set_speed);   
                              if(Overhead_Motor_connected_Flag==1)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(OHS_Set_speed);
                              DwinDisplay.Data_controller_to_Display_Vapour_Temp(Smoothed_Probe1_Temp);  
                              //  DwinDisplay.Data_controller_to_Display_Vapour_Temp(Final_Internal_Probe_Temp); // 
                              //  DwinDisplay.Data_controller_to_Display_Vapour_Temp(smoothed_KType_Temp);
                        }
                        if(Receipe_Mode==1)
                        {
                              sendDataFlag=0;
                              DwinDisplay.setPage(43);
                              DwinDisplay.Data_to_Display_Receipe(Receipe+1);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step0(Receipe_Set_Temp[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step1(Receipe_Set_Temp[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step2(Receipe_Set_Temp[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step3(Receipe_Set_Temp[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step4(Receipe_Set_Temp[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step5(Receipe_Set_Temp[Receipe][5]);

                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step0(Receipe_Set_Hour[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step1(Receipe_Set_Hour[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step2(Receipe_Set_Hour[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step3(Receipe_Set_Hour[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step4(Receipe_Set_Hour[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step5(Receipe_Set_Hour[Receipe][5]);

                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step0(Receipe_Set_Min[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step1(Receipe_Set_Min[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step2(Receipe_Set_Min[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step3(Receipe_Set_Min[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step4(Receipe_Set_Min[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step5(Receipe_Set_Min[Receipe][5]);
                            // DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step0(Receipe_Set_Hour[Receipe][0]);
                            // DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step1(Receipe_Set_Hour[Receipe][1]);
                            
                            // DwinDisplay.Data_to_Display_Receipe_Set_Min_Step0(Receipe_Set_Min[Receipe][0]);
                            // DwinDisplay.Data_to_Display_Receipe_Set_Min_Step1(Receipe_Set_Min[Receipe][1]);

                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step0(Receipe_Set_RPM[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step1(Receipe_Set_RPM[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step2(Receipe_Set_RPM[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step3(Receipe_Set_RPM[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step4(Receipe_Set_RPM[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step5(Receipe_Set_RPM[Receipe][5]);
                        }

                      break;
        case 1 : //----------------Set Temperature 
                        digitalWrite(Set_LED,HIGH);
                        // digitalWrite(Process_LED,LOW); 
                        if(Receipe_Mode==0)
                        {
                            // Serial2.println("main ");
                            sendDataFlag=0;
                            if(PT100_1_Detection_Occured==1)
                                       DwinDisplay.setPage(Set_page1[PT1000_Detection_Occured]);
                            if(PT100_1_Detection_Occured==0)
                            {
                                      if(toggle==0)
                                      {
                                         DwinDisplay.setPage(Set_page1_Vapor_alert[PT1000_Detection_Occured]);
                                      }
                                      if(toggle==1)
                                      {
                                         DwinDisplay.setPage(Set_page1_Vapor_alert_blank[PT1000_Detection_Occured]);
                                      }
                            }
                            DwinDisplay.Data_Arduino_to_Display_for_set(Set_temp); 
                            // DwinDisplay.Data_Arduino_to_Display_set_Hour(Set_Hour);
                            // DwinDisplay.Data_Arduino_to_Display_set_Min(Set_Min);
                             DwinDisplay.Data_Arduino_to_Display_Current_Temp(Temperature_After_Calibration);
                             DwinDisplay.Data_Arduino_to_Display_set_Hour(Set_Hour);
                            DwinDisplay.Data_Arduino_to_Display_set_Min(Set_Min);
                            // DwinDisplay.Save_Temperature(EEPROM_Set_Temp);
                            DwinDisplay.Save_hour(EEPROM_Hour);
                            DwinDisplay.Save_Min(EEPROM_Min);
                            if(Overhead_Motor_connected_Flag==0)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(Set_speed);   
                              if(Overhead_Motor_connected_Flag==1)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(OHS_Set_speed);
                            DwinDisplay.Data_controller_to_Display_Vapour_Temp(Smoothed_Probe1_Temp);
                        }
                        if(Receipe_Mode==1)
                        {
                              // Serial2.println("Recp ");
                              sendDataFlag=0;
                              // DwinDisplay.setPage(Receipe_Page[Receipe_Step]);   
                              DwinDisplay.setPage(RCP_Page_with_Arrow[Receipe_Step][Enter_Button]);
                              DwinDisplay.Data_to_Display_Receipe(Receipe+1);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step0(Receipe_Set_Temp[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step1(Receipe_Set_Temp[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step2(Receipe_Set_Temp[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step3(Receipe_Set_Temp[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step4(Receipe_Set_Temp[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Temp_Step5(Receipe_Set_Temp[Receipe][5]);

                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step0(Receipe_Set_RPM[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step1(Receipe_Set_RPM[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step2(Receipe_Set_RPM[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step3(Receipe_Set_RPM[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step4(Receipe_Set_RPM[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step5(Receipe_Set_RPM[Receipe][5]);
                              
                              
                            

                        }
                    
                       
                    break;
         case 2 : //----------------Set Hour
                        digitalWrite(Set_LED,HIGH);
                        if(Receipe_Mode==0)
                        {
                                  
                                  // digitalWrite(Process_LED,LOW); 
                                  sendDataFlag=0;
                                    if(PT100_1_Detection_Occured==1)
                                              DwinDisplay.setPage(Set_page2[PT1000_Detection_Occured]);
                                    if(PT100_1_Detection_Occured==0)
                                    {
                                              if(toggle==0)
                                              {
                                                DwinDisplay.setPage(Set_page2_Vapor_alert[PT1000_Detection_Occured]);
                                              }
                                              if(toggle==1)
                                              {
                                                DwinDisplay.setPage(Set_page2_Vapor_alert_blank[PT1000_Detection_Occured]);
                                              }
                                    }
                                  DwinDisplay.Data_Arduino_to_Display_for_set(Set_temp);
                                   DwinDisplay.Data_Arduino_to_Display_Current_Temp(Temperature_After_Calibration); 
                                  DwinDisplay.Data_Arduino_to_Display_set_Hour(Set_Hour);
                                  DwinDisplay.Data_Arduino_to_Display_set_Min(Set_Min);
                                  // DwinDisplay.Save_Temperature(EEPROM_Set_Temp);
                                  DwinDisplay.Save_hour(EEPROM_Hour);
                                  DwinDisplay.Save_Min(EEPROM_Min);
                                 if(Overhead_Motor_connected_Flag==0)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(Set_speed);   
                              if(Overhead_Motor_connected_Flag==1)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(OHS_Set_speed);
                                  DwinDisplay.Data_controller_to_Display_Vapour_Temp(Smoothed_Probe1_Temp);
                        }
                         if(Receipe_Mode==1)
                        {
                              
                              sendDataFlag=0;
                              // DwinDisplay.setPage(Receipe_Page[Receipe_Step]);
                              DwinDisplay.setPage(RCP_Page_with_Arrow[Receipe_Step][Enter_Button]);
                              DwinDisplay.Data_to_Display_Receipe(Receipe+1);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step0(Receipe_Set_Hour[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step1(Receipe_Set_Hour[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step2(Receipe_Set_Hour[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step3(Receipe_Set_Hour[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step4(Receipe_Set_Hour[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Hour_Step5(Receipe_Set_Hour[Receipe][5]);

                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step0(Receipe_Set_RPM[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step1(Receipe_Set_RPM[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step2(Receipe_Set_RPM[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step3(Receipe_Set_RPM[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step4(Receipe_Set_RPM[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step5(Receipe_Set_RPM[Receipe][5]);
                        
                        }
                    
                       
                    break;
        case 3 : //----------------Set Minute
                        digitalWrite(Set_LED,HIGH);
                        // digitalWrite(Process_LED,LOW);
                        if(Receipe_Mode==0)
                        { 
                              sendDataFlag=0;
                              // DwinDisplay.setPage(Set_page3[PT1000_Detection_Occured]);
                              if(PT100_1_Detection_Occured==1)
                                       DwinDisplay.setPage(Set_page3[PT1000_Detection_Occured]);
                            if(PT100_1_Detection_Occured==0)
                            {
                                      if(toggle==0)
                                      {
                                         DwinDisplay.setPage(Set_page3_Vapor_alert[PT1000_Detection_Occured]);
                                      }
                                      if(toggle==1)
                                      {
                                         DwinDisplay.setPage(Set_page3_Vapor_alert_blank[PT1000_Detection_Occured]);
                                      }
                            }
                              DwinDisplay.Data_Arduino_to_Display_for_set(Set_temp); 
                              DwinDisplay.Data_Arduino_to_Display_Current_Temp(Temperature_After_Calibration);
                              DwinDisplay.Data_Arduino_to_Display_set_Hour(Set_Hour);
                              DwinDisplay.Data_Arduino_to_Display_set_Min(Set_Min);
                              // DwinDisplay.Save_Temperature(EEPROM_Set_Temp);
                              DwinDisplay.Save_hour(EEPROM_Hour);
                              DwinDisplay.Save_Min(EEPROM_Min);
                              if(Overhead_Motor_connected_Flag==0)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(Set_speed);   
                              if(Overhead_Motor_connected_Flag==1)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(OHS_Set_speed);
                              DwinDisplay.Data_controller_to_Display_Vapour_Temp(Smoothed_Probe1_Temp);
                        }
                        if(Receipe_Mode==1)
                        {
                              sendDataFlag=0;
                              // DwinDisplay.setPage(Receipe_Page[Receipe_Step]);
                              DwinDisplay.setPage(RCP_Page_with_Arrow[Receipe_Step][Enter_Button]);
                              DwinDisplay.Data_to_Display_Receipe(Receipe+1);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step0(Receipe_Set_Min[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step1(Receipe_Set_Min[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step2(Receipe_Set_Min[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step3(Receipe_Set_Min[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step4(Receipe_Set_Min[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_Min_Step5(Receipe_Set_Min[Receipe][5]);

                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step0(Receipe_Set_RPM[Receipe][0]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step1(Receipe_Set_RPM[Receipe][1]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step2(Receipe_Set_RPM[Receipe][2]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step3(Receipe_Set_RPM[Receipe][3]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step4(Receipe_Set_RPM[Receipe][4]);
                              DwinDisplay.Data_to_Display_Receipe_Set_RPM_Step5(Receipe_Set_RPM[Receipe][5]);  

                        }
                    
                       
                    break;
        case 4 :  //----------------Process
                     if(ONCE_EEPROM_write_flag==0)
                     {
                         Exit_Process=1;
                         Receipe_Step=0;
                         if(Receipe_Mode==0)
                         {
                              EEPROM.write(1, Set_temp >> 8);//--------Save set Temperature
                              EEPROM.write(2, Set_temp & 0xFF);
                              EEPROM.write(3, Set_Hour);
                              EEPROM.write(4 ,Set_Min);
                              EEPROM.write(202, Set_speed >> 8); //--------set Temperature
                              EEPROM.write(203, Set_speed & 0xFF);
                              EEPROM_Set_Temp=Set_temp;
                              setMin=Set_Hour*60+Set_Min;
                                if(setMin==0)
                                {
                                  InF_mode=1;
                                  // Serial2.println("normal Inff ");
                                  
                                }
                                if(setMin>0)
                                {  
                                  InF_mode=0;
                                  Current_HOUR = setMin / 60;
                                  Current_Min = setMin % 60 ;
                                    // Serial2.println("normal defined ");
                                }
                              // Serial2.println("Normal ");
                         }
                         else if(Receipe_Mode==1)
                         {
                              // EEPROM_Set_Temp=Receipe_Set_Temp[Receipe][Receipe_Step];
                              Set_temp=Receipe_Set_Temp[Receipe][Receipe_Step];
                              Set_Hour=Receipe_Set_Hour[Receipe][Receipe_Step];
                              Set_Min=Receipe_Set_Min[Receipe][Receipe_Step];
                              setMin=Receipe_Set_Hour[Receipe][Receipe_Step]*60+Receipe_Set_Min[Receipe][Receipe_Step];
                                 if(setMin==0)
                                {
                                  InF_mode=0;
                                  countDownStart=0;
                                  Receipe_Mode=0;
                                  Exit_Process=0;
                                  Enter_Button=0;
                                  // Serial2.println("rcp inff ");
                                  
                                }
                                if(setMin>0)
                                {  
                                  InF_mode=0;
                                  Current_HOUR = setMin / 60;
                                  Current_Min = setMin % 60 ;
                                    // Serial2.println("rcp defined ");
                                }
                              if(Receipe_Set_RPM[Receipe][0]==0 && Set_speed>0)
                              {     
                                    Set_speed=0;
                                    Stop_pwm=233;
                                    Motor_Stop_Flagg=1;
                                    tickers.Motor_slow_stop_tick_start();
                                
                              }
                              Set_speed=Receipe_Set_RPM[Receipe][0];
                              // Serial2.println("Recp ");
                              // Serial2.print("** Set_temp :");
                              // Serial2.println(Set_temp );
                              // Serial2.print("** Set_speed :");
                              // Serial2.println(Set_speed );
                              // Serial2.print("** Set_Hour :");
                              // Serial2.println(Set_Hour );
                              // Serial2.print("** Set_Min :");
                              // Serial2.println(Set_Min );
                              // Serial2.print("** setMin :");
                              // Serial2.println(setMin );
                         }
                        ONCE_EEPROM_write_flag=1;
                     }
                      Process.PROCESS_START(); 
                      break;
       
        default:
                break;

  }
}

//***************************************Process Start Function***************************************//
void ProcessClass::PROCESS_START()
{ 
    // digitalWrite(relay,HIGH);
    Heater_PID_start_Flag=0;
    Process_Start_Flag=1;
    countDownStart=1;
    Inprocess_Flag_stop_motor=1;
    stop_motor_slowly_ONCE=1;
    if(Set_speed==0)
    {
        old_dimetime=0;
        dimtime=0;
        ramp_val=0; 
    }
    initial_temp_inc_check_count=0;
    digitalWrite(Set_LED,LOW);
    digitalWrite(Process_LED,HIGH);
    tickers.BUZZ_INTERVAL(1500); 
    tickers.Inprocess_Lamp_glow_ticker_start();
    Process.Setpoint_temperature_conversion(); 
    TimerUpdate.Time_calutation_tick_START();
    Temp_Value_for_Graph_ticker.start(); 
    Heater_PID_start_ticker.start();
    EEPROM.write(201, Receipe_Mode);
    EEPROM.write(35, 1);
   
    // Serial2.println("start ");
    Motor_stop_After_process_exit=1;
   
    while(Exit_Process > 0)//-------until time goes to zero
    { 
         Heater_PID_start_ticker.update();   
         Process.Temp_readings_ticker_update();
         Temp_Value_for_Graph_ticker.update();
         tickers.SSR_cutoff_Reach_ticker_update();
        // Serial.println("Process Start............... ");
         BLDC.Overhead_Motor_check_update();
          if(Motor_Stop_During_OHS_Interuption_Flag==1)
                  BLDC.Motor_Stop_During_OHS_Interuption();
          if(Overhead_Motor_connected_Flag==0)
                  BLDC.PID_motor_set();
         if(Overhead_Motor_connected_Flag==1)
                  BLDC.PID_Overhead_Stirrer_Motor();
         Process.Temp_Reading_After_Calibration();
         TimerUpdate.Time_calutation_tick_UPDATE();
         BLDC.Feedback_update();
        if(Heater_PID_start_Flag==1)
        {
            HeaterPID.Heater_PID_Function();
            // Serial2.println("Heater_PID_start ");
        }
        // if(Final_Internal_Probe_Temp>=400) //----------------Safety relay logic, If internal probe temp goes beyong 400C 
        // { 
        //       digitalWrite(relay,LOW);//---------------relay ON
        //       SSR_Failure_Flag=1;
        //       countDownStart=0;
        //       mode=0;
        //       Exit_Process=0;//------------Process exit
        // }
            if(SSR_cutoff_Reach_Count>=4)
            {
                // Serial2.println("SSR_Failed :");
                digitalWrite(relay,LOW);//---------------relay ON
                SSR_Failure_Flag=1;
                countDownStart=0;
                mode=0;
                Exit_Process=0;//------------Process exit
            }
             if(Final_Internal_Probe_Temp>=650 && SSR_cuttoff_reached_Flag==0) //----------------Safety relay logic, If internal probe temp goes beyong 400C 
             { 
                  // Serial2.println("SSR_cuttoff_reached_Flag :");
                  tickers.SSR_cutoff_Reach_ticker_start();
                  SSR_cuttoff_reached_Flag=1;
                 
             }

            tickers.In_Process_Ticker_Update();
            RTD_Sensor.PT100_Probe1_Temperature_Reading_update();
            RTD_Sensor.PT1000_Temperature_Reading_update();
            KType_sensor.Internal_Probe_Temperature();
            KType_sensor.KType_Reading_Update();
            tickers.Button_update(); 
            tickers.toggle_display_update();
            Encoder.encode_increment();
            Encoder.Encoder2_increment();
            tickers.Encoder_Fast_Inc_Dec_update();
            ProbeDetection.PT100_check_update();
            ProbeDetection.PT1000_check_update();
            tickers.Internal_probe_short_open_ticker_update();
            tickers.PT1000_Not_Detected_ticker_update();
            tickers.Motor_slow_stop_tick_update();
                if(Inprocess_page_change==2  && Process_stop_by_key1==0)
                {
                     sendDataFlag=0;
                     if(PT100_1_Detection_Occured==1)
                     { 
                        // sendDataFlag=0;
                        DwinDisplay.setPage(4);
                        DwinDisplay.Data_controller_to_Display_Inprocess_Vapour_Temp(Smoothed_Probe1_Temp);

                     }
                      if(PT100_1_Detection_Occured==0)
                      {
                                      if(toggle==0)
                                      {
                                         DwinDisplay.setPage(88);
                                      }
                                      if(toggle==1)
                                      {
                                         DwinDisplay.setPage(89);
                                      }
                      }
                    DwinDisplay.Inprocess_Temperature(Temperature_After_Calibration);
                    if(Overhead_Motor_connected_Flag==0)
                            DwinDisplay.Data_Arduino_to_Display_for_set_RPM(Set_speed);   
                    if(Overhead_Motor_connected_Flag==1)
                            DwinDisplay.Data_Arduino_to_Display_for_set_RPM(OHS_Set_speed);
                    
                    //  if(PT100_1_Detection_Occured==1)
                    //          DwinDisplay.Data_controller_to_Display_Inprocess_Vapour_Temp(Smoothed_Probe1_Temp);
                    //   if(PT100_1_Detection_Occured==0)
                    //   {
                    //                   if(toggle==0)
                    //                   {
                    //                      DwinDisplay.setPage(88);
                    //                   }
                    //                   if(toggle==1)
                    //                   {
                    //                      DwinDisplay.setPage(89);
                    //                   }
                    //   }
                }
                 if(Inprocess_page_change==1  && Process_stop_by_key1==0)
                  {  
                            sendDataFlag=0;
                            if(PT100_1_Detection_Occured==1)
                                        DwinDisplay.setPage(Process_page[PT1000_Detection_Occured]);
                            if(PT100_1_Detection_Occured==0)
                            {
                                      if(toggle==0)
                                      {
                                         DwinDisplay.setPage(Process_Vapor_alert[PT1000_Detection_Occured]);
                                      }
                                      if(toggle==1)
                                      {
                                         DwinDisplay.setPage(Process_Vapor_alert_blank[PT1000_Detection_Occured]);
                                      }
                            }
                      DwinDisplay.Data_Arduino_to_Display_for_set(Set_temp); 
                      DwinDisplay.Data_Arduino_to_Display_Current_Temp(Temperature_After_Calibration); 
                      DwinDisplay.Inprocess_Min(); 
                      DwinDisplay.Inprocess_hour();
                      DwinDisplay.Save_hour(Set_Hour);
                      DwinDisplay.Save_Min(Set_Min);
                     if(Overhead_Motor_connected_Flag==0)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(Set_speed);   
                      if(Overhead_Motor_connected_Flag==1)
                                      DwinDisplay.Data_Arduino_to_Display_for_set_RPM(OHS_Set_speed);
                      DwinDisplay.Data_controller_to_Display_Vapour_Temp(Smoothed_Probe1_Temp);
                      // DwinDisplay.Data_controller_to_Display_Vapour_Temp(Final_Internal_Probe_Temp);
                  }
                  if(Inprocess_page_change==0  && Process_stop_by_key1==0)
                  {  
                      sendDataFlag=0;
                      DwinDisplay.setPage(52);
                      DwinDisplay.Data_to_Display_Time_graph(TC);
                  }
                  if(Inprocess_page_change==3  && Process_stop_by_key1==0)
                  {  
                      sendDataFlag=0;
                      DwinDisplay.setPage(Receipe_Page[Receipe_Step]);
                      DwinDisplay.Data_to_Display_Receipe(Receipe+1);
                  }
                //  if(Inprocess_Set_RPM_show_flag==1 && Process_stop_by_key1==0) //----------------------Inprocess Set RPM show
                //  {   
                  
                //   }
                //   if(Inprocess_Set_RPM_show_flag==0 && Process_stop_by_key1==0)
                //   {   
                //       // sendDataFlag=0;
                //       // DwinDisplay.setPage(3);
                //   }
                  if(Process_stop_by_key1==1)
                  { 
                      sendDataFlag=0;
                      DwinDisplay.setPage(53);
                       
                                     
                  }
                  if(Process_stop_by_key1==2 ) //-----------------Exit process after pressing key1 2 times
                  {  
                      countDownStart=0;
                      Enter_Button=0;
                      Exit_Process=0;
                  }

                  if(Time_mode_Flag==1 && InF_mode==0 && (Temperature_After_Calibration>=(Setpoint-0.3)) && Soak_time_Once==0)//--------Soak time start,once actual temp reaches set temp.
                  {  
                      // Serial2.println("Once Soak ");
                      Soak_time_start_flag=1;
                      incrementTime=0;
                      Soak_time_Once=1;
                 }

    }
    // digitalWrite(pwm, LOW);//----------Overhead stirrer motor PWM
    // digitalWrite(relay,LOW);
    EEPROM.write(35, 0);
    digitalWrite(HEATER,LOW); 
    tickers.BUZZ_INTERVAL(2000);
    Process_Start_Flag=0;
    Exit_Process=0;

}

//*****************************************Setting Menu**********************************************//
void ProcessClass::Setting_menu()
{   
    if(Inside_Calibration_menu==0)
    {
              if(Knob_Single_Press_In_Settings) //--------------When press knob in setting menu
              {
                  switch (Setting_Menu)
                  {
                    case 0: //--------------Temperature Calibration
                              
                              if(Calibration_selection_flag==0)
                              { 
                                // Serial2.println("One ");
                                 sendDataFlag=0;
                                 DwinDisplay.setPage(18);
                              }
                              else if(Calibration_selection_flag==1)
                              { 
                                // Serial2.println("Two ");
                                 sendDataFlag=0;
                                 DwinDisplay.setPage(33);
                              }
                              break;
                    case 1:   //----------Recipe
                            sendDataFlag=0;
                            DwinDisplay.setPage(Receipe_cnt[Receipe]);
                            // DwinDisplay.Data_Arduino_to_Display_Pressure_Calb(Master_Pressure);
                            break;
                    case 2:  //----------RPM calibration
                              sendDataFlag=0;
                              DwinDisplay.setPage(23);
                              DwinDisplay.Data_Arduino_to_Display_RPM_Calb_current(0);
                              DwinDisplay.Data_Arduino_to_Display_RPM_Calb(Master_RPM);
                            break;
                    
                    case 3 : //---------------time mode
                              if(Time_mode_Flag==0)
                              {
                                  sendDataFlag=0;
                                  DwinDisplay.setPage(24);
                              }
                              else if(Time_mode_Flag==1)
                              {
                                  sendDataFlag=0;
                                  DwinDisplay.setPage(25);
                              }
                              
                              break;
                      case 4 : //--------------------Heat- slow/fast mode
                              if(Slow_Fast_Mode_Flag==0)
                              {
                                  sendDataFlag=0;
                                  DwinDisplay.setPage(26);
                              }
                              else
                              {
                                  sendDataFlag=0;
                                  DwinDisplay.setPage(27);
                              }
                              break;
                      case 5:
                             
                              if(Safe_Menu_Count==0)
                              {  
                                    sendDataFlag=0;
                                    DwinDisplay.setPage(90);
                                    DwinDisplay.Data_Arduino_to_Display_Internal_SAFE_TEMP(Safe_Temp[0]);
                                    DwinDisplay.Data_Arduino_to_Display_External_SAFE_TEMP(Safe_Temp[1]);
                                    DwinDisplay.Data_Arduino_to_Display_Vapour_SAFE_TEMP(Safe_Temp[2]);
                              }
                               if(Safe_Menu_Count==1)
                              {  
                                    sendDataFlag=0;
                                    DwinDisplay.setPage(91);
                                    DwinDisplay.Data_Arduino_to_Display_Internal_SAFE_TEMP(Safe_Temp[0]);
                                    DwinDisplay.Data_Arduino_to_Display_External_SAFE_TEMP(Safe_Temp[1]);
                                    DwinDisplay.Data_Arduino_to_Display_Vapour_SAFE_TEMP(Safe_Temp[2]);
                              }
                               if(Safe_Menu_Count==2)
                              {  
                                    sendDataFlag=0;
                                    DwinDisplay.setPage(92);
                                    DwinDisplay.Data_Arduino_to_Display_Internal_SAFE_TEMP(Safe_Temp[0]);
                                    DwinDisplay.Data_Arduino_to_Display_External_SAFE_TEMP(Safe_Temp[1]);
                                    DwinDisplay.Data_Arduino_to_Display_Vapour_SAFE_TEMP(Safe_Temp[2]);
                              }
                              break;
                    
                      case 6 : //--------------Auto Resume mode
                              if(Autoresume_Enable_Disable_Flag==0)
                              {
                                  sendDataFlag=0;
                                  DwinDisplay.setPage(29);
                              }
                              else
                              {
                                  sendDataFlag=0;
                                  DwinDisplay.setPage(30);
                              }
                              break;

                      default:
                              break;      
                
                  }
              }
              else
              {
                  switch (Setting_Menu)
                  {  
                    
                    case 0 : //---------Temp calb
                            sendDataFlag=0;
                            Cal2_Selection_Parameter=0;
                            DwinDisplay.setPage(10); 
                            break;
                    case 1 : //-----pressure calb
                            sendDataFlag=0;
                            DwinDisplay.setPage(11); 
                            break;
                    case 2 : //-------RPM calb
                            sendDataFlag=0;
                            DwinDisplay.setPage(12); 
                            break;
                    case 3 : //-----------Time mode
                            sendDataFlag=0;
                            DwinDisplay.setPage(13); 
                            break;
                    case 4 : //------------heat mode
                            sendDataFlag=0;
                            DwinDisplay.setPage(14); 
                            break;
                    case 5 : //------------Safe mode
                            sendDataFlag=0;
                            DwinDisplay.setPage(15); 
                            break;
                    case 6 : //-------------Auto resume
                            sendDataFlag=0;
                            DwinDisplay.setPage(16); 
                            break;
                      default:
                              break;
                  }
              }

    }
    //--------------------------------------------Calibartion Menu----------------------------------------------//
    if(Inside_Calibration_menu==1)
    {
              if(Calibration_selection_flag==0) //------------------Single point calibration
              {  

                    if(Knob_Single_Press_In_Calibration1)
                    { 
                        sendDataFlag=0;
                        DwinDisplay.setPage(32);

                    }
                    else 
                    {             
                                  Probe_Temp[0]=smoothed_KType_Temp;
                                  Probe_Temp[1]=Smoothed_PT1000_Temperature;
                                  sendDataFlag=0;
                                  DwinDisplay.setPage(31);
                                  DwinDisplay.Data_Arduino_to_Display_Cal1_Master_Temp(Calibration1_Value);
                                  DwinDisplay.Data_Arduino_to_Display_Cal1_Current_Temp(Probe_Temp[PT1000_Detection_Occured]);
                                  Cal1_Master_temperature_conversion();
                                  Error_Difference=Final_master_temp-Probe_Temp[PT1000_Detection_Occured]; 
                                  // Serial2.print("PT1000_Detection_Occured : ");
                                  //  Serial2.println(PT1000_Detection_Occured); 
                                  //  Serial2.print("Probe_Temp[PT1000_Detection_Occured] : ");
                                  //  Serial2.println(Probe_Temp[PT1000_Detection_Occured]); 
                                  //   Serial2.print("Final_master_temp : ");
                                  //  Serial2.println(Final_master_temp);  
                                  //  Serial2.print("Error_Difference : ");
                                  //  Serial2.println(Error_Difference);  
                                  if(Error_Difference>=0)
                                  {   
                                      Final_Error_Difference=int(Error_Difference*10);
                                      Calibration_1_plus_minus_EEPROM=0; 
                                       
                                  }
                                  else
                                  {   
                                      Final_Error_Difference=int(Error_Difference*(-10));
                                      Calibration_1_plus_minus_EEPROM=1;
                                    
                                  }
                                  // Serial2.print("Final_Error_Difference : ");
                                  // Serial2.println(Final_Error_Difference); 
                                  //  Serial2.print("Calibration_1_plus_minus_EEPROM : ");
                                  //  Serial2.println(Calibration_1_plus_minus_EEPROM);
                                  //  Serial2.println("*******************************************************");
                    }
              }
              else if(Calibration_selection_flag==1)
              { 
                       switch (Cal2_Selection_Parameter)  //----------Cal2 selection parameter
                        {
                              case 0 : //-------------------Enter Low set Temperature
                                      sendDataFlag=0;
                                      DwinDisplay.setPage(34);
                                      DwinDisplay.Data_Arduino_to_Display_Cal2_Low_Set_Temp(CAL2_Low_Set_temp);
                                      DwinDisplay.Data_Arduino_to_Display_Cal2_High_Set_Temp(CAL2_High_Set_temp);
                                      // Serial2.println("1");
                                      break;
                              case 1://-------------------Enter High set Temperature
                                      sendDataFlag=0;
                                      DwinDisplay.setPage(35);
                                      DwinDisplay.Data_Arduino_to_Display_Cal2_Low_Set_Temp(CAL2_Low_Set_temp);
                                      DwinDisplay.Data_Arduino_to_Display_Cal2_High_Set_Temp(CAL2_High_Set_temp);
                                      //  Serial2.println("2");
                                      break;
                              case 2://-------------------Low Heating
                                        digitalWrite(Process_LED,HIGH);
                                         if(PT1000_Detection_Occured==1)
                                         {
                                                EEPROM.write(15, CAL2_Low_Set_temp >> 8);//-----
                                                EEPROM.write(16, CAL2_Low_Set_temp & 0xFF);
                                                EEPROM.write(17, CAL2_High_Set_temp >> 8);//------
                                                EEPROM.write(18, CAL2_High_Set_temp & 0xFF);

                                         }
                                         if(PT1000_Detection_Occured==0)
                                         {
                                                EEPROM.write(23, CAL2_Low_Set_temp >> 8);//-----
                                                EEPROM.write(24, CAL2_Low_Set_temp & 0xFF);
                                                EEPROM.write(25, CAL2_High_Set_temp >> 8);//------
                                                EEPROM.write(26, CAL2_High_Set_temp & 0xFF);
                                                
                                         }
                                        incrementTime=0;
                                        countDownStart=1;
                                        setMin=0; 
                                        Current_HOUR = 0;
                                        Current_Min=0;
                                        InF_mode=1;
                                        Oncee_Cal2=1;
                                        Inprocess_Set_Temp_Save=1;
                                        Set_temp=CAL2_Low_Set_temp*10;
                                        SetPoint_for_Cal2=1;
                                        once_heater_PID=0;
                                        // Process.Setpoint_temperature_conversion();
                                        // Setpoint=Final_set_temperature+0.2;
                                        //  Setpoint=CAL2_Low_Set_temp;
                                        //  Serial2.println("cal222222222...");
                                        //  Serial2.print("Setpoint :");
                                        //  Serial2.println(Setpoint);
                                        //  Serial2.print("Set_temp :");
                                        //  Serial2.println(Set_temp);
                                        //  Serial2.print("Smoothed_PT1000_Temperature :");
                                        //  Serial2.println(Smoothed_PT1000_Temperature);
                                        //  while(0)
                                        // while(smoothed_KType_Temp<=CAL2_Low_Set_temp)
                                        SSR_cutoff_Reach_Count=0;
                                        SSR_Fail_check_Count=0;
                                        SSR_fail_In_Cal2_flag=1;
                                        while((Input<=CAL2_Low_Set_temp) && SSR_fail_In_Cal2_flag==1)
                                        {      
                                               sendDataFlag=0;
                                               DwinDisplay.setPage(109);
                                               tickers.Button_update();
                                               Encoder.Encoder2_increment();
                                               tickers.Encoder_Fast_Inc_Dec_update();
                                              //  DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(smoothed_KType_Temp);
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Set_Temp_Heating(CAL2_Low_Set_temp);
                                              if(PT1000_Detection_Occured==1)
                                              {
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(Smoothed_PT1000_Temperature);
                                              }
                                               if(PT1000_Detection_Occured==0)
                                              {
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(smoothed_KType_Temp);
                                              }
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_RPM(Set_speed);//Set_speed
                                              //  if(Final_Internal_Probe_Temp<=350)
                                              //   {  
                                                  //  Serial2.println("ON heater");
                                                  if( Oncee_Cal2)
                                                  // if(Slow_Fast_Mode_Flag==1 && Oncee_Cal2) //---------------------------fast heating
                                                  {  
                                                      
                                                        {
                                                              if(once_heater_PID == 0)//------------execute only once
                                                              {
                                                                    // myPID.SetOutputLimits(0, WindowSize);
                                                                    windowStartTime = millis();
                                                                    // Heater_PID_setpoint();//-----------final setpoint selection loop for temperature for adjustment
                                                                    //turn the PID on
                                                                    // myPID.SetMode(AUTOMATIC);
                                                                    once_heater_PID = 1;
                                                                    
                                                              } 
                                                                // if(Internal_Temp_Post_Calb <= (Setpoint*2.3))
                                                                // {

                                                                            if(Setpoint-0.2<=50)
                                                                            {
                                                                                  set_input_cmp_factor=12;
                                                                              
                                                                            }
                                                                            if(Setpoint-0.2>50 && Setpoint-0.2<=90)
                                                                            {
                                                                                  set_input_cmp_factor=10;
                                                                              
                                                                            }
                                                                            if(Setpoint-0.2>90)
                                                                            {
                                                                                  set_input_cmp_factor=12;
                                                                              
                                                                            }


                                                                            if((Setpoint - Input) > set_input_cmp_factor)
                                                                            {
                                                                              // myPID.SetTunings(kp_fast[PT1000_Detection_Occured],ki_fast[PT1000_Detection_Occured] , kd_fast[PT1000_Detection_Occured]); 
                                                                              
                                                                            }
                                                                            else if((Setpoint - Input) <= set_input_cmp_factor)
                                                                            {
                                                                              // myPID.SetTunings(consKp_fast[PT1000_Detection_Occured], consKi_fast[PT1000_Detection_Occured], consKd_fast[PT1000_Detection_Occured]); 
                                                                              
                                                                            }
                                                                                  // myPID.Compute();
                                                                                  if (millis() - windowStartTime > WindowSize)
                                                                                  { //time to shift the Relay Window
                                                                                    windowStartTime += WindowSize;
                                                                                  }
                                                                                  if (Output < millis() - windowStartTime) digitalWrite(HEATER, LOW);
                                                                                  else digitalWrite(HEATER, HIGH);
                                                                    // }
                                                                    
                                                          
                                                        }
                                                        
                                                        once_heater_PID=0;
                                                        Oncee_Cal2=0;
                                                  } 

                                                //  Serial2.print("Setpoint :");
                                                //  Serial2.println(Setpoint);
                                              //  Serial2.println("cal2 loop....."); 
                                              // Serial2.print("Smoothed_PT1000_Temperature :");
                                              // Serial2.println(Smoothed_PT1000_Temperature);
                                              // Serial2.print("smoothed_KType_Temp :");
                                              // Serial2.println(smoothed_KType_Temp);
                                              tickers.SSR_cutoff_Reach_ticker_update();
                                              if(SSR_cutoff_Reach_Count>=4)
                                              {
                                                  // Serial2.println("SSR_Failed :");
                                                  digitalWrite(relay,LOW);//---------------relay ON
                                                  SSR_Failure_Flag=1;
                                                  countDownStart=0;
                                                  mode=0;
                                                  SSR_fail_In_Cal2_flag=0;//------------Process exit
                                              }
                                              if(Final_Internal_Probe_Temp>=650 && SSR_cuttoff_reached_Flag==0) //----------------Safety relay logic, If internal probe temp goes beyong 400C 
                                              { 
                                                    // Serial2.println("SSR_cuttoff_reached_Flag :");
                                                    tickers.SSR_cutoff_Reach_ticker_start();
                                                    SSR_cuttoff_reached_Flag=1;
                                                  
                                              }
                                              
                                              HeaterPID.Heater_PID_Function();
                                              BLDC.PID_motor_set();
                                              BLDC.Feedback_update();
                                              tickers.Motor_slow_stop_tick_update();
                                              
                                              TimerUpdate.Time_calutation_tick_UPDATE();
                                              tickers.In_Process_Ticker_Update();
                                              RTD_Sensor.PT100_Probe1_Temperature_Reading_update();
                                              RTD_Sensor.PT1000_Temperature_Reading_update();
                                              KType_sensor.Internal_Probe_Temperature();
                                              KType_sensor.KType_Reading_Update();
                                              tickers.Internal_probe_short_open_ticker_update();
                                              //  Serial2.println("5");

                                               Process.Temp_readings_ticker_update();
                                        }
                                        CAL2_maintain_flag=1;
                                        Cal2_Selection_Parameter++;
                                        break;
                              case 3://-------------------Low Temperature maintain
                                      // Serial2.print("Low maintain ");
                                       incrementTime=0;
                                       Time_mode_Flag=0;
                                       countDownStart=1;
                                       setMin=30;
                                       InF_mode=0;
                                       Current_Min=30;
                                       SSR_cuttoff_reached_Flag=0;
                                       SSR_cutoff_Reach_Count=0;
                                       SSR_Fail_check_Count=0;
                                       SSR_fail_In_Cal2_flag=1;
                                       while(CAL2_maintain_flag && SSR_fail_In_Cal2_flag==1)
                                       {
                                              sendDataFlag=0;
                                              DwinDisplay.setPage(111);  
                                              DwinDisplay.Data_Arduino_to_Display_Cal2_Hour(0);
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Set_Temp_Heating(CAL2_Low_Set_temp);
                                              if(PT1000_Detection_Occured==1)
                                              {
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(Smoothed_PT1000_Temperature);
                                              }
                                               if(PT1000_Detection_Occured==0)
                                              {
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(smoothed_KType_Temp);
                                              }
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_RPM(Set_speed);//Set_speed
                                              DwinDisplay.Data_Arduino_to_Display_Cal2_Min(Current_Min);
                                              tickers.Button_update(); 

                                               tickers.SSR_cutoff_Reach_ticker_update();
                                              if(SSR_cutoff_Reach_Count>=4)
                                              {
                                                  // Serial2.println("SSR_Failed :");
                                                  digitalWrite(relay,LOW);//---------------relay ON
                                                  SSR_Failure_Flag=1;
                                                  countDownStart=0;
                                                  mode=0;
                                                  SSR_fail_In_Cal2_flag=0;//------------Process exit
                                              }
                                              if(Final_Internal_Probe_Temp>=650 && SSR_cuttoff_reached_Flag==0) //----------------Safety relay logic, If internal probe temp goes beyong 400C 
                                              { 
                                                    // Serial2.println("SSR_cuttoff_reached_Flag :");
                                                    tickers.SSR_cutoff_Reach_ticker_start();
                                                    SSR_cuttoff_reached_Flag=1;
                                                  
                                              }
                                              Encoder.Encoder2_increment();
                                               tickers.Encoder_Fast_Inc_Dec_update();
                                              HeaterPID.Heater_PID_Function();
                                              BLDC.PID_motor_set();
                                              BLDC.Feedback_update();
                                              tickers.Motor_slow_stop_tick_update();

                                              TimerUpdate.Time_calutation_tick_UPDATE();
                                              tickers.In_Process_Ticker_Update();
                                              RTD_Sensor.PT100_Probe1_Temperature_Reading_update();
                                              RTD_Sensor.PT1000_Temperature_Reading_update();
                                              KType_sensor.Internal_Probe_Temperature();
                                              KType_sensor.KType_Reading_Update();
                                              tickers.Internal_probe_short_open_ticker_update();   

                                               Process.Temp_readings_ticker_update();                                                                                                                                                            
                                      }
                                      digitalWrite(Process_LED,LOW);
                                      SSR_fail_In_Cal2_flag=0;
                                      if(Single_Click_In_Cal2_maintain==0)
                                          Cal2_Selection_Parameter++;

                                    break;
                              case 4:      //----------------------Entering master LOW Temp 
                                             sendDataFlag=0;
                                             DwinDisplay.setPage(38);
                                             Single_Click_In_Cal2_maintain=0;
                                             DwinDisplay.Data_Arduino_to_Display_Cal2_Master_Temp(CAL2_Low_Master);

                                      break;
                              case 5://-------------------High temperature Heating
                                      //  while(0<CAL2_High_Set_temp)
                                        digitalWrite(Process_LED,HIGH);
                                        incrementTime=0;
                                        countDownStart=1;
                                        setMin=0; 
                                        Current_HOUR = 0;
                                        Current_Min=0;
                                        InF_mode=1;
                                        Inprocess_Set_Temp_Save=1;
                                        Set_temp=CAL2_High_Set_temp*10;
                                        once_heater_PID=0;
                                        SSR_cuttoff_reached_Flag=0;
                                        SSR_cutoff_Reach_Count=0;
                                        SSR_Fail_check_Count=0;
                                        // Setpoint=CAL2_High_Set_temp;
                                        // while(smoothed_KType_Temp<=CAL2_High_Set_temp)
                                        SSR_fail_In_Cal2_flag=1;
                                        while((Input<=CAL2_High_Set_temp) && SSR_fail_In_Cal2_flag==1)
                                        {
                                             sendDataFlag=0;
                                             DwinDisplay.setPage(110);
                                              tickers.SSR_cutoff_Reach_ticker_update();
                                              if(SSR_cutoff_Reach_Count>=4)
                                              {
                                                  // Serial2.println("SSR_Failed :");
                                                  digitalWrite(relay,LOW);//---------------relay ON
                                                  SSR_Failure_Flag=1;
                                                  countDownStart=0;
                                                  mode=0;
                                                  SSR_fail_In_Cal2_flag=0;//------------Process exit
                                              }
                                              if(Final_Internal_Probe_Temp>=650 && SSR_cuttoff_reached_Flag==0) //----------------Safety relay logic, If internal probe temp goes beyong 400C 
                                              { 
                                                    // Serial2.println("SSR_cuttoff_reached_Flag :");
                                                    tickers.SSR_cutoff_Reach_ticker_start();
                                                    SSR_cuttoff_reached_Flag=1;
                                                  
                                              }
                                             tickers.Button_update(); 
                                             Encoder.Encoder2_increment();
                                             tickers.Encoder_Fast_Inc_Dec_update();
                                              // DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(smoothed_KType_Temp);
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Set_Temp_Heating(CAL2_High_Set_temp);
                                               if(PT1000_Detection_Occured==1)
                                              {
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(Smoothed_PT1000_Temperature);
                                              }
                                              if(PT1000_Detection_Occured==0)
                                              {
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(smoothed_KType_Temp);
                                              }
                                             DwinDisplay.Data_Arduino_to_Display_Cal2_RPM(Set_speed);
                                             HeaterPID.Heater_PID_Function();
                                             BLDC.PID_motor_set();
                                              BLDC.Feedback_update();
                                              tickers.Motor_slow_stop_tick_update();
                                             
                                              TimerUpdate.Time_calutation_tick_UPDATE();
                                              tickers.In_Process_Ticker_Update();
                                              RTD_Sensor.PT100_Probe1_Temperature_Reading_update();
                                              RTD_Sensor.PT1000_Temperature_Reading_update();
                                              KType_sensor.Internal_Probe_Temperature();
                                              KType_sensor.KType_Reading_Update();
                                              tickers.Internal_probe_short_open_ticker_update();
                                              //  Serial2.print("Setpoint :");
                                              //    Serial2.println(Setpoint);

                                               Process.Temp_readings_ticker_update();
                                       }
                                       CAL2_maintain_flag=1;
                                       Cal2_Selection_Parameter++;

                                     break;
                              case 6://-------------------High Temperature maintain
                                       InF_mode=0;
                                       Time_mode_Flag=0;
                                       incrementTime=0;
                                       countDownStart=1;
                                       setMin=30;
                                       Current_Min=30;
                                       SSR_cuttoff_reached_Flag=0;
                                       SSR_cutoff_Reach_Count=0;
                                       SSR_Fail_check_Count=0;
                                       SSR_fail_In_Cal2_flag=1;
                                       while(CAL2_maintain_flag && SSR_fail_In_Cal2_flag==1)
                                       {
                                              sendDataFlag=0;
                                              DwinDisplay.setPage(112);
                                              tickers.SSR_cutoff_Reach_ticker_update();
                                              if(SSR_cutoff_Reach_Count>=4)
                                              {
                                                  // Serial2.println("SSR_Failed :");
                                                  digitalWrite(relay,LOW);//---------------relay ON
                                                  SSR_Failure_Flag=1;
                                                  countDownStart=0;
                                                  mode=0;
                                                  SSR_fail_In_Cal2_flag=0;//------------Process exit
                                              }
                                              if(Final_Internal_Probe_Temp>=650 && SSR_cuttoff_reached_Flag==0) //----------------Safety relay logic, If internal probe temp goes beyong 400C 
                                              { 
                                                    // Serial2.println("SSR_cuttoff_reached_Flag :");
                                                    tickers.SSR_cutoff_Reach_ticker_start();
                                                    SSR_cuttoff_reached_Flag=1;
                                                  
                                              }

                                              HeaterPID.Heater_PID_Function();
                                              BLDC.PID_motor_set();
                                              BLDC.Feedback_update();
                                              tickers.Motor_slow_stop_tick_update();
                                              
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Set_Temp_Heating(CAL2_High_Set_temp);
                                              if(PT1000_Detection_Occured==1)
                                              {
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(Smoothed_PT1000_Temperature);
                                              }
                                               if(PT1000_Detection_Occured==0)
                                              {
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_Current_Temp(smoothed_KType_Temp);
                                              }
                                               DwinDisplay.Data_Arduino_to_Display_Cal2_RPM(Set_speed);//Set_speed
                                              DwinDisplay.Data_Arduino_to_Display_Cal2_Hour(0);
                                              DwinDisplay.Data_Arduino_to_Display_Cal2_Min(Current_Min);
                                              tickers.Button_update(); 
                                              Encoder.Encoder2_increment();
                                               tickers.Encoder_Fast_Inc_Dec_update();
                                              TimerUpdate.Time_calutation_tick_UPDATE();
                                              tickers.In_Process_Ticker_Update();
                                              RTD_Sensor.PT100_Probe1_Temperature_Reading_update();
                                              RTD_Sensor.PT1000_Temperature_Reading_update();
                                              KType_sensor.Internal_Probe_Temperature();
                                              KType_sensor.KType_Reading_Update();
                                              tickers.Internal_probe_short_open_ticker_update(); 

                                              Process.Temp_readings_ticker_update();
                                       }
                                       
                                        digitalWrite(Process_LED,LOW);
                                        SSR_fail_In_Cal2_flag=0;
                                        if(Set_speed!=0)
                                        {
                                            Set_speed=0;
                                            Stop_pwm=235;
                                            Motor_Stop_Flagg=1;
                                            tickers.Motor_slow_stop_tick_start();
                                        }
                                        if(Single_Click_In_Cal2_maintain==0)
                                                   Cal2_Selection_Parameter++;

                                    break;
                              case 7:      //----------------------Entering master High Temp 
                                         Single_Click_In_Cal2_maintain=0;
                                         SetPoint_for_Cal2=0;
                                         sendDataFlag=0;
                                         DwinDisplay.setPage(41);
                                         DwinDisplay.Data_Arduino_to_Display_Cal2_Master_Temp(CAL2_High_Master);

                                      break;
                              case 8:      //-----------------------Calibration 2 save mode
                                            sendDataFlag=0;
                                             DwinDisplay.setPage(42);
                                          
                                     break;
                              default:
                                    break;

                        }

              }


    }

}               

void  ProcessClass:: Setpoint_temperature_conversion()
{       
        set_temperature_num=Set_temp/10;
        set_temperature_decimal=Set_temp%10;
        String integerString_setTemp = String(set_temperature_num);

        // Convert the decimal to a string with a specified number of decimal places
        String decimalString_setTemp = String(set_temperature_decimal); // Use 1 decimal place

        // Concatenate the integer and decimal strings together
        String concatenatedString_setTemp = integerString_setTemp + "." + decimalString_setTemp;
        Final_set_temperature = atof(concatenatedString_setTemp.c_str());

} 

//--------------------------------------------------Calibartion functions--------------------------------------------------------------//
void  ProcessClass:: Temp_Reading_After_Calibration()
{ 
     probe_selection[0]=smoothed_KType_Temp;
     probe_selection[1]=Smoothed_PT1000_Temperature;
  
     if(!Calibration_selection_flag) //-------------One point calibration
     {  
          //  Serial2.println("Cal11111...........");
          if(PT1000_Detection_Occured==0)
          {
              Calibration_1_plus_minus_EEPROM=EEPROM.read(13);
              Final_Error_Difference=EEPROM.read(14);
              //  Serial2.println("Internal");
              
          } 
          if(PT1000_Detection_Occured==1)
          {
              // Final_Error_Difference= (EEPROM.read(12) << 8) + EEPROM.read(13);
              Calibration_1_plus_minus_EEPROM=EEPROM.read(11);
              Final_Error_Difference=EEPROM.read(12);
              //  Serial2.println("External");
              
          } 
            //  Serial2.print("Calibration_1_plus_minus_EEPROM : ");
            //  Serial2.println(Calibration_1_plus_minus_EEPROM);
            //  Serial2.print("Final_Error_Difference : ");
            //  Serial2.println(Final_Error_Difference);
         
            cal1_error_num= Final_Error_Difference/10;
            cal1_error_decimal=Final_Error_Difference%10;
            String cal1_error_integerString= String(cal1_error_num);
            // Convert the decimal to a string with a specified number of decimal places
            String  cal1_error_decimalString = String(cal1_error_decimal); // Use 1 decimal place
            // Concatenate the integer and decimal strings together
            String  cal1_erorr_concatenatedString= cal1_error_integerString + "." + cal1_error_decimalString;
            Final_calibration1_error_final[PT1000_Detection_Occured] = atof(cal1_erorr_concatenatedString.c_str()); 
            if(Calibration_1_plus_minus_EEPROM==0)
            {
              Temperature_After_Calibration= probe_selection[PT1000_Detection_Occured]+Final_calibration1_error_final[PT1000_Detection_Occured];
              Internal_Temp_Post_Calb=K_Type_emaFilter_Output+Final_calibration1_error_final[0];
              
              // Serial2.println("plus");  
            }
            else if(Calibration_1_plus_minus_EEPROM==1)
            {
              Temperature_After_Calibration= probe_selection[PT1000_Detection_Occured]-Final_calibration1_error_final[PT1000_Detection_Occured];
              Internal_Temp_Post_Calb=K_Type_emaFilter_Output-Final_calibration1_error_final[0];
              // Serial2.println("minus");  
            }
             
                 
             
  
            //  Serial2.print("Temperature_After_Calibration : ");
            //  Serial2.println(Temperature_After_Calibration);
            //  Serial2.print("Final_calibration1_error_final[PT1000_Detection_Occured] : ");
            //  Serial2.println(Final_calibration1_error_final[PT1000_Detection_Occured]);
            //   Serial2.println("*****************************************************");  
            
         
    }
    else if(Calibration_selection_flag==1)//-----------Two point calibration
    {      

      //  Serial.println("calibration 2.............");
        if(PT1000_Detection_Occured==1)
        {
            EEPROM_cal2_Low_Master = (EEPROM.read(19) << 8) + EEPROM.read(20);  //--------------Master
            EEPROM_cal2_High_Master=(EEPROM.read(21) << 8) + EEPROM.read(22);

            EEPROM_calibration2_LOW_value = (EEPROM.read(15) << 8) + EEPROM.read(16);//----------Set
            EEPROM_calibration2_High_value=(EEPROM.read(17) << 8) + EEPROM.read(18);
        }
        if(PT1000_Detection_Occured==0)
        {
            EEPROM_cal2_Low_Master = (EEPROM.read(27) << 8) + EEPROM.read(28);  //--------------Master
            EEPROM_cal2_High_Master=(EEPROM.read(29) << 8) + EEPROM.read(30);

            EEPROM_calibration2_LOW_value = (EEPROM.read(23) << 8) + EEPROM.read(24);//----------Set
            EEPROM_calibration2_High_value=(EEPROM.read(25) << 8) + EEPROM.read(26);
        }
     

        int cal2_Low[2]={};
        cal2_Low[PT1000_Detection_Occured]=EEPROM_cal2_Low_Master;        
        
        cal2_Low_temperature_num= cal2_Low[PT1000_Detection_Occured]/10; 
        cal2_Low_temperature_decimal=cal2_Low[PT1000_Detection_Occured]%10;
        String cal2_Low_integerString= String(cal2_Low_temperature_num);

        // Convert the decimal to a string with a specified number of decimal places
        String  cal2_Low_decimalString = String(cal2_Low_temperature_decimal); // Use 1 decimal place

        // Concatenate the integer and decimal strings together
        String  cal2_Low_concatenatedString= cal2_Low_integerString + "." + cal2_Low_decimalString;
        Final_calibration2_Low_Master[PT1000_Detection_Occured] = atof(cal2_Low_concatenatedString.c_str());
        
         int cal2_High[2]={};
         cal2_High[PT1000_Detection_Occured]=EEPROM_cal2_High_Master;        
        
        cal2_High_temperature_num= cal2_High[PT1000_Detection_Occured]/10;  
        cal2_High_temperature_decimal=cal2_High[PT1000_Detection_Occured]%10;
        String cal2_High_integerString= String(cal2_High_temperature_num);

        // Convert the decimal to a string with a specified number of decimal places
        String  cal2_High_decimalString = String(cal2_High_temperature_decimal); // Use 1 decimal place

        // Concatenate the integer and decimal strings together
        String  cal2_High_concatenatedString= cal2_High_integerString + "." + cal2_High_decimalString;
        Final_calibration2_High_Master[PT1000_Detection_Occured] = atof(cal2_High_concatenatedString.c_str());
 
        float Cal2_Low_Raw_Temp_For_Conv, Cal2_High_Raw_Temp_For_Conv, Master_Low_Temp_For_Conv, Master_High_Temp_For_Conv;
        // Cal2_Low_Raw_Temp_For_Conv  = Final_calibration2_Low_SET[probe_detection]; //calibration2_LOW_value ;
        // Cal2_High_Raw_Temp_For_Conv = Final_calibration2_High_SET[probe_detection];  //calibration2_High_value; 
        Cal2_Low_Raw_Temp_For_Conv  = EEPROM_calibration2_LOW_value; //calibration2_LOW_value ;
        Cal2_High_Raw_Temp_For_Conv = EEPROM_calibration2_High_value;   
        Master_Low_Temp_For_Conv    = Final_calibration2_Low_Master[PT1000_Detection_Occured];
        Master_High_Temp_For_Conv   = Final_calibration2_High_Master[PT1000_Detection_Occured];  

           //    Serial2.print("PT1000_Detection_Occured :"); 
      // Serial2.println(PT1000_Detection_Occured);
      //    Serial2.print("Cal2_Low_Raw_Temp_For_Conv :"); 
      // Serial2.println(Cal2_Low_Raw_Temp_For_Conv);
      //   Serial2.print("Cal2_High_Raw_Temp_For_Conv :"); 
      // Serial2.println(Cal2_High_Raw_Temp_For_Conv);
      //   Serial2.print("Master_Low_Temp_For_Conv :"); 
      // Serial2.println(Master_Low_Temp_For_Conv);
      //   Serial2.print("Master_High_Temp_For_Conv :"); 
      // Serial2.println(Master_High_Temp_For_Conv);
      
              
   //   // Temp_after_error_set[probe_detection] = mapfloat( probe_selection[probe_detection], Cal2_Low_Raw_Temp_For_Conv, Cal2_High_Raw_Temp_For_Conv, Master_Low_Temp_For_Conv,  Master_High_Temp_For_Conv);
    
     Final_temp_after_cal2[PT1000_Detection_Occured] = mapfloat(probe_selection[PT1000_Detection_Occured], Cal2_Low_Raw_Temp_For_Conv, Cal2_High_Raw_Temp_For_Conv, Master_Low_Temp_For_Conv,  Master_High_Temp_For_Conv);
    
              if(PT1000_Detection_Occured==0)
              {
                 Temperature_After_Calibration= Final_temp_after_cal2[PT1000_Detection_Occured];
                 Internal_Temp_Post_Calb = mapfloat(K_Type_emaFilter_Output, Cal2_Low_Raw_Temp_For_Conv, Cal2_High_Raw_Temp_For_Conv, Master_Low_Temp_For_Conv,  Master_High_Temp_For_Conv);
                  // Temperature_After_Calibration=smoothed_KType_Temp;
                  // Internal_Temp_Post_Calb=K_Type_emaFilter_Output;
                  // Serial2.print("Internal Inp :");
                  // Serial2.println(Temperature_After_Calibration);
                  //  Serial2.print("Internal_Temp_Post_Calb :");
                  // Serial2.println(Internal_Temp_Post_Calb);
              }
              if(PT1000_Detection_Occured==1)
              {
                   Temperature_After_Calibration=Final_temp_after_cal2[PT1000_Detection_Occured];
                   Internal_Temp_Post_Calb=K_Type_emaFilter_Output;
                  //  Serial2.print("Ext Inp :");
                  // Serial2.println(Temperature_After_Calibration);
              }

      // Serial2.print("PT1000_Detection_Occured : "); 
      // Serial2.println(PT1000_Detection_Occured);
      // Serial2.print("probe_selection[PT1000_Detection_Occured] : "); 
      // Serial2.println(probe_selection[PT1000_Detection_Occured]);
      // Serial2.print("Final_temp_after_cal2[probe_detection] : "); 
      // Serial2.println(Final_temp_after_cal2[PT1000_Detection_Occured]);
      // Serial2.println("************************************************"); 

  }
 
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void  Cal1_Master_temperature_conversion() //--------------Master temp float conersion
{       
        master_temp_num=Calibration1_Value/10;//----------integer part
        master_temp_decimal=Calibration1_Value%10;//----------fractional part
        String integerString_mater_temp = String(master_temp_num);//-----------integer to string

        // Convert the decimal to a string with a specified number of decimal places
        String decimalString_mater_temp = String(master_temp_decimal); //----------decimal to string

        // Concatenate the integer and decimal strings together
        String concatenatedString_mater_temp = integerString_mater_temp + "." + decimalString_mater_temp;
        Final_master_temp = atof(concatenatedString_mater_temp.c_str()); //--------strig to float Master Temp

        
}

void Temp_Value_for_Graph()
{
   Graph_Temp_update_Flag++;
   Graph_Time_update_Flag++;
  if (Graph_Temp_update_Flag == 1)
  {
    if(PT1000_Detection_Occured==0)
    {
         DwinDisplay.Data_to_Display_graph(Internal_Temp_Post_Calb);
      // DwinDisplay.Data_to_Display_graph(25);
    }
    if(PT1000_Detection_Occured==1)
    {
         DwinDisplay.Data_to_Display_graph(Smoothed_PT1000_Temperature);
      
    }
    Graph_Temp_update_Flag = 0;
  }
  if (Graph_Time_update_Flag == 60)
  {      
        TC++;
        if(TC>999)
        {
          TC=0;
        }
        // DwinDisplay.Data_to_Display_Time_graph(5);
        Graph_Time_update_Flag = 0;
  }
}


void ProcessClass::Temp_readings_ticker_update() 
{
 Temp_readings_ticker.update();
}

ProcessClass Process = ProcessClass();