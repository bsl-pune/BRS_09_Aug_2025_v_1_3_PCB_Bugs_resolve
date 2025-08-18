#ifndef DwinDisplay_h
#define DwinDisplay_h 
 
class DwinDisplay_class
{
   public :
   DwinDisplay_class();
   void Data_Arduino_to_Display_for_set(int temp_set);
   void Data_Arduino_to_Display_Current_Temp(float temp_set);
   void Data_Arduino_to_Display_for_set_RPM(int RPM_set);
   void Data_Arduino_to_Display_Inprocess_Current_RPM(int Current_RPM );
   void Data_Arduino_to_Display_set_Hour(int Hour_set);
   void Data_to_Display_graph(float temp_curve);
   void  Data_to_Display_Time_graph(int Time_Graph);
   void Inprocess_hour();
   void Data_Arduino_to_Display_set_Min(int Min_set);
   void Inprocess_Min();
   void setPage(int page);
   void Inprocess_Temperature(float Inprocess_Temp);
   void Save_Temperature(float Save_Temp);
   void Save_hour(int Save_Hour);
   void Save_Min(int Save_Min);
   void Data_controller_to_Display_Vapour_Temp(float Vapour_Temp );
   void Data_controller_to_Display_Inprocess_Vapour_Temp(float Process_Vapour_Temp);
   void Data_Arduino_to_Display_Internal_SAFE_TEMP(int Internal_Safe_Temperature);
   void Data_Arduino_to_Display_External_SAFE_TEMP(int External_Safe_Temperature);
   void Data_Arduino_to_Display_Vapour_SAFE_TEMP(int Vapour_Safe_Temperature);
   
   void Data_Arduino_to_Display_Pressure_Calb(int Pressure_Calb_for_display);
   void Data_Arduino_to_Display_RPM_Calb(int RPM_Calb_for_display);
   void Data_Arduino_to_Display_RPM_Calb_current(int RPM_Calb_current_for_display);
   
   void  Data_Arduino_to_Display_Cal1_Master_Temp(int Cal1_Master_Temp);
   void Data_Arduino_to_Display_Cal1_Current_Temp(float Cal1_Current_Temp);
   void Data_Arduino_to_Display_Cal2_Low_Set_Temp(int Cal2_Low_Set_Temp);
   void Data_Arduino_to_Display_Cal2_High_Set_Temp(int Cal2_High_Set_Temp);
   void Data_Arduino_to_Display_Cal2_Current_Temp(float Cal2_Current_Temp);
   void Data_Arduino_to_Display_Cal2_RPM(int Cal2_RPM);
   void Data_Arduino_to_Display_Cal2_Hour(int Cal2_Hour);
   void Data_Arduino_to_Display_Cal2_Min(int Cal2_Min);
   void Data_Arduino_to_Display_Cal2_Master_Temp(int Cal2_master_Temp);
   void Data_Arduino_to_Display_Cal2_Set_Temp_Heating(int Cal2_Heating);

   void Data_to_Display_Receipe_Set_Temp_Step0(int Step0_Set_Temp);
   void Data_to_Display_Receipe_Set_RPM_Step0(int Step0_Set_RPM);
   void Data_to_Display_Receipe_Set_Hour_Step0(int Step0_Set_Hour);
   void Data_to_Display_Receipe_Set_Min_Step0(int Step0_Set_Min);

  void Data_to_Display_Receipe_Set_Temp_Step1(int Step1_Set_Temp);
   void Data_to_Display_Receipe_Set_RPM_Step1(int Step1_Set_RPM);
   void Data_to_Display_Receipe_Set_Hour_Step1(int Step1_Set_Hour);
   void Data_to_Display_Receipe_Set_Min_Step1(int Step1_Set_Min);

   void Data_to_Display_Receipe_Set_Temp_Step2(int Step2_Set_Temp);
   void Data_to_Display_Receipe_Set_RPM_Step2(int Step2_Set_RPM);
   void Data_to_Display_Receipe_Set_Hour_Step2(int Step2_Set_Hour);
   void Data_to_Display_Receipe_Set_Min_Step2(int Step2_Set_Min);

   void Data_to_Display_Receipe_Set_Temp_Step3(int Step3_Set_Temp);
   void Data_to_Display_Receipe_Set_RPM_Step3(int Step3_Set_RPM);
   void Data_to_Display_Receipe_Set_Hour_Step3(int Step3_Set_Hour);
   void Data_to_Display_Receipe_Set_Min_Step3(int Step3_Set_Min);

   void Data_to_Display_Receipe_Set_Temp_Step4(int Step4_Set_Temp);
   void Data_to_Display_Receipe_Set_RPM_Step4(int Step4_Set_RPM);
   void Data_to_Display_Receipe_Set_Hour_Step4(int Step4_Set_Hour);
   void Data_to_Display_Receipe_Set_Min_Step4(int Step4_Set_Min);

   void Data_to_Display_Receipe_Set_Temp_Step5(int Step5_Set_Temp);
   void Data_to_Display_Receipe_Set_RPM_Step5(int Step5_Set_RPM);
   void Data_to_Display_Receipe_Set_Hour_Step5(int Step5_Set_Hour);
   void Data_to_Display_Receipe_Set_Min_Step5(int Step5_Set_Min);
 
   void Data_to_Display_Receipe(int Rcp_count);
   
};

extern DwinDisplay_class DwinDisplay;
#endif