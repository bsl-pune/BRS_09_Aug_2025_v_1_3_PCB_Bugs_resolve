
#include "ext_var.h"
#include <PID1_v2.h>

void Overhead_Motor_Detection();
bool Overhead_detection_read=0;
void Overhead_Motor_checkStatus();
Ticker Overhead_Motor_check(Overhead_Motor_checkStatus, 100, 0, MILLIS);

double Setpoint1, Input1, Output1;
// double Kp_m=0.06, Ki_m=0.04, Kd_m=0.002;
double Kp_m=0.04, Ki_m=0.03, Kd_m=0.002;  

PID1 myPID1(&Input1, &Output1, &Setpoint1, Kp_m, Ki_m, Kd_m, DIRECT1);
long set_speed = 0;
int A_speed = 255;
int Overhead_stirrer_motor_PWM_Map=0;
// int A_speed_val=255;
int counter1[3] = {0};
int counter2 = 0;
int z = 0;
long pulses = 0;
long Current_RPM1=0;

int old_dimetime = 0;
int dimtime=0,change_ramp =25,ramp_val=0;
bool Once_mtr=0,Motor_Stop_During_OHS_Interuption_Flag=0;

Motor_Class::Motor_Class()
{}

void Motor_Class :: Motor_SETUP()
{
    pinMode(Direction, OUTPUT);
    pinMode(pwm, OUTPUT);
    pinMode(feedback, INPUT);
    digitalWrite(Direction, LOW);

    pinMode(pwm_Overhead_Motor, OUTPUT);
    pinMode(feedback_Overhead_Motor, INPUT);
    // digitalWrite(Direction, LOW);
    
    digitalWrite(pwm, HIGH);
    // digitalWrite(pwm_Overhead_Motor, LOW);//----------Overhead stirrer motor PWM
 
    analogWriteFrequency(20);
  
    myPID1.SetOutputLimits1(0, 255);
    myPID1.SetMode1(AUTOMATIC1);

    pinMode(Overhead_Motor_Detection_Pin, INPUT_PULLUP); //INPUT_PULLUP 
    attachInterrupt(Overhead_Motor_Detection_Pin, Overhead_Motor_Detection, CHANGE); 
    Overhead_Motor_check.start();
     
}

void Motor_Class::PID_motor_set()
{      

       dimtime = Set_speed; 
       Setpoint1 =old_dimetime;
       Input1 = Current_RPM1;
       myPID1.Compute1();
      // myPID1.SetTunings1(Kp_m, Ki_m, Kd_m);
      // if(Int_Motor_Spd_control_flag==0)
      
        A_speed = map(Output1,255,0,165,241);
        // A_speed = map(Set_speed,300,1500,242,165);
        // A_speed = map(,200,1500,240,180); 
        if(Set_speed >= 1)
        { 
            // myPID1.Compute1();
            analogWrite(pwm, A_speed);
         
        }
        else if(Set_speed < 1)
        {
          //  myPID1.Initialize1();
                if(Motor_Stop_Flagg==1)  //----------------If set RPM changes from 1500 to 0
                {
                                analogWrite(pwm, Stop_pwm);
                                if (Stop_pwm >= 245) 
                                {
                                  // Serial2.println("stop");
                                  digitalWrite(pwm, HIGH);
                                  tickers.Motor_slow_stop_tick_stop();
                                  Stop_pwm = 233;
                                  Motor_stop_After_process_exit=0;
                                  Motor_Stop_Flagg=0;
                                 
                                }
                }
                if(Motor_Stop_Flagg==0)
                      digitalWrite(pwm, HIGH);

          //  digitalWrite(pwm, HIGH);
           old_dimetime=dimtime=ramp_val=0;
           Output1=0;
           pulses = 0;
           Current_RPM1=0;
        }
      //  A_speed = map(Output1,255,0,0,255);  //0,255, 255, 0
       
      //  Serial2.print("Output1 : ");
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
      // delay(50);
      
   
}
void Motor_Class::PID_Overhead_Stirrer_Motor()
{      
        // A_speed = map(Set_speed,300,1500,242,165);
        Overhead_stirrer_motor_PWM_Map = map(OHS_Set_speed,50,1000,31,210); //----------Overhead stirrer motor
         if(OHS_Set_speed >= 1)
        { 
           analogWrite(pwm_Overhead_Motor, Overhead_stirrer_motor_PWM_Map);
        }
        else
        {
          digitalWrite(pwm_Overhead_Motor, LOW); //-------Overhead stirrer PWM
          Current_RPM1=0;
        }
    
}

void Motor_Class::Ramp_up(int val1) //------------ramp function
{
  // if(Set_speed!=0)
  // {
        if(old_dimetime <= dimtime)
        {
          ramp_val++;
          if(ramp_val >= val1)
          {
            ramp_val = 0;
            if(old_dimetime < dimtime)
            {
              old_dimetime += 20; //-----------motor set point will be incremented by 20 
              // Serial2.print("old_dimetime :");
              // Serial2.println(old_dimetime);
            }
            else
            old_dimetime = dimtime;
          }
          

        }
        if(old_dimetime >= dimtime)
        {
          ramp_val++;
          if(ramp_val >= val1)
          {
            ramp_val = 0;
            if(old_dimetime > dimtime)
            {
              old_dimetime -= 20; //-----------motor set point will be decremented by 20 
            }
            else
            old_dimetime = dimtime;
          }
        }
  // }
}

void Overhead_Motor_checkStatus() 
{
        Overhead_detection_read = digitalRead(Overhead_Motor_Detection_Pin);
        Overhead_Motor_connected_Flag = (Overhead_detection_read) ? 0 : 1;
         if(Overhead_Motor_connected_Flag==1 && Set_speed!=0)
        {
          Stop_pwm=233;
          Motor_Stop_Flagg=1;
          tickers.Motor_slow_stop_tick_start();
          Motor_Stop_During_OHS_Interuption_Flag=1;
           Serial2.println("bottom motor :");
        }
        // Serial2.print("Overhead_Motor_connected_Flag :");
        // Serial2.println(Overhead_Motor_connected_Flag);
        OHS_Set_speed=0;
        Set_speed=0; 
        Overhead_Motor_check.stop();
        
}
void Overhead_Motor_Detection()
{          
        // Set_speed=0; 
        old_dimetime=dimtime=ramp_val=0;
        Output1=0;
        pulses = 0;
        Current_RPM1=0;
        // digitalWrite(pwm, HIGH); 
        digitalWrite(pwm_Overhead_Motor, LOW);
        Overhead_Motor_check.start();
        
}
void Motor_Class::Motor_Stop_During_OHS_Interuption()
{
                if(Motor_Stop_Flagg==1)
                {
                                analogWrite(pwm, Stop_pwm);
                                if (Stop_pwm >= 245) 
                                {
                                  // Serial2.println("stop");
                                  digitalWrite(pwm, HIGH);
                                  tickers.Motor_slow_stop_tick_stop();
                                  Stop_pwm = 233;
                                  Motor_Stop_During_OHS_Interuption_Flag=0;
                                  Motor_stop_In_Recipe=0;
                                  old_dimetime=dimtime=ramp_val=0;
                                  Output1=0;
                                  pulses = 0;
                                  Current_RPM1=0;
                                  Motor_Stop_Flagg=0;
                                 
                                }
                }
                if(Motor_Stop_Flagg==0)
                      digitalWrite(pwm, HIGH);
}

void Motor_Class::Overhead_Motor_check_update() 
{
    Overhead_Motor_check.update();
}



Motor_Class BLDC = Motor_Class();
