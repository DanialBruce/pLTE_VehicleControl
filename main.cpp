#include "mbed.h"
#include "EthernetInterface.h"
#include "MbedJSONValue.h"
#include <string>

#define REMOTE_PORT 5000
#define LOCAL_PORT 5001
#define BUFF_SIZE 256

EthernetInterface eth;

uint8_t ip[4] = {172, 16, 10, 31}; //remote vehicle IP
SocketAddress clientUDP(ip, NSAPI_IPv4); // remote vehicle
UDPSocket serverUDP;

AnalogIn steering(A0); //stick 1, right horizontal
AnalogIn speed(A1); //stick 2, left vertical
AnalogIn aux(A2); //not in use, stick 3, right vertical
AnalogIn gearshift(A3); //stick 4, left horizontal

DigitalIn indicatorRight(D8); //indicator right switch
DigitalIn indicatorLeft(D9); //indicator left switch
DigitalIn mainBeam(D10); //main and backlight switch

std::string s;

int main()
{
    //eth.set_network("IP, mask, gateway"); //use only when not using dhcp
    eth.connect(); 

    SocketAddress netAddress;
    eth.get_ip_address(&netAddress);
    printf("\nIP Address: %s\n", netAddress.get_ip_address());
    printf("\nMAC address: %s\n", eth.get_mac_address());

    serverUDP.open(&eth);
    int err = serverUDP.bind(LOCAL_PORT);
    printf("Port status is: %d\n", err);
    clientUDP.set_port(REMOTE_PORT);

    while(true){
        MbedJSONValue values;

        values["steering"] = steering.read_u16(); //read stick 1 value
        values["speed"] = speed.read_u16(); //read stick 2 value
        values["gearshift"] = gearshift.read_u16(); //read stick 4 value
        values["indicatorRight"] = indicatorRight.read(); //read indicator right switch value
        values["indicatorLeft"] = indicatorLeft.read(); //read indicator left switch value
        values["mainBeam"] = mainBeam.read(); //read main light switch value

        s = values.serialize(); //convert json values to string
        
        serverUDP.sendto(clientUDP, s.c_str(), s.size()); //send serialized json to vehicle
        //printf("sent json: %s\n", s.c_str());
        ThisThread::sleep_for(50ms); //wait for 50ms
    }
}
