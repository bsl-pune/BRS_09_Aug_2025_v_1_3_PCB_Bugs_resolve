#ifndef HeaterPID_h
#define HeaterPID_h 

#define HEATER 28

class HeaterPID_Class
{
   public :
   HeaterPID_Class();
   void HeaterPID_SETUP();
   void Heater_PID_Function();
   
   
};
extern HeaterPID_Class HeaterPID;

#endif