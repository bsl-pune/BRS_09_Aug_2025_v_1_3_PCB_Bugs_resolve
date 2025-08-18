#ifndef tickers_h
#define tickers_h

#define BUZZER 15

class tickers_class
{
  public:
  tickers_class();
  void tickers_SETUP();
  void  BUZZ_INTERVAL(int i);
  void VersionDisplay_update();
  void Button_update();
  void LongPress7sec_update();
  void Encoder_Fast_Inc_Dec_update();
  void toggle_display_update();
  void Process_stop_by_key1_ticker_start();
  void In_Process_Ticker_Update();
  void In_process_Set_RPM_show_start();
  void Inprocess_Lamp_glow_ticker_start();
  void Inprocess_Lamp_glow_ticker_update();
  void Internal_probe_short_open_ticker_start();
  void Internal_probe_short_open_ticker_update();
  void PT1000_Not_Detected_ticker_start();
  void PT1000_Not_Detected_ticker_update();
  void Motor_slow_stop_tick_start();
  void Motor_slow_stop_tick_update();
  void Motor_slow_stop_tick_stop();
  void initial_temp_inc_check_ticker_start();
  void initial_temp_inc_check_ticker_update();
  void initial_temp_inc_check_ticker_stop();
  void Ramp_ticker_update();
  void Int_Motor_Spd_control_tick_start();
  void Int_Motor_Spd_control_tick_update();
  void SSR_cutoff_Reach_ticker_start();
  void SSR_cutoff_Reach_ticker_update();
  void Calibration_save_ticker_start();
  void Calibration_save_ticker_update();
  
};
extern tickers_class tickers;

#endif