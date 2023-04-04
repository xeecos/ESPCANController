#pragma once
#include "driver/twai.h"

enum CID
{
    CID_MOTION_START = 1,
    CID_MOTION_STOP,
    CID_MOTION_END_X,
    CID_MOTION_END_Y,
    CID_MOTION_END_Z,
    CID_X_ACCELERATION = 100,
    CID_Y_ACCELERATION,
    CID_Z_ACCELERATION,
    CID_X_ACCEL_DISTANCE,
    CID_Y_ACCEL_DISTANCE,
    CID_Z_ACCEL_DISTANCE,
    CID_X_DEACCEL_DISTANCE,
    CID_Y_DEACCEL_DISTANCE,
    CID_Z_DEACCEL_DISTANCE,
    CID_X_TOTAL_DISTANCE,
    CID_Y_TOTAL_DISTANCE,
    CID_Z_TOTAL_DISTANCE,
} ;
void canbus_init();
bool canbus_available();
void canbus_receive();
void canbus_send(twai_message_t frame);