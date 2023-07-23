//
// Created by Administrator on 16/02/2023.
//

#ifndef T_IOT_901_STG_1_MSC_2023_BASE_H
#define T_IOT_901_STG_1_MSC_2023_BASE_H

const char* readerCard();
int readProduct();
void login();
const char* getToken();
int createMovement();
void setCurrentWareHouse(int w_h);
int getCurrentWareHouse();
const char* getCurrentProductId();
void setCurrentProductId(const char* p_id);
void setCurrentProductExit(int p_ex);
int getCurrentProductExit();

#endif //T_IOT_901_STG_1_MSC_2023_BASE_H
