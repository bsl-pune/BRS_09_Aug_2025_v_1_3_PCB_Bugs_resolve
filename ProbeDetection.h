#ifndef ProbeDetection_h
#define ProbeDetection_h 

#define PT100_1_Detection_Pin 26
#define PT1000_Detection_Pin 25
 
class ProbeDetection_class
{
   public :
   ProbeDetection_class();
   void SetupProbeDetection();
   void PT100_check_update();
   void PT1000_check_update();
};

extern ProbeDetection_class ProbeDetection;
#endif
