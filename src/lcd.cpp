#include "lcd.h"
#include "config.h"
#include <SSD1306.h>
#include "planner.h"
#include "encoder.h"
Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);
void lcd_init()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    // display.fillRect(1, 22, 125, 1, WHITE);
}
void lcd_show_string(const char *str, int x, int y, int size)
{
    display.setTextSize(size);
    display.setTextColor(WHITE);
    display.setCursor(x, y);
    display.print(str);
}
void lcd_show_message(const char *line1, const char *line2, const char *line3)
{
    display.clearDisplay();
    lcd_show_string(line1, 4, 4, 2);
    lcd_show_string(line2, 4, 27, 2);
    lcd_show_string(line3, 4, 50, 2);
    display.display();
}
void lcd_clear()
{
    display.clearDisplay();
}
void lcd_display()
{
    display.display();
}

int _line_number = 0;
int _last_line_number = 0;
long _line_time = 0;
bool _line_status = false;
bool _force_update = false;
void lcd_switch_status()
{
    if(_line_number==0)
    {
        _line_number = _last_line_number;
    }
    else
    {
        _last_line_number = _line_number;
        lcd_line_reset();
    }
}
void lcd_line_up()
{
    _line_number--;
    if (_line_number < 1)
    {
        _line_number = 1;
    }
    else
    {
        encoder_mark();
    }
}

void lcd_line_down()
{
    _line_number++;
    if (_line_number > 3)
    {
        _line_number = 3;
    }
    else
    {
        encoder_mark();
    }
}
void lcd_line_reset()
{
    _line_number = 0;
    encoder_mark();
}
int lcd_get_line_number()
{
    return _line_number;
}
void lcd_run()
{
    
}

void lcd_update()
{
    _force_update = true;
}