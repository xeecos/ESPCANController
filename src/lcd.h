#pragma once
void lcd_init();
void lcd_clear();
void lcd_display();
void lcd_show_string(const char *str, int x, int y, int size=1);
void lcd_show_message(const char *line1,const char *line2,const char *line3);
void lcd_line_up();
void lcd_line_down();
void lcd_line_reset();
int lcd_get_line_number();
void lcd_run();
void lcd_update();
void lcd_switch_status();