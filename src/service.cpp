#include "service.h"
#include <Arduino.h>
#include "canbus.h"
#include "planner.h"
#include "motion.h"
#include "uart.h"
#include "button.h"
#include "lcd.h"
#include "encoder.h"
#include "buzzer.h"
#include "tf.h"
void service_init()
{
    uart_init();
    canbus_init();
    encoder_init();
    lcd_init();
    tf_init();
    button_init();
    buzzer_init();
    planner_init();
    motion_init();
}
void service_run()
{
    if(canbus_available())
    {
        canbus_receive();
    }
    if(uart_available())
    {
        uart_receive();
    }
}