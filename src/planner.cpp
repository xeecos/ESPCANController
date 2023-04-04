#include "planner.h"
#include "math.h"
#include "motion.h"
#include "uart.h"
#define MAX_BUFFER_COUNT 16
float _dx[MAX_BUFFER_COUNT];
float _dy[MAX_BUFFER_COUNT];
float _dz[MAX_BUFFER_COUNT];
float _speed[MAX_BUFFER_COUNT];
float _distance[MAX_BUFFER_COUNT];

float _last_x = 0.0f;
float _last_y = 0.0f;
float _last_z = 0.0f;

int _pop_idx = 0;
int _push_idx = 0;
void planner_init()
{
}

void planner_add_position(float x, float y, float z, float speed)
{
    int idx = _push_idx % MAX_BUFFER_COUNT;
    float dx = x - _last_x;
    float dy = y - _last_y;
    float dz = z - _last_z;
    _dx[idx] = dx;
    _dy[idx] = dy;
    _dz[idx] = dz;
    _distance[idx] = sqrtf(dx * dx + dy * dy + dz * dz);
    _speed[idx] = speed;
    _last_x = x;
    _last_y = y;
    _last_z = z;
    _push_idx++;
}
bool planner_read()
{
    if(_pop_idx!=_push_idx)
    {
        int idx = _pop_idx % MAX_BUFFER_COUNT;
        motion_run(_dx[idx], _dy[idx], _dz[idx], _distance[idx], _speed[idx]);
        _pop_idx++;
        return true;
    }
    return false;
}