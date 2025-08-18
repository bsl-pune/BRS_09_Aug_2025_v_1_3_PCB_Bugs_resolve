//*****************************BRS(TFT display) v.1.0 code*****************************************************//
/*
//Project Description:BRS
//Dual Encoders
//TFT Display
//Escape & Set keys
//LED Indications
//Integrated relay circuit for enhanced safety features.
//Easy single step Start of Process.
//Easy single step Process Termination.
//In-Process Set Parameter Adjustment.
//Setting Menus: 1)Single Point Calibration
                 2)Probe/Energy regulator mode(default:Probe)
                 3)Safe(temperature) mode(default:External->170C, Internal->320C)
                 4)Slow/Fast heating mode(default:Slow)
                 5)Time Process/Soak/Diable mode (default:Disable)
                 6)Autorestart Enable/disable mode (default:disable)
                 7)Speed sensor enable/disable mode (default:enable)
                 8)Internal probe safety mode (default:320C)
*/

#include "ext_var.h" 
#define enSW 17
#define KEY1 14
#define KEY2 8

OneButton button0(enSW, true);
OneButton key1(KEY1, true);
OneButton key2(KEY2, true);
//************************************Functions declaration*********************************************//
void Single_Click();
void longPressStart1();
void longPressStop1();
void longPress1();
//************************************Global variables declaration**************************************//
//-----------------------version display-----------------------------------//
bool stopVerDisplay=1;
bool sendDataFlag = 0;
//---------------------------Long press variables-------------------------------//
int inc_time = 0;
int chk_time = 0;
//-----------------------Key1 & key2 variables-----------------------------//
int Process_stop_by_key1=0;

bool RPM_read = 1;
void Time_rpm();
Ticker rpm_time(Time_rpm, 1000, 0, MILLIS);

void Serial_read_func();
Ticker Serial_read_func_tick(Serial_read_func, 15000, 0);

void Serial_read_func()
{  
  //  Serial.print("Ext Probe Temp: ");
  //  Serial.println(Smoothed_Probe1_Temp);
  //  Serial.print("     \t");
  //  Serial.print(" Int Probe Temp: ");
  //  Serial.println(Internal_Probe_Temp_post_cal);
}

void setup() 
{
  // put your setup code here, to run once:
    Serial.begin(115200);
    Serial2.swap(1);
    Serial2.pins(38, 39);
    Serial2.begin(9600);

    // Serial.begin(9600);
    // Serial_read_func_tick.start();
    Encoder.SETUP();
    KType_sensor.KType_setup();
    RTD_Sensor.RTDSetup();
    Process.PROCESS_SETUP();
    TimerUpdate.TimerUpdate_SETUP();
    ProbeDetection.SetupProbeDetection();
    tickers.tickers_SETUP();
    AlertMsg.AlertMsg_SetUp();
    HeaterPID.HeaterPID_SETUP();
    BLDC.Motor_SETUP();
    TimerUpdate.Time_calutation_tick_START();

    pinMode(enSW, INPUT_PULLUP); 
    pinMode(KEY1, INPUT_PULLUP); 
    pinMode(KEY2, INPUT_PULLUP); 
    button0.attachClick(Single_Click);
    button0.attachLongPressStart(longPressStart1);
    button0.attachLongPressStop(longPressStop1);
    button0.attachDuringLongPress(longPress1);

    key1.attachClick(key1_Single_Click);    //----------ESC/Exit button 
    key2.attachClick(key2_Single_Click);   //---------To show set temp and set time parameter
    key2.attachLongPressStart(ESC_key_LongPress);
   
    attachInterrupt(digitalPinToInterrupt(feedback), interrupt, RISING);
    rpm_time.start();

    
    
}

void loop() 
{  
    Process.Temp_readings_ticker_update();
    // Serial_read_func_tick.update();
    //  Serial2.println("loop........");
    Process.Temp_Reading_After_Calibration();
    RTD_Sensor.PT100_Probe1_Temperature_Reading_update();
    RTD_Sensor.PT1000_Temperature_Reading_update();
    KType_sensor.KType_Reading_Update();
    KType_sensor.Internal_Probe_Temperature();
    Encoder.encode_increment();//-----go to increment and decrement loop
    Encoder.Encoder2_increment();
    ProbeDetection.PT100_check_update(); 
    ProbeDetection.PT1000_check_update();
    tickers.Motor_slow_stop_tick_update();
    // tickers.initial_temp_inc_check_ticker_update();

    tickers.Ramp_ticker_update();
    BLDC.Overhead_Motor_check_update();
    tickers.Calibration_save_ticker_update();
    // BLDC.PID_motor_set();
    // BLDC.PID_Overhead_Stirrer_Motor();
    if(Motor_Stop_During_OHS_Interuption_Flag==1)
        BLDC.Motor_Stop_During_OHS_Interuption();
    //  if(Overhead_Motor_connected_Flag==0)
    //      BLDC.PID_motor_set();
    //  if(Overhead_Motor_connected_Flag==1)
    //      BLDC.PID_Overhead_Stirrer_Motor();

    BLDC.Feedback_update();
    tickers.Int_Motor_Spd_control_tick_update();
                 if(initial_temp_inc_check_ONCE==0)  
                  { 
                    // Serial2.println("ssr 0:");

                    Initial_temp=Final_Internal_Probe_Temp;
                    initial_temp_inc_check_count=0;
                    tickers.initial_temp_inc_check_ticker_start();
                    initial_temp_inc_check_ONCE=1;
                  }
                  // if(initial_temp_inc_check_count>=3 || Final_Internal_Probe_Temp>=400) //-------------If temp contuinousy increases ,show 'triac fail'
                  if(initial_temp_inc_check_count>=3)
                  {   
                      // Serial2.println("ssr 1:");
                      digitalWrite( HEATER , LOW);
                      digitalWrite(relay,LOW);
                      tickers.initial_temp_inc_check_ticker_stop(); 
                      SSR_Failure_Flag=1;
                      mode=0;
                  }
    
    // Serial2.print("mode :");
    // Serial2.println(mode);
    if(mode==0)  //-----------------Software version & temp probe status mode
    { 
               
        if(stopVerDisplay)   //-----------------To display       
        {    
            sendDataFlag=0;
            tickers.VersionDisplay_update();
            DwinDisplay.setPage(0);
            // DwinDisplay.setPage(87);
            tickers.Internal_probe_short_open_ticker_start();
            //  Serial2.println("Set up");
           
        } 
        // else if(Probe_Error_Flag==1 || PT1000_Not_Detected_Flag==1)//------------------K-type probe error
        else if(Probe_Error_Flag==1)//------------------K-type probe error
        {
          //  Serial2.println("Probe error dispaly");
           digitalWrite(Set_LED,LOW);
           digitalWrite(Process_LED,LOW);
           digitalWrite(pwm, HIGH);
           digitalWrite(pwm_Overhead_Motor, LOW);
           sendDataFlag=0;
           
           if(toggle==0)
           {
                digitalWrite(BUZZER, LOW); 
                DwinDisplay.setPage(69);
           }
           else
           {
                 digitalWrite(BUZZER, HIGH); 
                 DwinDisplay.setPage(50);
           }
        }
         else if(SSR_Failure_Flag==1)//------------------K-type probe error
        {
          //  Serial2.println("SSR fail");
           digitalWrite(Set_LED,LOW);
           digitalWrite(Process_LED,LOW);
           digitalWrite(pwm, HIGH);
           digitalWrite(pwm_Overhead_Motor, LOW);
           sendDataFlag=0;
           
           if(toggle==0)
           {
                digitalWrite(BUZZER, LOW); 
                DwinDisplay.setPage(70);
           }
           else
           {
                 digitalWrite(BUZZER, HIGH); 
                 DwinDisplay.setPage(51);
           }
        }
    }
    if(mode==1) //-------------Set parameter mode
    {        
            Process.set_display();
    }
    if(mode==2)  //-------------Setting mode
    {      
     
           Process.Setting_menu();
    }

    if(Receipe_Mode==0) //----------------Not in recipe
    {
          if(Overhead_Motor_connected_Flag==0)
               BLDC.PID_motor_set();
          if(Overhead_Motor_connected_Flag==1)
               BLDC.PID_Overhead_Stirrer_Motor();
    }
    if(Receipe_Mode==1 && Motor_stop_In_Recipe==1)
    {
          BLDC.Motor_Stop_During_OHS_Interuption();
    }
    tickers.Button_update();
    tickers.LongPress7sec_update();
    tickers.toggle_display_update();
    tickers.LongPress7sec_update();
    tickers.Encoder_Fast_Inc_Dec_update();
    tickers.Internal_probe_short_open_ticker_update();
    tickers.PT1000_Not_Detected_ticker_update();
}

void Single_Click()
{ 
  if(SSR_Failure_Flag==0)
  { 
      sendDataFlag=0;
      if(mode==1)  //---------------SET parameters(Temp,Time) mode
      { 
        if(Receipe_Mode==0)
        {
            Enter_Button++;
            if(Enter_Button>=4) //-----------process start
            {  
                
              Enter_Button=4;
          
            }
        }
        if(Receipe_Mode==1)
        {
          // Receipe_Step
          // Receipe_Parameter
       
          if(!Knob_Single_Press_In_Receipe_start)
          {
              Enter_Button=1;
              Knob_Single_Press_In_Receipe_start=1;
              //  Serial2.println("1");
          }
          else
          {
                
                if(Receipe_Step!=6)
                {   
                    //  Serial2.println("vvvv");
                    Enter_Button++;
                    if(Enter_Button>=4) 
                    {   

                        EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step],   Receipe_Set_Temp[Receipe][Receipe_Step] >> 8); //--------Internal safe Temperature
                        EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+1, Receipe_Set_Temp[Receipe][Receipe_Step] & 0xFF);
                        EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+2, Receipe_Set_Hour[Receipe][Receipe_Step]);
                        EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+3, Receipe_Set_Min[Receipe][Receipe_Step]);
                        EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+4, Receipe_Set_RPM[Receipe][Receipe_Step] >> 8); //--------Internal safe Temperature
                        EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+5, Receipe_Set_RPM[Receipe][Receipe_Step] & 0xFF);
                        Receipe_Step++;
                        Set_speed=Receipe_Set_RPM[Receipe][Receipe_Step];
                        Enter_Button=1;
                  
                    }
                }
                if(Receipe_Step==6)
                { 
                    // Serial2.println("step done");
                    Process_start_stop_Rcp_step=6;
                    Enter_Button=4;
                }

          }

        }
          
      }
     
      if(mode==2)
      {  
          if(Inside_Calibration_menu==0)
          {
                  if(!Knob_Single_Press_In_Settings) //-------------single click to get in to the specific mode
                    {
                        Knob_Single_Press_In_Settings=1;
                      
                    }
                    else //--------------Single press to save values in setting menu
                    {  
                    
                      switch (Setting_Menu)  
                      {       
                              case 0 :      
                                      // checkflag == 1 ? >=3200 ? Error_value = 0 : Error_value+=speed_up[inc2] : Error_value<=0 ? Error_value=3200 : Error_value-=speed_up[inc2];
                                       EEPROM.write(10,Calibration_selection_flag);//--------
                                      //  Serial2.println("Inside_Calibration_menu");
                                       Inside_Calibration_menu=1;
                                       break;
                              case 1 :      
                                      // checkflag == 1 ? >=3200 ? Error_value = 0 : Error_value+=speed_up[inc2] : Error_value<=0 ? Error_value=3200 : Error_value-=speed_up[inc2];
                                       EEPROM.write(200, Receipe);
                                      break;
                              case 2 :      
                                      // checkflag == 1 ? >=3200 ? Error_value = 0 : Error_value+=speed_up[inc2] : Error_value<=0 ? Error_value=3200 : Error_value-=speed_up[inc2];
                                      // if(Master_RPM>=1000)
                                      // {
                                      //       Master_unit_RPM_diff=Master_RPM-1000;
                                            
                                      //       if(40<=Master_unit_RPM_diff<=50)
                                      //       {
                                      //         RPM_diff_Factor=1;
                                      //       }
                                      //       if(50<Master_unit_RPM_diff<=60)
                                      //       {
                                      //         RPM_diff_Factor=2;
                                      //       }
                                      // }
                                      break;
                              case 3 : //----------time mode: Pros/soak/dsbl
                                      EEPROM.write(5, Time_mode_Flag);
                                      //  Serial2.print("Time_mode_Flag :");
                                      //   Serial2.println(Time_mode_Flag);
                                      // checkflag == 1 ? >=3200 ? Error_value = 0 : Error_value+=speed_up[inc2] : Error_value<=0 ? Error_value=3200 : Error_value-=speed_up[inc2];
                                      break;  
                              case 4 : //-------------------Heat mode
                                      EEPROM.write(6, Slow_Fast_Mode_Flag);
                                    
                                      break;
                              case 5 : //---------------Safe temp
                                      if(Safe_Menu_Count==0)
                                      {
                                          EEPROM.write(8, Safe_Temp[Safe_Menu_Count] >> 8); //--------Internal safe Temperature
                                          EEPROM.write(9, Safe_Temp[Safe_Menu_Count] & 0xFF);
                                          
                                      }
                                      if(Safe_Menu_Count==1)
                                      {
                                          EEPROM.write(31, Safe_Temp[Safe_Menu_Count] >> 8); //--------External safe Temperature
                                          EEPROM.write(32, Safe_Temp[Safe_Menu_Count] & 0xFF);
                                         
                                      }
                                      if(Safe_Menu_Count==2)
                                      {
                                          EEPROM.write(33, Safe_Temp[Safe_Menu_Count] >> 8); //--------Vapour safe Temperature
                                          EEPROM.write(34, Safe_Temp[Safe_Menu_Count] & 0xFF);
                                          // Serial2.println("Vap safe :");
                                      }
                                      Safe_Menu_Count++;
                                      if(Safe_Menu_Count>2)
                                      {
                                        Safe_Menu_Count=0;
                                        Knob_Single_Press_In_Settings=0;
                                        // Serial2.println("safe end :");
                                      }
                                      
                                      break;        
                              case 6 :  //-----------Auto restart Enable/disable
                                        EEPROM.write(7, Autoresume_Enable_Disable_Flag);
                                        EEPROM.write(35, 0);
                                        
                                      break;
                              default:
                                      break;
                                    
                      }
                      // if(Setting_Menu==5 && Safe_Menu_Count>=2) 
                      //     Knob_Single_Press_In_Settings=0;
                          if(Setting_Menu!=5)
                          {
                            Knob_Single_Press_In_Settings=0;
                            // Serial2.println("ABCD... :");
                          }
                    }
          }
          else if(Inside_Calibration_menu==1)
          {

                if(Calibration_selection_flag==0) //------------------SIngle point calibration
                {  
                    if(!Knob_Single_Press_In_Calibration1) //------------
                    { 

                      if(PT1000_Detection_Occured==1)
                      {
                          EEPROM.write(12, Final_Error_Difference);
                          EEPROM.write(11,Calibration_1_plus_minus_EEPROM);
                          //  Serial2.println("Cal1 external saved... ");
                      }
                      if(PT1000_Detection_Occured==0)
                      {
                          EEPROM.write(14, Final_Error_Difference);
                          EEPROM.write(13,Calibration_1_plus_minus_EEPROM);
                          //  Serial2.println("Cal1 internal saved... ");
                      }
                       tickers.Calibration_save_ticker_start();
                       Knob_Single_Press_In_Calibration1=1;
                      
                    }
                    // else //-------------
                    // {   
                     
                    //    Serial2.println("single point ");
                    //   //  Knob_Single_Press_In_Calibration1=0;
                      
                    // }
                }
                if(Calibration_selection_flag==1) //------------------Two point calibration
                { 
                    if(Cal2_Selection_Parameter==3 || Cal2_Selection_Parameter==6)
                    { 
                        CAL2_maintain_flag=0;
                        Single_Click_In_Cal2_maintain=1;

                    }
                    if(Cal2_Selection_Parameter==7)
                    {     
                        
                           if(PT1000_Detection_Occured==1)
                           {
                                EEPROM.write(19, CAL2_Low_Master >> 8);//-----------------Low master
                                EEPROM.write(20, CAL2_Low_Master & 0xFF);
                                EEPROM.write(21, CAL2_High_Master >> 8);//--------------High Master
                                EEPROM.write(22, CAL2_High_Master & 0xFF);
                                 
                           }
                           if(PT1000_Detection_Occured==0)
                           {
                                EEPROM.write(27, CAL2_Low_Master >> 8);//-----------------Low master
                                EEPROM.write(28, CAL2_Low_Master & 0xFF);
                                EEPROM.write(29, CAL2_High_Master >> 8);//--------------High Master
                                EEPROM.write(30, CAL2_High_Master & 0xFF); 
                                 

                           }
                          tickers.Calibration_save_ticker_start();
                          // Serial2.println("Cal2 save");
                    }
                    // Serial2.println("Cal2 enterrrrrr");
                    if(Cal2_Selection_Parameter!=2 && Cal2_Selection_Parameter!=5 )
                    {
                              Cal2_Selection_Parameter++;
                              //  Serial2.print("Cal2_Selection_Parameter :");
                              //  Serial2.println(Cal2_Selection_Parameter);
                    }
                }


          }

      }

  }
}

//******************************Knob long press function****************************************************//
void longPressStart1()
{ 
  if(SSR_Failure_Flag==0)
  { 
    if(Process_Start_Flag==0 && Enter_Button==0 && (mode==0 || mode==1))
    {
       chk_time = 1;
    }
    else if(Process_Start_Flag==0 && Enter_Button==1 && mode==1 && Receipe_Mode==0)
    {
      Enter_Button=4;
    }
    else if(Process_Start_Flag==0  && mode==1 && Receipe_Mode==1)
    { 
      
      // Process_start_stop_Rcp_step=Receipe_Step+1;
       Process_start_stop_Rcp_step=6;
       Enter_Button=4;
    }
    else if(Process_Start_Flag==1)   
    {           
                EEPROM.write(35, 0);
                Motor_stop_After_process_exit=1;
                Receipe_Mode=0;
                Process_Start_Flag=0;
                countDownStart=0;
                encoder0Pos=0;
                Enter_Button=0;
                Exit_Process=0;
                setMin=0;
                incrementTime=0;
               
    }
    else if(mode==2 && Process_Start_Flag==0 && Inside_Calibration_menu==0)//----In setting mode: Go to the home page by knob long press
    {         
              if(Knob_Single_Press_In_Settings==1 && Setting_Menu==0)
              {
                 EEPROM.write(10,Calibration_selection_flag);
                //  Serial2.println("cal back ");
              }       
              Enter_Button=0;
              Setting_Menu=0;
              Knob_Single_Press_In_Settings=0;
              encoder0Pos=0;
              mode=1;

              // Serial2.println("AAAA ");
    } 
    else if(mode==2 && Process_Start_Flag==0 && Inside_Calibration_menu==1)//----In setting mode: Go to the home page by knob long press
    {
              digitalWrite(Process_LED,LOW);
              SSR_fail_In_Cal2_flag=0;
              Cal2_Selection_Parameter=0;
              Inside_Calibration_menu=0;
              Knob_Single_Press_In_Calibration1=0;
              Knob_Single_Press_In_Settings=0;
              Setting_Menu=0;
              encoder0Pos=0;
              // Serial2.println("Exit C ");
              
   }
 }
}

void longPress1() 
{ 

      if(inc_time >= 7 && chk_time == 1) //----------7 second long press to enter setting menu.
      {   
         
            mode=2;
            if(Set_speed!=0)
            {
                Set_speed=0;
                Stop_pwm=235;
                Motor_Stop_Flagg=1;
                tickers.Motor_slow_stop_tick_start();
            }
        //  Serial2.println("Long Press ...."); 

      }
}
void longPressStop1() 
{
      chk_time = 0;
      inc_time = 0;

}

void key1_Single_Click() //-----------SET Key
{
  if(SSR_Failure_Flag==0)
  {  
      if(Process_Start_Flag==0)   
      {
         if(mode==1)  //---------------SET parameters(Temp,Time) mode
         { 
                // Enter_Button++;
                // if(Enter_Button>=4) //-----------process start
                // {  
                    
                //   Enter_Button=4;
              
                // } 
               if(Receipe_Mode==0)
                {
                    Enter_Button++;
                    if(Enter_Button>=4) //-----------process start
                    {  
                        
                      Enter_Button=4;
                  
                    }
                }
                if(Receipe_Mode==1)
                {
          // Receipe_Step
          // Receipe_Parameter
       
                    if(!Knob_Single_Press_In_Receipe_start)
                    {
                        Enter_Button=1;
                        Knob_Single_Press_In_Receipe_start=1;
                        //  Serial2.println("1");
                    }
                    else
                    {
                        
                        if(Receipe_Step!=6)
                        {   
                            //  Serial2.println("vvvv");
                            Enter_Button++;
                            if(Enter_Button>=4) 
                            {   
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

                                EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step],   Receipe_Set_Temp[Receipe][Receipe_Step] >> 8); //--------Internal safe Temperature
                                EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+1, Receipe_Set_Temp[Receipe][Receipe_Step] & 0xFF);
                                EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+2, Receipe_Set_Hour[Receipe][Receipe_Step]);
                                EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+3, Receipe_Set_Min[Receipe][Receipe_Step]);
                                EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+4, Receipe_Set_RPM[Receipe][Receipe_Step] >> 8); //--------Internal safe Temperature
                                EEPROM.write(RCP_EEPROM_Address[Receipe][Receipe_Step]+5, Receipe_Set_RPM[Receipe][Receipe_Step] & 0xFF);
                                Receipe_Step++;
                                Set_speed=Receipe_Set_RPM[Receipe][Receipe_Step];
                                Enter_Button=1;
                          
                            }
                        }
                        if(Receipe_Step==6)
                        { 
                            
                            Process_start_stop_Rcp_step=6;
                            Enter_Button=4;
                        }

                      }

            }
         }
      }
      if(Process_Start_Flag==1 && Inprocess_page_change==1 && Receipe_Mode==0)   
      {
          Inprocess_Set_Temp_Change++;
          if(Inprocess_Set_Temp_Change>=2)
          {  
            EEPROM.write(1, Set_temp >> 8);//--------Save set Temperature
            EEPROM.write(2, Set_temp & 0xFF);
            // Serial2.println("Inprocess_Set_Temp_Change  Saved : ");
            Inprocess_Set_Temp_Save=1;
            Inprocess_Set_Temp_Change=0;
          }
      }

  }  
}

void key2_Single_Click() //-----------Esc Key
{
   if(SSR_Failure_Flag==0)
   { 
      if(Process_Start_Flag==0 && mode==1)
      {
            if(Receipe_Mode==0)  //-----------
            {
                  Enter_Button--;
                  if(Enter_Button<=0)
                    Enter_Button=0;
                  // Serial2.println("normal: ");
            }
            if(Receipe_Mode==1) //---------------Recipe mode
            {
   
                  if(Receipe_Step==0)
                  {
                      Enter_Button--;
                      if(Enter_Button<1) 
                           Enter_Button=0;
                  }
                   if(Receipe_Step!=0)
                  {   
                       if(Enter_Button==1) 
                       {
                          Receipe_Step--;
                          Enter_Button=4;
                          // Serial2.print("Receipe_Step : ");
                          // Serial2.println(Receipe_Step);  
                       }
                       if(Enter_Button!=1) 
                       {
                           Enter_Button--;
                           
                       }
                      
                     
                  }

            }

      }
     if(Process_Start_Flag==1)   
      { 
            Process_stop_by_key1++;
            if(Process_stop_by_key1==1)
            {
                tickers.Process_stop_by_key1_ticker_start();
            }
            if(Process_stop_by_key1==2)
            {
              EEPROM.write(35, 0);
              
            }
            if(Process_stop_by_key1>2)
            { 
              // EEPROM.write(35, 0);
              Process_stop_by_key1=2;
            }
      }
      if(mode==2) //---------Setting menu
      {  
          if(Knob_Single_Press_In_Settings==1) //----------Back
          {   
              Knob_Single_Press_In_Settings=0;
              
            
          }
          if(Inside_Calibration_menu==1)
          {
             if(Calibration_selection_flag==0)
             {
                 Knob_Single_Press_In_Settings=1;
                 Knob_Single_Press_In_Calibration1=0;
                 Inside_Calibration_menu=0;
             }
             if(Calibration_selection_flag==1)
             {
                  Cal2_Selection_Parameter--;
                  if(Cal2_Selection_Parameter<0)
                  {
                      Cal2_Selection_Parameter=0;
                      Knob_Single_Press_In_Settings=1;
                      Inside_Calibration_menu=0;
                  }

             }
          }
      }
   }
} 
void ESC_key_LongPress()
{
    if(SSR_Failure_Flag==0)
    { 
        if(Process_Start_Flag==0 && mode==1)
        {
            Enter_Button=0;
        }
    }
}
void tickers_class:: Button_update() 
{
      button0.tick();
      key1.tick();
      key2.tick();
}

void interrupt() 
{
  // Serial.println("feedback...........");
  if (RPM_read == 1) {
    pulses++;
  }
  if (RPM_read == 0)  // after every 1 sec
  {
    counter2 = (pulses * 60);
    // Current_RPM1= (counter2 ) / (3.75 * 4);
    // Current_RPM1= (counter2 ) / (4.5);
    // Current_RPM1= (counter2 )/3.5;
    Current_RPM1 = (counter2) / 4.0;
    if (Current_RPM1 < 0) {
      Current_RPM1 = 0;
    }
    if (Current_RPM1 > 5000) {
      Current_RPM1 = 0;
    }
    RPM_read = 1;
    pulses = 0;
  }
}

void Time_rpm()  // Timer for Reading Motor RPM (1sec)
{
  RPM_read = 0;
}

void Motor_Class::Feedback_update()
{ 
 rpm_time.update();
}