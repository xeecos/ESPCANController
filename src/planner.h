#pragma once
void planner_init();
void planner_add_position(float x, float y, float z, float speed);
bool planner_read();