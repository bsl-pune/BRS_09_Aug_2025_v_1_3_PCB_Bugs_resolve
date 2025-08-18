
//*************************************************Time calculation************************************************************************//
#include "ext_var.h"

// #define PERIOD_EXAMPLE_VALUE (500) 

//-------------------------Global function declaration-----------------------------//
void Time_Calculation();
//-------------------Ticker for time calculation----------------------------------------//
void Time_calutation_ticker_function();
Ticker Time_calutation_tick(Time_calutation_ticker_function, 1000, 0);

//-------------------------Global var---------------------------------------------------//
long setMin=0; 
bool countDownStart=0;
long incrementTime=0;
long Inf_time_count=0;
unsigned long TimePassed=0;
bool InF_mode=0;

TimerUpdate_Class::TimerUpdate_Class()
{}

//---------------------------------Set Up function-----------------------------------------------------------//
void TimerUpdate_Class::TimerUpdate_SETUP()
{ 
    // cli();//stop interrupts
    // TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;                                    /* enable overflow interrupt */  
    // TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;                            /* set Normal mode */
    // TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);                               /* disable event counting */ 
    // TCA0.SINGLE.PER = PERIOD_EXAMPLE_VALUE;                                     /* set the period */ 
    // TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc | TCA_SINGLE_ENABLE_bm; 
    // sei();//allow interrupts
}
//-----------------------------------------Interrupt service routine------------------------------------------//
// ISR(TCA0_OVF_vect)
// { 
//       tickers.LongPress7sec_update();
//       TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; 
// }

void Time_calutation_ticker_function()
{
     if(countDownStart==1)  //----------------If process start
      { 
        Time_Calculation(); //-------------------Calling time calculation function
      }
}
void TimerUpdate_Class::Time_calutation_tick_START() //---------start ticker
{
  Time_calutation_tick.start();
}
void TimerUpdate_Class::Time_calutation_tick_UPDATE() //-------update ticker function
{
   Time_calutation_tick.update();
}

void  Time_Calculation()
{
      incrementTime++;
      if(incrementTime >=60)   //------------------Enter after 1 min
      {    
            if(InF_mode==0) //------------------Defined time
            {  
                 if(Time_mode_Flag==0)
                 {
                        setMin--;
                        Current_HOUR = setMin / 60;
                        Current_Min = setMin % 60 ;
                        //  Serial2.println("Process time");
                        if(Receipe_Mode==0)
                        { 
                            if(setMin==0) //-----------when time becomes zero
                            {   
                               if(mode==1)
                               {
                                    countDownStart=0;
                                    Exit_Process=0;
                                    Enter_Button=0;
                                    // Serial2.println(" time over ");
                               }
                                if(mode==2)
                                {  
                                  // Single_Click_In_Cal2_maintain=1;
                                  //  Cal2_Selection_Parameter++;
                                   countDownStart=0;
                                   CAL2_maintain_flag=0;
                                  //  Serial2.println("cal2 time end ");
                                }
                              
                            }
                        }
                        if(Receipe_Mode==1)
                        { 
                            if(setMin==0) //-----------when time becomes zero
                            {  
                                 Receipe_Step++;
                                 if(Receipe_Step==Process_start_stop_Rcp_step)
                                 {
                                    Set_speed=Receipe_Set_RPM[Receipe][5];
                                    Motor_stop_After_process_exit=1;
                                    countDownStart=0;
                                    Receipe_Mode=0;
                                    Exit_Process=0;
                                    Enter_Button=0;
                                   
                                 }
                                 if(Receipe_Step!=Process_start_stop_Rcp_step)
                                 {   
                                       // EEPROM_Set_Temp=Receipe_Set_Temp[Receipe][Receipe_Step];
                                        Set_temp=Receipe_Set_Temp[Receipe][Receipe_Step];
                                        Set_Hour=Receipe_Set_Hour[Receipe][Receipe_Step];
                                        Set_Min=Receipe_Set_Min[Receipe][Receipe_Step];
                                        Set_speed=Receipe_Set_RPM[Receipe][Receipe_Step];

                                        if(Receipe_Set_RPM[Receipe][Receipe_Step-1]>0 && Set_speed==0)
                                        {
                                            Stop_pwm=230;
                                            Motor_Stop_Flagg=1;
                                            tickers.Motor_slow_stop_tick_start();
                                            // Serial2.println("iiiiiiiiiiiii" );
                                        }
                                        setMin=Receipe_Set_Hour[Receipe][Receipe_Step]*60+Receipe_Set_Min[Receipe][Receipe_Step];
                                        if(setMin==0)
                                        {
                                            Motor_stop_After_process_exit=1;
                                            countDownStart=0;
                                            Receipe_Mode=0;
                                            Exit_Process=0;
                                            Enter_Button=0;
                                            // Serial2.println("rcp process exitt" );
                                        }
                                        Current_HOUR = setMin / 60;
                                        Current_Min = setMin % 60 ;
                                        Inprocess_Set_Temp_Save=1;

                                        // Serial2.print("Receipe_Step :");
                                        // Serial2.println(Receipe_Step );
                                        // Serial2.print("Set_temp :");
                                        // Serial2.println(Set_temp );
                                        // Serial2.print("Set_speed :");
                                        // Serial2.println(Set_speed );
                                        // Serial2.print("Set_Hour1 :");
                                        // Serial2.println(Set_Hour );
                                        // Serial2.print("Set_Min1 :");
                                        // Serial2.println(Set_Min );
                                        // Serial2.print("setMin1 :");
                                        // Serial2.println(setMin );
                                        // if(Receipe_Step==6)
                                 }
                                
                              
                            }

                       }
                }
                if(Time_mode_Flag==1 && Soak_time_start_flag==1)
                {
                        setMin--;
                        Current_HOUR = setMin / 60;
                        Current_Min = setMin % 60 ;
                        //  Serial2.println("Soak time");
                        if(Receipe_Mode==0)
                        { 
                            if(setMin==0) //-----------when time becomes zero
                            {
                                countDownStart=0;
                                Exit_Process=0;
                                Enter_Button=0;
                                //  Serial2.println("Soak time over ");
                              
                            }
                        }
                        if(Receipe_Mode==1)
                        { 
                            if(setMin==0) //-----------when time becomes zero
                            {  
                                Receipe_Step++;
                                // EEPROM_Set_Temp=Receipe_Set_Temp[Receipe][Receipe_Step];
                                Set_temp=Receipe_Set_Temp[Receipe][Receipe_Step];
                                Set_Hour=Receipe_Set_Hour[Receipe][Receipe_Step];
                                Set_Min=Receipe_Set_Min[Receipe][Receipe_Step];
                                Set_speed=Receipe_Set_RPM[Receipe][Receipe_Step];
                                setMin=Receipe_Set_Hour[Receipe][Receipe_Step]*60+Receipe_Set_Min[Receipe][Receipe_Step];
                                Current_HOUR = setMin / 60;
                                Current_Min = setMin % 60 ;
                                Soak_time_start_flag=0;
                                Soak_time_Once=0;
                                Inprocess_Set_Temp_Save=1;

                                // Serial2.print("Receipe_Step :");
                                // Serial2.println(Receipe_Step );
                                // Serial2.print("EEPROM_Set_Temp1 :");
                                // Serial2.println(EEPROM_Set_Temp );
                                // Serial2.print("Set_Hour1 :");
                                // Serial2.println(Set_Hour );
                                // Serial2.print("Set_Min1 :");
                                // Serial2.println(Set_Min );
                                // Serial2.print("setMin1 :");
                                // Serial2.println(setMin );
                                // if(Receipe_Step==6)
                                if(Receipe_Step==Process_start_stop_Rcp_step)
                                {
                                  countDownStart=0;
                                  Receipe_Mode=0;
                                  Exit_Process=0;
                                  Enter_Button=0;
                                }
                              
                            }

                        }


                }
            }
            if(InF_mode==1) //---------------Infinite Time
            { 
              
                  // Exit_Process=1;  //---------process start
                  setMin++;
                  // if(Current_HOUR==99 && Current_Min==60)
                  if(setMin>5999)
                  {  
                     windowStartTime=0;
                     setMin=0;
                      // Serial2.println("INF....  cross");
                  } 
                  Current_HOUR = setMin / 60;
                  Current_Min = setMin % 60 ; 
                  
                  
            }
            // Serial2.print("Current_HOUR :");
            // Serial2.println(Current_HOUR);
            // Serial2.print("Current_Min :");
            // Serial2.println(Current_Min);  
          
            incrementTime=0;  //-------------reset this flag after completion of 1 min 
      }

}

TimerUpdate_Class TimerUpdate = TimerUpdate_Class();