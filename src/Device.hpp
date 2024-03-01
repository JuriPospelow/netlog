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

    std::string name() const { return _name;}
    std::string ip() const { return _ip;}
    std::string status() const { return _status;}

    void readStatus(std::string_view);

private:
    std::string _name{"dummy"};
    std::string _ip{"100.100.100.100"};
    std::string _status{"off"};

};
