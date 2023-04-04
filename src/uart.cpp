#include "uart.h"
#include "planner.h"
String _command = "";

float last_x;
float last_y;
float last_z;
int last_g;
int last_m;
float last_f;
float last_s;
void uart_init()
{
    HWSerial.begin(115200);
}
int uart_available()
{
    return HWSerial.available();
}
void uart_receive()
{
    char c = HWSerial.read();
    _command += c;
    if (c == '\n')
    {
        bool start_x = false, start_y = false, start_z = false, start_g = false, start_m = false, start_f = false, start_s = false;
        bool has_x = false, has_y = false, has_z = false, has_g = false, has_m = false, has_f = false, has_s = false;
        float x, y, z;
        int g, m, s, f;
        String str = "";
        for (int i = 0, count = _command.length(); i < count; i++)
        {
            char c = _command.charAt(i);
            if (c == 'x' || c == 'X')
            {
                start_x = true;
            }
            else if (c == 'y' || c == 'Y')
            {
                start_y = true;
            }
            else if (c == 'g' || c == 'G')
            {
                start_g = true;
            }
            else if (c == 'm' || c == 'M')
            {
                start_m = true;
            }
            else if (c == 's' || c == 'S')
            {
                start_s = true;
            }
            else if (c == 'f' || c == 'F')
            {
                start_f = true;
            }
            else if (c == ' ' || c == '\n')
            {
                if (start_x)
                {
                    x = str.toFloat();
                    str = "";
                    has_x = true;
                    start_x = false;
                }
                if (start_y)
                {
                    y = str.toFloat();
                    str = "";
                    has_y = true;
                    start_y = false;
                }
                if (start_g)
                {
                    g = str.toInt();
                    str = "";
                    has_g = true;
                    start_g = false;
                }
                if (start_m)
                {
                    m = str.toInt();
                    str = "";
                    has_m = true;
                    start_m = false;
                }
                if (start_f)
                {
                    f = str.toInt();
                    str = "";
                    has_f = true;
                    start_f = false;
                }
                if (start_s)
                {
                    s = str.toInt();
                    str = "";
                    has_s = true;
                    start_s = false;
                }
            }
            else
            {
                if (start_x || start_y || start_z || start_g || start_m || start_s || start_f)
                {
                    str += c;
                }
            }
        }
        if (has_x)
        {
            last_x = x;
        }
        if (has_y)
        {
            last_y = y;
        }
        if (has_z)
        {
            last_z = z;
        }
        if (has_g)
        {
            last_g = g;
        }
        if (has_m)
        {
            last_m = m;
        }
        if (has_f)
        {
            last_f = s;
        }
        if (has_s)
        {
            last_s = s;
        }
        if (has_g)
        {
            if (last_g == 1)
            {
                planner_add_position(last_x, last_y, last_z, last_f / 60.0);
            }
        }
        else if (has_m)
        {
        }
        _command = "";
        uart_send("ok\n");
    }
}
void uart_send(String msg)
{
    HWSerial.print(msg.c_str());
}