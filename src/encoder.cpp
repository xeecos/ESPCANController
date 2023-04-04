#include "encoder.h"
#include <Arduino.h>
#include "config.h"
#include "lcd.h"
#include "planner.h"
int _encoder_position = 0;
int _encoder_start_position = 0;
long time_a = 0;
long time_b = 0;
long last_time_a = 0;
long last_time_b = 0;
int level_a = 0;
int level_b = 0;
bool has_changed = false;
void encoder_a_isr()
{
    int res = 0;
    for (int i = 0; i < 10; i++)
    {
        res += digitalRead(ENCODER_A_PIN);
        delayMicroseconds(10);
    }
    level_a = res > 5 ? 1 : 0;
    if (level_a == 1 && level_b == 0)
    {
        _encoder_position--;
        has_changed = true;
    }
}
void encoder_b_isr()
{
    int res = 0;
    for (int i = 0; i < 10; i++)
    {
        res += digitalRead(ENCODER_B_PIN);
        delayMicroseconds(10);
    }
    level_b = res > 5 ? 1 : 0;
    if (level_b == 1 && level_a == 0)
    {
        _encoder_position++;
        has_changed = true;
    }
}
void encoder_init()
{
    pinMode(ENCODER_A_PIN, INPUT_PULLUP);
    pinMode(ENCODER_B_PIN, INPUT_PULLUP);
    attachInterrupt((ENCODER_A_PIN), encoder_a_isr, CHANGE);
    attachInterrupt((ENCODER_B_PIN), encoder_b_isr, CHANGE);
}
int encoder_get_position()
{
    has_changed = false;
    return _encoder_position - _encoder_start_position;
}
void encoder_mark()
{
    _encoder_start_position = _encoder_position;
}
bool encoder_has_changed()
{
    return has_changed;
}
void encoder_run()
{
    if (encoder_has_changed())
    {
        // lcd_clear();
        // char *str = (char *)malloc(20);
        // sprintf(str, "Encoder: %d\0", encoder_get_position());
        // lcd_show_string(str, 12, 12);
        // free(str);
        // lcd_display();
    }
}