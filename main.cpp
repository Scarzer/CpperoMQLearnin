#include <CpperoMQ/All.hpp>

#include <iostream>
#include <thread>
#include <vector>
#include <tuple>
#include <sstream>

using namespace std;
using namespace CpperoMQ;

/* Publisher */

// Pulling something out of the documentation
class Voltage : public Sendable, public Receivable{
public:

    // Whateverz
    virtual bool send(const CpperoMQ::Socket& socket, const bool moreToSend) const override{};

private:

    int voltageVal;
    int moduleNum;
    int shelfNum;
    std::string mName = "Voltage";
};


int main() {
    Context context;
    PublishSocket publisher(context.createPublishSocket());
    publisher.bind("tcp://*:5559");

    while (true){
        std::cout << "Sending multipart message" << std::endl;
        publisher.send(OutgoingMessage("Voltage"),
                       OutgoingMessage("12345"),
                       OutgoingMessage("More Message!"));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}


/* Subscriber

int main(){
    Context context;
    SubscribeSocket subscriber(context.createSubscribeSocket());
    subscriber.connect("tcp://localhost:5556");

    subscriber.subscribe("Voltage");

    int updateNumber = 0;
    long voltageTotal = 0;
    std::vector<std::tuple<int, int>> values;

    for (updateNumber = 0; updateNumber < 100; ++updateNumber){
        IncomingMessage update;
        subscriber.receive(update);

        std::cout << "Message Recieved" << std::endl;

        int voltage = 0;
        std::istringstream iss(std::string(update.charData(), update.size()));
        iss >> voltage;
        voltageTotal += voltage;
        values.push_back(std::tuple<int, int>(voltage, voltageTotal));
    }

    std::cout << "Average Voltage: " << (voltageTotal / updateNumber) << std::endl;
}

*/