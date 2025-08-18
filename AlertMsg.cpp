#include "ext_var.h"

AlertMsg_Class::AlertMsg_Class()
{} 
// #define Door_open_limit_switch 28

void  DoorOpenAlert();

void AlertMsg_Class::AlertMsg_SetUp()
{
  //  pinMode(Door_open_limit_switch, INPUT_PULLUP);  
  //  attachInterrupt(Door_open_limit_switch, DoorOpenAlert, CHANGE);  
}




AlertMsg_Class AlertMsg = AlertMsg_Class();