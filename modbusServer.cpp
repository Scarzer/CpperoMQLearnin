//
// Created by irvy on 12/6/15.
//

#include <bits/random.h>
#include <modbus.h>
#include "modbusServer.h"

modbusServer::modbusServer(std::string host, int post) : host(host), port(port){
    ctx = modbus_new_tcp(host.c_str(), port);

    if(ctx == NULL) {
        std::cerr << "There was an error allocating the modbus context" << std::endl;
        throw -1;
    }
    modbusSocket = modbus_tcp_listen(ctx, 1);
}

modbusServer::~modbusServer() {

    modbus_mapping_free(mapping);
    modbus_free(ctx);
}

void modbusServer::makeMapping() {

    mapping = modbus_mapping_new(0,0,1000,0);

    if(mapping == NULL){
        std::cerr << "There was a problem making the mapping" << std::endl;
        return;
    }
    std::cout << "Mapping has been made" << std::endl;

    modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_PROTOCOL);

    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<uint16_t> uniform_dist(1,600);

    for(auto i = 0; i < 1000; ++i){
        uint16_t number = uniform_dist(e1);
        mapping->tab_registers[i] = number;
    }
    mappingInitFlag = true;

    return;
}

void modbusServer::recieveModbus() {

    makeMapping();
    modbus_tcp_accept(ctx, &modbusSocket);

    if(modbusSocket == -1) std::cerr << modbus_strerror(errno) << std::endl;
    for(;;){
        modbus_reply(ctx, query, sizeof(query), mapping);

    }
}
