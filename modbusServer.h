//
// Created by irvy on 12/6/15.
//

#ifndef CPPEROMQLEARNIN_MODBUSSERVER_H
#define CPPEROMQLEARNIN_MODBUSSERVER_H


#include <modbus.h>
#include <mutex>
#include <iostream>

class modbusServer {

public:
    modbusServer(std::string host, int post);
    ~modbusServer();

    void recieveModbus();

private:
    int rc;
    modbus_t *ctx;
    int port = 1502;
    int errCount = 0;

    int modbusSocket;

    std::mutex mappingLock;

    bool mappingInitFlag = false;
    modbus_mapping_t *mapping;
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
    std::string host= "0.0.0.0";

    void makeMapping();
};


#endif //CPPEROMQLEARNIN_MODBUSSERVER_H
