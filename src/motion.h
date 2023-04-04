#pragma once
#include <stdint.h>
void motion_init();
void motion_run(float dx, float dy, float dz, float distance, float speed);
void motion_next();