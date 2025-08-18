
#ifndef Process_h
#define Process_h

#define Set_LED 21
#define Process_LED 22
#define HEATER 28
#define relay 27

class ProcessClass
{
  public:
  ProcessClass();
  void set_display();
  void PROCESS_SETUP();
  void PROCESS_START();
  void Setting_menu();
  void Setpoint_temperature_conversion();

  void Temp_readings_ticker_update() ;
  void Temp_Reading_After_Calibration();
  
};
extern ProcessClass Process;

#endif