//
// Created by Administrator on 16/02/2023.
//

#ifndef T_IOT_901_STG_1_MSC_2023_REQ_H
#define T_IOT_901_STG_1_MSC_2023_REQ_H

enum HTTP_METHOD {
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE
};

const char* requestGeneric(const char* url, enum HTTP_METHOD method, const char* token, const char* data);
const char* requestGet(const char* url, const char* token);
const char* requestPost(const char* url, const char* data, const char* token);
const char* requestPut(const char* url, const char* data, const char* token);

#endif //T_IOT_901_STG_1_MSC_2023_REQ_H
