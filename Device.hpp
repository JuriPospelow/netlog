#pragma once

#include <string>
#include <iostream>

class Device {

public:
    Device() = default;
    Device(std::string_view n, std::string_view i)
    : _name{n}, _ip{i}, _status{"off"} {
        // std::cout << "Constr.:" << this << std::endl;
    }
    ~Device(){
        // std::cout << "Destr.:" << this << std::endl;
    }
    void printAddr() {
        std::cout << "addr.:" << this << std::endl;
    }

    std::string name() { return _name;}
    std::string ip() { return _ip;}
    std::string status() { return _status;}

    void readStatus(std::string_view);
    void readStatusPing();
    void readStatusIPMI();

private:
    std::string _name{"dummy"};
    std::string _ip{"100.100.100.100"};
    std::string _status{"off"};

};