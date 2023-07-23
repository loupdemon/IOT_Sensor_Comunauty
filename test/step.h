//
// Created by Administrator on 16/02/2023.
//

#ifndef T_IOT_901_STG_1_MSC_2023_STEP_H
#define T_IOT_901_STG_1_MSC_2023_STEP_H

void step_motor_configuration();
void step_motor_run(int axes, int speed);
void step_motor_run_back(int axes, int speed);
void step_motor_unlock();
void step_motor_wait_idle();
const char* step_motor_status();

#endif //T_IOT_901_STG_1_MSC_2023_STEP_H
