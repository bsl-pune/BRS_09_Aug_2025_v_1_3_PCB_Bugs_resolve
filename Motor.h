#ifndef Motor_h
#define Motor_h

//-------------------------Motor pin declartion-------------------------------------//
// #define Direction  12 //32
// #define pwm  13//19
// #define feedback 11

#define Direction  31 //32
#define pwm  18  //19
#define feedback 32

#define pwm_Overhead_Motor  13//19
#define feedback_Overhead_Motor  11//19
#define Overhead_Motor_Detection_Pin  10

class Motor_Class
{
  public :
  Motor_Class();
  void Motor_SETUP();
  void PID_motor_set();
  void PID_Overhead_Stirrer_Motor();
  void Ramp_up(int val1);
  void Feedback_update();
  void Overhead_Motor_check_update();
  void Motor_Stop_During_OHS_Interuption();

};

extern Motor_Class BLDC;

#endif
