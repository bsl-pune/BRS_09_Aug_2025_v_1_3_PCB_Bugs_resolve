#include "ext_var.h"

void PT100_1_Detection();
void PT1000_Detection();
bool PT100_Probe_Read=0;
void PT100_checkStatus();
Ticker PT100_check(PT100_checkStatus, 100, 0, MILLIS);
//----------------PT1000 Probe(For Solution)----------------------//
bool PT1000_Probe_Read=0,once_det_read=0;
void PT1000_checkStatus();
Ticker PT1000_check(PT1000_checkStatus, 100, 0, MILLIS);

ProbeDetection_class::ProbeDetection_class()
{}

void ProbeDetection_class :: SetupProbeDetection() 
{  
  pinMode(PT100_1_Detection_Pin, INPUT_PULLUP);  
  attachInterrupt(PT100_1_Detection_Pin, PT100_1_Detection, CHANGE);  
  pinMode(PT1000_Detection_Pin, INPUT_PULLUP);  
  attachInterrupt(PT1000_Detection_Pin, PT1000_Detection, CHANGE);  
  PT100_check.start(); 
  PT1000_check.start();
  once_det_read=1;

}

//--------------PT100 Detection(Vapour temparature)-----------------------PT100_1//
void PT100_checkStatus() 
{
        PT100_Probe_Read = digitalRead(PT100_1_Detection_Pin) ;
        PT100_1_Detection_Occured = (PT100_Probe_Read) ? 0 : 1;
        Probe1_X=25.00, Probe1_P=0.01, Probe1_Q=10, Probe1_R=200000, Probe1_K=0.001;
        // Serial2.print("RTD :");
        // Serial2.println(PT100_1_Detection_Occured);
        PT100_check.stop();
        
}
void PT100_1_Detection()
{
        PT100_check.start();    
}
void ProbeDetection_class::PT100_check_update() 
{
    PT100_check.update();
}


//--------------PT1000 Detection-----------------------//
void PT1000_checkStatus() 
{
        PT1000_Probe_Read = digitalRead(PT1000_Detection_Pin) ;
        PT1000_Detection_Occured = (PT1000_Probe_Read) ? 0 : 1;
        if(Exit_Process==1)
        {
          // Serial2.println("probeee");
          Enter_Button=0;
          mode=1;
          Exit_Process=0;
          
        }
        PT1000_X=25.00, PT1000_P=0.01, PT1000_Q=10, PT1000_R=200000, PT1000_K=0.001;
        digitalWrite(BUZZER, LOW); 
        // Serial2.print("PT1000 :");
        // Serial2.println(PT1000_Detection_Occured);
        PT1000_check.stop();
        
}
void PT1000_Detection()
{
        PT1000_check.start();
           
}
void ProbeDetection_class::PT1000_check_update() 
{
    PT1000_check.update();
}


ProbeDetection_class ProbeDetection = ProbeDetection_class();