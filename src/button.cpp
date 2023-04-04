#include "button.h"
#include <Arduino.h>
#include "config.h"
#include "lcd.h"
#include "button.h"
#include "planner.h"
bool button_ok_pressed = false;
bool button_xm_pressed = false;
bool button_xp_pressed = false;
bool button_ym_pressed = false;
bool button_yp_pressed = false;
bool encoder_key_pressed = false;
long _last_pressed = 0;
int last_status = -1;
bool button_check()
{
    long t = millis();
    if(t-_last_pressed<300)
    {
        return false;
    }
    _last_pressed = t;
    return true;
}
void encoder_key_isr()
{
    encoder_key_pressed = !digitalRead(ENCODER_KEY_PIN);
    if(encoder_key_pressed && button_check())
    {
    }
}
void button_ok_isr()
{
    button_ok_pressed = !digitalRead(BUTTON_OK);
    if(button_ok_pressed && button_check())
    {
        lcd_switch_status();
    }
}
void button_xm_isr()
{
    button_xm_pressed = !digitalRead(BUTTON_XM);
    if(button_xm_pressed && button_check())
    {
    }
}
void button_xp_isr()
{
    button_xp_pressed = !digitalRead(BUTTON_XP);
    if(button_xp_pressed && button_check())
    {
    }
}
void button_ym_isr()
{
    button_ym_pressed = !digitalRead(BUTTON_YM);
    if(button_ym_pressed && button_check())
    {
        lcd_line_up();
    }
}
void button_yp_isr()
{
    button_yp_pressed = !digitalRead(BUTTON_YP);
    if(button_yp_pressed && button_check())
    {
        lcd_line_down();
    }
}
void button_init()
{
    pinMode(ENCODER_KEY_PIN, INPUT_PULLUP);
    pinMode(BUTTON_OK, INPUT_PULLUP);
    pinMode(BUTTON_XM, INPUT);
    pinMode(BUTTON_XP, INPUT);
    pinMode(BUTTON_YM, INPUT);
    pinMode(BUTTON_YP, INPUT);
    attachInterrupt((ENCODER_KEY_PIN), encoder_key_isr, CHANGE);
    attachInterrupt((BUTTON_OK), button_ok_isr, CHANGE);
    attachInterrupt((BUTTON_XM), button_xm_isr, CHANGE);
    attachInterrupt((BUTTON_XP), button_xp_isr, CHANGE);
    attachInterrupt((BUTTON_YM), button_ym_isr, CHANGE);
    attachInterrupt((BUTTON_YP), button_yp_isr, CHANGE);
}

int button_get_status()
{
    return (button_ok_pressed<<0) | (button_xm_pressed<<1) | (button_xp_pressed<<2) | (button_ym_pressed<<3) | (button_yp_pressed<<4) | (encoder_key_pressed<<5);
}
bool button_has_changed()
{
    int status = button_get_status();
    if(last_status!=status)
    {
        last_status=status;
        return true;
    }
    return false;
}
void button_run()
{
    if(button_has_changed())
    {
        // lcd_clear();
        // char *str = (char *)malloc(20);
        // sprintf(str, "button: %d\0", button_get_status());
        // lcd_show_string(str, 12, 12);
        // free(str);
        // lcd_display();
    }
}