#include <zmqpp/zmqpp.hpp>
#include <thread>
#include <iostream>
#include <chrono>
#include "modbusServer.h"

void modbusSock(zmqpp::context &context){
    zmqpp::socket_type type = zmqpp::socket_type::pair;

    zmqpp::socket inBout(context, type);
    zmqpp::socket outBout(context, type);

    inBout.set(zmqpp::socket_option::receive_timeout, 0);
    outBout.set(zmqpp::socket_option::send_timeout, 0);

    inBout.bind("inproc://modbusSock");
    outBout.connect("inproc://canbusSock");

    bool theTruth = true;

    while(theTruth) {

        zmqpp::message outMessage;

        outMessage << "41001" << 32;
        outBout.send(outMessage);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

void canbusSock(zmqpp::context& context){

    zmqpp::socket_type type = zmqpp::socket_type::pair;

    zmqpp::socket inBout(context, type);
    zmqpp::socket outBout(context, type);

    inBout.bind("inproc://canbusSock");
    outBout.connect("inproc://modbusSock");

    bool theTruth = true;

    while(theTruth){

        std::cout << "Sending a message..." << std::endl;
        zmqpp::message inboundMsg;
        inBout.receive(inboundMsg, false);

        std::cout << "Got something!" << std::endl;

        std::string registerNum;
        int value;

        inboundMsg>> registerNum >> value;
        std::cout << "Register # " << registerNum << "Value recieved: " << value << "\n";
        std::cout << "Sending out a 3..." << std::endl;

        zmqpp::message outgoingMsg;
        outgoingMsg << "Something" << 3;
        outBout.send(outgoingMsg);

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main(){

    /*
    std::cout << "Making the sockets that we'll be using!"
              << "\n They have to share a context. So send that shit out to the threads!";
    zmqpp::context context;

    std::cout << "Starting the test for Inter Thread Comm" << std::endl;

    std::thread mT(modbusSock, std::ref(context));
    std::thread cT(canbusSock, std::ref(context));

    mT.detach();
    cT.join();
    */

    modbusServer modSer("0.0.0.0", 1502);
    std::thread modbusThread ();

    return 0;

}