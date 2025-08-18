#ifndef RTD_Sensor_h
#define RTD_Sensor_h

class RTD_Sensor_class
{
   public :
   RTD_Sensor_class();
   void RTDSetup();
   void PT100_Probe1_Temperature_Reading_update();
   void  PT1000_Temperature_Reading_update();
   
};

extern RTD_Sensor_class RTD_Sensor;
#endif
