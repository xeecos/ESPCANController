#pragma once
#include <Arduino.h>
#ifdef ARDUINO_USB_MODE
#define HWSerial USBSerial
#else
#define HWSerial Serial
#endif
void uart_init();
int uart_available();
void uart_receive();
void uart_send(String msg);