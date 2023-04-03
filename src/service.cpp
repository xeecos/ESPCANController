#include "service.h"
#include <Arduino.h>
#include "canbus.h"
#include "planner.h"
#include "motion.h"
#include "log.h"
void service_init()
{
    LOG_INIT(115200);
    canbus_init();
    motion_init();
    planner_init();
}
void service_run()
{
    if(canbus_available())
    {
        canbus_receive();
    }
}