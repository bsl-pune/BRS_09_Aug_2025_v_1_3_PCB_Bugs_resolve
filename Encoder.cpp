
//**********************************************************************Rotary encoder ****************************************************************************************//
#include "ext_var.h"
//-----------------------------------pin declarations-------------------------//
const int pinA =19;  //-----------------Encoder1 pin 
const int pinB = 16;  //----------------Encoder2 pin  
const int pinA_Encoder2 =37;  //-----------------Encoder1 pin 
const int pinB_Encoder2 = 36;

//****************************************Function declartion**********************************************//
void PinA();
void PinB(); 
void PinA_Encoder2();
void PinB_Encoder2(); 
void Encoder2_increment();
//******************************************Global Variables********************************************//
//-------------------------------First rotary encoder variables-------------------------//
volatile byte aFlag = 0;
volatile byte bFlag = 0;
volatile int encoderPos = 0; 
volatile int oldEncPos = 0;
volatile byte reading = 0;
volatile byte reading2 = 0;
volatile int encoder0Pos = 0;
int checkflag=0;
int inc2=0,accel=0,inc1=0;
//-------------------------------Second rotary encoder variables-------------------------//
volatile byte aFlag_Encoder2 = 0;
volatile byte bFlag_Encoder2 = 0;
volatile int encoderPos_Encoder2 = 0; 
volatile int oldEncPos_Encoder2 = 0;
volatile byte reading_Encoder2 = 0;
volatile byte reading2_Encoder2 = 0;
volatile int encoder0Pos_Encoder2 = 0;
int checkflag_Encoder2=0;
int accel_Encoder2=0,inc2_Encoder2=0;

//---------------------------------------------------------------------------------------//
bool ONCE_Inc=0;


int speed_up[6] = {0,1,4,8,19,26};
int speed_up1[5] = {0,5,10,15,30};

Eclass::Eclass()
{}

void Eclass :: SETUP()
{ 
  // mySerial.begin(9600);
  pinMode(pinA, INPUT_PULLUP); 
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(pinA,PinA,RISING);
  attachInterrupt(pinB,PinB,RISING);
  pinMode(pinA_Encoder2, INPUT_PULLUP); 
  pinMode(pinB_Encoder2, INPUT_PULLUP);
  attachInterrupt(pinA_Encoder2,PinA_Encoder2,RISING);
  attachInterrupt(pinB_Encoder2,PinB_Encoder2,RISING);

} 

void PinA()
{
  cli(); //stop interrupts happening before we read pin values
   if(digitalRead(pinA) == HIGH && digitalRead(pinB) == HIGH && aFlag)
  { 
    encoderPos --;
    bFlag = 0; 
    aFlag = 0; 
    checkflag=0;
    
   
  } 
  else if (digitalRead(pinA) == HIGH) bFlag = 1;
  sei(); //restart interrupts
   if(inc2==1 || inc2==0) tickers.BUZZ_INTERVAL(50);  
  // Encoder.encode_increment();//-----go to increment and decrement loop
}


void PinB()
{
  cli(); //stop interrupts happening before we read pin values
   if(digitalRead(pinA) == HIGH && digitalRead(pinB) == HIGH && bFlag)
  { 
    encoderPos++; 
    bFlag = 0; 
    aFlag = 0; 
    checkflag=1;
   
  }
  else if (digitalRead(pinB) == HIGH) aFlag = 1;
  sei(); //restart interrupts
   if(inc2==1 || inc2==0) tickers.BUZZ_INTERVAL(50);  
  // Encoder.encode_increment();//-----go to increment and decrement loop
}

//------------------------------------------------------------------------------------------------------//
void PinA_Encoder2()
{
  cli(); //stop interrupts happening before we read pin values

   if(digitalRead(pinA_Encoder2) == HIGH && digitalRead(pinB_Encoder2) == HIGH && aFlag_Encoder2)
  { 
    encoderPos_Encoder2 --;
    bFlag_Encoder2 = 0; 
    aFlag_Encoder2 = 0; 
    checkflag_Encoder2=0;
    
   
  } 
  else if (digitalRead(pinA_Encoder2) == HIGH) bFlag_Encoder2 = 1;
  sei(); //restart interrupts
  if(inc2_Encoder2==1 || inc2_Encoder2==0) tickers.BUZZ_INTERVAL(50);  
//  Encoder2_increment();//-----go to increment and decrement loop
}


void PinB_Encoder2()
{
  cli(); //stop interrupts happening before we read pin values
   if(digitalRead(pinA_Encoder2) == HIGH && digitalRead(pinB_Encoder2) == HIGH && bFlag_Encoder2)
  { 
    encoderPos_Encoder2++; 
    bFlag_Encoder2 = 0; 
    aFlag_Encoder2 = 0; 
    checkflag_Encoder2=1;
   
  }
  else if (digitalRead(pinB_Encoder2) == HIGH) aFlag_Encoder2 = 1;
  sei(); //restart interrupts
  if(inc2_Encoder2==1 || inc2_Encoder2==0) tickers.BUZZ_INTERVAL(50);  
  // Encoder2_increment();//-----go to increment and decrement loop
}
//----------------------First Encoder ------------------------------//
void Eclass :: encode_increment()
{ 
  if(SSR_Failure_Flag==0 && SSR_fail_In_Cal2_flag==0)
  { 
    
    if(oldEncPos != encoderPos) 
    { 
      
      accel=1;
      inc2++;
      if(inc2>5) inc2=5;
      oldEncPos = encoderPos;
       if(mode == 1 && Process_Start_Flag==0 && Enter_Button==0)
       {
             
          checkflag == 1 ? Receipe_Mode=!Receipe_Mode : Receipe_Mode=!Receipe_Mode;
          // checkflag == 1 ? Receipe_Mode=1 : Receipe_Mode=0;
          if(Receipe_Mode==1)
          {  
                if(Set_speed!=0)
                {  
                    
                    if(Overhead_Motor_connected_Flag==0)
                    {   
                       
                        Stop_pwm=233;
                        Motor_Stop_Flagg=1;
                        tickers.Motor_slow_stop_tick_start();
                        Motor_stop_In_Recipe=1;
                    }
                }
                Set_speed=Receipe_Set_RPM[Receipe][0];
          }
          if(Receipe_Mode==0)
          { 
            Set_speed=0;
          }
          
       }
       if(mode == 1 && Process_Start_Flag==0 && Enter_Button!=0)//---Increasing/Decreasing temp & time 
       {   
           if(Receipe_Mode==0)
           {
            //  Serial2.println(2);
                switch (Enter_Button)
                {
                    case 1 :
                            checkflag == 1 ?  Set_temp>=Safe_Temp[PT1000_Detection_Occured] ? Set_temp=0: Set_temp += speed_up[inc2] :  Set_temp<=0 ? Set_temp=Safe_Temp[PT1000_Detection_Occured]: Set_temp -=speed_up[inc2];
                            break;
                    case 2 :
                            checkflag == 1 ?  Set_Hour>=99 ? Set_Hour=0: Set_Hour += speed_up[inc2] :  Set_Hour<=0 ? Set_Hour=99: Set_Hour -=speed_up[inc2];
                            break;
                    case 3 :
                            checkflag == 1 ?  Set_Min>=59 ? Set_Min=0: Set_Min += speed_up[inc2] :  Set_Min<=0 ? Set_Min=59: Set_Min -=speed_up[inc2];
                            break;
                    default:
                            break;
                }
           }
           if(Receipe_Mode==1)
           {  
            
                switch (Enter_Button)
                {
                    case 1 :
                            checkflag == 1 ?   Receipe_Set_Temp[Receipe][Receipe_Step]>=Safe_Temp[PT1000_Detection_Occured] ? Receipe_Set_Temp[Receipe][Receipe_Step]=0: Receipe_Set_Temp[Receipe][Receipe_Step] += speed_up[inc2] :  Receipe_Set_Temp[Receipe][Receipe_Step]<=0 ? Receipe_Set_Temp[Receipe][Receipe_Step]=Safe_Temp[PT1000_Detection_Occured]: Receipe_Set_Temp[Receipe][Receipe_Step] -=speed_up[inc2];
                            // Serial2.print(" Receipe_Set_Temp[Receipe][Receipe_Step] :");
                            //  Serial2.println(Receipe_Set_Temp[Receipe][Receipe_Step] );
                            break;
                    case 2 :
                            checkflag == 1 ?  Receipe_Set_Hour[Receipe][Receipe_Step]>=99 ?  Receipe_Set_Hour[Receipe][Receipe_Step]=0:   Receipe_Set_Hour[Receipe][Receipe_Step] += speed_up[inc2] :    Receipe_Set_Hour[Receipe][Receipe_Step]<=0 ?   Receipe_Set_Hour[Receipe][Receipe_Step]=99:   Receipe_Set_Hour[Receipe][Receipe_Step] -=speed_up[inc2];
                            // Serial2.println(Receipe_Set_Hour[Receipe][Receipe_Step] );
                            break;
                    case 3 :
                            checkflag == 1 ?  Receipe_Set_Min[Receipe][Receipe_Step]>=59 ?  Receipe_Set_Min[Receipe][Receipe_Step]=0:  Receipe_Set_Min[Receipe][Receipe_Step] += speed_up[inc2] :   Receipe_Set_Min[Receipe][Receipe_Step]<=0 ?  Receipe_Set_Min[Receipe][Receipe_Step]=59:  Receipe_Set_Min[Receipe][Receipe_Step] -=speed_up[inc2];
                            // Serial2.println(Receipe_Set_Min[Receipe][Receipe_Step] );
                            break;
                    default:
                            break;
                }
              
           }

          
          
       }
       if(Process_Start_Flag==1)
       { 
          if(Inprocess_Set_Temp_Change==0)
          {
              sendDataFlag=0;
              if(Receipe_Mode==0)
              {  
                  checkflag == 1 ?  Inprocess_page_change>=2 ? Inprocess_page_change=2: Inprocess_page_change +=1 :  Inprocess_page_change<=0 ? Inprocess_page_change=0: Inprocess_page_change -=1;
              } 
              if(Receipe_Mode==1)
              { 
                  checkflag == 1 ?  Inprocess_page_change>=3 ? Inprocess_page_change=3: Inprocess_page_change +=1 :  Inprocess_page_change<=0 ? Inprocess_page_change=0: Inprocess_page_change -=1;
              } 
          } 
          if(Inprocess_Set_Temp_Change==1)
          {
              checkflag == 1 ?  Set_temp>=Safe_Temp[PT1000_Detection_Occured] ? Set_temp=0: Set_temp += speed_up[inc2] :  Set_temp<=0 ? Set_temp=Safe_Temp[PT1000_Detection_Occured]: Set_temp -=speed_up[inc2];

          }

       }
        if(mode == 2)//-------------------if in setting 
        {
          
              if(Inside_Calibration_menu==0)  //--------------Not in Calibration mode
              {
                        if(Knob_Single_Press_In_Settings) //-----------in specific setting
                        { 
                          switch(Setting_Menu)
                          {      
                                case 0 :      
                                       
                                        checkflag == 1 ? Calibration_selection_flag=!Calibration_selection_flag : Calibration_selection_flag=!Calibration_selection_flag;
                                        break;
                                case 1 :      
                                        // checkflag == 1 ? Receipe_Count>=3 ? Receipe_Count = 0 : Receipe_Count+=1 : Receipe_Count<=0 ? Receipe_Count=3 : Receipe_Count-=1;
                                        
                                        checkflag == 1 ? Receipe>=3 ? Receipe = 0 : Receipe+=1 : Receipe<=0 ? Receipe=3 : Receipe-=1;

                                        break;
                                case 2 :      
                                        checkflag == 1 ? Master_RPM >=1500 ? Master_RPM = 0 : Master_RPM+=speed_up[inc2] : Master_RPM<=0 ? Master_RPM=1500 : Master_RPM-=speed_up[inc2];
                                        break;
                                case 3 :  //----------time mode: Pros/soak 
                                        // checkflag == 1 ? Time_mode_Flag>=2 ? Time_mode_Flag=0 : Time_mode_Flag+=1 : Time_mode_Flag<=0 ? Time_mode_Flag=2 : Time_mode_Flag-=1;    
                                        checkflag == 1 ? Time_mode_Flag=!Time_mode_Flag : Time_mode_Flag=!Time_mode_Flag;
                                        // checkflag == 1 ? >=3200 ? Error_value = 0 : Error_value+=speed_up[inc2] : Error_value<=0 ? Error_value=3200 : Error_value-=speed_up[inc2];
                                        break;  
                                case 4: //----------------slow/fast heating
                                        checkflag == 1 ? Slow_Fast_Mode_Flag=!Slow_Fast_Mode_Flag : Slow_Fast_Mode_Flag=!Slow_Fast_Mode_Flag;
                                        break;
                                case 5: //----------------------safe mode
                                        if(Safe_Menu_Count==0)
                                        {
                                            checkflag == 1 ? Safe_Temp[Safe_Menu_Count]>=3500 ? Safe_Temp[Safe_Menu_Count] = 0 : Safe_Temp[Safe_Menu_Count]+=speed_up[inc2] : Safe_Temp[Safe_Menu_Count]<=0 ? Safe_Temp[Safe_Menu_Count]=3500 : Safe_Temp[Safe_Menu_Count]-=speed_up[inc2];
                                            
                                         }
                                        if(Safe_Menu_Count==1)
                                        {
                                            checkflag == 1 ? Safe_Temp[Safe_Menu_Count]>=2500 ? Safe_Temp[Safe_Menu_Count] = 0 : Safe_Temp[Safe_Menu_Count]+=speed_up[inc2] : Safe_Temp[Safe_Menu_Count]<=0 ? Safe_Temp[Safe_Menu_Count]=2500 : Safe_Temp[Safe_Menu_Count]-=speed_up[inc2];
                                            
                                        }
                                        if(Safe_Menu_Count==2)
                                          {
                                           checkflag == 1 ? Safe_Temp[Safe_Menu_Count]>=1000 ? Safe_Temp[Safe_Menu_Count] = 0 : Safe_Temp[Safe_Menu_Count]+=speed_up[inc2] : Safe_Temp[Safe_Menu_Count]<=0 ? Safe_Temp[Safe_Menu_Count]=1000 : Safe_Temp[Safe_Menu_Count]-=speed_up[inc2];
                                            
                                          }
                                        break;        
                                case 6:  //-----------Auto restart Enable/disable
                                      checkflag == 1 ? Autoresume_Enable_Disable_Flag=!Autoresume_Enable_Disable_Flag : Autoresume_Enable_Disable_Flag=!Autoresume_Enable_Disable_Flag;
                                      break;
                                default:
                                        break;  

                          }
                        }
                        else //----------Setting menu scorlling
                        { 
                          
                              checkflag == 1 ? Setting_Menu>=6 ? Setting_Menu = 0 : Setting_Menu+=1 : Setting_Menu<=0 ? Setting_Menu=6 : Setting_Menu-=1;         
                        }

              }
               if(Inside_Calibration_menu==1)  //----------------------Inside calibration menu
                {  
                      if(Calibration_selection_flag==0)//-------------Single point Calb
                      {  
                          checkflag == 1 ? Calibration1_Value>=3500 ? Calibration1_Value = 0 : Calibration1_Value+=speed_up[inc2] : Calibration1_Value<=0 ? Calibration1_Value=3500 : Calibration1_Value-=speed_up[inc2];
                          // Calibration1_Value=encoder0Pos;
                      }
                      if(Calibration_selection_flag==1)//---------------------Two point Calb
                      { 
                            switch (Cal2_Selection_Parameter)
                            {
                                case 0 :
                                    checkflag == 1 ? CAL2_Low_Set_temp>=350 ? CAL2_Low_Set_temp = 0 : CAL2_Low_Set_temp+=speed_up[inc2] : CAL2_Low_Set_temp<=0 ? CAL2_Low_Set_temp=350 : CAL2_Low_Set_temp-=speed_up[inc2];
                                    break;
                                case 1 :
                                    checkflag == 1 ? CAL2_High_Set_temp>=500 ? CAL2_High_Set_temp = 0 : CAL2_High_Set_temp+=speed_up[inc2] : CAL2_High_Set_temp<=0 ? CAL2_High_Set_temp=500 : CAL2_High_Set_temp-=speed_up[inc2];
                                    break;
                                case 4 :
                                    checkflag == 1 ? CAL2_Low_Master>=3500 ? CAL2_Low_Master = 0 : CAL2_Low_Master+=speed_up[inc2] : CAL2_Low_Master<=0 ? CAL2_Low_Master=3500 : CAL2_Low_Master-=speed_up[inc2];
                                    break;
                                
                                case 7 :
                                    checkflag == 1 ? CAL2_High_Master>=5000 ? CAL2_High_Master = 0 : CAL2_High_Master+=speed_up[inc2] : CAL2_High_Master<=0 ? CAL2_High_Master=5000 : CAL2_High_Master-=speed_up[inc2];
                                    break;
                            }

                      }

                }

        }
    }
  }
}

void  Eclass ::Encoder2_increment()
{ 
  if(SSR_Failure_Flag==0)
  { 
    if(mode!=2 || SetPoint_for_Cal2==1)
    {        
      if(oldEncPos_Encoder2 != encoderPos_Encoder2) 
      {  
        accel_Encoder2=1;
        inc2_Encoder2++;
        if(inc2_Encoder2>4) inc2_Encoder2=4;
        oldEncPos_Encoder2 = encoderPos_Encoder2;
        if(Overhead_Motor_connected_Flag==0)
        {
          //  Serial2.println("RPMM.. :");     
              // if(Set_speed==0)
              // {
              //     //  Int_Motor_Spd_control_flag=1;
              //     Stop_pwm=230;
              //     tickers.Motor_slow_stop_tick_start();
              //       // tickers.Int_Motor_Spd_control_tick_start();
              // }

               if(checkflag_Encoder2 == 1)
               {
                      if(Set_speed==0)
                                Set_speed=200;
                      else
                      {
                            if(Set_speed>=1500)
                            {
                                Set_speed=0;
                                if(Receipe_Mode==0)
                                {
                                    Stop_pwm=233;
                                    Motor_Stop_Flagg=1;
                                    tickers.Motor_slow_stop_tick_start();
                                }
                                  // tickers.Int_Motor_Spd_control_tick_start();
                            }
                            else
                                Set_speed+=10;
                      }
                } 
                if(checkflag_Encoder2 == 0)
                {
                        if(Set_speed==200)
                                Set_speed=0;
                          else 
                          {
                              if(Set_speed<=0)
                                  Set_speed=1500;
                              else 
                                Set_speed-=10;
                          }
                }
        }
        if(Overhead_Motor_connected_Flag==1)
        {
             if(checkflag_Encoder2 == 1)
              {
                      if(OHS_Set_speed==0)
                                OHS_Set_speed=50;
                      else
                      {
                            if(OHS_Set_speed>=1000)
                                OHS_Set_speed=0;
                            else
                                OHS_Set_speed+=10;
                      }
                } 
                if(checkflag_Encoder2 == 0)
                {
                        if(OHS_Set_speed==50)
                                OHS_Set_speed=0;
                          else 
                          {
                              if(OHS_Set_speed<=0)
                                  OHS_Set_speed=1000;
                              else 
                                OHS_Set_speed-=10;
                          }
                }

        }
        if(Receipe_Mode==1)
        {
          Receipe_Set_RPM[Receipe][Receipe_Step]=Set_speed;
        }
          if(Process_Start_Flag==1)
          {     
                sendDataFlag=0; 
                Inprocess_Set_RPM_show_flag=1;
                tickers.In_process_Set_RPM_show_start();
          }

      }

   }
  }
  

}

Eclass Encoder = Eclass();
