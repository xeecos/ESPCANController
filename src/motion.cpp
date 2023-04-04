#include "motion.h"
#include "utils.h"
#include "planner.h"
#include "canbus.h"
#include <Arduino.h>

#define ACCELERATION    400.0f
#define STEPS_PER_MM_X  100
#define STEPS_PER_MM_Y  100
#define STEPS_PER_MM_Z  100

QueueHandle_t event_queue = xQueueCreate(1, 32);
char _task_tx[32];
void IRAM_ATTR motion_task(void *arg)
{
    char _task_rx[32];
    while(1)
    {
        xQueueReceive(event_queue, (void*)_task_rx, portMAX_DELAY);
        if(!planner_read())
        {
            delay(1000);
            motion_next();
        }
    }
}
void motion_init()
{
    xTaskCreatePinnedToCore(motion_task, "motion_task", 4096, NULL, 10, NULL, 0);
    motion_next();
}

void motion_run(float dx, float dy, float dz, float distance, float speed)
{
    float abs_dx = dx<0?-dx:dx;
    float abs_dy = dy<0?-dy:dy;
    float abs_dz = dz<0?-dz:dz;
    float accel_x = ACCELERATION * dx / distance;
    float accel_y = ACCELERATION * dy / distance;
    float accel_z = ACCELERATION * dz / distance;
    float speed_limit = sqrtf(distance * ACCELERATION);
    speed = speed > speed_limit ? speed_limit : speed;
    float speed_x = speed * dx / distance;
    float speed_y = speed * dy / distance;
    float speed_z = speed * dz / distance;
    float accel_distance_x = speed_x * speed_x / (accel_x * 2);
    float accel_distance_y = speed_y * speed_y / (accel_y * 2);
    float accel_distance_z = speed_z * speed_z / (accel_z * 2);
    float deaccel_distance_x = accel_distance_x;
    float deaccel_distance_y = accel_distance_y;
    float deaccel_distance_z = accel_distance_z;
    twai_message_t frame;
    Long2Bytes lv;
    Uint2Bytes uv;
    frame.identifier = CID_X_ACCELERATION;
    frame.data_length_code = 4;
    lv.longValue = accel_x * STEPS_PER_MM_X;
    frame.data[0] = lv.bytes[0];
    frame.data[1] = lv.bytes[1];
    frame.data[2] = lv.bytes[2];
    frame.data[3] = lv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_X_ACCEL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = accel_distance_x * STEPS_PER_MM_X;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_X_DEACCEL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = deaccel_distance_x * STEPS_PER_MM_X;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_X_TOTAL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = abs_dx * STEPS_PER_MM_X;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_Y_ACCELERATION;
    frame.data_length_code = 4;
    lv.longValue = accel_y * STEPS_PER_MM_Y;
    frame.data[0] = lv.bytes[0];
    frame.data[1] = lv.bytes[1];
    frame.data[2] = lv.bytes[2];
    frame.data[3] = lv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_Y_ACCEL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = accel_distance_y * STEPS_PER_MM_Y;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_Y_DEACCEL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = deaccel_distance_y * STEPS_PER_MM_Y;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_Y_TOTAL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = abs_dy * STEPS_PER_MM_Y;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_Z_ACCELERATION;
    frame.data_length_code = 4;
    lv.longValue = accel_z * STEPS_PER_MM_Z;
    frame.data[0] = lv.bytes[0];
    frame.data[1] = lv.bytes[1];
    frame.data[2] = lv.bytes[2];
    frame.data[3] = lv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_Z_ACCEL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = accel_distance_z * STEPS_PER_MM_Z;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_Z_DEACCEL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = deaccel_distance_z * STEPS_PER_MM_Z;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    frame.identifier = CID_Z_TOTAL_DISTANCE;
    frame.data_length_code = 4;
    uv.uint32Value = abs_dz * STEPS_PER_MM_Z;
    frame.data[0] = uv.bytes[0];
    frame.data[1] = uv.bytes[1];
    frame.data[2] = uv.bytes[2];
    frame.data[3] = uv.bytes[3];
    canbus_send(frame);
    if(abs_dx>abs_dy&&abs_dx>abs_dz)
    {
        frame.identifier = CID_MOTION_END_X;
        frame.data_length_code = 0;
        canbus_send(frame);
    }
    if(abs_dy>abs_dx&&abs_dy>abs_dz)
    {
        frame.identifier = CID_MOTION_END_Y;
        frame.data_length_code = 0;
        canbus_send(frame);
    }
    if(abs_dz>abs_dx&&abs_dz>abs_dy)
    {
        frame.identifier = CID_MOTION_END_Z;
        frame.data_length_code = 0;
        canbus_send(frame);
    }
    frame.identifier = CID_MOTION_START;
    frame.data_length_code = 0;
    canbus_send(frame);
}

void motion_next()
{
    xQueueSendFromISR(event_queue, (void*)_task_tx, (TickType_t)0);
}