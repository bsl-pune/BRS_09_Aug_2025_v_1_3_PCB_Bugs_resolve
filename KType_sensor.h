#ifndef KType_sensor_h
#define KType_sensor_h

class KType_sensor_class
{
  public:
  KType_sensor_class();
  void KType_Reading_Update();
  void KType_setup();
  void Internal_Probe_Temperature();
  
};
extern KType_sensor_class KType_sensor;

#endif