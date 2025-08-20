#include "ext_var.h"
#include <PID_v1.h>

int WindowSize = 5000; 
int WindowSize_slow=6800;   
unsigned long windowStartTime;
bool once_heater_PID = 0;
double  Setpoint,Input, Output; 
int set_input_cmp_factor=0;
double Kp, Ki, Kd = 0;
//------------Hello


// //-------PID12
// double Kp_slow[2]={30,36}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,6200}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,37}, consKi_slow[2]={0.02,0.02}, consKd_slow[2]={1200,6900};
//                   //---Int,Ext
// double kp_fast[2]={30,55},ki_fast[2]={0.03,0.01},kd_fast[2]={1000,5000};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,40},consKi_fast[2]={0.02,0.01},consKd_fast[2]={1100,6000};   // fast mode for both internal and external.

// //-------PID13
// double Kp_slow[2]={30,37}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,6250}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,40}, consKi_slow[2]={0.02,0.023}, consKd_slow[2]={1200,6600};
//                   //---Int,Ext
// double kp_fast[2]={30,58},ki_fast[2]={0.03,0.02},kd_fast[2]={1000,4900};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,43},consKi_fast[2]={0.02,0.01},consKd_fast[2]={1100,5800};   // fast mode for both internal and external.

// //-------PID13 update
// double Kp_slow[2]={30,53}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,5100}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,40}, consKi_slow[2]={0.02,0.015}, consKd_slow[2]={1200,6050};
//                   //---Int,Ext
// double kp_fast[2]={30,58},ki_fast[2]={0.03,0.02},kd_fast[2]={1000,4900};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,43},consKi_fast[2]={0.02,0.01},consKd_fast[2]={1100,5800};   // fast mode for both internal and external.

// //-------PID14
// double Kp_slow[2]={30,51}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,4900}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,41}, consKi_slow[2]={0.02,0.02}, consKd_slow[2]={1200,5600};
//                   //---Int,Ext
// double kp_fast[2]={30,57},ki_fast[2]={0.03,0.02},kd_fast[2]={1000,4700};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,43},consKi_fast[2]={0.02,0.02},consKd_fast[2]={1100,5500};   // fast mode for both internal and external.


// //-------PID15
// double Kp_slow[2]={30,51}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,4000}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,41}, consKi_slow[2]={0.02,0.02}, consKd_slow[2]={1200,5000};
//                   //---Int,Ext
// double kp_fast[2]={30,57},ki_fast[2]={0.03,0.02},kd_fast[2]={1000,4600};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,43},consKi_fast[2]={0.02,0.02},consKd_fast[2]={1100,5500};   // fast mode for both internal and external.

// //-------PID16
// double Kp_slow[2]={30,49}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,2000}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,41}, consKi_slow[2]={0.02,0.02}, consKd_slow[2]={1200,2100};
//                   //---Int,Ext
// double kp_fast[2]={30,57},ki_fast[2]={0.03,0.02},kd_fast[2]={1000,2300};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,43},consKi_fast[2]={0.02,0.02},consKd_fast[2]={1100,2500};   // fast mode for both internal and external.

// //-------PID17
// double Kp_slow[2]={30,48}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,1000}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,41}, consKi_slow[2]={0.02,0.03}, consKd_slow[2]={1200,900};
//                   //---Int,Ext
// double kp_fast[2]={30,58},ki_fast[2]={0.03,0.02},kd_fast[2]={1000,900};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,43},consKi_fast[2]={0.02,0.03},consKd_fast[2]={1100,800};   // fast mode for both internal and external.

// //-------PID18
// double Kp_slow[2]={30,46}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,910}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,39}, consKi_slow[2]={0.02,0.025}, consKd_slow[2]={1200,600};
//                   //---Int,Ext
// double kp_fast[2]={30,60},ki_fast[2]={0.03,0.03},kd_fast[2]={1000,700};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,45},consKi_fast[2]={0.02,0.03},consKd_fast[2]={1100,500};   // fast mode for both internal and external.

// //-------PID19
// double Kp_slow[2]={30,43}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,920}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,37}, consKi_slow[2]={0.02,0.025}, consKd_slow[2]={1200,620};
//                   //---Int,Ext
// double kp_fast[2]={30,55},ki_fast[2]={0.03,0.02},kd_fast[2]={1000,800};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,42},consKi_fast[2]={0.02,0.03},consKd_fast[2]={1100,600};   // fast mode for both internal and external.

// //-------PID21(OK)
// double Kp_slow[2]={30,32}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,1050}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,29}, consKi_slow[2]={0.02,0.022}, consKd_slow[2]={1200,800};
//                   //---Int,Ext
// double kp_fast[2]={30,50},ki_fast[2]={0.03,0.015},kd_fast[2]={1000,900};    // fast mode PID for both internal and external
// double consKp_fast[2]={29,37},consKi_fast[2]={0.02,0.02},consKd_fast[2]={1100,700};   // fast mode for both internal and external.

// //-------PID22
// double Kp_slow[2]={30,30}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,1100}; //slow mode heating for both external & internal probe.              
// double consKp_slow[2]={28,26}, consKi_slow[2]={0.02,0.022}, consKd_slow[2]={1200,820};
//                   //---Int,Ext
// double kp_fast[2]={30,50},ki_fast[2]={0.03,0.015},kd_fast[2]={1000,900};    // fast mode PID for both internal and external.
// double consKp_fast[2]={29,37},consKi_fast[2]={0.02,0.02},consKd_fast[2]={1100,700};   // fast mode for both internal and external.

//-------PID23
double Kp_slow[2]={30,31}, Ki_slow[2]={0.03,0.01}, Kd_slow[2]={1100,1060}; //slow mode heating for both external & internal probe.              
double consKp_slow[2]={28,28}, consKi_slow[2]={0.02,0.021}, consKd_slow[2]={1200,810};
                  //---Int,Ext
double kp_fast[2]={30,50},ki_fast[2]={0.03,0.015},kd_fast[2]={1000,900};    // fast mode PID for both internal and external
double consKp_fast[2]={29,37},consKi_fast[2]={0.02,0.02},consKd_fast[2]={1100,700};   // fast mode for both internal and external.


PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

HeaterPID_Class::HeaterPID_Class()
{}

void HeaterPID_Class :: HeaterPID_SETUP() 
{  
   pinMode(HEATER,OUTPUT);
   digitalWrite(HEATER,LOW);
}

//----------------------------------------PID function-----------------------------------------//
void HeaterPID_Class::Heater_PID_Function()
{ 
        Process.Setpoint_temperature_conversion();
        if(Inprocess_Set_Temp_Save==1)
        {
              Setpoint=Final_set_temperature+0.2;
              if(Setpoint<=100)
              {
                Internal_safety_cutoff=380;
                Serial2.print("Setpoint less than 100 :");
              }
              if(Setpoint>100)
              {
                Internal_safety_cutoff=600;
                Serial2.print("Setpoint >= 100 :");
              }
               Serial2.println(Internal_safety_cutoff);
              Inprocess_Set_Temp_Save=0;
        }
              if(PT1000_Detection_Occured==0)
              {
                  
                  if(SetPoint_for_Cal2==0)
                  {
                     Input = Internal_Temp_Post_Calb;
                     
                  }
                  if(SetPoint_for_Cal2==1)
                  {
                     Input = K_Type_emaFilter_Output;
                    //  Serial2.println("Intr cal2");
                    //  Serial2.println(Input);
                  }
                
              }
              if(PT1000_Detection_Occured==1)
              {  
                    if(SetPoint_for_Cal2==0)
                    {
                        Input = Temperature_After_Calibration;
                        
                    }
                    if(SetPoint_for_Cal2==1)
                    {
                        Input = Smoothed_PT1000_Temperature;
                        // Serial2.println("Extr cal2");
                        // Serial2.println(Input);
                    }
                
              }
//------------------------------------ PID logic-------------------------------------------------------//
    if(Final_Internal_Probe_Temp<=Internal_safety_cutoff)
    {  
      //  Serial2.println("ON heater");
       if(Slow_Fast_Mode_Flag==1) //---------------------------fast heating
       {  
            // Serial2.println("FAST  heating**************************************: "); 
            if( Input >= Setpoint)
            {
              digitalWrite(HEATER, LOW);
            }
            else
            {
                  if(once_heater_PID == 0)//------------execute only once
                  {
                        myPID.SetOutputLimits(0, WindowSize);
                        windowStartTime = millis();
                        // Heater_PID_setpoint();//-----------final setpoint selection loop for temperature for adjustment
                        //turn the PID on
                        myPID.SetMode(AUTOMATIC);
                        once_heater_PID = 1;
                        
                  } 
                   

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
                                  myPID.SetTunings(kp_fast[PT1000_Detection_Occured],ki_fast[PT1000_Detection_Occured] , kd_fast[PT1000_Detection_Occured]); 
                                  
                                }
                                else if((Setpoint - Input) <= set_input_cmp_factor)
                                {
                                  myPID.SetTunings(consKp_fast[PT1000_Detection_Occured], consKi_fast[PT1000_Detection_Occured], consKd_fast[PT1000_Detection_Occured]); 
                                  
                                }
                                      myPID.Compute();
                                      if (millis() - windowStartTime > WindowSize)
                                      { //time to shift the Relay Window
                                        windowStartTime += WindowSize;
                                      }
                                      if (Output < millis() - windowStartTime) digitalWrite(HEATER, LOW);
                                      else digitalWrite(HEATER, HIGH);
                       
               
            }


       } 
  
        if(Slow_Fast_Mode_Flag==0) //---------------------slow heating
        {   
          //  Serial2.println("slow  heating**************************************: ");
           if( Input >= Setpoint)
            {
              digitalWrite(HEATER, LOW);
              // Serial2.println("Input >");
            }
            else
            {

                      if(once_heater_PID == 0)//------------execute only once
                      {
                          myPID.SetOutputLimits(0, WindowSize_slow);
                          windowStartTime = millis();
                          // Heater_PID_setpoint();//-----------final setpoint selection loop for temperature for adjustment
                          myPID.SetMode(AUTOMATIC);
                          once_heater_PID = 1;
                          
                      } 
                     
             
                              if(Setpoint-0.2<=50)
                              {
                                  set_input_cmp_factor=14;
                                
                              }
                              if(Setpoint-0.2>50 && Setpoint-0.2<=90)
                              {
                                  set_input_cmp_factor=12;
                                
                              }
                              if(Setpoint-0.2>90)
                              {
                                    set_input_cmp_factor=14;
                              
                              }

                              // Serial.print("Kp_slow : "); 
                              // Serial.println(Kp_slow[External_probe_detection]);
                              // Serial.print("Ki_slow : "); 
                              // Serial.println(Ki_slow[External_probe_detection]);
                              // Serial.print("Kd_slow : "); 
                              // Serial.println(Kd_slow[External_probe_detection]);
                              // Serial.println("**********************************************"); 
                              // Serial.print("consKp_slow : "); 
                              // Serial.println(consKp_slow[External_probe_detection]);
                              // Serial.print("consKi_slow : "); 
                              // Serial.println(consKi_slow[External_probe_detection]);
                              // Serial.print("consKd_slow : "); 
                              // Serial.println(consKd_slow[External_probe_detection]);
                              // Serial.println("**********************************************"); 


                              if((Setpoint - Input) > set_input_cmp_factor)
                              {
                                myPID.SetTunings(Kp_slow[PT1000_Detection_Occured], Ki_slow[PT1000_Detection_Occured], Kd_slow[PT1000_Detection_Occured]); 
                                
                              }
                              else if((Setpoint - Input) <= set_input_cmp_factor)
                              {
                                myPID.SetTunings(consKp_slow[PT1000_Detection_Occured], consKi_slow[PT1000_Detection_Occured], consKd_slow[PT1000_Detection_Occured]); 
                                
                              }

                                                myPID.Compute();
                                                // * turn the output pin on/off based on pid output
                                                // ************************************************/
                                                if (millis() - windowStartTime > WindowSize_slow)
                                                { //time to shift the Relay Window
                                                      windowStartTime += WindowSize_slow;
                                                }  
                                                if (Output < millis() - windowStartTime) digitalWrite(HEATER, LOW);
                                                else digitalWrite(HEATER, HIGH);
                       


              } 

         }

    }
    if(Final_Internal_Probe_Temp>Internal_safety_cutoff)
    {    
        digitalWrite(HEATER,LOW);
        // Serial2.println("Heater OFF ");
    }

}




HeaterPID_Class HeaterPID = HeaterPID_Class();